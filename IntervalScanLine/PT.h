#pragma once
#include <iostream>
#include <vector>
#include "glm/glm.hpp"

using namespace std;

class PT_node
{
public:
	PT_node() {  };
	int poly_id;
	int inout_flag = 0;
	float a, b, c, d; //多边形所在平面的方程系数，a^2+b^2+c^2=1，法线向量(a,b,c)
	glm::vec3 color;
	int dy;//多边形跨跃的扫描线数目
	PT_node * next = NULL;
	float z;//组成该多边形的所有点的深度的平均值
};

//PT为链表结构
class PT
{
public:
	PT() { pt->next = NULL; }
	PT_node* pt = new PT_node();

};
