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
        let mut a: Vec<i32> = vec![0i32; n];
        for x in a.iter_mut() {
            *x = input.next();
        }
        let mut matches: HashMap<(i32, i32), (Vec<i32>, Vec<i32>)> = HashMap::new();
        for i in 0..n - 1 {
            let n1 = a[i];
            let n2 = a[i + 1];

            let entry = matches.entry((n1, n2)).or_insert((vec![], vec![]));
            if i < n - 2 {
                entry.1.push(a[i + 2]);
            }
            if i > 0 {
                entry.0.push(a[i - 1]);
            }
        }
        let mut middle: HashMap<(i32, i32), Vec<i32>> = HashMap::new();
        for i in 1..n - 1 {
            let n1 = a[i - 1];
            let n2 = a[i + 1];
            let entry = middle.entry((n1, n2)).or_insert(vec![]);
            entry.push(a[i]);
        }
        let mut res: usize = 0;
        for (k, m) in matches.iter() {
            if m.0.len() > 1 {
                let mut freq_1: HashMap<i32, usize> = HashMap::new();
                for x in m.0.iter() {
                    let count = freq_1.entry(*x).or_insert(0);
                    *count += 1;
                }
                let mut left_matches = m.0.len();
                left_matches = (left_matches * (left_matches - 1)) / 2;

                for (k, &v) in freq_1.iter() {
                    if v > 1 {
                        left_matches -= (v * (v - 1)) / 2;
                    }
                }
                res += left_matches;
            }
            if m.1.len() > 1 {
                let mut freq_2: HashMap<i32, usize> = HashMap::new();
                for x in m.1.iter() {
                    let count = freq_2.entry(*x).or_insert(0);
                    *count += 1;
                }
                let mut right_matches = m.1.len();
                right_matches = (right_matches * (right_matches - 1)) / 2;

                for (k, &v) in freq_2.iter() {
                    if v > 1 {
                        right_matches -= (v * (v - 1)) / 2;
                    }
                }
                res += right_matches;
            }
        }
        for (k, m) in middle.iter() {
            if m.len() > 1 {
                let mut freq: HashMap<i32, usize> = HashMap::new();
                for x in m.iter() {
                    let count = freq.entry(*x).or_insert(0);
                    *count += 1;
                }
                let mut matches = m.len();
                matches = (matches * (matches - 1)) / 2;

                for (k, &v) in freq.iter() {
                    if v > 1 {
                        matches -= (v * (v - 1)) / 2;
                    }
                }
                res += matches;
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
