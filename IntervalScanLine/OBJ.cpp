#include "OBJ.h"

using namespace std;



bool OBJ::load(const std::string & path)
{
	ifstream file(path);
	string type;
	if (!file.is_open())
	{
		return false;
	}
	//加载顶点坐标

	if (lookat == 0)
	{
		while (file >> type)
		{
			if (type == "v")
			{
				Vertex v;
				file >> v.point.x >> v.point.y >> v.point.z;
				vts.push_back(v);
			}

			else if (type == "f")
			{
				Face face;
				int vi, ti, ni;
				int faceIndex = faces.size();
				while (true)
				{
					char c = file.get();
					if (c == ' ') continue;
					else if (c == '\n' || c == EOF) break;
					else file.putback(c);
					file >> vi;
					char splitter = file.get();
					ni = 0;
					if (splitter == '/')
					{
						splitter = file.get();
						if (splitter == '/')
						{
							file >> ni;
						}
						else
						{
							file.putback(splitter);
							file >> ti;
							splitter = file.get();
							if (splitter == '/')
							{
								file >> ni;
							}
							else file.putback(splitter);
						}
					}
					else file.putback(splitter);
					face.vti.push_back(vi - 1);
					face.nmi.push_back(ni - 1);
				}
				//计算法向量
				if (face.vti.size() > 2)
				{
					glm::vec3 &a = vts[face.vti[0]].point, &b = vts[face.vti[1]].point, &c = vts[face.vti[2]].point, normal = OBJ::normalize(OBJ::cross(b - a, c - b));
					face.normal = normal;
					faces.push_back(face);
				}
			}
			else if (type == "vn")
			{
				glm::vec3 vn;
				file >> vn.x >> vn.y >> vn.z;
				normals.push_back(vn);
			}
		}
	}
	else if (lookat == 1)
	{
		while (file >> type)
		{
			if (type == "v")
			{
				Vertex v;
				file >> v.point.z >> v.point.y >> v.point.x;
				vts.push_back(v);
			}

			else if (type == "f")
			{
				Face face;
				int vi, ti, ni;
				int faceIndex = faces.size();
				while (true)
				{
					char c = file.get();
					if (c == ' ') continue;
					else if (c == '\n' || c == EOF) break;
					else file.putback(c);
					file >> vi;
					char splitter = file.get();
					ni = 0;
					if (splitter == '/')
					{
						splitter = file.get();
						if (splitter == '/')
						{
							file >> ni;
						}
						else
						{
							file.putback(splitter);
							file >> ti;
							splitter = file.get();
							if (splitter == '/')
							{
								file >> ni;
							}
							else file.putback(splitter);
						}
					}
					else file.putback(splitter);
					face.vti.push_back(vi - 1);
					face.nmi.push_back(ni - 1);
				}
				//计算法向量
				if (face.vti.size() > 2)
				{
					glm::vec3 &a = vts[face.vti[0]].point, &b = vts[face.vti[1]].point, &c = vts[face.vti[2]].point, normal = OBJ::normalize(OBJ::cross(b - a, c - b));
					face.normal = normal;
					faces.push_back(face);
				}
			}
			else if (type == "vn")
			{
				glm::vec3 vn;
				file >> vn.x >> vn.y >> vn.z;
				normals.push_back(vn);
			}
		}
	}
	else if(lookat == 2)
	{
		while (file >> type)
		{
			if (type == "v")
			{
				Vertex v;
				file >> v.point.x >> v.point.z >> v.point.y;
				vts.push_back(v);
			}

			else if (type == "f")
			{
				Face face;
				int vi, ti, ni;
				int faceIndex = faces.size();
				while (true)
				{
					char c = file.get();
					if (c == ' ') continue;
					else if (c == '\n' || c == EOF) break;
					else file.putback(c);
					file >> vi;
					char splitter = file.get();
					ni = 0;
					if (splitter == '/')
					{
						splitter = file.get();
						if (splitter == '/')
						{
							file >> ni;
						}
						else
						{
							file.putback(splitter);
							file >> ti;
							splitter = file.get();
							if (splitter == '/')
							{
								file >> ni;
							}
							else file.putback(splitter);
						}
					}
					else file.putback(splitter);
					face.vti.push_back(vi - 1);
					face.nmi.push_back(ni - 1);
				}
				//计算法向量
				if (face.vti.size() > 2)
				{
					glm::vec3 &a = vts[face.vti[0]].point, &b = vts[face.vti[1]].point, &c = vts[face.vti[2]].point, normal = OBJ::normalize(OBJ::cross(b - a, c - b));
					face.normal = normal;
					faces.push_back(face);
				}
			}
			else if (type == "vn")
			{
				glm::vec3 vn;
				file >> vn.x >> vn.y >> vn.z;
				normals.push_back(vn);
			}
		}
	}
	
	file.close();
	cout << "模型顶点数：" << vts.size() << endl;
	cout << "模型面片数：" << faces.size() << endl;
	return true;
}

glm::vec3 OBJ::cross(const glm::vec3 & u, const glm::vec3 & v)
{
	return glm::vec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}

glm::vec3  OBJ::normalize(const glm::vec3 &u)
{
	return u * (1.0f / sqrt(u.x * u.x + u.y * u.y + u.z * u.z));
}