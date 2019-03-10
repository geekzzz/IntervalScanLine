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
	float x;//上端点x坐标
	float y_max;//y最大值,设置y最大和y最小值是为了方便区间扫描线不同y值得扫描线扫描时的求交操作
	float y_min;//y最小值,设置y最大和y最小值是为了方便区间扫描线不同y值得扫描线扫描时的求交操作
	float dx;//相邻两条扫描线交点的x坐标差，-1/k
	float dy;//跨越的扫描线的数目
	float a, b, c, d;
	int poly_id;//属于的多边形的编号
	PT_node * poly;//指向所属polygon
};
//ET为vector<vector<ET_node>> 结构
class ET
{
public:
	ET() { et.clear(); };
	vector<vector<ET_node>> et;
};