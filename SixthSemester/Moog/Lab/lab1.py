import numpy as np
from matplotlib import pyplot as plt
from matplotlib import collections as mc

# start points
SIZE = 9
points_x = [1, 2, 4, 5, 7, 6, 8, 9, 10]
points_y = [1, 2, 1, 3, 2, 1, 4, 5, 3]

lines = np.empty(0)
for i in range(SIZE - 1):
    lines = np.append(lines, [points_x[i], points_y[i], points_x[i + 1], points_y[i + 1]])
lines = np.reshape(lines, (lines.shape[0] // 4, 2, 2))

fig = plt.figure(1)
ax = plt.axes(xlim=(-1, 11), ylim=(-1, 11))
lc = mc.LineCollection(lines, colors='green', linewidths=1.2)
ax.add_collection(lc)


# find Bezier coef
def rec_form(points, start, end, t):
    if start == end:
        return points[start]
    return (1.0-t)*rec_form(points, start, end-1, t) + t*rec_form(points, start+1, end, t)


# get bezier points:
bezier_points_x = np.empty(0)
bezier_points_y = np.empty(0)
points_on_plot, = ax.plot(points_x, points_y, 'ro')

t = 0.0
while t <= 1.0:
    bezier_points_x = np.append(bezier_points_x, rec_form(points_x, 0, SIZE-1, t))
    bezier_points_y = np.append(bezier_points_y, rec_form(points_y, 0, SIZE-1, t))

    t += 0.01

bezier_p, = ax.plot(bezier_points_x, bezier_points_y, color='darkorchid', linewidth=3)

plt.show()
