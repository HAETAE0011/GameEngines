#include "OpenGLParticle.h"

OpenGLParticle::OpenGLParticle(GLuint shaderProgram_, GLuint textureID_, std::string filename_) : position(glm::vec3(0.0f)), velocity(glm::vec3(0.0f)), angle(0), lifeTime(1.5f), scale(glm::vec2(1.0f, 1.0f)), 
colour(glm::vec3(1.0f)), VAO(0), VBO(0), modelLoc(0), projLoc(0), colourLoc(0), textureLoc(0)
{
	shaderProgram = shaderProgram_;
	textureID = textureID_;

	Vertex2D_P vertA;
	vertA.position = glm::vec2(-0.5f, 0.5f);
	vertA.texCoords = glm::vec2(0.0f, 0.0f);
	vertexList.push_back(vertA);

	Vertex2D_P vertB;
	vertB.position = glm::vec2(0.5f, 0.5f);
	vertB.texCoords = glm::vec2(1.0f, 0.0f);
	vertexList.push_back(vertB);

	Vertex2D_P vertC;
	vertC.position = glm::vec2(-0.5f, -0.5f);
	vertC.texCoords = glm::vec2(0.0f, 1.0f);
	vertexList.push_back(vertC);

	Vertex2D_P vertD;
	vertD.position = glm::vec2(0.5f, -0.5f);
	vertD.texCoords = glm::vec2(1.0f, 1.0f);
	vertexList.push_back(vertD);

	//textureID = LoadTexture(imageName_);

	width = TextureHandler::GetInstance()->GetTextureData(filename_)->width;
	height = TextureHandler::GetInstance()->GetTextureData(filename_)->height;
	std::cout << width << " " << height << std::endl;

	GenerateBuffers();

}

OpenGLParticle::~OpenGLParticle()
{
	vertexList.clear();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void OpenGLParticle::Render(Camera* camera_)
{
	//texture
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
	model = glm::rotate(model, angle, glm::vec3(0, 0, 1));

	// scale should use
	//	vec4 dist = view * model * vec4(pos, 1.0f);
	//	float len = length(vec3(dist.x, dist.y, dist.z));
	//	inversesqrt(0.1 * len)

	model = glm::scale(model, glm::vec3(width * scale.x, height * scale.y, 1.0f));

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	glUniform3fv(colourLoc, 1, glm::value_ptr(colour));
	glUniform3fv(posLoc, 1, glm::value_ptr(position));

	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexList.size());
	//std::cout << "drew " << vertexList[i].position.x << "," << vertexList[i].position.y << std::endl;


	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLParticle::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);

	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex2D_P), &vertexList[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D_P), (GLvoid*)0);

	//TEXTURECORDINATE
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D_P), (GLvoid*)offsetof(Vertex2D_P, texCoords));




	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	colourLoc = glGetUniformLocation(shaderProgram, "ParticleColour");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");
	posLoc = glGetUniformLocation(shaderProgram, "pos");
}

float OpenGLParticle::getWidth()
{
	return width;
}

float OpenGLParticle::getHeight()
{
	return height;
}
