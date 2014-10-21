/*
 * Chrisdona Joan C. Paraiso
 * CSCE412
 * Program 4
 * 4/3/2013
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <cstdlib>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace PLUGraphicsLib {

	class Camera {
	public:
		Camera();
		Camera(glm::vec3 pos, glm::vec3 at, glm::vec3 up, float fov,
			float aspect, float n, float f);
		void set(glm::vec3 pos, glm::vec3 at, glm::vec3 up);
		void setViewVolume(float fov, float aspect, float n, float f);
		glm::mat4 getProjectionMatrix();
		glm::mat4 getViewMatrix();

		void pan(float x, float y, float z);
		
		void zoomIn();
		void zoomOut();
	
	private:
		glm::vec3 position;
		glm::vec3 at;
		glm::vec3 up;
		float fov;
		float aspectRatio;
		float nearPlane;
		float farPlane;
	};

}

#endif /* CAMERA_H_ */
