#include "stdafx.h"
#include "IPOPApp.h"
#include "Disp_3D_Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDisp_3D_Doc, CDocument)
  
BEGIN_MESSAGE_MAP(CDisp_3D_Doc, CDocument)
	//{{AFX_MSG_MAP(CDisp_3D_Doc)
		// NOTE - the ClassWizard will push_back and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
  
/////////////////////////////////////////////////////////////////////////////
// CDisp_3D_Doc construction/destruction

CDisp_3D_Doc::CDisp_3D_Doc() {
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
	SetFrontView();	
	for( i=0;i<30;i++)
	 m_Lines_b[i]= m_Lines_p_b[i]=
	 m_Points_b[i]= m_Points_p_b[i]=
	 m_Point_b[i]= m_Point_p_b[i]=
	 m_Vectors_b[i]= m_Vectors_p_b[i]=
	 m_Frames_b[i]= m_Frames_p_b[i]=1;
	SetTitle("3D-Darstellung"); }


CDisp_3D_Doc::~CDisp_3D_Doc(){
	CIPOPApp* pApp = (CIPOPApp*) AfxGetApp();
	pApp->m_Disp_3D_pDoc=0; }


/////////////////////////////////////////////////////////////////////////////
// CDisp_3D_Doc diagnostics

#ifdef _DEBUG
void CDisp_3D_Doc::AssertValid() const{CDocument::AssertValid();}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDisp_3D_Doc commands

void CDisp_3D_Doc::RenderScene(void){
	//VORARBEITEN
	//-----------
	glLoadIdentity();
	m_ViewDirection.center(0) = m_ViewDirection.eye(0) + 5 * sin( m_angle * pi/180);
	m_ViewDirection.center(1) = m_ViewDirection.eye(1);
	m_ViewDirection.center(2) = m_ViewDirection.eye(2) + 5 * cos( m_angle * pi/180);
	gluLookAt(m_ViewDirection.eye(0), m_ViewDirection.eye(1), m_ViewDirection.eye(2), m_ViewDirection.center(0), m_ViewDirection.center(1), 
	m_ViewDirection.center(2), m_ViewDirection.up[0], m_ViewDirection.up[1], m_ViewDirection.up[2]);
	//HAUPTARBEIT
	//; -----------------------------------------------
	//; BILDPUNKTE
	glPushMatrix();
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

void CDisp_3D_Doc::SetLeftView()
{
	m_ViewDirection.eye(0) = -50; m_ViewDirection.eye(1) = 0; 
	m_ViewDirection.eye(2) = 1000;
	m_angle = 90;
}

void CDisp_3D_Doc::SetRightView()
{
	m_ViewDirection.eye(0) = 50; m_ViewDirection.eye(1) = 0; 
	m_ViewDirection.eye(2) =  1000;
	m_angle = -90;
}

void CDisp_3D_Doc::SetBackView()
{
	m_ViewDirection.eye(0) = 0; m_ViewDirection.eye(1) = 0; 
	m_ViewDirection.eye(2) =  0;
	m_angle = 180;

}

void CDisp_3D_Doc::SetFrontView()
{
	m_ViewDirection.eye(0) = 0; m_ViewDirection.eye(1) = 0; 
	m_ViewDirection.eye(2) =  600;
	m_angle = 0;
}

void CDisp_3D_Doc::Draw_Points(vector< GCV_VECTOR3D > &Points) {
	glBegin(GL_POINTS);
		for( int i=0; i<Points.size(); i++)
			glVertex3d( Points[i](0), Points[i](1), Points[i](2) );
	glEnd();}
 

void CDisp_3D_Doc::Draw_Points(vector< GCV_VECTOR3D > *pPoints) {
	glBegin(GL_POINTS);
		if(pPoints)	for( int i=0; i<pPoints->size(); i++)
			glVertex3d( (*pPoints)[i](0), (*pPoints)[i](1), (*pPoints)[i](2) );
	glEnd(); }


void CDisp_3D_Doc::Draw_Point( GCV_VECTOR3D &Point) {
	glBegin(GL_POINTS);	glVertex3d( Point(0), Point(1), Point(2) );
	glEnd(); }


void CDisp_3D_Doc::Draw_Point( GCV_VECTOR3D* pPoint){
	glBegin(GL_POINTS);
	if(pPoint) glVertex3d( (*pPoint)(0), (*pPoint)(1), (*pPoint)(2) );
	glEnd(); }


void CDisp_3D_Doc::Draw_Lines(vector< GCV_LINE3D > &Lines){
	glBegin(GL_LINES);
		for( int i=0;i<Lines.size();i++){
			glVertex3d(Lines[i].pt1(0),Lines[i].pt1(1), Lines[i].pt1(2));
			glVertex3d(Lines[i].pt2(0),Lines[i].pt2(1), Lines[i].pt2(2));
	} glEnd(); }


void CDisp_3D_Doc::Draw_Lines(vector< GCV_LINE3D* > &Lines){
	glBegin(GL_LINES);
		for( int i=0;i<Lines.size();i++){
			glVertex3d(Lines[i]->pt1(0),Lines[i]->pt1(1), Lines[i]->pt1(2));
			glVertex3d(Lines[i]->pt2(0),Lines[i]->pt2(1), Lines[i]->pt2(2));
		}	glEnd(); }


void CDisp_3D_Doc::Draw_Lines(vector< GCV_LINE3D > *pLines) {
	glBegin(GL_LINES);
		if(pLines)
		for( int i=0;i<pLines->size();i++){
			glVertex3d((*pLines)[i].pt1(0),(*pLines)[i].pt1(1), (*pLines)[i].pt1(2));
			glVertex3d((*pLines)[i].pt2(0),(*pLines)[i].pt2(1), (*pLines)[i].pt2(2));
	} glEnd(); }


void CDisp_3D_Doc::Draw_Line( GCV_LINE3D *pLine){
	glBegin(GL_LINES);
	if(pLine){
			glVertex3d(pLine->pt1(0),pLine->pt1(1), pLine->pt1(2));
			glVertex3d(pLine->pt2(0),pLine->pt2(1), pLine->pt2(2));	}
	glEnd(); }


void CDisp_3D_Doc::Draw_Line( GCV_LINE3D &Line){
	glBegin(GL_LINES);
			glVertex3d(Line.pt1(0),Line.pt1(1), Line.pt1(2));
			glVertex3d(Line.pt2(0),Line.pt2(1), Line.pt2(2));
	glEnd(); }


void CDisp_3D_Doc::Draw_Vector( GCV_VECTOR3D *pVec){
	glBegin(GL_LINES);
	if(pVec){
		glVertex3d(0,0,0);glVertex3d((*pVec)(0),(*pVec)(1), (*pVec)(2));}
	glEnd(); }


void CDisp_3D_Doc::Draw_Vector( GCV_VECTOR3D &Vec)
{
	glBegin(GL_LINES);
			glVertex3d(0,0,0);
			glVertex3d(Vec(0),Vec(1), Vec(2));
	glEnd();}


void CDisp_3D_Doc::Draw_Vectors( vector < GCV_VECTOR3D > *pVecs){
	glBegin(GL_LINES);
	if(pVecs)
		for( int i=0;i<pVecs->size();i++){
			glVertex3d(0,0,0);
			glVertex3d((*pVecs)[i](0),(*pVecs)[i](1), (*pVecs)[i](2));	}
	glEnd();}


void CDisp_3D_Doc::Draw_Vectors( vector < GCV_VECTOR3D > &Vecs){
	glBegin(GL_LINES);
		for( int i=0;i<Vecs.size();i++){
			glVertex3d(0,0,0);
			glVertex3d(Vecs[i](0),Vecs[i](1), Vecs[i](2));	}
	glEnd();}


void CDisp_3D_Doc::Draw_Frame( GCV_EULER3D &Frame){
	GCV_LINE3D vecpair; int scale=40;
	GCV_MATRIX3D temp;
	XYZEulerToRotMat(Frame.rot_x, Frame.rot_y, Frame.rot_z, temp);
	vecpair.pt1(0)=Frame.trans_x; vecpair.pt1(1)=Frame.trans_y;
	vecpair.pt1(2)=Frame.trans_z;
	//; Nullpunkt des Frames

	//; Die Spalten sind die Einheitsrichtungsvektoren
	for(int i=0;i<3;i++){
		vecpair.pt2(0)=(temp)(0,i)*scale; 
		vecpair.pt2(1)=(temp)(1,i)*scale; 
		vecpair.pt2(2)=(temp)(2,i)*scale; 
		vecpair.pt2 += vecpair.pt1;
		Draw_Line(vecpair);	}}

void CDisp_3D_Doc::Draw_Frame( GCV_EULER3D *Frame){
	GCV_LINE3D vecpair; int scale=40;
	GCV_MATRIX3D temp;
	XYZEulerToRotMat(Frame->rot_x, Frame->rot_y, Frame->rot_z, temp);
	vecpair.pt1(0)=Frame->trans_x; vecpair.pt1(1)=Frame->trans_y;
	vecpair.pt1(2)=Frame->trans_z;

	for(int i=0;i<3;i++){
		vecpair.pt2(0)=(temp)(0,i)*scale; 
		vecpair.pt2(1)=(temp)(1,i)*scale; 
		vecpair.pt2(2)=(temp)(2,i)*scale; 
		vecpair.pt2 += vecpair.pt1;
		Draw_Line(vecpair);	}}


void CDisp_3D_Doc::Draw_Frame( GCV_MATRIX3D *Frame){
	GCV_LINE3D vecpair; int scale=40;
	GCV_MATRIX3D temp = *Frame;
	vecpair.pt1(0)=temp(0,3); vecpair.pt1(1)=temp(1,3);
	vecpair.pt1(2)=temp(2,3);
	for(int i=0;i<3;i++){
		vecpair.pt2(0)=(temp)(0,i)*scale; 
		vecpair.pt2(1)=(temp)(1,i)*scale; 
		vecpair.pt2(2)=(temp)(2,i)*scale; 
		vecpair.pt2 += vecpair.pt1;
		Draw_Line(vecpair);	}}


void CDisp_3D_Doc::Draw_Frames( vector < GCV_EULER3D > &Frames){
	for(int i=0;i<Frames.size();i++)
		Draw_Frame(Frames[i]);}


void CDisp_3D_Doc::Draw_Frames( vector < GCV_EULER3D > *Frames){
	for(int i=0;i<Frames->size();i++)
		Draw_Frame((*Frames)[i]);}