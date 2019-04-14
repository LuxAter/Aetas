class Relu():
    def __call__(self, input):
        self.input = input
        return np.maximum(input, 0)

    def backward(self):
        return np.where(self.input <= 0, 0, 1)
