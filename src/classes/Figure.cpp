#include "Figure.h"

Figure::Figure() {
    vert_size = 0;
    coord_num = 0;
}

Figure::Figure(double **vert, int v_s, int c_n) {
    //copy data + add 1 to end
    vert_size = v_s;
    coord_num = c_n;
    vertexes = new double*[vert_size];
    for(int i = 0; i < vert_size; i++)
    {
        vertexes[i] = new double[coord_num + 1];
        for(int j = 0; j < coord_num; j++)
        {
            vertexes[i][j] = vert[i][j];
        }
        vertexes[i][coord_num] = 1;
    }
}

Figure::~Figure() {
    if(vertexes)
    {
        for(int i = 0; i < vert_size; i++)
            delete [] vertexes[i];
        delete [] vertexes;
    }
}

Figure::Figure(const Figure &fig) {
    if(vertexes)
    {
        for(int i = 0; i < vert_size; i++)
            delete [] vertexes[i];
        delete [] vertexes;
    }
    vert_size = fig.vert_size;
    coord_num = fig.coord_num;
    vertexes = new double*[vert_size];
    for(int i = 0; i < vert_size; i++)
    {
        vertexes[i] = new double[coord_num + 1];
        for(int j = 0; j <= coord_num; j++)
        {
            vertexes[i][j] = fig.vertexes[i][j];
        }
    }
}

Figure & Figure::operator=(const Figure &fig) {
    if(this == &fig)
        return *this;
    if(vertexes)
    {
        for(int i = 0; i < vert_size; i++)
            delete [] vertexes[i];
        delete [] vertexes;
    }
    vert_size = fig.vert_size;
    coord_num = fig.coord_num;
    vertexes = new double*[vert_size];
    for(int i = 0; i < vert_size; i++)
    {
        vertexes[i] = new double[coord_num + 1];
        for(int j = 0; j <= coord_num; j++)
        {
            vertexes[i][j] = fig.vertexes[i][j];
        }
    }
    return *this;
}

