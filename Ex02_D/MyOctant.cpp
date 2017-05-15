#include "MyOctant.h"
using namespace ReEng;
//  MyOctant
void MyOctant::Init(void)
{
	m_v3Position = vector3(0.0f);
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_fSize = 0.0f;
	m_pBOMngr = MyBOManager::GetInstance();

	int nObjectCont = m_pBOMngr->GetObjectCount();
	//YOUR CODE GOES HERE
	vector3 sum = vector3(0.0f);
	vector3 min = vector3(0.0f);
	vector3 max = vector3(0.0f);
	for (int i = 0; i < nObjectCont; i++) {
		MyBOClass* temp = m_pBOMngr->GetBoundingObject(i);
		sum += temp->GetCenterGlobal();
		if (min.x > temp->GetMinG().x) min.x = temp->GetMinG().x;
		else if (max.x < temp->GetMaxG().x) max.x = temp->GetMaxG().x;
		if (min.y > temp->GetMinG().y) min.y = temp->GetMinG().y;
		else if (max.y < temp->GetMaxG().y) max.y = temp->GetMaxG().y;
		if (min.z > temp->GetMinG().z) min.z = temp->GetMinG().z;
		else if (max.z < temp->GetMaxG().z) max.z = temp->GetMaxG().z;
		temp = nullptr;
	}
	m_v3Position = sum / float(nObjectCont);
	m_fSize = max.x - min.x;
	if (m_fSize < (max.y - min.y)) m_fSize = max.y - min.y;
	if (m_fSize < (max.z - min.z)) m_fSize = max.z - min.z;
	m_fSize += 5.0f;
	
	Display();
}
void MyOctant::Release(void)
{
}
//The big 3
MyOctant::MyOctant(){Init();}
MyOctant::~MyOctant(){Release();};

void MyOctant::Display(void)
{
	m_pMeshMngr->AddCubeToRenderList(glm::translate(m_v3Position) * glm::scale(vector3(m_fSize)), REPURPLE, WIRE);
}


