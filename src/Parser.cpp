#include "Parser.h"

using namespace std;

Parser::Parser(){
    max_x = max_y = max_z = -1;
    min_x = min_y = min_z = 1e9;
    vertices = vector <Vertex>(50000);
    indices = vector <GLuint>(50000);
};
Parser::~Parser(){};

float Parser::max_float(float a, float b){
    if(a > b){
        return a;
    }
    return b;
}

float Parser::min_float(float a, float b){
    if(a > b)
    {
        return b;
    }
    return a;
}

vector <string> Parser::split(const string &input){
    vector <string> ret;
    string temp = "";

    for(int i = 0; i<input.size(); i++)
    {
        if(input[i] != ' ')
        {
            temp += input[i];
        }
        else
        {
            ret.push_back(temp);
            temp = "";
        }
    }
    if(temp != "")
    {
        ret.push_back(temp);
    }
    return ret;
}

void Parser::normalize(vector <Vertex> &vertices){
    float max_num = -1;
    max_num = max_float(max_num, max_x);
    max_num = max_float(max_num, max_y);
    max_num = max_float(max_num, max_z);
    max_num = max_float(max_num, abs(min_x));
    max_num = max_float(max_num, abs(min_y));
    max_num = max_float(max_num, abs(min_z));

    min_x = min_x/(max_num*2.0f);
    min_y = min_y/(max_num*2.0f);
    min_z = min_z/(max_num*2.0f);
    max_x = max_x/(max_num*2.0f);
    max_y = max_y/(max_num*2.0f);
    max_z = max_z/(max_num*2.0f);

    float mid_x = (min_x + max_x) / 2;
    float mid_y = (min_y + max_y) / 2;
    float mid_z = (min_z + max_z) / 2;

    for(int i = 0; i < num_vertices; i++){
        glm::vec3 pos = vertices[i].getPosition();
        pos = pos/(max_num*2.0f);
        pos.x -= mid_x;
        pos.y -= mid_y;
        pos.z -= mid_z;
        vertices[i].setPosition(pos);
    }
}

vector <Vertex> Parser::getVertices(){
    return vertices;
}

vector <GLuint> Parser::getIndices(){
    return indices;
}

float Parser::getMaxY(){
    return max_y;
}

float Parser::getMaxZ(){
    return max_z;
}

float Parser::getMaxX(){
    return max_x;
}

float Parser::getMinX(){
    return min_x;
}

float Parser::getMinY(){
    return min_y;
}

float Parser::getMinZ(){
    return min_z;
}


int Parser::getNumVertices(){
    return num_vertices;
}

int Parser::getNumIndices(){
    return num_indices;
}

void Parser::readPly(string filename){
    ifstream in_file(filename);
    string raw_line;
    vector <string> line;

    if(!in_file.is_open())
    {
        cout << "No data file exists\n";
    }

    while(getline(in_file, raw_line)){
        line = split(raw_line);
        if(line[0] == "element"){
            if(line[1] == "vertex"){
                num_vertices = stoi( line[2] );
            }
            else if(line[1] == "face"){
                num_indices = stoi( line[2] );
            }
        }
        else if(line[0] == "end_header\r" or line[0] == "end_header"){
            break;
        }
    }

    float x, y, z;
    GLuint size, i1, i2, i3;
    
    for(int i = 0; i < num_vertices; i++){
        in_file >> x >> y >> z;

        max_x = max_float(x, max_x);
        max_y = max_float(y, max_y);
        max_z = max_float(z, max_z);

        min_x = min_float(x, min_x);
        min_y = min_float(y, min_y);
        min_z = min_float(z, min_z);

        Vertex v(glm::vec3(x, y, z));

        vertices[i] = v;
    }

    for(int i = 0; i < num_indices; i++){
        in_file >> size >> i1 >> i2 >> i3;
        indices[3*i] = i1;
        indices[3*i+1] = i2;
        indices[3*i+2] = i3;
    }
    normalize(vertices);

}