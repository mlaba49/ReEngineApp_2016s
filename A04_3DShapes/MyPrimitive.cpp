#define _USE_MATH_DEFINES
#include <math.h>
#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyPrimitive::AddTriangle(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTop)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTop);
}
void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	vector3 topPoint(0, 0, a_fHeight); //Top of the cone
	float angle = (2 * M_PI) / a_nSubdivisions; //Angle of each subdivision
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTriangle(vector3(0, 0, 0), vector3(sin(i * angle), cos(i * angle), 0), vector3(sin((i + 1) * angle), cos((i + 1) * angle), 0)); //One triangle for the base of the cone...
		AddTriangle(vector3(sin(i * angle), cos(i * angle), 0), topPoint, vector3(sin((i + 1) * angle), cos((i + 1) * angle), 0)); //...and one for the sides.
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	
	float angle = (2 * M_PI) / a_nSubdivisions; //Angle of each subdivision
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTriangle(vector3(0, 0, 0), vector3(a_fRadius * sin(i * angle), a_fRadius * cos(i * angle), 0), vector3(a_fRadius * sin((i + 1) * angle), a_fRadius * cos((i + 1) * angle), 0)); //One triangle for the base of the cylinder...
		AddTriangle(vector3(0, 0, a_fHeight), vector3(a_fRadius * sin((i + 1) * angle), a_fRadius * cos((i + 1) * angle), a_fHeight), vector3(a_fRadius * sin(i * angle), a_fRadius * cos(i * angle), a_fHeight)); //...one for the top...
		AddQuad(vector3(a_fRadius * sin((i + 1) * angle), a_fRadius * cos((i + 1) * angle), 0), //...and a quad for the sides.
			vector3(a_fRadius * sin(i * angle), a_fRadius * cos(i * angle), 0),
			vector3(a_fRadius * sin((i + 1) * angle), a_fRadius * cos((i + 1) * angle), a_fHeight),
			vector3(a_fRadius * sin(i * angle), a_fRadius * cos(i * angle), a_fHeight));
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	
	float angle = (2 * M_PI) / a_nSubdivisions; //Angle of each subdivision
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddQuad(vector3(a_fOuterRadius * sin((i + 1) * angle), a_fOuterRadius * cos((i + 1) * angle), 0), //Add a quad for the outer sides...
			vector3(a_fOuterRadius * sin(i * angle), a_fOuterRadius * cos(i * angle), 0),
			vector3(a_fOuterRadius * sin((i + 1) * angle), a_fOuterRadius * cos((i + 1) * angle), a_fHeight),
			vector3(a_fOuterRadius * sin(i * angle), a_fOuterRadius * cos(i * angle), a_fHeight));
		AddQuad(vector3(a_fInnerRadius * sin(i * angle), a_fInnerRadius * cos(i * angle), 0), //...a quad for the inner sides...
			vector3(a_fInnerRadius * sin((i + 1) * angle), a_fInnerRadius * cos((i + 1) * angle), 0),
			vector3(a_fInnerRadius * sin(i * angle), a_fInnerRadius * cos(i * angle), a_fHeight), 
			vector3(a_fInnerRadius * sin((i + 1) * angle), a_fInnerRadius * cos((i + 1) * angle), a_fHeight));
		AddQuad(vector3(a_fOuterRadius * sin(i * angle), a_fOuterRadius * cos(i * angle), 0), //...a quad for the bottom...
			vector3(a_fOuterRadius * sin((i + 1) * angle), a_fOuterRadius * cos((i + 1) * angle), 0),
			vector3(a_fInnerRadius * sin(i * angle), a_fInnerRadius * cos(i * angle), 0), 
			vector3(a_fInnerRadius * sin((i + 1) * angle), a_fInnerRadius * cos((i + 1) * angle), 0));
		AddQuad(vector3(a_fOuterRadius * sin((i + 1) * angle), a_fOuterRadius * cos((i + 1) * angle), a_fHeight), //...and a quad for the top.
			vector3(a_fOuterRadius * sin(i * angle), a_fOuterRadius * cos(i * angle), a_fHeight),
			vector3(a_fInnerRadius * sin((i + 1) * angle), a_fInnerRadius * cos((i + 1) * angle), a_fHeight),
			vector3(a_fInnerRadius * sin(i * angle), a_fInnerRadius * cos(i * angle), a_fHeight));
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	//Your code starts here
	
	float angle = (2 * M_PI) / a_nSubdivisions; //Angle of each subdivision
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		for (int j = 0; j < a_nSubdivisions; j++)
		{
			AddQuad(vector3(cos(j * angle) * cos((i + 1) * angle), sin(j * angle) * cos((i + 1) * angle), sin((i + 1) * angle)),
				vector3(cos(j * angle) * cos(i * angle), sin(j * angle) * cos(i * angle), sin(i * angle)),
				vector3(cos((j + 1) * angle) * cos((i + 1) * angle), sin((j + 1) * angle) * cos((i + 1) * angle), sin((i + 1) * angle)),
				vector3(cos((j + 1) * angle) * cos(i * angle), sin((j + 1) * angle) * cos(i * angle), sin(i * angle)));

			//Alternate failed solution
			/*AddQuad(vector3(sin((i + 1) * angle), cos((i + 1) * angle), 0),
				vector3(sin(i * angle), cos(i * angle), 0),
				vector3(sin((i + 1) * angle), cos((i + 1) * angle), 1),
				vector3(sin(i * angle), cos(i * angle), 1));
			AddQuad(vector3(sin(j * angle), -.5, cos(j * angle) + .5),
				vector3(sin((j + 1) * angle), -.5, cos((j + 1) * angle) + .5),
				vector3(sin(j * angle), .5, cos(j * angle) + .5),
				vector3(sin((j + 1) * angle), .5, cos((j + 1) * angle) + .5));
			AddTriangle(vector3(sin((i + 1) * angle), cos((i + 1) * angle), 1),
				vector3(sin(i * angle), cos(i * angle), 1), 
				vector3(sin(j * angle), -.5, cos(j * angle) + .5));
			AddTriangle(vector3(sin((i + 1) * angle), cos((i + 1) * angle), 0),
				vector3(sin(i * angle), cos(i * angle), 0),
				vector3(sin(j * angle), -.5, cos(j * angle) + .5));*/
		}
	}

	//Your code ends here
	CompileObject(a_v3Color);
}