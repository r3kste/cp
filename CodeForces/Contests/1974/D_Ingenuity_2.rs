#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::collections::HashMap;
use std::io::{self, prelude::*};

fn solve<R: BufRead, W: Write>(mut input: FastInput<R>, mut w: W) {
    let t: usize = input.next();
    for _ in 0..t {
        let n: usize = input.next();
        let s: Vec<u8> = input.next();

        let mut freq: HashMap<u8, usize> = [
            ('N' as u8, 0),
            ('E' as u8, 0),
            ('S' as u8, 0),
            ('W' as u8, 0),
        ]
        .iter()
        .cloned()
        .collect();
        for c in s {
            *freq.entry(c).or_insert(0) += 1;
        }

        let (y1, y2, y1_key, y2_key) = if freq[&('N' as u8)] < freq[&('S' as u8)] {
            (freq[&('N' as u8)], freq[&('S' as u8)], 'N' as u8, 'S' as u8)
        } else {
            (freq[&('S' as u8)], freq[&('N' as u8)], 'S' as u8, 'N' as u8)
        };

        let (x1, x2, x1_key, x2_key) = if freq[&('E' as u8)] < freq[&('W' as u8)] {
            (freq[&('E' as u8)], freq[&('W' as u8)], 'E' as u8, 'W' as u8)
        } else {
            (freq[&('W' as u8)], freq[&('E' as u8)], 'W' as u8, 'E' as u8)
        };

        if (y2 - y1) % 2 == 0 && (x2 - x1) % 2 == 0 {
            let mut y1_list = Vec::new();
            let mut y2_list = Vec::new();
            let mut x1_list = Vec::new();
            let mut x2_list = Vec::new();

            if y1 > 0 {
                for i in 0..(y1 - 1) {
                    y1_list.push('R' as u8);
                    y2_list.push('R' as u8);
                }
                y1_list.push('H' as u8);
                y2_list.push('H' as u8);
            }

            for _ in 0..((y2 - y1) / 2) {
                y2_list.push('R' as u8);
                y2_list.push('H' as u8);
            }

            if x1 > 0 {
                for i in 0..(x1 - 1) {
                    x1_list.push('H' as u8);
                    x2_list.push('H' as u8);
                }
                x1_list.push('R' as u8);
                x2_list.push('R' as u8);
            }

            for _ in 0..(x2 - x1) / 2 {
                x2_list.push('R' as u8);
                x2_list.push('H' as u8);
            }

            let mut output = String::new();
            for &c in &s {
                if c == y1_key {
                    output.push(y1_list.remove(0) as char);
                } else if c == y2_key {
                    output.push(y2_list.remove(0) as char);
                } else if c == x1_key {
                    output.push(x1_list.remove(0) as char);
                } else if c == x2_key {
                    output.push(x2_list.remove(0) as char);
                }
            }

            if output.matches('R').count() == 0 || output.matches('H').count() == 0 {
                writeln!(w, "NO");
            } else {
                writeln!(w, "{}", output);
            }
        } else {
            writeln!(w, "NO");
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
