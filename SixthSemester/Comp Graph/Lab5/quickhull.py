import matplotlib.pyplot as plt
import numpy as np


class Point:
    def __init__(self, x=0.0, y=0.0):
        self.x = x
        self.y = y

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __repr__(self):
        return "(" + str(self.x) + " ; " + str(self.y) + ")"


hull = []


def read_points(file_name):
    points_list = []
    input_array = open(file_name).read().split()

    i = 0
    while i < len(input_array):
        new_point = Point(int(input_array[i]), int(input_array[i + 1]))
        points_list.append(new_point)
        i += 2
    return points_list


def distance(p1, p2, p):
    outer_product = (p[0] - p1[0]) * (p2[1] - p1[1]) - (p[1] - p1[1]) * (p2[0] - p1[0])
    return abs(outer_product)


def on_side(p1, p2, p):
    outer_product = (p[0] - p1[0]) * (p2[1] - p1[1]) - (p[1] - p1[1]) * (p2[0] - p1[0])

    if outer_product > 0:
        return 1
    if outer_product < 0:
        return -1
    return 0


def quick_hull(points, n, p1, p2, side):
    inner_point = None
    max_distance = 0

    for point in points:
        dist = distance(p1, p2, point)
        if dist > max_distance and on_side(p1, p2, point) == side:
            max_distance = dist
            inner_point = point

    if inner_point is None:
        if p1 not in hull:
            hull.append(p1)
        if p2 not in hull:
            hull.append(p2)
        return

    quick_hull(points, n, inner_point, p1, -1 * on_side(inner_point, p1, p2))
    quick_hull(points, n, inner_point, p2, -1 * on_side(inner_point, p2, p1))


def find_hull(points, n):
    if n < 3:
        print("Алгоритм працює тільки з кількістю точок, що перевищує 3")
        return

    min_x = min(points, key=lambda point: point[0])
    max_x = max(points, key=lambda point: point[0])

    quick_hull(points, n, min_x, max_x, 1)
    quick_hull(points, n, min_x, max_x, -1)

    for point in hull:
        print(point)
    return


def main():
	N = int(input("Введіть кількість точок: "))
	points = [(np.random.randint(0,300),np.random.randint(0,300)) for i in range(N)]
	n = len(points)

	for point in points:
		plt.plot(point[0], point[1], 'g.')

	find_hull(points, n)
	for point in hull:
		plt.plot(point[0], point[1], 'ro-')
	#plt.axis([-10, 10, -10, 10])
	plt.show()
	return


if __name__ == '__main__':
	main()