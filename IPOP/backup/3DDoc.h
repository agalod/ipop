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
	void SetProjectionRays();
	void SetSensingArea();
	void SetObjectpointlist(const vector <CPoint> &aList);
	void SetImagepointlist(vector<CPoint> *aList);
	void SetCameraStruct( D3DCAMERA cam);
	D3DCAMERA m_Camera;
	//vector<CPoint> m_Imagepointlist;
	//vector<D3DVECTOR> m_Objectpointlist;

// Attributes
public:
	GLfloat SurfaceRed[4],SurfaceGreen[4],SurfaceBlue[4],SurfaceWhite[4],
		SurfaceDarkGreen[4],SurfaceYellow[4],SurfaceCyan[4];
	//vector<D3DVECTORPAIR, D3DVECTORPAIR&> m_Distances;
	vector< D3DVECTOR >  m_Points1, m_Points2, *m_pPoints1, *m_pPoints2;
	vector< D3DVECTORPAIR > m_Lines1, m_Lines2, *m_pLines1;
	D3DVIEWPARAMS m_ViewDirection;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DDoc)
	public:
	//}}AFX_VIRTUAL
// Implementation
public:
	void UpdateData();
	void RenderScene(void);
	void SetFrontView();
	void SetBackView();
	void SetRightView();
	void SetLeftView();

	GLdouble m_angle,m_yRotate,m_xRotate;
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
