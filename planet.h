#ifndef PLANET_H_
#define PLANET_H_

#include <ctime>
#include <gtc/matrix_transform.hpp>

#include <swephexp.h>
#include "sphere.h"

namespace PLUGraphicsLib {
	class Planet {
		private:
			float radius; //equatorial radius
			float pradius; //polar radius
			glm::vec3 color;
			int body_num;
			/*
			glm::vec3 spinAxes;
			float dayPeriod;
			float orbitPeriod;
			float distanceFromSun;
			//add fields for rings?
			*/
		public:
			Planet(GLfloat r, int body_num, glm::vec3 color);
			~Planet();
			//instead should spit us out a glm::mat4
			glm::mat4 adjustOrbit(double utctime, bool aroundSun);
			glm::vec3 getColor();
			int getBodyNum();
	};
};

#endif
