import numpy as np

def sigmoid(x):
  return 1.0 / (1.0 + np.exp(-x))

def d_sigmoid(x):
  return x * (1.0 - x)

class NN:
  def __init__(self, input_sz, out_fc0_sz, out_fc1_sz):
    # Weights and biases
    self.w0 = np.random.rand(input_sz, out_fc0_sz)
    self.b0 = np.random.rand(1, out_fc0_sz)

    self.w1 = np.random.rand(out_fc0_sz, out_fc1_sz)
    self.b1 = np.random.rand(1, out_fc1_sz)

  def forward(self, x):
    input = np.expand_dims(x, axis=0)

    # Fully connected 0
    self.out_fc0 = np.dot(input, self.w0) + self.b0
    self.out_fc0 = sigmoid(self.out_fc0)

    # Fully connected 1
    self.out_fc1 = np.dot(self.out_fc0, self.w1) + self.b1
    self.out_fc1 = sigmoid(self.out_fc1)

    return self.out_fc1

  def backward(self, x, y):
    input = np.expand_dims(x, axis=0)
    actual_out = y

    # Error/delta
    e_out_fc1 = actual_out - self.out_fc1
    d_out_fc1 = e_out_fc1 * d_sigmoid(self.out_fc1)

    e_out_fc0 = np.dot(d_out_fc1, self.w1.T)
    d_out_fc0 = e_out_fc0 * d_sigmoid(self.out_fc0)

    # Learning rate
    lr = 0.1

    # Calculate the weights adjustments
    w0_1 = np.dot(input.T, d_out_fc0)
    w1_1 = np.dot(self.out_fc0.T, d_out_fc1)
    w0_1 *= lr
    w1_1 *= lr
    # Calculate the biases adjustments
    b0_1 = d_out_fc0 * lr
    b1_1 = d_out_fc1 * lr

    # Update weights and biases
    self.w0 += w0_1
    self.b0 += b0_1
    self.w1 += w1_1
    self.b1 += b1_1

if __name__ == "__main__":
  # XOR/NAND dataset
  X = np.array([[0, 0, 0], [0, 1, 0], [1, 0, 0], [1, 1, 0], [0, 0, 1], [0, 1, 1], [1, 0, 1], [1, 1, 1]])
  Y = np.array([[0], [1], [1], [0], [1], [1], [1], [0]])

  nn = NN(input_sz=3, out_fc0_sz=3, out_fc1_sz=1)

  epochs = 10000

  for epoch in range(epochs):
    loss = 0
    num_correct_pred = 0

    for input, actual_out in zip(X, Y):

      # Feed-forward
      predicted_out = nn.forward(input)

      # Update accuracy
      if np.round(predicted_out) == actual_out:
        num_correct_pred += 1

      # For the loss we will be using mean square error(MSE)
      # Update loss
      loss += np.square(actual_out - predicted_out[0]) / len(Y)

      # Backpropagation
      nn.backward(input, actual_out)

    # Print accuracy and loss after each epoch
    if epoch % 100 == 0:
      acc = num_correct_pred / len(Y)
      print("epoch[{epoch}] loss: {loss} - accuracy: {acc}".format(epoch=epoch, loss=loss[0], acc=acc))

  print("Training finished!")

  # Model testing
  for x in X:
    print(f"Input: {x}, Output: {np.round(nn.forward(x)[0])}")
