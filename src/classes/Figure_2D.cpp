#include "Figure_2D.h"

Figure_2D::Figure_2D() : Figure() {
    color = 0;
}

Figure_2D::Figure_2D(double **vert, int vert_size, int col) : Figure(vert, vert_size, 2) {
    color = col;
}
void Figure_2D::draw()
{
    cout << "Figure_2d draw" << endl;
    for(int i = 0; i < vert_size; i++)
    {
        for(int j = 0; j <= coord_num; j++)
            cout << vertexes[i][j] << " ";
        cout << endl;
    }
}

Figure_2D::Figure_2D(const Figure_2D &fig): Figure(fig) {
    color = fig.color;
}

Figure_2D &Figure_2D::operator=(const Figure_2D &fig) {
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
    color = fig.color;
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
