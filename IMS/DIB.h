//
//  Class:		CDIB
//
//  File :		CDIB.h
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

#ifndef _DIBmp_H_
#define _DIBmp_H_

// used prototypes (MFC):
class CDC;
class CFile;


// Std-Lib:
// -------------------------------
#if defined (_MSC_VER)	// MS VC++
// -------------------------------
# include <assert.h>
# include <wtypes.h>
# include <iostream>
# pragma warning (disable:4786)
# pragma warning (disable:4804)
using namespace std;
// -------------------------------
#elif defined (__GNUC__) //GNU C++
// -------------------------------
# error "MFC-Ext NOT supported with GNU"
// -------------------------------
#elif defined (_UCC)	// MW Hawk
// -------------------------------
# error "MFC-Ext NOT supported with UCC"
// -------------------------------
#else					// Default
// -------------------------------
# error "MFC-Ext NOT supported"
// -------------------------------
#endif//Compiler-specific includes
// -------------------------------


class CDIB 
//; class for displaying bitmaps in Windows
{
    friend class CBmpPalette;
    //; protected access to MFC class CBmpPalette

protected:
	bool m_CreateOwnDataField;
    //; flag for creating the own datafield
    BITMAPINFO * m_pInfo;
    //; Pointer to BMP Info Header
    BYTE * m_pPixels;
    //; Pointer to BMP Data
    CRITICAL_SECTION m_Lock;
    //; Critical Section for Multithreading-safe access

public:
    CDIB( bool const aCreateOwnDataField = true );
    //; Default construction

    virtual ~CDIB();
    //; simple destruction

    virtual void Draw( CDC * apDC, float const & aZoomFactor = 1.f, int const aDestX = 0, int const aDestY = 0 ) const;
    //; paint into a CDC with a zoom factor
    virtual void Draw( CDC* pDC, int const DestX, int const DestY, int DestWidth = 0, int DestHeight = 0 ) const; // draw the bitmap
    //; paint into a CDC into a destination rect

	virtual BOOL Load( lti::channel aImg );
    virtual BOOL Load( BYTE * apPixels, int const aSrcWidth, int const aSrcHeight, int const aDestWidth, int const aDestHeight );
    //; Load the image from a Data Field

    //; Get a MtqGreyImage from the DIB
    //; Get a MtqColorImage from the DIB

    bool const IsValid() const; 
    //; Check, if the image is valid
    
    void SetPixel( int const aX, int const aY, unsigned char const aCol );
    //; Set a pixel in a grey image
    void SetPixel( int const x, int const y, unsigned char const * rgb );
    //; Set a pixel in a color image
    BYTE* GetPixel( int const x, int const y );
    //; Get a pixel in a grey image

    int const Width() const;
    //; Get Bmp's Width() in pixels
    int const Height() const;
    //; Get Bmp's Width() in pixels

	void SetColorTable( unsigned char rgb[3][256] ); 
    //; Setup the color table from other table
    int GetBitCount() const { return m_pInfo->bmiHeader.biBitCount; }
    //; Get Bmp's bits per pixel

protected:
    void Lock()     { EnterCriticalSection( &m_Lock ); }
    //; Lock from the access of other threads
    void UnLock()   { EnterCriticalSection( &m_Lock ); }
    //; UnLock for the access of other threads

    BITMAPINFO* GetHeaderPtr();
    //; Get the pointer to the bitmap header (info & color table) 
    BITMAPINFO const * GetHeaderPtr() const;
    //; Get the pointer to the info header (image information)
    RGBQUAD * GetColorTablePtr();
    //; Get the pointer to the color table
    BYTE * GetPixelPtr();
    //; Get the pointer to the pixel data (L-Value)
    BYTE const * GetPixelPtr() const;
    //; Get the pointer to the pixel data (R-Value)
    int GetPalEntries() const { ASSERT( m_pInfo ); return GetPalEntries( *(BITMAPINFOHEADER*)m_pInfo ); }
    //; Get the pointer to the Palette Entries
    int GetPalEntries( BITMAPINFOHEADER & infoHeader ) const;
    //; Get the pointer to the Palette Entries
    int CalcZoomFactor(int aSrcWidth, int src_height, int dest_width, int dest_height);
    //; Calculate the zoom factor
};


/////////////////////////////////////////////
// Implementation of inline functions

inline BITMAPINFO* CDIB::GetHeaderPtr() 
{
    assert( m_pInfo );
    assert( m_pPixels );
    return m_pInfo;
}

inline BITMAPINFO const * CDIB::GetHeaderPtr() const 
{
    assert( m_pInfo );
    assert( m_pPixels );
    return m_pInfo;
}

inline BYTE* CDIB::GetPixelPtr() 
{
    assert( m_pInfo );
    assert( m_pPixels );
    return m_pPixels;
}

inline BYTE const * CDIB::GetPixelPtr() const 
{
    assert( m_pInfo );
    assert( m_pPixels );
    return m_pPixels;
}

inline int const CDIB::Width() const 
{
    assert( m_pInfo );
    return m_pInfo->bmiHeader.biWidth;
}

inline int const CDIB::Height() const 
{
    assert( m_pInfo );
    return m_pInfo->bmiHeader.biHeight;
}

inline bool const CDIB::IsValid() const
{ 
	return (m_pInfo && m_pInfo->bmiHeader.biSizeImage); 
}

inline void CDIB::SetPixel( int const aX, int const aY, unsigned char const aCol ) 
{ 
	assert( m_pInfo );
	assert( m_pPixels );
	
	unsigned int dib_mem_width = Width() * m_pInfo->bmiHeader.biBitCount/8;
	dib_mem_width = (!(dib_mem_width%sizeof(LONG)))? dib_mem_width : dib_mem_width - dib_mem_width%sizeof(LONG) + sizeof(LONG);
	m_pPixels[aX * m_pInfo->bmiHeader.biBitCount/8 + aY * dib_mem_width] = aCol; 
}

inline void CDIB::SetPixel( int const aX, int const aY, unsigned char const * aCol ) 
{ 
	assert( m_pInfo );
	assert( m_pPixels );
	
	unsigned int dib_mem_width = Width() * m_pInfo->bmiHeader.biBitCount/8;
	dib_mem_width = (!(dib_mem_width%sizeof(LONG)))? dib_mem_width : dib_mem_width - dib_mem_width%sizeof(LONG) + sizeof(LONG);
	memcpy( m_pPixels + aX * m_pInfo->bmiHeader.biBitCount/8 + aY * dib_mem_width, aCol, m_pInfo->bmiHeader.biBitCount/8); 
}

inline BYTE * CDIB::GetPixel( int const aX, int const aY ) 
{
    assert( m_pInfo );
    assert( m_pPixels );
    
    unsigned int dib_mem_width = Width() * m_pInfo->bmiHeader.biBitCount/8;
    dib_mem_width = (!(dib_mem_width%sizeof(LONG)))? dib_mem_width : dib_mem_width - dib_mem_width%sizeof(LONG) + sizeof(LONG);
    return m_pPixels + aX * m_pInfo->bmiHeader.biBitCount/8 + aY * dib_mem_width; 
}

inline int CDIB::GetPalEntries( BITMAPINFOHEADER & infoHeader ) const
{
    if( infoHeader.biClrUsed == 0 )
        return ( 1 << infoHeader.biBitCount );
    else return infoHeader.biClrUsed;
}

#endif /*_DIBmp_H_*/

