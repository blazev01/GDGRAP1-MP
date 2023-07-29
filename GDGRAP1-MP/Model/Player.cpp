#include "Player.hpp"

using namespace models;

Player::Player(glm::vec3 position, glm::vec3 forward) {
	this->F = glm::normalize(glm::vec3(forward - position));

	this->isOrbitingRight = false;
	this->isOrbitingLeft = false;
	this->isLookingRight = false;
	this->isLookingLeft = false;
	this->isLookingUp = false;
	this->isLookingDown = false;
	this->isTurningRight = false;
	this->isTurningLeft = false;
	this->isMovingForward = false;
	this->isMovingBackward = false;
}

void Player::circle(Camera* Cam) {
	if (this->isOrbitingRight) {
		this->isOrbitingRight = false;
		Cam->orbit(this->orbitSpeed, 0.0f, 1.0f, 0.0f);
	}
	else if (this->isOrbitingLeft) {
		this->isOrbitingLeft = false;
		Cam->orbit(-this->orbitSpeed, 0.0f, 1.0f, 0.0f);
	}
}

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

void Player::turn(Model3D* Model) {
	if (this->isTurningRight) {
		this->isTurningRight = false;
		Model->rotate(this->turnSpeed, 0.0f, 1.0f, 0.0f);
		this->calcForward(this->turnSpeed);

	}
	else if (this->isTurningLeft) {
		this->isTurningLeft = false;
		Model->rotate(-this->turnSpeed, 0.0f, 1.0f, 0.0f);
		this->calcForward(-this->turnSpeed);
	}
}

void Player::move(Model3D* Model) {
	if (this->isMovingForward) {
		this->isMovingForward = false;
		glm::vec3 velocity = this->F * this->moveSpeed;
		Model->translate(velocity);
	}
	else if (this->isMovingBackward) {
		this->isMovingBackward = false;
		glm::vec3 velocity = this->F * -this->moveSpeed;
		Model->translate(velocity);
	}
}

void Player::calcForward(float theta) {
	glm::vec3 U = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 R = glm::normalize(glm::cross(F, U));

	glm::mat4 orientation = glm::mat4(1.0f);

	orientation[0][0] = R.x;
	orientation[1][0] = R.y;
	orientation[2][0] = R.z;

	orientation[0][1] = U.x;
	orientation[1][1] = U.y;
	orientation[2][1] = U.z;

	orientation[0][2] = -this->F.x;
	orientation[1][2] = -this->F.y;
	orientation[2][2] = -this->F.z;

	orientation = glm::rotate(orientation, theta, U);

	this->F.x = -orientation[0][2];
	this->F.y = -orientation[1][2];
	this->F.z = -orientation[2][2];
}

bool Player::getIsOrbitingRight() {
	return this->isOrbitingRight;
}

void Player::setIsOrbitingRight(bool isOrbitingRight) {
	this->isOrbitingRight = isOrbitingRight;
}

bool Player::getIsOrbitingLeft() {
	return this->isOrbitingRight;
}

void Player::setIsOrbitingLeft(bool isOrbitingLeft) {
	this->isOrbitingLeft = isOrbitingLeft;
}

bool Player::getIsLookingRight() {
	return this->isLookingRight;
}

void Player::setIsLookingRight(bool isLookingRight) {
	this->isLookingRight = isLookingRight;
}

bool Player::getIsLookingLeft() {
	return this->isLookingLeft;
}

void Player::setIsLookingLeft(bool isLookingLeft) {
	this->isLookingLeft = isLookingLeft;
}

bool Player::getIsLookingUp() {
	return this->isLookingUp;
}

void Player::setIsLookingUp(bool isLookingUp) {
	this->isLookingUp = isLookingUp;
}

bool Player::getIsLookingDown() {
	return this->isLookingDown;
}

void Player::setIsLookingDown(bool isLookingDown) {
	this->isLookingDown = isLookingDown;
}

bool Player::getIsTurningRight() {
	return this->isTurningRight;
}

void Player::setIsTurningRight(bool isTurningRight) {
	this->isTurningRight = isTurningRight;
}

bool Player::getIsTurningLeft() {
	return this->isTurningLeft;
}

void Player::setIsTurningLeft(bool isTurningLeft) {
	this->isTurningLeft = isTurningLeft;
}

bool Player::getIsMovingForward() {
	return this->isMovingForward;
}

void Player::setIsMovingForward(bool isMovingForward) {
	this->isMovingForward = isMovingForward;
}

bool Player::getIsMovingBackward() {
	return this->isMovingBackward;
}

void Player::setIsMovingBackward(bool isMovingBackward) {
	this->isMovingBackward = isMovingBackward;
}