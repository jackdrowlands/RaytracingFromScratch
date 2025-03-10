#ifndef INTERVAL_H
#define INTERVAL_H

#include "utils.h"

class interval {
    public:
    double max, min;
    interval() : min(+INF), max(-INF) {} // Empty interval

    interval(double min, double max) : min(min), max(max) {}

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

    // Define static variables inline to avoid linker errors
    static const interval empty;
    static const interval universe;
};

// Define the static members
inline const interval interval::empty = interval(+INF, -INF);
inline const interval interval::universe = interval(-INF, +INF);

#endif