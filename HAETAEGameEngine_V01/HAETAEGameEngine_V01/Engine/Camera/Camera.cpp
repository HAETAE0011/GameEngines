#include "Camera.h"

#include "../Core/CoreEngine.h"


Camera::Camera() : position(glm::vec3()){
	fieldOfView = 45.0f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 5000.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	frustum.SetFrustum(position, forward, up, right, fieldOfView, CoreEngine::GetInstace()->GetWindowSize().x / CoreEngine::GetInstace()->GetWindowSize().y, nearPlane, farPlane);

	

	perspective = glm::perspective(fieldOfView, CoreEngine::GetInstace()->GetWindowSize().x / CoreEngine::GetInstace()->GetWindowSize().y, nearPlane, farPlane);
	
	orthographic = glm::ortho(0.0f, CoreEngine::GetInstace()->GetWindowSize().x, 0.0f, CoreEngine::GetInstace()->GetWindowSize().y, -1.0f, 1.0f);

	UpdateCameraVector();

}

Camera::~Camera(){
	OnDestroy();
}

void Camera::SetPosition(glm::vec3 position_)
{
	position = position_;
	UpdateCameraVector();
}

void Camera::SetRotation(float yaw_, float pitch_)
{
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVector();
}

void Camera::AddLightSource(LightSource* light)
{
	lights.push_back(light);
}

std::vector<LightSource*> Camera::GetLightSource()
{
	return lights;
}

glm::mat4 Camera::GetView() const
{
	return glm::lookAt(position, position + forward, up);
}

glm::mat4 Camera::GetPerspective() const
{
	return perspective;
}

glm::mat4 Camera::GetOrthographic() const
{
	return orthographic;
}

glm::vec3 Camera::GetCameraPosition()
{
	return position;
}

glm::vec2 Camera::GetClippingPlanes() const
{
	return glm::vec2(nearPlane, farPlane);
}

FrustumCulling Camera::GetFrustum()
{
	return frustum;
}

void Camera::ProcessMouseMovement(glm::vec2 offset_)
{
	offset_ *= 0.05f;

	yaw += offset_.x;
	pitch += offset_.y;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	if (yaw < 0.0f) {
		yaw += 360.0f;
	}
	if (yaw > 360.0f) {
		yaw -= 360.0f;
	}



	UpdateCameraVector();
}

void Camera::ProcessMouseZoom(int y_)
{
	if (y_ < 0 || y_ > 0) {
		position += static_cast<float>(y_)* (forward * 2.0f);
	}
	UpdateCameraVector();
}


void Camera::UpdateCameraVector()
{

	frustum.UpdateFrustum(position, forward, up, right, nearPlane, farPlane);
	//std::cout << frustum.ftl.x << frustum.ftl.y << frustum.ftl.z << std::endl;

	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	
	forward = glm::normalize(forward);

	right = glm::normalize(glm::cross(forward, worldUp));

	up = glm::normalize(glm::cross(right, forward));



}

void Camera::OnDestroy(){
	if (lights.size() > 0) {
		for (LightSource* l : lights) {
			delete l;
			l = nullptr;
		}
	}
	

}
