#include "SpriteSurface.h"

SpriteSurface::SpriteSurface(std::string imageName_, glm::vec2 scale_, float angle_, glm::vec4 tintColour_, GLuint shaderProgram_) : VAO (0), VBO (0), modelLoc (0), projLoc (0), colourLoc (0), textureLoc (0)
{
	shaderProgram = shaderProgram_;

	/*vertexList.push_back(Vertex2D(glm::vec4(-0.5f, 0.5f, 0.0f, 0.0f)));
	vertexList.push_back(Vertex2D(glm::vec4(0.5f, 0.5f, 1.0f, 0.0f)));
	vertexList.push_back(Vertex2D(glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f)));
	vertexList.push_back(Vertex2D(glm::vec4(0.5f, -0.5f, 1.0f, 1.0f)));*/
	Vertex2D vertA;
	vertA.position = glm::vec2(-0.5f, 0.5f);
	vertA.texCoords = glm::vec2(0.0f, 0.0f);
	vertexList.push_back(vertA);

	Vertex2D vertB;
	vertB.position = glm::vec2(0.5f, 0.5f);
	vertB.texCoords = glm::vec2(1.0f, 0.0f);
	vertexList.push_back(vertB);

	Vertex2D vertC;
	vertC.position = glm::vec2(-0.5f, -0.5f);
	vertC.texCoords = glm::vec2(0.0f, 1.0f);
	vertexList.push_back(vertC);

	Vertex2D vertD;
	vertD.position = glm::vec2(0.5f, -0.5f);
	vertD.texCoords = glm::vec2(1.0f, 1.0f);
	vertexList.push_back(vertD);

	scale = scale_;
	angle = angle_;
	tintColour = tintColour_;

	

	textureID = LoadTexture(imageName_);

	width = TextureHandler::GetInstance()->GetTextureData(imageName_)->width;
	height = TextureHandler::GetInstance()->GetTextureData(imageName_)->height;

	GenerateBuffers();
}

SpriteSurface::~SpriteSurface()
{
	vertexList.clear();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void SpriteSurface::Draw(Camera* camera_, glm::vec2 position_)
{
	/*glUniform1d(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(position_.x, position_.y, 0.0f));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(width * scale.x, height * scale.y, 1.0f));

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetOrthographic()));

	glUniform4fv(colourLoc, 1 , glm::value_ptr(tintColour));
	glBindVertexArray(VAO);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);*/

	//texture
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position_.x, position_.y, 0.0f));
	model = glm::rotate(model, angle, glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(width * scale.x, height * scale.y, 1.0f));



	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetOrthographic()));
	glUniform4fv(colourLoc, 1, glm::value_ptr(glm::vec4(tintColour.r, tintColour.g, tintColour.b, tintColour.a)));

	glBindVertexArray(VAO);

	for (int i = 0; i < vertexList.size(); i++)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexList.size());
	}


	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	//std::cout << "working?" << std::endl;
}

float SpriteSurface::getWidth()
{
	return width;
}

float SpriteSurface::getHeight()
{
	return height;
}

GLuint SpriteSurface::LoadTexture(std::string filename_)
{
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(filename_);
	if (currentTexture == 0)
	{
		TextureHandler::GetInstance()->CreateTexture(filename_, "./Resource/GUI/" + filename_ + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(filename_);
	}
	return currentTexture;
}

void SpriteSurface::GenerateBuffers()
{
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex2D), &vertexList[0], GL_STATIC_DRAW);

	////position
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (GLvoid*)0);

	////texcoord
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (GLvoid*)offsetof(Vertex2D, texCoords));

	//glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//modelLoc = glGetUniformLocation(shaderProgram, "model");
	//projLoc = glGetUniformLocation(shaderProgram, "proj");
	//colourLoc = glGetUniformLocation(shaderProgram, "tintColour");
	//textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex2D), &vertexList[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (GLvoid*)0);

	//TEXTURECORDINATE
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (GLvoid*)offsetof(Vertex2D, texCoords));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	colourLoc = glGetUniformLocation(shaderProgram, "tintColour");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");
}
