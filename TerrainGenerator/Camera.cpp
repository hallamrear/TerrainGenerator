#pragma once
#include "Camera.h"
#include "Commons.h"

Camera::Camera()
{
	_eye = Vector3(0.0f, 15.0f, 0.0f);
	_center = Vector3(0.0f, 0.0f, 1.0f);
	_up = universalUp;

	_cameraRotationYAxis = 0.0f;
	_cameraRotationXAxis = 0.0f;
	SetSensitivityToDefault();
};

Camera::Camera(Vector3 cameraEye, Vector3 cameraCenter)
{
	_eye = cameraEye;
	_center = cameraCenter;
	_up = universalUp;

	_cameraRotationYAxis = 0.0f;
	_cameraRotationXAxis = 0.0f;
	SetSensitivityToDefault();
};

//Pass in either X, Y or Z as a char to return it.
float Camera::ReturnEyeValue(char value)
{
	switch (value)
	{
	case 'x':
		return _eye.X;
		break;
	case 'y':
		return _eye.Y;
		break;
	case 'z':
		return _eye.Z;
		break;
	default:
		return 0.0f;
		break;
	}
};

//Pass in either X, Y or Z as a char to return it.
float Camera::ReturnCenterValue(char value)
{
	switch (value)
	{
	case 'x':
		return _center.X;
		break;
	case 'y':
		return _center.Y;
		break;
	case 'z':
		return _center.Z;
		break;
	default:
		return 0.0f;
		break;
	}
};

//Sets Camera Position
void Camera::SetCameraPosition(float X, float Y, float Z)
{
	_eye.X = X;
	_eye.Y = Y;
	_eye.Z = Z;
}

//Sets Camera Position (Vector3)
void Camera::SetCameraPosition(Vector3 position)
{
	_eye = position;
}

//Returns Camera Position
float Camera::GetCameraPosition(char value)
{
	switch (value)
	{
	case 'x':
		return _eye.X;
		break;
	case 'y':
		return _eye.Y;
		break;
	case 'z':
		return _eye.Z;
		break;
	default:
		return 0.0f;
		break;
	}
};

//Resets Camera sensitivity to Default (5.0f).
void Camera::SetSensitivityToDefault()
{
	_cameraSensitivity = 5.0f;
};

float Camera::GetSensitivity()
{
	return _cameraSensitivity;
};

//Set Camera Sensitivity to passed in float.
void Camera::SetSensitivity(float Sensitivity)
{
	_cameraSensitivity = Sensitivity;

	if (_cameraSensitivity <= 0.0f)
		_cameraSensitivity = 1.0f;

	std::cout << "Camera Sensitivity: " << _cameraSensitivity << std::endl;
};

//Increases sensitivity.
void Camera::IncreaseSensitivity()
{
	_cameraSensitivity -= 0.5f;

	if (_cameraSensitivity <= 0.0f)
		_cameraSensitivity = 0.5f;

	std::cout << "Camera Sensitivity: " << _cameraSensitivity << std::endl;
};

//Decreases sensitivity.
void Camera::DecreaseSensitivity()
{
	_cameraSensitivity += 0.5f;

	std::cout << "Camera Sensitivity: " << _cameraSensitivity << std::endl;
};

//Returns Camera Rotation around the Y axis.
float Camera::GetCameraRotationYAxis()
{
	return _cameraRotationYAxis;
};

//Sets Camera Rotation around the Y axis.
void Camera::SetCameraRotationYAxis(float newAngle)
{
	_cameraRotationYAxis = newAngle;
};

//Returns Camera Rotation around the X axis.
float Camera::GetCameraRotationXAxis()
{
	return _cameraRotationXAxis;
};

//Sets Camera Rotation around the X axis.
void Camera::SetCameraRotationXAxis(float newAngle)
{
	_cameraRotationXAxis = newAngle;
};
