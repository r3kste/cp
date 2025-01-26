#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::io::{self, prelude::*};

const MOD: usize = 1_000_000_007;
fn solve<R: BufRead, W: Write>(mut input: FastInput<R>, mut w: W) {
    // let t: usize = 1;
    let case: i32 = input.next();
    let mut s: String = String::new();
    if case == 1 {
        s += "yoink a
yoink b
*slaps a on top of b*
yeet b
go touch some grass"
    } else if case == 2 {
        s += "yoink a
bruh b is lowkey just 0
rip this b fell off by a
vibe check a ratios b
simp for 7
bruh a is lowkey just b
yeet a
go touch some grass"
    } else if case == 3 {
        s += "yoink n
yoink a
bruh m is lowkey just a[0]
bruh i is lowkey just 1
vibe check n ratios i
simp for 9
yeet m
go touch some grass
vibe check a[i] ratios m
bruh m is lowkey just a[i]
*slaps 1 on top of i*
simp for 5"
    } else {
        s += "yoink n
yoink a
yoink k
bruh temp is lowkey just n
rip this temp fell off by 1
bruh i is lowkey just 0
vibe check n ratios i
simp for 12
rip this k fell off by 1
yeet a[k]
go touch some grass
bruh j is lowkey just 0
bruh actualtemp is lowkey just temp
rip this actualtemp fell off by i
vibe check actualtemp ratios j
simp for 19
*slaps 1 on top of i*
simp for 7
bruh next is lowkey just j
*slaps 1 on top of next*
vibe check a[next] ratios a[j]
simp for 25
*slaps 1 on top of j*
simp for 15
bruh newtemp is lowkey just a[j]
bruh a[j] is lowkey just a[next]
bruh a[next] is lowkey just newtemp
simp for 23";
    }
    writeln!(w, "{s}");
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
