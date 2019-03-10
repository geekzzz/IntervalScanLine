#include "Interval_scanline.h"
#include <fstream>


using namespace std;


//区间扫描线算法
void Interval_scanline::Scan()
{
	//最左边的x = 0处的edge
	left_x.x = 0;
	left_x.dx = 0;
	left_x.poly_id = -100;//设背景polygon的poly_id为-100
	left_x.y_max = height - 1;
	left_x.y_min = 0;
	left_x.now_x = 0;
	left_x.poly = Back_ground;
	//最右边的x = width处的edge
	right_x.x = width - 1;
	right_x.dx = 0;
	right_x.poly_id = -100;
	right_x.y_max = height - 1;
	right_x.y_min = 0;
	right_x.now_x = width - 1;
	right_x.poly = Back_ground;
	//背景polygon
	Back_ground->a = 0;
	Back_ground->b = 0;
	Back_ground->c = 1;
	Back_ground->d = -1;
	Back_ground->color.x = 0;
	Back_ground->color.y = 0;
	Back_ground->color.z = 0;
	Back_ground->poly_id = -100;
	Back_ground->inout_flag = 0;
	Back_ground->z = -9999;
	int ymax = height - 1;
	int ymin = 0;
	y = ymax;
	AET.aet.clear();
	IPL.ipl.clear();
	AET.aet.push_back(left_x);
	AET.aet.push_back(right_x);
	vector<AET_node>::iterator e1;
	vector<AET_node>::iterator e2;
	//扫描线扫描
	for (y = ymax; y > ymin; --y)
	{
		IPL.ipl.clear();
		Add_Edge_to_AET();
		sort(AET.aet.begin(), AET.aet.end(), mysortfunc_edge);
		Back_ground->inout_flag = 2;//back_ground比较特殊，将flag设为2，避免维护ipl时出错
		IPL.ipl.push_back(*(Back_ground));
		//遍历AET
		for (e1 = AET.aet.begin(), e2 = e1 + 1; e2 != AET.aet.end();)
		{
			//如果inou_flag为0,加入IPL中
			if (e1->poly->inout_flag == 0)
			{
				IPL.ipl.push_back(*(e1->poly));
				e1->poly->inout_flag = 1;
			}
			//如果inou_flag为1,从IPL中删除
			else if (e1->poly->inout_flag == 1)
			{
				e1->poly->inout_flag = 0;
				for (auto i = IPL.ipl.begin(); i != IPL.ipl.end(); )
				{
					if (i->poly_id == e1->poly_id)
					{
						i = IPL.ipl.erase(i);
					}
					else
					{
						++i;
					}
				}
			}
			float lmax = -9999, rmax = -9999;//判断贯穿情况，记录e1与e2的最大深度
			float ldep, rdep;//每次计算的深度
			float zmax = -9999;//所有的最大深度
			glm::vec3 color(0, 0, 0);
			int l_poly_id = -100, r_poly_id = -100;
			float l_poly_a = Back_ground->a, l_poly_b = Back_ground->b, l_poly_c = Back_ground->c, l_poly_d = Back_ground->d, r_poly_a = Back_ground->a, r_poly_b = Back_ground->b, r_poly_c = Back_ground->c, r_poly_d = Back_ground->d;
			glm::vec3 l_poly_color(0, 0, 0);
			glm::vec3 r_poly_color(0, 0, 0);
			//遍历当前IPL，判断贯穿情况
			for (auto it = IPL.ipl.begin(); it != IPL.ipl.end(); ++it)
			{
				if (it->poly_id == -100)
				{
					continue;
				}
				//计算当前的深度值
				ldep = ((it->a * e1->now_x) + (it->b * y) + (it->d)) / (-it->c);
				rdep = ((it->a * e2->now_x) + (it->b * y) + (it->d)) / (-it->c);
				//通过比较，记录当前e1至e2区间中，IPL中的面在e1的（now_x,y）以及e2的(now_x,y)处分别的最大深度值
				if (lmax < ldep)
				{
					lmax = ldep;
					l_poly_id = it->poly_id;
					l_poly_a = it->a;
					l_poly_b = it->b;
					l_poly_c = it->c;
					l_poly_d = it->d;
					l_poly_color = it->color;
				}
				//通过比较，记录当前e1至e2区间中，IPL中的面在e1的（now_x,y）以及e2的(now_x,y)处分别的最大深度值
				if (rmax < rdep)
				{
					rmax = rdep;
					r_poly_id = it->poly_id;
					r_poly_a = it->a;
					r_poly_b = it->b;
					r_poly_c = it->c;
					r_poly_d = it->d;
					r_poly_color = it->color;
				}
				if (it->z > zmax)
				{
					zmax = it->z;
					color = it->color;
				}
			}

			if (l_poly_id != r_poly_id)//通过之前记录下的最大深度值的ID,判断是否贯穿
			{
				//联立两个平面的方程，解出在y值确定时的两平面交线处的x的值，使用解出来的x值对贯穿情况进行分割，分别进行作色
				float cross_x = (-(r_poly_c * l_poly_b * y) + (l_poly_c * r_poly_b * y) - (r_poly_c * l_poly_d) + (l_poly_c * r_poly_d)) / ((r_poly_c * l_poly_a) - (l_poly_c * r_poly_a));

				if (cross_x >= e1->now_x && cross_x <= e2->now_x)//判断是否超出两条边的范围，增加鲁棒性
				{
					setcolor(floor(e1->now_x), floor(cross_x), l_poly_color);//设置贯穿左边部分的颜色
					setcolor(floor(cross_x), floor(e2->now_x), r_poly_color);//设置贯穿右边部分的颜色
				}
				else
				{
					setcolor(floor(e1->now_x), floor(e2->now_x), color);//直接设置颜色
				}
			}
			else//未贯穿情况
			{
				setcolor(floor(e1->now_x), floor(e2->now_x), color);//直接e1至e2的颜色
			}
			++e1;//移动迭代器
			++e2;//移动迭代器
		}

		Update_AET();//对AET进行更新
	}

}

//将ET中y_max为y的值，加入AET中
void Interval_scanline::Add_Edge_to_AET()
{
	if (!ET.et[y].empty())
	{
		for (auto it = ET.et[y].begin(); it != ET.et[y].end(); ++it)
		{
			AET_node active_edge;
			active_edge.x = it->x;
			active_edge.dx = it->dx;
			active_edge.poly_id = it->poly_id;
			active_edge.y_max = it->y_max;
			active_edge.y_min = it->y_min;
			active_edge.poly = it->poly;
			active_edge.now_x = it->x;
			active_edge.poly->inout_flag = 0;
			AET.aet.push_back(active_edge);
		}
	}
}
//更新AET
void Interval_scanline::Update_AET()
{
	//遍历AET表
	for (auto it = AET.aet.begin(); it != AET.aet.end();)
	{
		it->poly->inout_flag = 0;
		//如果扫描线小于线段的y_min,移除
		if (it->y_min >= y - 1)
		{
			it = AET.aet.erase(it);
		}
		//now_x更新，now_x为下一条扫描线 
		else
		{
			it->now_x = it->now_x + it->dx;
			++it;
		}
	}
}

//对AET进行sort的排序函数
bool Interval_scanline::mysortfunc_edge(const AET_node & e1, const AET_node & e2)
{
	if (floor(e1.now_x) < floor(e2.now_x))
	{
		return true;
	}
	else if (floor(e1.now_x) == floor(e2.now_x))
	{
		if (floor(e1.dx) < floor(e2.dx))
		{
			return true;
		}
	}
	return false;

}
//对x1至x2坐标处的颜色进行设置，y值定义在Interval_scanline内，实时更新
void Interval_scanline::setcolor(int x1, int x2, glm::vec3 color)
{
	if (x1 == x2)
	{
		colorbuffer[x1][y].r = color.r;
		colorbuffer[x1][y].g = color.g;
		colorbuffer[x1][y].b = color.b;
	}
	else {
		for (int i = x1; i < x2; i++)
		{
			colorbuffer[i][y].r = color.r;
			colorbuffer[i][y].g = color.g;
			colorbuffer[i][y].b = color.b;
		}
	}
}
//建立PT,ET表
void Interval_scanline::Create_ET_PT(OBJ & obj)
{
	if (rendermode == 0)
	{
		ET.et.clear();
		ET.et.resize(height);
		int faces_size = obj.faces.size();
		for (int i = 0; i < faces_size; ++i)
		{
			float ymi = 9999, yma = -9999;
			Face& face = obj.faces[i];
			PT_node* polygon = new PT_node();
			polygon->next = NULL;
			polygon->poly_id = i;
			glm::vec3 v1 = obj.vts[face.vti[0]].point;
			float zbuf = 0;
			const vector<int>& vti = obj.faces[i].vti;
			for (int j = 0, vsize = vti.size(); j < vsize; ++j)
			{
				glm::vec3 pt1 = obj.vts[vti[j]].point;
				glm::vec3 pt2 = (j == vsize - 1 ? obj.vts[vti[0]].point : obj.vts[vti[j + 1]].point);
				zbuf += pt1.z;
				if (pt1.y < pt2.y)
				{
					swap(pt1, pt2);
				}
				ET_node edge;
				edge.dy = floor(pt1.y) - floor(pt2.y);
				if (edge.dy <= 0)
				{
					continue;
				}
				edge.x = pt1.x;
				edge.poly_id = polygon->poly_id;
				edge.dx = -(pt1.x - pt2.x) / (pt1.y - pt2.y);
				edge.y_max = pt1.y;
				edge.y_min = pt2.y;
				edge.poly = polygon;
				ET.et[floor(pt1.y)].push_back(edge);
				ymi = min(pt2.y, ymi);
				yma = max(pt1.y, yma);
			}
			//构建分类多边形表
			polygon->dy = floor(yma) - floor(ymi);
			if (polygon->dy > 0 && yma > 0 && ymi < height)
			{
				glm::vec3 v = obj.vts[face.vti[0]].point;
				polygon->a = face.normal.x;
				polygon->b = face.normal.y;
				polygon->c = face.normal.z;
				polygon->d = -(polygon->a*v.x + polygon->b*v.y + polygon->c*v.z);
				zbuf /= obj.faces[i].vti.size();
				polygon->z = zbuf;
				//使用深度进行作色
				float  tmp = (polygon->z - minpz) / (max_minpz);
				polygon->color.r = tmp;
				polygon->color.g = tmp;
				polygon->color.b = tmp;
				/*可使下面代码通过法线方向作色*/
				/*float tmp = dot(face.normal, glm::vec3(0, 0, 1));
				if (tmp < 0)
				{
				tmp = -tmp;
				}
				polygon->color.r = tmp;
				polygon->color.g = tmp;
				polygon->color.b = tmp;*/
				if (PT.pt->next == NULL)
				{
					PT.pt->next = polygon;
				}
				else
				{
					PT_node *tmp = NULL;
					tmp = PT.pt->next;
					PT.pt->next = polygon;
					polygon->next = tmp;
				}
			}
		}
	}
	else
	{
		ET.et.clear();
		ET.et.resize(height);
		int faces_size = obj.faces.size();
		for (int i = 0; i < faces_size; ++i)
		{
			float ymi = 9999, yma = -9999;
			Face& face = obj.faces[i];
			PT_node* polygon = new PT_node();
			polygon->next = NULL;
			polygon->poly_id = i;
			glm::vec3 v1 = obj.vts[face.vti[0]].point;
			float zbuf = 0;
			const vector<int>& vti = obj.faces[i].vti;
			for (int j = 0, vsize = vti.size(); j < vsize; ++j)
			{
				glm::vec3 pt1 = obj.vts[vti[j]].point;
				glm::vec3 pt2 = (j == vsize - 1 ? obj.vts[vti[0]].point : obj.vts[vti[j + 1]].point);
				zbuf += pt1.z;
				if (pt1.y < pt2.y)
				{
					swap(pt1, pt2);
				}
				ET_node edge;
				edge.dy = floor(pt1.y) - floor(pt2.y);
				if (edge.dy <= 0)
				{
					continue;
				}
				edge.x = pt1.x;
				edge.poly_id = polygon->poly_id;
				edge.dx = -(pt1.x - pt2.x) / (pt1.y - pt2.y);
				edge.y_max = pt1.y;
				edge.y_min = pt2.y;
				edge.poly = polygon;
				ET.et[floor(pt1.y)].push_back(edge);
				ymi = min(pt2.y, ymi);
				yma = max(pt1.y, yma);
			}
			//构建分类多边形表
			polygon->dy = floor(yma) - floor(ymi);
			if (polygon->dy > 0 && yma > 0 && ymi < height)
			{
				glm::vec3 v = obj.vts[face.vti[0]].point;
				polygon->a = face.normal.x;
				polygon->b = face.normal.y;
				polygon->c = face.normal.z;
				polygon->d = -(polygon->a*v.x + polygon->b*v.y + polygon->c*v.z);
				zbuf /= obj.faces[i].vti.size();
				polygon->z = zbuf;
				//使用深度进行作色
				/*float  tmp = (polygon->z - minpz) / (max_minpz);
				polygon->color.r = tmp;
				polygon->color.g = tmp;
				polygon->color.b = tmp;*/
				/*可使下面代码通过法线方向作色*/
				float tmp = dot(face.normal, glm::vec3(0, 0, 1));
				if (tmp < 0)
				{
					tmp = -tmp;
				}
				polygon->color.r = tmp;
				polygon->color.g = tmp;
				polygon->color.b = tmp;
				if (PT.pt->next == NULL)
				{
					PT.pt->next = polygon;
				}
				else
				{
					PT_node *tmp = NULL;
					tmp = PT.pt->next;
					PT.pt->next = polygon;
					polygon->next = tmp;
				}
			}
		}
	}
	

}

//将obj的坐标位置适应屏幕空间
void Interval_scanline::Fit_screen(OBJ & obj)
{
	glm::vec3 p1(999, 999, 999);
	glm::vec3 p2(-999, -999, -999);
	glm::vec3 p3(0.0, 0.0, 0.0);
	int vertex_num = obj.vts.size();
	for (int i = 0; i < vertex_num; ++i)
	{
		const glm::vec3& vertex = obj.vts[i].point;
		p1.x = min(p1.x, vertex.x); p1.y = min(p1.y, vertex.y); p1.z = min(p1.z, vertex.z); p2.x = max(p2.x, vertex.x); p2.y = max(p2.y, vertex.y); p2.z = max(p2.z, vertex.z);
	}
	p3.x = (p1.x + p2.x) / 2; p3.y = (p1.y + p2.y) / 2; p3.z = (p1.z + p2.z) / 2;
	float wh = p2.x - p1.x, ht = p2.y - p1.y, len = max(wh, ht);
	float s = min(width, height) / len;
	s *= 0.8;
	for (int i = 0; i < vertex_num; ++i)
	{
		glm::vec3& p = obj.vts[i].point;
		p.x = (p.x - p3.x)*s + width / 2;
		p.y = (p.y - p3.y)*s + height / 2;
		p.z = (p.z - p3.z)*s;
		if (maxpz < p.z)
		{
			maxpz = p.z;
		}
		if (minpz > p.z)
		{
			minpz = p.z;
		}
	}
	if (maxpz - minpz != 0)
	{
		max_minpz = maxpz - minpz;
	}
	else
	{
		max_minpz = 1;
	}
}