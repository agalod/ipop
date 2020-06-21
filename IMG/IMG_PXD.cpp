//
// Class:	IMG_PXC (: public MtqGrabber)
//
// File:	IMG_PXC.cpp
//
// Modul:	MtqLib: IP_Grabber
//
// Purpose:	Encapsuling of the framegrabber functions
//			of the fpxc200 ImaScan fframegrabber
//
// Author:	Alex Roehnisch (glo-ar)
//			WZL - RWTH Aachen
//
// Version:	
// Status:	WORKING										
//
#include "stdafx.h"
#include "IMG_PXC.h"


IMG_PXC::IMG_PXC( int aResWidth, int aResHeight ) {
	fImageMaxX = aResWidth; fImageMaxY = aResHeight;
	fStatus = kGrabberUndefined; fFastDisplayEnabled = FALSE; }

IMG_PXC::~IMG_PXC() {
	Disable(); }

int IMG_PXC::Init() {  
	if(GetGrabberStatus()==kGrabberInitialized) return 1;
    ffgh = 0;  ffrh = 0;  BOOL small_size = 0;
  /*-------------------------------------------------------------------------
  initialize the library
  -------------------------------------------------------------------------*/
	if (!imagenation_OpenLibrary("pxc2_95.dll",&fpxc200,sizeof(fpxc200)))
	if (!imagenation_OpenLibrary("pxc2_nt.dll",&fpxc200,sizeof(fpxc200))) {
		MessageBox(0,"Couldn't find pxc200 DLL or Driver.",0,MB_ICONSTOP);
		return 0;	}
	if (!imagenation_OpenLibrary("pxcdd.dll",&fpxcdd,sizeof(fpxcdd))) {
		MessageBox( 0, "Couldn't find pxcdd DLL and DirectDraw.", 0, MB_ICONSTOP );
		imagenation_CloseLibrary(&fpxc200);
		return 0;	}
	if (!imagenation_OpenLibrary("frame_32.dll",&fframe,sizeof(fframe))) {
    MessageBox(0, "couldn't load frame_32.dll", 0, MB_OK);
    return FALSE; }
/* allocate a fframe grabber */
	ffgh=fpxc200.AllocateFG(-1);
	if (!ffgh) {
		MessageBox(0,"Couldn't allocate a frame grabber.",0,MB_ICONSTOP);
		imagenation_CloseLibrary(&fpxc200);
		imagenation_CloseLibrary(&fpxcdd);
		return 0;	}
//	fImageMaxX = 768;	fImageMaxY = 576;
//	fImageMaxX = 768;	fImageMaxY = 576;
/* allocate a fframe from fpxcdd.  Try a half sized image if a full one
	doesn't work, in case the system's low on video memory. */
//	ffrh=fpxcdd.CreateSurface(752,576);
	ffrh=fpxcdd.CreateSurface(fImageMaxX,fImageMaxY);
	int i = fpxcdd.GetError();
	if (!ffrh)		{
		small_size = TRUE;
		ffrh=fpxcdd.CreateSurface(320,243);	}
	if (!ffrh) {
		MessageBox(0,"Couldn't allocate a video fframe.",0,MB_ICONSTOP);
		fpxc200.FreeFG(ffgh);
		imagenation_CloseLibrary(&fpxc200);
		imagenation_CloseLibrary(&fpxcdd);
		return 0;	}
/* Configure the fpxc200 settings to match the size of the fframe we configured. */
	if (small_size) {
	fpxc200.SetWidth (ffgh, 320);
	fpxc200.SetHeight (ffgh, 243);
	fpxc200.SetXResolution (ffgh, 320);
	fpxc200.SetYResolution (ffgh, 243);
	}
	else /* full-size image */ {
		fpxc200.SetWidth (ffgh, fImageMaxX);
		fpxc200.SetHeight (ffgh, fImageMaxY);
		fpxc200.SetXResolution (ffgh, fImageMaxX);
		fpxc200.SetYResolution (ffgh, fImageMaxY);
	}
  /*-------------------------------------------------------------------------
  allocate a fframe buffer
  -------------------------------------------------------------------------*/
fStatus = kGrabberInitialized;
return TRUE;}


int IMG_PXC::Disable() {
	if(fStatus==kGrabberInitialized)	{
		fpxc200.GrabContinuous(ffgh,ffrh,0,0);
		fpxc200.FreeFrame(ffrh);
		fpxc200.FreeFG(ffgh);
		imagenation_CloseLibrary(&fpxcdd);
		imagenation_CloseLibrary(&fpxc200);	} return 0; }


//; SEND THE LIVE IMAGE TO AWND
int IMG_PXC::StartLiveVideo( CWnd * apfframeWnd, HWND hwnd, CView * apView) { 
	/* Set up fpxcdd display */
	int i=0; if( fFastDisplayEnabled ) {
		if ( !fpxcdd.EnableFastDisplay(hwnd,ffrh,ffgh,FALSE) ) return 0;
		fFastDisplayEnabled = FALSE; }
	//; disable display before turning it on. Error if turned on display is turned on!
	if (!fpxcdd.EnableFastDisplay(hwnd,ffrh,ffgh,TRUE)) {
		i = fpxcdd.GetError();
		MessageBox(0,"Couldn't start fpxcdd display.",0,MB_ICONSTOP);
		fpxc200.FreeFrame(ffrh);
		fpxc200.FreeFG(ffgh);
		imagenation_CloseLibrary(&fpxc200);
		imagenation_CloseLibrary(&fpxcdd);
		return 0;	}
	else fFastDisplayEnabled = TRUE;
	if( !fpxc200.GrabContinuous(ffgh,ffrh,-1,0) ) return 0;
	//; parameter 3 = 0 means on, parameter 3 = -1 means stop
	return 1; }


int IMG_PXC::StopLiveVideo( HWND hwnd ) { 
	if(GetGrabberStatus()!=kGrabberInitialized) return 0;
	if( fFastDisplayEnabled ) {
		fpxcdd.EnableFastDisplay(hwnd,ffrh,ffgh,FALSE);
		fFastDisplayEnabled = FALSE; }
	if( !fpxc200.GrabContinuous(ffgh,ffrh,0,0) ) return 0;
	//; parameter 3 = 0 means on, parameter 3 = -1 means stop
	return 1; }


int IMG_PXC::SnapShot() {
	int width = fpxc200.GetWidth(ffgh);	int height = fpxc200.GetHeight(ffgh);
	ftagQ = fpxc200.Grab(ffgh, ffrh, QUEUED);
	fpxc200.WaitFinished(ffgh, ftagQ);
	//; blacken the top line ( it is white otherwise, for some reason )
	//for( short x=0; x<width; x++ )	aImg(x, height-1)=0;
	for( short y=2; y<=height; y++ ) for( short x=0; x<width; x++ )
			//fframe.GetPixel( ffrh, &aImg(x,height-y), x, y );
	return 0; }
  

int IMG_PXC::SelectCamera( int const aCamNr ) {
	//; camera index is zero- based -> aCamNr minus one
	fpxc200.SetCamera( ffgh, aCamNr-1, 0 ); return 1; }


bool const IMG_PXC::IsInitialised(){
//; Check, if the grabber was initialized properly
	return 1; }

void IMG_PXC::SaveBmp(char* str)
{
	if( fframe.WriteBMP(ffrh, str, 1) != SUCCESS )
		AfxMessageBox("Das Bild konnte nicht gespeichert werden.");
}

int IMG_PXC::FitWindow( CView * apView ) 
{
	CWnd * pMainFrm = AfxGetMainWnd();
	WINDOWPLACEMENT WndP;
	pMainFrm->GetWindowPlacement( & WndP );
	if (WndP.showCmd != SW_SHOWMAXIMIZED )
	{
		WndP.showCmd = SW_SHOWMAXIMIZED; 
		pMainFrm->SetWindowPlacement( & WndP );
	}

	WINDOWPLACEMENT WndPl;
	CFrameWnd * pChildFrame = (CFrameWnd*) apView->GetParentFrame();
	pChildFrame->GetWindowPlacement( & WndPl );
	if( WndPl.showCmd != SW_SHOWMAXIMIZED )
	{
		apView->GetParent()->SetWindowPos( NULL, 0, 0, fpxc200.GetWidth(ffgh)+10, fpxc200.GetHeight(ffgh)+30, SWP_NOMOVE | SWP_SHOWWINDOW | SWP_NOZORDER );			
		apView->GetParentOwner()->Invalidate( FALSE );
	}

	return 0;
}