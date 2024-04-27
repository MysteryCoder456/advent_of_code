use input::input::get_input;
use itertools::Itertools;
use std::{cell::RefCell, collections::HashMap};

#[derive(PartialEq)]
enum Type {
    File,
    Directory(HashMap<String, RefCell<Type>>),
}

fn part1(terminal: &str) -> i32 {
    let mut root = Type::Directory(HashMap::new());
    let mut pwd = RefCell::new(root);

    for line in terminal.lines() {
        let split = line.split(" ").collect_vec();

        match split[0] {
            "$" => match split[1] {
                "cd" => {
                    if split[2] == "/" {
                        pwd.replace(root);
                        continue;
                    }

                    if let Type::Directory(files) = pwd.into_inner() {
                        for name in files.keys() {
                            if name == split[2] {
                                let new_dir = files.get(name).unwrap();
                                pwd = *new_dir;
                                break;
                            }
                        }
                    }
                }
                _ => {}
            },
            "dir" => {
                if let Type::Directory(files) = pwd.get_mut() {
                    files.insert(
                        split[1].to_owned(),
                        RefCell::new(Type::Directory(HashMap::new())),
                    );
                }
            }
            _ => todo!(),
        }
    }

    todo!()
}

fn main() {
    let input = get_input(7);

    println!("Part 1 output: {}", part1(&input));
}
