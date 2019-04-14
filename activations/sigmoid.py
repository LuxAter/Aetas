class Sigmoid():
    def __call__(self, input):
        self.input = input
        return 1.0/(1+np.exp(-input))

    def backward(self):
        return np.exp(-input)/((1+np.exp(-input))**2)
