#pragma once
#define REFRESHRATE 16
#include <Windows.h>
#include "GL\freeglut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>

struct Vertex
{
	float X;
	float Y;
	float Z;

	Vertex()
	{
		X = 0.0f;
		Y = 0.0f;
		Z = 0.0f;
	};

	Vertex(float floatX, float floatY, float floatZ)
	{
		X = floatX;
		Y = floatY;
		Z = floatZ;
	};
};

struct Vector3
{
	float X;
	float Y;
	float Z;

	Vector3()
	{
		X = 0.0f;
		Y = 0.0f;
		Z = 0.0f;
	};

	Vector3(float floatX, float floatY, float floatZ)
	{
		X = floatX;
		Y = floatY;
		Z = floatZ;
	};
};

const Vector3 universalUp = { 0.0f, 1.0f, 0.0f };
const Vector3 zeroVector = { 0.0f, 0.0f, 0.0f };
const float toRadiansModifier = 3.141592654f / 180.0f; // The value of degree in radians