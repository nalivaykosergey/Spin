#ifndef FIGURE_H
#define FIGURE_H


class Figure
{
protected:
    double ** vertexes = nullptr;
    int vert_size;
    int coord_num;
public:
    Figure();
    Figure(double ** vert, int v_s, int c_n);
    Figure(const Figure & fig);
    Figure & operator = (const Figure & fig);
    virtual void draw() = 0;
    virtual ~Figure();
};


#endif
