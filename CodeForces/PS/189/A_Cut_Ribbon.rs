#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::io::{self, prelude::*};

fn f(n: isize, (a, b, c): (isize, isize, isize), dp: &mut Vec<i32>, dpd: &mut Vec<bool>) -> i32 {
    if n == 0 {
        return 0;
    }
    if dpd[n as usize] {
        return dp[n as usize];
    }
    let mut ans: i32 = -1;
    if n >= a {
        ans = ans.max(f(n - a, (a, b, c), dp, dpd));
    }
    if n >= b {
        ans = ans.max(f(n - b, (a, b, c), dp, dpd));
    }
    if n >= c {
        ans = ans.max(f(n - c, (a, b, c), dp, dpd));
    }
    if ans != -1 {
        ans += 1;
    }
    dp[n as usize] = ans;
    dpd[n as usize] = true;
    ans
}
fn solve<R: BufRead, W: Write>(mut input: FastInput<R>, mut w: W) {
    // let t: usize = input.next();
    let t: usize = 1;
    for _ in 0..t {
        let n: isize = input.next();
        let a: isize = input.next();
        let b: isize = input.next();
        let c: isize = input.next();

        let minn = a.min(b).min(c);

        // f(n) = maximum number of pieces of ribbon of length n
        // f(n) = max(f(n-a), f(n-b), f(n-c)) + 1
        // f(0) = 0
        // f(n) = -1 if n < 0
        // ans = f(n)

        let mut dp = vec![-1; (n + 1) as usize];
        let mut dpd = vec![false; (n + 1) as usize];
        dp[0] = 0;
        let ans = f(n, (a, b, c), &mut dp, &mut dpd);
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

macro_rules! impl_token_stream {
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

impl_token_stream!(isize);
impl_token_stream!(i32);
