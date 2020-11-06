#include "Model.h"
#include "../../Core/CoreEngine.h"

Model::Model(const std::string& objFilePath_, const std::string& mtlFilePath_, GLuint shaderProgram_) : subMeshes(std::vector<Mesh*>()), shaderProgram(0) {
	subMeshes.reserve(10000);
	shaderProgram = shaderProgram_;
	//modelInstances.reserve(5);
	boxInstances.reserve(5);

	renderertype = CoreEngine::GetInstace()->GetRendererType();

	obj = new LoadOBJModel();
	obj->LoadModel(objFilePath_, mtlFilePath_);
	this->LoadModel();

}

Model::~Model(){
	if (subMeshes.size() > 0) {
		for (Mesh* m : subMeshes) {
			delete m;
			m = nullptr;
		}
	}
	if (boxInstances.size() > 0) {
		boxInstances.clear();
	}
}

void Model::Render(Camera* camera_){

	if (toRender) {
		for (Mesh* m : subMeshes) {
			m->Render(camera_, boxInstances);
		}
	}
}

void Model::AddMesh(Mesh* mesh_){
	subMeshes.push_back(mesh_);
}

int Model::createInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	boxInstances.push_back(BoundingBox(box.maxVert, box.minVert, GetTransform(position_, angle_, rotation_, scale_)));

	return boxInstances.size() - 1;
}

void Model::UpdateInstance(int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	boxInstances[index_] = BoundingBox(box.maxVert, box.minVert, GetTransform(position_, angle_, rotation_, scale_));
}

void Model::SetPosition(glm::vec3 position_)
{
	position = position_;
	//std::cout << position.x << position.y << position.z << std::endl;
}

glm::mat4 Model::GetTransform(int index_) const
{
	return boxInstances[index_].transform;
}

BoundingBox Model::GetBoundingBox()
{
	return box;
}

GLuint Model::GetShaderProgram() const
{
	return shaderProgram;
}

glm::mat4 Model::GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const
{

	glm::mat4 model;
	model = glm::translate(model, position_);
	model = glm::rotate(model, angle_, rotation_);
	model = glm::scale(model, scale_);
	return model;

}

void Model::LoadModel(){
	if (renderertype == Renderer::RENDERER_TYPE::OPENGL) {
		for (int i = 0; i < obj->GetSubMeshes().size(); i++) {
			subMeshes.push_back(new OpenGLMesh(obj->GetSubMeshes()[i], shaderProgram));
		}
	}
	else if (renderertype == Renderer::RENDERER_TYPE::VULKAN) {
		// do Vulkan things
	}
	

	box = obj->GetBoundingBox();
	fVector = obj->fVector;

	delete obj;
	obj = nullptr;
}



