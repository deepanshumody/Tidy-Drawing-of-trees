## Tidy Drawing of trees
Implementation of Bresenham's Circle and line drawing algorithms and Tidier Drawings of Trees by Reingold and Tilford.

### Compile- g++ main.cpp -lglut -lGL -lGLU

Circle and line drawing folder consists of 1 file: 
```
1. Circle_linedrawing_final.cpp: Draws a circle taking in input radius, center coordinates and a line taking in end point 
   coordinates  
```
Tree drawing folder consists of 3 files:  
```
1. bst.h: Creates a simple binary tree to be used for. Returns the root of the constructed tree to main()  
2. main.cpp: Does the implementation of Tidy Drawings and then calls functions in draw.h for openGL display  
3. draw.h: draws the tree using openGL. The nodes are drawn using Midpoint circle drawing and lines using Bresenham's line 
   drawing algorithm.  
```
  
`PROJECT MEMBERS- Deepanshu Mody, Mahesh Swaminathan, Osama Fattah`

### Real World run time
![Capture12](https://user-images.githubusercontent.com/39831386/141995931-919e4758-1971-4904-8add-4c43bd98594e.PNG)
![Capture11](https://user-images.githubusercontent.com/39831386/141995942-d8e1aa5c-6475-417e-ac9a-5bb96f2c8f1f.PNG)

### Screenshots
![Capture2](https://user-images.githubusercontent.com/39831386/141995801-abb04c8a-5ccf-4bb2-8c8b-c325b8cf40a4.PNG)
![Capture8](https://user-images.githubusercontent.com/39831386/141995849-f2352f4c-bd16-444c-a3b0-6c55cc301d5b.PNG)
![Capture10](https://user-images.githubusercontent.com/39831386/141995918-dfc16bf9-a4eb-4947-b0e5-eab7d946e736.PNG)



