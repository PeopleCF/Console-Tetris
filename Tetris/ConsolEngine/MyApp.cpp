// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "MyApp.h"

#include "Enums.h"

#include <algorithm>
#include <chrono>
#include <mutex>
#include <thread>
#undef min
#undef max
std::chrono::milliseconds MyApp::interval = std::chrono::milliseconds(400);
MyApp::MyApp()
	: Parent(FieldWidth, FieldHeight)
	, ControlledFigure(std::max(1, rand() % (playfieldWidth - Figure::figureWidth)), 1, static_cast<FigureType>(rand() % 6), this)
	, figurePreview(previewFigureX, previewFigureY, static_cast<FigureType>(rand() % 6), this)
{
	mField.resize(FieldHeight);
	for (int i = 0; i < FieldHeight; i++)
		mField[i].resize(FieldWidth);

	for (int i = 0; i < FieldHeight; i++)
	{
		mField[i][0] = 2;
		mField[i][FieldWidth - 1] = 2;
		mField[i][playfieldWidth] = 2;
	}

	for (int i = 0; i < FieldWidth; i++)
	{
		mField[0][i] = 2;
		mField[FieldHeight - 1][i] = 2;
	}
	mOldField = mField;
}

void MyApp::Run()
{
	for (int i = 0; i < FieldHeight; i++)
	{
		for (int j = 0; j < FieldWidth; j++)
		{
			if (mField[i][j])
			{
				SetChar(j, i, L'#');
			}
			else
			{
				SetChar(j, i, L' ');
			}
		}
	}

	BaseApp::Run();
}

void MyApp::KeyPressed(int btnCode)
{
	if (btnCode == 115)	   // s
	{
		while (!ControlledFigure.checkCollision(Direction::DOWN))
		{
			ControlledFigure.erase();
			ControlledFigure.changePosition(ControlledFigure.getX(), ControlledFigure.getY() + 1);
			ControlledFigure.paint();
		}
	}
	else if (btnCode == 97)	   // a
	{
		if (ControlledFigure.checkCollision(Direction::LEFT))
		{
			return;
		}
		ControlledFigure.erase();
		ControlledFigure.changePosition(ControlledFigure.getX() - 1, ControlledFigure.getY());
		ControlledFigure.paint();
	}
	else if (btnCode == 100)	// d
	{
		if (ControlledFigure.checkCollision(Direction::RIGHT))
		{
			return;
		}
		ControlledFigure.erase();
		ControlledFigure.changePosition(ControlledFigure.getX() + 1, ControlledFigure.getY());
		ControlledFigure.paint();
	}
	else if (btnCode == 32)	   // space
	{
		ControlledFigure.rotate();
	}
}

void MyApp::UpdateF(float deltaTime)
{
	figurePreview.paint();
	auto currentTime = std::chrono::system_clock::now();
	auto s = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime);
	if (s < MyApp::interval)
	{
		return;
	}
	lastMoveTime = std::chrono::system_clock::now();

	if (!ControlledFigure.checkCollision(Direction::DOWN))
	{
		ControlledFigure.erase();
		ControlledFigure.changePosition(ControlledFigure.getX(), ControlledFigure.getY() + 1);
		ControlledFigure.paint();
	}
	else
	{
		auto layout = ControlledFigure.getLayout();
		std::vector<int> linesToCheck;
		for (int i = 0; i < layout.size(); i++)
		{
			for (int j = 0; j < layout[i].size(); j++)
			{
				if (layout[i][j] != 0)
				{
					linesToCheck.push_back(i + ControlledFigure.getY());
					break;
				}
			}
		}
		checkCompletenessOfLines(linesToCheck);
		ControlledFigure = figurePreview;
		ControlledFigure.changePosition(std::max(1, rand() % (playfieldWidth - Figure::figureWidth)), 1);
		figurePreview.randomise();
	}
}

void MyApp::DestroyLine(int line)
{
	for (int i = line; i > 2; i--)
	{
		for (int j = 1; j < playfieldWidth; j++)
		{
			mField[i][j] = mField[i - 1][j];
		}
	}
}

void MyApp::checkCompletenessOfLines(std::vector<int> lines)
{
	mOldField = mField;
	std::vector<int> linesToDestroy;
	for (auto line : lines)
	{
		bool isComplete = true;
		for (int i = 1; i < playfieldWidth; i++)
		{
			if (mField[line][i] == 0)
			{
				isComplete = false;
				break;
			}
		}
		if (isComplete)
		{
			linesToDestroy.push_back(line);
		}
	}
	if (linesToDestroy.size() > 0)
	{
		mOldField = mField;
		for (auto l :linesToDestroy)
		{
			DestroyLine(l);
		}
		paintField();
		//MyApp::interval *= 0.95;
	}
}

void MyApp::paintField()
{
	for (int i = 0; i < FieldHeight; i ++)
	{
		for (int j = 0; j < playfieldWidth; j++)
		{
			if (mField[i][j] != mOldField[i][j])
			{
				switch (mField[i][j])
				{
					case 0:
						SetChar(j, i, ' ');
						break;
					case 1:
						SetChar(j, i, MyApp::figureSymbol);
						break;
					case 2:
						SetChar(j, i, '#');
						break;
				}
			}
		}
	}
}

void MyApp::SetChar(int x, int y, wchar_t c)
{
	BaseApp::SetChar(x, y, c);
	int a = 0;
	switch (c)
	{
		case ' ':
			a = 0;
			break;
		case MyApp::figureSymbol:
			a = 1;
			break;
		case '#':
			a = 2;
			break;
		default:;
	}
	mField[y][x] = a;
}
