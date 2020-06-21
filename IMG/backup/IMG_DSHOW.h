// DXGrabber.h: Schnittstelle für die Klasse IMG_DSHOW.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DXGRABBER_H__4C8C2A03_6682_4F24_80C1_FFF66E9C6534__INCLUDED_)
#define AFX_DXGRABBER_H__4C8C2A03_6682_4F24_80C1_FFF66E9C6534__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IMG.h"
#include "DShow\SampleGrabber_CB.h"

class IMG_DSHOW   : public IMG {
public:
	void ShowFormatDlg();
	void GrabImage();
	typedef struct _callbackinfo 	{
		double dblSampleTime;
		long lBufferSize;
		BYTE *pBuffer;
		BITMAPINFOHEADER bih; } CALLBACKINFO;
	CALLBACKINFO cb;
	void main();
	HRESULT GetInterfaces(void);
	HRESULT CaptureVideo();
	HRESULT FindCaptureDevice(IBaseFilter ** ppSrcFilter);
	HRESULT SetupVideoWindow(void);
	void Msg(TCHAR *szFormat, ...);
	void CloseInterfaces(void);
	void ResizeVideoWindow(void);
	// Remote graph viewing functions
	enum PLAYSTATE {Stopped, Paused, Running, Init};
	//	// Macros	//
	IMG_DSHOW();
	virtual ~IMG_DSHOW();
	HWND ghApp;
    IBaseFilter *pSrcFilter;
	DWORD g_dwGraphRegister;
	IVideoWindow  * g_pVW ;
	IMediaControl * g_pMC;
	IMediaEventEx * g_pME;
	IGraphBuilder * g_pGraph;
	ICaptureGraphBuilder2 * g_pCapture;
	ISampleGrabber *m_pGrabber;
	IBaseFilter *g_pGrabberF;
	IBaseFilter *g_pVFW;
	IAMVfwCaptureDialogs* p_VFWDialogs;
	//CSampleGrabberCB mCB;
	PLAYSTATE g_psCurrent;
};

#endif // !defined(AFX_DXGRABBER_H__4C8C2A03_6682_4F24_80C1_FFF66E9C6534__INCLUDED_)
