class Output():
    def __init__(self, prev_layer):
        self.prev_layer = prev_layer
        self.input = None

    def forward(self):
        self.input = self.prev_layer.forward()


    def backward(self):
        pass
