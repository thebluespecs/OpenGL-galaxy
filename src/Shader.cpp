#include "Shader.h"

using namespace std;


Shader::Shader(){};
Shader::~Shader(){};



Shader::Shader(const string &vertexShader, const string &fragmentShader){
    vShader = vertexShader;
    fShader = fragmentShader;
}

Shader::Shader(const Shader &s){
    vShader = s.vShader;
    fShader = s.fShader;
}

string Shader::readFile(string fileLocation)
{
	string content;
	ifstream fileStream(fileLocation, ios::in);

	if (!fileStream.is_open()) {
		cout << "No file\n";
		cout << "Failed to read "  << fileLocation <<  " File doesn't exist.";
		return "";
	}

	string line = "";
	while (!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}


GLuint Shader::getshaderID(){
    return shaderID;
}

void Shader::addShader(const string &shaderIDCode, GLenum shaderIDType){
    GLuint theShader = glCreateShader(shaderIDType);

	const GLchar* theCode[1];
	theCode[0] = &shaderIDCode[0];

	GLint codeLength[1];
	codeLength[0] = strlen(&shaderIDCode[0]);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = {0};

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shaderID: '%s'\n", shaderIDType, eLog);
		return;
	}

	glAttachShader(shaderID, theShader);
}

void Shader::compileShader(const string &vertexCode, const string &fragmentCode){
    shaderID = glCreateProgram();

	if(!shaderID)
	{
		cout << "Error creating shaderID.\n";
		return;
	}

	addShader(vertexCode, GL_VERTEX_SHADER);
	addShader(fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}
}

void Shader::createShader(){
    string vertexString = readFile(vShader);
	string fragmentString = readFile(fShader);
	string vertexCode = vertexString.c_str();
    string fragmentCode = fragmentString.c_str();
	compileShader(vertexCode, fragmentCode);
}