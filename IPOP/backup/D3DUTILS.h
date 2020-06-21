// D3Dd3d.H
#ifndef D3DUTILS_H 
#define D3DUTILS_H 
/* 
**----------------------------------------------------------------------------- 
** Name:    D3Dd3d.h 
** Purpose: Various D3D utility functions 
** Notes: 
** 
** Improved by Alexander M. Roehnisch 2005
** Copyright (c) 1995 - 1997 by Microsoft, all rights reserved 
**----------------------------------------------------------------------------- 
*/ 
 
#define D3D_OVERLOADS 


typedef struct _D3DVECTOR {
    union {
	D3DVALUE x;
	D3DVALUE dvX;
    };
    union {
	D3DVALUE y;
	D3DVALUE dvY;
    };
    union {
	D3DVALUE z;
	D3DVALUE dvZ;
    };
#if (defined __cplusplus) && (defined D3D_OVERLOADS)

public:

    // =====================================
    // Constructors
    // =====================================

    _D3DVECTOR() {  x = y = z = 0; }
    _D3DVECTOR(D3DVALUE f);
    _D3DVECTOR(D3DVALUE _x, D3DVALUE _y, D3DVALUE _z);
    _D3DVECTOR(const D3DVALUE f[3]);

    // =====================================
    // Access grants
    // =====================================

    const D3DVALUE&operator[](int i) const;
    D3DVALUE&operator[](int i);

    // =====================================
    // Assignment operators
    // =====================================

    _D3DVECTOR& operator += (const _D3DVECTOR& v);
    _D3DVECTOR& operator -= (const _D3DVECTOR& v);
    _D3DVECTOR& operator *= (const _D3DVECTOR& v);
    _D3DVECTOR& operator /= (const _D3DVECTOR& v);
    _D3DVECTOR& operator *= (D3DVALUE s);
    _D3DVECTOR& operator /= (D3DVALUE s);

    // =====================================
    // Unary operators
    // =====================================

    friend _D3DVECTOR operator + (const _D3DVECTOR& v);
    friend _D3DVECTOR operator - (const _D3DVECTOR& v);


    // =====================================
    // Binary operators
    // =====================================

    // Addition and subtraction
        friend _D3DVECTOR operator + (const _D3DVECTOR& v1, const _D3DVECTOR& v2);
        friend _D3DVECTOR operator - (const _D3DVECTOR& v1, const _D3DVECTOR& v2);
    // Scalar multiplication and division
        friend _D3DVECTOR operator * (const _D3DVECTOR& v, D3DVALUE s);
        friend _D3DVECTOR operator * (D3DVALUE s, const _D3DVECTOR& v);
        friend _D3DVECTOR operator / (const _D3DVECTOR& v, D3DVALUE s);
    // Memberwise multiplication and division
        friend _D3DVECTOR operator * (const _D3DVECTOR& v1, const _D3DVECTOR& v2);
        friend _D3DVECTOR operator / (const _D3DVECTOR& v1, const _D3DVECTOR& v2);

    // Vector dominance
        friend int operator < (const _D3DVECTOR& v1, const _D3DVECTOR& v2);
        friend int operator <= (const _D3DVECTOR& v1, const _D3DVECTOR& v2);

    // Bitwise equality
        friend int operator == (const _D3DVECTOR& v1, const _D3DVECTOR& v2);

    // Length-related functions
        friend D3DVALUE SquareMagnitude (const _D3DVECTOR& v);
        friend D3DVALUE Magnitude (const _D3DVECTOR& v);

    // Returns vector with same direction and unit length
        friend _D3DVECTOR Normalize (const _D3DVECTOR& v);

    // Return min/max component of the input vector
        friend D3DVALUE Min (const _D3DVECTOR& v);
        friend D3DVALUE Max (const _D3DVECTOR& v);

    // Return memberwise min/max of input vectors
        friend _D3DVECTOR Minimize (const _D3DVECTOR& v1, const _D3DVECTOR& v2);
        friend _D3DVECTOR Maximize (const _D3DVECTOR& v1, const _D3DVECTOR& v2);

    // Dot and cross product
        friend D3DVALUE DotProduct (const _D3DVECTOR& v1, const _D3DVECTOR& v2);
        friend _D3DVECTOR CrossProduct (const _D3DVECTOR& v1, const _D3DVECTOR& v2);

#endif

} D3DVECTOR, *LPD3DVECTOR;

#if (defined __cplusplus) && (defined D3D_OVERLOADS)
#include "d3dvec.inl"
#endif




typedef struct _D3DMATRIX {
#if (defined __cplusplus) && (defined D3D_OVERLOADS)
    union {
        struct {
#endif

            D3DVALUE        _11, _12, _13, _14;
            D3DVALUE        _21, _22, _23, _24;
            D3DVALUE        _31, _32, _33, _34;
            D3DVALUE        _41, _42, _43, _44;

#if (defined __cplusplus) && (defined D3D_OVERLOADS)
        };
        D3DVALUE m[4][4];
    };
    _D3DMATRIX(){}
    _D3DMATRIX( D3DVALUE _m00, D3DVALUE _m01, D3DVALUE _m02, D3DVALUE _m03,
                D3DVALUE _m10, D3DVALUE _m11, D3DVALUE _m12, D3DVALUE _m13,
                D3DVALUE _m20, D3DVALUE _m21, D3DVALUE _m22, D3DVALUE _m23,
                D3DVALUE _m30, D3DVALUE _m31, D3DVALUE _m32, D3DVALUE _m33
        ) 
        {
                m[0][0] = _m00; m[0][1] = _m01; m[0][2] = _m02; m[0][3] = _m03;
                m[1][0] = _m10; m[1][1] = _m11; m[1][2] = _m12; m[1][3] = _m13;
                m[2][0] = _m20; m[2][1] = _m21; m[2][2] = _m22; m[2][3] = _m23;
                m[3][0] = _m30; m[3][1] = _m31; m[3][2] = _m32; m[3][3] = _m33;
        }

    D3DVALUE& operator()(int iRow, int iColumn) { return m[iRow][iColumn]; }
    const D3DVALUE& operator()(int iRow, int iColumn) const { return m[iRow][iColumn]; }
#endif
} D3DMATRIX, *LPD3DMATRIX;



#include <math.h>

// =====================================
// Constructors
// =====================================

inline
_D3DVECTOR::_D3DVECTOR(D3DVALUE f)
{
    x = y = z = f;
}

inline
_D3DVECTOR::_D3DVECTOR(D3DVALUE _x, D3DVALUE _y, D3DVALUE _z)
{
    x = _x; y = _y; z = _z;
}

inline
_D3DVECTOR::_D3DVECTOR(const D3DVALUE f[3])
{
    x = f[0]; y = f[1]; z = f[2];
}

// =====================================
// Access grants
// =====================================

inline const D3DVALUE&
_D3DVECTOR::operator[](int i) const
{
    return (&x)[i];
}

inline D3DVALUE&
_D3DVECTOR::operator[](int i)
{
    return (&x)[i];
}


// =====================================
// Assignment operators
// =====================================

inline _D3DVECTOR&
_D3DVECTOR::operator += (const _D3DVECTOR& v)
{
   x += v.x;   y += v.y;   z += v.z;
   return *this;
}

inline _D3DVECTOR&
_D3DVECTOR::operator -= (const _D3DVECTOR& v)
{
   x -= v.x;   y -= v.y;   z -= v.z;
   return *this;
}

inline _D3DVECTOR&
_D3DVECTOR::operator *= (const _D3DVECTOR& v)
{
   x *= v.x;   y *= v.y;   z *= v.z;
   return *this;
}

inline _D3DVECTOR&
_D3DVECTOR::operator /= (const _D3DVECTOR& v)
{
   x /= v.x;   y /= v.y;   z /= v.z;
   return *this;
}

inline _D3DVECTOR&
_D3DVECTOR::operator *= (D3DVALUE s)
{
   x *= s;   y *= s;   z *= s;
   return *this;
}

inline _D3DVECTOR&
_D3DVECTOR::operator /= (D3DVALUE s)
{
   x /= s;   y /= s;   z /= s;
   return *this;
}

inline _D3DVECTOR
operator + (const _D3DVECTOR& v)
{
   return v;
}

inline _D3DVECTOR
operator - (const _D3DVECTOR& v)
{
   return _D3DVECTOR(-v.x, -v.y, -v.z);
}

inline _D3DVECTOR
operator + (const _D3DVECTOR& v1, const _D3DVECTOR& v2)
{
   return _D3DVECTOR(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
}

inline _D3DVECTOR
operator - (const _D3DVECTOR& v1, const _D3DVECTOR& v2)
{
   return _D3DVECTOR(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
}

inline _D3DVECTOR
operator * (const _D3DVECTOR& v1, const _D3DVECTOR& v2)
{
   return _D3DVECTOR(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z);
}

inline _D3DVECTOR
operator / (const _D3DVECTOR& v1, const _D3DVECTOR& v2)
{
   return _D3DVECTOR(v1.x/v2.x, v1.y/v2.y, v1.z/v2.z);
}

inline int
operator < (const _D3DVECTOR& v1, const _D3DVECTOR& v2)
{
   return v1[0] < v2[0] && v1[1] < v2[1] && v1[2] < v2[2];
}

inline int
operator <= (const _D3DVECTOR& v1, const _D3DVECTOR& v2)
{
   return v1[0] <= v2[0] && v1[1] <= v2[1] && v1[2] <= v2[2];
}

inline _D3DVECTOR
operator * (const _D3DVECTOR& v, D3DVALUE s)
{
   return _D3DVECTOR(s*v.x, s*v.y, s*v.z);
}

inline _D3DVECTOR
operator * (D3DVALUE s, const _D3DVECTOR& v)
{
   return _D3DVECTOR(s*v.x, s*v.y, s*v.z);
}

inline _D3DVECTOR
operator / (const _D3DVECTOR& v, D3DVALUE s)
{
   return _D3DVECTOR(v.x/s, v.y/s, v.z/s);
}

inline int
operator == (const _D3DVECTOR& v1, const _D3DVECTOR& v2)
{
   return v1.x==v2.x && v1.y==v2.y && v1.z == v2.z;
}

inline D3DVALUE
Magnitude (const _D3DVECTOR& v)
{
   return (D3DVALUE) sqrt(SquareMagnitude(v));
}

inline D3DVALUE
SquareMagnitude (const _D3DVECTOR& v)
{
   return v.x*v.x + v.y*v.y + v.z*v.z;
}

inline _D3DVECTOR
Normalize (const _D3DVECTOR& v)
{
   return v / Magnitude(v);
}

inline D3DVALUE
Min (const _D3DVECTOR& v)
{
   D3DVALUE ret = v.x;
   if (v.y < ret) ret = v.y;
   if (v.z < ret) ret = v.z;
   return ret;
}

inline D3DVALUE
Max (const _D3DVECTOR& v)
{
   D3DVALUE ret = v.x;
   if (ret < v.y) ret = v.y;
   if (ret < v.z) ret = v.z;
   return ret;
}

inline _D3DVECTOR
Minimize (const _D3DVECTOR& v1, const _D3DVECTOR& v2)
{
   return _D3DVECTOR( v1[0] < v2[0] ? v1[0] : v2[0],
                   v1[1] < v2[1] ? v1[1] : v2[1],
                   v1[2] < v2[2] ? v1[2] : v2[2]);
}

inline _D3DVECTOR
Maximize (const _D3DVECTOR& v1, const _D3DVECTOR& v2)
{
   return _D3DVECTOR( v1[0] > v2[0] ? v1[0] : v2[0],
                   v1[1] > v2[1] ? v1[1] : v2[1],
                   v1[2] > v2[2] ? v1[2] : v2[2]);
}

inline D3DVALUE
DotProduct (const _D3DVECTOR& v1, const _D3DVECTOR& v2)
{
   return v1.x*v2.x + v1.y * v2.y + v1.z*v2.z;
}

inline _D3DVECTOR
CrossProduct (const _D3DVECTOR& v1, const _D3DVECTOR& v2)
{
	_D3DVECTOR result;

	result[0] = v1[1] * v2[2] - v1[2] * v2[1];
	result[1] = v1[2] * v2[0] - v1[0] * v2[2];
	result[2] = v1[0] * v2[1] - v1[1] * v2[0];

	return result;
}



 
extern const float pi; 
 
/* 
**----------------------------------------------------------------------------- 
** Function Prototypes 
**----------------------------------------------------------------------------- 
*/ 

struct D3DMATRIXBIG{
	float m[99][99];
	D3DMATRIXBIG(){
		for(int i=0;i<99;i++)for(int j=0;j<99;j++)m[i][j]=0;};
	float& operator()(int r, int c) { return m[r][c];}
	float& MaxValue(int& c, int& r){ float max=0; 
		for(int i=0;i<99;i++) for(int j=0;j<99;j++){
			if(m[i][j]>max){max=m[i][j];c=i;r=j;}  }
		return max;};
	float& MinValue(int& c, int& r) { float min=99999999; 
	for(int i=0;i<99;i++) for(int j=0;j<99;j++)	{
		if(m[i][j]<min){min=m[i][j];;c=i;r=j;} }
		return min;};
};

 
namespace d3d{

// generic simple matrix routines 
extern D3DMATRIX ZeroMatrix(void); 
extern D3DMATRIX IdentityMatrix(void); 
 
extern D3DMATRIX ProjectionMatrix(const float near_plane, const float far_plane, const float fov); 
extern D3DMATRIX ViewMatrix(const D3DVECTOR & from, const D3DVECTOR & at,  
const D3DVECTOR & up, const float roll=0.0f); 
 
extern D3DMATRIX RotateXMatrix(const float rads); 
extern D3DMATRIX RotateYMatrix(const float rads); 
extern D3DMATRIX RotateZMatrix(const float rads); 
extern D3DMATRIX TranslateMatrix(const float dx, const float dy, const float dz); 
extern D3DMATRIX TranslateMatrix(const D3DVECTOR & v); 
extern D3DMATRIX ScaleMatrix(const float size); 
extern D3DMATRIX ScaleMatrix(const float a, const float b, const float c); 
extern D3DMATRIX ScaleMatrix(const D3DVECTOR & v); 
 
extern D3DMATRIX MatrixMult(const D3DMATRIX & a, const D3DMATRIX & b); 
extern D3DMATRIX MatrixInverse(const D3DMATRIX & m); 
extern D3DMATRIX MatrixTranspose(const D3DMATRIX & m); 
 
extern D3DVECTOR TransformVector(const D3DVECTOR & v, const D3DMATRIX & m); 
extern D3DVECTOR TransformVector( const D3DMATRIX & m,const D3DVECTOR & v); 
extern D3DVECTOR TransformNormal(const D3DVECTOR & v, const D3DMATRIX & m); 
 

extern void RotMatToCardan(const D3DMATRIX & aMat, float &alpha_grad, float &beta_grad, float &gamma_grad);
extern void RotMatToCardan(const D3DMATRIX & aMat, float &alpha_grad, float &beta_grad, float &gamma_grad);
extern void RotMatToXYXEuler(const D3DMATRIX & aMat, float &psi, float &theta, float &phigrad);
extern void RotMatToXYZEuler(const D3DMATRIX & aMat, float &AlphaGrad, float &BetaGrad, float &GammaGrad);
extern void XYXEulerToRotMat(float PsiGrad, float ThetaGrad, float PhiGrad, D3DMATRIX & aMat);
extern void XYZEulerToRotMat(float PsiGrad, float ThetaGrad, float PhiGrad, D3DMATRIX & aMat);
extern void CardanToRotMat(float alpha, float beta, float gamma, const D3DMATRIX & aRotMat);



// Other stuff 
extern float rnd(void); 
 
}
 
 
/* 
**----------------------------------------------------------------------------- 
**End of File 
**----------------------------------------------------------------------------- 
*/ 
#endif // D3DUTILS_H