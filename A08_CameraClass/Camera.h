#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

class Camera {
public:
	Camera();
	~Camera();
	matrix4 GetView();
	matrix4 GetProjection(bool bOrtographic);
	void SetPosition(vector3 v3Position);
	void SetTarget(vector3 v3Target);
	void SetUp(vector3 v3Up);
	void MoveForward(float fIncrement);
	void MoveSideways(float fIncrement);
	void MoveVertical(float fIncrement);
	void ChangePitch(float fIncrement);
	void ChangeRoll(float fIncrement);
	void ChangeYaw(float fIncrement);
private:
};