pub mod input {
    use std::{fs::File, io::Read};

    pub fn get_input(day: u32) -> String {
        let file_path = format!("src/bin/day{}/input.txt", day);

        let mut buf = String::new();
        File::open(file_path)
            .unwrap()
            .read_to_string(&mut buf)
            .unwrap();

        buf
    }
}
