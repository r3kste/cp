#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::{
    collections::HashMap,
    io::{self, prelude::*},
};

fn solve<R: BufRead, W: Write>(mut input: FastInput<R>, mut w: W) {
    let t: usize = input.next();
    // let t: usize = 1;

    let mut angles: HashMap<usize, f64> = HashMap::new();
    angles.insert(1, 60.0);
    angles.insert(2, 30.0);
    angles.insert(3, 0.0);
    angles.insert(4, 330.0);
    angles.insert(5, 300.0);
    angles.insert(6, 270.0);
    angles.insert(7, 240.0);
    angles.insert(8, 210.0);
    angles.insert(9, 180.0);
    angles.insert(10, 150.0);
    angles.insert(11, 120.0);
    angles.insert(12, 90.0);

    for _ in 0..t {
        let a: usize = input.next();
        let b: usize = input.next();
        let c: usize = input.next();
        let d: usize = input.next();

        let t1 = angles.get(&a).unwrap();
        let t2 = angles.get(&b).unwrap();
        let t3 = angles.get(&c).unwrap();
        let t4 = angles.get(&d).unwrap();

        let mut t2 = t2 - t1;
        let mut t3 = t3 - t1;
        let mut t4 = t4 - t1;
        let t1 = 0.0;

        if t2 < 0.0 {
            t2 += 360.0;
        }
        if t3 < 0.0 {
            t3 += 360.0;
        }
        if t4 < 0.0 {
            t4 += 360.0;
        }

        if t3 < t2 {
            if t4 < t2 {
                writeln!(w, "NO");
            } else {
                writeln!(w, "YES");
            }
        } else {
            if t4 > t2 {
                writeln!(w, "NO");
            } else {
                writeln!(w, "YES");
            }
        }
    }
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
