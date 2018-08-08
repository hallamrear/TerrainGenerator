#pragma once
#include "mainGame.h"
#include "GLUTCallbacks.h"
#include "Commons.h"
#include "Camera.h"

#include "Basic_Submarine.h"

class mainGame
{
private:
	Vertex * * _pointMap;
	int _mapSize = 32;
	float _waterLevel = -0.25f;
	float _closePlane = 0.1f;
	float _farPlane = 100.0f;
	Camera * _mainCamera;
	float _camMovementSpeed = 0.5f;
	bool _mouseEnabled = true;

	Basic_Submarine * _sub;

public:

	mainGame(int argc, char* argv[]);
	~mainGame();
	
	void Display();
	void ChangeSize(int w, int h);
	void ProcessSpecialKeys(int key, int x, int y);
	void ProcessKeys(unsigned char key, int x, int y);
	void MousePassiveMove(int x, int y);

	UINT32 GetTimeSeed();
	void CreateMap();
	void DrawTerrain();

	int factorial(int n)
	{
		return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
	};
};