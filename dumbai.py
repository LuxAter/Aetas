import time

def dumb_ai(position):
    time.sleep(0.1)
    snake = position[0]
    apple = position[1]

    def dist(a, b):
        return abs(a[0] - b[0]) + abs(a[1] - b[1])

    options = []
    if (snake[-1][0], snake[-1][1] - 1) not in snake:
        options.append([0, (snake[-1][0], snake[-1][1] - 1)])
    if (snake[-1][0], snake[-1][1] + 1) not in snake:
        options.append([1, (snake[-1][0], snake[-1][1] + 1)])
    if (snake[-1][0] + 1, snake[-1][1]) not in snake:
        options.append([2, (snake[-1][0] + 1, snake[-1][1])])
    if (snake[-1][0] - 1, snake[-1][1]) not in snake:
        options.append([3, (snake[-1][0] - 1, snake[-1][1])])

    for i in options:
        i.append(dist(i[1], apple))

    options = sorted(options, key=lambda x: x[2])
    if not options:
        return -1
    return options[0][0]

