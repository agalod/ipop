// Von Klassen-Assistent automatisch erstellte IDispatch-Kapselungsklasse(n). 
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse _IAVTFormatPageEvents 

class _IAVTFormatPageEvents : public COleDispatchDriver
{
public:
	_IAVTFormatPageEvents() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	_IAVTFormatPageEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_IAVTFormatPageEvents(const _IAVTFormatPageEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
};
/////////////////////////////////////////////////////////////////////////////
// Wrapper-Klasse IAVTFormatPage 

class IAVTFormatPage : public COleDispatchDriver
{
public:
	IAVTFormatPage() {}		// Ruft den Standardkonstruktor für COleDispatchDriver auf
	IAVTFormatPage(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAVTFormatPage(const IAVTFormatPage& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attribute
public:

// Operationen
public:
	void SetICamera(LPUNKNOWN newValue);
	void SetIStream(LPUNKNOWN newValue);
	void Init();
};
