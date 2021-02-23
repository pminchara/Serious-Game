#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>

#include <glew.h>
#include<glfw3.h>

#include<glm.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>

#include"Vertex.h"

static std::vector<Vertex> loadOBJ(const char* file_name)
{
	//Vertex portions
	std::vector<glm::fvec3> vertex_positions;
	std::vector<glm::fvec2> vertex_texcoords;
	std::vector<glm::fvec3> vertex_normals;

	//face vectors
	std::vector<GLint> vertex_position_indices;
	std::vector<GLint> vertex_normal_indices;
	std::vector<GLint> vertex_texcoord_indices;

	//vertex array
	std::vector<Vertex> vertices;

	std::stringstream ss;
	std::ifstream in_file(file_name);
	std::string line = "";
	std::string prefix = "";
	glm::vec3 temp_vec3;
	glm::vec2 temp_vec2;
	GLint temp_glint;

	//file open error
	if (!in_file.is_open())
	{
		throw "Error::objloader::Could not open file";
	}

	//read one line at a time
	while (std::getline(in_file, line))
	{
		//get the prefix of the line
		ss.clear();
		ss.str(line);
		ss >> prefix;
		
		if (prefix == "#")
		{

		}
		else if (prefix == "o")
		{

		}
		else if (prefix == "s")
		{

		}
		else if (prefix == "use_mtl")
		{

		}
		else if (prefix == "v") // vertex position
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_positions.push_back(temp_vec3);
		}
		else if (prefix == "vt") // texture
		{
			ss >> temp_vec2.x >> temp_vec2.y;
			vertex_texcoords.push_back(temp_vec2);
		}
		else if (prefix == "vn")
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_normals.push_back(temp_vec3);
		}
		else if (prefix == "f")
		{
			int counter = 0;
			while (ss >> temp_glint)
			{
				if (counter == 0)
				{
					vertex_position_indices.push_back(temp_glint);
				}
				else if (counter == 1)
				{
					vertex_texcoord_indices.push_back(temp_glint);
				}
				else if (counter == 2)
				{
					vertex_normal_indices.push_back(temp_glint);
				}
				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}

				if (counter > 2)
					counter = 0;
			}
		}
		else
		{
		}
	}
	//build fianl vertex array (mesh)
	vertices.resize(vertex_position_indices.size(), Vertex());

	//load in all indices
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		vertices[i].position = vertex_positions[vertex_position_indices[i] - 1];
		vertices[i].texcoord = vertex_texcoords[vertex_texcoord_indices[i] - 1];
		vertices[i].normal = vertex_normals[vertex_normal_indices[i] - 1];
		vertices[i].color = glm::vec3(1.f, 1.f, 1.f);
	}

	//debug
	std::cout << "Nr of vertices: " << vertices.size() << "\n";

	//loaded sucess
	std::cout << "obj file loaded" << "\n";
	return vertices;

}