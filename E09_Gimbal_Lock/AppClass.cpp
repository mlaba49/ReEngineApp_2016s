#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Bobadilla, Alberto - Gimbal Lock");
	m_v4ClearColor = vector4(0.0f, 0.0f, 0.0f, 0.0f);
}
void AppClass::InitVariables(void)
{
	//Loading the model
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");

	//Set the axis of Steve visible
	m_pMeshMngr->SetVisibleAxis(true, "Steve");
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//My quaternions
	quaternion quatX = quaternion(cos(m_v3Orientation.x / 2), sin(m_v3Orientation.x / 2), 0, 0);
	quaternion quatX2 = quaternion(cos(m_v3Orientation.x / 2), -sin(m_v3Orientation.x / 2), 0, 0);
	quaternion quatY = quaternion(cos(m_v3Orientation.y / 2), 0, sin(m_v3Orientation.y / 2), 0);
	quaternion quatY2 = quaternion(cos(m_v3Orientation.y / 2), 0, -sin(m_v3Orientation.y / 2), 0);
	quaternion quatZ = quaternion(cos(m_v3Orientation.z / 2), 0, 0, sin(m_v3Orientation.z / 2));
	quaternion quatZ2 = quaternion(cos(m_v3Orientation.z / 2), 0, 0, -sin(m_v3Orientation.z / 2));

	//Rotation matrices
	matrix3 quatXMat = matrix3(1, 0, 0,
		0, 1 - 2 * sin(m_v3Orientation.x / 2) * sin(m_v3Orientation.x / 2), 2 * cos(m_v3Orientation.x / 2) * sin(m_v3Orientation.x / 2),
		0, 2 * cos(m_v3Orientation.x / 2) * sin(m_v3Orientation.x / 2), 1 - 2 * 2 * cos(m_v3Orientation.x / 2) * sin(m_v3Orientation.x / 2) * 2 * cos(m_v3Orientation.x / 2) * sin(m_v3Orientation.x / 2));
	matrix4 rotX = quatXMat * vector3(0, 0, 0) * quatX2;
	matrix4 rotY = quatY * vector3(0, 0, 0) * quatY2;
	matrix4 rotZ = quatZ * vector3(0, 0, 0) * quatZ2;

	//linear combination
	m_mToWorld = rotX * rotY * rotZ;

	//Setting the model matrix
	m_pMeshMngr->SetModelMatrix(m_mToWorld, "Steve");

	//Adding the instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("Steve");

	int nFPS = m_pSystem->GetFPS();
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("X:", REYELLOW);
	m_pMeshMngr->PrintLine(std::to_string(m_v3Orientation.x), RERED);
	m_pMeshMngr->Print("Y:", REYELLOW);
	m_pMeshMngr->PrintLine(std::to_string(m_v3Orientation.y), RERED);
	m_pMeshMngr->Print("Z:", REYELLOW);
	m_pMeshMngr->PrintLine(std::to_string(m_v3Orientation.z), RERED);

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
	m_pMeshMngr->Render(); //renders the list of meshes in the system.
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release();
}