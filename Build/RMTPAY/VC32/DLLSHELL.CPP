// Borland C++ - (C) Copyright 1991, 1992 by Borland International

// Example program used to demonstrate DLL's. This file one of the
// files used to build BITMAP.DLL which is used in the DLLDEMO program.

#include <windows.h>
#include <stdio.h>
#include "rmtpay32.h"

HINSTANCE hInst=NULL;
HGLOBAL hUp=NULL,hDown=NULL;
struct strTransUp * pUp=NULL;
struct strTransDown * pDown=NULL;
PFN_lpay lpay=NULL;

void freeLib()
{
	if (hInst)
	{
		FreeLibrary(hInst); hInst=NULL;
	}
}

void donePara()
{
	if (hUp)
	{
		GlobalUnlock(hUp); GlobalFree(hUp); hUp=NULL;
	}
	if (hDown)
	{
		GlobalUnlock(hDown); GlobalFree(hDown); hDown=NULL;
	}
	pUp=NULL; pDown=NULL;
}

int loadLib(BOOL showMsg)
{
	hInst=LoadLibrary("silkcloud.airport.dll");
	if (hInst)
	{
		lpay = (PFN_lpay)GetProcAddress(hInst, "pay");
		if (lpay==NULL)
		{
			if (showMsg) MessageBox(NULL,"无法获取pay","",NULL);
			return 0;
		}
	}
	else
	{
		if (showMsg) MessageBox(NULL,"无法打开silkcloud.airport.dll","",NULL);
		return 0;
	}
	return -1;
}

int initPara()
{
	if (loadLib(TRUE)==0) return 0;
	freeLib();
	hUp=GlobalAlloc(GPTR+GMEM_SHARE,sizeof(struct strTransUp));
	hDown=GlobalAlloc(GPTR+GMEM_SHARE,sizeof(struct strTransDown));
	if (hUp==NULL||hDown==NULL)
	{
		MessageBox(NULL,"内存分配失败","",NULL);
		return 0;
	}
	pUp=(struct strTransUp *)GlobalLock(hUp); 
	pDown=(struct strTransDown *)GlobalLock(hDown);
	if (pUp==NULL||pDown==NULL)
	{
		MessageBox(NULL,"内存地址分配失败","",NULL);
		return 0;
	}
	return -1;
}

//int FAR PASCAL LibMain(HINSTANCE, WORD, WORD wHeapSize, LPSTR){
BOOL APIENTRY DllMain(HINSTANCE hModule, 
                      DWORD  ul_reason_for_call, 
                      LPVOID lpReserved)
{
    switch( ul_reason_for_call ) {
    case DLL_PROCESS_ATTACH:
		if (initPara()==0) 
		{
			donePara();
			return 0;
		}
		break;
//    case DLL_THREAD_ATTACH:
//		MessageBox(0,"OK2","OK1",0); break;
//    case DLL_THREAD_DETACH:
//		MessageBox(0,"OK3","OK1",0); break;
    case DLL_PROCESS_DETACH:
		donePara();
		break;
    }
    return TRUE;
}
