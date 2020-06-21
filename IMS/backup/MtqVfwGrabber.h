// MtqVFWGrabber.h: Schnittstelle für die Klasse MtqVFWGrabber.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MTQVFWGRABBER_H__AC975A4D_0C49_4479_84CF_7F5A6815B3FB__INCLUDED_)
#define AFX_MTQVFWGRABBER_H__AC975A4D_0C49_4479_84CF_7F5A6815B3FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vfw.h>
#include "ipl.h"

enum EGrabberStatus
//; Enumeration type that specifies the frame grabber status.
{
	kGrabberError		= -1, 
	kGrabberUndefined	= 0, 
	kGrabberInitialized = 1, 
	kGrabberLiveMode	= 2 
};

enum EGrabberErrorCodes
//: Enumeration type that specifies the different error codes returned by the
//. frame grabber functions.

{
	kNoGrabberError				= 0, 
	kUnknownError				= -1, 
	kGrabberLibraryError		= -2, 
	kGrabberDriverError			= -3, 
	kGrabberBoardInitError		= -4,
	kGrabberAlreadyInitialized	= -5,
	kWindowHandleError			= -6,
	kGrabberNotInitialized		= -7,
	kVideoAlreadyOff			= -8,
	kGrabberAlreadyDisabled		= -9,
	kMemoryAllocationFailed		= -10,
	kCameraSelectionFailed		= -11,
	kGrabberCouldNotGetImage	= -12,
	kCouldNotLoadImage			= -13,
	kCouldNotWriteImage			= -14,
	kCouldNotTurnLiveModeOn		= -15,
	kCouldNotShutLiveModeDown	= -16
};

enum EGrabberType
//; Enumeration type that specifies the different frame grabbers (boards).
{
	kNoGrabber				= 0,
	kImagraphImascan		= 1,
	kImagingTechnologyITEX	= 2,
	kImagenationPXC200		= 3,
	kAVTMarlin				= 4,
	kGrabberTypeMax			= 5 
};


//; Returns the type of frame grabber given by aType as a string.

//	static CImage* iplimg;

class MtqVFWGrabber 
{
public:
	MtqVFWGrabber();
	virtual ~MtqVFWGrabber();
protected:
	CAPDRIVERCAPS m_caps;
	
	EGrabberStatus fStatus;
	//; Frame Grabber Status
	bool fUseOwnErrorMsgs;
	//: Flag for creating error windows within the framegrabber class 
	//. otherwise return error codes (OK) / throw exception (to be implemented)
   CImage* m_frame;
	CAPDRIVERCAPS CapDrvCaps;
	//	CWnd m_WndC;
	HWND m_hWndC;
	IplImage* m_IplImage;
	
public:	
	void ChooseDisplay();
	void ChooseFormat();
	CImage* GetStaticImage();
	void SaveFrameToBmp();
	void SaveFrameToBmp(char* name);
	void GrabFrame();
	void ChooseSource();
	bool fbLive;
	void OnFrame( BYTE* data, int width, int height, int format, int bpp );
	
	int m_ScreenWidth;
	int m_ScreenHeight;
	
	virtual int Init();
	//; Initialize the grabber
	virtual int Disable();
	//; Disable the grabber
	
	virtual EGrabberStatus const GetGrabberStatus() { return fStatus; }
	//; Get the grabber status
	
	virtual int StartLiveVideo( CWnd * apFrameWnd, HWND parent, CView * apView );
	
	//; Send the live image to aWnd
	virtual int StopLiveVideo( HWND aWnd );
	//; Stop the live image to aWnd
	//	virtual int SnapShot( MtqGreyImage & aImg );
	
	//virtual int SnapShot( HWND aWindowHandle, MtqGreyImage & aImg, CView * apView = 0 ); 
	//: Get one new image (SnapShot) from the grabber
	//. Target for storage is the Image "aImg" (MtqGreyImage)
	
	virtual bool const IsInitialised();	
	//; Check, if the grabber was initialized properly
	
	virtual int SelectCamera( int const aCamNr );
	//; Switch to other camera
	//void Show( HDC dc, int x, int y, int w, int h, int from_x, int from_y );
	
protected:
	int FitWindow( CView * apView ); 
	//: This protected util fct will be used for 2 reasons
	//+ a) adcGetDib() and adcGetCaptureImage() in SnapShot() will transform 
	//+    the complete Client-area of the video window to a bitmap 
	//+	   -> Fit the window before use
	//. b) shrink / blow up the window for video mode to image size
	
};

#endif // !defined(AFX_MTQVFWGRABBER_H__AC975A4D_0C49_4479_84CF_7F5A6815B3FB__INCLUDED_)
