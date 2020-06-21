inline
GCV_VECTOR3D::GCV_VECTOR3D(double f)
{
    x = y = z = f;
}

inline
GCV_VECTOR3D::GCV_VECTOR3D(double _x, double _y, double _z)
{
    x = _x; y = _y; z = _z;
}

inline
GCV_VECTOR3D::GCV_VECTOR3D(const double f[3])
{
    x = f[0]; y = f[1]; z = f[2];
}

// =====================================
// Access grants
// =====================================

inline const double&
GCV_VECTOR3D::operator[](int i) const
{
    return (&x)[i];
}

inline double&
GCV_VECTOR3D::operator[](int i)
{
    return (&x)[i];
}

inline double&
GCV_VECTOR3D::operator()(int i)
{
    return (&x)[i];
}

// =====================================
// Assignment operators
// =====================================

inline GCV_VECTOR3D&
GCV_VECTOR3D::operator += (const GCV_VECTOR3D& v)
{
   x += v.x;   y += v.y;   z += v.z;
   return *this;
}

inline GCV_VECTOR3D&
GCV_VECTOR3D::operator -= (const GCV_VECTOR3D& v)
{
   x -= v.x;   y -= v.y;   z -= v.z;
   return *this;
}

inline GCV_VECTOR3D&
GCV_VECTOR3D::operator *= (const GCV_VECTOR3D& v)
{
   x *= v.x;   y *= v.y;   z *= v.z;
   return *this;
}

inline GCV_VECTOR3D&
GCV_VECTOR3D::operator /= (const GCV_VECTOR3D& v)
{
   x /= v.x;   y /= v.y;   z /= v.z;
   return *this;
}

inline GCV_VECTOR3D&
GCV_VECTOR3D::operator *= (double s)
{
   x *= s;   y *= s;   z *= s;
   return *this;
}

inline GCV_VECTOR3D&
GCV_VECTOR3D::operator /= (double s)
{
   x /= s;   y /= s;   z /= s;
   return *this;
}

inline GCV_VECTOR3D
operator + (const GCV_VECTOR3D& v)
{
   return v;
}

inline GCV_VECTOR3D
operator - (const GCV_VECTOR3D& v)
{
   return GCV_VECTOR3D(-v.x, -v.y, -v.z);
}

inline GCV_VECTOR3D
operator + (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2)
{
   return GCV_VECTOR3D(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
}

inline GCV_VECTOR3D
operator - (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2)
{
   return GCV_VECTOR3D(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
}

inline double
operator * (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2)
{
   return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

inline GCV_VECTOR3D
operator / (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2)
{
   return GCV_VECTOR3D(v1.x/v2.x, v1.y/v2.y, v1.z/v2.z);
}

inline int
operator < (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2)
{
   return v1[0] < v2[0] && v1[1] < v2[1] && v1[2] < v2[2];
}

inline int
operator <= (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2)
{
   return v1[0] <= v2[0] && v1[1] <= v2[1] && v1[2] <= v2[2];
}

inline GCV_VECTOR3D
operator * (const GCV_VECTOR3D& v, double s)
{
   return GCV_VECTOR3D(s*v.x, s*v.y, s*v.z);
}

inline GCV_VECTOR3D
operator * (double s, const GCV_VECTOR3D& v)
{
   return GCV_VECTOR3D(s*v.x, s*v.y, s*v.z);
}

inline GCV_VECTOR3D
operator / (const GCV_VECTOR3D& v, double s)
{
   return GCV_VECTOR3D(v.x/s, v.y/s, v.z/s);
}

inline int
operator == (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2)
{
   return v1.x==v2.x && v1.y==v2.y && v1.z == v2.z;
}

inline double
Magnitude (const GCV_VECTOR3D& v)
{
   return (double) sqrt(SquareMagnitude(v));
}

inline double
SquareMagnitude (const GCV_VECTOR3D& v)
{
   return v.x*v.x + v.y*v.y + v.z*v.z;
}

inline GCV_VECTOR3D
Normalize (const GCV_VECTOR3D& v)
{
   return v / Magnitude(v);
}

inline double
Min (const GCV_VECTOR3D& v)
{
   double ret = v.x;
   if (v.y < ret) ret = v.y;
   if (v.z < ret) ret = v.z;
   return ret;
}

inline double
Max (const GCV_VECTOR3D& v)
{
   double ret = v.x;
   if (ret < v.y) ret = v.y;
   if (ret < v.z) ret = v.z;
   return ret;
}

inline GCV_VECTOR3D
Minimize (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2)
{
   return GCV_VECTOR3D( v1[0] < v2[0] ? v1[0] : v2[0],
                   v1[1] < v2[1] ? v1[1] : v2[1],
                   v1[2] < v2[2] ? v1[2] : v2[2]);
}

inline GCV_VECTOR3D
Maximize (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2)
{
   return GCV_VECTOR3D( v1[0] > v2[0] ? v1[0] : v2[0],
                   v1[1] > v2[1] ? v1[1] : v2[1],
                   v1[2] > v2[2] ? v1[2] : v2[2]);
}

inline double
DotProduct (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2)
{
   return v1.x*v2.x + v1.y * v2.y + v1.z*v2.z;
}

inline GCV_VECTOR3D
CrossProduct (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2)
{
	GCV_VECTOR3D result;

	result[0] = v1[1] * v2[2] - v1[2] * v2[1];
	result[1] = v1[2] * v2[0] - v1[0] * v2[2];
	result[2] = v1[0] * v2[1] - v1[1] * v2[0];

	return result;
}


inline GCV_MATRIX3D
TranspProduct (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2)
{
	GCV_MATRIX3D result;

	for( int y = 0; y < 3; y++)
			for( int x = 0; x < 3; x++)
				result(y,x) = v1[y] * v2[x];

	return result;
}


inline GCV_MATRIX3D
operator* (const GCV_MATRIX3D a, const GCV_MATRIX3D b)
{
    GCV_MATRIX3D ret;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            ret(i, j) = 0.0f;
            for (int k=0; k<4; k++) {
                ret(i, j) += a(i, k) * b(k, j);
            }
		}
    }
    return ret;
}

inline GCV_MATRIX3D
operator* ( double aVal, const GCV_MATRIX3D a)
{
    GCV_MATRIX3D ret;
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            ret(i, j) = a(i,j) * aVal;
        }
    }
    return ret;
}
