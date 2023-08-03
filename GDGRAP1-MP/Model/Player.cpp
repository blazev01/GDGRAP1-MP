#include "Player.hpp"

using namespace models;

// @brief The constructor of the Player class.
// @param position - The position of the player
// @param forward - Initial forward direction of the player
Player::Player(glm::vec3 position, glm::vec3 forward, ViewTag CurrentView) {
	this->position = position;
	this->worldUp = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f));
	this->F = glm::normalize(forward);
	this->orientation = this->calcOrientation();
	this->CurrentView = CurrentView;

	this->togglePersonView = false;
	this->toggleOverhead = false;
	this->isOrbitingRight = false;
	this->isOrbitingLeft = false;
	this->isOrbitingUp = false;
	this->isOrbitingDown = false;
	this->isLookingRight = false;
	this->isLookingLeft = false;
	this->isLookingUp = false;
	this->isLookingDown = false;
	this->isTurningRight = false;
	this->isTurningLeft = false;
	this->isMovingForward = false;
	this->isMovingBackward = false;
}

void Player::swapView() {
	if (this->togglePersonView) {
		this->togglePersonView = false;
		if (this->CurrentView != ViewTag::THIRD_PERSON) {
			this->CurrentView = ViewTag::THIRD_PERSON;
		}
		else if (this->CurrentView != ViewTag::FIRST_PERSON) {
			this->CurrentView = ViewTag::FIRST_PERSON;
		}
	}
	else if (this->toggleOverhead) {
		this->toggleOverhead = false;
		if (this->CurrentView != ViewTag::OVERHEAD) {
			this->CurrentView = ViewTag::OVERHEAD;
		}
	}
}

// @brief Orbits the camera around the player.
// @param Cam - Pointer to the Camera class, denotes the current camera of the application
void Player::circle(Camera* Cam) {
	if (this->isOrbitingRight) {
		this->isOrbitingRight = false;
		Cam->orbit(this->orbitSpeed, 0.0f, 1.0f, 0.0f);
	}
	else if (this->isOrbitingLeft) {
		this->isOrbitingLeft = false;
		Cam->orbit(-this->orbitSpeed, 0.0f, 1.0f, 0.0f);
	}
	if (this->isOrbitingUp) {
		this->isOrbitingUp = false;
		if (Cam->getPosition().y < Cam->getCenterDistance() - 1.0f)
		Cam->orbit(this->orbitSpeed, 1.0f, 0.0f, 0.0f);
	}
	else if (this->isOrbitingDown) {
		this->isOrbitingDown = false;
		if (Cam->getPosition().y > 0.5f)
		Cam->orbit(-this->orbitSpeed, 1.0f, 0.0f, 0.0f);
	}

	if (Cam->getPosition().y <= 0.0f) {
		Cam->setPosition(glm::vec3(Cam->getPosition().x, 0.00f, Cam->getPosition().z));
	}
}

// @brief Tilts the camera to where the player is looking at.
// @param Cam - Pointer to the Camera class, denotes the current camera of the application
void Player::look(Camera* Cam) {
	if (this->isLookingRight) {
		this->isLookingRight = false;
		Cam->tilt(this->lookSpeed, 0.0f, 1.0f, 0.0f);
	}
	else if (this->isLookingLeft) {
		this->isLookingLeft = false;
		Cam->tilt(-this->lookSpeed, 0.0f, 1.0f, 0.0f);
	}

	if (this->isLookingUp) {
		this->isLookingUp = false;
		Cam->tilt(this->lookSpeed, 1.0f, 0.0f, 0.0f);
	}
	else if (this->isLookingDown) {
		this->isLookingDown = false;
		Cam->tilt(-this->lookSpeed, 1.0f, 0.0f, 0.0f);
	}
}

// @brief Rotates the player on its own vertical axis should they turn.
// @param Model - Pointer to the Model3D class, pertains to the player's model on the application
void Player::turn(Model3D* Model, Light* FlashLight, Camera* Cam) {
	if (this->isTurningRight) {
		this->isTurningRight = false;
		this->reorient(this->turnSpeed * this->turnSpeedOffset, glm::vec3(0.0f, 1.0f, 0.0f));
		Model->rotate(-this->turnSpeed, 0.0f, 1.0f, 0.0f);
		Cam->tilt(this->turnSpeed * this->camTurnOffset, 0.0f, 1.0f, 0.0f);
		FlashLight->setPosition(Cam->getCenter());
	}
	else if (this->isTurningLeft) {
		this->isTurningLeft = false;
		this->reorient(-this->turnSpeed * this->turnSpeedOffset, glm::vec3(0.0f, 1.0f, 0.0f));
		Model->rotate(this->turnSpeed, 0.0f, 1.0f, 0.0f);
		Cam->tilt(-this->turnSpeed * this->camTurnOffset, 0.0f, 1.0f, 0.0f);
		FlashLight->setPosition(Cam->getCenter());
	}
}

// @brief Translates the model forward/backward should the player move.
// @param Model - Pointer to the Model3D class, pertains to the player's model on the application
void Player::move(Model3D* Model, Light* FlashLight, Camera* ViewCam, Camera* TankCam) {
	if (this->isMovingForward || this->isMovingBackward) {
		glm::vec3 velocity = glm::vec3(0.0f);
		if (this->isMovingForward) {
			this->isMovingForward = false;
			velocity = glm::vec3(this->F * this->moveSpeed);
		}
		else if (this->isMovingBackward) {
			this->isMovingBackward = false;
			velocity = glm::vec3(this->F * -this->moveSpeed);
		}
		glm::vec3 camPos = Model->getPosition();
		camPos.y += this->fpCamHeight;

		Model->translate(velocity);
		ViewCam->movePositionWithCenter(camPos);
		TankCam->moveCenterWithPosition(camPos);
		FlashLight->setPosition(TankCam->getCenter());
	}
}

// @brief Calculates the new forward direction of the player camera after turning at a given angle.
// @param theta - The angle (in radians) by which the camera had tilted
glm::mat4 Player::calcOrientation() {
	this->R = glm::normalize(glm::cross(this->F, this->worldUp));
	this->U = glm::normalize(glm::cross(this->R, this->F));

	glm::mat4 orientation = glm::mat4(1.0f);

	orientation[0][0] = this->R.x;
	orientation[1][0] = this->R.y;
	orientation[2][0] = this->R.z;

	orientation[0][1] = this->U.x;
	orientation[1][1] = this->U.y;
	orientation[2][1] = this->U.z;

	orientation[0][2] = -this->F.x;
	orientation[1][2] = -this->F.y;
	orientation[2][2] = -this->F.z;

	return orientation;
}

void Player::reorient(float theta, glm::vec3 axis) {
	if (axis.x) this->orientation = glm::rotate(this->orientation, theta, this->R);
	if (axis.y) this->orientation = glm::rotate(this->orientation, theta, this->U);
	if (axis.z) this->orientation = glm::rotate(this->orientation, theta, this->F);

	this->R.x = this->orientation[0][0];
	this->R.y = this->orientation[1][0];
	this->R.z = this->orientation[2][0];

	this->U.x = this->orientation[0][1];
	this->U.y = this->orientation[1][1];
	this->U.z = this->orientation[2][1];

	this->F.x = -this->orientation[0][2];
	this->F.y = -this->orientation[1][2];
	this->F.z = -this->orientation[2][2];
}

ViewTag Player::getCurrentView() {
	return this->CurrentView;
}

bool Player::getTogglePersonView() {
	return this->togglePersonView;
}

void Player::setTogglePersonView(bool togglePersonView) {
	this->togglePersonView = togglePersonView;
}

bool Player::getToggleOverhead() {
	return this->toggleOverhead;
}

void Player::setToggleOverhead(bool toggleOverhead) {
	this->toggleOverhead = toggleOverhead;
}

// @brief Gets the boolean value as to whether or not the player is orbiting right.
bool Player::getIsOrbitingRight() {
	return this->isOrbitingRight;
}

// @brief Sets the boolean value as to whether or not the player is orbiting right.
// @param isOrbitingRight - boolean value, self explanatory
void Player::setIsOrbitingRight(bool isOrbitingRight) {
	this->isOrbitingRight = isOrbitingRight;
}

// @brief Gets the boolean value as to whether or not the player is orbiting left.
bool Player::getIsOrbitingLeft() {
	return this->isOrbitingRight;
}

// @brief Sets the boolean value as to whether or not the player is orbiting left.
// @param isOrbitingLeft - boolean value, self explanatory
void Player::setIsOrbitingLeft(bool isOrbitingLeft) {
	this->isOrbitingLeft = isOrbitingLeft;
}

// @brief Gets the boolean value as to whether or not the player is orbiting up.
bool Player::getIsOrbitingUp() {
	return this->isOrbitingUp;
}

// @brief Sets the boolean value as to whether or not the player is orbiting up.
// @param isOrbitingUp - boolean value, self explanatory
void Player::setIsOrbitingUp(bool isOrbitingUp) {
	this->isOrbitingUp = isOrbitingUp;
}

// @brief Gets the boolean value as to whether or not the player is orbiting down.
bool Player::getIsOrbitingDown() {
	return this->isOrbitingDown;
}

// @brief Sets the boolean value as to whether or not the player is orbiting down.
// @param isOrbitingDown - boolean value, self explanatory
void Player::setIsOrbitingDown(bool isOrbitingDown) {
	this->isOrbitingDown = isOrbitingDown;
}

// @brief Gets the boolean value as to whether or not the player is looking to the right.
bool Player::getIsLookingRight() {
	return this->isLookingRight;
}

// @brief Sets the boolean value as to whether or not the player is looking to the right.
// @param isLookingRight - boolean variable, self-explanatory
void Player::setIsLookingRight(bool isLookingRight) {
	this->isLookingRight = isLookingRight;
}

// @brief Gets the boolean value as to whether or not the player is looking to the left.
bool Player::getIsLookingLeft() {
	return this->isLookingLeft;
}

// @brief Sets the boolean value as to whether or not the player is looking to the left.
// @param isLookingLeft - boolean variable, self-explanatory
void Player::setIsLookingLeft(bool isLookingLeft) {
	this->isLookingLeft = isLookingLeft;
}

// @brief Gets the boolean value as to whether or not the player is looking up.
bool Player::getIsLookingUp() {
	return this->isLookingUp;
}

// @brief Sets the boolean value as to whether or not the player is looking up.
// @param isLookingUp - boolean variable, self-explanatory
void Player::setIsLookingUp(bool isLookingUp) {
	this->isLookingUp = isLookingUp;
}

// @brief Gets the boolean value as to whether or not the player is looking down.
bool Player::getIsLookingDown() {
	return this->isLookingDown;
}

// @brief Sets the boolean value as to whether or not the player is looking down.
// @param isLookingDown - boolean variable, self-explanatory
void Player::setIsLookingDown(bool isLookingDown) {
	this->isLookingDown = isLookingDown;
}

// @brief Gets the boolean value as to whether or not the player is turning to the right.
bool Player::getIsTurningRight() {
	return this->isTurningRight;
}

// @brief Sets the boolean value as to whether or not the player is turning to the right.
// @param isTurningRight - boolean variable, self-explanatory
void Player::setIsTurningRight(bool isTurningRight) {
	this->isTurningRight = isTurningRight;
}

// @brief Gets the boolean value as to whether or not the player is turning to the left.
bool Player::getIsTurningLeft() {
	return this->isTurningLeft;
}

// @brief Sets the boolean value as to whether or not the player is turning to the left.
// @param isTurningLeft - boolean variable, self-explanatory
void Player::setIsTurningLeft(bool isTurningLeft) {
	this->isTurningLeft = isTurningLeft;
}

// @brief Gets the boolean value as to whether or not the player is currently moving forward.
bool Player::getIsMovingForward() {
	return this->isMovingForward;
}

// @brief Sets the boolean value as to whether or not the player is currently moving forward.
// @param isMovingForward - boolean variable, self-explanatory
void Player::setIsMovingForward(bool isMovingForward) {
	this->isMovingForward = isMovingForward;
}

// @brief Sets the boolean value as to whether or not the player is currently moving backward.
bool Player::getIsMovingBackward() {
	return this->isMovingBackward;
}

// @brief Sets the boolean value as to whether or not the player is currently moving backward.
// @param isMovingBackward - boolean variable, self-explanatory
void Player::setIsMovingBackward(bool isMovingBackward) {
	this->isMovingBackward = isMovingBackward;
}