# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt

import math
def Mod(x, y):
  if y==0:  return x
  return x-y*math.floor(x/y)

class TCubicHermiteSpline:
  class TKeyPoint:
    T= 0.0  #Input
    X= 0.0  #Output
    M= 0.0  #Gradient
    def __str__(self):
      return '['+str(self.T)+', '+str(self.X)+', '+str(self.M)+']'

  class TParam: pass

  def __init__(self):
    self.idx_prev= 0
    self.Param= self.TParam()

  def FindIdx(self, t, idx_prev=0):
    idx= idx_prev
    if idx>=len(self.KeyPts): idx= len(self.KeyPts)-1
    while idx+1<len(self.KeyPts) and t>self.KeyPts[idx+1].T:  idx+=1
    while idx>=0 and t<self.KeyPts[idx].T:  idx-=1
    return idx

  def Evaluate(self, t):
    idx= self.FindIdx(t,self.idx_prev)
    if abs(t-self.KeyPts[-1].T)<1.0e-6:  idx= len(self.KeyPts)-2
    if idx<0 or idx>=len(self.KeyPts)-1:
      if idx<0:
        idx= 0
        t= self.KeyPts[0].T
      else:
        idx= len(self.KeyPts)-2
        t= self.KeyPts[-1].T

    h00= lambda t: t*t*(2.0*t-3.0)+1.0
    h10= lambda t: t*(t*(t-2.0)+1.0)
    h01= lambda t: t*t*(-2.0*t+3.0)
    h11= lambda t: t*t*(t-1.0)

    self.idx_prev= idx
    p0= self.KeyPts[idx]
    p1= self.KeyPts[idx+1]
    tr= (t-p0.T) / (p1.T-p0.T)
    return h00(tr)*p0.X + h10(tr)*(p1.T-p0.T)*p0.M + h01(tr)*p1.X + h11(tr)*(p1.T-p0.T)*p1.M

  def PhaseInfo(self, t):
    t0= self.KeyPts[0].T
    te= self.KeyPts[-1].T
    T= te-t0
    mod= Mod(t-t0,T)
    tp= t0+mod  #Phase
    n= (t-t0-mod)/T
    return n, tp

  def EvaluateC(self, t, pi=None):
    if pi==None:
      n, tp= self.PhaseInfo(t)
    else:
      n, tp= pi
    return self.Evaluate(tp) + n*(self.KeyPts[-1].X - self.KeyPts[0].X)

  #data= [[t0,x0],[t1,x1],[t2,x2],...]
  FINITE_DIFF=0  #Tangent method: finite difference method
  CARDINAL=1  #Tangent method: Cardinal spline (c is used)
  ZERO= 0  #End tangent: zero
  GRAD= 1  #End tangent: gradient (m is used)
  CYCLIC= 2  #End tangent: treating data as cyclic (KeyPts[-1] and KeyPts[0] are considered as an identical point)
  def Initialize(self, data, tan_method=CARDINAL, end_tan=GRAD, c=0.0, m=1.0):
    if data != None:
      self.KeyPts= [self.TKeyPoint() for i in range(len(data))]
      for idx in range(len(data)):
        self.KeyPts[idx].T= data[idx][0]
        self.KeyPts[idx].X= data[idx][1]

    #Store parameters for future use / remind parameters if not given
    if tan_method==None:  tan_method= self.Param.TanMethod
    else:                 self.Param.TanMethod= tan_method
    if end_tan==None:  end_tan= self.Param.EndTan
    else:              self.Param.EndTan= end_tan
    if c==None:  c= self.Param.C
    else:        self.Param.C= c
    if m==None:  c= self.Param.M
    else:        self.Param.M= m

    grad= lambda idx1,idx2: (self.KeyPts[idx2].X-self.KeyPts[idx1].X)/(self.KeyPts[idx2].T-self.KeyPts[idx1].T)

    if tan_method == self.FINITE_DIFF:
      for idx in range(1,len(self.KeyPts)-1):
        self.KeyPts[idx].M= 0.5*grad(idx,idx+1) + 0.5*grad(idx-1,idx)
    elif tan_method == self.CARDINAL:
      for idx in range(1,len(self.KeyPts)-1):
        self.KeyPts[idx].M= (1.0-c)*grad(idx-1,idx+1)

    if end_tan == self.ZERO:
      self.KeyPts[0].M= 0.0
      self.KeyPts[-1].M= 0.0
    elif end_tan == self.GRAD:
      self.KeyPts[0].M= m*grad(0,1)
      self.KeyPts[-1].M= m*grad(-2,-1)
    elif end_tan == self.CYCLIC:
      if tan_method == self.FINITE_DIFF:
        grad_p1= grad(0,1)
        grad_n1= grad(-2,-1)
        M= 0.5*grad_p1 + 0.5*grad_n1
        self.KeyPts[0].M= M
        self.KeyPts[-1].M= M
      elif tan_method == self.CARDINAL:
        T= self.KeyPts[-1].T - self.KeyPts[0].T
        X= self.KeyPts[-1].X - self.KeyPts[0].X
        grad_2= (X+self.KeyPts[1].X-self.KeyPts[-2].X)/(T+self.KeyPts[1].T-self.KeyPts[-2].T)
        M= (1.0-c)*grad_2
        self.KeyPts[0].M= M
        self.KeyPts[-1].M= M

  def Update(self):
    self.Initialize(data=None, tan_method=None, end_tan=None, c=None, m=None)


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

        #plt.plot([low.x, high.x], [low.y, high.y], 'ro')

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
    key_points = []
    for point in hull:
        key_points.append([point.x, point.y])
        xs.append(point.x)
        ys.append(point.y)

    xs.append(xs[0])
    ys.append(ys[0])
    #key_points.append([xs[0], ys[0]])
    #plt.plot(xs, ys, '-go')
    #plt.plot([xs[0], xs[len(hull) - 1]], [ys[0], ys[len(hull) - 1]], '-go')

    #key_points.sort()

    flag = True
    key_points_1 = []
    key_points_2 = []
    for i in range(len(xs) - 1):
        if (xs[i]<xs[i+1] and flag):
            key_points_1.append([xs[i], ys[i]])
        elif (xs[i]<xs[i+1] and not flag):
            if (xs[i-1]>xs[i]):
                key_points_2.append([xs[i], ys[i]])
            key_points_1.insert(0, [xs[i], ys[i]])
        else:
            if (flag):
                key_points_1.append([xs[i], ys[i]])
            key_points_2.append([xs[i], ys[i]])
            flag = False

    spline1= TCubicHermiteSpline()
    spline1.Initialize(key_points_1, tan_method=spline1.CARDINAL, c=0.0)
    

    X= []
    Y= []
    import numpy as np
    for i in range(len(key_points_1)-1):
        for t in np.arange(key_points_1[i][0], key_points_1[i+1][0], 0.001):
            x= spline1.Evaluate(t)
            X.append(t)
            Y.append(x)

    plt.plot(X,Y, '-m')

    X= []
    Y= []

    key_points_2.sort()
    spline2= TCubicHermiteSpline()
    spline2.Initialize(key_points_2, tan_method=spline2.CARDINAL, c=0.0)

    for i in range(len(key_points_2)-1):
        for t in np.arange(key_points_2[i][0], key_points_2[i+1][0], 0.001):
            x= spline2.Evaluate(t)
            X.append(t)
            Y.append(x)
            
    plt.plot(X,Y, '-m')

    plt.axis([-10, 10, -10, 10])
    plt.show()



if __name__ == '__main__':
	main()