#ifndef MODELS_DIR_LIGHT_HPP
#define MODELS_DIR_LIGHT_HPP

#include "../Light.hpp"

namespace models {
	class DirLight : public Light {
	public:
		DirLight(glm::vec3 position);

	};
}

#endif