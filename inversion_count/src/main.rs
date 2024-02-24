use rand::{Rng, thread_rng};

fn randArray(length: i32) -> Vec<i32> {
    let mut result: Vec<i32> = Vec::new();
    for _ in 0..length {
        result.push(thread_rng().gen());
    }
    return result;
}
fn main() {
    let rand_array = randArray(50);
    println!("{:?}",rand_array);
}