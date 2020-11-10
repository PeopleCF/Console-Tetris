#pragma once
#include "Enums.h"

#include <cstdint>
#include <vector>
class MyApp;
class Figure
{
	static std::vector<std::vector<std::vector<int>>> figures;

public:
	static const int figureWidth;
	Figure(int x, int y, FigureType type, MyApp* MyApp);
	void paint();
	void erase();
	void rotate();
	void onLinesDestroyed(int firstLine, int lastLine);
	void changePosition(int x, int y);
	bool checkCollision(Direction direction);
	void randomise();
	std::pair<int, int> getLinesToCheck();
	int getX();
	int getY();
	std::vector<std::vector<int>>& getLayout();

private:
	int mX, mY;
	bool mMovable;
	MyApp* mApp;
	std::vector<std::vector<int>> mLayout;
};
