use std::fmt;
use std::fmt::Formatter;

#[derive(Debug, Copy, Clone, PartialEq)]
pub struct Pixel {
    pub r: u8,
    pub g: u8,
    pub b: u8,
}

impl fmt::Display for Pixel {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "{} {} {}", self.r, self.g, self.b)
    }
}

pub struct Image {
    pub width: usize,
    pub height: usize,
    pub data: Vec<Pixel>,
}

impl Image {
    pub fn new(width: usize, height: usize) -> Image {
        let black_pixel  = Pixel { r: 0, g: 0, b: 0 };
        let data = vec![black_pixel; width * height];
        Image {
            width,
            height,
            data,
        }
    }

    pub fn get(&self, x: usize, y: usize) -> Option<&Pixel> {
        if x < self.width && y < self.height {
            let idx = y * self.width + x;
            Some(&self.data[idx])
        } else {
            None
        }
    }

    pub fn get_mut(&mut self, x: usize, y: usize) -> Option<&mut Pixel> {
        if x < self.width && y < self.height {
            let idx = y * self.width + x;
            Some(&mut self.data[idx])
        } else {
            None
        }
    }

    pub fn get_mandelbrot_pixels(&self) -> usize {
        self.data.iter().filter(|p| p.r == 0 && p.g == 0 && p.b == 0).count()
    }
}