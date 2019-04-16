class Dense():
    def __init__(self, size, prev_layer, activ, step_size, batch_size):
        # depends on input layer size and this layer's size
        self.size = size
        self.prev_layer = prev_layer
        self.activ = activ
        self.input = None
        self.weights = np.random.rand(size, prev_layer.size)
        self.weights_grad = None
        self.step_size = step_size
        self.batch_size = batch_size
        self.current_batch = 0

    def forward(self):
        # matrix multiplication of weights and previous layer Output
        # activ will take and return a vector
        self.input = self.prev_layer.forward()
        return self.activ(self.weights@self.input)

    def backward(self, grad):
        grad = self.activ.backward(grad)
        grad_input = (self.weight.T@grad)
        #call previous layer
        self.prev_layer.backward(grad_input)
        #update weights
        # if weights grad has not been init, then init it.
        if not self.weights_grad:
            self.weights_grad = grad@self.input.T
        else:
            # if it has been, the add to it
            self.weights_grad += grad@self.input.T
        self.current_batch += 1
        # If we are at our batch size, then average the weights grad and
        # update the weights.
        if self.current_batch == self.batch_size:
            self.weights += (self.weights_grad/self.batch_size)*self.step_size
            self.weights_grad = None
            self.current_batch = 0
