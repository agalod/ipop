// IMG_VFW.cpp: Implementierung der Klasse IMG_VFW.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IMG_VFW.h"
//#include "ipl.h"
#include <assert.h>
//#include "MtqImageIO.h"

//#include "Bitmap.h"

/* conversion YUV->RGB */
#define TWIST_BITS 12
#define TAP(x) ((int)((x)*(1<<TWIST_BITS) + 0.5 ))

static const int YUV2RGB[] = 
{
	TAP(1.1644), TAP(1.596), TAP(    0), -TAP(222.9184),
		TAP(1.1644),-TAP(0.815),-TAP( 0.39),  TAP(135.6096),
		TAP(1.1644), TAP(0),     TAP(2.016), -TAP(276.6784)
};

#define PROCESS_UV( uv_ofs, r0, g0, b0 )                                       \
	b0 = U[uv_ofs]*YUV2RGB[1+4*0] +           /* 0 + */        YUV2RGB[3+4*0]; \
	g0 = U[uv_ofs]*YUV2RGB[1+4*1] + V[uv_ofs]*YUV2RGB[2+4*1] + YUV2RGB[3+4*1]; \
r0 =      /*  0 + */            V[uv_ofs]*YUV2RGB[2+4*2] + YUV2RGB[3+4*2];

#define PROCESS_Y( y_ofs, r, g, b, r0, g0, b0 ) \
	r = Y[y_ofs]*YUV2RGB[0+4*0];                \
	b = (r + b0) >> TWIST_BITS;                 \
	g = (r + g0) >> TWIST_BITS;                 \
r = (r + r0) >> TWIST_BITS;

#define SATURATE(x) (BYTE)(!((x)&~255)?(x):~((x)>>31))

#define SAVE_RGB(ofs,r,g,b)     \
	BGR[(ofs)]   = SATURATE(b); \
	BGR[(ofs)+1] = SATURATE(g); \
BGR[(ofs)+2] = SATURATE(r);


static void ConvertYUV420_TO_BGR( int width, int height,
											BYTE* Y, BYTE* U, BYTE* V,
											BYTE* BGR, int bgrStep )
{
	int  i, j;
	assert( ((width|height)&7) == 0 );
	
	int delta = bgrStep - width*3;
	width /= 2;
	
	for( i = 0; i < height; i += 2, Y += 4*width,
		U += width, V += width,
		BGR += delta + bgrStep )
	{
		for( j = 0; j < width; j++, BGR += 6 )
		{
			int r0, g0, b0, r, g, b;
			
			PROCESS_UV( j, r0, g0, b0 );
			
			PROCESS_Y( j*2, r, g, b, r0, g0, b0 );
			SAVE_RGB( 0, r, g, b );
			
			PROCESS_Y( j*2 + 1, r, g, b, r0, g0, b0 );
			SAVE_RGB( 3, r, g, b );
			
			PROCESS_Y( j*2 + width*2, r, g, b, r0, g0, b0 );
			SAVE_RGB( bgrStep, r, g, b );
			
			PROCESS_Y( j*2 + width*2 + 1, r, g, b, r0, g0, b0 );
			SAVE_RGB( bgrStep + 3, r, g, b );
		}
	}
}


static void CopyBGR_TO_BGR( int width, int height, BYTE* srcBGR, int srcStep,
									BYTE* dstBGR, int dstStep )
{
	int i;
	
	for( i = 0; i < height; i++, srcBGR += srcStep, dstBGR += dstStep )
	{
		memcpy( dstBGR, srcBGR, width*3 );            
	}
}


LRESULT CALLBACK capErrorCallback(
											 HWND hWnd,  
											 int nID,    
											 LPCSTR lpsz 
											 )
{
	AfxMessageBox(lpsz);
	return 1;
}


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

IMG_VFW::IMG_VFW()
{
	fbLive = 0;
	m_ScreenWidth = 640;
	m_ScreenHeight = 480;
	//iplimg = cvCreateImage( cvSize(600,800), IPL_DEPTH_32F, 3 );
	m_IplImage = cvCreateImage( cvSize(600,800), IPL_DEPTH_8U, 1 );

}

IMG_VFW::~IMG_VFW()
{
	if(m_hWndC)
		capDriverDisconnect( m_hWndC );
//	cvReleaseImage(&iplimg);
//	cvReleaseImage(&m_IplImage);
	
}

int IMG_VFW::Init()
{
	fStatus = kGrabberInitialized;
	return 1;
}


BYTE data[460800];
BYTE* dataf;
// Frame callback
LRESULT  FrameCallbackProc( HWND hWnd, VIDEOHDR* hdr ) 
{ 
			//capPreview(hWnd, 1);       
	//data = (BYTE*) hdr->lpData;
//	memcpy(iplimg->imageData, (hdr->lpData),350000);
	//m_IplImage->imageData = hdr->lpData;
	
	return 1;
	
} 

int IMG_VFW::StartLiveVideo( CWnd * apFrameWnd, HWND parent, CView * apView )
{
	if(!fbLive)
	{
		//apView->GetParent()->SetWindowPos( NULL, 0, 0, 800 , 600, SWP_NOMOVE | SWP_SHOWWINDOW | SWP_NOZORDER );			
		//HWND m_hWndC;
		//m_WndC = apFrameWnd;
		char szDeviceName[80];
		char szDeviceVersion[80];
		//m_hWndC = 0; 
		int wIndex = 0, format = -1;
		CAPSTATUS CapStatus;
		
		CAPTUREPARMS CaptureParms;
		float FramesPerSec = 10.0;
		LPBITMAPINFO lpbi;
		DWORD dwSize;
		
		
		 capGetDriverDescription( 0, szDeviceName, 
			sizeof (szDeviceName), szDeviceVersion, 
			sizeof (szDeviceVersion));
		 capGetDriverDescription( 1, szDeviceName, 
			sizeof (szDeviceName), szDeviceVersion, 
			sizeof (szDeviceVersion));
		
		//RECT rect;
		//apView->GetClientRect(&rect);
		ChooseSource();	
		while(wIndex<4){
		if( capGetDriverDescription( wIndex, szDeviceName, 
			sizeof (szDeviceName), szDeviceVersion, 
			sizeof (szDeviceVersion))) 
		{
			m_hWndC = capCreateCaptureWindow ( "My Own Capture Window", 
				WS_CHILD | WS_VISIBLE , 0, 0, m_ScreenWidth, m_ScreenHeight, parent, 0);
			//m_WndC.Attach(m_hWndC);
			if( capDriverConnect (m_hWndC, wIndex))
			{
				capSetCallbackOnError(m_hWndC,capErrorCallback); 
//				dwSize = capGetVideoFormatSize(m_hWndC);
//				lpbi = (LPBITMAPINFO)GlobalAlloc (GHND, dwSize);
//				capGetVideoFormat(m_hWndC, lpbi, dwSize); 
//				lpbi->bmiHeader.biWidth = 640;
//				lpbi->bmiHeader.biHeight = 480;
				//lpbi->bmiHeader.biBitCount = 8;
//				if(!capSetVideoFormat(  m_hWndC,  lpbi,  dwSize ))
//					ChooseFormat();
				capPreview(m_hWndC, TRUE);       
				capSetCallbackOnFrame(m_hWndC, FrameCallbackProc);
				capPreviewRate(m_hWndC, 66);     // rate, in milliseconds
				capPreviewScale(m_hWndC,TRUE);
				//capGrabFrame(m_WndC);
				FitWindow(apView);
			}
			fbLive = 1;
		}wIndex++;}
	}
	return 1;
	
}

void IMG_VFW::SaveFrameToBmp()
{
	if( !capFileSaveDIB(m_hWndC,"D:\\Bilder.bmp") )
		AfxMessageBox("Fehler in SaveFrameToBmp!"); 
	//StartLiveVideo(m_hWnd,
}  

void IMG_VFW::SaveFrameToBmp(char* name)
{
	if( !capFileSaveDIB(m_hWndC,name) )
		AfxMessageBox("Fehler in SaveFrameToBmp!"); 
}  

void IMG_VFW::GrabFrame()
{
	capGrabFrameNoStop(m_hWndC);
	
}


///LPBITMAPINFO lpbi;
//DWORD dwSize;

//dwSize = capGetVideoFormatSize(m_WndC);
//lpbi = (LPBITMAPINFO)GlobalAlloc (GHND, dwSize);
/**/	//	capGetVideoFormat(m_WndC, lpbi, dwSize); 
//lpbi->bmiHeader.biWidth = 100;
//lpbi->bmiHeader.biBitCount = 8;
// Access the video format and then free the allocated memory.

//capSetVideoFormat(  m_WndC,  lpbi,  dwSize );

/**/	//	capDriverGetCaps(m_WndC, &CapDrvCaps, sizeof (CAPDRIVERCAPS)); 

// Video source dialog box. 
//	if (CapDrvCaps.fHasDlgVideoSource)
//	capDlgVideoSource(m_WndC); 

// Video format dialog box. 
//if (CapDrvCaps.fHasDlgVideoDisplay)
//	capDlgVideoDisplay(m_WndC); 
//if (CapDrvCaps.fHasDlgVideoFormat) 
//				{
//	capDlgVideoFormat(m_WndC); 
// Are there new image dimensions?
// If so, notify the parent of a size change.
// Video display dialog box. 
//	} 
/**/	//	capGetStatus(m_WndC, &CapStatus, sizeof (CAPSTATUS));

//apView->GetParent()->SetWindowPos( NULL, 0, 0, CapStatus.uiImageWidth+10 , CapStatus.uiImageHeight+30, SWP_NOMOVE | SWP_SHOWWINDOW | SWP_NOZORDER );			


//capGetStatus(m_WndC, &CapStatus, sizeof (CAPSTATUS)); 
//capDriverGetCaps(m_WndC, &CapDrvCaps, sizeof (CAPDRIVERCAPS)); 
//capCaptureGetSetup(m_WndC, &CaptureParms, sizeof(CAPTUREPARMS));
//CaptureParms.dwRequestMicroSecPerFrame = (DWORD) (1.0e6 / 
//	FramesPerSec);
//capCaptureSetSetup(m_WndC, &CaptureParms, sizeof (CAPTUREPARMS)); 
//capSetCallbackOnFrame(m_WndC, FrameCallbackProc);
//capPreviewRate(m_WndC, 66);     // rate, in milliseconds
//capPreviewScale(m_WndC,TRUE);
//capPreview(WndC, TRUE);       
//capCaptureSequence(WndC);
//capFileSaveAs(WndC,"abra.avi");
//LPSTR text;
//capCaptureSequenceNoFile(WndC);
//}
//	fbLive = 1;
//FitWindow(apView);

// Wrapper for frame callback
void IMG_VFW::OnFrame( BYTE* data, int width, int height, int format, int bpp )
{
/*const int mirror = 1;

  if( m_isRunning )
  {
  BYTE *BGR;
  int bgrStep;
  CImage* img;
  bool refresh = width != m_frame.Width() || height != m_frame.Height();
  
	 // check if need reallocate image 
	 m_frame.Create( width, height, 24 );
	 
		img = m_frame.GetImage();
		
        BGR = (BYTE*)(img->imageData);
        bgrStep = img->Width()Step;
		  
			 if( format == MAKEFOURCC('Y','V','1','2') || format == MAKEFOURCC('I','4','2','0'))
			 {
			 BYTE *Y = data,
			 *U = Y + width*height,
			 *V = U + width*height/4;
			 
            ConvertYUV420_TO_BGR( width, height, Y, U, V, BGR, bgrStep );
				}
				else if( format == 0 && bpp == 24 )
				{
            int step = (width*3 + 3) & -4;
				
				  if( mirror )
				  {
				  BGR += bgrStep*(height - 1);
				  bgrStep = -bgrStep;
				  }
				  
					 CopyBGR_TO_BGR( width, height, data, step, BGR, bgrStep );
					 }
					 uchar buffer[sizeof(BITMAPINFOHEADER) + 1024];
					 BITMAPINFO* bmi = (BITMAPINFO*)buffer;
					 int bmp_w = 300;//Width();
					 int bmp_h = 300;//Height();
					 
						FillBitmapInfo( bmi, bmp_w, bmp_h, 1*8);//m_img.nChannels*8 );
						
						  int sw = 800;//MAX( MIN( bmp_w - from_x, w ), 0 );
						  int sh = 600;//MAX( MIN( bmp_h - from_y, h ), 0 );
						  
							 int res = StretchDIBits(//SetDIBitsToDevice(
							 m_HDC,                        // handle to DC
							 0,                         // x-coord of destination upper-left corner
							 0,                         // y-coord of destination upper-left corner 
							 sw,                        // source rectangle width
							 sh,                        // source rectangle height
							 0,                    // x-coord of source lower-left corner
							 0,                    // y-coord of source lower-left corner
							 300,                    // first scan line in array
							 300,                        // number of scan lines
							 data, //+ from_y*m_img.widthStep + from_x*m_img.nChannels,    // array of DIB bits
							 (BITMAPINFO*)bmi,          // bitmap information
							 DIB_RGB_COLORS,
							 SRCCOPY );
							 
								//UpdateParent( refresh );
}*/
}



/*void IMG_VFW::Show( HDC dc, int x, int y, int w, int h, int from_x, int from_y )
{
if( m_img.width > 0 )
{
uchar buffer[sizeof(BITMAPINFOHEADER) + 1024];
BITMAPINFO* bmi = (BITMAPINFO*)buffer;
int bmp_w = Width();
int bmp_h = Height();

  FillBitmapInfo( bmi, bmp_w, bmp_h, m_img.nChannels*8 );
  
	 int sw = MAX( MIN( bmp_w - from_x, w ), 0 );
	 int sh = MAX( MIN( bmp_h - from_y, h ), 0 );
	 
		int res = SetDIBitsToDevice(
		dc,                        // handle to DC
		x,                         // x-coord of destination upper-left corner
		y,                         // y-coord of destination upper-left corner 
		sw,                        // source rectangle width
		sh,                        // source rectangle height
		from_x,                    // x-coord of source lower-left corner
		from_y,                    // y-coord of source lower-left corner
		from_y,                    // first scan line in array
		sh,                        // number of scan lines
		m_img.imageData + from_y*m_img.widthStep + from_x*m_img.nChannels,    // array of DIB bits
		(BITMAPINFO*)bmi,          // bitmap information
		DIB_RGB_COLORS );          // RGB or palette indexes
		}
}*/




int IMG_VFW::Disable()
{
	return 0;
}
//; Disable the grabber

//; Send the live image to aWnd
int IMG_VFW::StopLiveVideo( HWND aWnd )
{
	capPreview(m_hWndC, 0);       
	return 0;
}
//; Stop the live image to aWnd

/*	int IMG_VFW::SnapShot( HWND aWindowHandle, MtqGreyImage & aImg, CView * apView )
{
char str[300];
sprintf(str,"c:\dib.bmp");
int error = capFileSaveDIB(WndC, str);
Bitmap bmp(str,BM_NORMAL);
bmp.ConvertTo8BitGrayScale();
MtqGreyImage img(640,480,bmp.Buffer);
aImg = img;
return 0;
	} */
//: Get one new image (SnapShot) from the grabber
//. Target for storage is the Image "aImg" (MtqGreyImage)

bool const IMG_VFW::IsInitialised()
{
	return 0;
}	
//; Check, if the grabber was initialized properly

int IMG_VFW::SelectCamera( int const aCamNr )
{
	return 0;
}
//; Switch to other camera

int IMG_VFW::FitWindow( CView * apView )
{
	apView->GetParent()->SetWindowPos( NULL, 0, 0, 650, 500, SWP_NOMOVE | SWP_SHOWWINDOW | SWP_NOZORDER );			
	return 1;
} 

/*int IMG_VFW::SnapShot( MtqGreyImage & aImg )
{
return 0;
	}*/

void IMG_VFW::ChooseSource()
{
	// Video source dialog box. 
	if (CapDrvCaps.fHasDlgVideoSource)
		capDlgVideoSource(m_hWndC); 
	
}


void IMG_VFW::ChooseFormat()
{
	// Video format dialog box. 
	if (CapDrvCaps.fHasDlgVideoFormat)
		capDlgVideoFormat(m_hWndC); 

}


void IMG_VFW::ChooseDisplay()
{
	// Video display dialog box. 
	if (CapDrvCaps.fHasDlgVideoDisplay)
		capDlgVideoDisplay(m_hWndC); 

}



CImage* IMG_VFW::GetStaticImage()
{
//	CImage* greyimg = cvCreateImageHeader(cvSize(600,800),IPL_DEPTH_32F,1); 
//	cvCreateImageData(greyimg);
//	cvCvtColor(iplimg, greyimg, CV_RGB2GRAY); // convery color image to grey

	//return greyimg;
	return 0;
}



