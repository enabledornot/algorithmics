fn generate_seq_ary(length: i32) -> Vec<i32> {
    let mut rslt: Vec<i32> = Vec::new();
    for i in 0..length {
        rslt.push(i);
    }
    return rslt;
}

fn main() {
    let seq_arry = generate_seq_ary(10);
    print!("{:?}",seq_arry);
}
