fn pow(x: usize, y: usize, m: usize) -> usize {
    let mut res = 1;
    let mut x = x;
    let mut y = y;
    while y > 0 {
        if y & 1 == 1 {
            res = res * x;
            res %= m;
        }
        x *= x;
        x %= m;
        y >>= 1;
    }
    res % m
}

fn inv(n: usize, m: usize) -> usize {
    pow(n, m - 2, m)
}
fn mul(x: usize, y: usize, m: usize) -> usize {
    (x % m) * (y % m) % m
}
fn div(x: usize, y: usize, m: usize) -> usize {
    mul(x, inv(y, m), m)
}

fn nCr(n: usize, r: usize, m: usize) -> usize {
    if r > n {
        return 0;
    }
    if r == 0 {
        return 1;
    }

    if n - r < r {
        return nCr(n, n - r, m);
    }

    let mut res: usize = 1;

    for i in (1..=r).rev() {
        res = div(mul(res, n - i + 1, m), i, m);
    }

    res
}

fn nCr_fact(n: usize, r: usize, m: usize, fact: &Vec<usize>, inv: &Vec<usize>) -> usize {
    if r > n {
        return 0;
    }
    fact[n] * inv[r] % m * inv[n - r] % m
}

fn main() {
    let n: usize = 200_001;

    let mut fact = vec![1; n];
    let mut invfact = vec![1; n];
    let m: usize = 1_000_000_007;

    for i in 1..n {
        fact[i] = mul(fact[i - 1], i, m);
        invfact[i] = inv(fact[i], m);
    }
}
