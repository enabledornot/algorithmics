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
    let c = req_swap(ary, amnt);
    if c == 0 {
        return
    }
    else if c < amnt {
        return shift_n(&mut ary[c..],amnt-c);
    }
    else {
        return shift_n(&mut ary[c..],amnt);
    }

}



fn main() {
    let mut seq_arry = generate_seq_ary(14);
    shift_n(&mut seq_arry,12);
    println!("{:?}",seq_arry);
}
