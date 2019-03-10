#include "Interval_scanline.h"
#include <fstream>


using namespace std;


//����ɨ�����㷨
void Interval_scanline::Scan()
{
	//����ߵ�x = 0����edge
	left_x.x = 0;
	left_x.dx = 0;
	left_x.poly_id = -100;//�豳��polygon��poly_idΪ-100
	left_x.y_max = height - 1;
	left_x.y_min = 0;
	left_x.now_x = 0;
	left_x.poly = Back_ground;
	//���ұߵ�x = width����edge
	right_x.x = width - 1;
	right_x.dx = 0;
	right_x.poly_id = -100;
	right_x.y_max = height - 1;
	right_x.y_min = 0;
	right_x.now_x = width - 1;
	right_x.poly = Back_ground;
	//����polygon
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
	//ɨ����ɨ��
	for (y = ymax; y > ymin; --y)
	{
		IPL.ipl.clear();
		Add_Edge_to_AET();
		sort(AET.aet.begin(), AET.aet.end(), mysortfunc_edge);
		Back_ground->inout_flag = 2;//back_ground�Ƚ����⣬��flag��Ϊ2������ά��iplʱ����
		IPL.ipl.push_back(*(Back_ground));
		//����AET
		for (e1 = AET.aet.begin(), e2 = e1 + 1; e2 != AET.aet.end();)
		{
			//���inou_flagΪ0,����IPL��
			if (e1->poly->inout_flag == 0)
			{
				IPL.ipl.push_back(*(e1->poly));
				e1->poly->inout_flag = 1;
			}
			//���inou_flagΪ1,��IPL��ɾ��
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
			float lmax = -9999, rmax = -9999;//�жϹᴩ�������¼e1��e2��������
			float ldep, rdep;//ÿ�μ�������
			float zmax = -9999;//���е�������
			glm::vec3 color(0, 0, 0);
			int l_poly_id = -100, r_poly_id = -100;
			float l_poly_a = Back_ground->a, l_poly_b = Back_ground->b, l_poly_c = Back_ground->c, l_poly_d = Back_ground->d, r_poly_a = Back_ground->a, r_poly_b = Back_ground->b, r_poly_c = Back_ground->c, r_poly_d = Back_ground->d;
			glm::vec3 l_poly_color(0, 0, 0);
			glm::vec3 r_poly_color(0, 0, 0);
			//������ǰIPL���жϹᴩ���
			for (auto it = IPL.ipl.begin(); it != IPL.ipl.end(); ++it)
			{
				if (it->poly_id == -100)
				{
					continue;
				}
				//���㵱ǰ�����ֵ
				ldep = ((it->a * e1->now_x) + (it->b * y) + (it->d)) / (-it->c);
				rdep = ((it->a * e2->now_x) + (it->b * y) + (it->d)) / (-it->c);
				//ͨ���Ƚϣ���¼��ǰe1��e2�����У�IPL�е�����e1�ģ�now_x,y���Լ�e2��(now_x,y)���ֱ��������ֵ
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
				//ͨ���Ƚϣ���¼��ǰe1��e2�����У�IPL�е�����e1�ģ�now_x,y���Լ�e2��(now_x,y)���ֱ��������ֵ
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

			if (l_poly_id != r_poly_id)//ͨ��֮ǰ��¼�µ�������ֵ��ID,�ж��Ƿ�ᴩ
			{
				//��������ƽ��ķ��̣������yֵȷ��ʱ����ƽ�潻�ߴ���x��ֵ��ʹ�ý������xֵ�Թᴩ������зָ�ֱ������ɫ
				float cross_x = (-(r_poly_c * l_poly_b * y) + (l_poly_c * r_poly_b * y) - (r_poly_c * l_poly_d) + (l_poly_c * r_poly_d)) / ((r_poly_c * l_poly_a) - (l_poly_c * r_poly_a));

				if (cross_x >= e1->now_x && cross_x <= e2->now_x)//�ж��Ƿ񳬳������ߵķ�Χ������³����
				{
					setcolor(floor(e1->now_x), floor(cross_x), l_poly_color);//���ùᴩ��߲��ֵ���ɫ
					setcolor(floor(cross_x), floor(e2->now_x), r_poly_color);//���ùᴩ�ұ߲��ֵ���ɫ
				}
				else
				{
					setcolor(floor(e1->now_x), floor(e2->now_x), color);//ֱ��������ɫ
				}
			}
			else//δ�ᴩ���
			{
				setcolor(floor(e1->now_x), floor(e2->now_x), color);//ֱ��e1��e2����ɫ
			}
			++e1;//�ƶ�������
			++e2;//�ƶ�������
		}

		Update_AET();//��AET���и���
	}

}

//��ET��y_maxΪy��ֵ������AET��
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
//����AET
void Interval_scanline::Update_AET()
{
	//����AET��
	for (auto it = AET.aet.begin(); it != AET.aet.end();)
	{
		it->poly->inout_flag = 0;
		//���ɨ����С���߶ε�y_min,�Ƴ�
		if (it->y_min >= y - 1)
		{
			it = AET.aet.erase(it);
		}
		//now_x���£�now_xΪ��һ��ɨ���� 
		else
		{
			it->now_x = it->now_x + it->dx;
			++it;
		}
	}
}

//��AET����sort��������
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
//��x1��x2���괦����ɫ�������ã�yֵ������Interval_scanline�ڣ�ʵʱ����
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
//����PT,ET��
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
			//�����������α�
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
				//ʹ����Ƚ�����ɫ
				float  tmp = (polygon->z - minpz) / (max_minpz);
				polygon->color.r = tmp;
				polygon->color.g = tmp;
				polygon->color.b = tmp;
				/*��ʹ�������ͨ�����߷�����ɫ*/
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
			//�����������α�
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
				//ʹ����Ƚ�����ɫ
				/*float  tmp = (polygon->z - minpz) / (max_minpz);
				polygon->color.r = tmp;
				polygon->color.g = tmp;
				polygon->color.b = tmp;*/
				/*��ʹ�������ͨ�����߷�����ɫ*/
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

//��obj������λ����Ӧ��Ļ�ռ�
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