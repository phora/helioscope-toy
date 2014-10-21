#include "planet.h"
namespace PLUGraphicsLib {

Planet::Planet(GLfloat f, int body_num, glm::vec3 color):
	radius(f), pradius(f),
	color(color.x, color.y, color.z),
	body_num(body_num)//,
	/*spinAxes(spinAxes),
	dayPeriod(1.f),
	orbitPeriod(365.25f),
	distanceFromSun(8E6)*/
	//should probably have tilty orbit axis?
{
}

Planet::~Planet() { }

glm::mat4 Planet::adjustOrbit(double utctime, bool aroundSun)
{
	double v[6]; //or vector<double>
	char serr[256]; //where's AS_MAXCH?
	//float dscale=1000.f;
	//float rscale=1000.f;
	
	/*
	//distances are in term of astronomical units btw
	swe_calc_ut(utc_juldays, body_num, SEFLG_HELCTR, v, &serr);
	glm::mat4 nmm;
	nmm = glm::translate(nmm,glm::vec3(distanceFromSun,0.f,0.f));
	//see http://www.astro.com/swisseph/swephprg.htm#_Toc335137325
	nmm = glm::rotate(nmm, v[0], glm::vec3(0.f,1.f,0.f))
	//glm
	*/

	//hey, let's try SEFLG_HELCTR|SEFLG_XYZ for ultra-realistic orbits!
	
	//tack on minutes and seconds as decimal portions of time
	long flags = 0;
	if (aroundSun) {
		flags|=SEFLG_HELCTR;
	}
	swe_calc_ut(utctime, body_num, flags, v, serr);

	glm::mat4 nmm;
	//nmm = glm::scale(nmm, glm::vec3(radius*rscale, pradius*rscale, radius*rscale));
	//nmm = glm::translate(nmm, glm::vec3(v[0]/*dscale*/,v[1]/*dscale*/,v[2]/*dscale*/));
	//nmm = glm::translate(nmm, glm::vec3(v[0]/*dscale*/,v[1]/*dscale*/,v[2]/*dscale*/));
	nmm = glm::rotate(nmm, (float)v[0], glm::vec3(0,0,1));
	//printf("Velocities in AU: %E,%E,%E\n",v[3],v[4],v[5]);
	return nmm;
}

glm::vec3 Planet::getColor()
{
	return color;
}

int Planet::getBodyNum()
{
	return body_num;
}

}
