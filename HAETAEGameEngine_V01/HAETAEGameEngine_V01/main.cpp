#include "Engine/Core/CoreEngine.h"
#include "Game/Game2.h"
#include "rapidxml.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace rapidxml;
using namespace std;

int main(int argc, char* argv[]) {

	//XML
	cout << "Capstone group" << endl;
	xml_document<> doc;
	xml_node<>* root;
	// Read the xml file into a vector
	ifstream file("./Resource/Test.xml");
	vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root = doc.first_node("ProjectManAtArms");
	// Iterate over the brewerys
	for (xml_node<>* brewery_node = root->first_node("Member"); brewery_node; brewery_node = brewery_node->next_sibling())
	{
		printf("member: %s living in %s. ",
			brewery_node->first_attribute("name")->value(),
			brewery_node->first_attribute("location")->value());
		// Interate over the beers
		for (xml_node<>* beer_node = brewery_node->first_node("role"); beer_node; beer_node = beer_node->next_sibling())
		{
			printf("for this project, I am %s, %s. ",
				beer_node->first_attribute("name")->value(),
				beer_node->first_attribute("description")->value());
			printf(beer_node->value());
		}
		cout << endl;
	}

	CoreEngine::GetInstace()->SetGameInterface(new Game2, Renderer::RENDERER_TYPE::OPENGL);

	if (!CoreEngine::GetInstace()->OnCreate("GAME ENGINE 4", 1000, 500)) {
		//std::cout << "Engine failed to be created" << std::endl;
		Debug::FatalError("Engine failed to be created", "main.cpp", __LINE__);
		return 0;
	}

	CoreEngine::GetInstace()->Run();

	return 0;
}
