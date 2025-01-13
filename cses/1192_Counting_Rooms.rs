#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::io::{self, prelude::*};

const MOD: usize = 1_000_000_007;

fn dfs(x: usize, y: usize, grid: &Vec<Vec<u8>>, visited: &mut Vec<Vec<bool>>) {
    if x < 0 || x >= grid.len() || y < 0 || y >= grid[0].len() {
        return;
    }

    if grid[x][y] == b'#' || visited[x][y] {
        return;
    }

    visited[x as usize][y as usize] = true;

    dfs(x + 1, y, grid, visited);
    dfs(x - 1, y, grid, visited);
    dfs(x, y + 1, grid, visited);
    dfs(x, y - 1, grid, visited);
}

fn solve<R: BufRead, W: Write>(input: &mut FastInput<R>, w: &mut W) {
    let n: i64 = input.next();
    let m: i64 = input.next();

    let grid = (0..n).map(|_| input.next()).collect::<Vec<Vec<u8>>>();

    let mut visited = vec![vec![false; m as usize]; n as usize];

    let mut res = 0;
    for i in 0..n {
        for j in 0..m {
            if grid[i as usize][j as usize] == b'.' && !visited[i as usize][j as usize] {
                dfs(i as usize, j as usize, &grid, &mut visited);
                res += 1;
            }
        }
    }

    writeln!(w, "{}", res);
}

fn main() {
    let stdin = io::stdin();
    let stdout = io::stdout();
    let mut input = FastInput::from(stdin.lock());
    let mut writer = io::BufWriter::new(stdout.lock());

    // let t: usize = input.next();
    let t: usize = 1;
    for _ in 0..t {
        solve(&mut input, &mut writer);
    }
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
istream!(i64);
