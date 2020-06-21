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
   
// Note:  Must Define D3D_OVERLOADS to get C++ version of GCV_MATRIX3D 
#include "stdafx.h"
    
#include "gcvision.h" 
  
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
 
GCV_MATRIX3D  
gcvision::ZeroMatrix(void) 
{ 
    GCV_MATRIX3D ret; 
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
 
GCV_MATRIX3D 
gcvision::IdentityMatrix(void) 
{ 
    GCV_MATRIX3D ret; 
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
**  Name:       RotateXMatrix 
**  Purpose:Rotate matrix about X axis 
**----------------------------------------------------------------------------- 
*/ 
 
GCV_MATRIX3D 
gcvision::RotateXMatrix(const float rads) 
{ 
float cosine, sine; 
 
cosine = (float) cos(rads); 
sine = (float) sin(rads); 
    GCV_MATRIX3D ret = IdentityMatrix(); 
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
 
GCV_MATRIX3D 
gcvision::RotateYMatrix(const float rads) 
{ 
float cosine, sine; 
 
cosine = (float) cos(rads); 
sine = (float) sin(rads); 
    GCV_MATRIX3D ret = IdentityMatrix(); 
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
 
GCV_MATRIX3D 
gcvision::RotateZMatrix(const float rads) 
{ 
float cosine, sine; 
 
cosine = (float) cos(rads); 
sine = (float) sin(rads); 
    GCV_MATRIX3D ret = IdentityMatrix(); 
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
 
GCV_MATRIX3D  
gcvision::TranslateMatrix(const float dx, const float dy, const float dz) 
{ 
    GCV_MATRIX3D ret = IdentityMatrix(); 
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
 
GCV_MATRIX3D  
gcvision::TranslateMatrix(const GCV_VECTOR3D& v) 
{ 
    GCV_MATRIX3D ret = IdentityMatrix(); 
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
 
GCV_MATRIX3D  
gcvision::ScaleMatrix(const float size) 
{ 
    GCV_MATRIX3D ret = IdentityMatrix(); 
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
 
GCV_MATRIX3D  
gcvision::ScaleMatrix(const float a, const float b, const float c) 
{ 
    GCV_MATRIX3D ret = IdentityMatrix(); 
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
 
GCV_MATRIX3D  
gcvision::ScaleMatrix(const GCV_VECTOR3D& v) 
{ 
    GCV_MATRIX3D ret = IdentityMatrix(); 
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
 
GCV_MATRIX3D 
gcvision::MatrixMult(const GCV_MATRIX3D & a, const GCV_MATRIX3D & b){ 
	GCV_MATRIX3D ret = ZeroMatrix(); 
	for (int i=0; i<4; i++) for (int j=0; j<4; j++)	for (int k=0; k<4; k++)
		ret(i, j) += a(i, k) * b(k, j); 
	return ret; 
} // end MatrixMult 


GCV_MATRIX3D 
gcvision::MatrixMult(const float  a, const GCV_MATRIX3D  b) 
{ 
	GCV_MATRIX3D ret = b; 
	for (int i=0; i<4; i++)	for (int j=0; j<4; j++)	ret(i, j) *= a; 
	return ret; 
} // end MatrixMult 


GCV_MATRIX3D 
gcvision::MatrixAdd(const GCV_MATRIX3D & a, const GCV_MATRIX3D & b){ 
	GCV_MATRIX3D ret = ZeroMatrix(); ret(3,3)=1;
	for (int i=0; i<3; i++) 
		for (int j=0; j<3; j++) 
			ret(i, j) = a(i, j) + b(i, j); 
	return ret; 
} // end MatrixMult 
 
/* 
**----------------------------------------------------------------------------- 
**  Name:       TransformVector 
**  Purpose:V' = V * [M] 
**----------------------------------------------------------------------------- 
*/ 
 
GCV_VECTOR3D  
gcvision::TransformVector(const GCV_VECTOR3D& v, const GCV_MATRIX3D & m) 
{ 
	float hvec[4]; 
 
	for (int i=0; i<3; i++) { 
		hvec[i] = 0.0f; 
		for (int j=0; j<4; j++) { 
			if (j==3) hvec[i] += m(i, j); 
			else hvec[i] += v[j] * m(i, j); 
		} 
	} 
	GCV_VECTOR3D ret(hvec[0], hvec[1], hvec[2]); 
 
	return ret; 
} // end TransformVector 
 
GCV_VECTOR3D  
gcvision::TransformVector(const GCV_MATRIX3D & m, const GCV_VECTOR3D& v) 
{ 
float hvec[4]; 
 
for (int i=0; i<4; i++) { 
hvec[i] = 0.0f; 
for (int j=0; j<4; j++) { 
if (j==3) { 
hvec[i] += m(i, j); 
} else { 
hvec[i] += v[j] * m(i, j); 
} 
} 
} 
GCV_VECTOR3D ret(hvec[0]/hvec[3], hvec[1]/hvec[3], hvec[2]/hvec[3]); 
 
return ret; 
} // end TransformVector 


 /* 
**----------------------------------------------------------------------------- 
**  Name:       TransformNormal 
**  Purpose:N' = N * [M] 
**----------------------------------------------------------------------------- 
*/ 
 
GCV_VECTOR3D 
gcvision::TransformNormal(const GCV_VECTOR3D& v, const GCV_MATRIX3D & mat) 
{ 
GCV_MATRIX3D m; 
 
m = MatrixInverse(mat); 
m = MatrixTranspose(m); 
return TransformVector(v, m); 
}  // end TransformNormal 
 



void gcvision::RotMatToCardan(const GCV_MATRIX3D &aMat, float &alpha_grad, float &beta_grad, float &gamma_grad)
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



void gcvision::XYZEulerToRotMat(float AlphaGrad, float BetaGrad, float GammaGrad, GCV_MATRIX3D &aMat)
{
	float alpha = AlphaGrad/180 * pi;
	float beta = BetaGrad/180 * pi;
	float gamma = GammaGrad/180 * pi;

	aMat(0,0) =  cos(gamma) * cos(beta);
	aMat(0,1) =  -sin(gamma) * cos(beta);
	aMat(0,2) =  sin(beta);

	aMat(1,0) =  cos(alpha) * sin(gamma) + sin(alpha)*sin(beta)*cos(gamma);
	aMat(1,1) =  cos(gamma)*cos(alpha)-sin(alpha)*sin(beta)*sin(gamma);
	aMat(1,2) =  -sin(alpha)*cos(beta);

	aMat(2,0) = sin(alpha)*sin(gamma)-cos(alpha)*sin(beta)*cos(gamma);
	aMat(2,1) = sin(alpha)*cos(gamma)+cos(alpha)*sin(beta)*sin(gamma);
	aMat(2,2) = cos(alpha)*cos(beta);
}

void gcvision::XYXEulerToRotMat(float PsiGrad, float ThetaGrad, float PhiGrad, GCV_MATRIX3D &aMat)
{
	float psi = PsiGrad/180 * pi;
	float phi =PhiGrad/180 * pi;
	float theta = ThetaGrad/180 * pi;
	//; translation in rad
	

	//; the rotation is an adapted euler rotation in xy'x''- direction 
	//; 1: rotation around the basis x-axis by psi
	//; 2: rotation around the new y-axis by theta
	//; 3: rotation around the new x-axis by phi

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


//; CAUTION: THIS FUNCTION ONLY WORKS FOR ANGLES UP TO PI/2!!!
//; ( DUE TO AMBIGUITIES IN SINUS AND COSINUS )
void gcvision::RotMatToXYZEuler(const GCV_MATRIX3D & aMat, float &AlphaGrad, float &BetaGrad, float &GammaGrad)
{
	float alpha=0, alpha2=0, Alpha2Grad=0, beta=0, gamma=0, gamma2=0, Gamma2Grad=0;
	beta = asin(aMat(0,2));
	BetaGrad = (180/pi) * beta;
	
	alpha = -asin(aMat(1,2)/cos(beta));
	AlphaGrad = (180/pi) * alpha;
	
	alpha2 = acos(aMat(2,2)/cos(beta));
	Alpha2Grad = (180/pi) * alpha2;
	
	gamma = asin(aMat(0,1)/cos(beta));
	GammaGrad = (180/pi) * -gamma;
	
	gamma2 = acos( aMat(0,0)/cos(beta));
	Gamma2Grad = (180/pi) * gamma2;
}




//; CAUTION: THIS FUNCTION ONLY WORKS FOR ANGLES UP TO PI/2!!!
//; ( DUE TO AMBIGUITIES IN SINUS AND COSINUS )
void gcvision::RotMatToXYXEuler(const GCV_MATRIX3D & aMat, float &psigrad, float &thetagrad, float &phigrad)
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

/*#define FNAME "MakeFrame"
Frame* MakeFrame(int mode,float par[6],Frame *frm)
Erzeugung einer Frame-Repraesentation aus einer Euler-Repraesentation*/
/* mode = 0 : Rcz*Rby*Rax */
/* mode = 1 : Rax*Rby*Rcz */
/* mode = 2 : Raz*Rby*Rcx (Roboter manutec r2)*/
/* mode = 3 : Raz*Rby*Rcz (Roboter stäubli rx90 == yaw/pitch/roll)
 {
  float sa,ca,sb,cb,sc,cc;
  int i;
  sa=sin(par[0]); ca=cos(par[0]);
  sb=sin(par[1]); cb=cos(par[1]);
  sc=sin(par[2]); cc=cos(par[2]);
  switch(mode)
  {
  case 0:
    frm->frame[0][0]=cb*cc;
    frm->frame[0][1]=sa*sb*cc-ca*sc;
    frm->frame[0][2]=ca*sb*cc+sa*sc;
    frm->frame[1][0]=cb*sc;
    frm->frame[1][1]=sa*sb*sc+ca*cc;
    frm->frame[1][2]=ca*sb*sc-sa*cc;
    frm->frame[2][0]=-sb;
    frm->frame[2][1]=sa*cb;
    frm->frame[2][2]=ca*cb;
    break;
  case 1:
    frm->frame[0][0]=cb*cc;
    frm->frame[0][1]=-cb*sc;
    frm->frame[0][2]=sb;
    frm->frame[1][0]=ca*sc+sa*sb*cc;
    frm->frame[1][1]=ca*cc-sa*sb*sc;
    frm->frame[1][2]=-sa*cb;
    frm->frame[2][0]=sa*sc-ca*sb*cc;
    frm->frame[2][1]=sa*cc+ca*sb*sc;
    frm->frame[2][2]=ca*cb;
    break;
  case 2:
    frm->frame[0][0]=ca*cb;
    frm->frame[0][1]=ca*sb*sc-sa*cc;
    frm->frame[0][2]=ca*sb*cc+sa*sc;
    frm->frame[1][0]=sa*cb;
    frm->frame[1][1]=sa*sb*sc+ca*cc;
    frm->frame[1][2]=sa*sb*cc-ca*sc;
    frm->frame[2][0]=-sb;
    frm->frame[2][1]=cb*sc;
    frm->frame[2][2]=cb*cc;
    break;
  case 3:
    frm->frame[0][0]= ca*cb*cc-sa*sc;
    frm->frame[0][1]=-ca*cb*sc-sa*cc;
    frm->frame[0][2]= ca*sb;
    frm->frame[1][0]= sa*cb*cc+ca*sc;
    frm->frame[1][1]=-sa*cb*sc+ca*cc;
    frm->frame[1][2]= sa*sb;
    frm->frame[2][0]=-sb*cc;
    frm->frame[2][1]= sb*sc;
    frm->frame[2][2]= cb;
    break;
  default:
    Message(FNAME,M_WRONG_MODE,ERROR);
    return(NULL);
  }    
  for(i=0;i<3;i++)
  {
    frm->frame[i][3]=par[i+3];
    frm->frame[3][i]=0;
  }
  frm->frame[3][3]=1;
  return(frm);
}
#undef FNAME
*/

/*#define FNAME "MakeEuler"
int MakeEuler(int mode,Frame *f,float par1[6],float par2[6])
Umwandlung einer Frame-Repraesentation in die zug. Eulerrepraesentation*/
/*   mode = 0 : Rcz*Rby*Rax */
/*   mode = 1 : Rax*Rby*Rcz */
/*   mode = 2 : Raz*Rby*Rcx (Roboter manutec r2) */
/*{
  int i;
  float sa,ca;
  switch(mode)
  {
  case 0:
    par1[0]=atan2(f->frame[2][1],f->frame[2][2]);
    if(par1[0]>0) par2[0]=par1[0]-M_PI;
    else par2[0]=par1[0]+M_PI;
    sa=sin(par1[0]);
    if(fabs(sa)>0.5)
    {  
      par1[1]=atan2(-f->frame[2][0],f->frame[2][1]/sa);
      par2[1]=atan2(-f->frame[2][0],-f->frame[2][1]/sa);
    }
    else
    {
      ca=cos(par1[0]);
      par1[1]=atan2(-f->frame[2][0],f->frame[2][2]/ca);
      par2[1]=atan2(-f->frame[2][0],-f->frame[2][2]/ca);
    }
    par1[2]=atan2(f->frame[1][0],f->frame[0][0]);
    if(par1[2]>0) par2[2]=par1[2]-M_PI;
    else par2[2]=par1[2]+M_PI;
    break;
  case 1:
    par1[2]=atan2(-f->frame[0][1],f->frame[0][0]);
    if(par1[2]>0) par2[2]=par1[2]-M_PI;
    else par2[2]=par1[2]+M_PI;
    sa=sin(par1[2]);
    if(fabs(sa)>0.5)
    {
      par1[1]=atan2(f->frame[0][2],-f->frame[0][1]/sa);
      par2[1]=atan2(f->frame[0][2],f->frame[0][1]/sa);
    }
    else
    {
      ca=cos(par1[2]);
      par1[1]=atan2(f->frame[0][2],f->frame[0][0]/ca);
      par2[1]=atan2(f->frame[0][2],-f->frame[0][0]/ca);
    }
    par1[0]=atan2(-f->frame[1][2],f->frame[2][2]);
    if(par1[0]>0) par2[0]=par1[0]-M_PI;
    else par2[0]=par1[0]+M_PI;
    break;
  case 2:
    par1[2]=atan2(f->frame[2][1],f->frame[2][2]);
    if(par1[2]>0) par2[2]=par1[2]-M_PI;
    else par2[2]=par1[2]+M_PI;
    sa=sin(par1[2]);
    if(fabs(sa)>0.5)
    {  
      par1[1]=atan2(-f->frame[2][0],f->frame[2][1]/sa);
      par2[1]=atan2(-f->frame[2][0],-f->frame[2][1]/sa);
    }
    else
    {
      ca=cos(par1[2]);
      par1[1]=atan2(-f->frame[2][0],f->frame[2][2]/ca);
      par2[1]=atan2(-f->frame[2][0],-f->frame[2][2]/ca);
    }
    par1[0]=atan2(f->frame[1][0],f->frame[0][0]);
    if(par1[0]>0) par2[0]=par1[0]-M_PI;
    else par2[0]=par1[0]+M_PI;
    break;
  case 3:
    if(fabs(f->frame[1][2])<1e-10 && fabs(f->frame[0][2])<1e-10)
    {
      par1[1]=acos(f->frame[2][2]);
      par2[1]=par1[1];
      par1[0]=atan2(f->frame[1][0],f->frame[1][1]);
      par2[0]=par1[0];
      par1[2]=par2[2]=0;
    }
    else
    {
      par1[0]=atan2(f->frame[1][2],f->frame[0][2]);
      if(par1[0]>0) par2[0]=par1[0]-M_PI;
      else par2[0]=par1[0]+M_PI;
      sa=sin(par1[0]);
      if(fabs(sa)>0.5)
      {  
	par1[1]=atan2( f->frame[1][2]/sa,f->frame[2][2]);
	par2[1]=atan2(-f->frame[1][2]/sa,f->frame[2][2]);
      }
      else
      {
	ca=cos(par1[0]);
	par1[1]=atan2( f->frame[0][2]/ca,f->frame[2][2]);
	par2[1]=atan2(-f->frame[0][2]/ca,f->frame[2][2]);
      }
      par1[2]=atan2(f->frame[2][1],-f->frame[2][0]);
      if(par1[2]>0) par2[2]=par1[2]-M_PI;
      else par2[2]=par1[2]+M_PI;
    }
    break;
  default:
    Message(FNAME,M_WRONG_MODE,ERROR);
    return(ERROR);
  }
  for(i=0;i<3;i++)
  {
    par1[i+3]=f->frame[i][3];
    par2[i+3]=f->frame[i][3];
  }
  return(OK);
}
#undef FNAME
*/

/* 
**----------------------------------------------------------------------------- 
**  Name:       MatrixInverse 
**  Purpose:Creates the inverse of a 4x4 matrix 
**----------------------------------------------------------------------------- 
*/ 

 
static void lubksb(GCV_MATRIX3D & a, int *indx, float *b); 
static void ludcmp(GCV_MATRIX3D & a, int *indx, float *d); 
 
GCV_MATRIX3D    
gcvision::MatrixInverse(const GCV_MATRIX3D  m) 
{ 
GCV_MATRIX3D n, y; 
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
lubksb(GCV_MATRIX3D & a, int *indx, float *b) 
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
ludcmp(GCV_MATRIX3D & a, int *indx, float *d) 
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
 
GCV_MATRIX3D  
gcvision::MatrixTranspose(const GCV_MATRIX3D  m) 
{ 
GCV_MATRIX3D ret; 
int i, j; 
 
for (i=0; i<4; i++) { 
for (j=0; j<4; j++) { 
ret(i, j) = m(j, i); 
} 
} 
 
return ret; 
} // end MatrixTranspose 
 
GCV_MATRIX3D  
gcvision::HMatrixTranspose(const GCV_MATRIX3D  m) { 
	GCV_MATRIX3D msplit; GCV_VECTOR3D v;
	SplitMatrix(m, v, msplit); v *= -1;
	msplit = MatrixTranspose(msplit);
	return MergeMatrix(v, msplit);
} // end HMatrixTranspose 


GCV_MATRIXVECTOR3D 
gcvision::SplitMatrix(const GCV_MATRIX3D & m){ 
	GCV_MATRIXVECTOR3D ret; int i, j; 
	for (i=0; i<3; i++) ret.V(i)=m(i,3);
	for (i=0; i<3; i++)for (j=0; j<3; j++) ret.M(i,j)=m(i,j); 
	return ret;} 


void 
gcvision::SplitMatrix(const GCV_MATRIX3D & m, GCV_VECTOR3D &v, GCV_MATRIX3D& rm){ 
	int i, j; 
	for (i=0; i<3; i++) v(i)=m(i,3);
	for (i=0; i<3; i++)for (j=0; j<3; j++) rm(i,j)=m(i,j); } 
   

GCV_MATRIX3D 
gcvision::MergeMatrix(const GCV_VECTOR3D & v, const GCV_MATRIX3D & m) 
{	GCV_MATRIX3D ret; int i, j; 
for (i=0; i<3; i++) ret(i,3)=v[i];
for (i=0; i<3; i++)for (j=0; j<3; j++) ret(i,j)=m(i,j); 
return ret;} 

GCV_MATRIX3D 
gcvision::MergeMatrix(const GCV_MATRIXVECTOR3D & mv) 
{	GCV_MATRIX3D ret; int i, j; 
for (i=0; i<3; i++) ret(i,3)=mv.V[i];
for (i=0; i<3; i++)for (j=0; j<3; j++) ret(i,j)=mv.M(i,j); 
return ret;} 

void
gcvision::ConvertTransformationToPlane(GCV_MATRIX3D aTrafo, GCV_PLANE3D aPlane){
}

 void gcvision::AngleAndAxisFromRotMat(float &aAngleGrad, GCV_VECTOR3D &aDirection, const GCV_MATRIX3D aRotMat){
	float aAngle = acos( 0.5 * ( aRotMat(0,0) + aRotMat(1,1) + aRotMat(2,2) - 1 ) );
	aAngleGrad = aAngle * 180/pi;
	aDirection(0) = ( 1/(2*sin(aAngle)) ) * ( aRotMat(1,2) - aRotMat(2,1) );
	aDirection(1) = ( 1/(2*sin(aAngle)) ) * ( aRotMat(2,0) - aRotMat(0,2) );
	aDirection(2) = ( 1/(2*sin(aAngle)) ) * ( aRotMat(0,1) - aRotMat(1,0) );}


 float gcvision::DistanceLinePoint( GCV_VECTOR3D& aProjR, GCV_VECTOR3D& aObjP){
	float distance = Magnitude(CrossProduct(aObjP, aProjR)) / Magnitude(aProjR);
	return distance;}





void gcvision::EulerToMatrix(GCV_EULER3D eul, GCV_MATRIX3D &mat){
	GCV_MATRIX3D retmat;
	XYZEulerToRotMat(eul.rot_x, eul.rot_y, eul.rot_z, retmat);
	retmat(0,3) = eul.trans_x;
	retmat(1,3) = eul.trans_y;
	retmat(2,3) = eul.trans_z;
	mat = retmat; 
	
}


void gcvision::MatrixToEuler(GCV_MATRIX3D mat, GCV_EULER3D &eul){
	RotMatToXYZEuler(mat, eul.rot_x, eul.rot_y, eul.rot_z );
	eul.trans_x = mat(0,3);
	eul.trans_y = mat(1,3);
	eul.trans_z = mat(2,3);
}


float gcvision::VectorMult(const GCV_VECTOR3D & v1, const GCV_VECTOR3D & v2){
   	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

GCV_VECTOR3D gcvision::CalculateCrosspointProjRayPlane(GCV_VECTOR3D vec, GCV_PLANE3D aPlane){
	float scale = aPlane.OrthDistance / VectorMult(aPlane.Normal, vec);
	return (scale * vec);
}


bool gcvision::CalculateCrossPoint(const GCV_LINE2D &line1, const GCV_LINE2D &line2, GCV_POINT2D &crosspoint){
	
	//;*********************
	GCV_POINT2D d1,d2,d0;
    bool result = false;
	
	GCV_POINT2D p1 = line1.pt1, p2 = line1.pt2, p3 = line2.pt1, p4 = line2.pt2, p; 
    d1 = p2 - p1;
    d2 = p4 - p3;
	
    float det = d1.y*d2.x - d1.x*d2.y;
	
    if (det!=static_cast<float>(0)) {
		// lines are not parallel (they still can intersect...)
		
		d0 = p3 - p1;
		
		float t1 = d2.x*d0.y - d2.y*d0.x;
		float t2 = d1.x*d0.y - d1.y*d0.x;
		
		
		if (det >= 0) {
			if (((t1>=0) && (det >= t1)) &&
				((t2>=0) && (det >= t2))) {
				// compute where is the intersection point
				
				p.x = p1.x + (t1*d1.x)/det;
				p.y = p1.y + (t1*d1.y)/det;
				
				result = true;
			}
		} else {
			if (((t1<=0) && (det <= t1)) &&
				((t2<=0) && (det <= t2))) {
				
				p.x = p1.x + (t1*d1.x)/det;
				p.y = p1.y + (t1*d1.y)/det;
				
				result = true;
			}
		}
    }
	crosspoint = p;
	return result;
}

void gcvision::TransformVectorOfVector(GCV_MATRIX3D mat, std::vector< GCV_VECTOR3D > vec)
{
	for( int i=0; i<vec.size(); i++ )
		vec[i] = TransformVector(mat, vec[i]);
}


GCV_VECTOR3D gcvision::ConvertImagePtToProjectionRay(GCV_CAMERA camera, GCV_POINT2D pt){
	GCV_VECTOR3D vector;
	vector.x = ( pt.x - camera.PrincipalPointX ) * camera.CellSizeX/1000.0;
	vector.y = ( pt.y - camera.PrincipalPointY ) * camera.CellSizeY/1000.0;
	vector.z = camera.FocalLength; 
	return vector;
}


/* 
**----------------------------------------------------------------------------- 
**  end of File 
**----------------------------------------------------------------------------- 
*/ 
 
 
 

