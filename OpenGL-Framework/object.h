#pragma once
#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "utils.h"
#include "camera.h"
#include "MeshManager.h"

#include <string>

class CObject
{
public:

	//Program with shaders || Filepath for texture || Enum for the meshtype (MESH_2D_SPRITE,MESH_CUBE,MESH_SPHERE)
	CObject(GLuint &_program, std::string _imgFilepath, MeshType _meshtype);
	CObject();

	~CObject();

	//Currently defunct
	void Init(GLuint &_program, std::string _imgFilepath, MeshType _meshtype);

	void Render(CCamera* _pCamera);
	void Update();

	void ChangeTexture(glm::vec2 _texStartCoords, glm::vec2 _texEndCoords);

	void Translate(glm::vec3 _newPos);
	void Scale(glm::vec3 _scale);
	void Rotation(float _fDeg, glm::vec3 _rotAxis = glm::vec3(0.0f,0.0f,1.0f)) 
	{ 
		m_RotationDegrees = _fDeg;
		m_RotAxis = _rotAxis;
	}

	glm::vec3 GetPos() { return(m_objPosition); }
	glm::vec3 GetScale() { return(m_objScale); }
	float GetRot() { return(m_RotationDegrees); }

protected:
	GLuint m_program;
	//Translate
	glm::vec3 m_objPosition;
	//COORD m_objPixelPos;

	//Scale
	glm::vec3 m_objScale;

	//Rotation
	float m_RotationDegrees;
	glm::vec3 m_RotAxis;

	//Texture mapping
	glm::vec2 m_texStartScale;
	glm::vec2 m_texEndScale;

private:
	
	GLuint m_texture;

	

	//Mesh used
	MeshType m_MeshType;
};

#endif /*__SPRITE_H__*/