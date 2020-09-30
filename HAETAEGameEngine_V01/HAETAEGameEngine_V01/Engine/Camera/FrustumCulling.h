#ifndef FRUSTUMCULLING_H
#define FRUSTUMCULLING_H

#include <glm/glm.hpp>
#include "../Math/Plane.h"

class FrustumCulling
{
public:

	static enum {OUTSIDE, INTERSECT, INSIDE};
	

	FrustumCulling();
	~FrustumCulling();

	void SetFrustum(glm::vec3 p_, glm::vec3 forward_, glm::vec3 up_, glm::vec3 right_, float fov_, float ratio_, float nearDist_, float farDist_);
	void UpdateFrustum(glm::vec3 p_, glm::vec3 forward_, glm::vec3 up_, glm::vec3 right_, float nearDist_, float farDist_);
	int SphereFrustumCheck(glm::vec3& pos_, float radius);

	glm::vec3 fc, nc, ntl, ntr, nbr, nbl, ftl, ftr, fbr, fbl;
private:

	enum {
		TOP = 0,
		BOTTOM,
		LEFT,
		RIGHT,
		NEARP,
		FARP

	};

	Plane pl[6];

	
	
	float Hnear, Wnear, Hfar, Wfar;


};

#endif