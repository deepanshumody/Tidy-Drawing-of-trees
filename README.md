# Tidy-Drawing-of-trees
Implementation of Bresenham's Circle and line drawing algorithms and Tidier Drawings of Trees by Reingold and Tilford.

Compile: g++ main.cpp -lglut -lGL -lGLU

Circle and line drawing folder consists of 1 file:  
	1. Circle_linedrawing_final.cpp: Draws a circle taking in input radius, center coordinates and a line taking in end point coordinates  
  
Tree drawing folder consists of 3 files:  
	1. bst.h: Creates a simple binary tree to be used for. Returns the root of the constructed tree to main()  
	2. main.cpp: Does the implementation of Tidy Drawings and then calls functions in draw.h for openGL display  
	3. draw.h: draws the tree using openGL. The nodes are drawn using Midpoint circle drawing and lines using Bresenham's line drawing algorithm.  
  
  
PROJECT MEMBERS- Deepanshu Mody, Mahesh Swaminathan, Osama Fattah
