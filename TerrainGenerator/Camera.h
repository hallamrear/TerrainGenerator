#pragma once
#include "Commons.h"

class Camera
{
private:

	float toRads(const float &angleInDegrees)
	{
		return angleInDegrees * toRadiansModifier;
	};

	Vector3 _eye, _center, _up;
	float _cameraRotationYAxis;
	float _cameraRotationXAxis;
	float _cameraSensitivity;

public:

	
	Camera();

	Camera(Vector3 cameraEye, Vector3 cameraCenter);

	float ReturnEyeValue(char value);
	float ReturnCenterValue(char value);
	void SetCameraPosition(float x, float y, float z);
	void SetCameraPosition(Vector3 position);
	float GetCameraPosition(char value);
	void SetSensitivityToDefault();
	float GetSensitivity();
	void SetSensitivity(float Sensitivity);
	void IncreaseSensitivity();
	void DecreaseSensitivity();	
	float GetCameraRotationYAxis();
	void SetCameraRotationYAxis(float newAngle);
	float GetCameraRotationXAxis();
	void SetCameraRotationXAxis(float newAngle);
	
};


