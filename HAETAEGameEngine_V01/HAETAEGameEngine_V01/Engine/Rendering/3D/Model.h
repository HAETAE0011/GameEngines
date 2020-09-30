#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "LoadOBJModel.h"


class Model{
public:
	Model(const std::string& objFilePath_, const std::string& mtlFilePath_, GLuint shaderProgram_);
	~Model();
	void Render(Camera* camera_);
	void AddMesh(Mesh* mesh_);

	int createInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	void UpdateInstance(int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);

	void SetPosition(glm::vec3 position_);
	glm::mat4 GetTransform(int index_) const;
	//BoundingBox GetTransform(int index_) const;
	BoundingBox GetBoundingBox();
	GLuint GetShaderProgram() const;

	bool toRender = true;
	glm::vec3 fVector;

private:
	std::vector<Mesh*> subMeshes;
	GLuint shaderProgram;	
	//std::vector<glm::mat4> modelInstances; // change mat4 to boundingbox for frustrum culling
	std::vector<BoundingBox> boxInstances;
	LoadOBJModel* obj;


	BoundingBox box;
	glm::vec3 position;

	glm::mat4 GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const;
	void LoadModel();

	
};

#endif