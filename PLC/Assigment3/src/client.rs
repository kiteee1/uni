use std::env;
use std::num::ParseIntError;
use std::process;

pub fn parse_args() -> Result<(usize, usize, usize), ParseIntError> {
    let args: Vec<String> = env::args().collect();

    if args.len() < 3 {
        eprintln!("Usage: {} <width> <height> [<max_iterations>]", args[0]);
        process::exit(1);
    }

    let width = args[1].parse()?;

    let height = args[2].parse()?;

    let max_iterations = if args.len() > 3 {
        args[3].parse::<usize>().unwrap_or_else(|_| 1024)
    } else {
        1024
    };

    Ok((width, height, max_iterations))
}