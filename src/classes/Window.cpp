#include "Window.h"

Window::Window() {
    width = 1280;
    height = 720;
    win_name = "Hello, world";
}

Window::Window(int w, int h, char *w_n, Observer &o) {
    width = w;
    height = h;
    win_name = w_n;
    obs = &o;
}

void Window::init() {
    initwindow(width, height, win_name);
    setbkcolor(3);
}

Window::~Window() {
    list<Figure *>::iterator it;
    for (it = figures.begin(); it != figures.end(); ++it){
        delete *it;
    }
    closegraph();
}

void Window::add_figure(double **vert, int vert_size, int col) {
    auto * tmp = new Figure_2D(vert, vert_size, col);
    figures.push_back(tmp);
}

void Window::add_figure(double **vert, int vert_size, int **ed, int e_s, int * e_c_n, const int *colors,
                        double (*world_matrix)[4]) {
    auto * tmp = new Figure_3D(vert, vert_size, ed, e_s, e_c_n,colors);
    tmp->displace(world_matrix);
    tmp->link(*obs);
    figures.push_back(tmp);
}

void Window::draw() {
    if(figures.empty())
    {
        cout << "Nothing to draw" << endl;
        return;
    }
    cleardevice();
    list<Figure *>::iterator it;
    for (it = figures.begin(); it != figures.end(); ++it){
        (*it)->draw();
    }
}

void Window::remove_figure(int index) {
    auto it = figures.begin();
    advance(it, index);
    delete * it;
    figures.erase(it);
}
