#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "mnist.hpp"

using Args = std::vector<std::string>;

/*
this function finds the number that comes after whatever flag "--name" that I pass into it.
For example: for "--test 67", the number this function returns is "67".
It loops through the args, and stops at the first match - returning a fallback if it can't
find a match.
*/
double option(const Args& args, const std::string& name, double fallback) {
    for (std::size_t i = 0; i + 1 < args.size(); i++) {
        if (args[i] != "--" + name) continue;

        double value = 0.0;
        try {
            value = std::stod(args[i + 1]);

        } catch (const std::exception&) {
            throw std::runtime_error("--" + name + " expects a number, got \"" + args[i + 1] + "\"");
        }

        if (value < 0) throw std::runtime_error("--" + name + " must not be negative!");

        return value;
    }

    return fallback;
}

// makes the code process the "--index" flag and the value passed to it.
std::size_t process_index_flag(const Args& args, std::size_t size) {
    const double index = option(args, "index", 0);

    if (index >= static_cast<double>(size))
        throw std::runtime_error("--index must be between 0 and " + std::to_string(size - 1));

    return static_cast<std::size_t>(index);
}

const std::string DataDir = "data"; // where the four MNIST files live relative to root

// Processes the "show" command, after which it then expects an "--index [N]" to be passed
// afterwards.
int cmd_show(const Args& args) {
    const Dataset train = load_mnist(DataDir, "train");
    const std::size_t index = process_index_flag(args, train.size());

    std::cout << "Loaded " << train.size() << " training images of "
              << train.rows << "x" << train.cols << " pixels.\n";

    std::cout << "Image #" << index << " is labelled " << train.labels[index] << ":\n";

    print_digit(train.images[index], train.rows, train.cols);
    return 0;
}

int main(int argc, char* argv[]) {
    const Args args(argv + 1, argv + argc); // fills the args vector.
    try {

        if (!args.empty() && args[0] == "show") {
            return cmd_show(args);
        }
        std::cerr << "usage: ./mnist show [--index N]\n";
        return 1;

    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
