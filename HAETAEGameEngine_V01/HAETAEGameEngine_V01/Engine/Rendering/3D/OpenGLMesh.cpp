#include "OpenGLMesh.h"

OpenGLMesh::OpenGLMesh(SubMesh subMesh_, GLuint shaderProgram_) : VAO(0), VBO(0), modelLoc(0), viewLoc(0), projLoc(0),
viewPositionLoc(0), lightPositionLoc(0), ambientLoc(0), diffuseLoc(0), colorLoc(0) {
	shaderProgram = shaderProgram_;
	subMesh = subMesh_;
	GenerateBuffers();

}

OpenGLMesh::~OpenGLMesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0) {
		subMesh.vertexList.clear();
	}

	if (subMesh.meshIndices.size() > 0) {
		subMesh.meshIndices.clear();
	}
}

void OpenGLMesh::Render(Camera* camera_, std::vector<BoundingBox> instances_) {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);

	glUniform3fv(viewPositionLoc, 1, glm::value_ptr(camera_->GetCameraPosition()));

	glUniform3fv(lightPositionLoc, 1, glm::value_ptr(camera_->GetLightSource().front()->GetPosition()));
	glUniform1fv(ambientLoc, 1, camera_->GetLightSource().front()->GetAmbient());
	glUniform1fv(diffuseLoc, 1, camera_->GetLightSource().front()->GetDiffuse());
	glUniform3fv(colorLoc, 1, glm::value_ptr(camera_->GetLightSource().front()->GetColor()));


	glUniform1i(MdiffuseMapLoc, 0);
	glUniform1fv(MshininessLoc, 1, &(subMesh.material.shininess));
	glUniform1fv(MtransparencyLoc, 1, &(subMesh.material.transparency));
	glUniform3fv(MambientLoc, 1, glm::value_ptr(subMesh.material.ambient));
	glUniform3fv(MdiffuseLoc, 1, glm::value_ptr(subMesh.material.diffuse));
	glUniform3fv(MspecularLoc, 1, glm::value_ptr(subMesh.material.specular));


	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glBindVertexArray(VAO);
	for (int i = 0; i < instances_.size(); i++) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i].transform));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size()); // glDrawElements can also work - just need indicies : not all of format supports that ex)OBJ
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLMesh::GenerateBuffers() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//Texture Coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	//Colour
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	//textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");

	viewPositionLoc = glGetUniformLocation(shaderProgram, "viewPosition");
	lightPositionLoc = glGetUniformLocation(shaderProgram, "lightSource.lightPosition");
	ambientLoc = glGetUniformLocation(shaderProgram, "lightSource.ambient");
	diffuseLoc = glGetUniformLocation(shaderProgram, "lightSource.diffuse");
	colorLoc = glGetUniformLocation(shaderProgram, "lightSource.lightColor");

	MdiffuseMapLoc = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	MshininessLoc = glGetUniformLocation(shaderProgram, "material.shininess");
	MtransparencyLoc = glGetUniformLocation(shaderProgram, "material.transparency");
	MambientLoc = glGetUniformLocation(shaderProgram, "material.ambient");
	MdiffuseLoc = glGetUniformLocation(shaderProgram, "material.diffuse");
	MspecularLoc = glGetUniformLocation(shaderProgram, "material.specular");


}