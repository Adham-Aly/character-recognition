#include <cstdio>
#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>
#include "mnist.hpp"
#include "cli_helpers.hpp"

using namespace std;

typedef vector<size_t> vec;
typedef vector<vec> matrix;

int main(int argc, char* argv[]) {
    const Args args(argv + 1, argv + argc); // fills the args vector.

    if (!args.empty() && args[0] == "show") {
        return cmd_show(args);
    }
    cerr << "usage: ./mnist show [--index N]\n";

    return 0;
}
