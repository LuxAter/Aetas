class Input():
    def __init__(self):
        self.data = None
        pass

    def forward(self):
        #returns the vector of input data[]
        return self.data

    def backward(self):
        #does nothing
        pass
