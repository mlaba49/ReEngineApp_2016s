#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

matrix4 Camera::GetView()
{
	return matrix4();
}

matrix4 Camera::GetProjection(bool bOrtographic)
{
	return matrix4();
}

void Camera::SetPosition(vector3 v3Position)
{
}

void Camera::SetTarget(vector3 v3Target)
{
}

void Camera::SetUp(vector3 v3Up)
{
}

void Camera::MoveForward(float fIncrement)
{
}

void Camera::MoveSideways(float fIncrement)
{
}

void Camera::MoveVertical(float fIncrement)
{
}

void Camera::ChangePitch(float fIncrement)
{
}

void Camera::ChangeRoll(float fIncrement)
{
}

void Camera::ChangeYaw(float fIncrement)
{
}
