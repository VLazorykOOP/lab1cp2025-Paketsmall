import matplotlib.pyplot as plt
import numpy as np

def koch_curve(p1, p2, order):
    if order == 0:
        return [p1, p2]
    else:
        p1 = np.array(p1)
        p2 = np.array(p2)
        delta = (p2 - p1) / 3
        a = p1 + delta
        b = p1 + 2 * delta

        # Вектор повороту на 60 градусів назовні
        angle = np.pi / 3
        rot = np.array([[np.cos(angle), -np.sin(angle)],
                        [np.sin(angle),  np.cos(angle)]])
        peak = a + rot @ (delta)

        return (koch_curve(p1, a, order-1) +
                koch_curve(a, peak, order-1)[1:] +
                koch_curve(peak, b, order-1)[1:] +
                koch_curve(b, p2, order-1)[1:])

def draw_koch_square(order, size=1):
    # Кутові точки квадрату
    p1 = [0, 0]
    p2 = [size, 0]
    p3 = [size, size]
    p4 = [0, size]

    sides = [
        koch_curve(p1, p2, order),
        koch_curve(p2, p3, order),
        koch_curve(p3, p4, order),
        koch_curve(p4, p1, order)
    ]

    for side in sides:
        x, y = zip(*side)
        plt.plot(x, y)

    plt.axis('equal')
    plt.title(f"Фрактал Коха на квадраті (порядок {order})")
    plt.grid(True)
    plt.show()

draw_koch_square(order=3)
