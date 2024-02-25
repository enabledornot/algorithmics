use rand::{Rng, thread_rng};

fn rand() -> u32 {
    let rnd: i32 = thread_rng().gen_range(0..1000);
    return rnd as u32;
}
fn rand_array(length: u32) -> Vec<u32> {
    let mut result: Vec<u32> = Vec::new();
    for _ in 0..length {
        result.push(rand());
    }
    return result;
}
fn main() {
    println!("Hello, world!");
}
