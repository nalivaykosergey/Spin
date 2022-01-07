#include "Observer.h"

Observer::Observer() {
    teta = 0;
    fi = 0;
    ro = 0;
}

Observer::Observer(double r, double f, double t)
{
    ro = r;
    fi  = f * M_PI / 180.0;
    teta = t * M_PI / 180.0;
}

double Observer::get_ro() const {
    return ro;
}

double Observer::get_teta() const {
    return teta;
}

double Observer::get_fi() const {
    return fi;
}

void Observer::set_ro(double r) {
    ro = r;
}

void Observer::set_teta(double t) {
    teta = t * M_PI / 180.0;
}

void Observer::set_fi(double f) {
    fi = f * M_PI / 180.0;
}

void Observer::add_to_ro(double r) {
    ro += r;
}

void Observer::add_to_fi(double f) {
    fi += (f * M_PI / 180.0);
}

void Observer::add_to_teta(double t) {
    teta += (t * M_PI / 180.0);
};





