// DXGrabber2.cpp: Implementierung der Klasse CDXGrabber2.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "DXGrabber2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CDXGrabber2::CDXGrabber2()
{

}

CDXGrabber2::~CDXGrabber2()
{

}

void CDXGrabber2::main()
{
  /*  USES_CONVERSION;
    CComPtr< ISampleGrabber > pGrabber;
    CComPtr< IBaseFilter >    pSource;
    CComPtr< IGraphBuilder >  pGraph;
    CComPtr< IVideoWindow >   pVideoWindow;
    HRESULT hr;

    CString szFile = "grabbitmap.bmp";

    // Create the sample grabber
    //
    pGrabber.CoCreateInstance( CLSID_SampleGrabber );
    if( !pGrabber )
    {
        _tprintf( TEXT("Could not create CLSID_SampleGrabber\r\n") );
        return;
    }
    CComQIPtr< IBaseFilter, &IID_IBaseFilter > pGrabberBase( pGrabber );

    // Create the file reader
    //
    pSource.CoCreateInstance( CLSID_AsyncReader );
    if( !pSource )
    {
        _tprintf( TEXT("Could not create source filter\r\n") );
        return -1;
    }

    // Create the graph
    //
    pGraph.CoCreateInstance( CLSID_FilterGraph );
    if( !pGraph )
    {
        _tprintf( TEXT("Could not not create the graph\r\n") );
        return -1;
    }

    // Put them in the graph
    //
    hr = pGraph->AddFilter( pSource, L"Source" );
    hr = pGraph->AddFilter( pGrabberBase, L"Grabber" );

    // Load the source
    //
    CComQIPtr< IFileSourceFilter, &IID_IFileSourceFilter > pLoad( pSource );
    hr = pLoad->Load( T2W( szFile ), NULL );
    if( FAILED( hr ) )
    {
        _tprintf( TEXT("Could not load the media file\r\n") );
        return -1;
    }

    // Tell the grabber to grab 24-bit video. Must do this
    // before connecting it
    //
    CMediaType GrabType;
    GrabType.SetType( &MEDIATYPE_Video );
    GrabType.SetSubtype( &MEDIASUBTYPE_RGB24 );
    hr = pGrabber->SetMediaType( &GrabType );

    // Get the output pin and the input pin
    //
    CComPtr< IPin > pSourcePin;
    CComPtr< IPin > pGrabPin;

    pSourcePin = GetOutPin( pSource, 0 );
    pGrabPin   = GetInPin( pGrabberBase, 0 );

    // ... and connect them
    //
    hr = pGraph->Connect( pSourcePin, pGrabPin );
    if( FAILED( hr ) )
    {
        _tprintf( TEXT("Could not connect source filter to grabber\r\n") );
        return -1;
    }

    // This semi-COM object will receive sample callbacks for us
    //
    CSampleGrabberCB CB;

    // Ask for the connection media type so we know its size
    //
    AM_MEDIA_TYPE mt;
    hr = pGrabber->GetConnectedMediaType( &mt );

    VIDEOINFOHEADER * vih = (VIDEOINFOHEADER*) mt.pbFormat;
    CB.Width  = vih->bmiHeader.biWidth;
    CB.Height = vih->bmiHeader.biHeight;
    FreeMediaType( mt );

    // Render the grabber output pin (to a video renderer)
    //
    CComPtr <IPin> pGrabOutPin = GetOutPin( pGrabberBase, 0 );
    hr = pGraph->Render( pGrabOutPin );
    if( FAILED( hr ) )
    {
        _tprintf( TEXT("Could not render grabber output pin\r\n") );
        return -1;
    }

    // Don't buffer the samples as they pass through
    //
    hr = pGrabber->SetBufferSamples( FALSE );

    // Only grab one at a time, stop stream after
    // grabbing one sample
    //
    hr = pGrabber->SetOneShot( TRUE );

    // Set the callback, so we can grab the one sample
    //
    hr = pGrabber->SetCallback( &CB, 1 );

    // Get the seeking interface, so we can seek to a location
    //
    CComQIPtr< IMediaSeeking, &IID_IMediaSeeking > pSeeking( pGraph );

    // Query the graph for the IVideoWindow interface and use it to
    // disable AutoShow.  This will prevent the ActiveMovie window from
    // being displayed while we grab bitmaps from the running movie.
    CComQIPtr< IVideoWindow, &IID_IVideoWindow > pWindow = pGraph;
    if (pWindow)
    {
        hr = pWindow->put_AutoShow(OAFALSE);
    }

    // Find a limited number of frames
    //
    for( int i = 0 ; i < NUM_FRAMES_TO_GRAB ; i++ )
    {
        // set position
        REFERENCE_TIME Start = i * UNITS;
        hr = pSeeking->SetPositions( &Start, AM_SEEKING_AbsolutePositioning, 
                                     NULL, AM_SEEKING_NoPositioning );

        // activate the threads
        CComQIPtr< IMediaControl, &IID_IMediaControl > pControl( pGraph );
        hr = pControl->Run( );

        // wait for the graph to settle
        CComQIPtr< IMediaEvent, &IID_IMediaEvent > pEvent( pGraph );
        long EvCode = 0;

        hr = pEvent->WaitForCompletion( INFINITE, &EvCode );
        
        // callback wrote the sample
    }

    _tprintf(TEXT("Sample grabbing complete.\r\n"));
*/
}
