mod client; // includes a module
mod image;
mod complex;
mod mandelbrot;

fn main() {
    // uncomment and implement argument parsing, printing an error message in case of a parsing error
    // call client::parse_args() to get width, height and max_iterations from the input arguments

    let (width, height, max_iterations) = match client::parse_args() {
        Ok((w, h, iterations)) => (w, h, iterations),
        Err(e) => {
            eprintln!("Failed to parse arguments: {}", e);
            std::process::exit(1);
        }
    };

    // if the above was implemented correctly you can uncomment this line
    println!("Generating Mandelbrot for {}x{} image (max_iterations: {})", width, height, max_iterations);

    // call mandelbrot::generate_image(width, height, max_iterations) and save the result to an image
    let image = mandelbrot::generate_image(width, height, max_iterations);
    // call the get_mandelbrot_pixels() method on the image struct and save the result in mandelbrot_pixel_count
    let mandelbrot_pixel_count = image.get_mandelbrot_pixels();
    // if the above line worked you should be able to uncomment this line
    println!("Pixels in the set: {}", mandelbrot_pixel_count);

    // uncomment and call after you implement the mandelbrot functions, and handle the possible error
    client::save_to_file(&image, "mandelbrot.ppm");

}


