#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"
#include "../../Graphics//MaterialHandler.h"
#include "../../Math/BoundingBox.h"


struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 colour;
};

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<int> meshIndices;
	Material material;

};

class Mesh{
public:
	virtual void Render(Camera* camera_, std::vector<BoundingBox> instances_);

};

#endif // !MESH_H