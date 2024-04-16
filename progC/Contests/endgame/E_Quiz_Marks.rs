#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::io::{self, prelude::*};

const MOD: usize = 1_000_000_007;
fn solve<R: BufRead, W: Write>(mut input: FastInput<R>, mut w: W) {
    let t: usize = input.next();
    // let t: usize = 1;
    for _ in 0..t {
        let n: usize = input.next();
        let s: Vec<u8> = input.next();
        let s = s.iter().map(|&x| x - b'0').collect::<Vec<u8>>();
        let mut slices: Vec<(usize, usize)> = Vec::new();

        let mut cur = s[0];
        let mut c = 1;
        let mut res = 0;
        for i in 1..n {
            if s[i] == cur {
                if res < c {
                    slices.clear();
                    slices.push((i - c, i - 1));
                    res = c;
                }
                if res == c {
                    slices.push((i - c, i - 1));
                }
            } else {
                c += 1;
                cur = s[i];
            }
        }
        let og = s.clone();
        let mut ans = 0;
        let mut currentinsert: (usize, u8) = (0, 0);

        for slice in slices {
            let (l, r) = slice;
            let mut s = og.clone();
            let element = s[l] ^ 1;
            s.insert(l, element);
            let mut c = 1;
            for i in (0..l).rev() {
                if i == 0 {
                    c += 1;
                } else if s[i] != s[i - 1] {
                    c += 1;
                } else {
                    break;
                }
            }
            if c + res > ans {
                ans = c + res;
                currentinsert = (l, element);
            }
            let mut s = og.clone();
            let element = s[r] ^ 1;
            s.insert(r + 1, element);
            let mut c = 1;
            for i in (r + 1)..n {
                if s[i] != s[i - 1] {
                    c += 1;
                } else {
                    break;
                }
            }
            if c + res > ans {
                ans = c + res;
                currentinsert = (r + 1, element);
            }
        }
        let mut s = og.clone();
        s.insert(currentinsert.0, currentinsert.1 as u8);
        let mut c = 1;
        let mut ans: usize = 0;
        let mut cur = s[0];
        for i in 1..=n {
            if s[i] != cur {
                c += 1;
                cur = s[i];
            } else {
                ans += (c * (c + 1)) / 2;
                c = 1;
            }
        }
        ans += (c * (c + 1)) / 2;
        writeln!(w, "{}", ans);
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
