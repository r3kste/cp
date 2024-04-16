#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::{
    collections::HashMap,
    io::{self, prelude::*},
};

const MOD: usize = 1_000_000_007;
fn solve<R: BufRead, W: Write>(mut input: FastInput<R>, mut w: W) {
    let t: usize = input.next();
    // let t: usize = 1;
    'test: for _ in 0..t {
        let n: usize = input.next();
        let m: usize = input.next();
        let mut a: Vec<i32> = vec![0i32; n];
        for x in a.iter_mut() {
            *x = input.next();
        }
        let mut b: Vec<i32> = vec![0i32; n];
        for x in b.iter_mut() {
            *x = input.next();
        }
        let mut q: Vec<i32> = vec![0i32; m];
        let mut swappable: HashMap<usize, bool> = HashMap::new();
        for x in q.iter_mut() {
            *x = input.next();
            swappable.insert(*x as usize, true);
        }
        let mut neg_suff_suma: Vec<isize> = vec![0; n + 1];
        let mut neg_suff_sumb: Vec<isize> = vec![0; n + 1];

        for i in (0..n).rev() {
            neg_suff_suma[i] = neg_suff_suma[i + 1] - a[i] as isize;
            neg_suff_sumb[i] = neg_suff_sumb[i + 1] - b[i] as isize;
        }

        let mut ms: isize = 0;
        let mut ls: isize = 0;
        for pos in 0..n {
            let mario_needs = (ms < neg_suff_suma[pos]) as bool;
            let luigi_needs = (ls < neg_suff_sumb[pos]) as bool;
            let both_needs = mario_needs && luigi_needs;

            if both_needs {
                writeln!(w, "NO");
                continue 'test;
            }
            if swappable.get(&(pos + 1)).is_some() {
                if luigi_needs {
                    ls += ms - neg_suff_suma[pos];
                    ms -= neg_suff_suma[pos];
                }
                if mario_needs {
                    ms += ls - neg_suff_sumb[pos];
                    ls -= neg_suff_sumb[pos];
                }
            } else {
                if luigi_needs || mario_needs {
                    writeln!(w, "NO");
                    continue 'test;
                }
            }
        }

        if ls >= 0 && ms >= 0 {
            writeln!(w, "YES");
        } else {
            writeln!(w, "NO");
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
