// Reversi.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <algorithm>
#include <memory>
#include <functional>
#include <vector>
#include <iostream>

using namespace std;

class Board
{
public:
	const int size = 8;
private:
	vector<vector<int>> grid;
	int stones = 0;
public:
	Board(int s) : 
		size(s), grid(s, vector<int>(s))
	{}
	int countStone() const { return stones; }
	int stone(int row, int col) const
	{
		return grid[row][col];
	}
	bool valid(int row, int col) const
	{
		return row >= 0 && row < size &&
			col >= 0 && col < size;
	}
	int countScore() const
	{
		int countStone = 0;
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				countStone += grid[i][j];
			}
		}
		return countStone;
	}
	bool hasMove(bool side) const
	{
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if (canMove(i, j, side))
					return true;
			}
		}
		return false;
	}
	bool check(int &result) const
	{
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if (canMove(i, j, true) || canMove(i, j, false))
					return false;
			}
		}
		result = countScore();
		return true;
	}
	bool canMove(int row, int col, bool side) const
	{
		if (!valid(row, col) || grid[row][col] != 0)
			return false;
		int colour = side ? 1 : -1;
		for (int i = 1; row - i >= 0; ++i)
		{
			if (grid[row - i][col] == 0)
				break;
			else if (grid[row - i][col] == colour)
			{
				if (i > 1)
					return true;
				break;
			}
		}
		for (int i = 1; row + i < size; ++i)
		{
			if (grid[row + i][col] == 0)
				break;
			else if (grid[row + i][col] == colour)
			{
				if (i > 1)
					return true;
				break;
			}
		}
		for (int i = 1; col - i >= 0; ++i)
		{
			if (grid[row][col - i] == 0)
				break;
			else if (grid[row][col - i] == colour)
			{
				if (i > 1)
					return true;
				break;
			}
		}
		for (int i = 1; col + i < size; ++i)
		{
			if (grid[row][col + i] == 0)
				break;
			else if (grid[row][col + i] == colour)
			{
				if (i > 1)
					return true;
				break;
			}
		}
		for (int i = 1; row - i >= 0 && col - i >= 0; ++i)
		{
			if (grid[row - i][col - i] == 0)
				break;
			else if (grid[row - i][col - i] == colour)
			{
				if (i > 1)
					return true;
				break;
			}
		}
		for (int i = 1; row + i < size && col - i >= 0; ++i)
		{
			if (grid[row + i][col - i] == 0)
				break;
			else if (grid[row + i][col - i] == colour)
			{
				if (i > 1)
					return true;
				break;
			}
		}
		for (int i = 1; row - i >= 0 && col + i < size; ++i)
		{
			if (grid[row - i][col + i] == 0)
				break;
			else if (grid[row - i][col + i] == colour)
			{
				if (i > 1)
					return true;
				break;
			}
		}
		for (int i = 1; row + i < size && col + i < size; ++i)
		{
			if (grid[row + i][col + i] == 0)
				break;
			else if (grid[row + i][col + i] == colour)
			{
				if (i > 1)
					return true;
				break;
			}
		}
		return false;
	}
	bool makeMove(int row, int col, bool side)
	{
		if (!valid(row, col) || grid[row][col] != 0)
			return false;
		int colour = side ? 1 : -1;
		int countStone = 0;
		for (int i = 1; row - i >= 0; ++i)
		{
			if (grid[row - i][col] == 0)
				break;
			if (grid[row - i][col] == colour)
			{
				for (int j = 1; j < i; ++j)
				{
					grid[row - j][col] = colour;
					++countStone;
				}
				break;
			}
		}
		for (int i = 1; row + i < size; ++i)
		{
			if (grid[row + i][col] == 0)
				break;
			if (grid[row + i][col] == colour)
			{
				for (int j = 1; j < i; ++j)
				{
					grid[row + j][col] = colour;
					++countStone;
				}
				break;
			}
		}
		for (int i = 1; col - i >= 0; ++i)
		{
			if (grid[row][col - i] == 0)
				break;
			if (grid[row][col - i] == colour)
			{
				for (int j = 1; j < i; ++j)
				{
					grid[row][col - j] = colour;
					++countStone;
				}
				break;
			}
		}
		for (int i = 1; col + i < size; ++i)
		{
			if (grid[row][col + i] == 0)
				break;
			if (grid[row][col + i] == colour)
			{
				for (int j = 1; j < i; ++j)
				{
					grid[row][col + j] = colour;
					++countStone;
				}
				break;
			}
		}
		for (int i = 1; row - i >= 0 && col - i >= 0; ++i)
		{
			if (grid[row - i][col - i] == 0)
				break;
			if (grid[row - i][col - i] == colour)
			{
				for (int j = 1; j < i; ++j)
				{
					grid[row - j][col - j] = colour;
					++countStone;
				}
				break;
			}
		}
		for (int i = 1; row + i < size && col - i >= 0; ++i)
		{
			if (grid[row + i][col - i] == 0)
				break;
			if (grid[row + i][col - i] == colour)
			{
				for (int j = 1; j < i; ++j)
				{
					grid[row + j][col - j] = colour;
					++countStone;
				}
				break;
			}
		}
		for (int i = 1; row - i >= 0 && col + i < size; ++i)
		{
			if (grid[row - i][col + i] == 0)
				break;
			if (grid[row - i][col + i] == colour)
			{
				for (int j = 1; j < i; ++j)
				{
					grid[row - j][col + j] = colour;
					++countStone;
				}
				break;
			}
		}
		for (int i = 1; row + i < size && col + i < size; ++i)
		{
			if (grid[row + i][col + i] == 0)
				break;
			if (grid[row + i][col + i] == colour)
			{
				for (int j = 1; j < i; ++j)
				{
					grid[row + j][col + j] = colour;
					++countStone;
				}
				break;
			}
		}
		if (countStone == 0)
			return false;
		grid[row][col] = colour;
		++stones;
		return true;
	}
	void reset()
	{
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				grid[i][j] = 0;
			}
		}
		grid[size / 2][size / 2] = -1;
		grid[size / 2 - 1][size / 2] = 1;
		grid[size / 2][size / 2 - 1] = 1;
		grid[size / 2 - 1][size / 2 - 1] = -1;
		stones = 4;
	}
	void refresh(bool side) const
	{
		system("cls");
		int black = 0, white = 0;
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				switch (grid[i][j])
				{
				case 1:
					cout << 'B' << ' '; ++black;
					break;
				case -1:
					cout << 'W' << ' '; ++white;
					break;
				case 0:
					cout << (canMove(i, j, side) ? '@' : '#') << ' ';
					break;
				}
			}
			cout << endl;
		}
		cout << black << ' ' << white << endl;
		cout << (side ? 'B' : 'W') << endl;
	}
};

class Player
{
public:
	virtual void play(Board& board, bool side) const
	{
		for (int i = 0; i < board.size; ++i)
		{
			for (int j = 0; j < board.size; ++j)
			{
				if (board.makeMove(i, j, side))
					return;
			}
		}
	}
};

class Console : public Player
{
public:
	void play(Board& board, bool side) const override
	{
		int row, col;
		do
		{
			cin >> row >> col;
		} while (!board.makeMove(row, col, side));
	}
};

class Minimax : public Player
{
	const int maxDepth;
	const function<double(Board)> H;
public:
	Minimax(int d, double (*h)(const Board&)) : 
		maxDepth(d), H(h)
	{}
	void play(Board& board, bool side) const override
	{
		cout << maximize(board, side, 0, -INFINITY, INFINITY) << endl;
	}
private:
	double evaluate(const Board& board, bool side, int result, int depth) const
	{
		int colour = side ? 1 : -1;
		if (result != 0)
		{
			if (colour * result > 0)
				return INT_MAX - depth;
			else if (colour * result < 0)
				return -INT_MAX + depth;
			else
				return 0;
		}
		else
			return colour * H(board);
	}
	double maximize(Board& board, bool side, 
		int depth, double alpha, double beta) const
	{
		int result = 0;
		if (board.check(result) || depth == maxDepth)
			return evaluate(board, side, result, depth);
		else if (!board.hasMove(side))
			return -maximize(board, !side, depth + 1, -beta, -alpha);
		int maxRow, maxCol;
		double maxScore = -INFINITY;
		for (int i = 0; i < board.size; ++i)
		{
			for (int j = 0; j < board.size; ++j)
			{
				Board newBoard = board;
				if (newBoard.makeMove(i, j, side))
				{
					double score = -maximize(newBoard, !side, depth + 1, -beta, -alpha);
					if (score > maxScore)
					{
						maxScore = score;
						maxRow = i; maxCol = j;
					}
					alpha = max(alpha, maxScore);
					if (alpha >= beta)
						return maxScore;
				}
			}
		}
		board.makeMove(maxRow, maxCol, side);
		return maxScore;
	}
};

class Game
{
	Board board;
	Player *black, *white;
public:
	Game(Player* b, Player* w) : 
		board(8), black(b), white(w) {}
	void run()
	{
		board.reset();
		bool side = true;
		int result = 0;
		do
		{
			board.refresh(side);
			if (board.hasMove(side))
				(side ? black : white)->play(board, side);
			side = !side;
			//system("pause");
		} while (!board.check(result));
		board.refresh(side ? 1 : -1);
		cout << result << endl;
	}
};

class Heuristic
{
public:
	static double lin(const Board& board)
	{
		double sum = 0;
		for (int i = 0; i < board.size; ++i)
		{
			for (int j = 0; j < board.size; ++j)
			{
				sum += board.stone(i, j);
			}
		}
		return sum;
	}
	static double root(const Board& board)
	{
		const double s = board.size * board.size;
		double sum = 0;
		for (int i = 0; i < board.size; ++i)
		{
			for (int j = 0; j < board.size; ++j)
			{
				if ((i == 0 || i == board.size - 1) &&
					(j == 0 || j == board.size - 1))
				{
					sum += board.stone(i, j);
				}
				else if (i == 0 || i == board.size - 1 ||
					j == 0 || j == board.size - 1)
				{
					sum += board.stone(i, j) *
						sqrt(sqrt(board.countStone() / s));
				}
				else
				{
					sum += board.stone(i, j) *
						sqrt(board.countStone() / s);
				}
			}
		}
		return sum;
	}
};

int main()
{
	Console console;
	auto func1 = Heuristic::lin;
	auto func2 = Heuristic::root;
	Minimax minimax1(8, func1);
	Minimax minimax2(8, func2);
	Game game(&minimax1, &minimax2);
	game.run();
	return 0;
}
