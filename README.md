区间扫描线
一、项目开发环境及配置：
1. 本项目使用WIN 10 + VS 2017开发，使用的第三方库为GLUT以及GLM库。GLM库已放在目录中，不需要配置。GLUT库已经配置。  
2.项目模型文件放置在项目models文件夹中，包括6个obj文件，若需要使用更多obj文件可自己添加，加载路径在main.cpp文件中path处修改，使用控制台做了简单的交互操作界面。  
二、数据结构：  
1.数据结构包括AET，ET，IPL，PT四个结构。  
其中，PT为链表，存储面的信息。AET使用Vector<>存储AET结构体节点，方便使用STL进行排序，ET使用Vector<Vector<>>存储ET结构体节点，方便每次经过一条扫描线时，快速将边加入AET中，其中ET节点中拥有指针指向PT中的节点，方便快速通过边查找这条边属于的面的信息。IPL为Vector<>结构，方便维护IPL中的信息。  
具体数据结构可在项目中的AET.h，ET.H，IPL.H，PT.h文件中查看。  
2.区间扫描线算法在Interval_scanline.cpp以及Interval_scanline.h中定义。主要包括如下函数：  
（1）void Scan();//区间扫描线主要扫描函数  
（2）void Create_ET_PT(OBJ& obj);//建立ET,PT  
（3）void Fit_screen(OBJ& obj);//将点坐标归一化到屏幕空间  
（4）void Add_Edge_to_AET();//每次进入此条扫描线进行操作时，先将y扫描线的ET.et[y]中的边加入AET中  
（5）void Update_AET();//更新AET中边的数据  
三、使用及效果示例：    
1. 使用OpenGL进行绘制显示时,各个面片的颜色的RGB值采用面片的深度的值的归一化的值进行表示（深度越深，颜色越浅）  
2.首先可以根据提示选择加载6中不同obj，然后可以选择显示正面、侧面或顶面，然后将输出过程中各个步骤所使用的时间，示例如图，更多obj可使用程序进行进一步操作，效果图如下：  
![xiaoguo](https://github.com/geekzzz/IntervalScanLine/tree/master/preview/2.png)  
法线着色效果（可与后面采用深度进行着色进行对比）：  
![xiaoguo](https://github.com/geekzzz/IntervalScanLine/tree/master/preview/6.png)  
![xiaoguo](https://github.com/geekzzz/IntervalScanLine/tree/master/preview/7.png)  
其他物体效果（颜色采用深度表示）：  
![xiaoguo](https://github.com/geekzzz/IntervalScanLine/tree/master/preview/3.png)  
![xiaoguo](https://github.com/geekzzz/IntervalScanLine/tree/master/preview/4.png)  
![xiaoguo](https://github.com/geekzzz/IntervalScanLine/tree/master/preview/5.png)  
3.该算法解决了贯穿的问题，可以使用obj进行测试，如果要使用我提供的obj进行贯穿测试，请使用深度值进行作色，否则由于贯穿的多边形法线问题，造成作色不能很好的看出效果。贯穿解决效果如图：  
![guanchuan](https://github.com/geekzzz/IntervalScanLine/tree/master/preview/1.png)  
