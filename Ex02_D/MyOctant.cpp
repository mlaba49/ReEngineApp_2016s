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
	for (int i = 0; i < nObjectCont; i++) {
		MyBOClass* temp = m_pBOMngr->GetBoundingObject(i);
		sum += temp->GetCenterGlobal();
		//delete temp;
	}
	m_v3Position = sum / float(nObjectCont);
	std::cout << m_v3Position.x << ", " << m_v3Position.y << ", " << m_v3Position.z << std::endl;
	m_pMeshMngr->AddCubeToRenderList(glm::translate(m_v3Position) *
		glm::scale(vector3(5.0f)), REBLUE, WIRE);
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


