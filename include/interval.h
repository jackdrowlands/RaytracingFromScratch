#ifndef INTERVAL_H
#define INTERVAL_H

#include "utils.h"

class interval {
    public:
    double max, min;
    interval() : min(+INF), max(-INF) {}

    interval(double min, double max) : min(min) , max(max) {}

    double size() const {
        return max - min;
    }

    bool contains(double x) const {
        return x >= min && x <= max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }

    double clamp(double x) const {
        return std::clamp(x, min, max);
    }

    static const interval empty, universe;
};

#endif