#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::io::{self, prelude::*};

fn f(
    pos: usize,
    row: usize,
    players: &Vec<Vec<usize>>,
    dp: &mut Vec<Vec<usize>>,
    dpd: &mut Vec<Vec<bool>>,
) -> usize {
    if pos == players[0].len() {
        return u64::MIN as usize;
    }
    if dpd[row][pos] {
        return dp[row][pos];
    }
    let mut ans = players[row][pos] + f(pos + 1, row ^ 1, players, dp, dpd);
    ans = ans.max(f(pos + 1, row, players, dp, dpd));
    ans = ans.max(f(pos + 1, row ^ 1, players, dp, dpd));
    dp[row][pos] = ans;
    dpd[row][pos] = true;
    ans
}
fn solve<R: BufRead, W: Write>(mut input: FastInput<R>, mut w: W) {
    // let t: usize = input.next();
    let t: usize = 1;
    for _ in 0..t {
        let n: usize = input.next();
        let mut a: Vec<usize> = vec![0usize; n];
        for x in a.iter_mut() {
            *x = input.next();
        }
        let mut b: Vec<usize> = vec![0usize; n];
        for x in b.iter_mut() {
            *x = input.next();
        }
        let players: Vec<Vec<usize>> = vec![a, b];
        let mut dp: Vec<Vec<usize>> = vec![vec![0usize; n]; 2];
        let mut dpd: Vec<Vec<bool>> = vec![vec![false; n]; 2];
        // f(pos, row) = maximum height possible starting from position pos, with the next player having to be taken from otherrow.
        // f(pos, row) = max(height[pos][row] + f(pos+1, otherrow), max(f(pos+1, row),f(pos+1, otherrow)))
        // ans = max (f(0,0), f(0,1))
        let mut ans = f(0, 0, &players, &mut dp, &mut dpd);
        ans = ans.max(f(0, 1, &players, &mut dp, &mut dpd));
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
