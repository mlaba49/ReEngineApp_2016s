#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here
	static DWORD timerSinceBoot = GetTickCount(); //Time since the computer boot
	DWORD timerSinceStart = GetTickCount() - timerSinceBoot; //Current time minus the boot time.
	float fTimer = timerSinceStart / 1000.0f; //Was in milliseconds, need it in seconds.

	m_pMeshMngr->PrintLine(""); //Print an empty line.
	m_pMeshMngr->PrintLine("Timer: " + std::to_string(fTimer)); //Print the timer.

	matrix4 m4SpherePosition;

	vector3 v3One = vector3(-4.0f, -2.0f, 5.0f);
	vector3 v3Two = vector3(1.0f, -2.0f, 5.0f);
	vector3 v3Three = vector3(-3.0f, -1.0f, 3.0f);
	vector3 v3Four = vector3(2.0f, -1.0f, 3.0f);
	vector3 v3Five = vector3(-2.0f, 0.0f, 0.0f);
	vector3 v3Six = vector3(3.0f, 0.0f, 0.0f);
	vector3 v3Seven = vector3(-1.0f, 1.0f, -3.0f);
	vector3 v3Eight = vector3(4.0f, 1.0f, -3.0f);
	vector3 v3Nine = vector3(0.0f, 2.0f, -5.0f);
	vector3 v3Ten = vector3(5.0f, 2.0f, -5.0f);
	vector3 v3Eleven = vector3(1.0f, 3.0f, -5.0f);

	float percentage = MapValue(fTimer, 0.0f, 0.25f, 0.0f, 1.0f);
	if (percentage >= 0.0f && percentage < 1.0f) {
		vector3 v3Current = glm::lerp(v3One, v3Two, percentage);
		matrix4 m4WallEye = glm::translate(v3Current);
		m_pMeshMngr->SetModelMatrix(m4WallEye, "WallEye");
	}
	if (percentage >= 1.0f && percentage < 2.0f) {
		vector3 v3Current = glm::lerp(v3Two, v3Three, percentage - 1.0f);
		matrix4 m4WallEye = glm::translate(v3Current);
		m_pMeshMngr->SetModelMatrix(m4WallEye, "WallEye");
	}
	if (percentage >= 2.0f && percentage < 3.0f) {
		vector3 v3Current = glm::lerp(v3Three, v3Four, percentage - 2.0f);
		matrix4 m4WallEye = glm::translate(v3Current);
		m_pMeshMngr->SetModelMatrix(m4WallEye, "WallEye");
	}
	if (percentage >= 3.0f && percentage < 4.0f) {
		vector3 v3Current = glm::lerp(v3Four, v3Five, percentage - 3.0f);
		matrix4 m4WallEye = glm::translate(v3Current);
		m_pMeshMngr->SetModelMatrix(m4WallEye, "WallEye");
	}
	if (percentage >= 4.0f && percentage < 5.0f) {
		vector3 v3Current = glm::lerp(v3Five, v3Six, percentage - 4.0f);
		matrix4 m4WallEye = glm::translate(v3Current);
		m_pMeshMngr->SetModelMatrix(m4WallEye, "WallEye");
	}
	if (percentage >= 5.0f && percentage < 6.0f) {
		vector3 v3Current = glm::lerp(v3Six, v3Seven, percentage - 5.0f);
		matrix4 m4WallEye = glm::translate(v3Current);
		m_pMeshMngr->SetModelMatrix(m4WallEye, "WallEye");
	}
	if (percentage >= 6.0f && percentage < 7.0f) {
		vector3 v3Current = glm::lerp(v3Seven, v3Eight, percentage - 6.0f);
		matrix4 m4WallEye = glm::translate(v3Current);
		m_pMeshMngr->SetModelMatrix(m4WallEye, "WallEye");
	}
	if (percentage >= 7.0f && percentage < 8.0f) {
		vector3 v3Current = glm::lerp(v3Eight, v3Nine, percentage - 7.0f);
		matrix4 m4WallEye = glm::translate(v3Current);
		m_pMeshMngr->SetModelMatrix(m4WallEye, "WallEye");
	}
	if (percentage >= 8.0f && percentage < 9.0f) {
		vector3 v3Current = glm::lerp(v3Nine, v3Ten, percentage - 8.0f);
		matrix4 m4WallEye = glm::translate(v3Current);
		m_pMeshMngr->SetModelMatrix(m4WallEye, "WallEye");
	}
	if (percentage >= 9.0f && percentage < 10.0f) {
		vector3 v3Current = glm::lerp(v3Ten, v3Eleven, percentage - 9.0f);
		matrix4 m4WallEye = glm::translate(v3Current);
		m_pMeshMngr->SetModelMatrix(m4WallEye, "WallEye");
	}
	if (percentage >= 10.0f && percentage < 11.0f) {
		vector3 v3Current = glm::lerp(v3Eleven, v3One, percentage - 10.0f);
		matrix4 m4WallEye = glm::translate(v3Current);
		m_pMeshMngr->SetModelMatrix(m4WallEye, "WallEye");
	}
	if (percentage >= 11.0f) percentage -= 11.0f;
	m_pMeshMngr->PrintLine("Percentage: " + std::to_string(percentage)); //Print the percentage.
#pragma endregion

#pragma region More Michael code to hold all the debug spheres
	m4SpherePosition = glm::translate(v3One) * glm::scale(vector3(0.1));
	m_pMeshMngr->AddSphereToRenderList(m4SpherePosition, REBLUE, SOLID);
	m4SpherePosition = glm::translate(v3Two) * glm::scale(vector3(0.1));
	m_pMeshMngr->AddSphereToRenderList(m4SpherePosition, REBLUE, SOLID);
	m4SpherePosition = glm::translate(v3Three) * glm::scale(vector3(0.1));
	m_pMeshMngr->AddSphereToRenderList(m4SpherePosition, REBLUE, SOLID);
	m4SpherePosition = glm::translate(v3Four) * glm::scale(vector3(0.1));
	m_pMeshMngr->AddSphereToRenderList(m4SpherePosition, REBLUE, SOLID);
	m4SpherePosition = glm::translate(v3Five) * glm::scale(vector3(0.1));
	m_pMeshMngr->AddSphereToRenderList(m4SpherePosition, REBLUE, SOLID);
	m4SpherePosition = glm::translate(v3Six) * glm::scale(vector3(0.1));
	m_pMeshMngr->AddSphereToRenderList(m4SpherePosition, REBLUE, SOLID);
	m4SpherePosition = glm::translate(v3Seven) * glm::scale(vector3(0.1));
	m_pMeshMngr->AddSphereToRenderList(m4SpherePosition, REBLUE, SOLID);
	m4SpherePosition = glm::translate(v3Eight) * glm::scale(vector3(0.1));
	m_pMeshMngr->AddSphereToRenderList(m4SpherePosition, REBLUE, SOLID);
	m4SpherePosition = glm::translate(v3Nine) * glm::scale(vector3(0.1));
	m_pMeshMngr->AddSphereToRenderList(m4SpherePosition, REBLUE, SOLID);
	m4SpherePosition = glm::translate(v3Ten) * glm::scale(vector3(0.1));
	m_pMeshMngr->AddSphereToRenderList(m4SpherePosition, REBLUE, SOLID);
	m4SpherePosition = glm::translate(v3Eleven) * glm::scale(vector3(0.1));
	m_pMeshMngr->AddSphereToRenderList(m4SpherePosition, REBLUE, SOLID);
#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->PrintLine(std::to_string(nFPS), RERED);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}