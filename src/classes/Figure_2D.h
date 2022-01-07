#ifndef FIGURE_2D_H
#define FIGURE_2D_H

#include <iostream>
#include "Figure.h"
#include "graphics.h"

using namespace std;
class Figure_2D: public Figure
{
protected:
    int color;
public:
    Figure_2D();
    Figure_2D(double **vert, int vert_size, int col);
    Figure_2D(const Figure_2D &fig);
    Figure_2D & operator = (const Figure_2D & fig);
    void draw() override;
};


#endif
