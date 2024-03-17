#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::io::{self, prelude::*};

const MOD: usize = 1_000_000_007;
fn solve<R: BufRead, W: Write>(mut input: FastInput<R>, mut w: W) {
    let t: usize = 1;
    'test: for _ in 0..t {
        let n: usize = input.next();
        let p: usize = input.next();
        let mut arr: Vec<usize> = vec![0usize; 2 * n];
        let mut sum = 0;
        for i in 0..n {
            arr[i] = input.next();
            arr[i + n] = arr[i];
            sum += arr[i];
        }
        let cycles = p / sum;
        let p = p % sum;
        if p == 0 {
            writeln!(w, "1 {}", cycles * n);
            continue 'test;
        }
        let mut l = 0;
        let mut s = 0;
        let mut step = i32::MAX as usize;
        let mut pos = -1;
        for r in 0..2 * n {
            s += arr[r];
            if s >= p {
                if (r - l + 1) < step {
                    step = r - l + 1;
                    pos = (l % n) as i32;
                }
                while s >= p {
                    s -= arr[l];
                    l += 1;
                    if s >= p && r - l + 1 < step {
                        step = r - l + 1;
                        pos = (l % n) as i32;
                    }
                }
            }
        }
        while l < 2 * n && s >= p {
            s -= arr[l];
            l += 1;
            if s >= p && 2 * n - l + 1 < step {
                step = 2 * n - l + 1;
                pos = (l % n) as i32;
            }
        }
        writeln!(w, "{} {}", 1 + pos, step + n * cycles);
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
