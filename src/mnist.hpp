#pragma once

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct Dataset {
    std::vector<std::vector<double>> images;
    std::vector<int> labels;
    int rows = 0;
    int cols = 0;

    std::size_t size() const {
        return labels.size();
    }
};
// reads four bytes at a time - reads four bytes from a big-endian binary file
/*
Note: endianness only matters for values that are more than one byte. This is why
this function is only used for the header values, but not for the image data - because
each pixel in the image is a single byte only.
*/
inline std::uint32_t read_u32_be(std::ifstream& in) {
    unsigned char b[4];
    in.read(reinterpret_cast<char*>(b), 4);

    if (!in) throw std::runtime_error("unexpected end of file while reading the header");

    return (std::uint32_t(b[0]) << 24) | (std::uint32_t(b[1]) << 16) |
                        (std::uint32_t(b[2]) << 8) | std::uint32_t(b[3]);
}

inline std::vector<std::vector<double>> load_images(const std::string& path, int& rows, int& cols) {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        throw std::runtime_error("cannot open " + path);
    }

    if (read_u32_be(in) != 2051) {
        throw std::runtime_error(path + " is not an idx image file.");
    }

    const std::uint32_t count = read_u32_be(in);
    rows = static_cast<int>(read_u32_be(in));
    cols = static_cast<int>(read_u32_be(in));

    const std::size_t pixels = static_cast<std::size_t>(rows) * static_cast<std::size_t>(cols);
    std::vector<std::vector<double>> images(count, std::vector<double>(pixels));
    std::vector<unsigned char> buffer(pixels);

    for (std::uint32_t i = 0; i < count; i++) {
        in.read(reinterpret_cast<char*>(buffer.data()), static_cast<std::streamsize>(pixels));

        if (!in) {
            throw std::runtime_error(path + " file ended early");
        }

        for (std::size_t p = 0; p < pixels; p++) {
            images[i][p] = buffer[p] / 255.0;
        }
    }

    return images;
}

inline std::vector<int> load_labels(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        throw std::runtime_error("cannot open " + path);
    }

    if (read_u32_be(in) != 2049) {
        throw std::runtime_error(path + " is not an idx label file");
    }

    const std::uint32_t count = read_u32_be(in);

    std::vector<unsigned char> buffer(count);
    in.read(reinterpret_cast<char*>(buffer.data()), static_cast<std::streamsize>(count));
    if (!in) {
        throw std::runtime_error(path + " file ended early");
    }

    return std::vector<int>(buffer.begin(), buffer.end());
}

inline Dataset load_mnist(const std::string& dir, const std::string&prefix) {
    Dataset d;

    d.images = load_images(dir + "/" + prefix + "-images-idx3-ubyte", d.rows, d.cols);
    d.labels = load_labels(dir + "/" + prefix + "-labels-idx1-ubyte");

    if (d.images.size() != d.labels.size()) {
        throw std::runtime_error("image and label counts differ for " + prefix);
    }
    return d;
}

inline void print_digit(const std::vector<double>& image, int rows, int cols) {
    const std::string ramp = " .:-=+*#%@"; // 10 shades, from 0.0 up to 1.0
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            const double v = image[static_cast<std::size_t>(r * cols + c)];
            const char ch = ramp[static_cast<std::size_t>(v * 9.0 + 0.5)];
            std::cout << ch << ch;
        }
        std::cout << '\n';
    }
}
