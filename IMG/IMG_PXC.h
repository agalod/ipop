//
// Class:	IMG_PXC (: public MtqGrabber)
//
// File:	IMG_PXC.h
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

#ifndef _Mtq_PXC200_GrabberB_H_
#define _Mtq_PXC200_GrabberB_H_ 

//PXC200
#include "PXC/pxc.h"
#include "PXC/pxcdd.h"
#include "PXC/frame.h"
#include "IMG.h"

#define PXC_NAME "pxc_95.dll"
#define FRAME_NAME "frame_32.dll"
#define PXC_NT "pxc_nt.dll"

class IMG_PXC  : public IMG { 
public:
	bool SaveBmp(char* str);
	IMG_PXC( int aResWidth = 768, int aResHeight = 575 );              
 	//IMG_PXC( int aResWidth = 320, int aResHeight = 243 );              
   ~IMG_PXC();          
	//; Enumeration type that specifies the frame grabber status.
	enum EGrabberStatus	{
		kGrabberError		= -1, 
		kGrabberUndefined	= 0, 
		kGrabberInitialized = 1, 
		kGrabberLiveMode	= 2 }fStatus;
	int  fImageMaxX; int  fImageMaxY;
	long ffgh;	long ftagQ;
	FRAME __PX_FAR *ffrh;	PXC fpxc200;
	PXCDD fpxcdd;	FRAMELIB fframe;
	//: default construction, Parameter: 
    //; Resolution width and height, standard: 768x576
	 int Init();
	//; Initialize the grabber
	 int Disable();
	//; Disable the grabber
	 EGrabberStatus const GetGrabberStatus() { return fStatus; }
	//; Get the grabber status
	 int StartLiveVideo( CWnd * apFrameWnd, HWND aWnd, CView * apView = 0 );
	//; Send the live image to aWnd
	 int StopLiveVideo( HWND aWnd );
	//; Stop the live image to aWnd
	 int SnapShot(); 
	//: Get one new image (SnapShot) from the grabber
	 bool const IsInitialised();	
	//; Check, if the grabber was initialized properly
	 int SelectCamera( int const aCamNr );
	//; Switch to other camera
	//; sets the window- format to the frame- resolution

protected:
	BOOL fFastDisplayEnabled;
};                       

#endif /* _Mtq_PXC200_Grabber_H_ */