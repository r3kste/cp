#![allow(unused_variables)]
#![allow(unused_must_use)]
#![allow(non_snake_case)]
use std::{
    collections::{HashMap, VecDeque},
    io::{self, prelude::*},
};

const MOD: usize = 1_000_000_007;

fn find_char(grid: &Vec<Vec<u8>>, c: u8) -> (usize, usize) {
    for i in 0..grid.len() {
        for j in 0..grid[0].len() {
            if grid[i][j] == c {
                return (i, j);
            }
        }
    }

    (0, 0)
}

fn solve<R: BufRead, W: Write>(input: &mut FastInput<R>, w: &mut W) {
    let n: i64 = input.next();
    let m: i64 = input.next();

    let grid = (0..n).map(|_| input.next()).collect::<Vec<Vec<u8>>>();
    let start = find_char(&grid, b'A');
    let end = find_char(&grid, b'B');

    let mut visited = vec![vec![false; m as usize]; n as usize];
    let mut parents = vec![vec![' '; m as usize]; n as usize];

    let mut queue = VecDeque::new();
    queue.push_back((start, ' '));

    while !queue.is_empty() {
        let (pos, parent) = queue.pop_front().unwrap();
        if grid[pos.0][pos.1] == b'B' {
            visited[pos.0][pos.1] = true;
            parents[pos.0][pos.1] = parent;
            break;
        }

        if grid[pos.0][pos.1] == b'#' || visited[pos.0][pos.1] {
            continue;
        }

        visited[pos.0][pos.1] = true;
        parents[pos.0][pos.1] = parent;

        if pos.0 < grid.len() - 1 {
            queue.push_back(((pos.0 + 1, pos.1), 'D'));
        }
        if pos.0 > 0 {
            queue.push_back(((pos.0 - 1, pos.1), 'U'));
        }
        if pos.1 < grid[0].len() - 1 {
            queue.push_back(((pos.0, pos.1 + 1), 'R'));
        }
        if pos.1 > 0 {
            queue.push_back(((pos.0, pos.1 - 1), 'L'));
        }
    }

    if visited[end.0][end.1] {
        writeln!(w, "YES");
    } else {
        writeln!(w, "NO");
        return;
    }

    let direction: HashMap<char, (i64, i64)> =
        [('U', (1, 0)), ('D', (-1, 0)), ('L', (0, 1)), ('R', (0, -1))]
            .iter()
            .cloned()
            .collect();
    let mut path = Vec::new();
    let mut pos = end;
    while parents[pos.0][pos.1] != ' ' {
        let parent = parents[pos.0][pos.1];
        path.push(parent);
        let d = direction.get(&parent).unwrap();
        pos.0 = (pos.0 as i64 + d.0) as usize;
        pos.1 = (pos.1 as i64 + d.1) as usize;
    }

    writeln!(w, "{}", path.len());
    for c in path.iter().rev() {
        write!(w, "{}", c);
    }
    writeln!(w);
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
