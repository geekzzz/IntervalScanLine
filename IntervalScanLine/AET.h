#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "PT.h"

using namespace std;

class AET_node
{
public:
	AET_node() {};
	float now_x;//当扫描线扫描至当前y值时，扫描线y与此条边的交点的x的值，通过方程x + (y_max - y)*dx计算，其中y是扫描线y的值
	float x; // 边的上端点的x坐标
	float dx; // (交点边上)两相邻扫描线交点的x坐标之差.-1/k,扫描线向下移动1时x的增量
	float z; // 交点处多边形所在平面的深度值
	int y_max; //记录最大y值
	int y_min; //记录最小y值
	int poly_id; // 交点对所在的多边形的编号
	PT_node* poly = NULL;
};

class AET
{
public:
	AET() { aet.clear(); }
	vector<AET_node> aet;
};


