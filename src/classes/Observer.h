#ifndef OBSERVER_H
#define OBSERVER_H

#include <cmath>
#define M_PI 3.14
class Observer
{
private:
    double teta;
    double fi;
    double ro;
public:
    Observer();
    Observer(double r, double f, double t);
    double get_ro() const;
    double get_teta() const;
    double get_fi() const;
    void set_ro(double r);
    void set_teta(double t);
    void set_fi(double f);
    void add_to_ro(double r);
    void add_to_fi(double f);
    void add_to_teta(double t);
};


#endif
