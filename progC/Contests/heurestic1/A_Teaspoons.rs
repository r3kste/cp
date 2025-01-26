#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::io::{self, prelude::*};

#[derive(Debug, Clone, Copy)]
struct Point {
    x: i32,
    y: i32,
}

fn solve<R: BufRead, W: Write>(mut input: FastInput<R>, mut w: W) {
    let n: usize = input.next();
    let W: usize = input.next();
    let mut points: Vec<Point> = Vec::new();
    let mut weights: Vec<i32> = Vec::new();
    for i in 0..n {
        let x: i32 = input.next();
        let y: i32 = input.next();
        points.push(Point { x, y });
        let w: i32 = input.next();
        weights.push(w);
    }

    let current: Point = Point { x: 0, y: 0 };
    let mut out: Vec<i32> = Vec::new();
    out.push(0);

    let mut distances: Vec<Vec<usize>> = Vec::new();
    for i in 0..n {
        let mut row: Vec<usize> = Vec::new();
        for j in 0..n {
            let distance: usize =
                ((points[i].x - points[j].x).pow(2) + (points[i].y - points[j].y).pow(2)) as usize;
            row.push(distance);
        }
        distances.push(row);
    }

    // sort by weight
    let mut sorted_weights: Vec<(i32, usize)> =
        weights.iter().enumerate().map(|(i, &w)| (w, i)).collect();
    sorted_weights.sort_by(|a, b| a.0.cmp(&b.0));

    // bin weights
    // if lesser than x% of W, then bin them into n bins
    // if greater than x% of W, then do not bin them
    let N_BINS: usize = 3;
    let x = 100;
    // let W = std::cmp::max(W, sorted_weights.last().unwrap().0 as usize);
    let threshold = W as i32 * x / 100;
    if threshold < n as i32 {
        let N_BINS = 1;
    } else {
        let N_BINS = n;
    }

    let mut separate: Vec<i32> = Vec::new();
    let mut binned: Vec<(i32, i32, i32)> = Vec::new();
    for (w, i) in sorted_weights.iter() {
        let w = *w;
        let i = *i;
        let point = points[i];
        let (x, y) = (point.x, point.y);

        if w <= threshold {
            let bin = w * N_BINS as i32 / W as i32;
            let quadrant = match (x >= 0, y >= 0) {
                (true, true) => match (x >= y, x >= 2 * y, 2 * x >= y) {
                    (true, true, _) => 1,
                    (true, false, true) => 2,
                    (true, false, false) => 3,
                    (false, _, _) => 4,
                },
                (true, false) => match (x >= -y, x >= -2 * y, 2 * x >= -y) {
                    (true, true, _) => 5,
                    (true, false, true) => 6,
                    (true, false, false) => 7,
                    (false, _, _) => 8,
                },
                (false, true) => match (-x >= y, -x >= 2 * y, 2 * -x >= y) {
                    (true, true, _) => 13,
                    (true, false, true) => 14,
                    (true, false, false) => 15,
                    (false, _, _) => 16,
                },
                (false, false) => match (-x >= -y, -x >= -2 * y, 2 * -x >= -y) {
                    (true, true, _) => 9,
                    (true, false, true) => 10,
                    (true, false, false) => 11,
                    (false, _, _) => 12,
                },
            };
            binned.push((i as i32, bin, quadrant));
        } else {
            separate.push(i as i32);
        }
    }

    for &e in separate.iter() {
        out.push(e + 1);
        out.push(0);
    }
    for expected_bin in 0..=N_BINS {
        for expected_quadrant in 1..=16 {
            for &(i, bin, quadrant) in binned.iter() {
                if bin == expected_bin as i32 && quadrant == expected_quadrant {
                    out.push(i + 1);
                }
            }
            if out.last() != Some(&0) {
                out.push(0);
            }
        }
    }

    writeln!(w, "{}", out.len());
    for e in out {
        write!(w, "{} ", e);
    }
    writeln!(w);
}

fn main() {
    let stdin = io::stdin();
    let stdout = io::stdout();
    let input = FastInput::from(stdin.lock());
    let writer = io::BufWriter::new(stdout.lock());
    solve(input, writer);
}

trait TokenStream<T> {
    fn next(&mut self) -> T;
}

struct FastInput<R> {
    stdin: R,
    pos: usize,
}

impl<R: BufRead> From<R> for FastInput<R> {
    fn from(r: R) -> Self {
        FastInput { stdin: r, pos: 0 }
    }
}

impl<R: BufRead> TokenStream<u8> for FastInput<R> {
    fn next(&mut self) -> u8 {
        loop {
            if let Ok(buf) = self.stdin.fill_buf() {
                while self.pos < buf.len() {
                    self.pos += 1;
                    if buf[self.pos - 1] > 32 {
                        return buf[self.pos - 1];
                    }
                }
                if self.pos == 0 {
                    return 0;
                }
            } else {
                return 0;
            }
            self.stdin.consume(self.pos);
            self.pos = 0;
        }
    }
}

impl<R: BufRead> TokenStream<Vec<u8>> for FastInput<R> {
    fn next(&mut self) -> Vec<u8> {
        let mut ans = Vec::new();
        let mut parse_token = false;
        loop {
            if let Ok(buf) = self.stdin.fill_buf() {
                if !parse_token {
                    while self.pos < buf.len() && buf[self.pos] <= 32 {
                        self.pos += 1;
                    }
                }
                while self.pos < buf.len() && buf[self.pos] > 32 {
                    parse_token = true;
                    ans.push(buf[self.pos]);
                    self.pos += 1;
                }
                if self.pos != buf.len() || self.pos == 0 {
                    return ans;
                }
            }
            self.stdin.consume(self.pos);
            self.pos = 0;
        }
    }
}

macro_rules! ustream {
    ($($t:ident),+) => {$(
        impl<R: BufRead> TokenStream<$t> for FastInput<R> {
           fn next(&mut self) -> $t {
                let mut ans = 0;
                let mut parse_token = false;
                loop {
                    if let Ok(buf) = self.stdin.fill_buf() {
                        if !parse_token {
                            while self.pos < buf.len() && buf[self.pos] <= 32 {
                                self.pos += 1;
                            }
                        }
                        while self.pos < buf.len() && buf[self.pos] > 32 {
                            parse_token = true;
                            ans = ans * 10 + (buf[self.pos] - b'0') as $t;
                            self.pos += 1;
                        }
                        if self.pos != buf.len() || self.pos == 0 {
                            return ans;
                        }
                    }
                    self.stdin.consume(self.pos);
                    self.pos = 0;
                }
           }
        }
    )+}
}

macro_rules! istream {
    ($($t:ident),+) => {$(
        impl<R: BufRead> TokenStream<$t> for FastInput<R> {
           fn next(&mut self) -> $t {
                let mut ans = 0;
                let mut negative = false;
                let mut parse_token = false;
                loop {
                    if let Ok(buf) = self.stdin.fill_buf() {
                        if !parse_token {
                            while self.pos < buf.len() && buf[self.pos] <= 32 {
                                self.pos += 1;
                            }
                        }
                        if self.pos < buf.len() && buf[self.pos] == b'-' {
                            negative = true;
                            self.pos += 1;
                        }
                        while self.pos < buf.len() && buf[self.pos] > 32 {
                            parse_token = true;
                            ans = ans * 10 + (buf[self.pos] - b'0') as $t;
                            self.pos += 1;
                        }
                        if self.pos != buf.len() || self.pos == 0 {
                            return if negative { -ans } else { ans };
                        }
                    }
                    self.stdin.consume(self.pos);
                    self.pos = 0;
                }
           }
        }
    )+}
}

ustream!(usize);
istream!(i32);
