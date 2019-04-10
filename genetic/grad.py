import numpy as np
import matplotlib.pyplot as plt


def L(X):
    return ((X[0][0]**2) + (X[0][1]**2)) + (
        (1.0 - X[-1][0])**2 + (1.0 - X[-1][1])**2) + sum(
            [(X[i + 1][0] - X[i][0])**2 + (X[i + 1][1] - X[i][1])**2
             for i in range(0, X.shape[0] - 1)])


def calc_grad_uniform(pts):
    grad = np.ndarray(pts.shape)
    grad[0, 0] = 2.0 * pts[0][0] - 2.0 * (pts[1][0] - pts[0][0])
    grad[0, 1] = 2.0 * pts[0][1] - 2.0 * (pts[1][1] - pts[0][1])
    grad[-1, 0] = 2.0 * (pts[-1][0] - pts[-2][0]) - 2.0 * (1.0 - pts[-1][0])
    grad[-1, 1] = 2.0 * (pts[-1][1] - pts[-2][1]) - 2.0 * (1.0 - pts[-1][1])
    for i in range(1, grad.shape[0] - 1):
        grad[i, 0] = 2.0 * (pts[i][0] - pts[i - 1][0]) - 2.0 * (
            pts[i + 1][0] - pts[i][0])
        grad[i, 1] = 2.0 * (pts[i][1] - pts[i - 1][1]) - 2.0 * (
            pts[i + 1][1] - pts[i][1])
    return grad


def pderx(ptp, pt, ptn):
    return ((ptn[0] - pt[0])**2 +
            (ptn[1] - pt[1])**2)**(-0.5) * (-(ptn[0] - pt[0])) + (
                (pt[0] - ptp[0])**2 +
                (pt[1] - ptp[1])**2)**(-0.5) * (pt[0] - ptp[0])


def pdery(ptp, pt, ptn):
    return ((ptn[0] - pt[0])**2 +
            (ptn[1] - pt[1])**2)**(-0.5) * (-(ptn[1] - pt[1])) + (
                (pt[0] - ptp[0])**2 +
                (pt[1] - ptp[1])**2)**(-0.5) * (pt[1] - ptp[1])


def calc_grad(pts):
    grad = np.ndarray(pts.shape)
    grad[0, 0] = pderx((0, 0), pts[0], pts[1])
    grad[0, 1] = pdery((0, 0), pts[0], pts[1])
    grad[-1, 0] = pderx(pts[-2], pts[-1], (1, 1))
    grad[-1, 1] = pdery(pts[-2], pts[-1], (1, 1))
    for i in range(1, grad.shape[0] - 1):
        grad[i, 0] = pderx(pts[i-1], pts[i], pts[i+1])
        grad[i, 1] = pdery(pts[i-1], pts[i], pts[i+1])
    return grad


def main():
    count = 100
    pts = np.random.random((count, 2))
    for step in range(5000):
        print("STEP: {} FIT: {}".format(step, L(pts)))
        grad = calc_grad(pts)
        pts -= (0.005 * grad)
        if step % 10 == 0:
            fig = plt.figure(frameon=False)
            fig.set_size_inches(5, 5)
            ax = plt.Axes(fig, [0., 0., 1., 1.])
            ax.set_xlim(-0.05, 1.05)
            ax.set_ylim(-0.05, 1.05)
            ax.set_axis_off()
            fig.add_axes(ax)
            X = [0] + [pts[j][0] for j in range(0, count)] + [1]
            Y = [0] + [pts[j][1] for j in range(0, count)] + [1]
            ax.plot(X, Y)
            ax.plot(X, Y, 'k.')
            fig.savefig("img/{}.png".format(step // 10), dpi=200)


if __name__ == "__main__":
    main()
