#ifndef __LIGHT_H__
#include "utils.h"


class CLight
{
public:
	CLight();
	~CLight();

	void render();
private:
	GLuint m_program;
	glm::vec3 m_lightColor;
	glm::vec3 m_lightPos;
	glm::vec3 m_ambientColor;

	float m_lightSpecStr;
	float m_shininess;
	float m_ambientStrength;
	glm::vec3 m_lightColor;
	glm::vec3 m_lightPos;
	glm::vec3 m_ambientColor;

	float m_lightSpecStr;
	float m_shininess;
	float m_ambientStrength;
};
#endif // !__LIGHT_H__
