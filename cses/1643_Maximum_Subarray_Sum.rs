#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::io::{self, prelude::*};

const MOD: usize = 1_000_000_007;

fn solve<R: BufRead, W: Write>(input: &mut FastInput<R>, w: &mut W) {
    let n: i64 = input.next();
    let a: Vec<i64> = (0..n).map(|_| input.next()).collect();

    let mut l: usize = 0;
    let mut r: usize = 1;

    let mut max_sum = a[l];
    let mut s = a[l];

    while r < n as usize {
        if l == r {
            s += a[r];
            r += 1;

            if r == n as usize {
                max_sum = max_sum.max(s);
                break;
            }
        }

        if s < 0 {
            r += 1;
            l = r - 1;
            s = a[l];
        } else {
            s += a[r];
            r += 1;
        }

        max_sum = max_sum.max(s);
    }

    writeln!(w, "{}", max_sum);
}

fn main() {
    let stdin = io::stdin();
    let stdout = io::stdout();
    let mut input = FastInput::from(stdin.lock());
    let mut writer = io::BufWriter::new(stdout.lock());

    // let t: usize = input.next();
    let t: usize = 1;
    for _ in 0..t {
        solve(&mut input, &mut writer);
    }
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
istream!(i64);
