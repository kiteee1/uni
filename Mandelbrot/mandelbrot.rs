use crate::image::{Image, Pixel};
use crate::complex::Complex;

pub fn generate_image(width: usize, height: usize, max_iterations: usize) -> Image {
    let mut image = Image::new(width, height);

    for y in 0..height {
        for x in 0..width {
            let cx = (x as f64 / width as f64- 0.75)*3.5;
            let cy = (y as f64 / height as f64- 0.5)*2.0;
            let c = Complex {re: cx, im: cy};

            let result = check_pixel(c, max_iterations);
            let pixel_color = match result {
                Some(_) => Pixel {r: 255, g: 255, b: 255},
                None => Pixel { r: 0, g: 0, b: 0},
            };

            if let Some(pixel) = image.get_mut(x, y) {
                *pixel = pixel_color;
            }
        }
    }

    image
}

pub fn check_pixel(c: Complex, max_iterations: usize) -> Option<usize> {
    let mut z = Complex {re: 0.0, im: 0.0};

    for iteration in 0..max_iterations {
        z = z*z + c;

        if z.mag()>4.0 {
            return Some(iteration);
        }
    }

    None
}