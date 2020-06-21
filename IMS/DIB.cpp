//
//  Class:		CDIB
//
//  File :		CDIB.cpp
//
//  Modul:		MtqLib: MFCExt 
//
//  Purpose:	class for displaying bitmap 
//				images in windows
//
//  Author:		Dominic Sack (sac)
// 
//  Version:	13/01/01   Initial version							(sac)
//				18/01/01   Image on the head bug fixed, naming		(sac)
// 
//  Status:		working in slow (own data field, copy operation) version
//				fast version is in implementation
// 


// MFC functions & classes 
#include "stdafx.h"

// this file's header:
#include "DIB.h"

  

CDIB::CDIB( bool const aCreateOwnDataField )
{
	m_CreateOwnDataField = aCreateOwnDataField; 
    m_pInfo = 0;
    m_pPixels = 0;
    InitializeCriticalSection( &m_Lock );
}

CDIB::~CDIB()
{
	if (m_pInfo) 
	    delete[] (BYTE*)m_pInfo;
    if (m_CreateOwnDataField) 
		if (m_pPixels) 
			delete[] m_pPixels;
    DeleteCriticalSection( &m_Lock );
}

///////////////////////////////////////////////////////////////////////////
// load DIB from MtqImage (copy and zoom)

//DEL BOOL CDIB::Load( MtqColorImage const & aImg, int const aDestZoom )
//DEL {
//DEL 	// Store the sizes of the DIB structures
//DEL 	int cInfo = sizeof(BITMAPINFOHEADER);
//DEL 	unsigned int dibwidth = (!((aImg.Width()*3)%sizeof(LONG))) ? (aImg.Width()*3) : (aImg.Width()*3) - (aImg.Width()*3)%sizeof(LONG) + sizeof(LONG);
//DEL 	unsigned int cPixels = aImg.Height()* dibwidth * 3;
//DEL 	if (!m_pInfo) 
//DEL 	{// alloc new DIB
//DEL 		m_pInfo = (BITMAPINFO*)new BYTE[cInfo];
//DEL 		m_pPixels = new BYTE[cPixels];
//DEL 		ASSERT(m_pInfo);
//DEL 		ASSERT(m_pPixels);
//DEL 	} 
//DEL 	else if (m_pInfo->bmiHeader.biSizeImage != cPixels) 
//DEL 	{// delete old and allocate new DIB pixel array
//DEL 		delete[] m_pPixels;
//DEL 		m_pPixels = new BYTE[cPixels];
//DEL 		ASSERT(m_pPixels);
//DEL 	}
//DEL 	
//DEL 	// init DIB header
//DEL 	m_pInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);	// bih size
//DEL 	m_pInfo->bmiHeader.biWidth = aImg.Width() / aDestZoom;	// Img Width
//DEL 	m_pInfo->bmiHeader.biHeight = aImg.Height() / aDestZoom;// Img Width
//DEL 	m_pInfo->bmiHeader.biPlanes = 1;						// default for NT
//DEL 	m_pInfo->bmiHeader.biBitCount = 24;						// 8 bit per pixel
//DEL 	m_pInfo->bmiHeader.biCompression = BI_RGB;				// not compressed
//DEL 	m_pInfo->bmiHeader.biSizeImage = 0;						// image size
//DEL 	m_pInfo->bmiHeader.biXPelsPerMeter = 0;					// ???
//DEL 	m_pInfo->bmiHeader.biYPelsPerMeter = 0;					// ???
//DEL 	m_pInfo->bmiHeader.biClrUsed = 0;						// used colors (0 == max)
//DEL 	m_pInfo->bmiHeader.biClrImportant = 0;					// all colors important
//DEL 	
//DEL 	// copy pixels (line by line to mirror the image)
//DEL 	int i, j , k;
//DEL 	for(j = 0, k = 0; j < aImg.Height(); ++j)
//DEL 	{
//DEL 		for(i = 0; i < aImg.Width(); i++, k+=3)
//DEL 		{
//DEL 			m_pPixels[k] = aImg(i,j).R();
//DEL 			m_pPixels[k+1] = aImg(i,j).G();
//DEL 			m_pPixels[k+2] = aImg(i,j).B();
//DEL 		}
//DEL 	}
//DEL 	
//DEL 	return TRUE;
//DEL }


//DEL BOOL CDIB::Load( MtqGreyImage const & aImg, int const aDestZoom )
//DEL {
//DEL 	// Store the sizes of the DIB structures
//DEL     int cInfo = sizeof(BITMAPINFOHEADER) + (256 * sizeof(RGBQUAD));
//DEL     unsigned int dibwidth = aImg.Width();
//DEL     unsigned int cPixels = aImg.Height()* dibwidth;
//DEL 	int n = 0;	// loop counter
//DEL 
//DEL 	if (!m_pInfo) 
//DEL     {// alloc new DIB
//DEL 	    m_pInfo = (BITMAPINFO*)new BYTE[cInfo];
//DEL 	    m_pPixels = new BYTE[cPixels];
//DEL 		ASSERT(m_pInfo);
//DEL 		ASSERT(m_pPixels);
//DEL 	} 
//DEL     else if (m_pInfo->bmiHeader.biSizeImage != cPixels) 
//DEL     {// delete old and allocate new DIB pixel array
//DEL 		delete[] m_pPixels;
//DEL 	    m_pPixels = new BYTE[cPixels];
//DEL 		ASSERT(m_pPixels);
//DEL 	}
//DEL 
//DEL 	// init DIB header
//DEL 	m_pInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//DEL 	m_pInfo->bmiHeader.biWidth = aImg.Width() / aDestZoom; 
//DEL 	m_pInfo->bmiHeader.biHeight = aImg.Height() / aDestZoom; 
//DEL 	m_pInfo->bmiHeader.biPlanes = 1;			// default for NT
//DEL 	m_pInfo->bmiHeader.biBitCount = 8;			// 8 bit per pixel
//DEL 	m_pInfo->bmiHeader.biCompression = BI_RGB;	// not compressed
//DEL 	m_pInfo->bmiHeader.biSizeImage = aImg.Width() * aImg.Height();	// image size
//DEL 	m_pInfo->bmiHeader.biXPelsPerMeter = 0;		// ???
//DEL 	m_pInfo->bmiHeader.biYPelsPerMeter = 0;		// ???
//DEL 	m_pInfo->bmiHeader.biClrUsed = 256;			// used colors (0 == max)
//DEL 	m_pInfo->bmiHeader.biClrImportant = 0;		// all colors important
//DEL 
//DEL 	// init color table (256 colors, grey scale):
//DEL 	for (n = 0; n <256; n++) 
//DEL     {
//DEL 		m_pInfo->bmiColors[n].rgbBlue = n; 
//DEL 		m_pInfo->bmiColors[n].rgbGreen = n; 
//DEL 		m_pInfo->bmiColors[n].rgbRed = n; 
//DEL 		m_pInfo->bmiColors[n].rgbReserved = 0;
//DEL 	}
//DEL 
//DEL 	// copy pixels (line by line to mirror the image):
//DEL 	int line_offset;
//DEL     for(n = 0, line_offset = 0; n < aImg.Height(); ++n, line_offset+=dibwidth)
//DEL 		memcpy(m_pPixels + line_offset, aImg.GetLinePtr( n ), aImg.Width() );
//DEL 
//DEL 	return TRUE;
//DEL }

BOOL CDIB::Load( lti::channel aImg )
 {
 	// Store the sizes of the DIB structures
     int cInfo = sizeof(BITMAPINFOHEADER) + (256 * sizeof(RGBQUAD));
     unsigned int dibwidth = aImg.columns();
     unsigned int cPixels = aImg.rows()* dibwidth;
 	int n = 0;	// loop counter
 
 	if (!m_pInfo) 
     {// alloc new DIB
 	    m_pInfo = (BITMAPINFO*)new BYTE[cInfo];
 	    m_pPixels = new BYTE[cPixels];
 		ASSERT(m_pInfo);
 		ASSERT(m_pPixels);
 	} 
     else if (m_pInfo->bmiHeader.biSizeImage != cPixels) 
     {// delete old and allocate new DIB pixel array
 		delete[] m_pPixels;
 	    m_pPixels = new BYTE[cPixels];
 		ASSERT(m_pPixels);
 	}
 
 	// init DIB header
 	m_pInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
 	m_pInfo->bmiHeader.biWidth = aImg.columns() ; 
 	m_pInfo->bmiHeader.biHeight = aImg.rows() ; 
 	m_pInfo->bmiHeader.biPlanes = 1;			// default for NT
 	m_pInfo->bmiHeader.biBitCount = 8;			// 8 bit per pixel
 	m_pInfo->bmiHeader.biCompression = BI_RGB;	// not compressed
 	m_pInfo->bmiHeader.biSizeImage = aImg.columns() * aImg.rows();	// image size
 	m_pInfo->bmiHeader.biXPelsPerMeter = 0;		// ???
 	m_pInfo->bmiHeader.biYPelsPerMeter = 0;		// ???
 	m_pInfo->bmiHeader.biClrUsed = 256;			// used colors (0 == max)
 	m_pInfo->bmiHeader.biClrImportant = 0;		// all colors important
 
 	// init color table (256 colors, grey scale):
 	for (n = 0; n <256; n++) 
     {
 		m_pInfo->bmiColors[n].rgbBlue = n; 
 		m_pInfo->bmiColors[n].rgbGreen = n; 
 		m_pInfo->bmiColors[n].rgbRed = n; 
 		m_pInfo->bmiColors[n].rgbReserved = 0;
 	}
 
 	// copy pixels (line by line to mirror the image):
 	int line_offset;
     for(n = 0, line_offset = 0; n < aImg.rows(); ++n, line_offset+=dibwidth)
		for(int i=0;i<aImg.columns();i++)
			*(m_pPixels + line_offset)= aImg.at(n,i) * 256;
 		//memcpy(m_pPixels + line_offset, aImg.GetLinePtr( n ), aImg.Width() );
 
 	return TRUE;
 }

///////////////////////////////////////////////////////////////////////////
// load DIB from pixel-array (copy and zoom)

BOOL CDIB::Load( BYTE * apPixels, int const aSrcWidth, int const aSrcHeight, int aDestWidth, int aDestHeight )

{
	int DestZoom = CalcZoomFactor( aSrcWidth, aSrcHeight, aDestWidth, aDestHeight );
    int cInfo = sizeof(BITMAPINFOHEADER) + (256 * sizeof(RGBQUAD));
    unsigned int cPixels = (aSrcWidth * aSrcHeight) / DestZoom;

	if (!m_pInfo) 
    {// alloc new DIB
	    m_pInfo = (BITMAPINFO*)new BYTE[cInfo];
	    m_pPixels = new BYTE[cPixels];
		ASSERT(m_pInfo);
		ASSERT(m_pPixels);
	} 
	else if (m_pInfo->bmiHeader.biSizeImage != cPixels) 
    {// delete old and allocate new DIB pixel array
		delete[] m_pPixels;
	    m_pPixels = new BYTE[cPixels];
		ASSERT(m_pPixels);
	}

	m_pInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pInfo->bmiHeader.biWidth = aSrcWidth / DestZoom; 
	m_pInfo->bmiHeader.biHeight = aSrcHeight / DestZoom; 
	m_pInfo->bmiHeader.biPlanes = 1;			// default for NT
	m_pInfo->bmiHeader.biBitCount = 8;			// 8 bit per pixel
	m_pInfo->bmiHeader.biCompression = BI_RGB;	// not compressed
	m_pInfo->bmiHeader.biSizeImage = cPixels;	// image size
	m_pInfo->bmiHeader.biXPelsPerMeter = 0;		// ???
	m_pInfo->bmiHeader.biYPelsPerMeter = 0;		// ???
	m_pInfo->bmiHeader.biClrUsed = 0;			// used colors (0 == max)
	m_pInfo->bmiHeader.biClrImportant = 0;		// all colors important
	//; init the DIB header

	for (int n = 0; n <256; ++n) 
	{
		m_pInfo->bmiColors[n].rgbBlue = (unsigned char) n; 
		m_pInfo->bmiColors[n].rgbGreen = (unsigned char) n; 
		m_pInfo->bmiColors[n].rgbRed = (unsigned char) n; 
		m_pInfo->bmiColors[n].rgbReserved = 0;
	}
	//; init color table (256 colors, grey scale)

	// copy pixels and zoom (line by line to mirror the image)
	if (DestZoom == 1) 
    {
		int line_offset = 0;
		unsigned char * imgptr;
		imgptr = apPixels + (aSrcWidth * (aSrcHeight - 1)) ; // last line pointer
		for (n = 1; n <= aSrcHeight; n++) 
		{
		// for each line...
			memcpy(m_pPixels + line_offset, imgptr, aSrcWidth);
			line_offset += aSrcWidth-20;
			imgptr -= aSrcWidth-20;
		}
	} 
	else 
	{
		ASSERT( DestZoom <= 4 );
		unsigned char * tpix;
		unsigned int * spix;
		for (int y = 0; y < aSrcHeight / DestZoom; y++) 
		{
			tpix = m_pPixels + (y * (aSrcWidth / DestZoom));
			spix = (unsigned int *) (apPixels + (aSrcWidth * (aSrcHeight - y * DestZoom - 1)));
			for ( int x = 0; x < aSrcWidth / DestZoom; x += DestZoom /* ??? */) 
			{
				if (DestZoom == 2) 
				{
					*tpix = *spix & 0x000000ff;
					tpix++;
					*tpix = *spix & 0x00ff0000 >> 16;
					tpix++;
					spix++;
				} 
				else 
				{
					*tpix = *spix;
					spix += DestZoom;
					tpix++;
				}
			}
		}
	}
	return TRUE;
}



//DEL BOOL CDIB::GetImage( MtqGreyImage & aImg )
//DEL {
//DEL     if(m_pInfo->bmiHeader.biPlanes == 1 && m_pInfo->bmiHeader.biBitCount == 8)
//DEL     {
//DEL         int i,j;
//DEL         aImg.Set(m_pInfo->bmiHeader.biWidth, m_pInfo->bmiHeader.biHeight);
//DEL         for(i = 0; i < aImg.Width(); i++)
//DEL             for(j = 0; j < aImg.Height(); j++)
//DEL                 aImg(i,j) = *GetPixel(i,j);
//DEL             
//DEL         return TRUE;
//DEL     } 
//DEL     else 
//DEL         return FALSE;
//DEL     
//DEL }

//DEL BOOL CDIB::GetImage( MtqColorImage & aImg )
//DEL {
//DEL     if(m_pInfo->bmiHeader.biPlanes == 1 && m_pInfo->bmiHeader.biBitCount == 24)
//DEL     {
//DEL         int i,j;
//DEL         aImg.Set(m_pInfo->bmiHeader.biWidth, m_pInfo->bmiHeader.biHeight);
//DEL         for(i = 0; i < aImg.Width(); i++)
//DEL             for(j = 0; j < aImg.Height(); j++)
//DEL             {
//DEL                 MtqRGB & rgb = aImg(i,j);
//DEL                 rgb.Set(GetPixel(i,aImg.Height()-1-j)[2],GetPixel(i,aImg.Height()-1-j)[1],GetPixel(i,aImg.Height()-1-j)[0]);
//DEL             }
//DEL             
//DEL         return TRUE;
//DEL     } 
//DEL     else 
//DEL         return FALSE;
//DEL }


///////////////////////////////////////////////////////////////////////////
// draw DIB (and zoom)
void CDIB::Draw( CDC * apDC, float const & aZoomFactor, int const aDestX, int const aDestY ) const
{
    Draw( apDC, aDestX, aDestY, aZoomFactor * Width(), aZoomFactor * Height() );
}

void CDIB::Draw( CDC* pDC, int const DestX, int const DestY, int DestWidth, int DestHeight ) const
{
    int const SrcX=0;
    int const SrcY=0;
    int const SrcWidth=Width();
    int const SrcHeight=Height();
    ASSERT( pDC );
    // default params
    
    if (DestWidth == 0)
        DestWidth = Width();
    if (DestHeight == 0)
        DestHeight = Height();
    
    HDC hdc = pDC->GetSafeHdc();
    ASSERT(hdc);
    
    if( m_pInfo ) 
    {
        int rc;
        rc = StretchDIBits( 
            hdc,
            DestX,
            DestY,
            DestWidth,
            DestHeight,
            SrcX,
            SrcY,
            SrcWidth,
            SrcHeight,
            GetPixelPtr(),
            GetHeaderPtr(),
            DIB_RGB_COLORS,
            SRCCOPY );
        ASSERT(rc != GDI_ERROR);
    }
}

RGBQUAD* CDIB::GetColorTablePtr()
{
	ASSERT( m_pInfo );
	ASSERT( m_pPixels );
	RGBQUAD* pColorTable = 0;
	
	if( m_pInfo != 0 )
	{
		int cOffset = sizeof(BITMAPINFOHEADER);
		pColorTable = (RGBQUAD*)(((BYTE*)(m_pInfo)) + cOffset);
	}
	return pColorTable;
}


void CDIB::SetColorTable(unsigned char rgb[3][256])
{
    int n;
    for (n = 0; n <256; n++) 
    {
        m_pInfo->bmiColors[n].rgbRed = rgb[0][n];
        m_pInfo->bmiColors[n].rgbGreen = rgb[1][n];
        m_pInfo->bmiColors[n].rgbBlue = rgb[2][n];
        m_pInfo->bmiColors[n].rgbReserved = 0;
    }
    return;
}



int CDIB::CalcZoomFactor(int aSrcWidth, int aSrcHeight, int aDestWidth, int aDestHeight) 
{
    int DisplayZoom = 1;	// 1 == no zooming, src image is smaller then the display
    if (aSrcWidth > aDestWidth || aSrcHeight > aDestHeight) 
    {
        // lets zoom, image is bigger then display (in one or two directions...)
        if ( aSrcWidth <= aDestWidth ) 
        {// image is bigger in Y direction only
            DisplayZoom = aSrcHeight / aDestHeight + 1;
        } 
        else 
        {
            if ( aSrcHeight <= aDestHeight ) 
            {
                // image is bigger in Y direction only
                DisplayZoom = aSrcWidth / aDestWidth + 1;
            } 
            else 
            {
                // image is bigger in both directions
                if ((double)((double) aDestWidth / aSrcWidth) <= (double)((double) aDestHeight / aSrcHeight) ) 
                    DisplayZoom =  aSrcWidth / aDestWidth + 1;
                else DisplayZoom = aSrcHeight / aDestHeight + 1;
            }
        }
        // max zoom factor == 4
        if ( DisplayZoom > 4 )
            DisplayZoom = 4;
    }
    return DisplayZoom;
}

