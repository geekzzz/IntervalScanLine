#pragma once
#include <iostream>
#include <algorithm>
#include <omp.h>
#include "AET.h"
#include "ET.h"
#include "IPL.h"
#include "OBJ.h"
#include "PT.h"
#include "glm\glm.hpp"
//#include <GL\glut.h>
#include <GL\glut.h>

class Interval_scanline
{
public:
	void Create_ET_PT(OBJ& obj);//建立ET,PT,其中ET是vector<vector<ET_node>>方便使用stl sort进行排序。PT是链表记录polygon信息，不进行排序等操作
	void Fit_screen(OBJ& obj);//将点坐标归一化到屏幕空间
	void Add_Edge_to_AET();//每次进入此条扫描线进行操作时，先将y扫描线的ET.et[y]中的边加入AET中
	void Update_AET();//更新AET中边的数据
	void Scan();//进行扫描
	static bool mysortfunc_edge(const AET_node & e1, const AET_node & e2);//排序函数
	void setcolor(int x1, int x2, glm::vec3 color);//设置扫描线为y值时，x1至x2区间的颜色
	glm::vec3 colorbuffer[800][600];//记录颜色
	int y;//扫描线的值
	AET AET;//记录每条扫描线的活化边
	IPL IPL; //active in polygon list，inoutflag 为1的polygon在每次扫描时加入
	ET ET; //ET是vector<vector<ET_node>>方便使用stl sort进行排序,以及扫描线扫描时取ET_node
	PT PT; //PT是链表记录polygon信息，不进行排序等操作
	AET_node left_x;//最左方与x轴垂直的x0线段
	AET_node right_x; //最右方与x轴垂直的xn线段
	PT_node* Back_ground = new PT_node();  //背景polygon,left_x和right_x属于Back_grund
	const static int width = 800, height = 600;//窗口的长宽数据
	float maxpz, minpz, max_minpz;//采用面片的深度设置面片的颜色时，记录所有点的最大与最小深度值，方便归一化至（0,1）区间
	int rendermode = 0;
};