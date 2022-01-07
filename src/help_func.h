#ifndef HELP_FUNC_H
#define HELP_FUNC_H

#include <iostream>
#include <string>
#include <fstream>

void read_data(const std::string &, double ** vert, int & vert_size);
void read_data(const std::string & file_name, double ** vert, int & vert_size,
             int ** ed, int & ed_size,  int * ed_coord_size, int * colors);
double ** mul(double vec[4], int vec_size, int ** matr,
              int r, int c);

#endif
