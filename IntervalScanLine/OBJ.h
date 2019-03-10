#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "glm\glm.hpp"
#include <fstream>
#include <ctime>
#include <io.h>

using namespace std;

class Vertex
{
public:
	glm::vec3 point;
	glm::vec3 color;
	glm::vec3 normal;//顶点法向量
};

class Face
{
public:
	vector<int> vti;//面的定点索引
	vector<int> nmi;//obj文件面法向量的索引
	glm::vec3 normal;//面的法向量
	glm::vec3 color;//颜色
};

//加载obj
class OBJ
{
public:
	OBJ() {};
	//OBJ(const std::string& path);
	vector<Vertex> vts;
	vector<Face> faces;
	vector<glm::vec3> normals;//顶点法向量
	bool load(const std::string& path);
	glm::vec3 cross(const glm::vec3 &u, const glm::vec3 &v);
	glm::vec3  normalize(const glm::vec3 &u);
	int lookat = 0;
};