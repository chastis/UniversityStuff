import sys
import numpy as np
import matplotlib.pyplot as plt

# Поворот направо
def RightTurn(p1, p2, p3):
	if (p3[1]-p1[1])*(p2[0]-p1[0]) >= (p2[1]-p1[1])*(p3[0]-p1[0]):
		return False
	return True
	
# головний алгоритм
def razd_i_vlast(P):
	P.sort()			
	L_upper = [P[0], P[1]]		# Верхня частина
	# Рахує верхню частину оболонки
	for i in range(2,len(P)):
		L_upper.append(P[i])
		while len(L_upper) > 2 and not RightTurn(L_upper[-1],L_upper[-2],L_upper[-3]):
			del L_upper[-2]
	L_lower = [P[-1], P[-2]]	# Нижня частина
	# Рахує нижню частину оболонки
	for i in range(len(P)-3,-1,-1):
		L_lower.append(P[i])
		while len(L_lower) > 2 and not RightTurn(L_lower[-1],L_lower[-2],L_lower[-3]):
			del L_lower[-2]
	del L_lower[0]
	del L_lower[-1]
	L = L_upper + L_lower		# Будує повну оболонку
	return np.array(L)

def main():
	try:
		N = int(sys.argv[1])
	except:
		N = int(input("Введіть кількість точок: "))
	
	P = [(np.random.randint(0,300),np.random.randint(0,300)) for i in range(N)]
	L = razd_i_vlast(P)
	P = np.array(P)
	
	# Графік
	plt.figure()
	plt.plot(L[:,0],L[:,1], 'b-', picker=5)
	plt.plot([L[-1,0],L[0,0]],[L[-1,1],L[0,1]], 'b-', picker=5)
	plt.plot(P[:,0],P[:,1],".r")
	plt.axis('off')
	plt.show()

if __name__ == '__main__':
	main()