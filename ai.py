import snake
import network


def evaluate(chromosome, N=20):

    network = None

    def get_move(position, N):
        rays = snake.wall_ray(position, N) + snake.snake_ray(
            position, N) + snake.apple_ray(position, N)
        probs = network.forward(rays)
        return probs.index(max(probs))

    return snake.snake(N, get_move)
