#include "Figure.h"

#include "MyApp.h"
std::vector<std::vector<std::vector<int>>> Figure::figures = {
	{{0, 1, 0}, {0, 1, 0}, {1, 1, 0}},
	{{0, 1, 0}, {0, 1, 0}, {0, 1, 0}},
	{{1, 1, 0}, {1, 1, 0}, {0, 0, 0}},
	{{0, 1, 0}, {0, 1, 0}, {0, 1, 1}},
	{{1, 1, 0}, {0, 1, 1}, {0, 0, 0}},
	{{0, 1, 0}, {1, 1, 1}, {0, 0, 0}},
	{{0, 1, 1}, {1, 1, 0}, {0, 0, 0}}};


const int Figure::figureWidth = 3;

Figure::Figure(int x, int y, FigureType type, MyApp* MyApp)
	: mX(x), mY(y), mMovable(true), mApp(MyApp)
{
	switch (type)
	{
		case FigureType::I:
		{
			mLayout = figures[static_cast<int>(type)];
			break;
		}
		case FigureType::J:
		{
			mLayout = figures[static_cast<int>(type)];
			break;
		}
		case FigureType::O:
		{
			mLayout = figures[static_cast<int>(type)];
			break;
		}
		case FigureType::L:
		{
			mLayout = figures[static_cast<int>(type)];
			break;
		}
		case FigureType::Z:
		{
			mLayout = figures[static_cast<int>(type)];
			break;
		}
		case FigureType::T:
		{
			mLayout = figures[static_cast<int>(type)];
			break;
		}
		case FigureType::S:
		{
			mLayout = figures[static_cast<int>(type)];
			break;
		}
	}
}

void Figure::paint()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (mLayout[i][j] == 1)
			{
				mApp->SetChar(mX + j, mY + i, MyApp::figureSymbol);
			}
		}
	}
}

void Figure::erase()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (mLayout[i][j] == 1)
			{
				mApp->SetChar(mX + j, mY + i, ' ');
			}
		}
	}
}

void Figure::rotate()	 // rotate left
{
	if (!mMovable)
	{
		return;
	}
	erase();
	std::vector<std::vector<int>> temp;
	for (int x = 0; x < 3 / 2; x++)
	{
		for (int y = x; y < 3 - x - 1; y++)
		{
			int temp = mLayout[x][y];

			mLayout[x][y] = mLayout[y][3 - 1 - x];

			mLayout[y][3 - 1 - x] = mLayout[3 - 1 - x][3 - 1 - y];

			mLayout[3 - 1 - x][3 - 1 - y] = mLayout[3 - 1 - y][x];

			mLayout[3 - 1 - y][x] = temp;
		}
	}
	paint();
}

void Figure::onLinesDestroyed(int firstLine, int lastLine)
{
}

void Figure::changePosition(int x, int y)
{
	erase();
	mX = x;
	mY = y;
	paint();
}

bool Figure::checkCollision(Direction direction)
{
	switch (direction)
	{
		case Direction::UP:
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (mLayout[i][j] == 1 && mApp->GetChar(mX + j, mY + i - 1) != ' ' && !(i - 1 >= 0 && mLayout[i - 1][j] == 1))
					{
						return true;
					}
				}
			}
			break;
		}
		case Direction::DOWN:
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (mLayout[i][j] == 1 && mApp->GetChar(mX + j, mY + i + 1) != ' ' && !(i + 1 < 3 && mLayout[i + 1][j] == 1))
					{
						return true;
					}
				}
			}
			break;
		}
		case Direction::LEFT:
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					char x = mApp->GetChar(mX + j - 1, mY + i);
					if (mLayout[i][j] == 1 && mApp->GetChar(mX + j - 1, mY + i) != ' ' && !(j - 1 >= 0 && mLayout[i][j - 1] == 1))
					{
						return true;
					}
				}
			}
			break;
		}
		case Direction::RIGHT:
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (mLayout[i][j] == 1 && mApp->GetChar(mX + j + 1, mY + i) != ' ' && !(j + 1 < 3 && mLayout[i][j + 1] == 1))
					{
						return true;
					}
				}
			}
			break;
		}
	}
	return false;
}

void Figure::randomise()
{
	mLayout = figures[(rand() % 6)];
}

std::pair<int, int> Figure::getLinesToCheck()
{
	//for (vec : )
	return std::pair<int, int>();
}

int Figure::getX()
{
	return mX;
}

int Figure::getY()
{
	return mY;
}

std::vector<std::vector<int>>& Figure::getLayout()
{
	return mLayout;
}
