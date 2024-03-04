use rand::{Rng, thread_rng};

#[derive(Debug)]
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

fn brute_force(points: &Vec<Point>) -> f32 {
    let mut min = f32::MAX;
    for x in points.iter() {
        for y in points.iter() {
            let ndist = x.dist_to_sqr(y);
            if ndist < min {
                min = ndist;
            }
        }
    }
    return min;
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
    let points = create_n_points(10);
    print_points(&points);
}
