#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

/**
 * 3D vector class for representing positions, directions, and colors
 * Serves as the foundation for most of the ray tracing math operations
 */
class vec3 {
 public:
  double e[3];  // Array holding the three components (x, y, z)

  // Constructors
  vec3() : e{0, 0, 0} {}  // Default constructor initializes to zero vector
  vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}  // Component-wise initialization

  // Accessor methods for x, y, z components
  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  // Operator overloads for basic vector operations
  vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }  // Unary minus (negation)
  double operator[](int i) const { return e[i]; }  // Const array-style access
  double& operator[](int i) { return e[i]; }  // Mutable array-style access

  // Compound assignment operators
  vec3& operator+=(const vec3& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  vec3& operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  vec3& operator/=(const double t) { return *this *= 1 / t; }  // Division as multiplication by reciprocal

  // Vector length calculations
  double length() const { return std::sqrt(lengthSquared()); }  // Euclidean length

  double lengthSquared() const {  // Squared length (faster when only comparing magnitudes)
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  // Check if vector is very close to zero in all dimensions
  bool nearZero() const {
    auto s = 1e-8;  // Small threshold value
    return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
  }

  // Static methods for generating random vectors
  static vec3 random() {  // Random vector with components in [0,1)
    return vec3(randomDouble(), randomDouble(), randomDouble());
  }
  
  static vec3 random(double min, double max) {  // Random vector with components in [min,max)
    return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
  }
};

// Type alias for 3D points (semantically distinct but same implementation)
using point3 = vec3;

// Output stream operator for printing vectors
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// Vector addition
inline vec3 operator+(const vec3& u, const vec3& v) {
  return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// Vector subtraction
inline vec3 operator-(const vec3& u, const vec3& v) {
  return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// Component-wise vector multiplication
inline vec3 operator*(const vec3& u, const vec3& v) {
  return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// Scalar-vector multiplication
inline vec3 operator*(double t, const vec3& v) {
  return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

// Vector-scalar multiplication (commutative with scalar-vector)
inline vec3 operator*(const vec3& v, double t) { return t * v; }

// Vector-scalar division
inline vec3 operator/(vec3 v, double t) { return (1 / t) * v; }

// Dot product of two vectors
inline double dot(const vec3& u, const vec3& v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

// Cross product of two vectors
inline vec3 cross(const vec3& u, const vec3& v) {
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// Convert vector to unit vector (length 1)
inline vec3 unitVector(vec3 v) { return v / v.length(); }

// Generate a random unit vector (for diffuse reflection)
inline vec3 randomUnitVec3() {
  while (true) {
    auto p = vec3::random(-1, 1);  // Random point in a cube
    // Keep only points inside the unit sphere and not too close to zero
    if (1e-8 < p.lengthSquared() && p.lengthSquared() <= 1) {
      return p;
    }
  }
}

// Generate a random vector on the hemisphere oriented around the normal
inline vec3 randomOnHemisphere(const vec3& normal) {
  auto onUnitSphere = randomUnitVec3();
  // Flip the vector if it points into the wrong hemisphere
  if (dot(onUnitSphere, normal) > 0.0) {
    return onUnitSphere;
  } else {
    return -onUnitSphere;
  }
}

// Calculate reflection vector using the formula r = v - 2(v·n)n
inline vec3 reflect(const vec3& v, const vec3& n) {
  return v - 2 * dot(v, n) * n;
}

// Calculate refraction using Snell's law
inline vec3 refract(const vec3& uv, const vec3& n, double etaiOverEtat) {
  auto cosTheta = std::fmin(dot(-uv, n), 1.0);
  vec3 rOutPerp = etaiOverEtat * (uv + cosTheta * n);  // Perpendicular component
  vec3 rOutParallel = -std::sqrt(std::fabs(1.0 - rOutPerp.lengthSquared())) * n;  // Parallel component
  return rOutPerp + rOutParallel;  // Combined refracted vector
}

// Generate a random point in a unit disk (for depth of field effect)
inline vec3 randomInUnitDisk() {
  while (true) {
    auto p = vec3(randomDouble(-1, 1), randomDouble(-1, 1), 0);  // Random point in a 2D square
    if (p.lengthSquared() < 1) {  // Keep only points inside the unit disk
      return p;
    }
  }
}

#endif