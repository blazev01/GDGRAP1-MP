#ifndef MODELS_PLAYER_HPP
#define MODELS_PLAYER_HPP

#include <glm/glm.hpp>

#include "Camera.hpp"
#include "Model3D.hpp"

namespace models {
	class Player {
	private:
		const float orbitSpeed = 0.01f;
		const float lookSpeed = 0.0002f;
		const float turnSpeed = 1.0f;
		const float moveSpeed = 0.05f;

		glm::vec3 F;

		bool isOrbitingRight;
		bool isOrbitingLeft;
		bool isLookingRight;
		bool isLookingLeft;
		bool isLookingUp;
		bool isLookingDown;
		bool isTurningRight;
		bool isTurningLeft;
		bool isMovingForward;
		bool isMovingBackward;

	public:
		Player(glm::vec3 position, glm::vec3 forward);

	public:
		void circle(Camera* Cam);
		void look(Camera* Cam);
		void turn(Model3D* Model);
		void move(Model3D* Model);

	private:
		void calcForward(float theta);
		
	public:
		bool getIsOrbitingRight();
		void setIsOrbitingRight(bool isOrbitingRight);

		bool getIsOrbitingLeft();
		void setIsOrbitingLeft(bool isOrbitingLeft);

		bool getIsLookingRight();
		void setIsLookingRight(bool isLookingRight);

		bool getIsLookingLeft();
		void setIsLookingLeft(bool isLookingLeft);

		bool getIsLookingUp();
		void setIsLookingUp(bool isLookingUp);

		bool getIsLookingDown();
		void setIsLookingDown(bool isLookingDown);

		bool getIsTurningRight();
		void setIsTurningRight(bool isTurningRight);

		bool getIsTurningLeft();
		void setIsTurningLeft(bool isTurningLeft);

		bool getIsMovingForward();
		void setIsMovingForward(bool isMovingForward);

		bool getIsMovingBackward();
		void setIsMovingBackward(bool isMovingBackward);
	};
}

#endif