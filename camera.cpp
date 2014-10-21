#include "camera.h"

using namespace PLUGraphicsLib;

Camera::Camera(){}
Camera::Camera(glm::vec3 pos, glm::vec3 at, glm::vec3 up, 
				float fov, float aspect, float n, float f): 
			position(pos), at(at), up(up), fov(fov), 
			aspectRatio(aspect), nearPlane(n), farPlane(f) {}


void Camera::pan(float x, float y, float z)
{
	position.x+=x;
	position.y+=y;
	position.z+=z;
	
	at.x+=x;
	at.y+=y;
}			

//decreases our field of view angle to make things look big
void Camera::zoomIn()
{
	if (fov > 10.f) fov-=1.f;
}

//increases our field of view angle to make things look small
void Camera::zoomOut()
{
	if (fov < 100.f) fov+=1.f;
}

//sets the position of the camera, where it's looking, and which way is defined as up
void Camera::set(glm::vec3 pos, glm::vec3 at, glm::vec3 up)
{
	this->position=pos;
	this->at=at;
	this->up=up;
}

//sets the field of view angle, aspect ratio of the base of the pyramid, 
//the near plane, and the far plane
void Camera::setViewVolume(float fov, float aspect, float n, float f)
{
	this->fov=fov;
	this->aspectRatio=aspect;
	this->nearPlane=n;
	this->farPlane=f;
}

//gets the projection matrix from our field of view angle, aspect ratio
//near plane, and far plane via glm::projection
glm::mat4 Camera::getProjectionMatrix()
{
	glm::mat4 g = glm::perspective(this->fov,this->aspectRatio,
					this->nearPlane,this->farPlane);
	return g;
}

//gets the view matrix from our position, at, and up via glm::lookAt
glm::mat4 Camera::getViewMatrix()
{
	glm::mat4 g = glm::lookAt(this->position, this->at, this->up);
	return g;
}
