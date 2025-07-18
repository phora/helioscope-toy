#ifndef PLANET_H_
#define PLANET_H_

#include <ctime>
#include <gtc/matrix_transform.hpp>

#include <swisseph/swephexp.h>
#include "sphere.h"

namespace PLUGraphicsLib {
	class Planet {
		private:
			float radius; //equatorial radius
			float pradius; //polar radius
			glm::vec3 color;
			int body_num;
			float heliocentric_orbit_distance;
			float geocentric_orbit_distance;
			/*
			glm::vec3 spinAxes;
			float dayPeriod;
			float orbitPeriod;
			float distanceFromSun;
			//add fields for rings?
			*/
		public:
			Planet(GLfloat r, int body_num, float hel_orb_dist, float geo_orb_dist, glm::vec3 color);
			~Planet();
			//instead should spit us out a glm::mat4
			glm::mat4 adjustOrbit(double utctime, bool aroundSun);
			glm::vec3 getColor();
			float getOrbitDistance(bool aroundSun);
			int getBodyNum();
	};

	namespace PlanetConstants {
		namespace Orbits {
			static const double MERCURY = 87.969;
			static const double VENUS   = 224.698;
			static const double EARTH   = 365.256363051;
			static const double MARS    = 686.971;
			static const double JUPITER = 4332.59;
			static const double SATURN  = 10759.22;
			static const double URANUS  = 30799.095;
			static const double NEPTUNE = 60190.03;
			static const double PLUTO   = 89865.65;
		};
	};


};

#endif
