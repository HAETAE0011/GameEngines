#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "..\FX\LightSource.h"
#include <vector>
#include "frustumCulling.h"

class Camera{
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);

	void AddLightSource(LightSource* light);
	std::vector<LightSource*> GetLightSource();

	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;
	glm::vec3 GetCameraPosition();
	glm::vec2 GetClippingPlanes() const;
	FrustumCulling GetFrustum();

	void ProcessMouseMovement(glm::vec2 offset_);
	void ProcessMouseZoom(int y_);

private:
	void UpdateCameraVector();
	void OnDestroy();

	glm::vec3 position;
	glm::mat4 perspective, orthographic;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;

	FrustumCulling frustum;


	std::vector<LightSource*> lights;
};
#endif