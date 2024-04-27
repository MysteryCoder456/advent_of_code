use std::ops::RangeInclusive;

use input::input::get_input;

fn string_to_range(string: &str) -> RangeInclusive<i32> {
    string
        .split_once("-")
        .map(|(s1, s2)| s1.parse::<i32>().unwrap()..=s2.parse::<i32>().unwrap())
        .unwrap()
}

fn part1(input: &str) -> i32 {
    input
        .lines()
        .filter(|line| {
            let (range1_str, range2_str) = line.split_once(",").unwrap();

            let range1: RangeInclusive<i32> = string_to_range(range1_str);
            let range2: RangeInclusive<i32> = string_to_range(range2_str);

            range1.contains(range2.start()) && range1.contains(range2.end())
                || range2.contains(range1.start()) && range2.contains(range1.end())
        })
        .count() as i32
}

fn part2(input: &str) -> i32 {
    input
        .lines()
        .filter(|line| {
            let (range1_str, range2_str) = line.split_once(",").unwrap();

            let range1: RangeInclusive<i32> = string_to_range(range1_str);
            let range2: RangeInclusive<i32> = string_to_range(range2_str);

            range1.contains(range2.start())
                || range1.contains(range2.end())
                || range2.contains(range1.start())
                || range2.contains(range1.end())
        })
        .count() as i32
}

fn main() {
    let input = get_input(4);

    println!("Part 1 Output: {}", part1(&input));
    println!("Part 2 Output: {}", part2(&input));
}
