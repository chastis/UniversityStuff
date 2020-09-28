from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt

# start points:
point_x = [1, 2, 3, 3, 5, 6, 7, 9]
point_y = [1, 4, 2, 4, 1, 1, 2, 1]
point_z = [1, 0, 2, 2, 2, 0, 3, 3]

fig = plt.figure()
ax = plt.axes(projection='3d')
temp_p1_x, temp_p1_y, temp_p1_z = point_x[0::2], point_y[0::2], point_z[0::2]
temp_p2_x, temp_p2_y, temp_p2_z = point_x[1::2], point_y[1::2], point_z[1::2]

pol_order = 4
# knot vectors:
U = V = [0.0, 0.0, 1.0/4.0, 2.0/4.0, 3.0/4.0, 1.0, 1.0]


# find B for u
def get_b(i_, p, cur_u, arr_u):
    if p == 0:
        if arr_u[i_] <= cur_u < arr_u[i_ + 1]:
            return 1.0
        else:
            return 0.0
    else:
        sum_ = 0
        try:
            b = get_b(i_, p - 1, cur_u, arr_u)
            val1 = (cur_u - arr_u[i_]) / (arr_u[i_ + p] - arr_u[i_]) * b
            sum_ += val1
        except:
            sum_ = 0

        try:
            b = get_b(i_ + 1, p - 1, cur_u, arr_u)
            val2 = (arr_u[i_ + p + 1] - cur_u) / (arr_u[i_ + p + 1] - arr_u[i_ + 1]) * b
            sum_ += val2
        except:
            pass

        return sum_


# draw surface for 4 points
def count_for_points(points_x, points_y, points_z):
    u = 0.0
    surf_x = np.empty(0)
    surf_y = np.empty(0)
    surf_z = np.empty(0)
    while u <= 1.0:
        v = 0.0
        while v <= 1.0:
            count_top_x = 0.0
            count_top_y = 0.0
            count_top_z = 0.0
            count_down = 0.0
            for i in range(2):
                for j in range(2):
                    Bip = get_b(i, pol_order, u, U)
                    Bjp = get_b(j, pol_order, v, V)
                    count_top_x += Bip * Bjp * points_x[i * 2 + j]
                    count_top_y += Bip * Bjp * points_y[i * 2 + j]
                    count_top_z += Bip * Bjp * points_z[i * 2 + j]
                    count_down += Bip * Bjp

            if count_down != 0:
                surf_x = np.append(surf_x, count_top_x/count_down)
                surf_y = np.append(surf_y, count_top_y/count_down)
                surf_z = np.append(surf_z, count_top_z/count_down)
            v += 0.01

        u += 0.01
    ax.plot3D(surf_x, surf_y, surf_z, linewidth=2)


count_for_points(point_x[4:8], point_y[4:8], point_z[4:8])
count_for_points(point_x[2:6], point_y[2:6], point_z[2:6])
count_for_points(point_x[0:4], point_y[0:4], point_z[0:4])

p1, = ax.plot3D(temp_p1_x, temp_p1_y, temp_p1_z, 'ro')
p2, = ax.plot3D(temp_p2_x, temp_p2_y, temp_p2_z, 'go')
plt.show()
