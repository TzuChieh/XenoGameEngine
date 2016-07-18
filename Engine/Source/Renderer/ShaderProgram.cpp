#include "ShaderProgram.h"
#include "Shader.h"
#include "Core/graphicsApi.h"

#include <iostream>

using namespace xe;

ShaderProgram::ShaderProgram() {
	m_programId = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(m_programId);
}

void ShaderProgram::completeProgram(const Shader& vertShader, const Shader& fragShader) const {
	// TODO: check errors

	glAttachShader(m_programId, vertShader.m_shaderId);
	glAttachShader(m_programId, fragShader.m_shaderId);

	glLinkProgram(m_programId);

	glDetachShader(m_programId, vertShader.m_shaderId);
	glDetachShader(m_programId, fragShader.m_shaderId);
}

void ShaderProgram::use() const {
	glUseProgram(m_programId);
}

void ShaderProgram::registerUniform(const std::string& uniformName) {
	m_uniformIdMap.emplace(uniformName, getUniformIdFromOpenGL(uniformName));
}

void ShaderProgram::updateUniform(const std::string& uniformName, const int uniformValue) {
	glUniform1i(getUniformId(uniformName), uniformValue);
}

GLint ShaderProgram::getUniformIdFromOpenGL(const std::string& uniformName) const {
	int uniformLocationId = glGetUniformLocation(m_programId, uniformName.c_str());

	if(uniformLocationId == 0xFFFFFFFF) {
		std::cerr << "ShaderPorgram Error: uniform <" + uniformName + "> does not exist \n";
	}

	return uniformLocationId;
}

GLint ShaderProgram::getUniformId(const std::string& uniformName) {
	if(m_uniformIdMap.count(uniformName) == 1) {
		return m_uniformIdMap[uniformName];
	}
	else {
		if(m_uniformIdMap.count(uniformName) == 0) {
			std::cerr << "ShaderPorgram Error: uniform <" + uniformName + "> does not exist \n";
		}
		else {
			std::cerr << "ShaderPorgram Error: uniform <" + uniformName + "> caused unknown behavior, "
			          << "unordered_map.count() returns value larger than 1 \n";
		}

		return 0xFFFFFFFF;
	}
}