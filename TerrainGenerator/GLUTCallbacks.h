#pragma once
class mainGame;

namespace GLUTCallbacks
{
	void Init(mainGame * gl);
	void Display();
	void ChangeSize(int w, int h);
	void ProcessSpecialKeys(int key, int x, int y);
	void ProcessKeys(unsigned char key, int x, int y);
	void MousePassiveMove(int x, int y);
};