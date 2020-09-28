# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt


class Point:
    def __init__(self, x=0.0, y=0.0):
        self.x = x
        self.y = y

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __repr__(self):
        return "(" + str(self.x) + " ; " + str(self.y) + ")"

def read_points(file_name):
    points_list = []
    input_array = open(file_name).read().split()

    i = 0
    while i < len(input_array):
        new_point = Point(float(input_array[i]), float(input_array[i + 1]))
        points_list.append(new_point)
        i += 2
    return points_list

def orientation(a, b, c):
    value = (b.y - a.y) * (c.x - b.x) - (c.y - b.y) * (b.x - a.x)
    if value == 0:
        return 0
    if value > 0:
        return 1
    if value < 0:
        return -1


def get_jarvis_hull(points, n):
    if n <= 2:
        return

    result = []

    leftmost = 0
    p = leftmost
    q = -1
    while q != leftmost:
        result.append(points[p])
        q = get_next_index(points, p)
        for i in range(n):
            if orientation(points[p], points[i], points[q]) == -1:
                q = i

        p = q

    return result


def get_next_index(array, current_index):
    n = len(array)
    if current_index == n - 1:
        return 0
    return current_index + 1


def find_hull_approx(points):
    n = len(points)

    leftmost = points[0]
    rightmost = points[n - 1]
    distance = rightmost.x - leftmost.x

    k = int(distance / 2)

    width = distance / k
    stripes = []
    plt.plot([leftmost.x, leftmost.x], [-10, 10])

    for i in range(k):
        stripe = []
        for point in points:
            if leftmost.x + (i + 1) * width > point.x >= leftmost.x + i * width:
                stripe.append(point)
        stripes.append(stripe)
        if i == k - 1:
            stripes[i].append(rightmost)
        plt.plot([leftmost.x + (i + 1) * width, leftmost.x + (i + 1) * width], [-10, 10], '-b')

    plt.draw()
    potential_hull = []
    for stripe in stripes:
        if len(stripe) == 0:
            continue
        low = min(stripe, key = lambda point: point.y)
        high = max(stripe, key=lambda point: point.y)
        if potential_hull.count(low) == 0:
            potential_hull.append(low)
        if potential_hull.count(high) == 0:
            potential_hull.append(high)

        plt.plot([low.x, high.x], [low.y, high.y], 'ro')

    plt.draw()

    if potential_hull.count(leftmost) == 0:
        potential_hull.append(leftmost)
    if potential_hull.count(rightmost) == 0:
        potential_hull.append(rightmost)

    return get_jarvis_hull(potential_hull, len(potential_hull))


def main():
    points = read_points("points.txt")
    points = sorted(points, key=lambda point: point.x)
    print(points)

    xs = []
    ys = []
    for point in points:
        xs.append(point.x)
        ys.append(point.y)

    plt.plot(xs, ys, 'ko')
    plt.draw()

    hull = find_hull_approx(points)
    xs = []
    ys = []
    for point in hull:
        xs.append(point.x)
        ys.append(point.y)

    plt.plot(xs, ys, '-go')
    plt.plot([xs[0], xs[len(hull) - 1]], [ys[0], ys[len(hull) - 1]], '-go')

    plt.axis([-10, 10, -10, 10])
    plt.show()


if __name__ == '__main__':
	main()