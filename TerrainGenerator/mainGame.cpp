#pragma once
#define _USE_MATH_DEFINES
#include "mainGame.h"
#include "PerlinNoise.hpp"
#include <string>
#include <sstream>
#include <cmath>
#include <time.h>

mainGame::mainGame(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(15, 15);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Terrain Generator");

	GLUTCallbacks::Init(this);
	glutDisplayFunc(GLUTCallbacks::Display);
	glutReshapeFunc(GLUTCallbacks::ChangeSize);
	glutIdleFunc(GLUTCallbacks::Display);
	glutPassiveMotionFunc(GLUTCallbacks::MousePassiveMove);
	glutKeyboardFunc(GLUTCallbacks::ProcessKeys);
	glutSpecialFunc(GLUTCallbacks::ProcessSpecialKeys);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

	glutSetCursor(GLUT_CURSOR_NONE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	gluPerspective(90, 1.0, _closePlane, _farPlane);
	glMatrixMode(GL_MODELVIEW);

	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);

	_pointMap = new Vertex*[_mapSize];
	for (int i = 0; i < _mapSize; i++) 
	{
		_pointMap[i] = new Vertex[_mapSize]; 
	}
	
	CreateMap();

	_mainCamera = new Camera();
	_mainCamera->SetCameraPosition(
		(-_mapSize / 2) + 5,
		2.5f, 
		0.0f);
	_mainCamera->SetCameraRotationXAxis(45.0f);
	_mainCamera->SetCameraRotationYAxis(90.0f);

	_sub = new Basic_Submarine(_mapSize, _waterLevel, _pointMap);

	glutMainLoop();
}

mainGame::~mainGame()
{
	delete _mainCamera;
	_mainCamera = nullptr;

	for (int i = 0; i < _mapSize; i++)
	{
		delete[] _pointMap;
	}
	delete[] _pointMap;
}

void mainGame::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glRotatef(_mainCamera->GetCameraRotationXAxis(), 1.0f, 0.0f, 0.0f);
	glRotatef(_mainCamera->GetCameraRotationYAxis(), 0.0f, 1.0f, 0.0f);
	glTranslatef(-_mainCamera->GetCameraPosition('x'), -_mainCamera->GetCameraPosition('y'), -_mainCamera->GetCameraPosition('z'));

	DrawTerrain();
	_sub->Draw();

	glutSwapBuffers();
}

void mainGame::ChangeSize(int w, int h)
{
	if (h == 0) //Stops dividing by 0.
		h = 1;

	float ratio = 1.0F*w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(105, ratio, _closePlane, _farPlane);
	glMatrixMode(GL_MODELVIEW);
}

void mainGame::ProcessSpecialKeys(int key, int x, int y) 
{
	switch (key)
	{
		case GLUT_KEY_F1:
			exit(0);
			break;

		case GLUT_KEY_F2:
			glutFullScreenToggle();
			break;

		case GLUT_KEY_F3:
			_mouseEnabled = !_mouseEnabled;
			break;

		case GLUT_KEY_F5:
			CreateMap();
			_sub->UpdateSub();
			break;

		case GLUT_KEY_F4:
			Vector3 newposition;
			std::cout << "cam x" << std::endl;
			std::cin >> newposition.X;
			std::cout << "cam y" << std::endl;
			std::cin >> newposition.Y;
			std::cout << "cam z" << std::endl;
			std::cin >> newposition.Z;
			_mainCamera->SetCameraPosition(newposition);
			break;

		
	}
}

void mainGame::ProcessKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w': //Forward
			_mainCamera->SetCameraPosition(
				_mainCamera->GetCameraPosition('x') + _camMovementSpeed,
				_mainCamera->GetCameraPosition('y'),
				_mainCamera->GetCameraPosition('z'));
			break;

		case 's': //Back
			_mainCamera->SetCameraPosition(
				_mainCamera->GetCameraPosition('x') - _camMovementSpeed,
				_mainCamera->GetCameraPosition('y'),
				_mainCamera->GetCameraPosition('z'));
			break;

		case 'a': //Left
			_mainCamera->SetCameraPosition(
				_mainCamera->GetCameraPosition('x'),
				_mainCamera->GetCameraPosition('y'),
				_mainCamera->GetCameraPosition('z') + _camMovementSpeed);
			break;

		case 'd': //Right
			_mainCamera->SetCameraPosition(
				_mainCamera->GetCameraPosition('x'),
				_mainCamera->GetCameraPosition('y'),
				_mainCamera->GetCameraPosition('z') - _camMovementSpeed);
			break;

		case 'r': //Up
			_mainCamera->SetCameraPosition(
				_mainCamera->GetCameraPosition('x'),
				_mainCamera->GetCameraPosition('y') + _camMovementSpeed / 2,
				_mainCamera->GetCameraPosition('z'));
			break;

		case 'f': //Down
			_mainCamera->SetCameraPosition(
				_mainCamera->GetCameraPosition('x'),
				_mainCamera->GetCameraPosition('y') - _camMovementSpeed / 2,
				_mainCamera->GetCameraPosition('z'));
			break;

		case 'o':
			std::cout << _mainCamera->GetCameraPosition('x') << _mainCamera->GetCameraPosition('y') << _mainCamera->GetCameraPosition('z') << std::endl;
	}
}

void mainGame::MousePassiveMove(int x, int y)
{
	if (_mouseEnabled)
	{
		int _deltaMouseX = x - (glutGet(GLUT_WINDOW_WIDTH) / 2);
		int _deltaMouseY = y - (glutGet(GLUT_WINDOW_HEIGHT) / 2);

		if (_deltaMouseX != 0 && _deltaMouseY != 0)
		{
			_mainCamera->SetCameraRotationXAxis(_mainCamera->GetCameraRotationXAxis() + (_deltaMouseY / _mainCamera->GetSensitivity()));
			_mainCamera->SetCameraRotationYAxis(_mainCamera->GetCameraRotationYAxis() + (_deltaMouseX / _mainCamera->GetSensitivity()));

			//Up - Down
			if (_mainCamera->GetCameraRotationXAxis() < -90.0f)
			{
				_mainCamera->SetCameraRotationXAxis(-90.0f);
			}

			if (_mainCamera->GetCameraRotationXAxis() > 90.0f)
			{
				_mainCamera->SetCameraRotationXAxis(90.0f);
			}

			//Left - Right.
			if (_mainCamera->GetCameraRotationYAxis() < -180.0f)
			{
				_mainCamera->SetCameraRotationYAxis(_mainCamera->GetCameraRotationYAxis() + 360.0f);
			}

			if (_mainCamera->GetCameraRotationYAxis() > 180.0f)
			{
				_mainCamera->SetCameraRotationYAxis(_mainCamera->GetCameraRotationYAxis() - 360.0f);
			}

			glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		}
	}
}

void mainGame::CreateMap()
{
	double _frequency = 0.15;
	int _octaves = 512;

	float _xOff = _mapSize / 100 + 0.5;
	float _yOff = _mapSize / 100 - 0.5;

	siv::PerlinNoise* perlin = new siv::PerlinNoise();
	perlin->reseed(GetTimeSeed());
	
	for (int x = 0; x != _mapSize; x++)
	{
		for (int y = 0; y != _mapSize; y++)
		{
			_pointMap[x][y].X = (_mapSize / 10) * x;
			_pointMap[x][y].Y = (_mapSize / 8) * perlin->octaveNoise(_xOff, _yOff, _octaves);
			_pointMap[x][y].Z = (_mapSize / 10) * y;
			_yOff += 0.125 * (perlin->noise0_1(_yOff) / _frequency);
		}
		_xOff += 0.125 * (perlin->noise0_1(_xOff) / _frequency);
	}

	delete perlin;
	perlin = nullptr;
}

UINT32 mainGame::GetTimeSeed()
{
	UINT32 _timeSeed = time(NULL);
	return _timeSeed;
}

void mainGame::DrawTerrain()
{
	glPushMatrix();
	glTranslatef(-(_mapSize / 2), 0.0f, -(_mapSize / 2));

	for (int j = 0; j != _mapSize - 1; j++)
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i != _mapSize; i++)
		{
			glVertex3f(_pointMap[i][j].X, _pointMap[i][j].Y, _pointMap[i][j].Z);
			glVertex3f(_pointMap[i][j + 1].X, _pointMap[i][j + 1].Y, _pointMap[i][j + 1].Z);
		}
		glEnd();
	}
	
	for (int j = 0; j != _mapSize - 1; j++)
	{
		glPolygonMode(GL_FRONT, GL_FILL);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(0.0, 1.0);
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i != _mapSize; i++)
		{
			if (_pointMap[i][j].Y <= _waterLevel + 0.25f)
				glColor3f(0.3f, 0.2f, 0.2f);
			else
				glColor3f(0.2, 0.3f, 0.1f);
			glVertex3f(_pointMap[i][j].X, _pointMap[i][j].Y, _pointMap[i][j].Z);

			if (_pointMap[i][j + 1].Y <= _waterLevel + 0.25f)
				glColor3f(0.3f, 0.2f, 0.2f);
			else
				glColor3f(0.2, 0.3f, 0.1f);
			glVertex3f(_pointMap[i][j + 1].X, _pointMap[i][j + 1].Y, _pointMap[i][j + 1].Z);
		}
		glEnd();
		glDisable(GL_POLYGON_OFFSET_FILL);
	}

	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.5f, 0.9f);
	glVertex3f(_pointMap[_mapSize - 1][_mapSize - 1].X, _waterLevel, _pointMap[_mapSize - 1][_mapSize - 1].Z);
	glVertex3f(_pointMap[_mapSize - 1][_mapSize - 1].X, _waterLevel, _pointMap[0][0].Z);
	glVertex3f(_pointMap[0][0].X, _waterLevel, _pointMap[0][0].Z);
	glVertex3f(_pointMap[0][0].X, _waterLevel, _pointMap[_mapSize - 1][_mapSize - 1].Z);
	glEnd();
	glPopMatrix();
}