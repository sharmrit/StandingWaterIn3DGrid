#include <iostream>
#include <fstream>
using namespace std;

struct Cell
{
	char height; 
	bool visited; 
};

void CellsChecked(Cell* cells_at_same_level, unsigned short a_w, unsigned short a_h, unsigned short w, unsigned short h, unsigned __int64* sum, bool* overflow)
{

	Cell& cell = cells_at_same_level[h * a_w + w];
	if (cell.height == 0 && !cell.visited)
	{
		cell.visited = true;
		if (w == 0 || w + 1 == a_w || h == 0 || h + 1 == a_h)
		{
			*overflow = true;
			*sum = 0;
		}

		if (!*overflow)
		{
			++*sum;
		}

		if (h < a_h - 1)
		{
			CellsChecked(cells_at_same_level, a_w, a_h, w, h + 1, sum, overflow);
		}
		else if (h > 0)
		{
			CellsChecked(cells_at_same_level, a_w, a_h, w, h - 1, sum, overflow);
		}
		else if (w > 0)
		{
			CellsChecked(cells_at_same_level, a_w, a_h, w - 1, h, sum, overflow);
		}
		else if (w < a_w - 1)
		{
			CellsChecked(cells_at_same_level, a_w, a_h, w + 1, h, sum, overflow);
		}
	}
}

//@param int const * const unsigned short *a_board - argument representing the NxM board.
//@param unsigned short a_w - argument representing the width of the board
//@param unsigned short a_h - argument representing the height of the board
//@return - unsigned __int64 - the volume of water the board retains
unsigned __int64 CalculateVolume(const unsigned short *a_board, unsigned short a_w, unsigned short a_h)
{
	if (!a_board || a_w < 3 || a_h < 3)
	{
		return 0;
	}

	int n = a_w * a_h;


	int maximum_height = 0;
	for (int i = 0; i < n; ++i)
	{
		if (maximum_height < a_board[i])
		{
			maximum_height = a_board[i];
		}
	}
	
	
	int *board = new int[n];
	for (int i = 0; i < n; i++)
	{
		board[i] = a_board[i];

	}
	
	
	Cell* cells_at_same_level = new Cell[n];
	unsigned __int64 totalVolume = 0;
	for (int i = 0; i < maximum_height; ++i)
	{
		unsigned __int64 water_at_current_level = 0;
		for (int j = 0; j < n; ++j)
		{
			if (board[j] > 0)
			{
				--board[j];
				cells_at_same_level[j].height = 1;
			}
			else
			{
				cells_at_same_level[j].height = 0;
			}
			cells_at_same_level[j].visited = false;
		}

		for (int i = 0; i < a_h; ++i)
		{
			for (int j = 0; j < a_w; ++j)
			{
				unsigned __int64 sum = 0;
				bool overflow = false;
				CellsChecked(cells_at_same_level, a_w, a_h, i, j, &sum, &overflow);
				water_at_current_level += sum;
			}
		}
		totalVolume += water_at_current_level;
	}

	delete[] cells_at_same_level;
	delete[] board;

	return totalVolume;
}

int main()
{
	int n, m;
	ifstream myfile;
	myfile.open("TestCase1.txt");
	myfile >> n;
	myfile >> m;
	int num = (n)*(m);
	unsigned short* board = new unsigned short[num];


	for (int i = 0; i < num; i++)
	{
			myfile >> board[i];
	}

	myfile.close();
	cout << "Volume:" << CalculateVolume(board, n, m) << endl;
	delete(board);
	return 0;
}
