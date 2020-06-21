//
// Class:	MtqPXC200Grabber (: public MtqGrabber)
//
// File:	MtqPXC200Grabber.h
//
// Modul:	MtqLib: IP_Grabber
//
// Purpose:	Encapsuling of the Framegrabber functions
//			of the PXC200 ImaScan Framegrabber
//
// Author:	Alex Roehnisch (glo-ar)
//			WZL - RWTH Aachen
//
// To be copied into application- folder: ilib_32.lib
//
// Version:	
//			5/01/02		working, except that live video window can only be opened once	(glo-ar)
//			22/01/02	fixed some stuff
//
// Status:	WORKING										
//

#ifndef _Mtq_PXC200_Grabber_H_
#define _Mtq_PXC200_Grabber_H_ 

//MtqLib: IP_Grabber (Baseclass)
#include "MtqGrabber.h"
//PXC200
#include "pxc.h"
#include "pxcdd.h"
#include "frame.h"



#ifdef _WIN32
#define PXC_NAME "pxc_95.dll"
#define FRAME_NAME "frame_32.dll"
#define PXC_NT "pxc_nt.dll"
#else
#define PXC_NAME "pxc_31.dll"
#define FRAME_NAME "frame_16.dll"
#define PXC_NT    "pxc_31.dll"
#endif




class MtqPXC200Grabber : public MtqGrabber
{ 
protected:
	int  fImageMaxX; 
	int  fImageMaxY;

	long ffgh;
	long ftagQ;
	FRAME __PX_FAR *ffrh;

	PXC fpxc200;
	PXCDD fpxcdd;
	FRAMELIB fframe;

	EGrabberStatus fStatus;
	//; Frame Grabber Status

public:

   MtqPXC200Grabber( int aResWidth = 768, int aResHeight = 576 );              
	//: default construction, Parameter: 
    //; Resolution width and height, standard: 768x576
    virtual ~MtqPXC200Grabber();          

public:	
	virtual int Init();
	//; Initialize the grabber
	virtual int Disable();
	//; Disable the grabber
	
	virtual EGrabberStatus const GetGrabberStatus() { return fStatus; }
	//; Get the grabber status

	virtual int StartLiveVideo( CWnd * apFrameWnd, HWND aWnd, CView * apView = 0 );

	//; Send the live image to aWnd
	virtual int StopLiveVideo( HWND aWnd );
	//; Stop the live image to aWnd

	virtual int SnapShot( HWND aWindowHandle, MtqGreyImage & aImg, CView * apView = 0 ); 
	//: Get one new image (SnapShot) from the grabber
	//. Target for storage is the Image "aImg" (MtqGreyImage)

	virtual int SnapShot( MtqGreyImage & aImg ){return 0;};

	virtual bool const IsInitialised();	
	//; Check, if the grabber was initialized properly

	virtual int SelectCamera( int const aCamNr );
	//; Switch to other camera

	int FitWindow( CView * apView ); 
	//; sets the window- format to the frame- resolution


protected:
	BOOL fFastDisplayEnabled;

};                       

#endif /* _Mtq_PXC200_Grabber_H_ */