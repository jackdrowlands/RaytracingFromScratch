#ifndef INTERVAL_H
#define INTERVAL_H

#include "utils.h"

/**
 * Interval class representing a range of values between min and max
 * Used for ray parameter bounds, color clamping, and other range operations
 */
class interval {
    public:
    double max, min;  // Bounds of the interval
    
    // Default constructor creates an empty interval (min > max)
    interval() : min(+INF), max(-INF) {}
    
    // Constructor with explicit min and max bounds
    interval(double min, double max) : min(min), max(max) {}

    // Get the size (length) of the interval
    double size() const {
        return max - min;
    }

    // Check if a value is inside the interval (inclusive bounds)
    bool contains(double x) const {
        return x >= min && x <= max;
    }

    // Check if a value is strictly inside the interval (exclusive bounds)
    bool surrounds(double x) const {
        return min < x && x < max;
    }

    // Clamp a value to be within the interval
    double clamp(double x) const {
        return std::clamp(x, min, max);
    }

    // Static constant intervals for common use cases
    static const interval empty;     // Empty interval
    static const interval universe;  // Interval containing all real values
};

// Define the static members inline to avoid linker errors
inline const interval interval::empty = interval(+INF, -INF);
inline const interval interval::universe = interval(-INF, +INF);

#endif