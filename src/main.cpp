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

struct Network {
    int numLayers;
    vector<int> sizes; // number of neurons in each layer
    vector<matrix> weights_matrices; // the weights of each neuron in each layer.

    vector<vec> b; // biases of each neuron, for each layer
};

struct SavedValues {
    vector<vec> z; // the preactivations (aka "weighted sums") of the neurons in each layer.
    vector<vec> a; // the activations of the neurons in each layer.
};

struct Gradient {
    vector<matrix> dW; // dc/dw for each weight for each neuron in each layer
    vector<vec> db; // dc/db for each bias for each neuron in each layer
};

double sigmoid(double z) {
    return 1.0 / (1.0 + exp(-z));
}

double sigmoidPrime(double z) {
    double s = sigmoid(z);
    return s * (1.0 - s);
}

void forwardPass(vec& inputLayer, Network& net, SavedValues& saved) {
    int layerCount = net.numLayers;

    saved.z = vector<vec>(layerCount);
    saved.a = vector<vec>(layerCount);
    saved.a[0] = inputLayer;

    // we're starting from l = 1, because the input layer activations are already computed
    for (int l = 1; l < layerCount; l++) {
        /*
         * Goal: for each layer (each iteration of this loop) we want to compute all of
         * the activations and preactivations of the neurons of this layer, and then
         * save them to the savedValues for future use.
         *
         */
    }
}

int main(int argc, char* argv[]) {
    const Args args(argv + 1, argv + argc); // fills the args vector.

    if (!args.empty() && args[0] == "show") {
        return cmd_show(args);
    }
    cerr << "usage: ./mnist show [--index N]\n";

    return 0;
}
