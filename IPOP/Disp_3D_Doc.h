///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Written by cand.ing. Alexander M.Roehnisch @ WZL-RWTH, Aachen, Germany, 2005
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
#ifndef DDOC_H
#define DDOC_H
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
class CDisp_3D_Doc : public CDocument {
public:
	CDisp_3D_Doc();
	DECLARE_DYNCREATE(CDisp_3D_Doc)
	GLfloat SurfaceRed[4],SurfaceGreen[4],SurfaceBlue[4],SurfaceWhite[4],
		SurfaceDarkGreen[4],SurfaceYellow[4],SurfaceCyan[4];
	vector < vector< GCV_LINE3D	> >		        m_Vec_Lines;
	vector < vector< GCV_LINE3D > *>	        m_Vec_p_Lines;
	vector < vector< GCV_VECTOR3D > >	        m_Vec_Points;
	vector < vector< GCV_VECTOR3D > *>	        m_Vec_p_Points;
	vector < GCV_VECTOR3D		>		        m_Vec_Point;
	vector < GCV_VECTOR3D			*>		    m_Vec_p_Point;
	vector < vector< GCV_VECTOR3D		> >		m_Vec_Vectors;
	vector < vector< GCV_VECTOR3D		> *>	m_Vec_p_Vectors;
	vector < GCV_EULER3D   >					m_Vec_Frames;
	vector< GCV_LINE3D*   >						m_p_Lines;
	vector< GCV_MATRIX3D* >						m_Vec_p_Frames;
	int m_Lines_b[30], m_Lines_p_b[30], m_Points_b[30], m_Points_p_b[30],
		m_Point_b[30], m_Point_p_b[30], m_Vectors_b[30], m_Vectors_p_b[30],
		m_Frames_b[30], m_Frames_p_b[30];
	GCV_VIEWPARAMS m_ViewDirection;
	//{{AFX_VIRTUAL(CDisp_3D_Doc)
	public:
	//}}AFX_VIRTUAL
	void Draw_Lines(vector< GCV_LINE3D > &Lines);
	void Draw_Lines(vector< GCV_LINE3D > *Lines);
	void Draw_Lines(vector< GCV_LINE3D* > &Lines);
	void Draw_Points( vector< GCV_VECTOR3D > &Points);
	void Draw_Points( vector< GCV_VECTOR3D > *Points);
	void Draw_Point(  GCV_VECTOR3D  &Point);
	void Draw_Point(  GCV_VECTOR3D  *pPoint);
	void Draw_Line( GCV_LINE3D &Line);
	void Draw_Line( GCV_LINE3D *Line);
	void Draw_Vector( GCV_VECTOR3D *pVec);
	void Draw_Vector( GCV_VECTOR3D &Vec);
	void Draw_Vectors( vector < GCV_VECTOR3D > &Vecs);
	void Draw_Vectors( vector < GCV_VECTOR3D > *Vecs);
	//void Draw_Frame( D3DMATRIX *pFrame);
	void Draw_Frame( GCV_EULER3D &Frame);
	void Draw_Frame( GCV_EULER3D *Frame);
	void Draw_Frame( GCV_MATRIX3D *Frame);
	void Draw_Frames( vector < GCV_EULER3D > &Frame);
	void Draw_Frames( vector < GCV_EULER3D > *Frame);
	void UpdateData();
	void RenderScene(void);
	void SetFrontView();	void SetBackView();
	void SetRightView();	void SetLeftView();
	GLfloat m_angle;
	virtual ~CDisp_3D_Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif
protected:
	//{{AFX_MSG(CDisp_3D_Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
