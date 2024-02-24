use rand::{Rng, thread_rng};

fn randArray(length: i32) -> Vec<i32> {
    let mut result: Vec<i32> = Vec::new();
    for _ in 0..length {
        result.push(thread_rng().gen());
    }
    return result;
}
fn slowInvertCount(ary: Vec<i32>) -> i32 {
    let mut icount: i32 = 0;
    for i in 0..ary.len() {
        for j in (i+1)..ary.len() {
            if ary.get(i) > ary.get(j) {
                icount+=1;
            }
        }
    }
    return icount;
}
fn main() {
    let rand_array = randArray(10);
    println!("{:?}",rand_array);
    let invCount = slowInvertCount(rand_array);
    println!("{:?}", invCount);
}