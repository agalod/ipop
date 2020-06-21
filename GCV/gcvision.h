// gcvision.H
#ifndef _GCV_ 
#define _GCV_ 
/* 
**----------------------------------------------------------------------------- 
** Name:    gcvision.h 
** Purpose: Various D3D utility functions 
** Notes: 
** 
** by Alexander M. Roehnisch June 2005
**----------------------------------------------------------------------------- 
*/ 
#include <math.h> 
#include <vector>
//using namespace std; 

struct GCV_MATRIX3D;

struct GCV_VECTOR3D {
	float x;
	float y;
	float z;

public:

    // =====================================
    // Constructors
    // =====================================

    GCV_VECTOR3D() {  x = y = z = 0; }
    GCV_VECTOR3D(float f);
    GCV_VECTOR3D(float _x, float _y, float _z);
    GCV_VECTOR3D(const float f[3]);

    // =====================================
    // Access grants
    // =====================================

    const float&operator[](int i) const;
    float&operator[](int i);
    float&operator()(int i);

    // =====================================
    // Assignment operators
    // =====================================

    GCV_VECTOR3D& operator += (const GCV_VECTOR3D& v);
    GCV_VECTOR3D& operator -= (const GCV_VECTOR3D& v);
    GCV_VECTOR3D& operator *= (const GCV_VECTOR3D& v);
    GCV_VECTOR3D& operator /= (const GCV_VECTOR3D& v);
    GCV_VECTOR3D& operator *= (float s);
    GCV_VECTOR3D& operator /= (float s);

    // =====================================
    // Unary operators
    // =====================================
  
    friend GCV_VECTOR3D operator + (const GCV_VECTOR3D& v);
    friend GCV_VECTOR3D operator - (const GCV_VECTOR3D& v);


    // =====================================
    // Binary operators
    // =====================================

    // Addition and subtraction
        friend GCV_VECTOR3D operator + (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);
        friend GCV_VECTOR3D operator - (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);
    // Scalar multiplication and division
        friend GCV_VECTOR3D operator * (const GCV_VECTOR3D& v, float s);
        friend GCV_VECTOR3D operator * (float s, const GCV_VECTOR3D& v);
        friend GCV_VECTOR3D operator / (const GCV_VECTOR3D& v, float s);
    // Memberwise multiplication and division
        friend float operator * (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);
        friend GCV_VECTOR3D operator / (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);

    // Vector dominance
        friend int operator < (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);
        friend int operator <= (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);

    // Bitwise equality
        friend int operator == (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);

    // Length-related functions
        friend float SquareMagnitude (const GCV_VECTOR3D& v);
        friend float Magnitude (const GCV_VECTOR3D& v);

    // Returns vector with same direction and unit length
        friend GCV_VECTOR3D Normalize (const GCV_VECTOR3D& v);

    // Return min/max component of the input vector
        friend float Min (const GCV_VECTOR3D& v);
        friend float Max (const GCV_VECTOR3D& v);

    // Return memberwise min/max of input vectors
        friend GCV_VECTOR3D Minimize (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);
        friend GCV_VECTOR3D Maximize (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);

    // Dot and cross product
        friend float DotProduct (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);
        friend GCV_VECTOR3D CrossProduct (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);
        friend GCV_MATRIX3D TranspProduct (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);

		void clear(){ x = y = z = 0;};

};

struct GCV_MATRIX3D {
	union{
		 struct {
            float        _11, _12, _13, _14;
            float        _21, _22, _23, _24;
            float        _31, _32, _33, _34;
            float        _41, _42, _43, _44;
		 };
        float m[4][4];

    };
    GCV_MATRIX3D()
		{
                m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
                m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
                m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
                m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
        }
    GCV_MATRIX3D( float _m00, float _m01, float _m02, float _m03,
                float _m10, float _m11, float _m12, float _m13,
                float _m20, float _m21, float _m22, float _m23,
                float _m30, float _m31, float _m32, float _m33
        ) 
        {
                m[0][0] = _m00; m[0][1] = _m01; m[0][2] = _m02; m[0][3] = _m03;
                m[1][0] = _m10; m[1][1] = _m11; m[1][2] = _m12; m[1][3] = _m13;
                m[2][0] = _m20; m[2][1] = _m21; m[2][2] = _m22; m[2][3] = _m23;
                m[3][0] = _m30; m[3][1] = _m31; m[3][2] = _m32; m[3][3] = _m33;
        }

    inline float& operator()(int iRow, int iColumn) { return m[iRow][iColumn]; }
    inline const float& operator()(int iRow, int iColumn) const { return m[iRow][iColumn]; }
    friend GCV_MATRIX3D operator* (const GCV_MATRIX3D vec1, const GCV_MATRIX3D vec2);
    friend GCV_MATRIX3D operator* (float aVal, const GCV_MATRIX3D vec);
	GCV_VECTOR3D GetTranslation(){ GCV_VECTOR3D ret; 
		for(int i=0;i<3;i++) ret(i)=m[i][3]; return ret; };
	void SetTranslation(GCV_VECTOR3D vec){ ; 
		for(int i=0;i<3;i++) m[i][3]=vec(i); };
	GCV_MATRIX3D GetRotation(){ GCV_MATRIX3D ret;
		for(int i=0;i<3;i++) for(int j=0;j<3;j++) ret(i,j)=m[i][j]; return ret; };
	void SetRotation(GCV_MATRIX3D mat){ ;
		for(int i=0;i<3;i++) for(int j=0;j<3;j++) m[i][j]=mat(i,j); };
};


struct GCV_PLANE3D{
	GCV_VECTOR3D Normal;
	float OrthDistance;
};

struct GCV_POINT2D{
	float x,y;
	GCV_POINT2D(){x=y=0;}
	GCV_POINT2D(CPoint pt){this->x=pt.x; this->y=pt.y;}
	GCV_POINT2D& operator-(GCV_POINT2D pt){
		GCV_POINT2D ret; ret.x = this->x - pt.x; ret.y = this->y - pt.y; return ret;};
		bool operator!=(GCV_POINT2D pt){
			if(this->x==pt.x&&this->y==pt.y) return false;
			else return true;};
		bool operator==(GCV_POINT2D pt){
			if(this->x==pt.x&&this->y==pt.y) return true;
			else return false;};
			void operator=(CPoint pt){this->x=pt.x; this->y=pt.y;};
			void clear(){x=y=0;};
				
} ;


struct GCV_QUAD2D{
	GCV_POINT2D pt1, pt2, pt3, pt4;
	clear(){pt1.x=pt2.x=pt3.x=pt4.x=pt1.y=pt2.y=pt3.y=pt4.y=0;}
};

struct GCV_EULER3D{
	float trans_x, trans_y, trans_z;
	float rot_x, rot_y, rot_z;
	GCV_EULER3D(){
		trans_x= trans_y= trans_z = rot_x = rot_y = rot_z = 0;};
	GCV_EULER3D(float a, float b, float c, float d, float e, float f){
		rot_x = a; rot_y = b; rot_z = c;
		trans_x=d; trans_y=e; trans_z = f; 
	};

	void operator+=(GCV_EULER3D eul){
		this->trans_x+=eul.trans_x;	this->trans_y+=eul.trans_y;
		this->trans_z+=eul.trans_z;	this->rot_x+=eul.rot_x;	
		this->rot_y+=eul.rot_y;	this->rot_z+=eul.rot_z;
	};
	GCV_EULER3D operator+(GCV_EULER3D eul){
		GCV_EULER3D ret;
		ret.trans_x = this->trans_x + eul.trans_x;	
		ret.trans_y = this->trans_y + eul.trans_y;	
		ret.trans_z = this->trans_z + eul.trans_z;	
		ret.rot_x = this->rot_x + eul.rot_x;	
		ret.rot_y = this->rot_y + eul.rot_y;	
		ret.rot_z = this->rot_z + eul.rot_z;	
		return ret;
	};
	GCV_EULER3D operator-(GCV_EULER3D eul){
		GCV_EULER3D ret;
		ret.trans_x = this->trans_x - eul.trans_x;	
		ret.trans_y = this->trans_y - eul.trans_y;	
		ret.trans_z = this->trans_z - eul.trans_z;	
		ret.rot_x = this->rot_x - eul.rot_x;	
		ret.rot_y = this->rot_y - eul.rot_y;	
		ret.rot_z = this->rot_z - eul.rot_z;	
		return ret;
	};
	void clear(){trans_x= trans_y= trans_z = rot_x = rot_y = rot_z = 0;};

};


class GCV_CAMERA{
public:
	float DistortionParameters[6], CameraMatrix[9], FocalLength, CellSizeX,
		CellSizeY, PixNumX, PixNumY, PrincipalPointX, PrincipalPointY;
	GCV_CAMERA():FocalLength(16.8),CellSizeX(8.2),CellSizeY(8.2),PixNumY(576),
		PixNumX(752),PrincipalPointX(PixNumX/2),PrincipalPointY(PixNumY/2)
	{for(int i=0;i<5;i++)DistortionParameters[i]=0;
	for(i=0;i<9;i++)CameraMatrix[i]=0;};
	void operator=(GCV_CAMERA cam){
		PixNumY = cam.PixNumY; PixNumX = cam.PixNumX;
		PrincipalPointX = cam.PrincipalPointX; 
		PrincipalPointY = cam.PrincipalPointY; 
		CellSizeX= cam.CellSizeX; CellSizeY= cam.CellSizeY;
		FocalLength = cam.FocalLength;};
};

struct GCV_LINE3D{
	GCV_VECTOR3D pt1,pt2;
	void clear(){pt1.clear(); pt2.clear();};
};

struct GCV_LINE2D{
	GCV_POINT2D pt1,pt2;
	bool show;
};


struct GCV_VIEWPARAMS{
 GCV_VECTOR3D eye, center, up;
};



struct GCV_IMAGEPOINT3D{
	GCV_VECTOR3D vector;
	GCV_CAMERA camera;
	GCV_POINT2D point;
	GCV_IMAGEPOINT3D(){};
	GCV_IMAGEPOINT3D(GCV_POINT2D pt){
		point = pt;
		vector.x = ( pt.x - camera.PrincipalPointX ) * camera.CellSizeX/1000.0;
		vector.y = ( pt.y - camera.PrincipalPointY ) * camera.CellSizeY/1000.0;
		vector.z = camera.FocalLength; };
	void operator=(GCV_POINT2D pt){
		point = pt;
		vector.x = ( pt.x - camera.PrincipalPointX ) * camera.CellSizeX/1000.0;
		vector.y = ( pt.y - camera.PrincipalPointY ) * camera.CellSizeY/1000.0;
		vector.z = camera.FocalLength; };

};
// =====================================
// Constructors
// =====================================


 
extern const float pi; 
 
/* 
**----------------------------------------------------------------------------- 
** Function Prototypes 
**----------------------------------------------------------------------------- 
*/ 

struct GCV_MATRIXBIG{
public:
	float m[99][99];
	GCV_MATRIXBIG(){
		for(int i=0;i<99;i++)for(int j=0;j<99;j++)m[i][j]=999999.0;}
	float& operator()(int r, int c) { return m[r][c];};
	float& MaxValue(int& c, int& r){ float max=0; 
		for(int i=0;i<99;i++) for(int j=0;j<99;j++){
			if(m[i][j]>max){max=m[i][j];c=i;r=j;}  }
		return max;};
	float& MinValue(int& r, int& c) { float min=99999999; 
	for(int i=0;i<99;i++) for(int j=0;j<99;j++)	{
		if(m[i][j]<min){min=m[i][j];;r=i;c=j;} }
		return min;};
};


struct GCV_MATRIXVECTOR3D{
GCV_MATRIX3D M;
GCV_VECTOR3D V;
};
 

#include "gcvision.inl" 

namespace gcvision{

// generic simple matrix routines 
extern GCV_MATRIX3D ZeroMatrix(void); 
extern GCV_MATRIX3D IdentityMatrix(void); 
 
extern GCV_MATRIX3D ProjectionMatrix(const float near_plane, const float far_plane, const float fov); 
extern GCV_MATRIX3D ViewMatrix(const GCV_VECTOR3D & from, const GCV_VECTOR3D & at,  
const GCV_VECTOR3D & up, const float roll=0.0f); 
 
extern GCV_MATRIX3D RotateXMatrix(const float rads); 
extern GCV_MATRIX3D RotateYMatrix(const float rads); 
extern GCV_MATRIX3D RotateZMatrix(const float rads); 
extern GCV_MATRIX3D TranslateMatrix(const float dx, const float dy, const float dz); 
extern GCV_MATRIX3D TranslateMatrix(const GCV_VECTOR3D & v); 
extern GCV_MATRIX3D ScaleMatrix(const float size); 
extern GCV_MATRIX3D ScaleMatrix(const float a, const float b, const float c); 
extern GCV_MATRIX3D ScaleMatrix(const GCV_VECTOR3D & v); 
 
extern GCV_MATRIX3D MatrixMult(const GCV_MATRIX3D & a, const GCV_MATRIX3D & b); 
extern GCV_MATRIX3D MatrixMult(const float  a, const GCV_MATRIX3D  b); 
extern GCV_MATRIX3D MatrixAdd(const GCV_MATRIX3D & a, const GCV_MATRIX3D & b); 
extern GCV_MATRIX3D MatrixInverse(const GCV_MATRIX3D  m); 
extern GCV_MATRIX3D MatrixTranspose(const GCV_MATRIX3D  m); 
extern GCV_MATRIX3D HMatrixTranspose(const GCV_MATRIX3D  m);
 
extern GCV_VECTOR3D TransformVector(const GCV_VECTOR3D & v, const GCV_MATRIX3D & m); 
extern GCV_VECTOR3D TransformVector( const GCV_MATRIX3D & m,const GCV_VECTOR3D & v); 
extern void	TransformVectorOfVector(GCV_MATRIX3D mat, std::vector< GCV_VECTOR3D > vec);
extern GCV_VECTOR3D TransformNormal(const GCV_VECTOR3D & v, const GCV_MATRIX3D & m); 
extern GCV_MATRIXVECTOR3D SplitMatrix(const GCV_MATRIX3D & m); 
extern void SplitMatrix(const GCV_MATRIX3D & m, GCV_VECTOR3D &v, GCV_MATRIX3D& rm); 
extern GCV_MATRIX3D MergeMatrix(const GCV_VECTOR3D & v, const GCV_MATRIX3D & m); 
extern GCV_MATRIX3D MergeMatrix(const GCV_MATRIXVECTOR3D & mv); 
 

extern void RotMatToCardan(const GCV_MATRIX3D & aMat, float &alpha_grad, float &beta_grad, float &gamma_grad);
extern void RotMatToCardan(const GCV_MATRIX3D & aMat, float &alpha_grad, float &beta_grad, float &gamma_grad);
extern void RotMatToXYXEuler(const GCV_MATRIX3D & aMat, float &psi, float &theta, float &phigrad);
extern void RotMatToXYZEuler(const GCV_MATRIX3D & aMat, float &AlphaGrad, float &BetaGrad, float &GammaGrad);
extern void XYXEulerToRotMat(float PsiGrad, float ThetaGrad, float PhiGrad, GCV_MATRIX3D & aMat);
extern void XYZEulerToRotMat(float PsiGrad, float ThetaGrad, float PhiGrad, GCV_MATRIX3D & aMat);
extern void CardanToRotMat(float alpha, float beta, float gamma, const GCV_MATRIX3D & aRotMat);
extern void AngleAndAxisFromRotMat(float &aAngleGrad, GCV_VECTOR3D &aDirection, const GCV_MATRIX3D aRotMat);

extern float DistanceLinePoint( GCV_VECTOR3D& aProjR, GCV_VECTOR3D& aObjP);
extern void ConvertTransformationToPlane(GCV_MATRIX3D aTrafo, GCV_PLANE3D aPlane);
extern GCV_VECTOR3D CalculateCrosspointProjRayPlane(GCV_VECTOR3D aLine, GCV_PLANE3D aPlane);
extern bool CalculateCrossPoint(const GCV_LINE2D &line1, const GCV_LINE2D &line2, GCV_POINT2D& crosspoint);

extern GCV_VECTOR3D ConvertImagePtToProjectionRay(GCV_CAMERA camera, GCV_POINT2D pt);
extern void	EulerToMatrix(GCV_EULER3D eul, GCV_MATRIX3D &mat);
extern void	MatrixToEuler(GCV_MATRIX3D mat, GCV_EULER3D &eul);

extern float VectorMult(const GCV_VECTOR3D & v1, const GCV_VECTOR3D & v2); 

// Other stuff 
//extern float rnd(void); 
 
}
 
 
/* 
**----------------------------------------------------------------------------- 
**End of File 
**----------------------------------------------------------------------------- 
*/ 
#endif