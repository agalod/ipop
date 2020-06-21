// Von Klassen-Assistent automatisch erstellte IDispatch-Kapselungsklasse(n).

#include "stdafx.h"
#include "avtpicturecontrol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _ICameraViewEvents 

/////////////////////////////////////////////////////////////////////////////
// Operationen _ICameraViewEvents 


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften ICameraView 

/////////////////////////////////////////////////////////////////////////////
// Operationen ICameraView 

void ICameraView::SetGain(long gain)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 gain);
}

long ICameraView::GetGain()
{
	long result;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long ICameraView::GetGainMin()
{
	long result;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long ICameraView::GetGainMax()
{
	long result;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void ICameraView::Wait(long milli)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 milli);
}

void ICameraView::StatusText(LPCTSTR test)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 test);
}

void ICameraView::StartCapture()
{
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ICameraView::StopCapture()
{
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ICameraView::FullSize()
{
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ICameraView::HalfSize()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ICameraView::QuarterSize()
{
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long ICameraView::CameraProperties()
{
	long result;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long ICameraView::FormatProperties()
{
	long result;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void ICameraView::FullMainWindow()
{
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ICameraView::NormalMainWindow()
{
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ICameraView::SaveBitmap(LPCTSTR fileName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 fileName);
}

void ICameraView::TakeBitmap()
{
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften _ICMainFrmObjEvents 

/////////////////////////////////////////////////////////////////////////////
// Operationen _ICMainFrmObjEvents 


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften ICMainFrmObj 

/////////////////////////////////////////////////////////////////////////////
// Operationen ICMainFrmObj 

void ICMainFrmObj::PaintStatusText(LPCTSTR text)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 text);
}

void ICMainFrmObj::ShowNormal()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ICMainFrmObj::ShowMaximized()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ICMainFrmObj::ShowMinimized()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH ICMainFrmObj::GetCameraNames()
{
	LPDISPATCH result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ICMainFrmObj::GetFriendlyNames()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ICMainFrmObj::ShowDeviceDialog()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ICMainFrmObj::OpenCamera(long camera, long view)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		camera, view);
	return result;
}

void ICMainFrmObj::Cascade()
{
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void ICMainFrmObj::Tile(BOOL horizontal)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 horizontal);
}

LPDISPATCH ICMainFrmObj::GetActive()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH ICMainFrmObj::GetViewNames()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long ICMainFrmObj::GetIndexForName(LPCTSTR name)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		name);
	return result;
}

long ICMainFrmObj::GetIndexForFriendlyName(LPCTSTR friendlyName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		friendlyName);
	return result;
}

long ICMainFrmObj::GetIndexForView(LPCTSTR view)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		view);
	return result;
}

void ICMainFrmObj::Sleep(long milliSeconds)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 milliSeconds);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften INameArray 

/////////////////////////////////////////////////////////////////////////////
// Operationen INameArray 

LPUNKNOWN INameArray::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

VARIANT INameArray::GetItem(long index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		index);
	return result;
}

long INameArray::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften IFriendlyNameArray 

/////////////////////////////////////////////////////////////////////////////
// Operationen IFriendlyNameArray 

LPUNKNOWN IFriendlyNameArray::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

VARIANT IFriendlyNameArray::GetItem(long index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		index);
	return result;
}

long IFriendlyNameArray::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften INormalChild 

/////////////////////////////////////////////////////////////////////////////
// Operationen INormalChild 

void INormalChild::Start()
{
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void INormalChild::Stop()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void INormalChild::FullSize()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void INormalChild::HalfSize()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void INormalChild::QuarterSize()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void INormalChild::FullScreen()
{
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long INormalChild::GetXPos()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void INormalChild::SetXPos(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long INormalChild::GetYPos()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void INormalChild::SetYPos(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long INormalChild::GetWidth()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void INormalChild::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long INormalChild::GetHeight()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void INormalChild::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long INormalChild::GetPictureWidth()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void INormalChild::SetPictureWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long INormalChild::GetPictureHeight()
{
	long result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void INormalChild::SetPictureHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void INormalChild::FormatDialog()
{
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void INormalChild::PropertieDialog()
{
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void INormalChild::ShowMaximized()
{
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void INormalChild::ShowMinimized()
{
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void INormalChild::ShowNormal()
{
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString INormalChild::GetCameraName()
{
	CString result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString INormalChild::GetFriendlyName()
{
	CString result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString INormalChild::GetViewType()
{
	CString result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH INormalChild::GetCameraObj()
{
	LPDISPATCH result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void INormalChild::TakePicture()
{
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void INormalChild::SavePicture(LPCTSTR fileName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 fileName);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften IViewArray 

/////////////////////////////////////////////////////////////////////////////
// Operationen IViewArray 

LPUNKNOWN IViewArray::Get_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}

VARIANT IViewArray::GetItem(long index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		index);
	return result;
}

long IViewArray::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften IActivXChild 

/////////////////////////////////////////////////////////////////////////////
// Operationen IActivXChild 

void IActivXChild::Start()
{
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IActivXChild::Stop()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IActivXChild::FullSize()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IActivXChild::HalfSize()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IActivXChild::QuarterSize()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IActivXChild::FullScreen()
{
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IActivXChild::GetXPos()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IActivXChild::SetXPos(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IActivXChild::GetYPos()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IActivXChild::SetYPos(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IActivXChild::GetWidth()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IActivXChild::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IActivXChild::GetHeight()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IActivXChild::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IActivXChild::FormatDialog()
{
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IActivXChild::PropertieDialog()
{
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IActivXChild::ShowMaximized()
{
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IActivXChild::ShowMinimized()
{
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IActivXChild::ShowNormal()
{
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString IActivXChild::GetCameraName()
{
	CString result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IActivXChild::GetFriendlyName()
{
	CString result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IActivXChild::GetViewType()
{
	CString result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH IActivXChild::GetControl()
{
	LPDISPATCH result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IActivXChild::GetAVTExtender()
{
	LPDISPATCH result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IActivXChild::GetCameraObj()
{
	LPDISPATCH result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften IAVTExtender 

/////////////////////////////////////////////////////////////////////////////
// Operationen IAVTExtender 

CString IAVTExtender::GetFriendlyCameraName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAVTExtender::SetFriendlyCameraName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IAVTExtender::CameraProperties()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAVTExtender::FormatProperties()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAVTExtender::Run()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAVTExtender::Stop()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAVTExtender::ActivateMenu(unsigned long hMenu)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 hMenu);
}

void IAVTExtender::HandleMenuCommand(unsigned long commandID)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 commandID);
}

BOOL IAVTExtender::IsRunning()
{
	BOOL result;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IAVTExtender::IsWritingFile()
{
	BOOL result;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAVTExtender::DeInitialize()
{
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAVTExtender::GetStandardSize(long* Width, long* Height)
{
	static BYTE parms[] =
		VTS_PI4 VTS_PI4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Width, Height);
}


/////////////////////////////////////////////////////////////////////////////
// Eigenschaften ICameraObj 

/////////////////////////////////////////////////////////////////////////////
// Operationen ICameraObj 

BOOL ICameraObj::GetGamma()
{
	BOOL result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void ICameraObj::SetGamma(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long ICameraObj::GetGainMin()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICameraObj::GetGainMax()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL ICameraObj::GetGainAutoAvailable()
{
	BOOL result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL ICameraObj::GetGainOnePushAvailable()
{
	BOOL result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long ICameraObj::GetGain()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ICameraObj::SetGain(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL ICameraObj::GetGainOnePush()
{
	BOOL result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void ICameraObj::SetGainOnePush(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL ICameraObj::GetGainAuto()
{
	BOOL result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void ICameraObj::SetGainAuto(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long ICameraObj::GetWhitebalanceVMin()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICameraObj::GetWhitebalanceVMax()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL ICameraObj::GetWhitebalanceVAutoAvailable()
{
	BOOL result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL ICameraObj::GetWhitebalanceVOnePushAvailable()
{
	BOOL result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long ICameraObj::GetWhitebalanceV()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ICameraObj::SetWhitebalanceV(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL ICameraObj::GetWhitebalanceVOnePush()
{
	BOOL result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void ICameraObj::SetWhitebalanceVOnePush(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL ICameraObj::GetWhitebalanceVAuto()
{
	BOOL result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void ICameraObj::SetWhitebalanceVAuto(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long ICameraObj::GetWhitebalanceUMin()
{
	long result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICameraObj::GetWhitebalanceUMax()
{
	long result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL ICameraObj::GetWhitebalanceUAutoAvailable()
{
	BOOL result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL ICameraObj::GetWhitebalanceUOnePushAvailable()
{
	BOOL result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long ICameraObj::GetWhitebalanceU()
{
	long result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ICameraObj::SetWhitebalanceU(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL ICameraObj::GetWhitebalanceUOnePush()
{
	BOOL result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void ICameraObj::SetWhitebalanceUOnePush(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL ICameraObj::GetWhitebalanceUAuto()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void ICameraObj::SetWhitebalanceUAuto(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long ICameraObj::GetBrightnessMin()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICameraObj::GetBrightnessMax()
{
	long result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL ICameraObj::GetBrightnessAutoAvailable()
{
	BOOL result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL ICameraObj::GetBrightnessOnePushAvailable()
{
	BOOL result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long ICameraObj::GetBrightness()
{
	long result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ICameraObj::SetBrightness(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL ICameraObj::GetBrightnessOnePush()
{
	BOOL result;
	InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void ICameraObj::SetBrightnessOnePush(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL ICameraObj::GetBrightnessAuto()
{
	BOOL result;
	InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void ICameraObj::SetBrightnessAuto(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long ICameraObj::GetExposureMin()
{
	long result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICameraObj::GetExposureMax()
{
	long result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL ICameraObj::GetExposureAutoAvailable()
{
	BOOL result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL ICameraObj::GetExposureOnePushAvailable()
{
	BOOL result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long ICameraObj::GetExposure()
{
	long result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ICameraObj::SetExposure(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x22, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL ICameraObj::GetExposureOnePush()
{
	BOOL result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void ICameraObj::SetExposureOnePush(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL ICameraObj::GetExposureAuto()
{
	BOOL result;
	InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void ICameraObj::SetExposureAuto(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x24, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long ICameraObj::GetTestImageAvailable()
{
	long result;
	InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICameraObj::GetTestImage()
{
	long result;
	InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ICameraObj::SetTestImage(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x26, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString ICameraObj::GetVendor()
{
	CString result;
	InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ICameraObj::GetModel()
{
	CString result;
	InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString ICameraObj::GetDriver()
{
	CString result;
	InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long ICameraObj::GetSerialNumber()
{
	long result;
	InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long ICameraObj::GetTimeBase()
{
	long result;
	InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void ICameraObj::SetTimeBase(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void ICameraObj::SetValue(long address, long value)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 address, value);
}

long ICameraObj::GetValue(long address)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		address);
	return result;
}
