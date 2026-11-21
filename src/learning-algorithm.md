class Layer {
  ...
}


class Network {
  vector<Layer> layers;
  
}

mynn = vector<Layer>;

Setup() {
  Initialize all the weights and biases to a random value.
} 




Choose a batch size, m.
Randomly choose the batch.
epoch = 0

while (Continue Training Condition == true) {
  randomly shuffle the training examples into batches
  for each batch {
    gradient so far = vector<int>(batch-size);
    for each training example in the current batch {
      forward_pass(mynn)
      backward_pass(mynn, gradient so far) // updates gradient so far
      
    }

    divide gradient so far by batch size
    for every parameter, update it by the corresponding entry in the gradient vector
  }

  epoch++
}
