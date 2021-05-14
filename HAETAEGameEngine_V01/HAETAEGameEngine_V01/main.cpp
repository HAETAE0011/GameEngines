#include "Engine/Core/CoreEngine.h"
#include "Game/Game2.h"
#include "rapidxml.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace rapidxml;
using namespace std;

int main(int argc, char* argv[]) {

	////XML
	//cout << "Capstone group" << endl;
	//xml_document<> doc;
	//xml_node<>* root;
	//// Read the xml file into a vector
	//ifstream file("./Resource/Test.xml");

	//vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	//buffer.push_back('\0');

	//// Parse the buffer using the xml file parsing library into doc 
	//doc.parse<0>(&buffer[0]);

	////close file here
	//file.close();

	//// Find our root node
	//root = doc.first_node("ProjectManAtArms");
	//// Iterate over the members
	//for (xml_node<>* memeberNode = root->first_node("Member"); memeberNode; memeberNode = memeberNode->next_sibling())
	//{
	//	printf("member: %s living in %s. ", memeberNode->first_attribute("name")->value(), memeberNode->first_attribute("location")->value());

	//	//the jobs
	//	xml_node<>* job_node = memeberNode->first_node("role");
	//	printf("for this project, I am a %s, %s. ",	job_node->first_attribute("job")->value(), job_node->first_attribute("description")->value());
	//	printf(job_node->value());
	//	
	//	cout << endl;
	//}

	CoreEngine::GetInstace()->SetGameInterface(new Game2, Renderer::RENDERER_TYPE::OPENGL);

	if (!CoreEngine::GetInstace()->OnCreate("GAME ENGINE 4", 1000, 500)) {
		//std::cout << "Engine failed to be created" << std::endl;
		Debug::FatalError("Engine failed to be created", "main.cpp", __LINE__);
		return 0;
	}

	CoreEngine::GetInstace()->Run();

	return 0;
}
