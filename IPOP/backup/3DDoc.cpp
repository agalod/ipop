#include "stdafx.h"
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
		m_ViewDirection.up(i) = 0;
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
	m_pPoints2 = 0;	m_pLines1 = 0; 
	SetFrontView();
}

C3DDoc::~C3DDoc(){
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
	int sign = 1, i=0;
	double x=0,y=0,z=0,x1=0, y1=0, z1=0;
	//HAUPTARBEIT
	//; -----------------------------------------------
	//; BILDPUNKTE
	glPushMatrix();glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceYellow);glPointSize(1);
	glBegin(GL_POINTS);
		for( i=0; i<m_Points1.size(); i++){
			//Debug: x=m_Points1->GetAt(i)(0); y=m_Points1->GetAt(i)(1); z=m_Points1->GetAt(i)(2);
			glVertex3d( m_Points1[i](0), m_Points1[i](1), sign*m_Points1[i](2));}
	glEnd();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceGreen);glPointSize(3);
	glBegin(GL_POINTS);
		for( i=0; i<m_Points2.size(); i++){
			//Debug: x=m_Points1->GetAt(i)(0); y=m_Points1->GetAt(i)(1); z=m_Points1->GetAt(i)(2);
			glVertex3d( m_Points2[i](0), m_Points2[i](1), sign*m_Points2[i](2));}
	glEnd();
	//; -----------------------------------------------
	//; -----------------------------------------------
	//; OBJEKTPUNKTE
	glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceGreen);glPointSize(3);
	glBegin(GL_POINTS);
		//for( i=0; i<m_pPoints2->size()(); i++)
		glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceGreen);
		if(m_pPoints1)
		for( i=0; i<m_pPoints1->size(); i++)			{
			//Debug: x1=m_pPoints2->GetAt(i)(0); y1=m_pPoints2->GetAt(i)(1); z1=m_pPoints2->GetAt(i)(2);
			glVertex3d( (*m_pPoints1)[i](0), (*m_pPoints1)[i](1), 
				sign*(*m_pPoints1)[i](2) );
		}
	glEnd();
	//; -----------------------------------------------
	glBegin(GL_POINTS);
		//for( i=0; i<m_pPoints2->size()(); i++)
		glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceGreen);
		if(m_pPoints2)
		for( i=0; i<m_pPoints2->size(); i++)			{
			//Debug: x1=m_pPoints2->GetAt(i)(0); y1=m_pPoints2->GetAt(i)(1); z1=m_pPoints2->GetAt(i)(2);
			glVertex3d( (*m_pPoints2)[i](0), (*m_pPoints2)[i](1), sign*(*m_pPoints2)[i](2) );
		}
	glEnd();
/*	glBegin(GL_POINTS);
		//for( i=0; i<m_pPoints2->size()(); i++)
		glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceGreen);glPointSize(1);
			for( i=0; i<m_FlatPoints.Points.size(); i++)			{
			//Debug: x1=m_pPoints2->GetAt(i)(0); y1=m_pPoints2->GetAt(i)(1); z1=m_pPoints2->GetAt(i)(2);
			glVertex3d( m_FlatPoints.Points[i].x, m_FlatPoints.Points[i].y, 
				m_FlatPoints.zValue );
		}
	glEnd();*/
	//; Projektionsfläche
	glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceCyan);glPointSize(1);
	glBegin(GL_LINES);
		for( i=0;i<m_Lines1.size();i++){
			glVertex3d(m_Lines1[i].Pt1(0),m_Lines1[i].Pt1(1), sign*m_Lines1[i].Pt1(2));
			glVertex3d(m_Lines1[i].Pt2(0),m_Lines1[i].Pt2(1), sign*m_Lines1[i].Pt2(2));
		}
	glEnd();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceGreen);
	glBegin(GL_LINES);
		for( i=0;i<m_Lines2.size();i++){
			glVertex3d(m_Lines2[i].Pt1(0),m_Lines2[i].Pt1(1), sign*m_Lines2[i].Pt1(2));
			glVertex3d(m_Lines2[i].Pt2(0),m_Lines2[i].Pt2(1), sign*m_Lines2[i].Pt2(2));
		}
	glEnd();
	//; Projektionsstrahlen
	glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceRed);
	glBegin(GL_LINES);
		if(m_pLines1)
	for( i=0;i<m_pLines1->size();i++){
		glVertex3d((*m_pLines1)[i].Pt1(0),(*m_pLines1)[i].Pt1(1), sign*(*m_pLines1)[i].Pt1(2));
		glVertex3d((*m_pLines1)[i].Pt2(0),(*m_pLines1)[i].Pt2(1), sign*(*m_pLines1)[i].Pt2(2));
	}
	//; Koordinatensystem
	glMaterialfv(GL_FRONT, GL_DIFFUSE, SurfaceCyan);glLineWidth(3);
	glBegin(GL_LINES);
		glVertex3d(0.0,0.0,0.0);glVertex3d(3.0,0.0,0.0);
		glVertex3d(0.0,0.0,0.0);glVertex3d(0.0,3.0,0.0);
		glVertex3d(0.0,0.0, 0.0);glVertex3d(0.0,0.0, 3.0);
	glEnd();
	glFlush();glPopMatrix();
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
	m_Camera = cam; int scal = 1;
	m_Lines1.clear();
	D3DVECTORPAIR line;
	line.Pt1(2) = line.Pt2(2) =  m_Camera.FocalLength * scal;

	float halfwidth=(m_Camera.PixNumX - m_Camera.PrincipalPointX)*(m_Camera.CellSizeX/1000)*scal, 
		halfheight=line.Pt1(1)=(m_Camera.PixNumY - m_Camera.PrincipalPointY)*(m_Camera.CellSizeY/1000)*scal;

	line.Pt1(0)=-halfwidth; line.Pt1(1)=halfheight; 
	line.Pt2(0)= halfwidth; line.Pt2(1)=halfheight; 
	m_Lines1.push_back(line);

	line.Pt1(0)=-halfwidth; line.Pt1(1)=-halfheight; 
	line.Pt2(0)=halfwidth; line.Pt2(1)=-halfheight; 
	m_Lines1.push_back(line);

	line.Pt1(0)=halfwidth; line.Pt1(1)=halfheight; 
	line.Pt2(0)=halfwidth; line.Pt2(1)=-halfheight; 
	m_Lines1.push_back(line);

	line.Pt1(0)=-halfwidth; line.Pt1(1)=halfheight; 
	line.Pt2(0)=-halfwidth; line.Pt2(1)=-halfheight; 
	m_Lines1.push_back(line);
}



void C3DDoc::SetImagepointlist(vector <CPoint> *aList)
{
	//; all values in mm * 10
	//; Image Points
	m_Points1.clear(); float xval=0, yval=0; float scal = 1;
	D3DVECTOR pt; pt(2) =  m_Camera.FocalLength*scal;
	m_Lines2.clear(); float t=100;
	D3DVECTORPAIR line; line.Pt2(2) = m_Camera.FocalLength*t;
	for(int i=0;i<aList->size();i++){
		//xval=aList->GetAt(i).x; yval=aList->GetAt(i).y;
		pt(0) = ((float)(*aList)[i].x - m_Camera.PrincipalPointX) * (m_Camera.CellSizeX/1000.0)*scal;
		pt(1) = ((float)(*aList)[i].y - m_Camera.PrincipalPointY) * (m_Camera.CellSizeY/1000.0)*scal;
		m_Points1.push_back(pt);
		line.Pt2(0) = pt(0) * t;
		line.Pt2(1) = pt(1) * t;
		m_Lines2.push_back(line);
	}
	//; Projection Rays
	
/*	line.Pt2(0) = (aList.GetAt(0).x - m_Camera.PrincipalPointX) * (m_Camera.CellSizeX/1000) * t;
	line.Pt2(1) = - (aList.GetAt(0).y - m_Camera.PrincipalPointY) * (m_Camera.CellSizeY/1000) * t;
	m_Lines2.push_back(line);

	line.Pt2(0) = (aList.GetAt(size-1).x - m_Camera.PrincipalPointX) * (m_Camera.CellSizeX/1000) * t;
	line.Pt2(1) = - (aList.GetAt(size-1).y - m_Camera.PrincipalPointY) * (m_Camera.CellSizeY/1000) * t;
	m_Lines2.push_back(line);*/
}

void C3DDoc::SetObjectpointlist(const vector <CPoint> &aList)
{
	//; all values in mm * 10
	m_Points2.clear(); float xval=0, yval=0;
	D3DVECTOR pt; pt(2) = 0;
	for(int i=0;i<aList.size();i++){
		xval=aList[i].x; yval=aList[i].y;
		pt(0) = aList[i].x; pt(1) = aList[i].y;
		m_Points2.push_back(pt);
	}
}

void C3DDoc::SetSensingArea()
{
	
}

void C3DDoc::SetProjectionRays()
{
	
}
