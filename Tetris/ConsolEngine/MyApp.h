// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#pragma once

#include "BaseApp.h"
#include "Figure.h"
#include <chrono>
#include <mutex>
class MyApp : public BaseApp
{
	typedef BaseApp Parent;

public:
	static std::chrono::milliseconds interval;
	MyApp();
	void Run() override;
	virtual void KeyPressed(int btnCode);
	virtual void UpdateF(float deltaTime);
	void SetChar(int x, int y, wchar_t c) override;
	static const wchar_t MyApp::figureSymbol = 'D';
private:
	void DestroyLine(int line);
	void checkCompletenessOfLines(std::vector<int> lines);
	std::vector<std::vector<int>> mField;
	std::vector<std::vector<int>> mOldField;
	std::chrono::system_clock::time_point lastMoveTime;
	static const int playfieldWidth = 15;
	static const int FieldWidth = 30;
	static const int FieldHeight = 20;
	static const int previewFigureX = 17;
	static const int previewFigureY = 4;
	std::mutex mMutex;
	void paintField();
	Figure ControlledFigure;
	Figure figurePreview;
};
