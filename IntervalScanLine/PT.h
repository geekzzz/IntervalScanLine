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
	float a, b, c, d; //���������ƽ��ķ���ϵ����a^2+b^2+c^2=1����������(a,b,c)
	glm::vec3 color;
	int dy;//����ο�Ծ��ɨ������Ŀ
	PT_node * next = NULL;
	float z;//��ɸö���ε����е����ȵ�ƽ��ֵ
};

//PTΪ����ṹ
class PT
{
public:
	PT() { pt->next = NULL; }
	PT_node* pt = new PT_node();

};
