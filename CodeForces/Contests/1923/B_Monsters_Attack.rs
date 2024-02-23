#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::{
    collections::HashMap,
    io::{self, prelude::*},
};

fn solve<R: BufRead, W: Write>(mut input: FastInput<R>, mut w: W) {
    let t: i64 = input.next();
    // let t: usize = 1;
    'test: for _ in 0..t {
        let n: i64 = input.next();
        let k: i64 = input.next();

        let mut a: Vec<i64> = vec![0i64; n as usize];
        for x in a.iter_mut() {
            *x = input.next();
        }

        let mut x: Vec<i64> = vec![0i64; n as usize];
        let mut maxpos: i64 = 0;
        for pos in x.iter_mut() {
            *pos = input.next();
            maxpos = maxpos.max((*pos).abs());
        }
        let mut ground: Vec<i64> = vec![0i64; 600001];
        // let mut ground: HashMap<i64, i64> = HashMap::new();

        for i in 0..n {
            let pos = x[i as usize] + 300000;
            let health = a[i as usize];
            ground[pos as usize] += health;
        }
        let mut bullets: i64 = 0;
        for i in 1..=maxpos {
            let l = -i + 300000;
            let r = i + 300000;
            let mut health: i64 = 0;
            health += ground[l as usize];
            health += ground[r as usize];
            bullets += k as i64;
            if health > bullets {
                writeln!(w, "NO");
                continue 'test;
            }
            bullets -= health;
        }
        writeln!(w, "YES");
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
                let mut sign: i64 = 1;
                let mut parse_token = false;
                loop {
                    if let Ok(buf) = self.stdin.fill_buf() {
                        if !parse_token {
                            while self.pos < buf.len() && buf[self.pos] <= 32 {
                                self.pos += 1;
                            }
                            if self.pos < buf.len() && buf[self.pos] == b'-' {
                                sign = -1;
                                self.pos += 1;
                            }
                        }
                        while self.pos < buf.len() && buf[self.pos] > 32 {
                            parse_token = true;
                            ans = ans * 10 + (buf[self.pos] - b'0') as $t;
                            self.pos += 1;
                        }
                        if self.pos != buf.len() || self.pos == 0 {
                            return sign * ans;
                        }
                    }
                    self.stdin.consume(self.pos);
                    self.pos = 0;
                }
           }
        }
    )+}
}

// impl_token_stream!(usize);
impl_token_stream!(i64);
