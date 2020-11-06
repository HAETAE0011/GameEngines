#ifndef OPENGLMESH
#define OPENGLMESH

#include "Mesh.h"

class OpenGLMesh : public Mesh
{
public:
	OpenGLMesh(SubMesh subMesh_, GLuint shaderProgram_);
	~OpenGLMesh();
	virtual void Render(Camera* camera_, std::vector<BoundingBox> instances_);
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


#endif // !1

