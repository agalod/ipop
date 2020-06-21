#ifndef DDOC_H
#define DDOC_H

//#include "RungeZipperer.h"	// Hinzugefügt von der Klassenansicht
#define checkImageWidth 64
#define checkImageHeight 64

class C3DDoc : public CDocument
{
protected: // create from serialization only
	C3DDoc();
	DECLARE_DYNCREATE(C3DDoc)
	void SetCameraStruct( D3DCAMERA cam);
	D3DCAMERA* m_Camera;
	//D3DEULER* m_pEuler;
	//vector<CPoint> m_Imagepointlist;
	//vector<D3DVECTOR> m_Objectpointlist;

// Attributes
public:
	GLfloat SurfaceRed[4],SurfaceGreen[4],SurfaceBlue[4],SurfaceWhite[4],
		SurfaceDarkGreen[4],SurfaceYellow[4],SurfaceCyan[4];
	//vector<D3DVECTORLINE, D3DVECTORLINE&> m_Distances;

	vector < vector< D3DVECTORLINE	> > m_Vec_Lines;
	vector < vector< D3DVECTORLINE > *>  m_Vec_p_Lines;
	vector < vector< D3DVECTOR		> > m_Vec_Points;
	vector < vector< D3DVECTOR		> *> m_Vec_p_Points;
	vector < D3DVECTOR				>	m_Vec_Point;
	vector < D3DVECTOR				*>	m_Vec_p_Point;
	vector < vector< D3DVECTOR		> > m_Vec_Vectors;
	vector < vector< D3DVECTOR		> *> m_Vec_p_Vectors;
	vector < D3DEULER  > m_Vec_Frames;
	vector < D3DEULER *> m_Vec_p_Frames;

	vector< D3DVECTORLINE* > m_p_Lines;

	int m_Lines_b[30], m_Lines_p_b[30];
	int m_Points_b[30], m_Points_p_b[30];
	int m_Point_b[30], m_Point_p_b[30];
	int m_Vectors_b[30], m_Vectors_p_b[30];
	int m_Frames_b[30], m_Frames_p_b[30];

	/*
	D3DMATRIX *m_pFrame1, *m_pFrame2, *m_pFrame3;
	D3DMATRIX m_Frame1, m_Frame2, m_Frame3;
	vector< D3DVECTOR >  m_Points1, m_Points2, *m_pPoints1, *m_pPoints2,
		*m_pProjRays;	D3DVECTOR* m_pPoint1;
	vector< D3DVECTORLINE > m_Lines1, m_Lines2, *m_pLines1, *m_pLines2;
	D3DVECTORLINE *m_pLine1;D3DVECTOR *m_pVector1;*/

	D3DVIEWPARAMS m_ViewDirection;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DDoc)
	public:
	//}}AFX_VIRTUAL
// Implementation
public:
	void Draw_Lines(vector< D3DVECTORLINE > &Lines);
	void Draw_Lines(vector< D3DVECTORLINE > *Lines);
	void Draw_Lines(vector< D3DVECTORLINE* > &Lines);
	void Draw_Points( vector< D3DVECTOR > &Points);
	void Draw_Points( vector< D3DVECTOR > *Points);
	void Draw_Point(  D3DVECTOR  &Point);
	void Draw_Point(  D3DVECTOR  *pPoint);
	void Draw_Line( D3DVECTORLINE &Line);
	void Draw_Line( D3DVECTORLINE *Line);
	void Draw_Vector( D3DVECTOR *pVec);
	void Draw_Vector( D3DVECTOR &Vec);
	void Draw_Vectors( vector < D3DVECTOR > &Vecs);
	void Draw_Vectors( vector < D3DVECTOR > *Vecs);
	//void Draw_Frame( D3DMATRIX *pFrame);
	void Draw_Frame( D3DEULER &Frame);
	void Draw_Frame( D3DEULER *Frame);
	void Draw_Frames( vector < D3DEULER > &Frame);
	void Draw_Frames( vector < D3DEULER > *Frame);



	void UpdateData();
	void RenderScene(void);
	void SetFrontView();
	void SetBackView();
	void SetRightView();
	void SetLeftView();

	GLfloat m_angle,m_yRotate,m_xRotate;
	virtual ~C3DDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(C3DDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
/////////////////////////////////////////////////////////////////////////////
