use input::input::get_input;
use std::collections::HashSet;

fn contains_duplicate(string: &str) -> bool {
    let set = string.chars().collect::<HashSet<_>>();
    string.len() != set.len()
}

fn solution(datastream: &str, window_size: usize) -> usize {
    for i in window_size - 1..datastream.len() {
        let window = &datastream[i - (window_size - 1)..=i];

        if !contains_duplicate(window) {
            return i + 1;
        }
    }

    0
}

fn main() {
    let input = get_input(6);

    println!("Part 1 output: {}", solution(&input, 4));
    println!("Part 1 output: {}", solution(&input, 14));
}
