use std::collections::HashMap;

use input::input::get_input;
use itertools::Itertools;

type Stacks = HashMap<usize, Vec<char>>;

fn generate_stacks(stacks_str: &str) -> Stacks {
    let mut stacks: HashMap<usize, Vec<char>> = HashMap::new();

    stacks_str.lines().rev().enumerate().for_each(|(i, line)| {
        if i != 0 {
            for (j, ch) in line.chars().enumerate() {
                if !ch.is_alphabetic() {
                    continue;
                }

                let n = (j - 1) / 4 + 1;

                if let Some(s) = stacks.get_mut(&n) {
                    s.push(ch);
                } else {
                    stacks.insert(n, vec![ch]);
                }
            }
        }
    });

    stacks
}

fn part1(initial_stack: &Stacks, procedure: &str) -> String {
    let mut stacks = initial_stack.clone();

    for instruction in procedure.lines() {
        let s = instruction.split(" ").collect::<Vec<_>>();

        let move_count = s.get(1).unwrap().parse::<usize>().unwrap();
        let from = s.get(3).unwrap().parse::<usize>().unwrap();
        let to = s.get(5).unwrap().parse::<usize>().unwrap();

        for _ in 0..move_count {
            let from_stack = stacks.get_mut(&from).unwrap();
            let cra = from_stack.pop().unwrap();

            let to_stack = stacks.get_mut(&to).unwrap();
            to_stack.push(cra);
        }
    }

    stacks
        .iter()
        .sorted_by_key(|(i, _)| **i)
        .map(|(_, sta)| sta.last().unwrap().to_owned())
        .collect::<String>()
}

fn part2(initial_stack: &Stacks, procedure: &str) -> String {
    let mut stacks = initial_stack.clone();

    for instruction in procedure.lines() {
        let s = instruction.split(" ").collect::<Vec<_>>();

        let move_count = s.get(1).unwrap().parse::<usize>().unwrap();
        let from = s.get(3).unwrap().parse::<usize>().unwrap();
        let to = s.get(5).unwrap().parse::<usize>().unwrap();

        let from_stack = stacks.get_mut(&from).unwrap();
        let crates_to_move: Vec<char> = from_stack
            .drain((from_stack.len() - move_count)..)
            .collect_vec();

        let to_stack = stacks.get_mut(&to).unwrap();
        to_stack.extend(crates_to_move);
    }

    stacks
        .iter()
        .sorted_by_key(|(i, _)| **i)
        .map(|(_, sta)| sta.last().unwrap().to_owned())
        .collect::<String>()
}

fn main() {
    let input = get_input(5);
    let (stacks_str, procedure) = input.split_once("\n\n").unwrap();
    let stacks = generate_stacks(stacks_str);

    println!("Part 1 Output: {}", part1(&stacks, procedure));
    println!("Part 2 Output: {}", part2(&stacks, procedure));
}
