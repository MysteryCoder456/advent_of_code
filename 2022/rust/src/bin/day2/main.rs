use input::input::get_input;

mod part1 {
    /// lose = -1
    /// draw = 0
    /// win = +1
    fn calculate_game_outcome(elf: &str, me: &str) -> i32 {
        let win_states = [("A", "Y"), ("B", "Z"), ("C", "X")];

        for (e, m) in win_states {
            if e == elf && m == me {
                return 1;
            }
        }

        let lose_states = [("X", "B"), ("Y", "C"), ("Z", "A")];

        for (m, e) in lose_states {
            if e == elf && m == me {
                return -1;
            }
        }

        // Nothing matched, draw
        0
    }

    pub fn part1(input: &str) {
        let total_points = input
            .lines()
            .map(|line| {
                let (elf, me) = line.split_once(" ").unwrap();

                let move_points = match me {
                    "X" => 1,
                    "Y" => 2,
                    "Z" => 3,
                    _ => 0,
                };

                let game_outcome = calculate_game_outcome(elf, me);
                let outcome_points = (game_outcome + 1) * 3;

                outcome_points + move_points
            })
            .sum::<i32>();

        println!("Part 1 total points: {total_points}");
    }
}

mod part2 {
    fn calculate_round_points(elf: &str, outcome: &str) -> i32 {
        match outcome {
            "X" => match elf {
                "A" => 3,
                "B" => 1,
                "C" => 2,
                _ => 0,
            },
            "Y" => match elf {
                "A" => 1 + 3,
                "B" => 2 + 3,
                "C" => 3 + 3,
                _ => 0,
            },
            "Z" => match elf {
                "A" => 2 + 6,
                "B" => 3 + 6,
                "C" => 1 + 6,
                _ => 0,
            },
            _ => 0,
        }
    }

    pub fn part2(input: &str) {
        let total_points = input
            .lines()
            .map(|line| {
                let (elf, outcome) = line.split_once(" ").unwrap();
                calculate_round_points(elf, outcome)
            })
            .sum::<i32>();

        println!("Part 2 total points: {total_points}");
    }
}

fn main() {
    let input = get_input(2);

    part1::part1(&input);
    part2::part2(&input);
}
