#include <iostream>
#include <stack>
#include <time.h>
#include <iomanip>
using namespace std;

const int n = 15;
const char element[3] = {'*', '#', '*'};


struct point
{
	int x, y, orient;
	point(int x, int y, int o)
	{
		this->x = x;
		this->y = y;
		this->orient = o;
	}
	void print()
	{
		cout << this->x << '\t' << this->y << '\t' << this->orient << endl;
	}
};


point offset(int o)
{
	int a = 0, b = 0;
	switch (o)
	{
	case(0):
		a = -1;
		break;
	case(1):
		a = -1;
		b = 1;
		break;
	case(2):
		b = 1;
		break;
	case(3):
		a = 1;
		b = 1;
		break;
	case(4):
		a = 1;
		break;
	case(5):
		a = 1;
		b = -1;
		break;
	case(6):
		b = -1;
		break;
	case(7):
		a = -1;
		b = -1;
		break;
	default:
		cerr << "不符合要求";
		exit(1);
		break;
	}
	point q(a, b, o);
	return q;
}

void move(point& p, int o)
{
	p.x += offset(o).x;
	p.y += offset(o).y;
	p.orient = o;
}


char** MazeGenerator()
{
	// allocate space for the two-dimensional array
	char** Maze = new char*[n];
	for (int i = 0; i < n; i++) {
		Maze[i] = new char[n];
	}
	// make time to be rand(in order to generate different numbers in every operations)
	srand((unsigned)time(NULL));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++ ) {
			// some border is certained
			if ((i == 0) || (i == n-1) || (j == 0) || (j == n-1)) {
				if ((i == 1 && j == 0) || (i == n - 2 && j == n - 1))
					Maze[i][j] = element[0];
				else
					Maze[i][j] = element[1];
			}
			else if ((i == 1 && j == 0)|| (i == 1 && j == 1)|| (i == n-2 && j == n-1)||(i == n-2 && j == n-2)) {
				Maze[i][j] = element[0];
			}
			else
				// allocate random values
				Maze[i][j] = element[rand()%3];
		}
	}
	return Maze;
}

char** BlankMazeGenerator()
{
	char** Maze = new char*[n];
	for (int i = 0; i < n; i++) {
		Maze[i] = new char[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			Maze[i][j] = element[0];
		}
	}
	return Maze;
}

char **BMaze = BlankMazeGenerator();


void MazePrint(char** maze)
{
	cout << setw(4) << ' ';
	for (int i = 0; i < n; i++) {
		cout << setw(4) << i;
	}
	cout << endl << setw(3)<<' ';
	for (int i = 0; i < n; i++) {
		cout << i << setw(4);
		for (int j = 0; j < n; j++) {
			cout << maze[i][j] << setw(4);
		}
		cout << endl;
	}
}

stack<point> FindPath(char** maze)
{
	// initiate a stack to store the path
	stack<point> s;
	// generate and store the first move method
	point p(1, 1, 2);
	BMaze[0][1] = 1;
	BMaze[1][1] = 1;
	s.push(p);
	int i(0);
	// if the stack is not empty, execute these operations
	while (s.size()!=0)
	{
		while (i < 8)
		{
			int x = p.x + offset(i).x;
			int y = p.y + offset(i).y;
			// when next position can be moved and is not traveled before, then move it
			if (maze[x][y] == '*' && BMaze[x][y] == '*') {
				move(p, i);
				s.push(p);
				if (x == n - 2 && y == n - 2) {
					return s;
				}
				// mark the travelled postion
				BMaze[x][y] = '#';
				i = 0;
				continue;
			}
			++i;
		}
		s.pop();
		if (s.size()==0) {
			cout << "该迷宫无解！请重新运行程序以刷新迷宫样式...";
		}
		else
		{
			p = point(s.top().x, s.top().y, s.top().orient);
			i = 0;
		}
	}
}


int main()
{
	char **maze = MazeGenerator();
	cout << "随机地图：" << endl;
	MazePrint(maze);
	cout << endl;
	stack<point> s = FindPath(maze);
	stack<point> output;
	cout << endl;
	while (s.size() != 0) {
		point p = s.top();
		output.push(p);
		s.pop();
	}
	while (output.size() != 0) {
		point q = output.top();
		output.pop();
		if(output.size()==0)
			cout << "(" << q.x << "," << q.y << ")" << endl;
		else
			cout << "(" << q.x << "," << q.y << ") ---> ";
	}
	cout << endl;
}