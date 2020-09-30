#include "Plane.h"

Plane::Plane(glm::vec3& v1_, glm::vec3& v2_, glm::vec3& v3_)
{
	Set3Points(v1_, v2_, v3_);
}

Plane::Plane()
{
}

Plane::~Plane()
{
}

void Plane::Set3Points(glm::vec3& v1_, glm::vec3& v2_, glm::vec3& v3_)
{
	glm::vec3 aux1, aux2;
	
	aux1 = v1_ - v2_;
	aux2 = v3_ - v2_;

	normal = glm::cross(aux2, aux1);

	glm::normalize(normal);
	point = glm::vec3(v2_.x, v2_.y, v2_.z);
	d = -(glm::dot(normal, point));
	

}

float Plane::GetDistance(glm::vec3& pos_)
{
	return (d + glm::dot(normal, pos_));
}
