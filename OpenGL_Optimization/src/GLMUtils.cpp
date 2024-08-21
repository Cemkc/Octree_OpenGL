#include "GLMUtils.h"
#include <sstream>

std::string printVector3(const glm::vec3& vec) {
	std::ostringstream result;
	result << vec.x << " " << vec.y << " " << vec.z << " " << std::endl;
	return result.str();
}

std::string printMatrix(const glm::mat4& matrix) {
	std::ostringstream result;
	for (unsigned int j = 0; j < 4; j++) {
		for (unsigned int i = 0; i < 4; i++) {
			result << " | " << matrix[i][j] << " | ";
		}
		result << std::endl;
	}
	return result.str();
}