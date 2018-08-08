#pragma once
#include "mainGame.h"
#include "GLUTCallbacks.h"
#include "Commons.h"

#include <time.h>

class Basic_Submarine
{
private:
	Vector3 subPos;
	int _mapSize;
	float _waterLevel;
	Vertex ** PointMapReference;

public:

	Basic_Submarine(int MAPSIZE, float WATERLEVEL, Vertex ** PointMapRef)
	{
		_mapSize = MAPSIZE;
		_waterLevel = WATERLEVEL;
		PointMapReference = PointMapRef;

		UpdateSub();
	}

	void UpdateSub()
	{
		srand(time(0));
		int posNo = (rand() % (_mapSize * _mapSize) / 4) + 1;
		
		int posCount = 0;
		bool breakOut = false;

		for (int j = 0; j != _mapSize - 1; j++)
		{
			for (int i = 0; i != _mapSize; i++)
			{
				if (PointMapReference[i][j].Y < _waterLevel && PointMapReference[i][j + 1].Y < _waterLevel  && PointMapReference[i][j - 1].Y)
				{
					subPos.X = PointMapReference[i][j].X;
					subPos.Y = _waterLevel;
					subPos.Z = PointMapReference[i][j].Z;

					if (i == _mapSize || j == _mapSize - 1)
					{
						posCount--;
						posCount--;
					}

					if (posCount >= posNo)
						breakOut = true;
					else
						posCount++;
				}

				if (breakOut)
					break;
			}
			if (breakOut)
				break;
		}
	}

	void Draw()
	{
	

		glPushMatrix();
		glPolygonMode(GL_FRONT, GL_FILL);
		glTranslatef(-(_mapSize / 2), 0.0f, -(_mapSize / 2));
		glTranslatef(subPos.X, subPos.Y, subPos.Z);
		glColor3f(0.2f, 0.2f, 0.9f);
		glutSolidCylinder(0.25f, 1.0f, 35, 35);
		glTranslatef(0.0f, 0.0f, 1.0f);
		glutSolidSphere(0.25f, 35, 35);
		glTranslatef(0.0f, 0.0f, -1.0f);
		glutSolidSphere(0.25f, 35, 35);
		glTranslatef(0.0f, 0.25f, 0.5f);
		glutSolidCube(0.25);
		glTranslatef(0.0f, 0.3f, 0.05f);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glutSolidCylinder(0.075f / 2, 0.35f / 2, 35, 35);
		glutSolidSphere(0.075f / 2, 35, 35);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glutSolidCylinder(0.075f / 2, 0.125f/ 2, 35, 35);
		glPopMatrix();

		glPushMatrix();
		glLineWidth(2.0);
		glPolygonMode(GL_FRONT, GL_LINE);
		glEnable(GL_POLYGON_OFFSET_LINE);
		glPolygonOffset(1.0, 1.0);
		glTranslatef(-(_mapSize / 2), 0.0f, -(_mapSize / 2));
		glTranslatef(subPos.X, subPos.Y, subPos.Z);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCylinder(0.25f, 1.0f, 35, 35);
		glTranslatef(0.0f, 0.0f, 1.0f);
		glutWireSphere(0.25f, 35, 35);
		glTranslatef(0.0f, 0.0f, -1.0f);
		glutWireSphere(0.25f, 35, 35);
		glTranslatef(0.0f, 0.25f, 0.5f);
		glutWireCube(0.25);
		glTranslatef(0.0f, 0.3f, 0.05f);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glutWireCylinder(0.075f / 2, 0.35f / 2, 35, 35);
		glutWireSphere(0.075f / 2, 35, 35);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glutWireCylinder(0.075f / 2, 0.125f / 2, 35, 35);
		glDisable(GL_POLYGON_OFFSET_LINE);
		glLineWidth(1.0);
		glPopMatrix();
	}	
};

