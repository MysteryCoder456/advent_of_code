use input::input::get_input;

fn main() {
    let input = get_input(1);
    let mut top_elves = [0, 0, 0];

    input.split("\n\n").for_each(|elf| {
        let mut elf_calories = 0;

        elf.split("\n")
            .for_each(|calories_str| match calories_str.parse::<i32>() {
                Ok(calories) => elf_calories += calories,
                Err(_) => {}
            });

        if elf_calories > top_elves[0] {
            top_elves[2] = top_elves[1];
            top_elves[1] = top_elves[0];
            top_elves[0] = elf_calories;
        } else if elf_calories > top_elves[1] {
            top_elves[2] = top_elves[1];
            top_elves[1] = elf_calories;
        } else if elf_calories > top_elves[2] {
            top_elves[2] = elf_calories;
        }
    });

    println!("Calories by top elf: {}", top_elves[0]);
    println!(
        "Total calories of top 3 elves: {}",
        top_elves[0] + top_elves[1] + top_elves[2]
    );
}
