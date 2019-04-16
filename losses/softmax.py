class Softmax():
    def __call__(self, input):
        self.input = input
        return input

    def backward(self, actual):
        return -actual + np.log(np.sum(np.exp(self.input)))
