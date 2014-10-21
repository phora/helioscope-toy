#include "shaderprogram.h"

#include <fstream>
#include <sstream>
#include <iostream>
using std::cerr;
using std::endl;

namespace PLUGraphicsLib {

ShaderProgram::ShaderProgram() : programID(0), linked(false) { }

ShaderProgram::~ShaderProgram() {
	if(programID == 0) return;

	// Query the number of attached shaders
	GLint numShaders = 0;
	glGetProgramiv(programID, GL_ATTACHED_SHADERS, &numShaders);

	// Get the shader names
	GLuint * shaderNames = new GLuint[numShaders];
	glGetAttachedShaders(programID, numShaders, NULL, shaderNames);

	// Delete the shaders
	for (int i = 0; i < numShaders; i++)
		glDeleteShader(shaderNames[i]);

	// Delete the program
	glDeleteProgram (programID);

	delete[] shaderNames;
}

void ShaderProgram::use() {
	if( programID != 0 && linked )
		glUseProgram(programID);
}

void ShaderProgram::compile(const char * vShaderCode, const char * fShaderCode) {
	// Create the shader objects
	GLuint vert = glCreateShader(GL_VERTEX_SHADER);
	GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);

	// Load the shader source
	glShaderSource(vert, 1, &vShaderCode, NULL);
	glShaderSource(frag, 1, &fShaderCode, NULL);

	// Compile
	glCompileShader(vert);
	if (!checkCompilationStatus(vert)) {
		glDeleteShader(vert);
		glDeleteShader(frag);
		throw ShaderCompilationError("Failed to compile vertex shader.");
	}
	glCompileShader(frag);
	if (!checkCompilationStatus(frag)) {
		glDeleteShader(vert);
		glDeleteShader(frag);
		throw ShaderCompilationError("Failed to compile fragment shader.");
	}

	// Create the program object
	programID = glCreateProgram();
	glAttachShader(programID, vert);
	glAttachShader(programID, frag);
}

void ShaderProgram::setUniform(const char *name, const glm::mat4 & m) {
	GLint location = glGetUniformLocation(programID, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
}

void ShaderProgram::setUniform(const char * name, const glm::vec3 & value ) {
	GLint location = glGetUniformLocation(programID, name);
	glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::setUniform(const char * name, float value ) {
	GLint location = glGetUniformLocation(programID, name);
	glUniform1f(location, value);
}

void ShaderProgram::setUniform(const char * name, int value ) {
	GLint location = glGetUniformLocation(programID, name);
	glUniform1i(location, value);
}

void ShaderProgram::compileFromFile(const char *vShaderFileName, const char * fShaderFileName) {
	string vShaderCode, fShaderCode;

	loadFile(vShaderFileName, vShaderCode);
	loadFile(fShaderFileName, fShaderCode);

	compile(vShaderCode.c_str(), fShaderCode.c_str());
}

void ShaderProgram::bindAttribLocation(GLuint index, const char * attribName ) {
	glBindAttribLocation(programID, index, attribName);
}

void ShaderProgram::link() {
	if( programID != 0 ) {
		glLinkProgram( programID );
		checkLinkStatus();
		linked = true;
	}
}

void ShaderProgram::loadFile( const char * fName, string &result ) {
	std::ifstream inFile(fName);
	if (!inFile) throw ShaderCompilationError("Shader file not found.");
	std::stringstream code;
	code << inFile.rdbuf();
	inFile.close();
	result = code.str();
}

bool ShaderProgram::checkCompilationStatus( GLuint shaderID )
{
    GLint status, logLen;
    GLchar *log;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
    if( GL_TRUE == status ) return true;

    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLen);
    log = new GLchar[ logLen ];
    glGetShaderInfoLog(shaderID, logLen, NULL, log);

    cerr << "Failed to compile shader" << endl;
    cerr << log << endl;

    delete [] log;
    return false;
}

bool ShaderProgram::checkLinkStatus(  )
{
    GLint status, logLen;
    GLchar *log;
    glGetProgramiv(programID, GL_LINK_STATUS, &status);
    if( GL_TRUE == status ) return true;

    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLen);
    log = new GLchar[ logLen ];
    glGetProgramInfoLog(programID, logLen, NULL, log);

    cerr << "Failed to link shader" << endl;
    cerr << log << endl;

    delete [] log;
    return false;
}

} /* namespace PLUGraphicsLib */
