/**
    Drawing a 3d shape using the graphics.h library.
    @author Nalivayko Sergey
    @version 1.1 1/15/21
*/
#include <iostream>
#include <fstream>
#include "help_func.h"
#include "classes/Window.h"
#include "classes/Observer.h"
#include "classes/Observer.h"
#include "classes/Figure_2D.h"
#include "classes/Figure_3D.h"
using namespace std;

#define Cube 0
#define Pyramid 0
#define MMM 1


int main() {
	
#if Pyramid
	double **vert_3d = new double*[5];
    int vert_3d_size;
    int ** edges_3d = new int*[5];
    int edges_3d_size;
    int * colors = new int[5];
    int * n = new int[5];
    string filename = "figures/pyramid.fig";
    double world_matrix[4][4]
        {
                { 1, 0, 0, 0 },
                { 0, 1, 0, 0},
                { 0, 0, 1, 0 },
                { 0, 0, -100, 1 }
        };
#endif
#if Cube
	double **vert_3d = new double*[5];
    int vert_3d_size;
    int ** edges_3d = new int*[5];
    int edges_3d_size;
    int * colors = new int[5];
    int * n = new int[5];
    string filename = "figures/cube.fig";
    double world_matrix[4][4]
        {
                { 1, 0, 0, 0 },
                { 0, 1, 0, 0},
                { 0, 0, 1, 0 },
                { -100, -100, -100, 1 }
        };
#endif

#if MMM
	double **vert_3d = new double*[20];
    int vert_3d_size;
    int ** edges_3d = new int*[12];
    int edges_3d_size;
    int * colors = new int[12];
    int * n = new int[12];
    string filename = "figures/dodecahedron.fig";
    double world_matrix[4][4]
        {
                { 1, 0, 0, 0 },
                { 0, 1, 0, 0},
                { 0, 0, 1, 0 },
                {  0, 0, -125, 1 }
        };
#endif
    
    Observer obs(500, -45, 45);
    read_data(filename, vert_3d, vert_3d_size, edges_3d, edges_3d_size, n, colors);    
	Window win(360, 360, "Figures", obs);
    win.init();
    win.add_figure(vert_3d, vert_3d_size, edges_3d, edges_3d_size,
                   n, colors, world_matrix);
    win.draw();
	
	
    while(true)
    {
    	 Sleep(75);
    	 obs.add_to_teta(3);
    	 obs.add_to_fi(3);
    	 cleardevice();
		 win.draw();
	}
	getch();
    for(int i = 0; i < vert_3d_size; i++)
        delete [] vert_3d[i];
    delete [] vert_3d;
    for(int i = 0; i < edges_3d_size; i++)
        delete [] edges_3d[i];
    delete [] edges_3d;
    delete [] colors;
    delete [] n;
    return 0;
}
