#include "stdafx.h"
#include "IPOPApp.h"
#include "3DDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(C3DDoc, CDocument)
  
BEGIN_MESSAGE_MAP(C3DDoc, CDocument)
	//{{AFX_MSG_MAP(C3DDoc)
		// NOTE - the ClassWizard will push_back and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
  
/////////////////////////////////////////////////////////////////////////////
// C3DDoc construction/destruction

C3DDoc::C3DDoc(){
	// TODO: push_back one-time construction code here
	for(int i=0;i<3;i++)
		m_ViewDirection.up[i] = 0;
	m_ViewDirection.up[1] = -1; 
	m_ViewDirection.center(0) = 0; m_ViewDirection.center(1) = 0;	m_ViewDirection.center(2) = -10;
	m_ViewDirection.eye(0) = 0; m_ViewDirection.eye(1) = 0; m_ViewDirection.eye(2) =  - 350;
	m_angle = 180;

	SurfaceRed[0] = 1.0f;	SurfaceRed[1] = 0.0f;
	SurfaceRed[2] = 0.0f;	SurfaceRed[3] = 1.0f;
	SurfaceDarkGreen[0] = 0.0f;	SurfaceDarkGreen[1] = 0.05f;
	SurfaceDarkGreen[2] = 0.0f;	SurfaceDarkGreen[3] = 1.0f;
	SurfaceGreen[0] = 0.0f;	SurfaceGreen[1] = 1.0f;
	SurfaceGreen[2] = 0.0f;	SurfaceGreen[3] = 1.0f;
	SurfaceBlue[0] = 0.0f;	SurfaceBlue[1] = 0.0f;
	SurfaceBlue[2] = 1.0f;	SurfaceBlue[3] = 1.0f;
	SurfaceCyan[0] = 0.0f;	SurfaceCyan[1] = 1.0f;
	SurfaceCyan[2] = 1.0f;	SurfaceCyan[3] = 1.0f;
	SurfaceYellow[0] = 1.0f;	SurfaceYellow[1] = 1.0f;
	SurfaceYellow[2] = 0.0f;	SurfaceYellow[3] = 1.0f;
	//m_pPoints2 = 0;	m_pLines1 = 0; m_pLine1 = 0;
	//m_pPoint1=0; m_pVector1 = 0;
	SetFrontView();	
	for( i=0;i<30;i++)
	 m_Lines_b[i]= m_Lines_p_b[i]=
	 m_Points_b[i]= m_Points_p_b[i]=
	 m_Point_b[i]= m_Point_p_b[i]=
	 m_Vectors_b[i]= m_Vectors_p_b[i]=
	 m_Frames_b[i]= m_Frames_p_b[i]=1;

	SetTitle("3D-Darstellung");


}

C3DDoc::~C3DDoc(){
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->m_Display_3D_pDoc=0;

}


/////////////////////////////////////////////////////////////////////////////
// C3DDoc diagnostics

#ifdef _DEBUG
void C3DDoc::AssertValid() const{CDocument::AssertValid();}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C3DDoc commands

void C3DDoc::RenderScene(void){
	//UpdateData();
	//VORARBEITEN
	//-----------
	//glclear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	m_ViewDirection.center(0) = m_ViewDirection.eye(0) + 5 * sin( m_angle * pi/180);
	m_ViewDirection.center(1) = m_ViewDirection.eye(1);
	m_ViewDirection.center(2) = m_ViewDirection.eye(2) + 5 * cos( m_angle * pi/180);
	//ConvertViewDirection( m_angles[0], m_angles[1], m_angles[2] );
	gluLookAt(m_ViewDirection.eye(0), m_ViewDirection.eye(1), m_ViewDirection.eye(2), m_ViewDirection.center(0), m_ViewDirection.center(1), 
		m_ViewDirection.center(2), m_ViewDirection.up[0], m_ViewDirection.up[1], m_ViewDirection.up[2]);
	//HAUPTARBEIT
	//; -----------------------------------------------
	
	//; BILDPUNKTE
	glPushMatrix();
	
	/*glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceYellow);glPointSize(1);
	Draw_Points(m_Points1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceGreen);glPointSize(3);
	Draw_Points(m_Points2);
	//; -----------------------------------------------
	
	//; OBJEKTPUNKTE
	glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceGreen);glPointSize(3);
	Draw_Points(m_pPoints1); Draw_Points(m_pPoints2);
	Draw_Point(m_pPoint1); 
	//; -----------------------------------------------

	//; Projektionsfläche
	glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceCyan);glLineWidth(1);
	Draw_Lines(m_Lines1); Draw_Line(m_pLine1); Draw_Vector(m_pVector1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceGreen);
	Draw_Lines(m_Lines2); 
	//; Projektionsstrahlen
	glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceRed);
	Draw_Lines(m_pLines1);

	
	//; Proj.Rays
	glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceGreen);
	Draw_Vectors(m_pProjRays);

	glLineWidth(2);	glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceRed);
	Draw_Frame(m_pFrame1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceCyan);
	Draw_Frame(m_Frame1);*/

	glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceGreen);glPointSize(3);
	glLineWidth(1);
	for( int i=0;i<m_Vec_Point.size();i++)
		if(m_Point_b[i]) Draw_Point(m_Vec_Point[i]);
	for(  i=0;i<m_Vec_p_Points.size();i++)
		if(m_Point_p_b[i]) Draw_Point((m_Vec_p_Point)[i]);

	for(  i=0;i<m_Vec_Points.size();i++)
		if(m_Points_b[i]) Draw_Points(m_Vec_Points[i]);
	for(  i=0;i<m_Vec_p_Points.size();i++)
		if(m_Points_p_b[i]) Draw_Points((m_Vec_p_Points)[i]);

	for( i=0;i<m_Vec_Lines.size();i++)
		switch(m_Lines_b[i]){
			case 0: break;
			case 1: glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceRed);
					Draw_Lines(m_Vec_Lines[i]); break;
			case 2: glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceGreen);
					Draw_Lines(m_Vec_Lines[i]); break;
			case 3: glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceYellow);
					Draw_Lines(m_Vec_Lines[i]); break;
		}
	for( i=0;i<m_Vec_p_Lines.size();i++)
		switch(m_Lines_p_b[i]){
			case 0: break;
			case 1: glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceRed);
					Draw_Lines((m_Vec_p_Lines)[i]); break;
			case 2: glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceGreen);
					Draw_Lines((m_Vec_p_Lines)[i]); break;
			case 3: glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceYellow);
					Draw_Lines((m_Vec_p_Lines)[i]); break;
		}
	glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceRed);
	Draw_Lines(m_p_Lines);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceGreen);

	for(  i=0;i<m_Vec_Vectors.size();i++)
		if(m_Vectors_b[i]) Draw_Vectors(m_Vec_Vectors[i]);
	for(  i=0;i<m_Vec_p_Vectors.size();i++)
		if(m_Vectors_p_b[i]) Draw_Vectors((m_Vec_p_Vectors)[i]);
	
	glLineWidth(3);
	for( i=0;i<m_Vec_Frames.size();i++)
		switch(m_Frames_b[i]){
			case 0: break;
			case 1: glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceRed);
					Draw_Frame(m_Vec_Frames[i]); break;
			case 2: glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceGreen);
					Draw_Frame(m_Vec_Frames[i]); break;
			case 3: glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceYellow);
					Draw_Frame(m_Vec_Frames[i]); break;
		} 
	for( i=0;i<m_Vec_p_Frames.size();i++)
		switch(m_Frames_p_b[i]){
			case 0: break;
			case 1: glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceRed);
					Draw_Frame(m_Vec_p_Frames[i]); break;
			case 2: glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceGreen);
					Draw_Frame(m_Vec_p_Frames[i]); break;
			case 3: glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceYellow);
					Draw_Frame(m_Vec_p_Frames[i]); break;
		} 
	glFlush();glPopMatrix();
	SetTitle("3D-Darstellung");

}

void C3DDoc::SetLeftView()
{
	m_ViewDirection.eye(0) = -50; m_ViewDirection.eye(1) = 0; 
	m_ViewDirection.eye(2) = 1000;
	m_angle = 90;
}

void C3DDoc::SetRightView()
{
	m_ViewDirection.eye(0) = 50; m_ViewDirection.eye(1) = 0; 
	m_ViewDirection.eye(2) =  1000;
	m_angle = -90;
}

void C3DDoc::SetBackView()
{
	m_ViewDirection.eye(0) = 0; m_ViewDirection.eye(1) = 0; 
	m_ViewDirection.eye(2) =  0;
	m_angle = 180;

}

void C3DDoc::SetFrontView()
{
	m_ViewDirection.eye(0) = 0; m_ViewDirection.eye(1) = 0; 
	m_ViewDirection.eye(2) =  600;
	m_angle = 0;
}


void C3DDoc::SetCameraStruct( D3DCAMERA cam)
{
	//if(!m_Camera) AfxMessageBox("Fehler in C3DDoc::SetCameraStruct(D3DCAMERA* m_Camera): m_Camera==0");
	//; all values in mm * 10
/*	m_Camera = cam; int scal = 1;
	vector< D3DVECTORLINE	> Lines;	
	D3DVECTORLINE line;
	line.pt1(2) = line.pt2(2) =  m_Camera->FocalLength * scal;

	double halfwidth=(m_Camera->PixNumX - m_Camera->PrincipalPointX)*(m_Camera->CellSizeX/1000)*scal, 
		halfheight=line.pt1(1)=(m_Camera->PixNumY - m_Camera->PrincipalPointY)*(m_Camera->CellSizeY/1000)*scal;

	line.pt1(0)=-halfwidth; line.pt1(1)=halfheight; 
	line.pt2(0)= halfwidth; line.pt2(1)=halfheight; 
	Lines.push_back(line);

	line.pt1(0)=-halfwidth; line.pt1(1)=-halfheight; 
	line.pt2(0)=halfwidth; line.pt2(1)=-halfheight; 
	Lines.push_back(line);

	line.pt1(0)=halfwidth; line.pt1(1)=halfheight; 
	line.pt2(0)=halfwidth; line.pt2(1)=-halfheight; 
	Lines.push_back(line);

	line.pt1(0)=-halfwidth; line.pt1(1)=halfheight; 
	line.pt2(0)=-halfwidth; line.pt2(1)=-halfheight; 
	Lines.push_back(line);
	
	m_Vec_Lines.push_back(Lines);*/
}



//DEL void C3DDoc::SetImagepointlist(vector <CPoint> *aList)
//DEL {
//DEL 	//; all values in mm * 10
//DEL 	//; Image Points
//DEL 	m_Points1.clear(); double xval=0, yval=0; double scal = 1;
//DEL 	D3DVECTOR pt; pt(2) =  m_Camera->FocalLength*scal;
//DEL 	m_Lines2.clear(); double t=100;
//DEL 	D3DVECTORLINE line; line.pt2(2) = m_Camera->FocalLength*t;
//DEL 	for(int i=0;i<aList->size();i++){
//DEL 		//xval=aList->GetAt(i).x; yval=aList->GetAt(i).y;
//DEL 		pt(0) = ((double)(*aList)[i].x - m_Camera->PrincipalPointX) * (m_Camera->CellSizeX/1000.0)*scal;
//DEL 		pt(1) = ((double)(*aList)[i].y - m_Camera->PrincipalPointY) * (m_Camera->CellSizeY/1000.0)*scal;
//DEL 		m_Points1.push_back(pt);
//DEL 		line.pt2(0) = pt(0) * t;
//DEL 		line.pt2(1) = pt(1) * t;
//DEL 		//m_Lines2.push_back(line);
//DEL 	}
//DEL 	//; Projection Rays
//DEL 	
//DEL /*	line.pt2(0) = (aList.GetAt(0).x - m_Camera->PrincipalPointX) * (m_Camera->CellSizeX/1000) * t;
//DEL 	line.pt2(1) = - (aList.GetAt(0).y - m_Camera->PrincipalPointY) * (m_Camera->CellSizeY/1000) * t;
//DEL 	m_Lines2.push_back(line);
//DEL 
//DEL 	line.pt2(0) = (aList.GetAt(size-1).x - m_Camera->PrincipalPointX) * (m_Camera->CellSizeX/1000) * t;
//DEL 	line.pt2(1) = - (aList.GetAt(size-1).y - m_Camera->PrincipalPointY) * (m_Camera->CellSizeY/1000) * t;
//DEL 	m_Lines2.push_back(line);*/
//DEL }

//DEL void C3DDoc::SetObjectpointlist(const vector <CPoint> &aList)
//DEL {
//DEL 	//; all values in mm * 10
//DEL 	m_Points2.clear(); double xval=0, yval=0;
//DEL 	D3DVECTOR pt; pt(2) = 0;
//DEL 	for(int i=0;i<aList.size();i++){
//DEL 		xval=aList[i].x; yval=aList[i].y;
//DEL 		pt(0) = aList[i].x; pt(1) = aList[i].y;
//DEL 		m_Points2.push_back(pt);
//DEL 	}
//DEL }


void C3DDoc::Draw_Points(vector< D3DVECTOR > &Points)
{
	glBegin(GL_POINTS);
		for( int i=0; i<Points.size(); i++)
			glVertex3d( Points[i](0), Points[i](1), Points[i](2) );
	glEnd();

}

void C3DDoc::Draw_Points(vector< D3DVECTOR > *pPoints)
{
	glBegin(GL_POINTS);
		if(pPoints)
		for( int i=0; i<pPoints->size(); i++)
			glVertex3d( (*pPoints)[i](0), (*pPoints)[i](1), (*pPoints)[i](2) );
	glEnd();

}

void C3DDoc::Draw_Point( D3DVECTOR &Point)
{
	glBegin(GL_POINTS);
			glVertex3d( Point(0), Point(1), Point(2) );
	glEnd();

}

void C3DDoc::Draw_Point( D3DVECTOR* pPoint)
{
	glBegin(GL_POINTS);
		if(pPoint)
			glVertex3d( (*pPoint)(0), (*pPoint)(1), (*pPoint)(2) );
	glEnd();

}

void C3DDoc::Draw_Lines(vector< D3DVECTORLINE > &Lines)
{
	glBegin(GL_LINES);
		for( int i=0;i<Lines.size();i++){
			glVertex3d(Lines[i].pt1(0),Lines[i].pt1(1), Lines[i].pt1(2));
			glVertex3d(Lines[i].pt2(0),Lines[i].pt2(1), Lines[i].pt2(2));
		}
	glEnd();

}

void C3DDoc::Draw_Lines(vector< D3DVECTORLINE* > &Lines)
{
	glBegin(GL_LINES);
		for( int i=0;i<Lines.size();i++){
			glVertex3d(Lines[i]->pt1(0),Lines[i]->pt1(1), Lines[i]->pt1(2));
			glVertex3d(Lines[i]->pt2(0),Lines[i]->pt2(1), Lines[i]->pt2(2));
		}
	glEnd();

}

void C3DDoc::Draw_Lines(vector< D3DVECTORLINE > *pLines)
{
	glBegin(GL_LINES);
		if(pLines)
		for( int i=0;i<pLines->size();i++){
			glVertex3d((*pLines)[i].pt1(0),(*pLines)[i].pt1(1), (*pLines)[i].pt1(2));
			glVertex3d((*pLines)[i].pt2(0),(*pLines)[i].pt2(1), (*pLines)[i].pt2(2));
		}
	glEnd();
}

void C3DDoc::Draw_Line( D3DVECTORLINE *pLine)
{
	glBegin(GL_LINES);
	if(pLine){
			glVertex3d(pLine->pt1(0),pLine->pt1(1), pLine->pt1(2));
			glVertex3d(pLine->pt2(0),pLine->pt2(1), pLine->pt2(2));	}
	glEnd();
}

void C3DDoc::Draw_Line( D3DVECTORLINE &Line)
{
	glBegin(GL_LINES);
			glVertex3d(Line.pt1(0),Line.pt1(1), Line.pt1(2));
			glVertex3d(Line.pt2(0),Line.pt2(1), Line.pt2(2));
	glEnd();
}

void C3DDoc::Draw_Vector( D3DVECTOR *pVec)
{
	glBegin(GL_LINES);
	if(pVec){
			glVertex3d(0,0,0);
			glVertex3d((*pVec)(0),(*pVec)(1), (*pVec)(2));	}
	glEnd();
}

void C3DDoc::Draw_Vector( D3DVECTOR &Vec)
{
	glBegin(GL_LINES);
			glVertex3d(0,0,0);
			glVertex3d(Vec(0),Vec(1), Vec(2));
	glEnd();
}



void C3DDoc::Draw_Vectors( vector < D3DVECTOR > *pVecs)
{
	glBegin(GL_LINES);
	if(pVecs)
		for( int i=0;i<pVecs->size();i++){
			glVertex3d(0,0,0);
			glVertex3d((*pVecs)[i](0),(*pVecs)[i](1), (*pVecs)[i](2));	}
	glEnd();
}

void C3DDoc::Draw_Vectors( vector < D3DVECTOR > &Vecs)
{
	glBegin(GL_LINES);
		for( int i=0;i<Vecs.size();i++){
			glVertex3d(0,0,0);
			glVertex3d(Vecs[i](0),Vecs[i](1), Vecs[i](2));	}
	glEnd();
}





/*void C3DDoc::Draw_Frame( D3DEULER &Frame)
{
	D3DVECTORLINE vecpair; int scale=23;
	D3DMATRIX temp;
	XYZEulerToRotMat(Frame.rot_x, Frame.rot_y, Frame.rot_z, temp);
	vecpair.pt1(0)=Frame.trans_x; vecpair.pt1(1)=Frame.trans_y;
	vecpair.pt1(2)=Frame.trans_z;

	for(int i=0;i<3;i++){
		vecpair.pt2(0)=(temp)(0,i)*scale; 
		vecpair.pt2(1)=(temp)(1,i)*scale; 
		vecpair.pt2(2)=(temp)(2,i)*scale; 
		vecpair.pt2 += vecpair.pt1;
		Draw_Line(vecpair);	}
}
*/

void C3DDoc::Draw_Frame( D3DEULER &Frame)
{
	D3DVECTORLINE vecpair; int scale=40;
	D3DMATRIX temp;
	XYZEulerToRotMat(Frame.rot_x, Frame.rot_y, Frame.rot_z, temp);
	vecpair.pt1(0)=Frame.trans_x; vecpair.pt1(1)=Frame.trans_y;
	vecpair.pt1(2)=Frame.trans_z;

	for(int i=0;i<3;i++){
		vecpair.pt2(0)=(temp)(0,i)*scale; 
		vecpair.pt2(1)=(temp)(1,i)*scale; 
		vecpair.pt2(2)=(temp)(2,i)*scale; 
		vecpair.pt2 += vecpair.pt1;
		Draw_Line(vecpair);	}
}

void C3DDoc::Draw_Frame( D3DEULER *Frame)
{
	D3DVECTORLINE vecpair; int scale=40;
	D3DMATRIX temp;
	XYZEulerToRotMat(Frame->rot_x, Frame->rot_y, Frame->rot_z, temp);
	vecpair.pt1(0)=Frame->trans_x; vecpair.pt1(1)=Frame->trans_y;
	vecpair.pt1(2)=Frame->trans_z;

	for(int i=0;i<3;i++){
		vecpair.pt2(0)=(temp)(0,i)*scale; 
		vecpair.pt2(1)=(temp)(1,i)*scale; 
		vecpair.pt2(2)=(temp)(2,i)*scale; 
		vecpair.pt2 += vecpair.pt1;
		Draw_Line(vecpair);	}
}

void C3DDoc::Draw_Frames( vector < D3DEULER > &Frames)
{
	for(int i=0;i<Frames.size();i++)
		Draw_Frame(Frames[i]);
}

void C3DDoc::Draw_Frames( vector < D3DEULER > *Frames)
{
	for(int i=0;i<Frames->size();i++)
		Draw_Frame((*Frames)[i]);
}
