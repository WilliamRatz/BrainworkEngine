#pragma once
#include "VK_inc.h"

class GameObject;

enum Mobility
{
	m_moveable,
	m_static
};

class Transform
{
private:
	Matrix<float, 4, 4>			m_globalMatrix;
	Matrix<float, 4, 4>			m_localMatrix;

	Mobility					m_mobility = Mobility::m_moveable;
	GameObject*					m_pParentObject = NULL;
	std::vector<GameObject>		m_children;

	Matrix<float, 4, 4>			recalculateMatrix();

public:
	Transform		();
	Transform		(const Transform&);
	~Transform		();

	Matrix<float, 4, 4>			getGlobalMatrix		();
	Matrix<float, 4, 4>			getLocalMatrix		();
	Matrix<float, 4, 4>&		getLocalMatrixRef	();

	void						setParent		(GameObject* parentObject);
	void						addChild		(GameObject& childObject);
	void						addChildren		(std::vector<GameObject>& childrenObject);

	Mobility&					getMobility		();
	GameObject*					getParent		();
	GameObject&					getChild		(uint16_t index);
	std::vector<GameObject>&	getChildren		();

	void CleanUpTransform	();
};

