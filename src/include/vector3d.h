#ifndef RAYTRACER_VECTOR3D_H_
#define RAYTRACER_VECTOR3D_H_

#include <cstddef>
#include <cmath>

template <typename T>
class Vector3d
{
private:
  T DefaultValue = T();
  T X;
  T Y;
  T Z;

public:
  //! Sets all members to zero
  Vector3d();

  //! Explicitly converts from one type to another
  template <typename R>
  explicit Vector3d(const Vector3d<R> &other);

  Vector3d(const T &x, const T &y, const T &z);

  Vector3d(const T coords[3]);

  // Get-Set methods

  const T &getX() const;
  void setX(const T &newX);

  const T &getY() const;
  void setY(const T &newY);

  const T &getZ() const;
  void setZ(const T &newZ);

  void getv(T buffer[3]) const;
  void setv(const T coords[3]);

  void get(T &x, T &y, T &z) const;
  void set(const T &x, const T &y, const T &z);

  // Interface for indexing

  const T &operator[](size_t index) const;
  T &operator[](size_t index);

  //! Considering vectors as matrices with one row
  const T &operator()(size_t column) const;
  T &operator()(size_t column);

  // Standard operations

  //! This does absolutely nothing, but it should be included for consistency
  const Vector3d operator+() const;

  const Vector3d operator+(const Vector3d &other) const;
  Vector3d &operator+=(const Vector3d &other);

  //! The same as multiplying *this by -1
  const Vector3d operator-() const;

  const Vector3d operator-(const Vector3d &other) const;
  Vector3d &operator-=(const Vector3d &other);

  //! Multiplying *this by a scalar
  const Vector3d operator*(const T &scalar) const;
  Vector3d &operator*=(const T &scalar);

  //! Same as multiplication by 1/scalar, maybe more accurate but also slower
  const Vector3d operator/(const T &scalar) const;
  Vector3d &operator/=(const T &scalar);

  //! Calculate the dot/inner/scalar product
  const T operator*(const Vector3d &other) const;

  //! Calculate the cross/outer/vector product
  const Vector3d operator%(const Vector3d &other) const;
  Vector3d &operator%=(const Vector3d &other);

  // Auxiliary methods

  //! Returns the squared length of *this
  const T getSqrLen() const;
  //! Returns the length of *this
  const T getLen() const;

  //! Returns a vector with the same orientation, but with a length of 1
  const Vector3d getUnit() const;

  //! Returns cross product
  const Vector3d cross(const Vector3d &other) const;

  //! Returns dot product
  const T dot(const Vector3d &other) const;

  //! Interpolates *this between another vector, by a ratio
  const Vector3d getInterpolation(const Vector3d &other, const T &ratio) const;

  //! Reflects *this according to a surface's normal
  const Vector3d getReflection(const Vector3d &surfaceNormal) const;

  //! Rotates *this about an origin, using Euler angles( X=pitch, Y=yaw, Z=roll)
  const Vector3d getRotationEuler(const Vector3d &angles,
                                  const Vector3d &origin = Vector3d(), bool degs = true, bool ccw = true) const;

  //! Rotates *this about an origin, using an arbitrary axis( axis should be a unit vector )
  const Vector3d getRotationArbAxis(const Vector3d &axis, const T &amount,
                                    const Vector3d &origin = Vector3d(), bool degs = true, bool ccw = true) const;
};

template <typename T>
inline Vector3d<T>::Vector3d()
    : X(0), Y(0), Z(0)
{
}

template <typename T>
template <typename R>
inline Vector3d<T>::Vector3d(const Vector3d<R> &other)
    : X(other.X), Y(other.Y), Z(other.Z)
{
}

template <typename T>
inline Vector3d<T>::Vector3d(const T &x, const T &y, const T &z)
    : X(x), Y(y), Z(z)
{
}

template <typename T>
inline Vector3d<T>::Vector3d(const T coords[3])
    : X(coords[0]), Y(coords[1]), Z(coords[2])
{
}

template <typename T>
inline const T &Vector3d<T>::getX() const
{
  return X;
}

template <typename T>
inline void Vector3d<T>::setX(const T &newX)
{
  X = newX;
}

template <typename T>
inline const T &Vector3d<T>::getY() const
{
  return Y;
}

template <typename T>
inline void Vector3d<T>::setY(const T &newY)
{
  Y = newY;
}

template <typename T>
inline const T &Vector3d<T>::getZ() const
{
  return Z;
}

template <typename T>
inline void Vector3d<T>::setZ(const T &newZ)
{
  Z = newZ;
}

template <typename T>
inline void Vector3d<T>::getv(T buffer[3]) const
{
  buffer[0] = X;
  buffer[1] = Y;
  buffer[2] = Z;
}

template <typename T>
inline void Vector3d<T>::setv(const T coords[3])
{
  X = coords[0];
  Y = coords[1];
  Z = coords[2];
}

template <typename T>
inline void Vector3d<T>::get(T &x, T &y, T &z) const
{
  x = X;
  y = Y;
  z = Z;
}

template <typename T>
inline void Vector3d<T>::set(const T &x, const T &y, const T &z)
{
  X = x;
  Y = y;
  Z = z;
}

template <typename T>
inline const T &Vector3d<T>::operator[](size_t index) const
{
  switch (index)
  {
  case 0:
    return X;
  case 1:
    return Y;
  case 2:
    return Z;
  }

  return T();
}

template <typename T>
inline T &Vector3d<T>::operator[](size_t index)
{
  switch (index)
  {
  case 0:
    return X;
  case 1:
    return Y;
  case 2:
    return Z;
  }

  return DefaultValue;
}

template <typename T>
inline const T &Vector3d<T>::operator()(size_t column) const
{
  switch (column)
  {
  case 1:
    return X;
  case 2:
    return Y;
  case 3:
    return Z;
  }

  return T();
}

template <typename T>
inline T &Vector3d<T>::operator()(size_t column)
{
  switch (column)
  {
  case 1:
    return X;
  case 2:
    return Y;
  case 3:
    return Z;
  }

  return DefaultValue;
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::operator+() const
{
  return *this;
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::operator+(const Vector3d &other) const
{
  return Vector3d(X + other.X, Y + other.Y, Z + other.Z);
}

template <typename T>
inline Vector3d<T> &Vector3d<T>::operator+=(const Vector3d &other)
{
  return *this = *this + other;
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::operator-() const
{
  return Vector3d(-X, -Y, -Z);
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::operator-(const Vector3d &other) const
{
  return Vector3d(X - other.X, Y - other.Y, Z - other.Z);
}

template <typename T>
inline Vector3d<T> &Vector3d<T>::operator-=(const Vector3d &other)
{
  return *this = *this - other;
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::operator*(const T &scalar) const
{
  return Vector3d(X * scalar, Y * scalar, Z * scalar);
}

template <typename T>
inline Vector3d<T> &Vector3d<T>::operator*=(const T &scalar)
{
  return *this = *this * scalar;
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::operator/(const T &scalar) const
{
  return Vector3d(X / scalar, Y / scalar, Z / scalar);
}

template <typename T>
inline Vector3d<T> &Vector3d<T>::operator/=(const T &scalar)
{
  return *this = *this / scalar;
}

template <typename T>
inline const T Vector3d<T>::operator*(const Vector3d &other) const
{
  return X * other.X + Y * other.Y + Z * other.Z;
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::operator%(const Vector3d &other) const
{
  return Vector3d(Y * other.Z - Z * other.Y,
                  Z * other.X - X * other.Z,
                  X * other.Y - Y * other.X);
}

template <typename T>
inline Vector3d<T> &Vector3d<T>::operator%=(const Vector3d &other)
{
  return *this = *this % other;
}

template <typename T>
inline const T Vector3d<T>::getSqrLen() const
{
  return X * X + Y * Y + Z * Z;
}

template <typename T>
inline const T Vector3d<T>::getLen() const
{
  return std::sqrt(getSqrLen());
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::getUnit() const
{
  if (getSqrLen() != 0)
    return *this / getLen();

  return *this;
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::cross(const Vector3d &other) const
{
  return *this % other;
}

template <typename T>
inline const T Vector3d<T>::dot(const Vector3d &other) const
{
  return (*this) * other;
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::getInterpolation(const Vector3d &other, const T &ratio) const
{
  return *this + (other - *this) * ratio;
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::getReflection(const Vector3d &surfaceNormal) const
{
  return *this - surfaceNormal * ((*this * surfaceNormal) * 2);
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::
    getRotationEuler(const Vector3d &angles, const Vector3d &origin, bool degs, bool ccw) const
{
  T sin_phi, sin_theta, sin_psi;
  T cos_phi, cos_theta, cos_psi;

  if (degs)
  {
    const T degToRad = T(M_PI) / 360;

    sin_phi = std::sin(angles.getX() * degToRad);
    sin_theta = std::sin(angles.getY() * degToRad);
    sin_psi = std::sin(angles.getZ() * degToRad);

    cos_phi = std::cos(angles.getX() * degToRad);
    cos_theta = std::cos(angles.getY() * degToRad);
    cos_psi = std::cos(angles.getZ() * degToRad);
  }
  else
  {
    sin_phi = std::sin(angles.getX());
    sin_theta = std::sin(angles.getY());
    sin_psi = std::sin(angles.getZ());

    cos_phi = std::cos(angles.getX());
    cos_theta = std::cos(angles.getY());
    cos_psi = std::cos(angles.getZ());
  }

  if (!ccw)
  {
    sin_phi = -sin_phi;
    sin_theta = -sin_theta;
    sin_psi = -sin_psi;
  }

  Vector3d temp = *this - origin;
  Vector3d result = temp;

  result.setY(temp.getY() * cos_phi + temp.getZ() * sin_phi);
  result.setZ(-temp.getY() * sin_phi + temp.getZ() * cos_phi);

  temp = result;

  result.setX(temp.getX() * cos_theta - temp.getZ() * sin_theta);
  result.setZ(temp.getX() * sin_theta + temp.getZ() * cos_theta);

  temp = result;

  result.setX(temp.getX() * cos_psi + temp.getY() * sin_psi);
  result.setY(-temp.getX() * sin_psi + temp.getY() * cos_psi);

  return result + origin;
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::
    getRotationArbAxis(const Vector3d &axis, const T &amount, const Vector3d &origin, bool degs, bool ccw) const
{
  T cos_theta, sin_theta;

  if (degs)
  {
    const T degToRad = T(M_PI) / 360;

    cos_theta = std::cos(amount * degToRad);
    sin_theta = std::sin(amount * degToRad);
  }
  else
  {
    cos_theta = std::cos(amount);
    sin_theta = std::sin(amount);
  }

  if (!ccw)
    sin_theta = -sin_theta;

  return *this * cos_theta + (axis % *this) * sin_theta + axis * ((axis * *this) * (1 - cos_theta));
}

#endif // RAYTRACER_VECTOR3D_H_