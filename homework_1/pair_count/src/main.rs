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
fn rand_sorted(length: u32) -> Vec<u32> {
    let mut rand = rand_array(length);
    rand.sort_by(|a, b| b.cmp(a));
    return rand;
}

fn slow_pair_count(a: &Vec<u32>, b: &Vec<u32>, c: u32) -> u32 {
    let mut count = 0;
    for p in a.iter() {
        for q in b.iter() {
            if p + q > c  {
                count = count + 1;
            }
        }
    }
    return count;
}

fn fast_pair_count(a: &Vec<u32>, b: &Vec<u32>, c: u32) -> usize {
    let mut qi = 0;
    let mut count = 0;
    for p in a.iter().rev() {
        while qi < b.len() && b[qi] + p > c  {
            qi = qi + 1;
        }
        count = count + qi;
    }
    return count;
}

fn main() {
    let a = rand_sorted(5);
    let b = rand_sorted(7);
    let c = rand();
    // let a = vec![4,10,11,12,13,15];
    // let b = vec![10,8,5,3];
    // let c = 10;
    println!("a={:?},b={:?},c={}",a,b,c);
    let slow_count = slow_pair_count(&a,&b,c);
    let fast_count = fast_pair_count(&a,&b,c);
    println!("slow={:?},fast={:?}",slow_count,fast_count);
}
