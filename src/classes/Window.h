#ifndef WINDOW_H
#define WINDOW_H
#include <iostream>
#include <list>
#include "../help_func.h"
#include "Observer.h"
#include "Figure.h"
#include "Figure_3D.h"
#include "Figure_2D.h"
using namespace std;
class Window
{
private:
    int width;
    int height;
    char * win_name;
    Observer * obs = nullptr;
    list<Figure *> figures;
public:
    Window();
    Window(int w, int h, char * w_n, Observer & o);
    void init();
    void draw();
    void add_figure(double **vert, int vert_size, int col);
    void add_figure(double **vert, int vert_size, int **ed,
                    int e_s, int * e_c_n, const int *colors,
                    double world_matrix[4][4]);
    void remove_figure(int index);
    ~Window();
};


#endif
