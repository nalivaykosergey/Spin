#include "Figure_3D.h"
Figure_3D::Figure_3D(): Figure() {
    edges_size = 0;
}

Figure_3D::Figure_3D(double **vert, int vert_size, int **ed,
                     int e_s, const int * e_c_n, const int *colors): Figure(vert, vert_size, 3)
{
    edges_size = e_s;
    edges_coord_num = new int[edges_size];
    edges_colors = new int[edges_size];
    edges = new int*[edges_size];
    visible_state = new bool[edges_size];
    for(int i = 0; i < edges_size; i++)
    {
        edges_coord_num[i] = e_c_n[i];
        edges_colors[i] = colors[i];
        edges[i] = new int[edges_coord_num[i]];
        for(int j = 0; j < edges_coord_num[i]; j++)
            edges[i][j] = (ed[i][j] - 1);
    }
}

Figure_3D::Figure_3D(const Figure_3D &fig) : Figure(fig){
    if(edges)
    {
        for(int i = 0; i < edges_size; i++)
            delete [] edges[i];
        delete [] edges;
        delete [] edges_colors;
        delete [] edges_coord_num;
    }
    edges_size = fig.edges_size;
    edges_coord_num = new int[edges_size];
    edges_colors = new int[edges_size];
    edges = new int*[edges_size];
    for(int i = 0; i < edges_size; i++)
    {
        edges_coord_num[i] = fig.edges_coord_num[i];
        edges_colors[i] = fig.edges_colors[i];
        edges[i] = new int[edges_coord_num[i]];
        for(int j = 0; j < edges_coord_num[i]; j++)
            edges[i][j] = fig.edges[i][j];
    }
}

Figure_3D &Figure_3D::operator=(const Figure_3D &fig) {
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
    if(edges)
    {
        for(int i = 0; i < edges_size; i++)
            delete [] edges[i];
        delete [] edges;
        delete [] edges_colors;
        delete [] edges_coord_num;
    }
    edges_size = fig.edges_size;
    edges_coord_num = new int[edges_size];
    edges_colors = new int[edges_size];
    edges = new int*[edges_size];
    for(int i = 0; i < edges_size; i++)
    {
        edges_colors[i] = fig.edges_colors[i];
        edges[i] = new int[edges_coord_num[i]];
        for(int j = 0; j < edges_coord_num[i]; j++)
            edges[i][j] = fig.edges[i][j];
    }
    return *this;
}


Figure_3D::~Figure_3D() {
    if(edges)
    {
        for(int i = 0; i < edges_size; i++)
            delete [] edges[i];
        delete [] edges_colors;
        delete [] edges;
        delete [] visible_state;
        delete [] edges_coord_num;
    }
}

void Figure_3D::link(Observer &o) {
    obs = &o;
}

void Figure_3D::displace(double (*matr)[4]) {
    auto tmp = new double[4];
    for(int k = 0; k < vert_size; k++)
    {
        for(int i = 0; i < 4; i++)
        {
            tmp[i] = 0;
            for(int j = 0; j < 4; j++)
                tmp[i]+= vertexes[k][j] * matr[j][i];
        }
        for(int i = 0; i < 4; i++)
            vertexes[k][i] = tmp[i];
    }
    delete [] tmp;
}

void Figure_3D::draw() {
    if(!obs)
        return;
    auto tmp_2d_coord = render();
    int index1, index2;
    for(int i =0; i < edges_size; i++)
    {
        if(visible_state[i])
        {
            for(int j = 0; j < edges_coord_num[i] - 1; j++)
            {
                index1 = edges[i][j];
                index2 = edges[i][j + 1];
                line(tmp_2d_coord[index1][0], tmp_2d_coord[index1][1],
                     tmp_2d_coord[index2][0], tmp_2d_coord[index2][1]);
            }
            index1 = edges[i][0];
            index2 = edges[i][edges_coord_num[i] - 1];
            line(tmp_2d_coord[index1][0], tmp_2d_coord[index1][1],
                 tmp_2d_coord[index2][0], tmp_2d_coord[index2][1]);
            fill_area(tmp_2d_coord, edges[i], i);
        }
    }
    for(int i = 0; i < vert_size; i++)
        delete [] tmp_2d_coord[i];
    delete [] tmp_2d_coord;
}

int **Figure_3D::render() {
    auto ret_val = new int*[vert_size];
    auto obs_view = to_observer();
    //visible_alg1(obs_view);
    visible_alg2(obs_view);
    for(int i = 0; i < vert_size; i++)
    {
        ret_val[i] = new int[2];
        ret_val[i][0] = floor((obs->get_ro() / 2.0 ) * (obs_view[i][0]/obs_view[i][2])  + 0.5) + getmaxx()/2;
        ret_val[i][1] = floor((obs->get_ro() / 2.0 ) * (obs_view[i][1]/obs_view[i][2])  + 0.5) + getmaxy()/2;
    }
    for(int i = 0; i < vert_size; i++)
        delete [] obs_view[i];
    delete [] obs_view;
    return ret_val;
}

double **Figure_3D::to_observer() {
    auto ** ret_val = new double*[vert_size];
    double ro, fi, teta;

    ro = obs->get_ro();
    fi = obs->get_fi();
    teta = obs->get_teta();

    double V[4][4] = {
            { -sin(teta), -cos(fi)*cos(teta), -sin(fi)*cos(teta), 0 },
            { cos(teta), -cos(fi)*sin(teta), -sin(fi)*sin(teta), 0 },
            {0, sin(fi), -cos(fi), 0},
            {0, 0, ro, 1}
    };
    //Copy data
    for(int i = 0; i < vert_size; i++)
    {
        ret_val[i] = new double[4];
        for(int j = 0; j < 4; j++)
            ret_val[i][j] = vertexes[i][j];
    }
    //Mulptip (vec * matr)
    for(int k = 0; k < vert_size; k++)
    {
        auto tmp = new double[4];
        for(int i = 0; i < 4; i++)
        {
            tmp[i] = 0;
            for(int j = 0; j < 4; j++)
                tmp[i]+= vertexes[k][j] * V[j][i];
        }
        for(int i = 0; i < 4; i++)
            ret_val[k][i] = tmp[i];
        delete [] tmp;
    }
    return ret_val;
}

void Figure_3D::visible_alg1(double ** obs_view) {
    double x1,x2,x3,y1,y2,y3,z1,z2,z3, det1,det2,det3, h;
    int index1,index2, index3;
    for(int i = 0; i < edges_size; i++)
    {
        index1 = edges[i][0];
        index2 = edges[i][1];
        index3 = edges[i][2];
        x1 = obs_view[index1][0];
        x2 = obs_view[index2][0];
        x3 = obs_view[index3][0];
        y1 = obs_view[index1][1];
        y2 = obs_view[index2][1];
        y3 = obs_view[index3][1];
        z1 = obs_view[index1][2];
        z2 = obs_view[index2][2];
        z3 = obs_view[index3][2];
        det1 = (y2-y1) * (z3 - z1) - (z2-z1)*(y3-y1);
        det2 = -((x2-x1) * (z3-z1) - (z2-z1) * (x3-x1));
        det3 = (x2-x1) * (y3-y1) - (y2-y1) * (x3-x1);
        h = (-x1 * det1) + (-y1 * det2) + (-z1 * det3);
        if(h < 0)
            visible_state[i] = true;
        else
            visible_state[i] = false;
    }
}

void Figure_3D::visible_alg2(double **obs_view) {
    int index1, index2, index3;
    double x1,x2,x3,y1,y2,y3,z1,z2,z3,h, L_i, alpha;
    double cube_center[3] = {0,0,0};
    for(int i = 0; i < vert_size; i++)
        for(int j = 0; j < 3; j++)
            cube_center[j] += obs_view[i][j];
    for(int j = 0; j < 3; j++)
        cube_center[j] /= vert_size;
    for(int i = 0; i < edges_size; i++)
    {
        double det[3] = {0, 0, 0};
        double d[3] = {0, 0, 0};
        double de = 0, mod_e = 0, mod_d = 0, tmp;
        index1 = edges[i][0];
        index2 = edges[i][1];
        index3 = edges[i][2];
        x1 = obs_view[index1][0];
        x2 = obs_view[index2][0];
        x3 = obs_view[index3][0];
        y1 = obs_view[index1][1];
        y2 = obs_view[index2][1];
        y3 = obs_view[index3][1];
        z1 = obs_view[index1][2];
        z2 = obs_view[index2][2];
        z3 = obs_view[index3][2];
        det[0] = (y2-y1) * (z3 - z1) - (z2-z1)*(y3-y1);
        det[1] = -((x2-x1) * (z3-z1) - (z2-z1) * (x3-x1));
        det[2] = (x2-x1) * (y3-y1) - (y2-y1) * (x3-x1);
        h = (-x1 * det[0]) + (-y1 * det[1]) + (-z1 * det[2]);
        L_i = det[0] * cube_center[0] + det[1] * cube_center[1] + det[2] * cube_center[2] + h;
        if(L_i < 0)
            for(int k = 0; k < 3; k++)
                det[k] *= (-1);
        d[0] = (x1 + x3)/2;
        d[1] = (y1 + y3)/2;
        d[2] = (z1 + z3)/2;
        for(int k =0; k < 3; k++)
            de += det[k] * d[k];
        for(int k =0; k < 3; k++)
            mod_d += (d[k] * d[k]);
        mod_d = sqrt(mod_d);
        for(int k =0; k < 3; k++)
            mod_e += (det[k] * det[k]);
        mod_e = sqrt(mod_e);
        tmp = de / (mod_d * mod_e);
        alpha = acos(tmp) * 180.0 / M_PI;
        if(alpha > 0 && alpha < 90)
            visible_state[i] = true;
        else
            visible_state[i] = false;
    }
}
void Figure_3D::fill_area(int ** vert, int * edge, int edge_no)
{
    auto data  = new int[edges_coord_num[edge_no] * 2];

    for(int i = 0, k = 0; i < edges_coord_num[edge_no]; i++, k+=2)
    {
        data[k] = vert[edge[i]][0];
        data[k+1] = vert[edge[i]][1];
    }
    setfillstyle(1, edges_colors[edge_no]);
	setcolor(15);
    fillpoly(edges_coord_num[edge_no], data);
    delete [] data;
}
