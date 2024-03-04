use rand::{Rng, thread_rng};
use core::cmp::Ordering;

#[derive(Debug)]
#[derive(PartialEq)]
#[derive(Copy)]
#[derive(Clone)]
struct Point {
    x: f32,
    y: f32
}

impl Point {
    fn new() -> Self {
        Point {x:rand(),y:rand()}
    }
    fn dist_to_sqr(&self, p: &Point) -> f32 {
        let dx = (self.x - p.x).abs();
        let dy = (self.y - p.y).abs();
        return dx*dx + dy*dy;
    }
}

fn brute_force(points: &[Point]) -> f32 {
    let mut min = f32::MAX;
    for x in points.iter() {
        for y in points.iter() {
            if x == y {
                continue;
            }
            let ndist = x.dist_to_sqr(y);
            if ndist < min {
                min = ndist;
            }
        }
    }
    return min;
}

fn min(a: f32, b: f32) -> f32 {
    if a < b {
        return a;
    }
    return b;
}

fn cmp(a: f32, b: f32) -> Ordering {
    return a.partial_cmp(&b).unwrap();
}

fn remove_in_range(points: &mut [Point], old_min: f32) -> f32 {
    let mut min = old_min;
    points.sort_by(|a, b| cmp(a.y,b.y));
    for i in 0..points.len() {
        let mut j = i + 1;
        while j < points.len() && (points[j].y - points[i].x) < min {
            let dist = points[i].dist_to_sqr(&points[j]);
            if dist < min {
                min = dist;
            }
            j = j + 1;
        }
    }
    return min;
}

fn minimum_distance_rec(points: &mut [Point]) -> f32 {
    if points.len() < 4 {
        return brute_force(points);
    }
    let mid = points.len()/2;
    let d0 = minimum_distance_rec(&mut points[0..mid]);
    let d1 = minimum_distance_rec(&mut points[mid..]);
    let d = min(d0,d1);
    let mut in_range: Vec<Point> = Vec::new();
    for point in points.iter() {
        if point.x - points[mid].x < d {
            in_range.push(*point);
        }
    }
    return min(d, remove_in_range(&mut in_range, d));
}

fn minimum_distance(points: &mut [Point]) -> f32 {
    points.sort_by(|a, b| cmp(a.x,b.x));
    return minimum_distance_rec(points);
}
fn create_n_points(n: u32) -> Vec<Point> {
    let mut points: Vec<Point> = Vec::new();
    for _ in 0..n {
        points.push(Point::new());
    }
    return points;
}

fn rand() -> f32 {
    let rnd: f32 = thread_rng().gen_range(-1000.0..1000.0);
    return rnd;
}

fn print_points(points: &Vec<Point>) {
    for point in points.iter() {
        println!("{:?}",point);
    }
}

fn main() {
    let mut points = create_n_points(10);
    print_points(&points);
    let min_dist = brute_force(&points);
    println!("{:?}",min_dist);
    let min_dist_fast = minimum_distance(&mut points);
    println!("{:?}",min_dist_fast);
}
