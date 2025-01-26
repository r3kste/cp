#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::io::{self, prelude::*};

fn solve<R: BufRead, W: Write>(mut input: FastInput<R>, mut w: W) {
    let t: usize = input.next();
    // let t: usize = 1;
    for _ in 0..t {
        let n: usize = input.next();
        let m: usize = input.next();
        let tot = n + m + 1;
        let mut p: Vec<i32> = vec![0i32; tot];
        for x in p.iter_mut() {
            *x = input.next();
        }
        let mut t: Vec<i32> = vec![0; tot];
        for x in t.iter_mut() {
            *x = input.next();
        }

        let mut suitable: Vec<char> = Vec::new();
        let (mut p_count, mut t_count) = (0, 0);
        let (mut p_sum, mut t_sum) = (Vec::new(), Vec::new());
        p_sum.push(0);
        t_sum.push(0);
        for i in 0..tot {
            if p[i] > t[i] {
                suitable.push('p');
                p_count += 1;
            } else {
                suitable.push('t');
                t_count += 1;
            }
        }
        let mut ptr = 0;
        for i in 0..tot {
            if suitable[i] == 'p' {
                p_sum.push(p_sum[ptr] + p[i]);
                ptr += 1;
            }
        }
        ptr = 0;
        for i in 0..tot {
            if suitable[i] == 't' {
                // t_sum.push(t_sum[i] + t[i]);
                t_sum.push(t_sum[ptr] + t[i]);
                ptr += 1;
            }
        }

        let have = (p_count, t_count);
        let req = (n, m);
        for drop in 0..tot {
            let mut res = 0;
            let mut new_have = have.clone();
            let (p_drop, t_drop) = (p[drop], t[drop]);
            let (mut is_p, mut is_t) = (false, false);
            if suitable[drop] == 'p' {
                new_have.0 -= 1;
                is_p = true;
            } else {
                new_have.1 -= 1;
                is_t = true;
            }

            let (req_p, req_t) = req;
            let (have_p, have_t) = new_have;

            if req_p == have_p && req_t == have_t {
                res = p_sum[req_p] + t_sum[req_t];
            } else if req_p <= have_p && req_t >= have_t {
                res += p_sum[req_p + if is_p { 1 } else { 0 }];
                res -= if is_p { p_drop } else { 0 };
                let excess_p = have_p - req_p;
                res += t_sum[t_sum.len() - 1];
                res -= t_sum[req_p + if is_t { 1 } else { 0 }];
            } else {
                res += t_sum[req_t + if is_t { 1 } else { 0 }];
                res -= if is_t { t_drop } else { 0 };
                res += p_sum[p_sum.len() - 1];
                res -= p_sum[req_t + if is_p { 1 } else { 0 }];
            }
            write!(w, "{} ", res);
        }
        writeln!(w);
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
