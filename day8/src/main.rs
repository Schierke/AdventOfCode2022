use std::fs::File;
use std::io::{self, BufRead, ErrorKind, Error};
use std::path::Path;
use std::cmp;

fn main() {
    let vec = read_file("input.txt").unwrap();
    
    let mut input: Vec<Vec<u32>> = Vec::new();
    for line in vec {
        const RADIX: u32 = 10;
        let current = line.chars().map(|c| c.to_digit(RADIX).unwrap()).collect();
        input.push(current);
    }

    let mut ret1: u32 = 0;
    let mut ret2: u32 = 0;
    for i in 0..input.len() {
        for j in 0..input[0].len() {
            if i == 0 || i == input.len() - 1 || j == 0 || j == input[0].len() - 1 {
                ret1+=1;
                continue;
            }
            
            if check_if_visible(input.clone(), i, j) {
                ret1+=1;
            }

            ret2 = cmp::max(ret2, calculate_score(input.clone(), i, j));
        }
    }

    println!("{}", ret1);
    println!("{}", ret2);
}

fn check_if_visible(input: Vec<Vec<u32>>, i :usize, j: usize) -> bool{
    let mut is_visible = true;
    for k in 0..i {
        if input[k][j] >= input[i][j] {
            is_visible = false;
        }
    }

    if is_visible {
        return is_visible;
    };

    is_visible = true;
    for k in (i+1)..input.len() {
        if input[k][j] >= input[i][j] {
            is_visible = false;
        }
    }

    if is_visible {
        return is_visible;
    };

    is_visible = true;
    for k in 0..j {
        if input[i][k] >= input[i][j] {
            is_visible = false;
        }
    }

    if is_visible {
        return is_visible;
    };

    is_visible = true;
    for k in j+1..input[0].len() {
        if input[i][k] >= input[i][j] {
            is_visible = false;
        }
    }

    is_visible

}

fn calculate_score(input: Vec<Vec<u32>>, i :usize, j: usize) -> u32{
    let (mut l, mut r, mut u, mut d) = (0 , 0, 0, 0);
    for k in (0..i).rev() {
        l+=1;
        if input[k][j] >= input[i][j] {
            break;
        }
    }

    for k in (i+1)..input.len() {
        r+=1;
        if input[k][j] >= input[i][j] {
            break;
        }
    }

    for k in (0..j).rev() {
        u+=1;
        if input[i][k] >= input[i][j] {
            break;
        }
    }

    for k in j+1..input[0].len() {
        d+=1;
        if input[i][k] >= input[i][j] {
            break;
        }
    }

    return l * r * u * d;
}

fn read_file<P>(filename :P) -> Result<Vec<String>, Error> 
where P: AsRef<Path> {
    let file = File::open(filename)?;
    io::BufReader::new(file).lines().map(|line| line.and_then(|v| v.parse().map_err(|e| Error::new(ErrorKind::InvalidData, e))))
    .collect()
}