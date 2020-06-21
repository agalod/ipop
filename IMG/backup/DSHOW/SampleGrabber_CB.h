// SampleGrabber_CB.h: Schnittstelle f�r die Klasse CSampleGrabber_CB.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMPLEGRABBER_CB_H__CB3D8BC5_B4F3_449B_9C67_331C1A810FA5__INCLUDED_)
#define AFX_SAMPLEGRABBER_CB_H__CB3D8BC5_B4F3_449B_9C67_331C1A810FA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "basetsd.h"
#include "strmif.h"
#include <dplay.h>
#include <dshow.h>
#include <atlbase.h>
//#include <atlstr.h>
#include "dshowutil.h"

#include "qedit.h"
#include <mtype.h>
#include <reftime.h>
//#include "dshowutil.cpp"


#define SAFE_RELEASE(x) { if (x) x->Release(); x = NULL; }

#define JIF(x) if (FAILED(hr=(x))) \
	{Msg(TEXT("FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n\0"), hr); return hr;}

//
// Constants
//
#define DEFAULT_VIDEO_WIDTH     640
#define DEFAULT_VIDEO_HEIGHT    480

#define APPLICATIONNAME TEXT("Live View\0")
#define CLASSNAME       TEXT("VidCapPreviewer\0")

// Application-defined message to notify app of filtergraph events
#define WM_GRAPHNOTIFY  WM_APP+1

//
// Resource constants
//
#define IDI_VIDPREVIEW          100

DEFINE_GUID(CLSID_SampleGrabber, 
0x2fa4f053, 0x6d60, 0x4cb0, 0x95, 0x3, 0x8e, 0x89, 0x23, 0x4f, 0x3f, 0x73);




// Note: this object is a SEMI-COM object, and can only be created statically.
// We use this little semi-com object to handle the sample-grab-callback,
// since the callback must provide a COM interface. We could have had an interface
// where you provided a function-call callback, but that's really messy, so we
// did it this way. You can put anything you want into this C++ object, even
// a pointer to a CDialog. Be aware of multi-thread issues though.
//
class CSampleGrabberCB : public ISampleGrabberCB 
{

public:
	CSampleGrabberCB():m_bGrab(0){};
    STDMETHODIMP_(ULONG) AddRef() { return 2; }
    // The sample grabber is calling us back on its deliver thread.
    // This is NOT the main app thread!
    //
    STDMETHODIMP BufferCB( double SampleTime, BYTE * pBuffer, long BufferSize )
    {
        //
        // Convert the buffer into a bitmap
        //
		//AfxMessageBox("In BufferCB");
		if(!m_bGrab) return 0;
        TCHAR szFilename[MAX_PATH];
        wsprintf(szFilename, TEXT("CBGrabed.bmp\0") );

        // Create a file to hold the bitmap
        HANDLE hf = CreateFile(szFilename, GENERIC_WRITE, FILE_SHARE_READ, 
                               NULL, CREATE_ALWAYS, NULL, NULL );

        if( hf == INVALID_HANDLE_VALUE )
        {
            return 0;
        }

        // Write out the file header
        //
        BITMAPFILEHEADER bfh;
        memset( &bfh, 0, sizeof( bfh ) );
        bfh.bfType = 'MB';
        bfh.bfSize = sizeof( bfh ) + BufferSize + sizeof( BITMAPINFOHEADER );
        bfh.bfOffBits = sizeof( BITMAPINFOHEADER ) + sizeof( BITMAPFILEHEADER );

        DWORD Written = 0;
        WriteFile( hf, &bfh, sizeof( bfh ), &Written, NULL );

        // Write the bitmap format
        //
        BITMAPINFOHEADER bih;
        memset( &bih, 0, sizeof( bih ) );
        bih.biSize = sizeof( bih );
        bih.biWidth = Width;
        bih.biHeight = Height;
        bih.biPlanes = 1;
        bih.biBitCount = 24;

        Written = 0;
        WriteFile( hf, &bih, sizeof( bih ), &Written, NULL );

        // Write the bitmap bits
        //
        Written = 0;
        WriteFile( hf, pBuffer, BufferSize, &Written, NULL );

        CloseHandle( hf );

        return 0;
    }

    // These will get set by the main thread below. We need to
    // know this in order to write out the bmp
    long Width;
    long Height;
	bool m_bGrab;

    // Fake out any COM ref counting
    //
    STDMETHODIMP_(ULONG) Release() { return 1; }

    // Fake out any COM QI'ing
    //
    STDMETHODIMP QueryInterface(REFIID riid, void ** ppv)
    {
        //CheckPointer(ppv,E_POINTER);
        
        if( riid == IID_ISampleGrabberCB || riid == IID_IUnknown ) 
        {
            *ppv = (void *) static_cast<ISampleGrabberCB*> ( this );
            return NOERROR;
        }    

        return E_NOINTERFACE;
    }


    // We don't implement this one
    //
    STDMETHODIMP SampleCB( double SampleTime, IMediaSample * pSample )
    {
  	AfxMessageBox("In BufferCB");
      return 0;
    }


};


#endif // !defined(AFX_SAMPLEGRABBER_CB_H__CB3D8BC5_B4F3_449B_9C67_331C1A810FA5__INCLUDED_)
