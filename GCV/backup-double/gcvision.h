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
	double x;
	double y;
	double z;

public:

    // =====================================
    // Constructors
    // =====================================

    GCV_VECTOR3D() {  x = y = z = 0; }
    GCV_VECTOR3D(double f);
    GCV_VECTOR3D(double _x, double _y, double _z);
    GCV_VECTOR3D(const double f[3]);

    // =====================================
    // Access grants
    // =====================================

    const double&operator[](int i) const;
    double&operator[](int i);
    double&operator()(int i);

    // =====================================
    // Assignment operators
    // =====================================

    GCV_VECTOR3D& operator += (const GCV_VECTOR3D& v);
    GCV_VECTOR3D& operator -= (const GCV_VECTOR3D& v);
    GCV_VECTOR3D& operator *= (const GCV_VECTOR3D& v);
    GCV_VECTOR3D& operator /= (const GCV_VECTOR3D& v);
    GCV_VECTOR3D& operator *= (double s);
    GCV_VECTOR3D& operator /= (double s);

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
        friend GCV_VECTOR3D operator * (const GCV_VECTOR3D& v, double s);
        friend GCV_VECTOR3D operator * (double s, const GCV_VECTOR3D& v);
        friend GCV_VECTOR3D operator / (const GCV_VECTOR3D& v, double s);
    // Memberwise multiplication and division
        friend double operator * (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);
        friend GCV_VECTOR3D operator / (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);

    // Vector dominance
        friend int operator < (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);
        friend int operator <= (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);

    // Bitwise equality
        friend int operator == (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);

    // Length-related functions
        friend double SquareMagnitude (const GCV_VECTOR3D& v);
        friend double Magnitude (const GCV_VECTOR3D& v);

    // Returns vector with same direction and unit length
        friend GCV_VECTOR3D Normalize (const GCV_VECTOR3D& v);

    // Return min/max component of the input vector
        friend double Min (const GCV_VECTOR3D& v);
        friend double Max (const GCV_VECTOR3D& v);

    // Return memberwise min/max of input vectors
        friend GCV_VECTOR3D Minimize (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);
        friend GCV_VECTOR3D Maximize (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);

    // Dot and cross product
        friend double DotProduct (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);
        friend GCV_VECTOR3D CrossProduct (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);
        friend GCV_MATRIX3D TranspProduct (const GCV_VECTOR3D& v1, const GCV_VECTOR3D& v2);

		void clear(){ x = y = z = 0;};

};

struct GCV_MATRIX3D {
	union{
		 struct {
            double        _11, _12, _13, _14;
            double        _21, _22, _23, _24;
            double        _31, _32, _33, _34;
            double        _41, _42, _43, _44;
		 };
        double m[4][4];

    };
    GCV_MATRIX3D()
		{
                m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
                m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
                m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
                m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
        }
    GCV_MATRIX3D( double _m00, double _m01, double _m02, double _m03,
                double _m10, double _m11, double _m12, double _m13,
                double _m20, double _m21, double _m22, double _m23,
                double _m30, double _m31, double _m32, double _m33
        ) 
        {
                m[0][0] = _m00; m[0][1] = _m01; m[0][2] = _m02; m[0][3] = _m03;
                m[1][0] = _m10; m[1][1] = _m11; m[1][2] = _m12; m[1][3] = _m13;
                m[2][0] = _m20; m[2][1] = _m21; m[2][2] = _m22; m[2][3] = _m23;
                m[3][0] = _m30; m[3][1] = _m31; m[3][2] = _m32; m[3][3] = _m33;
        }

    inline double& operator()(int iRow, int iColumn) { return m[iRow][iColumn]; }
    inline const double& operator()(int iRow, int iColumn) const { return m[iRow][iColumn]; }
    friend GCV_MATRIX3D operator* (const GCV_MATRIX3D vec1, const GCV_MATRIX3D vec2);
    friend GCV_MATRIX3D operator* (double aVal, const GCV_MATRIX3D vec);
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
	double OrthDistance;
};

struct GCV_POINT2D{
	double x,y;
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
	double trans_x, trans_y, trans_z;
	double rot_x, rot_y, rot_z;
	GCV_EULER3D(){
		trans_x= trans_y= trans_z = rot_x = rot_y = rot_z = 0;};
	GCV_EULER3D(double a, double b, double c, double d, double e, double f){
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
	double DistortionParameters[6], CameraMatrix[9], FocalLength, CellSizeX,
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


 
extern const double pi; 
 
/* 
**----------------------------------------------------------------------------- 
** Function Prototypes 
**----------------------------------------------------------------------------- 
*/ 

struct GCV_MATRIXBIG{
public:
	double m[99][99];
	GCV_MATRIXBIG(){
		for(int i=0;i<99;i++)for(int j=0;j<99;j++)m[i][j]=999999.0;}
	double& operator()(int r, int c) { return m[r][c];};
	double& MaxValue(int& c, int& r){ double max=0; 
		for(int i=0;i<99;i++) for(int j=0;j<99;j++){
			if(m[i][j]>max){max=m[i][j];c=i;r=j;}  }
		return max;};
	double& MinValue(int& r, int& c) { double min=99999999; 
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
 
extern GCV_MATRIX3D ProjectionMatrix(const double near_plane, const double far_plane, const double fov); 
extern GCV_MATRIX3D ViewMatrix(const GCV_VECTOR3D & from, const GCV_VECTOR3D & at,  
const GCV_VECTOR3D & up, const double roll=0.0f); 
 
extern GCV_MATRIX3D RotateXMatrix(const double rads); 
extern GCV_MATRIX3D RotateYMatrix(const double rads); 
extern GCV_MATRIX3D RotateZMatrix(const double rads); 
extern GCV_MATRIX3D TranslateMatrix(const double dx, const double dy, const double dz); 
extern GCV_MATRIX3D TranslateMatrix(const GCV_VECTOR3D & v); 
extern GCV_MATRIX3D ScaleMatrix(const double size); 
extern GCV_MATRIX3D ScaleMatrix(const double a, const double b, const double c); 
extern GCV_MATRIX3D ScaleMatrix(const GCV_VECTOR3D & v); 
 
extern GCV_MATRIX3D MatrixMult(const GCV_MATRIX3D & a, const GCV_MATRIX3D & b); 
extern GCV_MATRIX3D MatrixMult(const double  a, const GCV_MATRIX3D  b); 
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
 

extern void RotMatToCardan(const GCV_MATRIX3D & aMat, double &alpha_grad, double &beta_grad, double &gamma_grad);
extern void RotMatToCardan(const GCV_MATRIX3D & aMat, double &alpha_grad, double &beta_grad, double &gamma_grad);
extern void RotMatToXYXEuler(const GCV_MATRIX3D & aMat, double &psi, double &theta, double &phigrad);
extern void RotMatToXYZEuler(const GCV_MATRIX3D & aMat, double &AlphaGrad, double &BetaGrad, double &GammaGrad);
extern void XYXEulerToRotMat(double PsiGrad, double ThetaGrad, double PhiGrad, GCV_MATRIX3D & aMat);
extern void XYZEulerToRotMat(double PsiGrad, double ThetaGrad, double PhiGrad, GCV_MATRIX3D & aMat);
extern void CardanToRotMat(double alpha, double beta, double gamma, const GCV_MATRIX3D & aRotMat);
extern void AngleAndAxisFromRotMat(double &aAngleGrad, GCV_VECTOR3D &aDirection, const GCV_MATRIX3D aRotMat);

extern double DistanceLinePoint( GCV_VECTOR3D& aProjR, GCV_VECTOR3D& aObjP);
extern void ConvertTransformationToPlane(GCV_MATRIX3D aTrafo, GCV_PLANE3D aPlane);
extern GCV_VECTOR3D CalculateCrosspointProjRayPlane(GCV_VECTOR3D aLine, GCV_PLANE3D aPlane);
extern bool CalculateCrossPoint(const GCV_LINE2D &line1, const GCV_LINE2D &line2, GCV_POINT2D& crosspoint);

extern GCV_VECTOR3D ConvertImagePtToProjectionRay(GCV_CAMERA camera, GCV_POINT2D pt);
extern void	EulerToMatrix(GCV_EULER3D eul, GCV_MATRIX3D &mat);
extern void	MatrixToEuler(GCV_MATRIX3D mat, GCV_EULER3D &eul);

extern double VectorMult(const GCV_VECTOR3D & v1, const GCV_VECTOR3D & v2); 

// Other stuff 
//extern double rnd(void); 
 
}
 
 
/* 
**----------------------------------------------------------------------------- 
**End of File 
**----------------------------------------------------------------------------- 
*/ 
#endif