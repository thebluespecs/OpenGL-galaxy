#pragma once

#include <fstream>

#include "Vertex.h"

using namespace std;

class Parser{
private:
	vector <Vertex> vertices;
	vector <GLuint> indices;
	int num_vertices, num_indices;
	float max_x, max_y, max_z, min_x, min_y, min_z;
	float max_float(float a, float b);
	float min_float(float a, float b);
	vector <string> split(const string &input);
	void normalize(vector <Vertex> &vertices);

public:
	Parser();
	~Parser();

	vector <Vertex> getVertices();
	vector <GLuint> getIndices();
	int getNumIndices();
	int getNumVertices();
	float getMaxX();
	float getMaxY();
	float getMaxZ();
	float getMinX();
	float getMinY();
	float getMinZ();
	void readPly(string filename);
};
