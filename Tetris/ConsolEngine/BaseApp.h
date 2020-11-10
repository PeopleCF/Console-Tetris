#pragma once

#include <Windows.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BaseApp
{
private:
	HANDLE mConsole;
	HANDLE mConsoleIn;

protected:
	CHAR_INFO* mChiBuffer;
	COORD mDwBufferSize;
	COORD mDwBufferCoord;
	SMALL_RECT mLpWriteRegion;

	void Render();

public:
	const int X_SIZE;
	const int Y_SIZE;

	BaseApp(int xSize = 100, int ySize = 80);
	virtual ~BaseApp();

	virtual void Run();


	virtual void SetChar(int x, int y, wchar_t c);
	virtual wchar_t GetChar(int x, int y);

	virtual void UpdateF(float deltaTime)
	{
	}
	virtual void KeyPressed(int btnCode)
	{
	}
};