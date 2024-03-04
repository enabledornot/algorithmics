use rand::{Rng, thread_rng};

fn rand_array(length: i32) -> Vec<i32> {
    let mut result: Vec<i32> = Vec::new();
    for _ in 0..length {
        result.push(thread_rng().gen());
    }
    return result;
}
fn slow_invert_count(ary: &Vec<i32>) -> i32 {
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
fn merge(ary: &mut [i32], mid: usize) -> usize {
    let mut merged: Vec<i32> = Vec::new();
    let mut i = 0;
    let mut j = mid;
    let mut inv_count = 0;
    while i < mid && j < ary.len() {
        let iel = ary[i];
        let jel = ary[j];
        if iel < jel {
            merged.push(iel);
            i = i + 1;
        }
        else {
            merged.push(jel);
            inv_count = inv_count + mid - i;
            j = j + 1;
        }
    }
    while i < mid {
        merged.push(ary[i]);
        i = i + 1;
    }
    while j < ary.len() {
        merged.push(ary[j]);
        inv_count = inv_count + mid - i;
        j = j + 1;
    }
    ary.clone_from_slice(&merged);
    return inv_count;
}
fn merge_sort(ary: &mut [i32]) -> usize {
    let mut inv_count = 0;
    if ary.len() > 1 {
        let mid = ary.len()/2;
        inv_count+=merge_sort(&mut ary[0..mid]);
        inv_count+=merge_sort(&mut ary[mid..]);
        inv_count+=merge(ary, mid);
    }
    return inv_count;
}
fn main() {
    let mut rand_array = rand_array(10);
    println!("{:?}",rand_array);
    let inv_count = slow_invert_count(&rand_array);
    println!("{:?}", inv_count);
    let inv_count_fast = merge_sort(&mut rand_array);
    println!("{:?} - {:?}",rand_array,inv_count_fast);
}