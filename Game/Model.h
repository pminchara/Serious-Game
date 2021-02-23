#pragma once

#include"Mesh.h"
#include"Texture.h"
#include"Shader.h"
#include"Material.h"
#include"OBJLoader.h"

class Model
{
private:
	Material* material;
	Texture* overrideTextureDiffuse;
	Texture* overrideTextureSpecular;

	std::vector<Mesh*> meshes;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	void updateUniforms()
	{

	}


public:
	Model(glm::vec3 position, Material* material, Texture* overrideTextureDiffuse, Texture* overrideTextureSpecular,std::vector<Mesh*> meshes)
	{
		this->position = position;
		this->material = material;
		this->overrideTextureDiffuse = overrideTextureDiffuse;
		this->overrideTextureSpecular = overrideTextureSpecular;

		for (auto* i : meshes)
		{
			this->meshes.push_back(new Mesh(*i));
		}

		for (auto& i : this->meshes)
		{
			i->move(this->position);
			i->setOrigin(this->position);
		}
	}

	//obj file loaded model
	Model(glm::vec3 position, Material* material, Texture* overrideTextureDiffuse, Texture* overrideTextureSpecular, const char* objFile, glm::vec3 rotation, glm::vec3 scale)
	{
		this->position = position;
		this->material = material;
		this->overrideTextureDiffuse = overrideTextureDiffuse;
		this->overrideTextureSpecular = overrideTextureSpecular;
		this->rotation = rotation;
		this->scale = scale;

		std::vector<Vertex> mesh = loadOBJ(objFile);
		this->meshes.push_back(new Mesh(mesh.data(), mesh.size(), NULL, 0, glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.f), this->rotation, this->scale));

		for (auto& i : this->meshes)
		{
			i->move(this->position);
			i->setOrigin(this->position);
		}
	}

	~Model()
	{
		for (auto*& i : this->meshes)
		{
			delete i;
		}
	}

	//functions
	void rotate(const glm::vec3 rotation)
	{
		for (auto& i : this->meshes)
			i->rotate(rotation);
	}

	void update()
	{

	}
	void render(Shader* shader)
	{
		this->updateUniforms();

		//update uniforms 
		this->material->sendToShader(*shader);

		//use a program
		 shader->use();


		//draw
		for (auto& i : this->meshes)
		{
			//activate texture
			this->overrideTextureDiffuse->bind(0);
			this->overrideTextureSpecular->bind(1);
			i->render(shader);
		}

	}
};
