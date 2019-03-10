#pragma once
#include <iostream>
#include <vector>
#include "PT.h"

using namespace std;

class ET_node
{
public:
	ET_node() {};
	ET_node(float x, float y_max, float y_min, float dx, int poly_id) : x(x), y_max(y_max), y_min(y_min), dx(dx), poly_id(poly_id) {};
	float x;//�϶˵�x����
	float y_max;//y���ֵ,����y����y��Сֵ��Ϊ�˷�������ɨ���߲�ͬyֵ��ɨ����ɨ��ʱ���󽻲���
	float y_min;//y��Сֵ,����y����y��Сֵ��Ϊ�˷�������ɨ���߲�ͬyֵ��ɨ����ɨ��ʱ���󽻲���
	float dx;//��������ɨ���߽����x����-1/k
	float dy;//��Խ��ɨ���ߵ���Ŀ
	float a, b, c, d;
	int poly_id;//���ڵĶ���εı��
	PT_node * poly;//ָ������polygon
};
//ETΪvector<vector<ET_node>> �ṹ
class ET
{
public:
	ET() { et.clear(); };
	vector<vector<ET_node>> et;
};