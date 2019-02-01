#include "pch.h"
#include "window.h"
#include "maths.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../entity/camera.h"

namespace FSEngine {

glm::mat4 GenerateOrthoMat(const Camera *cam, const Window &window)
{
	glm::mat4 projMat = glm::ortho(0.0f, (float)(window.getWidth()), 0.0f, (float)(window.getHeight()), -5.0f, 5.0f);
	projMat = glm::translate(projMat, glm::vec3(-cam->getPosition(), 1.0));
	return projMat;	
}

glm::mat4 GenerateTransformationMatrix(const glm::vec2 &position, const glm::vec2 &scale, const glm::vec2 &rot)
{
	glm::mat4 matrix(1);
	matrix = glm::translate(matrix, glm::vec3(position.x, position.y, 0.0));
	matrix = glm::rotate(matrix, rot.x, glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, rot.y, glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, glm::vec3(scale, 1));
	return matrix;
}

}