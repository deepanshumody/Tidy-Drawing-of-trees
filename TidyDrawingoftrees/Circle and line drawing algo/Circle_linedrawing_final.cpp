#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

// Center of the cicle = (xc,yc)
int xc , yc;

// Initialize radius of circle
int r;

// Initialize coordinates for end points of line
int x1, z1, x2, z2;



// Plot eight points using circle's symmetrical property
void plot_point(int x, int y)
{
  glBegin(GL_POINTS);
  glVertex2i(xc+x, yc+y);
  glVertex2i(xc+x, yc-y);
  glVertex2i(xc+y, yc+x);
  glVertex2i(xc+y, yc-x);
  glVertex2i(xc-x, yc-y);
  glVertex2i(xc-y, yc-x);
  glVertex2i(xc-x, yc+y);
  glVertex2i(xc-y, yc+x);
  glEnd();
}

// Function to draw a circle using bresenham's
// circle drawing algorithm
void bresenham_circle(int r, int xc, int yc)
{
  int x=0,y=r;
  int hk=1-r;
  int deltaE = 3;
  int deltaSE = -2 * r + 5;

  /* Plot the points */
  /* Plot the first point */
  plot_point(x,y);
  int k;
  /* Find all vertices till x=y */
  while(x < y)
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
    
    plot_point(x,y);
  }
  glFlush();
}

void draw_pixel(int x, int y)
{
    // Draws the point by specifying the primitive in glBegin 
    // and specifying vertex coordinates
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void draw_line(int x1, int x2, int y1, int y2) {
	int dx, dy, d, incrE, incrNE, incrSE, incrS;
	int x, y,xtemp,ytemp;
	if (x2 < x1)
	{
		xtemp = x2;
		x2 = x1;
		x1 = xtemp;

		ytemp = y2;
		y2 = y1;
		y1 = ytemp;

	}

	dx = x2 - x1;
	dy = y2 - y1;
	float m = (float)dy / dx;
	printf("%f %d", m, dy);
	if (m < 0 && m >= -1)
	{
		d = 2 * dy + dx;

		incrE = 2 * dy;
		incrSE = 2 * (dy + dx);
		x = x1;
		y = y1;
		draw_pixel(x, y);
		while (x < x2) {
			if (d <= 0) {
				d += incrSE;
				x++;
				y--;
			}
			else {
				d += incrE;
				x++;
			}
			draw_pixel(x, y);
		}
	}
	if (m <= 1 && m >= 0)
	{
		d = 2 * dy - dx;

		incrE = 2 * dy;
		incrNE = 2 * (dy - dx);
		x = x1;
		y = y1;
		draw_pixel(x, y);
		while (x < x2) {
			if (d <= 0) {
				d += incrE;
				x++;
			}
			else {
				d += incrNE;
				x++;
				y++;
			}
			draw_pixel(x, y);
		}
	}
	if (m > 1)
	{
		d = 2 * dy - dx;
		incrE = 2 * dx;
		incrNE = 2 * (dx - dy);
		x = x1;
		y = y1;
		draw_pixel(x, y);
		while (y < y2) {
			if (d <= 0) {
				d += incrE;
				y++;
			}
			else {
				d += incrNE;
				x++;
				y++;
			}
			draw_pixel(x, y);
		}
	}

	if (m < -1)
	{
		d = dy + 2 * dx;

		incrS = 2 * dx;
		incrSE = 2 * (dy + dx);
		x = x1;
		y = y1;
		draw_pixel(x, y);
		while (y > y2) {
			if (d <= 0) {
				d += incrS;
				y--;
			}
			else {
				d += incrSE;
				y--;
				x++;
			}
			draw_pixel(x, y);
		}
	}

}
// Function to draw line and circle


void concentric_circles(void)
{
  /* Clears buffers to preset values */
  glClear(GL_COLOR_BUFFER_BIT);
  
  bresenham_circle(r, xc, yc);
  draw_line(x1, x2, z1, z2);
  glFlush();
}

void Init()
{
  /* Set clear color to white */
  glClearColor(1.0,1.0,1.0,0);
  /* Set fill color to black */
  glColor3f(0.0,0.0,0.0);
  /* glViewport(0 , 0 , 640 , 480); */
  /* glMatrixMode(GL_PROJECTION); */
  /* glLoadIdentity(); */
  gluOrtho2D(0 , 640 , 0 , 480);
}

void main(int argc, char **argv)
{
  printf("Enter radius,xc,yc\n");
  scanf_s("%d %d %d", &r, &xc, &yc);
  printf("Enter end point coordinates of line x1,y1,x2,y2\n");
  scanf_s("%d %d %d %d", &x1, &z1, &x2, &z2);
  /* Initialise GLUT library */
  glutInit(&argc,argv);
  /* Set the initial display mode */
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  /* Set the initial window position and size */
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  /* Create the window with title "DDA_Line" */
  glutCreateWindow("bresenham_circle");
  /* Initialize drawing colors */
  Init();
  /* Call the displaying function */
  glutDisplayFunc(concentric_circles);
  /* Keep displaying untill the program is closed */
  glutMainLoop();
}