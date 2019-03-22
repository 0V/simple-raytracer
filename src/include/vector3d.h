#ifndef RAyTRACER_VECTOR3D_H_
#define RAyTRACER_VECTOR3D_H_

#include <cstddef>
#include <cmath>

template <typename T>
class Vector3d
{
private:
  T DefaultValue = T();

public:
  T x;
  T y;
  T z;
  //! Sets all members to zero
  Vector3d();

  //! Explicitly converts from one type to another
  template <typename R>
  explicit Vector3d(const Vector3d<R> &other);

  Vector3d(const T &x, const T &y, const T &z);

  Vector3d(const T coords[3]);

  // Get-Set methods

  const T &getx() const;
  void setx(const T &newx);

  const T &gety() const;
  void sety(const T &newy);

  const T &getz() const;
  void setz(const T &newz);

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
  const T square_length() const;
  //! Returns the length of *this
  const T length() const;

  //! Returns a vector with the same orientation, but with a length of 1
  const Vector3d normalize() const;

  //! Returns cross product
  const Vector3d cross(const Vector3d &other) const;

  //! Returns dot product
  const T dot(const Vector3d &other) const;

  //! Returns product each value
  const Vector3d<T> product(const Vector3d &other) const;

  //! Interpolates *this between another vector, by a ratio
  const Vector3d getInterpolation(const Vector3d &other, const T &ratio) const;

  //! Reflects *this according to a surface's normal
  const Vector3d getReflection(const Vector3d &surfaceNormal) const;

  //! Rotates *this about an origin, using Euler angles( x=pitch, y=yaw, z=roll)
  const Vector3d getRotationEuler(const Vector3d &angles,
                                  const Vector3d &origin = Vector3d(), bool degs = true, bool ccw = true) const;

  //! Rotates *this about an origin, using an arbitrary axis( axis should be a unit vector )
  const Vector3d getRotationArbAxis(const Vector3d &axis, const T &amount,
                                    const Vector3d &origin = Vector3d(), bool degs = true, bool ccw = true) const;
};

template <typename T>
inline Vector3d<T>::Vector3d()
    : x(0), y(0), z(0)
{
}

template <typename T>
template <typename R>
inline Vector3d<T>::Vector3d(const Vector3d<R> &other)
    : x(other.x), y(other.y), z(other.z)
{
}

template <typename T>
inline Vector3d<T>::Vector3d(const T &x, const T &y, const T &z)
    : x(x), y(y), z(z)
{
}

template <typename T>
inline Vector3d<T>::Vector3d(const T coords[3])
    : x(coords[0]), y(coords[1]), z(coords[2])
{
}

template <typename T>
inline const T &Vector3d<T>::getx() const
{
  return x;
}

template <typename T>
inline void Vector3d<T>::setx(const T &newx)
{
  x = newx;
}

template <typename T>
inline const T &Vector3d<T>::gety() const
{
  return y;
}

template <typename T>
inline void Vector3d<T>::sety(const T &newy)
{
  y = newy;
}

template <typename T>
inline const T &Vector3d<T>::getz() const
{
  return z;
}

template <typename T>
inline void Vector3d<T>::setz(const T &newz)
{
  z = newz;
}

template <typename T>
inline void Vector3d<T>::getv(T buffer[3]) const
{
  buffer[0] = x;
  buffer[1] = y;
  buffer[2] = z;
}

template <typename T>
inline void Vector3d<T>::setv(const T coords[3])
{
  x = coords[0];
  y = coords[1];
  z = coords[2];
}

template <typename T>
inline void Vector3d<T>::get(T &x, T &y, T &z) const
{
  x = x;
  y = y;
  z = z;
}

template <typename T>
inline void Vector3d<T>::set(const T &x, const T &y, const T &z)
{
  x = x;
  y = y;
  z = z;
}

template <typename T>
inline const T &Vector3d<T>::operator[](size_t index) const
{
  switch (index)
  {
  case 0:
    return x;
  case 1:
    return y;
  case 2:
    return z;
  }

  return T();
}

template <typename T>
inline T &Vector3d<T>::operator[](size_t index)
{
  switch (index)
  {
  case 0:
    return x;
  case 1:
    return y;
  case 2:
    return z;
  }

  return DefaultValue;
}

template <typename T>
inline const T &Vector3d<T>::operator()(size_t column) const
{
  switch (column)
  {
  case 1:
    return x;
  case 2:
    return y;
  case 3:
    return z;
  }

  return T();
}

template <typename T>
inline T &Vector3d<T>::operator()(size_t column)
{
  switch (column)
  {
  case 1:
    return x;
  case 2:
    return y;
  case 3:
    return z;
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
  return Vector3d(x + other.x, y + other.y, z + other.z);
}

template <typename T>
inline Vector3d<T> &Vector3d<T>::operator+=(const Vector3d &other)
{
  return *this = *this + other;
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::operator-() const
{
  return Vector3d(-x, -y, -z);
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::operator-(const Vector3d &other) const
{
  return Vector3d(x - other.x, y - other.y, z - other.z);
}

template <typename T>
inline Vector3d<T> &Vector3d<T>::operator-=(const Vector3d &other)
{
  return *this = *this - other;
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::operator*(const T &scalar) const
{
  return Vector3d(x * scalar, y * scalar, z * scalar);
}

template <typename T>
inline Vector3d<T> &Vector3d<T>::operator*=(const T &scalar)
{
  return *this = *this * scalar;
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::operator/(const T &scalar) const
{
  return Vector3d(x / scalar, y / scalar, z / scalar);
}

template <typename T>
inline Vector3d<T> &Vector3d<T>::operator/=(const T &scalar)
{
  return *this = *this / scalar;
}

template <typename T>
inline const T Vector3d<T>::operator*(const Vector3d &other) const
{
  return x * other.x + y * other.y + z * other.z;
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::operator%(const Vector3d &other) const
{
  return Vector3d(y * other.z - z * other.y,
                  z * other.x - x * other.z,
                  x * other.y - y * other.x);
}

template <typename T>
inline Vector3d<T> &Vector3d<T>::operator%=(const Vector3d &other)
{
  return *this = *this % other;
}

template <typename T>
inline const T Vector3d<T>::square_length() const
{
  return x * x + y * y + z * z;
}

template <typename T>
inline const T Vector3d<T>::length() const
{
  return std::sqrt(square_length());
}

template <typename T>
inline const Vector3d<T> Vector3d<T>::normalize() const
{
  if (square_length() != 0)
    return *this / length();

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
inline const Vector3d<T> Vector3d<T>::product(const Vector3d &other) const
{
  return Vector3d<T>((*this).x * other.x, (*this).y * other.y, (*this).z * other.z);
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

    sin_phi = std::sin(angles.getx() * degToRad);
    sin_theta = std::sin(angles.gety() * degToRad);
    sin_psi = std::sin(angles.getz() * degToRad);

    cos_phi = std::cos(angles.getx() * degToRad);
    cos_theta = std::cos(angles.gety() * degToRad);
    cos_psi = std::cos(angles.getz() * degToRad);
  }
  else
  {
    sin_phi = std::sin(angles.getx());
    sin_theta = std::sin(angles.gety());
    sin_psi = std::sin(angles.getz());

    cos_phi = std::cos(angles.getx());
    cos_theta = std::cos(angles.gety());
    cos_psi = std::cos(angles.getz());
  }

  if (!ccw)
  {
    sin_phi = -sin_phi;
    sin_theta = -sin_theta;
    sin_psi = -sin_psi;
  }

  Vector3d temp = *this - origin;
  Vector3d result = temp;

  result.sety(temp.gety() * cos_phi + temp.getz() * sin_phi);
  result.setz(-temp.gety() * sin_phi + temp.getz() * cos_phi);

  temp = result;

  result.setx(temp.getx() * cos_theta - temp.getz() * sin_theta);
  result.setz(temp.getx() * sin_theta + temp.getz() * cos_theta);

  temp = result;

  result.setx(temp.getx() * cos_psi + temp.gety() * sin_psi);
  result.sety(-temp.getx() * sin_psi + temp.gety() * cos_psi);

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

template <typename T>
inline Vector3d<T> operator*(const T &scalar, const Vector3d<T> &v)
{
  return Vector3d(v.x * scalar, v.y * scalar, v.z * scalar);
}

#endif // RAyTRACER_VECTOR3D_H_