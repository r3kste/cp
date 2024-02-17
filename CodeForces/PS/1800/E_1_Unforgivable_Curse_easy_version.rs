#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::{
    collections::{HashMap, HashSet, VecDeque},
    io::{self, prelude::*},
};
fn add(
    s: &mut String,
    i: usize,
    j: usize,
    n: usize,
    was: &mut HashSet<String>,
    q: &mut VecDeque<String>,
) {
    if i < n && j < n && i < j {
        let mut t = s.clone();
        t.replace_range(i..=i, &s[j..=j]);
        t.replace_range(j..=j, &s[i..=i]);
        if !was.contains(&t) {
            was.insert(t.clone());
            q.push_back(t);
        }
    }
}

fn solve<R: BufRead, W: Write>(mut input: FastInput<R>, mut w: W) {
    let t: usize = input.next();
    // let t: usize = 1;
    for _ in 0..t {
        let n: usize = input.next();
        let k: usize = input.next();
        let s: Vec<u8> = input.next();
        let s = std::string::String::from_utf8(s).unwrap();
        let t: Vec<u8> = input.next();
        let t = std::string::String::from_utf8(t).unwrap();

        if n <= 5 {
            let mut was: HashSet<String> = HashSet::new();
            let mut q: VecDeque<String> = VecDeque::new();
            q.push_back(s.clone());
            was.insert(s.clone());

            while let Some(s) = q.pop_front() {
                for i in 0..n {
                    add(&mut s.clone(), i, i + k, n, &mut was, &mut q);
                    add(&mut s.clone(), i, i + k + 1, n, &mut was, &mut q);
                    if i >= k {
                        add(&mut s.clone(), i - k, i, n, &mut was, &mut q);
                    }
                    if i >= k + 1 {
                        add(&mut s.clone(), i - k - 1, i, n, &mut was, &mut q);
                    }
                }
            }
            if was.contains(&t) {
                writeln!(w, "YES");
            } else {
                writeln!(w, "NO");
            }
        } else {
            let mut freq: HashMap<char, i32> = HashMap::new();
            for c in s.chars() {
                *freq.entry(c).or_insert(0) += 1;
            }
            for c in t.chars() {
                *freq.entry(c).or_insert(0) -= 1;
            }
            let mut ok = true;
            for (_, &v) in freq.iter() {
                if v != 0 {
                    ok = false;
                    break;
                }
            }
            if ok {
                writeln!(w, "YES");
            } else {
                writeln!(w, "NO");
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

impl_token_stream!(usize);
impl_token_stream!(i32);
