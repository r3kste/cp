#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::{
    collections::HashMap,
    io::{self, prelude::*},
};

fn solve<R: BufRead, W: Write>(mut input: FastInput<R>, mut w: W) {
    let t: usize = input.next();
    // let t: usize = 1;
    for _ in 0..t {
        let n: usize = input.next();
        let k: usize = input.next();
        let mut lk: isize = 2 * k as isize;
        let mut rk: isize = 2 * k as isize;
        let mut a: Vec<i32> = vec![0i32; 2 * n];
        for x in a.iter_mut() {
            *x = input.next();
        }
        let mut freq1: HashMap<i32, usize> = HashMap::new();
        let mut freq2: HashMap<i32, usize> = HashMap::new();
        for i in 0..n {
            *freq1.entry(a[i]).or_default() += 1;
            *freq2.entry(a[i + n]).or_default() += 1;
        }
        let mut l: Vec<i32> = Vec::new();
        let mut r: Vec<i32> = Vec::new();
        for (e, c) in freq1.iter_mut() {
            if *c == 2 {
                if lk >= 2 {
                    l.push(*e);
                    l.push(*e);
                    *c = 0;
                }
                lk -= 2;
                if lk == 0 {
                    break;
                }
            }
        }
        for (e, c) in freq2.iter_mut() {
            if *c == 2 {
                if rk >= 2 {
                    r.push(*e);
                    r.push(*e);
                    *c = 0;
                }
                rk -= 2;
                if rk == 0 {
                    break;
                }
            }
        }
        if lk == 0 || rk == 0 {
            for i in l {
                write!(w, "{} ", i);
            }
            writeln!(w, "");
            for i in r {
                write!(w, "{} ", i);
            }
            writeln!(w, "");
        } else {
            let rem = lk as usize;
            for (e, c) in freq1 {
                if c == 1 {
                    l.push(e);
                    lk -= 1;
                    r.push(e);
                    rk -= 1;
                    if lk == 0 || rk == 0 {
                        break;
                    }
                }
            }
            if lk == 0 || rk == 0 {
                for i in l {
                    write!(w, "{} ", i);
                }
                writeln!(w, "");
                for i in r {
                    write!(w, "{} ", i);
                }
                writeln!(w, "");
            }
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
