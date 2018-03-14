#include "GLUTCallbacks.h"
#include "mainGame.h"

namespace GLUTCallbacks
{
	namespace
	{
		mainGame * maingame = nullptr;
	}

	void Init(mainGame * gl)
	{
		maingame = gl;
	}

	void MousePassiveMove(int x, int y)
	{
		if (maingame != nullptr)
			maingame->MousePassiveMove(x, y);
	}

	void Display()
	{
		if (maingame != nullptr)
			maingame->Display();
	}

	void ProcessKeys(unsigned char key, int x, int y)
	{
		if (maingame != nullptr)
			maingame->ProcessKeys(key, x, y);
	}

	void ProcessSpecialKeys(int key, int x, int y)
	{
		if (maingame != nullptr)
			maingame->ProcessSpecialKeys(key, x, y);
	}

	void ChangeSize(int w, int h)
	{
		if (maingame != nullptr)
			maingame->ChangeSize(w, h);
	}
}