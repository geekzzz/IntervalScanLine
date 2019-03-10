#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "PT.h"

using namespace std;

class AET_node
{
public:
	AET_node() {};
	float now_x;//��ɨ����ɨ������ǰyֵʱ��ɨ����y������ߵĽ����x��ֵ��ͨ������x + (y_max - y)*dx���㣬����y��ɨ����y��ֵ
	float x; // �ߵ��϶˵��x����
	float dx; // (�������)������ɨ���߽����x����֮��.-1/k,ɨ���������ƶ�1ʱx������
	float z; // ���㴦���������ƽ������ֵ
	int y_max; //��¼���yֵ
	int y_min; //��¼��Сyֵ
	int poly_id; // ��������ڵĶ���εı��
	PT_node* poly = NULL;
};

class AET
{
public:
	AET() { aet.clear(); }
	vector<AET_node> aet;
};


