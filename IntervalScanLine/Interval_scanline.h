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
	void Create_ET_PT(OBJ& obj);//����ET,PT,����ET��vector<vector<ET_node>>����ʹ��stl sort��������PT�������¼polygon��Ϣ������������Ȳ���
	void Fit_screen(OBJ& obj);//���������һ������Ļ�ռ�
	void Add_Edge_to_AET();//ÿ�ν������ɨ���߽��в���ʱ���Ƚ�yɨ���ߵ�ET.et[y]�еı߼���AET��
	void Update_AET();//����AET�бߵ�����
	void Scan();//����ɨ��
	static bool mysortfunc_edge(const AET_node & e1, const AET_node & e2);//������
	void setcolor(int x1, int x2, glm::vec3 color);//����ɨ����Ϊyֵʱ��x1��x2�������ɫ
	glm::vec3 colorbuffer[800][600];//��¼��ɫ
	int y;//ɨ���ߵ�ֵ
	AET AET;//��¼ÿ��ɨ���ߵĻ��
	IPL IPL; //active in polygon list��inoutflag Ϊ1��polygon��ÿ��ɨ��ʱ����
	ET ET; //ET��vector<vector<ET_node>>����ʹ��stl sort��������,�Լ�ɨ����ɨ��ʱȡET_node
	PT PT; //PT�������¼polygon��Ϣ������������Ȳ���
	AET_node left_x;//������x�ᴹֱ��x0�߶�
	AET_node right_x; //���ҷ���x�ᴹֱ��xn�߶�
	PT_node* Back_ground = new PT_node();  //����polygon,left_x��right_x����Back_grund
	const static int width = 800, height = 600;//���ڵĳ�������
	float maxpz, minpz, max_minpz;//������Ƭ�����������Ƭ����ɫʱ����¼���е���������С���ֵ�������һ������0,1������
	int rendermode = 0;
};