//D3DUTILS.CPP
/* 
**----------------------------------------------------------------------------- 
** Name:    D3DUTILS.cpp 
** Purpose: Various D3D utility functions 
** Notes: 
** 
** Copyright (c) 1995 - 1997 by Microsoft, all rights reserved. 
**----------------------------------------------------------------------------- 
*/ 
 
// Note:  Must Define D3D_OVERLOADS to get C++ version of D3DMATRIX 
#define D3D_OVERLOADS 
#include "stdafx.h"
#include <float.h> 
#include <math.h> 
 
#include "d3dutils.h" 
 
const float pi = 3.141592654f; 
 
/* 
**----------------------------------------------------------------------------- 
** Functions 
**----------------------------------------------------------------------------- 
*/ 
 
/* 
**----------------------------------------------------------------------------- 
**  Name:       ZeroMatrix 
**  Purpose:sets D3D matrix to all 0's 
**----------------------------------------------------------------------------- 
*/ 
 
D3DMATRIX  
d3d::ZeroMatrix(void) 
{ 
    D3DMATRIX ret; 
    for (int i=0; i<4; i++) { 
        for (int j=0; j<4; j++) { 
            ret(i,j) = 0.0f; 
} 
} 
    return ret; 
} // end ZeroMatrix 
 
/* 
**----------------------------------------------------------------------------- 
**  Name:       IdentityMatrix 
**  Purpose:sets D3D matrix to Identiy (1's on diagonal, zero's elsewhere) 
**----------------------------------------------------------------------------- 
*/ 
 
D3DMATRIX 
d3d::IdentityMatrix(void) 
{ 
    D3DMATRIX ret; 
    for (int i=0; i<4; i++) { 
        for (int j=0; j<4; j++){ 
            ret(i, j) = 0.0f; 
} 
ret(i,i) = 1.0f; 
} 
    return ret; 
} // end IdentityMatrix 
   
/* 
**----------------------------------------------------------------------------- 
**  Name:       ProjectionMatrix 
**  Purpose:sets Projection matrix from fov, near and far planes 
**  Notes: 
**1. fov is in radians. 
**2. See Blinn, "A Trip Down the Graphics pipeline" pg 188 for details. 
**----------------------------------------------------------------------------- 
*/ 
 
D3DMATRIX  
d3d::ProjectionMatrix(const float near_plane,  
 const float far_plane,  
 const float fov) 
{ 
float c, s, Q; 
 
c = (float) cos(fov*0.5); 
s = (float) sin(fov*0.5); 
Q = s/(1.0f - near_plane/far_plane); 
 
    D3DMATRIX ret = ZeroMatrix(); 
    ret(0, 0) = c; 
    ret(1, 1) = c; 
ret(2, 2) = Q; 
ret(3, 2) = -Q*near_plane; 
    ret(2, 3) = s; 
    return ret; 
}// end ProjectionMatrix 
 
/* 
**----------------------------------------------------------------------------- 
**  Name:       ViewMatrix 
**  Purpose:Controls where the camara is. 
**  Notes: 
**1. Note the roll parameter is in radians and rools the viewpoint 
**around the viewing direction 
**----------------------------------------------------------------------------- 
*/ 
 
D3DMATRIX 
d3d::ViewMatrix(const D3DVECTOR& from,  
   const D3DVECTOR& at,  
   const D3DVECTOR& world_up,  
   const float roll) 
{ 
    D3DMATRIX view = IdentityMatrix(); 
    D3DVECTOR up, right, view_dir; 
 
    view_dir = Normalize(at - from); 
right = CrossProduct(world_up, view_dir); 
up = CrossProduct(view_dir, right); 
 
right = Normalize(right); 
up = Normalize(up); 
 
    view(0, 0) = right.x; 
    view(1, 0) = right.y; 
    view(2, 0) = right.z; 
    view(0, 1) = up.x; 
    view(1, 1) = up.y; 
    view(2, 1) = up.z; 
    view(0, 2) = view_dir.x; 
    view(1, 2) = view_dir.y; 
    view(2, 2) = view_dir.z; 
 
    view(3, 0) = -DotProduct(right, from); 
    view(3, 1) = -DotProduct(up, from); 
    view(3, 2) = -DotProduct(view_dir, from); 
 
// Set roll 
if (roll != 0.0f) { 
view = MatrixMult(RotateZMatrix(-roll), view); 
} 
 
    return view; 
} // end ViewMatrix 
 
/* 
**----------------------------------------------------------------------------- 
**  Name:       RotateXMatrix 
**  Purpose:Rotate matrix about X axis 
**----------------------------------------------------------------------------- 
*/ 
 
D3DMATRIX 
d3d::RotateXMatrix(const float rads) 
{ 
float cosine, sine; 
 
cosine = (float) cos(rads); 
sine = (float) sin(rads); 
    D3DMATRIX ret = IdentityMatrix(); 
    ret(1,1) = cosine; 
ret(2,2) = cosine; 
ret(1,2) = -sine; 
ret(2,1) = sine; 
    return ret; 
} // end RotateXMatrix 
 
/* 
**----------------------------------------------------------------------------- 
**  Name:       RotateYMatrix 
**  Purpose:Rotate matrix about Y axis 
**----------------------------------------------------------------------------- 
*/ 
 
D3DMATRIX 
d3d::RotateYMatrix(const float rads) 
{ 
float cosine, sine; 
 
cosine = (float) cos(rads); 
sine = (float) sin(rads); 
    D3DMATRIX ret = IdentityMatrix(); 
    ret(0,0) = cosine; 
ret(2,2) = cosine; 
ret(0,2) = sine; 
ret(2,0) = -sine; 
    return ret; 
} // end RotateY 
   
/* 
**----------------------------------------------------------------------------- 
**  Name:       RotateZMatrix 
**  Purpose:Rotate matrix about Z axis 
**----------------------------------------------------------------------------- 
*/ 
 
D3DMATRIX 
d3d::RotateZMatrix(const float rads) 
{ 
float cosine, sine; 
 
cosine = (float) cos(rads); 
sine = (float) sin(rads); 
    D3DMATRIX ret = IdentityMatrix(); 
    ret(0,0) = cosine; 
ret(1,1) = cosine; 
ret(0,1) = -sine; 
ret(1,0) = sine; 
    return ret; 
} // end RotateZMatrix 
 
/* 
**----------------------------------------------------------------------------- 
**  Name:       TranslateMatrix 
**  Purpose:    Returns matrix to translate by (dx, dy, dz) 
**----------------------------------------------------------------------------- 
*/ 
 
D3DMATRIX  
d3d::TranslateMatrix(const float dx, const float dy, const float dz) 
{ 
    D3DMATRIX ret = IdentityMatrix(); 
ret(3, 0) = dx; 
ret(3, 1) = dy; 
ret(3, 2) = dz; 
return ret; 
} // end TranslateMatrix 
 
/* 
**----------------------------------------------------------------------------- 
**  Name:       TranslateMatrix 
**  Purpose:    Returns matrix to translate by v 
**----------------------------------------------------------------------------- 
*/ 
 
D3DMATRIX  
d3d::TranslateMatrix(const D3DVECTOR& v) 
{ 
    D3DMATRIX ret = IdentityMatrix(); 
ret(3, 0) = v[0]; 
ret(3, 1) = v[1]; 
ret(3, 2) = v[2]; 
return ret; 
} // end TranslateMatrix 
 
/* 
**----------------------------------------------------------------------------- 
**  Name:       ScaleMatrix 
**  Purpose:    scale matrix (uniform) 
**----------------------------------------------------------------------------- 
*/ 
 
D3DMATRIX  
d3d::ScaleMatrix(const float size) 
{ 
    D3DMATRIX ret = IdentityMatrix(); 
ret(0, 0) = size; 
ret(1, 1) = size; 
ret(2, 2) = size; 
return ret; 
} // end ScaleMatrix 
   
/* 
**----------------------------------------------------------------------------- 
**  Name:       ScaleMatrix 
**  Purpose:scale matrix 
**----------------------------------------------------------------------------- 
*/ 
 
D3DMATRIX  
d3d::ScaleMatrix(const float a, const float b, const float c) 
{ 
    D3DMATRIX ret = IdentityMatrix(); 
ret(0, 0) = a; 
ret(1, 1) = b; 
ret(2, 2) = c; 
return ret; 
} // end ScaleMatrix 
   
/* 
**----------------------------------------------------------------------------- 
**  Name:       ScaleMatrix 
**  Purpose:scale matrix 
**----------------------------------------------------------------------------- 
*/ 
 
D3DMATRIX  
d3d::ScaleMatrix(const D3DVECTOR& v) 
{ 
    D3DMATRIX ret = IdentityMatrix(); 
ret(0, 0) = v.x; 
ret(1, 1) = v.y; 
ret(2, 2) = v.z; 
return ret; 
} // end ScaleMatrix 
 
/* 
**----------------------------------------------------------------------------- 
**  Name:       MatrixMult 
**  Purpose:[C] = [A] * [B] 
**----------------------------------------------------------------------------- 
*/ 
 
D3DMATRIX 
d3d::MatrixMult(const D3DMATRIX & a, const D3DMATRIX & b) 
{ 
D3DMATRIX ret = ZeroMatrix(); 
 
for (int i=0; i<4; i++) { 
for (int j=0; j<4; j++) { 
for (int k=0; k<4; k++) { 
ret(i, j) += a(k, j) * b(i, k); 
} 
} 
} 
return ret; 
} // end MatrixMult 
 
/* 
**----------------------------------------------------------------------------- 
**  Name:       TransformVector 
**  Purpose:V' = V * [M] 
**----------------------------------------------------------------------------- 
*/ 
 
D3DVECTOR  
d3d::TransformVector(const D3DVECTOR& v, const D3DMATRIX & m) 
{ 
float hvec[4]; 
 
for (int i=0; i<4; i++) { 
hvec[i] = 0.0f; 
for (int j=0; j<4; j++) { 
if (j==3) { 
hvec[i] += m(j, i); 
} else { 
hvec[i] += v[j] * m(j, i); 
} 
} 
} 
D3DVECTOR ret(hvec[0]/hvec[3], hvec[1]/hvec[3], hvec[2]/hvec[3]); 
 
return ret; 
} // end TransformVector 
 
D3DVECTOR  
d3d::TransformVector(const D3DMATRIX & m, const D3DVECTOR& v) 
{ 
float hvec[4]; 
 
for (int i=0; i<4; i++) { 
hvec[i] = 0.0f; 
for (int j=0; j<4; j++) { 
if (j==3) { 
hvec[i] += m(j, i); 
} else { 
hvec[i] += v[j] * m(j, i); 
} 
} 
} 
D3DVECTOR ret(hvec[0]/hvec[3], hvec[1]/hvec[3], hvec[2]/hvec[3]); 
 
return ret; 
} // end TransformVector 


 /* 
**----------------------------------------------------------------------------- 
**  Name:       TransformNormal 
**  Purpose:N' = N * [M] 
**----------------------------------------------------------------------------- 
*/ 
 
D3DVECTOR 
d3d::TransformNormal(const D3DVECTOR& v, const D3DMATRIX & mat) 
{ 
D3DMATRIX m; 
 
m = MatrixInverse(mat); 
m = MatrixTranspose(m); 
return TransformVector(v, m); 
}  // end TransformNormal 
 



void d3d::RotMatToCardan(const D3DMATRIX &aMat, float &alpha_grad, float &beta_grad, float &gamma_grad)
{
	float gamma_grad2=0, alpha_grad2=0;
	alpha_grad2 = (180/pi) * atan(-aMat(0,2)/aMat(2,2));

	float M02=aMat(0,2);
	float beta_rad = -asin(aMat(0,2));
	gamma_grad2 = (180/pi) * ((acos( aMat(0,0) / cos(beta_rad))) );
	
	alpha_grad = (180/pi) * ((acos( aMat(2,2) / cos(beta_rad))) );
	alpha_grad2= (180/pi) * ((asin( aMat(1,2) / -cos(beta_rad))) );

	gamma_grad = (180/pi) * ((asin( aMat(0,1) / cos(beta_rad))) );
	gamma_grad2 = (180/pi) * atan(-aMat(0,1)/aMat(0,0));

	beta_grad = (180/pi) * beta_rad;

}



void d3d::XYZEulerToRotMat(float AlphaGrad, float BetaGrad, float GammaGrad, D3DMATRIX &aMat)
{
	float alpha = AlphaGrad/180 * pi;
	float beta = BetaGrad/180 * pi;
	float gamma = GammaGrad/180 * pi;

	aMat(0,0) =  cos(gamma) * cos(beta);
	aMat(1,0) =  -sin(gamma) * cos(beta);
	aMat(2,0) =  sin(beta);

	aMat(0,1) =  cos(alpha) * sin(gamma) + sin(alpha)*sin(beta)*cos(gamma);
	aMat(1,1) =  cos(gamma)*cos(alpha)-sin(alpha)*sin(beta)*sin(gamma);
	aMat(2,1) =  -sin(alpha)*cos(beta);

	aMat(0,2) = -cos(alpha)*sin(beta)*cos(gamma)+sin(alpha)*sin(gamma);
	aMat(1,2) =  sin(alpha)*cos(gamma)+cos(alpha)*sin(beta)*sin(gamma);
	aMat(2,2) = cos(alpha)*cos(beta);

}

void d3d::XYXEulerToRotMat(float PsiGrad, float ThetaGrad, float PhiGrad, D3DMATRIX &aMat)
{
	float psi = PsiGrad/180 * pi;
	float phi =PhiGrad/180 * pi;
	float theta = ThetaGrad/180 * pi;
	//; translation in rad
	

	//; the rotation is an adapted euler rotation in xy'x''- direction 
	//; 1: rotation around the basis x-axis by psi
	//; 2: rotation around the new y-axis by theta
	//; 3: rotation around the new x-axis by phi (=0)

	aMat(0,0) =  cos(theta);
	aMat(1,0) =  sin(theta) * sin(psi);
	aMat(2,0) =  sin(theta) * cos(psi);

	aMat(0,1) =  sin(theta) * sin(phi);
	aMat(1,1) =  cos(psi)   * cos(phi) - cos(theta) * sin(psi) * sin(phi);
	aMat(2,1) = -cos(phi)   * sin(psi) - cos(theta) * sin(phi) * cos(psi);

	aMat(0,2) = -sin(theta) * cos(phi);
	aMat(1,2) =  sin(phi)   * cos(psi) + cos(theta) * cos(phi) * sin(psi);
	aMat(2,2) = -sin(psi)   * sin(phi) + cos(theta) * cos(psi) * cos(phi);




}    
void d3d::RotMatToXYZEuler(const D3DMATRIX & aMat, float &AlphaGrad, float &BetaGrad, float &GammaGrad)
{
	float alpha=0, alpha2=0, Alpha2Grad=0, beta=0, gamma=0, gamma2=0, Gamma2Grad=0;
	beta = asin(aMat(2,0));
	BetaGrad = (180/pi) * beta;

	alpha = -asin(aMat(2,1)/cos(beta));
	AlphaGrad = (180/pi) * alpha;

	alpha2 = acos(aMat(2,2)/cos(beta));
	Alpha2Grad = (180/pi) * alpha2;

	gamma = asin(aMat(1,0)/cos(beta));
	GammaGrad = (180/pi) * -gamma;

	gamma2 = acos( aMat(0,0)/cos(beta));
	Gamma2Grad = (180/pi) * gamma2;
}




void d3d::RotMatToXYXEuler(const D3DMATRIX & aMat, float &psigrad, float &thetagrad, float &phigrad)
{
	float psi2 = 0, psi3=0, thetarad =0, psigrad1= 0, phigrad1=0, psigrad2 = 0;
	float M00 = aMat(0,0);

	thetarad = -acos(aMat(0,0));
	thetagrad = (180/pi) * thetarad;
	psigrad   = -(180/pi) * acos(aMat(2,0)/sin(thetarad));
	phigrad   = (180/pi) * asin(aMat(0,1)/sin(thetarad));

	psigrad1 = (180/pi) *  asin(aMat(1,0)/sin(thetarad));
	phigrad1 = (180/pi) * -acos(aMat(0,2)/sin(thetarad));


	if( abs((180/pi) * acos( aMat(2,2) / cos(thetarad))) < 90 )
		psigrad2 = -(180/pi) * acos( aMat(2,2) / cos(thetarad) );
	else
		psigrad2 = (180/pi) * asin( aMat(0,1) / sin(thetarad) );
	thetagrad = (180/pi) * thetarad;

	
}



/* 
**----------------------------------------------------------------------------- 
**  Name:       MatrixInverse 
**  Purpose:Creates the inverse of a 4x4 matrix 
**----------------------------------------------------------------------------- 
*/ 

 
static void lubksb(D3DMATRIX & a, int *indx, float *b); 
static void ludcmp(D3DMATRIX & a, int *indx, float *d); 
 
D3DMATRIX    
d3d::MatrixInverse(const D3DMATRIX & m) 
{ 
D3DMATRIX n, y; 
int i, j, indx[4]; 
float d, col[4]; 
 
n = m; 
ludcmp(n, indx, &d); 
 
for (j=0; j<4; j++) { 
for (i=0; i<4; i++) { 
col[i] = 0.0f; 
} 
col[j] = 1.0f; 
lubksb(n, indx, col); 
for (i=0; i<4; i++) { 
y(i, j) = col[i]; 
} 
} 
return y; 
} // end MatrixInverse 
 
/* 
**----------------------------------------------------------------------------- 
**  Name:       lubksb 
**  Purpose:backward subsitution 
**----------------------------------------------------------------------------- 
*/ 
 
static void  
lubksb(D3DMATRIX & a, int *indx, float *b) 
{ 
int i, j, ii=-1, ip; 
float sum; 
 
for (i=0; i<4; i++) { 
ip = indx[i]; 
sum = b[ip]; 
b[ip] = b[i]; 
if (ii>=0) { 
for (j=ii; j<=i-1; j++) { 
sum -= a(i, j) * b[j]; 
} 
} else if (sum != 0.0) { 
ii = i; 
} 
b[i] = sum; 
} 
for (i=3; i>=0; i--) { 
sum = b[i]; 
for (j=i+1; j<4; j++) { 
sum -= a(i, j) * b[j]; 
} 
b[i] = sum/a(i, i); 
} 
} // end lubksb 
 
/* 
**----------------------------------------------------------------------------- 
**  Name:       ludcmp 
**  Purpose:LU decomposition 
**----------------------------------------------------------------------------- 
*/ 
 
static void  
ludcmp(D3DMATRIX & a, int *indx, float *d) 
{ 
float vv[4];               /* implicit scale for each row */ 
float big, dum, sum, tmp; 
int i, imax, j, k; 
 
*d = 1.0f; 
for (i=0; i<4; i++) { 
big = 0.0f; 
for (j=0; j<4; j++) { 
if ((tmp = (float) fabs(a(i, j))) > big) { 
big = tmp; 
} 
} 
/* 
if (big == 0.0f) { 
printf("ludcmp(): singular matrix found...\n"); 
exit(1); 
} 
*/ 
vv[i] = 1.0f/big; 
} 
for (j=0; j<4; j++) { 
for (i=0; i<j; i++) { 
sum = a(i, j); 
for (k=0; k<i; k++) { 
sum -= a(i, k) * a(k, j); 
} 
a(i, j) = sum; 
} 
big = 0.0f; 
for (i=j; i<4; i++) { 
sum = a(i, j); 
for (k=0; k<j; k++) { 
sum -= a(i, k)*a(k, j); 
} 
a(i, j) = sum; 
if ((dum = vv[i] * (float)fabs(sum)) >= big) { 
big = dum; 
imax = i; 
} 
} 
if (j != imax) { 
for (k=0; k<4; k++) { 
dum = a(imax, k); 
a(imax, k) = a(j, k); 
a(j, k) = dum; 
} 
*d = -(*d); 
vv[imax] = vv[j]; 
} 
indx[j] = imax; 
if (a(j, j) == 0.0f) { 
a(j, j) = 1.0e-20f;      /* can be 0.0 also... */ 
} 
if (j != 3) { 
dum = 1.0f/a(j, j); 
for (i=j+1; i<4; i++) { 
a(i, j) *= dum; 
} 
} 
} 
} // end ludcmp 
   
/* 
**----------------------------------------------------------------------------- 
**  Name:       Matrix Transpose 
**  Purpose:[M] = [M]' 
**----------------------------------------------------------------------------- 
*/ 
 
D3DMATRIX  
d3d::MatrixTranspose(const D3DMATRIX & m) 
{ 
D3DMATRIX ret; 
int i, j; 
 
for (i=0; i<4; i++) { 
for (j=0; j<4; j++) { 
ret(i, j) = m(j, i); 
} 
} 
 
return ret; 
} // end MatrixTranspose 
 

/* 
**----------------------------------------------------------------------------- 
**  end of File 
**----------------------------------------------------------------------------- 
*/ 
 
 
 

