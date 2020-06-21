// MtqCamCalibDoc.cpp : Implementierung der Klasse CImageServer
//

#include "stdafx.h"
#include "ImageServer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageServer

/////////////////////////////////////////////////////////////////////////////
// CImageServer Konstruktion/Destruktion

CImageServer::CImageServer()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen
	m_pos = 0;
	m_ImageIndex=0;
	//m_CImg = new CImage();
}

CImageServer::~CImageServer()
{
	FreeCListImage(m_CListImage);
}


/////////////////////////////////////////////////////////////////////////////
// CImageServer Serialisierung

void CImageServer::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// ZU ERLEDIGEN: Hier Code zum Speichern einfügen
	}
	else
	{
		// ZU ERLEDIGEN: Hier Code zum Laden einfügen
	}
}


/////////////////////////////////////////////////////////////////////////////
// CImageServer Befehle
/////////////////////////////////////////////////////////////////////////////
// Befehle CImageServer 
int CImageServer::CList_GetIndex()
{
	POSITION position = m_CListImage.GetHeadPosition();
	for( int i = 0; i<= m_CListImage.GetCount(); i++)	{
		if(  m_pos == position ) return i;
		else
			m_CListImage.GetNext(position);	}
	return -1;
}



void CImageServer::CList_AppendImage(  CImage* image, CString ImgName)
{
	// Hilfsvariable fuer CBV_LiveDoc um zu pruefen, ob ein VecDoc/-View existiert
	m_pos = m_CListImage.AddTail( image );
	m_CListNames.Add(ImgName);
	//DIB_LoadImage();
	//m_CImg->CopyOf(*image);	
	//m_CImg.CopyOf(m_CImg);
}

void CImageServer::CList_AppendImageCopy(  CImage* image, CString ImgName)
{
	// Hilfsvariable fuer CBV_LiveDoc um zu pruefen, ob ein VecDoc/-View existiert
	CImage* newimg = new CImage; newimg->CopyOf(*image,0);
	m_pos = m_CListImage.AddTail( newimg );
	m_CListNames.Add(ImgName);
	//DIB_LoadImage();
	//m_CImg->CopyOf(*image);	
	//m_CImg.CopyOf(m_CImg);
}

void CImageServer::CList_AppendImage(lti::channel aImg, CString ImgName)
{
	lti::saveImage writer;
	writer.save("CImageServer_SaveLTIImage.bmp", aImg );
	CImage* img = new CImage();
	img->Load("CImageServer_SaveLTIImage.bmp",0);

	m_CListNames.Add(ImgName);
	m_pos = m_CListImage.AddTail( img );
	//DIB_LoadImage();
}


void CImageServer::CList_AppendImage(IplImage aImg, CString ImgName)
{

//	cvSaveImage("CImageServer_SaveIPLImage.bmp", &aImg );
	CImage* img = new CImage();
	img->CopyOf(&aImg);
//	img->Load("CImageServer_SaveIPLImage.bmp",0);

	m_CListNames.Add(ImgName);
	m_pos = m_CListImage.AddTail( img );
	//DIB_LoadImage();
}


void CImageServer::CList_BrowseBackward()
{
	POSITION hp = m_CListImage. GetHeadPosition();
	if( (m_pos == hp) || m_CListImage.IsEmpty() ) return;
	m_CListImage. GetPrev(m_pos); // dekrementiert m_pos
}

void CImageServer::CList_BrowseForward()
{
	if(m_pos == m_CListImage.GetTailPosition() || m_CListImage.IsEmpty() ) return;
	m_CListImage. GetNext(m_pos); // inkrementiert m_pos
}


int CImageServer::CList_GetCount()
{
	return m_CListImage.GetCount();
}
 
void CImageServer::CList_SaveAsBmps() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	CString numstr, Basepath, Fullpath, ext; 
 	//ImageVec* vec = CList_GetImageVec();
	static char BASED_CODE szFilter[] = "Image Files (*.bmp)|*.bmp|Image Files (*.jpg)|*.jpg||";//
	CFileDialog Dlg( 0, (LPCTSTR) &"bmp", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter );
	POSITION pos;
	if(Dlg.DoModal()==IDOK)
	{
		CString Basepath = (LPCTSTR) Dlg.GetFileName();
		if(Dlg.GetFileExt()=="bmp"){
			ext = ".bmp";
			Basepath.TrimRight(ext);
		}
		else if(Dlg.GetFileExt()=="jpg"){
			ext = ".jpg";
			Basepath.TrimRight(ext);
		}
		pos = m_CListImage.GetHeadPosition();
		for(int i=0;i<m_CListImage.GetCount();i++){
			numstr.Format("%d%s",i+1, ext); Fullpath = Basepath + numstr;
			if (! m_CListImage.GetNext(pos)->Save(Fullpath) )
				AfxMessageBox( "Das Bild konnte nicht gespeichert werden!", MB_ICONSTOP );
		}
	}
}


void CImageServer::CList_SaveCurrentImage()
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	static char BASED_CODE szFilter[] = "Image Files (*.bmp)|*.bmp|Image Files (*.jpg)|*.jpg||";//
	CFileDialog Dlg( 0, (LPCTSTR) &"bmp", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter );
	if(Dlg.DoModal()==IDOK)
	{
		if (! m_CListImage.GetAt(m_pos)->Save((LPCTSTR)Dlg.GetFileName()))
			AfxMessageBox( "Das Bild konnte nicht gespeichert werden!", MB_ICONSTOP );
	}

}


void CImageServer::CList_DeleteCurrImage()
{
	if( m_CListImage. GetCount() < 2 ) return;
	int imgidx = CList_GetIndex(); 
	m_CListImage.GetAt(m_pos)->Destroy();
	m_CListImage.RemoveAt(m_pos);
	if(imgidx>=m_CListImage.GetCount()) imgidx = m_CListImage.GetCount()-1;
	m_pos = m_CListImage.FindIndex(imgidx); 
	m_CListNames.RemoveAt(imgidx);
}


void CImageServer::FreeCListImage(CListImage &aCListImage)
{
	POSITION pos = aCListImage.GetHeadPosition();
	for(int i=0;i<aCListImage.GetCount();i++){
		aCListImage.GetNext(pos)->Destroy();
	}
	aCListImage.RemoveAll();
	
}





lti::channel CImageServer::CList_GetCurrentImageAsLTI()
{
	CList_GetCurrentImage()->Save("CImageServer_SaveIplImage.bmp");
	lti::loadImage loader; // functor to load images
	lti::channel img;        // the image loaded will be left here.

	//loader.load("myimage.png",img);  // load PNG image
	loader.load("CImageServer_SaveIplImage.bmp",img);  // load BMP image
	return img;
}

lti::channel CImageServer::CList_GetCurrentImageAsLTI(const int &relindex)
{
	POSITION relpos;
	relpos = m_CListImage.FindIndex(CList_GetIndex()+relindex);
	m_CListImage.GetAt(relpos)->Save("CImageServer_SaveIplImage.bmp");
	lti::loadImage loader; // functor to load images
	lti::channel img;        // the image loaded will be left here.

	//loader.load("myimage.png",img);  // load PNG image
	loader.load("CImageServer_SaveIplImage.bmp",img);  // load BMP image
	return img;
}

CString CImageServer::CList_GetCurrentImageName()
{
	return m_CListNames.GetAt(CList_GetIndex());
}




void CImageServer::CList_GetCurrentImage_GreyIPL()
{
	CImage* ImgDest = new CImage();
	IplImage* IplImgDest, *IplImgSrc, *greyimg2, *greyimg, *greyimg3;

	IplImgSrc = CList_GetCurrentImage()->GetImage();
	IplImgDest = cvCloneImage(IplImgSrc);
	greyimg = cvCreateImageHeader(cvSize(IplImgSrc->width,IplImgSrc->height),IPL_DEPTH_8U,1); 
	greyimg2 = cvCreateImageHeader(cvSize(IplImgSrc->width,IplImgSrc->height),IPL_DEPTH_32F,1); 
	greyimg3 = cvCloneImage(greyimg2);

	cvCreateImageData(greyimg);
	cvCreateImageData(greyimg2);
	cvCvtColor(IplImgSrc,greyimg,CV_RGB2GRAY);

	//cvGoodFeaturesToTrack(greyimg,greyimg2,);

	greyimg2 = cvCloneImage(greyimg);

}

//DEL bool CImageServer::DIB_LoadImage()
//DEL {
//DEL 	m_WindowsDIB.Load(CList_GetCurrentImageAsLTI());
//DEL 	return 1;
//DEL }

//DEL bool CImageServer::DIB_ShowImage(CDC* aDC)
//DEL {
//DEL 	if(m_WindowsDIB.IsValid()) 
//DEL 		m_WindowsDIB.Draw(aDC);
//DEL 	return 1;
//DEL }

void CImageServer::CList_GetAtImageAsLTI(const int &index)
{
/*	POSITION position = m_CListImage.GetHeadPosition();
	for( int i = 0; i<= m_CListImage.GetCount(); i++)
		if(  i == index ) 
			return 

	return -1;
*/
}

IplImage* CImageServer::CList_GetCurrentImageAsIPL()
{
	return CList_GetCurrentImage()->GetImage();
}
