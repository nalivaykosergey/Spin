#include "help_func.h"
void read_data(const std::string & file_name, double ** vert, int & vert_size)
{
    std::ifstream file;
    file.open(file_name);
    if(!file)
    {
        std::cout << "Can't find file" <<std::endl;
        exit(1);
    }
    file >> vert_size;
    for(int i = 0; i < vert_size; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            file >> vert[i][j];
        }
    }
    file.close();
}
void read_data(const std::string & file_name, double ** vert, int & vert_size, int ** ed, int & ed_size, int * ed_coord_size, int * colors)
{
    std::ifstream file;
    file.open(file_name);
    if(!file)
    {
        std::cout << "Can't find file" <<std::endl;
        exit(1);
    }
    file >> vert_size;
    
    for(int i = 0; i < vert_size; i++)
    {
    	vert[i] = new double[3];
        for(int j = 0; j < 3; j++)
            file >> vert[i][j];
    }
    file >> ed_size;
    for(int i = 0; i < ed_size; i++)
    {
    	file >> ed_coord_size[i];
    	ed[i] = new int[ed_coord_size[i]];
        for(int j = 0; j < ed_coord_size[i]; j++)
            file >> ed[i][j];
    }
    for(int i = 0; i < ed_size; i++)
        file >> colors[i];
    file.close();
}

double ** mul(double * vec, int vec_size, int ** matr,
              int r, int c)
{
    if(vec_size != r)
        return nullptr;
    auto ret_val = new double*[vec_size];
}
