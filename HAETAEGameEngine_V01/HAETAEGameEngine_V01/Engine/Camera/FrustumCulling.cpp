#include "FrustumCulling.h"
#include <iostream>

FrustumCulling::FrustumCulling()
{

}

FrustumCulling::~FrustumCulling()
{
}

void FrustumCulling::SetFrustum(glm::vec3 p_, glm::vec3 forward_, glm::vec3 up_, glm::vec3 right_, float fov_, float ratio_, float nearDist_, float farDist_)
{
	Hnear = 2.0f * tan(fov_ / 2.0f) * nearDist_;
	Wnear = Hnear * ratio_;

	Hfar = 2.0f * tan(fov_ / 2.0f) * farDist_;
	Wfar = Hfar * ratio_;

	fc = p_ + forward_ * farDist_;

	ftl = fc + (up_ * Hfar / 2.0f) - (right_ * Wfar / 2.0f);
	ftr = fc + (up_ * Hfar / 2.0f) + (right_ * Wfar / 2.0f);
	fbl = fc - (up_ * Hfar / 2.0f) - (right_ * Wfar / 2.0f);
	fbr = fc - (up_ * Hfar / 2.0f) + (right_ * Wfar / 2.0f);

	nc = p_ + forward_ * nearDist_;

	ntl = nc + (up_ * Hnear / 2.0f) - (right_ * Wnear / 2.0f);
	ntr = nc + (up_ * Hnear / 2.0f) + (right_ * Wnear / 2.0f);
	nbl = nc - (up_ * Hnear / 2.0f) - (right_ * Wnear / 2.0f);
	nbr = nc - (up_ * Hnear / 2.0f) + (right_ * Wnear / 2.0f);
}

void FrustumCulling::UpdateFrustum(glm::vec3 p_, glm::vec3 forward_, glm::vec3 up_, glm::vec3 right_, float nearDist_, float farDist_)
{
	fc = p_ + forward_ * farDist_;

	ftl = fc + (up_ * Hfar / 2.0f) - (right_ * Wfar / 2.0f);
	ftr = fc + (up_ * Hfar / 2.0f) + (right_ * Wfar / 2.0f);
	fbl = fc - (up_ * Hfar / 2.0f) - (right_ * Wfar / 2.0f);
	fbr = fc - (up_ * Hfar / 2.0f) + (right_ * Wfar / 2.0f);

	nc = p_ + forward_ * nearDist_;

	ntl = nc + (up_ * Hnear / 2.0f) - (right_ * Wnear / 2.0f);
	ntr = nc + (up_ * Hnear / 2.0f) + (right_ * Wnear / 2.0f);
	nbl = nc - (up_ * Hnear / 2.0f) - (right_ * Wnear / 2.0f);
	nbr = nc - (up_ * Hnear / 2.0f) + (right_ * Wnear / 2.0f);

	pl[TOP].Set3Points(ntr, ntl, ftl);
	pl[BOTTOM].Set3Points(nbl, nbr, fbr);
	pl[LEFT].Set3Points(ntl, nbl, fbl);
	pl[RIGHT].Set3Points(nbr, ntr, fbr);
	pl[NEARP].Set3Points(ntl, ntr, nbr);
	pl[FARP].Set3Points(ftr, ftl, fbl);




}

int FrustumCulling::SphereFrustumCheck(glm::vec3& pos_, float radius)
{

	int result = INSIDE;
	float distance;

	for (int i = 0; i < 6; i++) {
		distance = pl[i].GetDistance(pos_);
		if (i == 3) {
		//	std::cout << pl[3].d << std::endl;
			//std::cout << distance << std::endl;
			//std::cout << pos_.x << " " << pos_.x << " " << pos_.y << " " << pos_.z << std::endl;
		}
		
		if (distance < -radius) {
			return OUTSIDE;
		}
		else if (distance < radius) {
			result = INTERSECT;
			
		}

	}
	return result;

}

