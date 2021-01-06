#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <climits>
#include <queue>
#include <math.h>
#include <string.h>
using namespace std;

#define RADIUS 10								/*! \def radius of circle*/
#define SCALE 30								/*!Y \def coordinate Scaling factor*/
#define WINDOW 800							    /*! \def Size of Window*/
													
struct Node *temproot = NULL;					//!temp root of tree

//!Initialize OpenGL
void init(void){
    glClearColor(0,0,0,0.0);						//set display-window background color to black
    glMatrixMode(GL_PROJECTION);					//set projection paramaters
    gluOrtho2D(0.0,300.0,0.0,300.0);
}

//!PlotPixel at given coordinate
void PlotPixel(int x, int y){
    y = WINDOW/2 - y;							//moving origin to top-left, default is bottom-left
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush(); 									//executes all OpenGL functions as quickly as possible
}




 void draw_line(int x0, int y0, int x1, int y1, int dir) {

	if(x0 > x1){
		swap(x0, x1);
		swap(y0, y1);
	}
	int dx=x1-x0, dy=y1-y0;
	int d = 2*dy - dx;
	int incrE=2*dy, incrNE=2*(dy-dx);
	int x=x0, y=y0;
	PlotPixel(x, y);

	while(x < x1){
		if(d<=0){								//choose E
			d = d + incrE;
			if(dir) y--;						//if left child decrement y
		}
		else{									//choose NE
			d = d + incrNE;
			if(!dir) y++;						
		}
		x++;
		PlotPixel(x, y);
	}
}

 void connectNodes(int x1, int y1, int x2, int y2, int check)
{	
    float xl, xr, yl, yr;

    //!Distance between two nodes.
    float dist = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));

    //Locate Perimeter point of node to draw line from.
    xl = x1 + RADIUS*(x2-x1)/dist;
    yl = y1 + RADIUS*(y2-y1)/dist;

    xr = x2 + RADIUS*(x1-x2)/dist;
    yr = y2 + RADIUS*(y1-y2)/dist;

    if(check)
	draw_line(xl, yl, xr, yr, 1);
	else
	draw_line(xl, yl, xr, yr, 0);

}


//!plot pixels based on a circle's symmetry
void plot_point(int xc, int yc, int x, int y)
{
  PlotPixel(xc+x, yc+y);
  PlotPixel(xc+x, yc-y);
  PlotPixel(xc+y, yc+x);
  PlotPixel(xc+y, yc-x);
  PlotPixel(xc-x, yc-y);
  PlotPixel(xc-y, yc-x);
  PlotPixel(xc-x, yc+y);
  PlotPixel(xc-y, yc+x);
}


//!Draw circle using midpoint circle algorithm
void draw_circle(int xc, int yc)
{
	int x = 0, y = RADIUS;
	int hk = 1 - RADIUS;
	int deltaE = 3;
	int deltaSE = -2 * RADIUS + 5;

	/* Plot the points */
	/* Plot the first point */
	plot_point(xc,yc, x, y);
	int k;
	/* Find all vertices till x=y */
	while (x < y)
	{
		if (hk < 0) /*select E*/
		{
			hk += deltaE;
			deltaE += 2;
			deltaSE += 2;
		}
		else
		{
			hk += deltaSE; /*Select SE*/
			deltaE += 2;
			deltaSE += 4;
			y--;
		}
		x++;

		plot_point(xc,yc, x, y);
	}
	glFlush();
}

//!function to convert integer to string
 string to_string(int n){
    string str;
    while(n){
        str.push_back(n%10 + 48);
        n = n/10;
    }
    reverse(str.begin(), str.end());
    return str;
}

//!Write the data inside the drawn node
void drawText(int data, int x0, int y0){
    glColor3f(0.0,1.0,0.0);                                         //change data color to green
	GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	y0 = WINDOW/2 - y0 - RADIUS/2;
	x0 = x0 - RADIUS/2;                                             //bring str to center of circle
	string str = to_string(data);
	glRasterPos2f(x0, y0);
	for(int i=0; i<str.size(); i++){
        glutBitmapCharacter(font_style, str[i]);
        //cout<<"print"<<str[i]<<" ";
	}
	//cout<<endl;
    glColor3f(0.0,0.0,1.0);											
}

void inorder(struct Node *root){
	//!Inorder traversal of tree
	if(root == NULL) return;
	if(root->parent == NULL) ;
	inorder(root->right);
	inorder(root->left);
	draw_circle(root->x - 50, (root->y)*SCALE + 130);
	drawText(root->data, root->x - 50, (root->y)*SCALE + 130);
	if(root->right){
	connectNodes(root->x - 50, (root->y)*SCALE + 130, (root->right)->x - 50, (root->right->y)*SCALE + 130, 0);
	}
	if(root->left){
	connectNodes(root->x - 50, (root->y)*SCALE + 130, (root->left)->x - 50, (root->left->y)*SCALE + 130, 1);
	}
	
}

void draw(){
	int x0, y0, x1, y1;
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);
    glPointSize(4.0);
	struct Node *root = temproot;
	inorder(root);	
}

void draw_main(struct Node *root, int argc, char *argv[]){

	temproot = root;								//temporarily holds root												
	glutInit(&argc,argv);							//initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//initialize display mode
    glutInitWindowSize(WINDOW, WINDOW);			
    glutInitWindowPosition(0, 0);					//Position of top-left corner
    glutCreateWindow("Binary trees");

    init();
    glutDisplayFunc(draw);

    glutMainLoop();				//display everything
	
}
