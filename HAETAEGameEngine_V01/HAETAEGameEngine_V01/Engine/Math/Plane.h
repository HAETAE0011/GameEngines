#ifndef PLANE_H
#define PLANE_H

#include <glm/glm.hpp>

class Plane
{
public:
	glm::vec3 normal, point;
	float d;

	Plane(glm::vec3 &v1_, glm::vec3& v2_, glm::vec3& v3_);
	Plane();
	~Plane();

	void Set3Points(glm::vec3& v1_, glm::vec3& v2_, glm::vec3& v3_);
	float GetDistance(glm::vec3& pos_);


};


#endif // !PLANE_H
