#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include "gl_compat_3_2.h"

#include <stdexcept>
using std::runtime_error;

#include <string>
using std::string;

#include <glm.hpp>

namespace PLUGraphicsLib {

class ShaderCompilationError : public runtime_error
{
public:
	ShaderCompilationError(const char * message ) : runtime_error(message) {}
};

class ShaderProgram {
public:
	ShaderProgram();
	~ShaderProgram();

	void compile(const char * vShaderCode, const char * fShaderCode);
	void compileFromFile(const char * vShaderFileName, const char * fShaderFileName);

	void link();
	void use();

	void bindAttribLocation(GLuint index, const char * attribName);
	void setUniform(const char * name, const glm::mat4 & m);
	void setUniform(const char * name, const glm::vec3 & value);
	void setUniform(const char * name, float value);
	void setUniform(const char * name, int value );

private:
	GLuint programID;
	bool linked;

	void loadFile( const char * fileName, string &contents /*out*/ );
	bool checkCompilationStatus(GLuint id);
	bool checkLinkStatus();

	// Making these private helps to avoid copying ShaderProgram objects.
	// We want these objects to essentially be non-copyable.
	ShaderProgram( const ShaderProgram & other );
	ShaderProgram & operator=( const ShaderProgram & );
};

} /* namespace PLUGraphicsLib */
#endif /* SHADERPROGRAM_H_ */
