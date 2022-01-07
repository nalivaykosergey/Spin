#ifndef FIGURE_3D_H
#define FIGURE_3D_H

#include <iostream>
#include "graphics.h"
#include "Figure.h"
#include "Observer.h"

using namespace std;

class Figure_3D: public Figure
{
private:
    bool * visible_state = nullptr;
protected:
    int ** edges = nullptr;
    int edges_size;
    int *  edges_coord_num = nullptr;
    int * edges_colors = nullptr;
    Observer * obs = nullptr;
public:
    Figure_3D();
    Figure_3D(double **vert, int vert_size, int ** edges, int edges_size,
              const int * edges_coord_num, const int * colors);
    Figure_3D(const Figure_3D &fig);
    Figure_3D & operator = (const Figure_3D & fig);
    ~Figure_3D() override;
    void draw() override;
    void link(Observer & o);
    void displace(double matr[4][4]);
private:
    double ** to_observer();
    void visible_alg1(double ** obs_view);
    void visible_alg2(double ** obs_view);
    void fill_area(int ** vert, int * edge, int edge_no);
    int ** render();

};


#endif
