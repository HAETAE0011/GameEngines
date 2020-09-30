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
	Mesh(SubMesh subMesh_, GLuint shaderProgram_);
	~Mesh();
	void Render(Camera* camera_, std::vector<BoundingBox> instances_);

private:
	void GenerateBuffers();

	SubMesh subMesh;

	GLuint VAO, VBO;
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, projLoc;
	//GLuint textureLoc;

	GLuint viewPositionLoc;
	GLuint lightPositionLoc;
	GLuint ambientLoc;
	GLuint diffuseLoc;
	GLuint colorLoc;

	GLuint MdiffuseMapLoc; //newmtl
	GLuint MshininessLoc; // Ns
	GLuint MtransparencyLoc; //d
	GLuint MambientLoc; //Ka
	GLuint MdiffuseLoc; //Kd
	GLuint MspecularLoc; //Ks
};

#endif // !MESH_H