#ifndef MODELS_PLAYER_HPP
#define MODELS_PLAYER_HPP

#include <glm/glm.hpp>

#include "Camera.hpp"
#include "Model3D.hpp"
#include "Light.hpp"

#include "Enum/ViewTag.hpp"


namespace models {
	class Player {
	private:
		const float orbitSpeed = 0.05f;
		const float lookSpeed = 0.05;
		const float turnSpeed = 2.0f;
		const float moveSpeed = 0.05f;

		float positionY = 0.0f;
		float velocityY = 0.25f;
		float jumpSpeed = 0.1f;
		float jumpTime = 0.1f;

		const float turnSpeedOffset = 0.00001f;
		const float camTurnOffset = 0.017454f;

		const float fpCamHeight = 1.5f;

		glm::vec3 position;
		glm::vec3 worldUp;

		glm::vec3 F;
		glm::vec3 R;
		glm::vec3 U;

		glm::mat4 orientation;

		ViewTag CurrentView;

		bool togglePersonView;
		bool toggleOverhead;
		bool isOrbitingRight;
		bool isOrbitingLeft;
		bool isOrbitingUp;
		bool isOrbitingDown;
		bool isLookingRight;
		bool isLookingLeft;
		bool isLookingUp;
		bool isLookingDown;
		bool isPanningRight;
		bool isPanningLeft;
		bool isPanningUp;
		bool isPanningDown;
		bool isTurningRight;
		bool isTurningLeft;
		bool isMovingForward;
		bool isMovingBackward;
		bool isJumping;

	public:
		Player(glm::vec3 position, glm::vec3 forward, ViewTag CurrentView);

	public:
		void swapView();
		void circle(Camera* Cam);
		void look(Camera* Cam);
		void pan(Camera* Cam);
		void turn(Model3D* Model, Light* FlashLight, Camera* Cam);
		void move(Model3D* Model, Light* FlashLight, Camera* ViewCam, Camera* TankCam);
		void jump(Model3D* Model, Light* FlashLight);

	private:
		glm::mat4 calcOrientation();
		void reorient(float theta, glm::vec3 axis);
		
	public:
		ViewTag getCurrentView();

		bool getTogglePersonView();
		void setTogglePersonView(bool togglePersonView);

		bool getToggleOverhead();
		void setToggleOverhead(bool toggleOverhead);

		bool getIsOrbitingRight();
		void setIsOrbitingRight(bool isOrbitingRight);

		bool getIsOrbitingLeft();
		void setIsOrbitingLeft(bool isOrbitingLeft);

		bool getIsOrbitingUp();
		void setIsOrbitingUp(bool isOrbitingUp);

		bool getIsOrbitingDown();
		void setIsOrbitingDown(bool isOrbitingDown);

		bool getIsLookingRight();
		void setIsLookingRight(bool isLookingRight);

		bool getIsLookingLeft();
		void setIsLookingLeft(bool isLookingLeft);

		bool getIsLookingUp();
		void setIsLookingUp(bool isLookingUp);

		bool getIsLookingDown();
		void setIsLookingDown(bool isLookingDown);

		bool getIsPanningRight();
		void setIsPanningRight(bool isPanningRight);

		bool getIsPanningLeft();
		void setIsPanningLeft(bool isPanningLeft);

		bool getIsPanningUp();
		void setIsPanningUp(bool isPanningUp);

		bool getIsPanningDown();
		void setIsPanningDown(bool isPanningDown);

		bool getIsTurningRight();
		void setIsTurningRight(bool isTurningRight);

		bool getIsTurningLeft();
		void setIsTurningLeft(bool isTurningLeft);

		bool getIsMovingForward();
		void setIsMovingForward(bool isMovingForward);

		bool getIsMovingBackward();
		void setIsMovingBackward(bool isMovingBackward);

		bool getIsJumping();
		void setIsJumping(bool isJumping);
	
	};
}

#endif