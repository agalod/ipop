// Von Klassen-Assistent automatisch erstellte IDispatch-Kapselungsklasse(n). 
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _ICameraViewEvents 

class _ICameraViewEvents : public COleDispatchDriver
{
public:
	_ICameraViewEvents() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_ICameraViewEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_ICameraViewEvents(const _ICameraViewEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse ICameraView 

class ICameraView : public COleDispatchDriver
{
public:
	ICameraView() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	ICameraView(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ICameraView(const ICameraView& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	void SetGain(long gain);
	long GetGain();
	long GetGainMin();
	long GetGainMax();
	void Wait(long milli);
	void StatusText(LPCTSTR test);
	void StartCapture();
	void StopCapture();
	void FullSize();
	void HalfSize();
	void QuarterSize();
	long CameraProperties();
	long FormatProperties();
	void FullMainWindow();
	void NormalMainWindow();
	void SaveBitmap(LPCTSTR fileName);
	void TakeBitmap();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _ICMainFrmObjEvents 

class _ICMainFrmObjEvents : public COleDispatchDriver
{
public:
	_ICMainFrmObjEvents() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_ICMainFrmObjEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_ICMainFrmObjEvents(const _ICMainFrmObjEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse ICMainFrmObj 

class ICMainFrmObj : public COleDispatchDriver
{
public:
	ICMainFrmObj() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	ICMainFrmObj(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ICMainFrmObj(const ICMainFrmObj& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	void PaintStatusText(LPCTSTR text);
	void ShowNormal();
	void ShowMaximized();
	void ShowMinimized();
	LPDISPATCH GetCameraNames();
	LPDISPATCH GetFriendlyNames();
	LPDISPATCH ShowDeviceDialog();
	LPDISPATCH OpenCamera(long camera, long view);
	void Cascade();
	void Tile(BOOL horizontal);
	LPDISPATCH GetActive();
	LPDISPATCH GetViewNames();
	long GetIndexForName(LPCTSTR name);
	long GetIndexForFriendlyName(LPCTSTR friendlyName);
	long GetIndexForView(LPCTSTR view);
	void Sleep(long milliSeconds);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse INameArray 

class INameArray : public COleDispatchDriver
{
public:
	INameArray() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	INameArray(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	INameArray(const INameArray& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPUNKNOWN Get_NewEnum();
	VARIANT GetItem(long index);
	long GetCount();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse IFriendlyNameArray 

class IFriendlyNameArray : public COleDispatchDriver
{
public:
	IFriendlyNameArray() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	IFriendlyNameArray(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IFriendlyNameArray(const IFriendlyNameArray& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPUNKNOWN Get_NewEnum();
	VARIANT GetItem(long index);
	long GetCount();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse INormalChild 

class INormalChild : public COleDispatchDriver
{
public:
	INormalChild() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	INormalChild(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	INormalChild(const INormalChild& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	void Start();
	void Stop();
	void FullSize();
	void HalfSize();
	void QuarterSize();
	void FullScreen();
	long GetXPos();
	void SetXPos(long nNewValue);
	long GetYPos();
	void SetYPos(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetPictureWidth();
	void SetPictureWidth(long nNewValue);
	long GetPictureHeight();
	void SetPictureHeight(long nNewValue);
	void FormatDialog();
	void PropertieDialog();
	void ShowMaximized();
	void ShowMinimized();
	void ShowNormal();
	CString GetCameraName();
	CString GetFriendlyName();
	CString GetViewType();
	LPDISPATCH GetCameraObj();
	void TakePicture();
	void SavePicture(LPCTSTR fileName);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse IViewArray 

class IViewArray : public COleDispatchDriver
{
public:
	IViewArray() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	IViewArray(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IViewArray(const IViewArray& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	LPUNKNOWN Get_NewEnum();
	VARIANT GetItem(long index);
	long GetCount();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse IActivXChild 

class IActivXChild : public COleDispatchDriver
{
public:
	IActivXChild() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	IActivXChild(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IActivXChild(const IActivXChild& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	void Start();
	void Stop();
	void FullSize();
	void HalfSize();
	void QuarterSize();
	void FullScreen();
	long GetXPos();
	void SetXPos(long nNewValue);
	long GetYPos();
	void SetYPos(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	void FormatDialog();
	void PropertieDialog();
	void ShowMaximized();
	void ShowMinimized();
	void ShowNormal();
	CString GetCameraName();
	CString GetFriendlyName();
	CString GetViewType();
	LPDISPATCH GetControl();
	LPDISPATCH GetAVTExtender();
	LPDISPATCH GetCameraObj();
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse IAVTExtender 

class IAVTExtender : public COleDispatchDriver
{
public:
	IAVTExtender() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	IAVTExtender(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAVTExtender(const IAVTExtender& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	CString GetFriendlyCameraName();
	void SetFriendlyCameraName(LPCTSTR lpszNewValue);
	void CameraProperties();
	void FormatProperties();
	void Run();
	void Stop();
	void ActivateMenu(unsigned long hMenu);
	void HandleMenuCommand(unsigned long commandID);
	BOOL IsRunning();
	BOOL IsWritingFile();
	void DeInitialize();
	void GetStandardSize(long* Width, long* Height);
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse ICameraObj 

class ICameraObj : public COleDispatchDriver
{
public:
	ICameraObj() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	ICameraObj(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ICameraObj(const ICameraObj& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	BOOL GetGamma();
	void SetGamma(BOOL bNewValue);
	long GetGainMin();
	long GetGainMax();
	BOOL GetGainAutoAvailable();
	BOOL GetGainOnePushAvailable();
	long GetGain();
	void SetGain(long nNewValue);
	BOOL GetGainOnePush();
	void SetGainOnePush(BOOL bNewValue);
	BOOL GetGainAuto();
	void SetGainAuto(BOOL bNewValue);
	long GetWhitebalanceVMin();
	long GetWhitebalanceVMax();
	BOOL GetWhitebalanceVAutoAvailable();
	BOOL GetWhitebalanceVOnePushAvailable();
	long GetWhitebalanceV();
	void SetWhitebalanceV(long nNewValue);
	BOOL GetWhitebalanceVOnePush();
	void SetWhitebalanceVOnePush(BOOL bNewValue);
	BOOL GetWhitebalanceVAuto();
	void SetWhitebalanceVAuto(BOOL bNewValue);
	long GetWhitebalanceUMin();
	long GetWhitebalanceUMax();
	BOOL GetWhitebalanceUAutoAvailable();
	BOOL GetWhitebalanceUOnePushAvailable();
	long GetWhitebalanceU();
	void SetWhitebalanceU(long nNewValue);
	BOOL GetWhitebalanceUOnePush();
	void SetWhitebalanceUOnePush(BOOL bNewValue);
	BOOL GetWhitebalanceUAuto();
	void SetWhitebalanceUAuto(BOOL bNewValue);
	long GetBrightnessMin();
	long GetBrightnessMax();
	BOOL GetBrightnessAutoAvailable();
	BOOL GetBrightnessOnePushAvailable();
	long GetBrightness();
	void SetBrightness(long nNewValue);
	BOOL GetBrightnessOnePush();
	void SetBrightnessOnePush(BOOL bNewValue);
	BOOL GetBrightnessAuto();
	void SetBrightnessAuto(BOOL bNewValue);
	long GetExposureMin();
	long GetExposureMax();
	BOOL GetExposureAutoAvailable();
	BOOL GetExposureOnePushAvailable();
	long GetExposure();
	void SetExposure(long nNewValue);
	BOOL GetExposureOnePush();
	void SetExposureOnePush(BOOL bNewValue);
	BOOL GetExposureAuto();
	void SetExposureAuto(BOOL bNewValue);
	long GetTestImageAvailable();
	long GetTestImage();
	void SetTestImage(long nNewValue);
	CString GetVendor();
	CString GetModel();
	CString GetDriver();
	long GetSerialNumber();
	long GetTimeBase();
	void SetTimeBase(long nNewValue);
	void SetValue(long address, long value);
	long GetValue(long address);
};
