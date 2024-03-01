#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::io::{self, prelude::*};

fn solve<R: BufRead, W: Write>(mut input: FastInput<R>, mut w: W) {
    let t: usize = input.next();
    // let t: usize = 1;
    for _ in 0..t {
        let n: usize = input.next();
        let s1: Vec<u8> = input.next();
        let ss1 = std::str::from_utf8(&s1).unwrap();
        let s2: Vec<u8> = input.next();
        let ss2 = std::str::from_utf8(&s2).unwrap();
        // let mut ps1: Vec<usize> = Vec::new();
        // let mut sum: usize = 0;
        // for c in s1.iter() {
        //     ps1.push(sum);
        //     if c == &b'1' {
        //         sum += 1;
        //     }
        // }
        // ps1.push(sum);
        // sum = 0;
        // let mut ps2: Vec<usize> = Vec::new();
        // for c in s2.iter() {
        //     ps2.push(sum);
        //     if c == &b'1' {
        //         sum += 1;
        //     }
        // }
        // ps2.push(sum);
        // let mut minindex: usize = n + 1;
        // let mut minvale: usize = u64::MAX as usize;
        // let mut cnt: usize = 0;
        // for change in 1..=n {
        //     let top = ps1[change] - ps1[0];
        //     let bot = ps2[n] - ps2[change - 1];
        //     if top + bot == minvale {
        //         cnt += 1;
        //     } else if top + bot < minvale {
        //         minvale = top + bot;
        //         minindex = change;
        //         cnt = 1;
        //     }
        // }
        // for i in 0..minindex {
        //     write!(w, "{}", s1[i] as char);
        // }
        // for i in (minindex - 1)..n {
        //     write!(w, "{}", s2[i] as char);
        // }
        // writeln!(w, "\n{}", cnt);

        let mut break_index = n - 1;
        for i in 0..(n - 1) {
            if s1[i + 1] == b'1' && s2[i] == b'0' {
                break_index = i;
                break;
            }
        }
        let seq = String::from(&ss1[..=break_index]) + &ss2[break_index..];
        let mut ans = 1;
        let mut i: usize = break_index;
        while i > 0 {
            if s1[i] == s2[i - 1] {
                ans += 1;
                i -= 1;
            } else {
                break;
            }
        }
        writeln!(w, "{}", seq);
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
                        if buf[self.pos] == b'-' {
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
