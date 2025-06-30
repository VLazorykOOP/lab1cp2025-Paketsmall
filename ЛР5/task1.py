import matplotlib.pyplot as plt
import numpy as np

# Точки
P1 = np.array([1, 1])
P2 = np.array([2, 3])
P3 = np.array([4, 3])
P4 = np.array([5, 1])

def bezier(t, P1, P2, P3, P4):
    return (1 - t)**3 * P1 + 3*(1 - t)**2 * t * P2 + 3*(1 - t) * t**2 * P3 + t**3 * P4

t_vals = np.linspace(0, 1, 100)
curve = np.array([bezier(t, P1, P2, P3, P4) for t in t_vals])

plt.plot(curve[:,0], curve[:,1], label="Крива Без’є")
plt.plot(*zip(P1, P2, P3, P4), 'ro--', label='Контрольні точки')
plt.legend()
plt.title("Крива Без’є 3-го порядку")
plt.axis('equal')
plt.grid(True)
plt.show()
