// DXGrabber.cpp: Implementierung der Klasse IMG_DSHOW.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IMG_DSHOW.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
	CSampleGrabberCB mCB;


IMG_DSHOW::IMG_DSHOW()
{
	//ghApp=0;
	g_dwGraphRegister=0;
	g_pVW = NULL;
	g_pMC = NULL;
	g_pME = NULL;
	g_pGraph = NULL;
	g_pCapture = NULL;
	g_psCurrent = Stopped;
	g_pGrabberF = NULL;
	pSrcFilter = NULL;
}

IMG_DSHOW::~IMG_DSHOW()
{

}


LRESULT CALLBACK WndMainProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

void IMG_DSHOW::main()
{
 	HRESULT hr = ::CoInitialize(NULL);
 
	MSG msg={0};
    // Register the window class
    WNDCLASS wc;
	HINSTANCE hInstance = AfxGetInstanceHandle();
    ZeroMemory(&wc, sizeof wc);
    wc.lpfnWndProc   = WndMainProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASSNAME;
    wc.lpszMenuName  = NULL;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VIDPREVIEW));

    if(!AfxRegisterClass(&wc))    {
        Msg(TEXT("RegisterClass Failed! Error=0x%x\r\n"), GetLastError());
        CoUninitialize(); return;    }

	ghApp = CreateWindow(CLASSNAME, APPLICATIONNAME,
                         WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_CLIPCHILDREN,
                         CW_USEDEFAULT, CW_USEDEFAULT,
                         DEFAULT_VIDEO_WIDTH, DEFAULT_VIDEO_HEIGHT,
                         0, 0, AfxGetInstanceHandle( ), 0);

   if(ghApp)

   {  

		// Create DirectShow graph and start capturing video
		hr = CaptureVideo();
		if (FAILED (hr))
		{
			CloseInterfaces();
			//DestroyWindow(ghApp);
		}
        ShowWindow(ghApp, 1);

    }
   // Release COM
    CoUninitialize();
}

HRESULT IMG_DSHOW::GetInterfaces(void)
{
    HRESULT hr;
	// Create the Sample Grabber.
	hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER,
		IID_IBaseFilter, (void**)&g_pGrabberF);
    if (FAILED(hr))
        return hr;

    // Create the filter graph
    hr = CoCreateInstance (CLSID_FilterGraph, NULL, CLSCTX_INPROC,
                           IID_IGraphBuilder, (void **) &g_pGraph);
    if (FAILED(hr))
        return hr;

    // Create the capture graph builder
    hr = CoCreateInstance (CLSID_CaptureGraphBuilder2 , NULL, CLSCTX_INPROC,
                           IID_ICaptureGraphBuilder2, (void **) &g_pCapture);
    if (FAILED(hr))
        return hr;
    
    // Create the vfw-structure
    hr = CoCreateInstance (CLSID_VfwCapture , NULL, CLSCTX_INPROC,
                           IID_IBaseFilter, (void **) &g_pVFW);
    if (FAILED(hr))
        return hr;

    // Obtain interfaces for media control and Video Window
    hr = g_pVFW->QueryInterface(IID_IAMVfwCaptureDialogs,(LPVOID *) &p_VFWDialogs);
    if (FAILED(hr))
        return hr;

    // Obtain interfaces for media control and Video Window
    hr = g_pGraph->QueryInterface(IID_IMediaControl,(LPVOID *) &g_pMC);
    if (FAILED(hr))
        return hr;

    hr = g_pGraph->QueryInterface(IID_IVideoWindow, (LPVOID *) &g_pVW);
    if (FAILED(hr))
        return hr;
	//g_pVW->put_Caption("Liveansicht");

    hr = g_pGraph->QueryInterface(IID_IMediaEvent, (LPVOID *) &g_pME);
    if (FAILED(hr))
        return hr;

    hr = g_pGrabberF->QueryInterface(IID_ISampleGrabber, (void**)&m_pGrabber);
    if (FAILED(hr))
        return hr;

   // Set the window handle used to process graph events
    //hr = g_pME->SetNotifyWindow((OAHWND)ghApp, WM_GRAPHNOTIFY, 0);

    return hr;
}

HRESULT IMG_DSHOW::CaptureVideo()
{
    HRESULT hr;

    // Get DirectShow interfaces
    hr = GetInterfaces();
    if (FAILED(hr))
    {
        Msg(TEXT("Failed to get video interfaces!  hr=0x%x"), hr);
        return hr;
    }

    // Attach the filter graph to the capture graph
    hr = g_pCapture->SetFiltergraph(g_pGraph);
    if (FAILED(hr))
    {
        Msg(TEXT("Failed to set capture filter graph!  hr=0x%x"), hr);
        return hr;
    }

    // Use the system device enumerator and class enumerator to find
    // a video capture/preview device, such as a desktop USB video camera.
    hr = FindCaptureDevice(&pSrcFilter);
    if (FAILED(hr))
    {
        // Don't display a message because FindCaptureDevice will handle it
        return hr;
    }
   
    // Add Capture filter to our graph.
    hr = g_pGraph->AddFilter(pSrcFilter, L"Video Capture");
    if (FAILED(hr))
    {
        Msg(TEXT("Couldn't add the capture filter to the graph!  hr=0x%x\r\n\r\n") 
            TEXT("If you have a working video capture device, please make sure\r\n")
            TEXT("that it is connected and is not being used by another application.\r\n\r\n")
            TEXT("The sample will now close."), hr);
        pSrcFilter->Release();
        return hr;
    }

	hr = g_pGraph->AddFilter(g_pGrabberF, L"Sample Grabber");
	if (FAILED(hr))
	{
		// Return an error.
        Msg(TEXT("Failed Add Filter Sample Grabber!  hr=0x%x"), hr);
	}


    CComPtr<IBaseFilter> pRenderer;

    // Render the preview pin on the video capture filter
    // Use this instead of g_pGraph->RenderFile
    //hr = g_pCapture->RenderStream (&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,
    //                               pSrcFilter, NULL, NULL);
	hr = g_pCapture->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,
	 pSrcFilter, g_pGrabberF, pRenderer);

    if (FAILED(hr))
    {
        Msg(TEXT("Couldn't render the video capture stream.  hr=0x%x\r\n")
            TEXT("The capture device may already be in use by another application.\r\n\r\n")
            TEXT("The sample will now close."), hr);
        pSrcFilter->Release();
        return hr;
    }

    // Now that the filter has been added to the graph and we have
    // rendered its stream, we can release this reference to the filter.
    pSrcFilter->Release();

    // Set video window style and position
    hr = SetupVideoWindow();
    if (FAILED(hr))
    {
        Msg(TEXT("Couldn't initialize video window!  hr=0x%x"), hr);
        return hr;
    }


//;-----------------------
	
    // force it to connect to video, 24 bit
    //
    CMediaType VideoType;
    VideoType.SetType( &MEDIATYPE_Video );
    VideoType.SetSubtype( &MEDIASUBTYPE_RGB24 );
    hr = m_pGrabber->SetMediaType( &VideoType ); // shouldn't fail
    if( FAILED( hr ) )
    {
        Msg( TEXT("Could not set media type"));
        return hr;
    }
    // ask for the connection media type so we know how big
    // it is, so we can write out bitmaps
    //
    AM_MEDIA_TYPE mt;
    hr = m_pGrabber->GetConnectedMediaType( &mt );
    if ( FAILED( hr) )
    {
        Msg( TEXT("Could not read the connected media type"));
        return hr;
    }
    VIDEOINFOHEADER * vih = (VIDEOINFOHEADER*) mt.pbFormat;

    //vih->bmiHeader.biWidth = 640;
    //vih->bmiHeader.biHeight = 480;
    mCB.Width  = vih->bmiHeader.biWidth;
    mCB.Height = vih->bmiHeader.biHeight;
 
//	hr = m_pGrabber->SetMediaType( &mt );
    if ( FAILED( hr) )
    {
        Msg( TEXT("Could not set the media type"));
        return hr;
    }
   
	FreeMediaType( mt );   


	IAMStreamConfig *pConfig = NULL;
	hr = g_pCapture->FindInterface(
		&PIN_CATEGORY_CAPTURE, // Preview pin.
		&MEDIATYPE_Video,    // Any media type.
		pSrcFilter, // Pointer to the capture filter.
		IID_IAMStreamConfig, (void**)&pConfig);

	int iCount = 0, iSize = 0, lowx, lowy, highx, highy;
	CSize xs(0,0), ys(0,0);
	hr = pConfig->GetNumberOfCapabilities(&iCount, &iSize);

	VIDEO_STREAM_CONFIG_CAPS scc;
	AM_MEDIA_TYPE *pmtConfig;
	// Check the size to make sure we pass in the correct structure.
	if (iSize == sizeof(VIDEO_STREAM_CONFIG_CAPS))
	{
		// Use the video capabilities structure.

		for (int iFormat = 0; iFormat < iCount; iFormat++)
		{
			hr = pConfig->GetStreamCaps(iFormat, &pmtConfig, (BYTE*)&scc);
			if (SUCCEEDED(hr))
			{
				/* Examine the format, and possibly use it. */
				//xs= scc.MinOutputSize; ys = scc.MaxOutputSize;
				lowx= scc.MinOutputSize.cx;	lowy= scc.MinOutputSize.cy;
				highx= scc.MaxOutputSize.cx; highy= scc.MaxOutputSize.cy;
				// Delete the media type when you are done.
				DeleteMediaType(pmtConfig);
			}
		}
	}
    // don't buffer the samples as they pass through
    //
    hr = m_pGrabber->SetBufferSamples( 1 );

    // only grab one at a time, stop stream after
    // grabbing one sample
    //
    hr = m_pGrabber->SetOneShot( 0 );

    // set the callback, so we can grab the one sample
    //
    hr = m_pGrabber->SetCallback( &mCB, 1 );
	if(hr!= S_OK) 
    {
        Msg(TEXT("Failed to set callback function!  hr=0x%x"), hr);
        return hr;
    }

//;-----------------------

    // Start previewing video data
    hr = g_pMC->Run();
    if (FAILED(hr))
    {
        Msg(TEXT("Couldn't run the graph!  hr=0x%x"), hr);
        return hr;
    }



   g_psCurrent = Running;
    return S_OK;
}


void IMG_DSHOW::CloseInterfaces(void)
{
    // Stop previewing data
    if (g_pMC)
        g_pMC->StopWhenReady();

    g_psCurrent = Stopped;

    // Stop receiving events
    if (g_pME)
        g_pME->SetNotifyWindow(NULL, WM_GRAPHNOTIFY, 0);

    // Relinquish ownership (IMPORTANT!) of the video window.
    // Failing to call put_Owner can lead to assert failures within
    // the video renderer, as it still assumes that it has a valid
    // parent window.
    if(g_pVW)
    {
        g_pVW->put_Visible(OAFALSE);
        g_pVW->put_Owner(NULL);
    }

    // Release DirectShow interfaces
    SAFE_RELEASE(g_pMC);
    SAFE_RELEASE(g_pME);
    SAFE_RELEASE(g_pVW);
    SAFE_RELEASE(g_pGraph);
	//g_pCapture->Release();
    SAFE_RELEASE(g_pCapture);
}


HRESULT IMG_DSHOW::SetupVideoWindow(void)
{
    HRESULT hr;

    // Set the video window to be a child of the main window
    hr = g_pVW->put_Owner((OAHWND)ghApp);
    if (FAILED(hr))
        return hr;
    
    // Set video window style
    hr = g_pVW->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN);
    if (FAILED(hr))
        return hr;

    // Use helper function to position video window in client rect 
    // of main application window
    ResizeVideoWindow();

    // Make the video window visible, now that it is properly positioned
    hr = g_pVW->put_Visible(OATRUE);
	hr = g_pVW->put_WindowState(SW_SHOW);
    if (FAILED(hr))
        return hr;

    return hr;
}


void IMG_DSHOW::ResizeVideoWindow(void)
{
    // Resize the video preview window to match owner window size
    if (g_pVW)
    {
        RECT rc;
        
        // Make the preview video fill our window
        GetClientRect(ghApp, &rc);
        //g_pVW->SetWindowPosition(0, 0, 800, 600);
        g_pVW->SetWindowPosition(0, 0, rc.right, rc.bottom);
   }
}


void IMG_DSHOW::Msg(TCHAR *szFormat, ...)
{
    TCHAR szBuffer[1024];  // Large buffer for long filenames or URLs
    const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
    const int LASTCHAR = NUMCHARS - 1;

    // Format the input string
    va_list pArgs;
    va_start(pArgs, szFormat);

    // Use a bounded buffer size to prevent buffer overruns.  Limit count to
    // character size minus one to allow for a NULL terminating character.
    _vsntprintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
    va_end(pArgs);

    // Ensure that the formatted string is NULL-terminated
    szBuffer[LASTCHAR] = TEXT('\0');

    MessageBox(NULL, szBuffer, TEXT("Fehlermeldung"), MB_OK | MB_ICONERROR);
}


HRESULT IMG_DSHOW::FindCaptureDevice(IBaseFilter ** ppSrcFilter)
{
    HRESULT hr;
    IBaseFilter * pSrc = NULL;
    CComPtr <IMoniker> pMoniker =NULL;
    ULONG cFetched;

    if (!ppSrcFilter)
        return E_POINTER;
   
    // Create the system device enumerator
    CComPtr <ICreateDevEnum> pDevEnum =NULL;

    hr = CoCreateInstance (CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC,
                           IID_ICreateDevEnum, (void **) &pDevEnum);
    if (FAILED(hr))
    {
        Msg(TEXT("Couldn't create system enumerator!  hr=0x%x"), hr);
        return hr;
    }

    // Create an enumerator for the video capture devices
    CComPtr <IEnumMoniker> pClassEnum = NULL;

    hr = pDevEnum->CreateClassEnumerator (CLSID_VideoInputDeviceCategory, &pClassEnum, 0);
    if (FAILED(hr))
    {
        Msg(TEXT("Couldn't create class enumerator!  hr=0x%x"), hr);
        return hr;
    }

    // If there are no enumerators for the requested type, then 
    // CreateClassEnumerator will succeed, but pClassEnum will be NULL.
    if (pClassEnum == NULL)
    {
        Msg(TEXT("No video capture device was detected.\r\n\r\n")
                   TEXT("This sample requires a video capture device, such as a USB WebCam,\r\n")
                   TEXT("to be installed and working properly.  The sample will now close."),
                   TEXT("No Video Capture Hardware"), MB_OK | MB_ICONINFORMATION);
        return E_FAIL;
    }

	while(S_OK == (pClassEnum->Next(1, &pMoniker, &cFetched)))
	{
		CComPtr<IPropertyBag> pBag;
		hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
		if(SUCCEEDED(hr))
		{
			VARIANT var;
			var.vt = VT_BSTR;
			hr = pBag->Read(L"FriendlyName", &var, NULL);
			if(SUCCEEDED(hr))
			{
				CString temp(var.bstrVal);
				VariantClear(&var);
				if(temp.Left(3) == "Aip")
				{
					hr = pMoniker->BindToObject(0, 0, 
						IID_IBaseFilter, (void**)&pSrc);
					if(FAILED(hr))
						return hr;
					//return S_OK;
					break;
				}          
			}
		}
		pMoniker = NULL;
	}


    // Copy the found filter pointer to the output parameter.
    // Do NOT Release() the reference, since it will still be used
    // by the calling function.
    *ppSrcFilter = pSrc;

    return hr;
}


//;--------------------------*************************************
//; Global


LRESULT CALLBACK WndMainProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int a=0;
    switch (message)
    {
        case WM_LBUTTONDOWN:
            AfxMessageBox("Linke Maustaste");
			a=3; break;

        case WM_GRAPHNOTIFY:
            //grabber->HandleGraphEvent();
            break;

        case WM_SIZE:
            //grabber->ResizeVideoWindow();
            break;

        case WM_WINDOWPOSCHANGED:
            //grabber->ChangePreviewState(! (IsIconic(hwnd)));
			a =4;
            break;

        case WM_CLOSE:            
            // Hide the main window while the graph is destroyed
            //ShowWindow(grabber->ghApp, SW_HIDE);
            //grabber->CloseInterfaces();  // Stop capturing and release interfaces
            break;

        case WM_DESTROY:
            //PostQuitMessage(0);
            return 0;

    }

    // Pass this message to the video window for notification of system changes
 //   if (grabber->g_pVW)
   //     grabber->g_pVW->NotifyOwnerMessage((LONG_PTR) hwnd, message, wParam, lParam);

    return DefWindowProc (hwnd , message, wParam, lParam);
}



void IMG_DSHOW::GrabImage()
{
	mCB.m_bGrab =1;
	Sleep(99);
	mCB.m_bGrab = 0;


}

void IMG_DSHOW::ShowFormatDlg()
{
   HRESULT hr;
 /*	g_pMC->Stop(); // Stop the graph.

	// Query the capture filter for the IAMVfwCaptureDialogs interface.
	IAMVfwCaptureDialogs *pVfw = 0;
	hr = g_pVFW->QueryInterface(IID_IAMVfwCaptureDialogs, (void**)&pVfw);

	hr = g_pCapture->FindInterface(
		&PIN_CATEGORY_CAPTURE, // Preview pin.
		&MEDIATYPE_Video,    // Any media type.
		g_pVFW, // Pointer to the capture filter.
		IID_IAMVfwCaptureDialogs, (void**)&pVfw);
		
		// Check if the device supports this dialog box.
//		if (S_OK == p_VFWDialogs->HasDialog(VfwCaptureDialog_Source))
		{
			// Show the dialog box.
			hr = pVfw->ShowDialog( VfwCaptureDialog_Display , ghApp);
			if (FAILED(hr))
			{
				Msg("Unable to show source dialog");
			}
		}
	g_pMC->Run();
*/
	   if(g_pCapture)
   {
     CComPtr<IAMStreamConfig> pSC;
     hr = g_pCapture->FindInterface(&PIN_CATEGORY_CAPTURE,
           &MEDIATYPE_Video, pSrcFilter,
           IID_IAMStreamConfig, (void **)&pSC);

     CComPtr<ISpecifyPropertyPages> pSpec;
     CAUUID cauuid;
     hr = pSC->QueryInterface(IID_ISpecifyPropertyPages,    
           (void **)&pSpec);
 
     if(SUCCEEDED(hr))
     {
        hr = pSpec->GetPages(&cauuid);
        hr = OleCreatePropertyFrame(ghApp, 30, 30, NULL, 1,
              (IUnknown **)&(pSC.p), cauuid.cElems,
              (GUID *)cauuid.pElems, 0, 0, NULL);

        CoTaskMemFree(cauuid.pElems);
     }
   }

}
