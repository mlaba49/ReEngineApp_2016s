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

	vector3 vectorList[11]; //Create a list of vector positions.
	vectorList[0] = (vector3(-4.0f, -2.0f, 5.0f)); //Create all eleven positions.
	vectorList[1] = vector3(1.0f, -2.0f, 5.0f);
	vectorList[2] = vector3(-3.0f, -1.0f, 3.0f);
	vectorList[3] = vector3(2.0f, -1.0f, 3.0f);
	vectorList[4] = vector3(-2.0f, 0.0f, 0.0f);
	vectorList[5] = vector3(3.0f, 0.0f, 0.0f);
	vectorList[6] = vector3(-1.0f, 1.0f, -3.0f);
	vectorList[7] = vector3(4.0f, 1.0f, -3.0f);
	vectorList[8] = vector3(0.0f, 2.0f, -5.0f);
	vectorList[9] = vector3(5.0f, 2.0f, -5.0f);
	vectorList[10] = vector3(1.0f, 3.0f, -5.0f);
	float percentage = MapValue(fTimer, 0.0f, 0.50f, 0.0f, 1.0f); //A percentage value of how far along the guy is.
	int perInt = floor(percentage); //This stuff makes it so that the code knows when to switch to a new target.
	int num = perInt % 11;
	int num2 = num + 1;
	while (num2 >= 11) num2 -= 11;
	int iteration = floor(percentage / 11); //The iteration number allows the guy to loop.
	vector3 v3Current = glm::lerp(vectorList[num], vectorList[num2], percentage - (11 * iteration) - num);
	matrix4 m4WallEye = glm::translate(v3Current);
	m_pMeshMngr->SetModelMatrix(m4WallEye, "WallEye");
	m_pMeshMngr->PrintLine("Percentage: " + std::to_string(percentage)); //Print the percentage.

	matrix4 m4SpherePosition; //Create a sphere position matrix.
	for (int i = 0; i < 11; i++) {
		m4SpherePosition = glm::translate(vectorList[i]) * glm::scale(vector3(0.1));
		m_pMeshMngr->AddSphereToRenderList(m4SpherePosition, REBLUE, SOLID); //Creates debug spheres for knowing where I'm supposed to be going.
	}
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