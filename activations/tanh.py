class Tanh():
    def __call__(self, input):
        self.input = input
        return np.tanh(input)

    def backward(self):
        return 1.0/((np.cosh(input))**2)
