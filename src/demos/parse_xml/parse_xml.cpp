#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "../../dependencies/rapidxml/rapidxml.hpp"

using namespace std;
using namespace rapidxml;

char* fileToString(const char* fileName);

int main()
{
	// declare the document to be parsed
	// empty paramans for the template defaults to char
	xml_document<> doc;
	
	// load text from file
	char* text = fileToString("cell_test_entity.xml");
	
	cout << text << endl;
	
	// pass the text to be parsed
	// ( 0 means to use the default parse flags )
	doc.parse<0>(text);
	
	xml_node<> *root = doc.first_node("entity");
		
	xml_node<> *position = root->first_node("position");
		xml_node<> *x_attr = position->first_node("x");
		xml_node<> *y_attr = position->first_node("y");
		
	xml_node<> *graphics = root->first_node("graphics");
		xml_node<> *texture_attr = graphics->first_node("texture");
		xml_node<> *g_width_attr = graphics->first_node("width");
		xml_node<> *g_height_attr = graphics->first_node("height");
		
	string shape;
	float radius;
	float p_width, p_height;
	
	xml_node<> *physics = root->first_node("physics");
		xml_node<> *shape_attr = physics->first_node("shape");
		shape = string(shape_attr->value());
		if(shape == "box")
		{
			xml_node<> *p_width_attr = physics->first_node("width");
			p_width = atof(p_width_attr->value());
			xml_node<> *p_height_attr = physics->first_node("height");
			p_height = atof(p_width_attr->value());
		}
		else
		{
			xml_node<> *radius_attr = physics->first_node("radius");
			float radius = atof(radius_attr->value());
		}
		xml_node<> *mass_attr = physics->first_node("mass");
		float mass = atof(mass_attr->value());
		
	float x = atof(x_attr->value());
	float y = atof(y_attr->value());
	
	string texture(texture_attr->value());
	float g_width = atof(g_width_attr->value());
	float g_height = atof(g_height_attr->value());
	
	cout << " ENTITY " << endl;
	cout << "--------" << endl;
	
	cout << "Position: " << "(" << x << "," << y << ")" << endl;
	
	cout << "Texture: " << texture << endl;
	
	cout << "\tWidth: " << g_width << endl;
	
	cout << "\tHeight: " << g_height << endl;
	
	cout << "Shape: " << shape << endl;
	
	if(shape == "box")
	{
		cout << "\tWidth: " << p_width << endl;
		cout << "\tHeight: " << p_height << endl;
	}
	
	else
	{
		cout << "\tRadius: " << radius << endl;
	}
	
	cout << "\tMass: " << mass << endl;
	
	
	
	
}

char* fileToString(const char* fileName)
{
	
	fstream fs;
	fs.open(fileName, fstream::in);
	
	fs.seekg(0, fs.end);
	int length = fs.tellg();
	fs.seekg(0, fs.beg);
	
	char *buffer;
	buffer = new char[length+1];
	fs.read(buffer, length);
	buffer[length] = '\0';
	
	return buffer;
	
}
