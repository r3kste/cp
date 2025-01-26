#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::io::{self, prelude::*};

const MOD: usize = 1_000_000_007;

fn f(
    pos: usize,
    sum: usize,
    cnt: &Vec<usize>,
    dp: &mut Vec<Vec<usize>>,
    dpd: &mut Vec<Vec<bool>>,
) -> usize {
    if dpd[sum][pos] {
        return dp[sum][pos];
    }
    let ans = (f(pos - 1, 2, cnt, dp, dpd) * cnt[(sum + 1) % 3]
        + f(pos - 1, 1, cnt, dp, dpd) * cnt[(sum + 2) % 3]
        + f(pos - 1, 0, cnt, dp, dpd) * cnt[sum % 3])
        % MOD;
    dp[sum][pos] = ans;
    dpd[sum][pos] = true;
    ans
}
fn solve<R: BufRead, W: Write>(mut input: FastInput<R>, mut w: W) {
    // let t: usize = input.next();
    let t: usize = 1;
    for _ in 0..t {
        let n: usize = input.next();
        let l: usize = input.next();
        let r: usize = input.next();
        let c0: usize = (r / 3) + 1 - ((l + 2) / 3);
        let c1: usize = ((r - 1) / 3) + 1 - ((l + 1) / 3);
        let c2: usize;
        if r <= 1 {
            c2 = 0;
        } else {
            c2 = ((r - 2) / 3) + 1 - (l / 3);
        }
        let cnt: Vec<usize> = vec![c0, c1, c2];

        // f(pos, sum) = number of ways to restore array from 0..=pos to get sum % 3 as 'sum'
        // ans = f(n-1, 0);

        let mut dp: Vec<Vec<usize>> = vec![vec![0usize; n]; 3];
        let mut dpd: Vec<Vec<bool>> = vec![vec![false; n]; 3];
        dp[0][0] = cnt[0];
        dp[1][0] = cnt[1];
        dp[2][0] = cnt[2];
        dpd[0][0] = true;
        dpd[1][0] = true;
        dpd[2][0] = true;

        let ans = f(n - 1, 0, &cnt, &mut dp, &mut dpd);
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
