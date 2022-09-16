implement of interval scan line 

Data structure：  
The data structure includes AET, ET, IPL, PT four structures.
PT is a linked list, which stores the information of the surface.
AET uses Vector<> to store AET structure nodes
ET uses Vector<Vector<>> to store ET structure nodes, which is convenient to quickly add edges to AET each time it passes through a scan line. The ET node has a pointer to the node in PT, which is convenient to quickly find this edge through the edge. Information about the face to which it belongs.
The IPL is a Vector<> structure, which is convenient for maintaining the information in the IPL.

The interval scanline algorithm is defined in Interval_scanline.cpp and Interval_scanline.h. It mainly includes the following functions:
(1) void Scan();//The main scan function of the interval scan line
(2) void Create_ET_PT(OBJ& obj);//Create ET,PT
(3) void Fit_screen(OBJ& obj);//Normalize point coordinates to screen space
(4) void Add_Edge_to_AET();//Every time you enter this scan line for operation, first add the edge in ET.et[y] of the y scan line to AET
(5) void Update_AET();//Update the edge data in AET

Results：

![xiaoguo](https://github.com/geekzzz/IntervalScanLine/blob/master/preview/2.png)  
Normal shading effect (contrast with depth shading later):
![xiaoguo](https://github.com/geekzzz/IntervalScanLine/blob/master/preview/6.png)  
![xiaoguo](https://github.com/geekzzz/IntervalScanLine/blob/master/preview/7.png)  
Other object effects (colors are represented by depth):
![xiaoguo](https://github.com/geekzzz/IntervalScanLine/blob/master/preview/3.png)  
![xiaoguo](https://github.com/geekzzz/IntervalScanLine/blob/master/preview/4.png)  
![xiaoguo](https://github.com/geekzzz/IntervalScanLine/blob/master/preview/5.png)  
This algorithm solves the problem of penetration and can be tested with obj. If you want to use the obj provided by me for penetration test, please use the depth value for coloring, otherwise the coloring will not look good due to the problem of the normal of the penetrating polygon. out the effect. The solution effect is as follows:
![guanchuan](https://github.com/geekzzz/IntervalScanLine/blob/master/preview/1.png)  
