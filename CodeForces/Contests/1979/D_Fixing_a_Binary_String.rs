#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::io::{self, prelude::*};

fn solve<R: BufRead, W: Write>(mut input: FastInput<R>, mut w: W) {
    let t: usize = input.next();
    // let t: usize = 1;
    for _ in 0..t {
        let n: usize = input.next();
        let k: usize = input.next();

        let s: Vec<u8> = input.next();

        let mut zero_ct: Vec<(usize, usize)> = Vec::new();
        let mut one_ct: Vec<(usize, usize)> = Vec::new();

        let mut tot_zero = 0;
        let mut tot_one = 0;

        let mut prev_count = 1;
        for i in 1..n {
            if s[i] == s[i - 1] {
                prev_count += 1;
            } else {
                if s[i - 1] == b'0' {
                    zero_ct.push((prev_count, i - prev_count));
                }
                if s[i - 1] == b'1' {
                    one_ct.push((prev_count, i - prev_count));
                }
                prev_count = 1;
            }
        }
        if s[n - 1] == b'0' {
            zero_ct.push((prev_count, n - prev_count));
        }
        if s[n - 1] == b'1' {
            one_ct.push((prev_count, n - prev_count));
        }

        // writeln!(w, "{:?}\n{:?}\n", zero_ct, one_ct);

        for i in 0..n {
            if s[i] == b'0' {
                tot_zero += 1;
            } else {
                tot_one += 1;
            }
        }

        let expected = k;

        let zero_mut: bool = zero_ct.iter().all(|e| e.0 == expected);
        let one_mut: bool = one_ct.iter().all(|e| e.0 == expected);

        let mut res: i32 = 0;

        let mut excess: Vec<(usize, usize)> = Vec::new();
        let mut defict: Vec<(usize, usize)> = Vec::new();
        if (!zero_mut && one_mut) || (one_ct.len() == 0) {
            for e in zero_ct.iter() {
                if e.0 > expected {
                    excess.push(*e);
                }
                if e.0 < expected {
                    defict.push(*e);
                }
            }
        } else if (!one_mut && zero_mut) || (zero_ct.len() == 0) {
            for e in one_ct.iter() {
                if e.0 > expected {
                    excess.push(*e);
                }
                if e.0 < expected {
                    defict.push(*e);
                }
            }
        } else {
            res = -1;
        }

        if res != -1 {
            if excess.len() == 0 && defict.len() == 0 {
                res = n as i32;
            } else if excess.len() > 1 {
                res = -1;
            } else {
                if excess.len() == 0 {
                    if defict.len() != 2 {
                        res = -1;
                    } else {
                        let pos1 = defict[0].1;
                        let pos2 = defict[1].1;

                        if pos2 == n - defict[1].0 {
                            res = (defict[0].0 + defict[0].1) as i32;
                        } else {
                            res = -1;
                        }
                    }
                } else if excess.len() == 1 {
                    if defict.len() == 0 {
                        let pos1 = excess[0].1;
                        let pos2 = n - 1;

                        res = (pos1 + (excess[0].0 - expected)) as i32;
                    } else if defict.len() == 1 {
                        let pos1 = excess[0].1;
                        let pos2 = defict[0].1;

                        if pos2 == n - 1 {
                            res = (pos1 + (excess[0].0 - expected)) as i32;
                        } else {
                            res = -1;
                        }
                    } else {
                        res = -1;
                    }
                } else {
                    res = -1;
                }
            }
        }

        writeln!(w, "{}", res);
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
