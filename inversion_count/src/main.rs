use rand::{Rng, thread_rng};

fn randArray(length: i32) -> Vec<i32> {
    let mut result: Vec<i32> = Vec::new();
    for _ in 0..length {
        result.push(thread_rng().gen());
    }
    return result;
}
fn slowInvertCount(ary: &Vec<i32>) -> i32 {
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
fn merge(ary: &mut [i32], mid: usize) {
    let mut merged: Vec<i32> = Vec::new();
    let mut i = 0;
    let mut j = mid;
    while i < mid && j < ary.len() {
        let iel = ary[i];
        let jel = ary[j];
        if iel < jel {
            merged.push(iel);
            i = i + 1;
        }
        else {
            merged.push(jel);
            j = j + 1;
        }
    }
    while i < mid {
        merged.push(ary[i]);
        i = i + 1;
    }
    while j < ary.len() {
        merged.push(ary[j]);
        j = j + 1;
    }
    ary.clone_from_slice(&merged);
}
fn mergeSort(ary: &mut [i32]) {
    if ary.len() > 1 {
        let mid = ary.len()/2;
        mergeSort(&mut ary[0..mid]);
        mergeSort(&mut ary[mid..]);
        merge(ary, mid);
    }
}
fn main() {
    let mut rand_array = randArray(10);
    println!("{:?}",rand_array);
    let invCount = slowInvertCount(&rand_array);
    println!("{:?}", invCount);
    mergeSort(&mut rand_array);
    println!("{:?}",rand_array);
}