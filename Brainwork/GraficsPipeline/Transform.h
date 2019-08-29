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
	Matrix<float, 4, 4>			m_startDependencieMatrix;
	Matrix<float, 4, 4>			m_dependencieMatrix;
	Matrix<float, 4, 4>			m_localMatrix;

	Mobility					m_mobility = Mobility::m_moveable;
	Transform*					m_pParentTransform = nullptr;
	std::vector<Transform*>		m_childrenTransform;

	void						recalculateMatrix();

public:
	Transform		();
	Transform		(const Transform&) = default;
	~Transform		();

	Matrix<float, 4, 4>				getGlobalMatrix		();
	Matrix<float, 4, 4>				getLocalMatrix		();
	void							setLocalMatrix		(Matrix<float, 4, 4> localMatrix);

	void						setParent		(Transform* parentTransform);
	void						removeParent	();
	void						addChild		(Transform* childTransform);
	void						addChildren		(std::vector<Transform*>& childrenTransform);

	Mobility&					getMobility		();
	Transform*					getParent		();
	Transform*					getChild		(uint16_t index);
	std::vector<Transform*>&	getChildren		();

	void CleanUpTransform	();
};

