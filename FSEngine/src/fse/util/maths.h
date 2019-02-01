#pragma once

namespace FSEngine {

class Camera;

extern FSDLL glm::mat4 GenerateOrthoMat(const Camera *cam, const Window &window);
extern FSDLL glm::mat4 GenerateTransformationMatrix(const glm::vec2 &position, const glm::vec2 &scale, const glm::vec2 &rot);

}