#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;

typedef vector<vector<bool> > V2b;
typedef vector<vector<vector<bool>>> V3b;
const int Right_bound = 15000, Left_bound = -15000, Up_bound = 15000, Down_bound = -15000;

//https://www.youtube.com/watch?v=Y-O4fkOAOk8&feature=youtu.be
//суть задачи это пэинт
//представляем прямоугольники в виде пикселей
//у нас есть только стенки толщиной один пиксель
//начиная сначала проходим по каждому пикселю и закрашиваем его
//и рекурсивно его соседей если это не стенка
//в итоге получается как заливка в пэинте
//каждый раз когда мы новый раз тыкаем заливку
//тобишь заливаем НЕ рекурсивно
//увеличиваем количество плоскостей на 1
//готово
struct Rectangle
{
	int minX, minY;
	int maxX, maxY;
};
int IndexOfSqueeze(vector<int> x, int val);
void PrintRectangles(vector<Rectangle>);
int CountFields(vector<Rectangle>&, int, int);
void Paint(int, int, V2b&, const V3b&, int, int);
int main()
{
	ifstream fin("data.in");
	vector<Rectangle> fig;
	int n;
	//cin >> n;
	fin >> n;
	for (int i(0); i < n; i++)
	{
		int x1, y1, x2, y2;
		//cin >> x1 >> y1 >> x2 >> y2;
		fin >> x1 >> y1 >> x2 >> y2;
		fig.push_back(Rectangle{ min(x1,x2),min(y1,y2),max(x1,x2),max(y1,y2) });
	}

	//fig.push_back(Rectangle{ Left_bound,Down_bound,Right_bound,Up_bound });
	PrintRectangles(fig);

	vector<int> x_squeeze, y_squeeze;
	x_squeeze.push_back(Right_bound + 1);
	x_squeeze.push_back(Left_bound - 1);
	y_squeeze.push_back(Up_bound + 1);
	y_squeeze.push_back(Down_bound - 1);

	for (Rectangle r : fig)
	{
		x_squeeze.push_back(r.minX); x_squeeze.push_back(r.maxX);
		y_squeeze.push_back(r.minY); y_squeeze.push_back(r.maxY);
	}

	sort(x_squeeze.begin(), x_squeeze.end());
	sort(y_squeeze.begin(), y_squeeze.end());

	x_squeeze.erase(unique(x_squeeze.begin(), x_squeeze.end()), x_squeeze.end());
	y_squeeze.erase(unique(y_squeeze.begin(), y_squeeze.end()), y_squeeze.end());

	for (Rectangle &r : fig)
	{ //except of realization binary_search with returning index, using lower_bound
		r.minX = IndexOfSqueeze(x_squeeze, r.minX);
		r.maxX = IndexOfSqueeze(x_squeeze, r.maxX);
		r.minY = IndexOfSqueeze(y_squeeze, r.minY);
		r.maxY = IndexOfSqueeze(y_squeeze, r.maxY);
	}
	PrintRectangles(fig);

	int count = CountFields(fig, x_squeeze.size(), y_squeeze.size());
	cout << count << "\n";
	cout << endl << "That's all Folks!" << endl;
	system("pause");
}
void PrintRectangles(vector<Rectangle> a)
{
	cout << "\n";
	for (int i(0); i < a.size(); i++)
		cout << i << ": " << a[i].minX << " " << a[i].minY << " " << a[i].maxX << " " << a[i].maxY << "\n";
}
int IndexOfSqueeze(vector<int> x, int val)
{
	vector<int>::iterator first = lower_bound(x.begin(), x.end(), val);
	return static_cast<int>(first - x.begin());// перевод из итератора в интежер
}
int CountFields(vector<Rectangle> &fig, int xs, int ys)
{
	int count = 0;
	int n = fig.size();

	V3b belongs(xs - 1, V2b(ys - 1, vector<bool>(n, false)));
	//belong[x][y][rectangle index]
	for (int ri = 0; ri < n; ri++)
	{
		for (int x = fig[ri].minX; x < fig[ri].maxX; x++)
			for (int y = fig[ri].minY; y < fig[ri].maxY; y++)
				belongs[x][y][ri] = 1;
	}

	V2b painted(xs - 1, vector<bool>(ys - 1, 0));
	for (int x = 0; x < xs - 1; x++)
		for (int y = 0; y < ys - 1; y++)
		{
			if (!painted[x][y])
			{
				Paint(x, y, painted, belongs, xs, ys);
				count++;
			}
		}

	return count;
}
void Paint(int x, int y, V2b& painted, const V3b& belongs, int xs, int ys)
{
	painted[x][y] = true;

	for (int dx = -1; dx <= 1; dx++)
		for (int dy = -1; dy <= 1; dy++)
			if (dx*dx + dy * dy == 1)
			{
				int nx = x + dx;
				int ny = y + dy;
				if (0 <= nx && nx < xs - 1 && 0 <= ny && ny < ys - 1 &&
					!painted[nx][ny] && belongs[x][y] == belongs[nx][ny])
					Paint(nx, ny, painted, belongs, xs, ys);
			}
}
