/***************************************************************************
  FILE NAME:       PXCDD.H
  TARGET PLATFORM: Windows 95 32-bit  and Windows NT                         
                                                                          
  Copyright (c) ImageNation Corporation 1998
 ***************************************************************************/

#ifndef __INCLUDED_PXCDD_H
#define __INCLUDED_PXCDD_H

#include <windows.h>
#include <ddraw.h>
#include "frame.h"

typedef struct tagPXCDD {
  long pad1;
  long pad2;
  FRAME __PX_FAR *(__PX_CALL *CreateSurface)(short dx, short dy);
  LPDIRECTDRAWSURFACE (__PX_CALL *GetDDSurface)(FRAME __PX_FAR *f);
  long (__PX_CALL *LoadOverlay)(FRAME __PX_FAR *ovr,long trans);
  short (__PX_CALL *UnloadOverlay)(long ovrh);
  short (__PX_CALL *EnableOverlay)(FRAME __PX_FAR *frh,long ovr,short x,
          short y,short enable);
  short (__PX_CALL *EnableFastDisplay)(HWND hwnd,FRAME __PX_FAR *frh,
          long fgh,short enable);
  short (__PX_CALL *GetError)(void);
  short (__PX_CALL *GetBitDepth)(void);
  short (__PX_CALL *MoveOverlay)(long ovr0,short x,short y);  
  int (__PX_CALL *GetRenderCount)(void);  
  void (__PX_CALL *Display)(HWND hwnd,FRAME __PX_FAR *f);
  LPDIRECTDRAWSURFACE (__PX_CALL *GetOverlaySurface)(long ovr);
  short (__PX_CALL *MoveSurface)(FRAME __PX_FAR *f,short x,short y);
} PXCDD;

#ifdef  __cplusplus
extern "C" {
#endif

short imagenation_OpenLibrary(char __PX_FAR *file,
      void __PX_FAR *iface,short count);
void imagenation_CloseLibrary(void __PX_FAR *iface);

#ifdef  __cplusplus
  }
#endif

/* ERROR MESSAGES */
#define FUNCTION_SUCCESS         0
#define ERR_NO_DIRECTDRAW        1
#define ERR_VIDEO_MEM            2
#define ERR_SYSTEM_MEM            4
#define ERR_INVALID_PARAMETER  8
#define ERR_NOT_DD_FRAME        16
#define ERR_WRONG_BIT_DEPTH    32
#define ERR_ACTIVE_FRAME         64
#define ERR_WINDOW_ATTACHED   128
#define ERR_FRAME_ATTACHED       256
#define ERR_OVERLAY_ATTACHED  512
#define ERR_DISPLAY_INACTIVE    1024

#endif
