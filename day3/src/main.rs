use std::fs::File;
use std::io::{self, BufRead, ErrorKind, Error};
use std::path::Path;
use std::collections::{HashMap, HashSet};

fn main() {
    let vec = read_file("input.txt").unwrap();
    

    println!("{}", part1(&vec));
    println!("{}", part2(&vec));

}

fn read_file<P>(filename :P) -> Result<Vec<String>, Error> 
where P: AsRef<Path> {
    let file = File::open(filename)?;
    io::BufReader::new(file).lines().map(|line| line.and_then(|v| v.parse().map_err(|e| Error::new(ErrorKind::InvalidData, e))))
    .collect()
}

fn score(letter: char) -> u64 {
    let i = letter as u64;
    if i >= 97 {
        i - 96
    } else {
        i - 38
    }
}

fn part1(input: &Vec<String>) -> u64 {
    let mut ret: u64 = 0;
    for item in input {
        let my_vec: Vec<char> = item.chars().collect();
        let mut chars: HashMap<char, u64> = HashMap::new();
        for i in 0..(my_vec.len()/2) {
            let count = chars.entry(my_vec[i]).or_insert(0);
            *count +=1;
        }
        
        for i in my_vec.len()/2..my_vec.len() {
            if chars.contains_key(&my_vec[i]) {
                ret += score(my_vec[i]);
                break;
            }
        }
    }
    return ret;
}

fn part2(input: &Vec<String>) -> u64 {
    let mut ret: u64 = 0;

    for lines in input.chunks_exact(3) {
        let mut check1 : HashSet<char> = HashSet::new();
        let mut check2 : HashSet<char> = HashSet::new();
        let mut l = lines.iter();

        for c in l.next().unwrap().chars() {
            check1.insert(c);
        }

        for c in l.next().unwrap().chars() {
            if check1.contains(&c) {
                check2.insert(c);
            }
        }

        for c in l.next().unwrap().chars() {
            if check2.contains(&c) {
                println!("{}", c);
                ret += score(c);
                break;
            }
        }


    }
    return ret;
}

