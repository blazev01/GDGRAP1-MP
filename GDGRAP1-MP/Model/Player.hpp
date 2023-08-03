#ifndef MODELS_PLAYER_HPP
#define MODELS_PLAYER_HPP

#include <glm/glm.hpp>

#include "Camera.hpp"
#include "Camera/PerspectiveCamera.hpp"
#include "Model3D.hpp"
#include "Light.hpp"

#include "Enum/ViewTag.hpp"


namespace models {
	class Player {
	private:
		const float orbitSpeed = 0.05f;
		const float lookSpeed = 0.05f;
		const float panSpeed = 0.5f;
		const float zoomSpeed = 1.0f;
		const float turnSpeed = 2.0f;
		const float moveSpeed = 0.05f;

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
		bool isZoomingOut;
		bool isZoomingIn;
		bool isPanningRight;
		bool isPanningLeft;
		bool isPanningUp;
		bool isPanningDown;
		bool isTurningRight;
		bool isTurningLeft;
		bool isMovingForward;
		bool isMovingBackward;

	public:
		Player(glm::vec3 position, glm::vec3 forward, ViewTag CurrentView);

	public:
		void swapView();
		void circle(Camera* Cam);
		void look(Camera* Cam);
		void pan(Camera* Cam);
		void zoom(PerspectiveCamera* Cam);
		void turn(Model3D* Model, Light* FlashLight, Camera* Cam);
		void move(Model3D* Model, Light* FlashLight, Camera* ViewCam, Camera* TankCam);

	private:
		glm::mat4 calcOrientation();
		void reorient(float theta, glm::vec3 axis);
		
	public:
		ViewTag getCurrentView();

		void setTogglePersonView(bool togglePersonView);
		void setToggleOverhead(bool toggleOverhead);
		void setIsOrbitingRight(bool isOrbitingRight);
		void setIsOrbitingLeft(bool isOrbitingLeft);
		void setIsOrbitingUp(bool isOrbitingUp);
		void setIsOrbitingDown(bool isOrbitingDown);
		void setIsLookingRight(bool isLookingRight);
		void setIsLookingLeft(bool isLookingLeft);
		void setIsLookingUp(bool isLookingUp);
		void setIsLookingDown(bool isLookingDown);
		void setIsZoomingOut(bool isZoomingOut);
		void setIsZoomingIn(bool isZoomingIn);
		void setIsPanningRight(bool isPanningRight);
		void setIsPanningLeft(bool isPanningLeft);
		void setIsPanningUp(bool isPanningUp);
		void setIsPanningDown(bool isPanningDown);
		void setIsTurningRight(bool isTurningRight);
		void setIsTurningLeft(bool isTurningLeft);
		void setIsMovingForward(bool isMovingForward);
		void setIsMovingBackward(bool isMovingBackward);
	
	};
}

#endif