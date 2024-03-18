fn generate_seq_ary(length: i32) -> Vec<i32> {
    let mut rslt: Vec<i32> = Vec::new();
    for i in 0..length {
        rslt.push(i);
    }
    return rslt;
}


// divide and conquer
fn req_swap(ary: &mut [i32], k: usize) -> usize{
    let mut i = 0;
    let mut j = k;
    while i<k && j < ary.len() {
        ary.swap(i,j);
        i = i + 1;
        j = j + 1;
    }
    return i;
}
fn shift_n_divide(ary: &mut [i32], amnt: usize) {
    // let len = ary.len();
    shift_n_divide_rec(ary, amnt);
}
fn shift_n_divide_rec(ary: &mut [i32], amnt: usize) {
    let c = req_swap(ary, amnt);
    if c == 0 {
        return
    }
    else if c < amnt {
        return shift_n_divide_rec(&mut ary[c..],amnt-c);
    }
    else {
        return shift_n_divide_rec(&mut ary[c..],amnt);
    }

}

// shuffle
fn gcd(m: usize, n: usize) -> usize {
    if n == 0 {
        return m;
    }
    return gcd(n, m % n);
}

fn shift_n_shuffle(ary: &mut [i32], amntt: usize) {
    let len = ary.len();
    let amnt = len-amntt;
    for i in 0..gcd(len,amnt) {
        let mut cnt = (i+amnt)%len;
        let mut last = ary[i];
        while cnt != i {
            let lastalt = ary[cnt];
            ary[cnt] = last;
            last = lastalt;
            cnt = (cnt+amnt)%len;
        }
        ary[i] = last;
    }
}

fn main() {
    println!("By divide and conquer");
    let mut seq_arry = generate_seq_ary(14);
    shift_n_divide(&mut seq_arry,6);
    println!("{:?}",seq_arry);

    println!("By shuffle method");
    seq_arry = generate_seq_ary(14);
    shift_n_shuffle(&mut seq_arry,6);
    println!("{:?}",seq_arry);
}
