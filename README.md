�����ҵ�ͼ��ѧ����ɨ������ҵ
һ����Ŀ�������������ã�
1. ����Ŀʹ��WIN 10 + VS 2017������ʹ�õĵ�������ΪGLUT�Լ�GLM�⡣GLM���ѷ���Ŀ¼�У�����Ҫ���á�GLUT���Ѿ����á�  
2.��Ŀģ���ļ���������Ŀmodels�ļ����У�����6��obj�ļ�������Ҫʹ�ø���obj�ļ����Լ���ӣ�����·����main.cpp�ļ���path���޸ģ�ʹ�ÿ���̨���˼򵥵Ľ����������档  
�������ݽṹ��  
1.���ݽṹ����AET��ET��IPL��PT�ĸ��ṹ��  
���У�PTΪ�����洢�����Ϣ��AETʹ��Vector<>�洢AET�ṹ��ڵ㣬����ʹ��STL��������ETʹ��Vector<Vector<>>�洢ET�ṹ��ڵ㣬����ÿ�ξ���һ��ɨ����ʱ�����ٽ��߼���AET�У�����ET�ڵ���ӵ��ָ��ָ��PT�еĽڵ㣬�������ͨ���߲������������ڵ������Ϣ��IPLΪVector<>�ṹ������ά��IPL�е���Ϣ��  
�������ݽṹ������Ŀ�е�AET.h��ET.H��IPL.H��PT.h�ļ��в鿴��  
2.����ɨ�����㷨��Interval_scanline.cpp�Լ�Interval_scanline.h�ж��塣��Ҫ�������º�����  
��1��void Scan();//����ɨ������Ҫɨ�躯��  
��2��void Create_ET_PT(OBJ& obj);//����ET,PT  
��3��void Fit_screen(OBJ& obj);//���������һ������Ļ�ռ�  
��4��void Add_Edge_to_AET();//ÿ�ν������ɨ���߽��в���ʱ���Ƚ�yɨ���ߵ�ET.et[y]�еı߼���AET��  
��5��void Update_AET();//����AET�бߵ�����  
����ʹ�ü�Ч��ʾ����    
1. ʹ��OpenGL���л�����ʾʱ,������Ƭ����ɫ��RGBֵ������Ƭ����ȵ�ֵ�Ĺ�һ����ֵ���б�ʾ�����Խ���ɫԽǳ��  
2.���ȿ��Ը�����ʾѡ�����6�в�ͬobj��Ȼ�����ѡ����ʾ���桢������棬Ȼ����������и���������ʹ�õ�ʱ�䣬ʾ����ͼ������obj��ʹ�ó�����н�һ��������Ч��ͼ���£�  
![xiaoguo](https://github.com/geekzzz/IntervalScanLine/blob/master/preview/2.png)  
������ɫЧ����  
![xiaoguo](https://github.com/geekzzz/IntervalScanLine/blob/master/preview/6.png)  
![xiaoguo](https://github.com/geekzzz/IntervalScanLine/blob/master/preview/7.png)  
��������Ч����  
![xiaoguo](https://github.com/geekzzz/IntervalScanLine/blob/master/preview/3.png)  
![xiaoguo](https://github.com/geekzzz/IntervalScanLine/blob/master/preview/4.png)  
![xiaoguo](https://github.com/geekzzz/IntervalScanLine/blob/master/preview/5.png)  
3.���㷨����˹ᴩ�����⣬����ʹ��obj���в��ԣ����Ҫʹ�����ṩ��obj���йᴩ���ԣ���ʹ�����ֵ������ɫ���������ڹᴩ�Ķ���η������⣬�����ɫ���ܺܺõĿ���Ч�����ᴩ���Ч����ͼ��  
![guanchuan](https://github.com/geekzzz/IntervalScanLine/blob/master/preview/1.png)  