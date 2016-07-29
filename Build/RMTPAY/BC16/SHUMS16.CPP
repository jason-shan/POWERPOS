
#include <stdio.h>
#include <windows.h>
#include "wownt16.h"

extern DWORD ghLib;
extern DWORD grLib;

#define wincall far pascal _export

extern "C" {
  short wincall unionbank(long trantype,long amount,void * response);
  short wincall remotePay(void * request, void * response);
}

short wincall unionbank(long trantype,long amount,void * response)
{
//    {FILE * f=fopen("c:\\sh.txt","a+t");
//    fprintf(f,"unionbank in 16, trantype=%ld\n",trantype);
//    fclose(f);}
    FARPROC fp=(FARPROC)GetProcAddress32W(ghLib,"W32_UnionBank");
    if (fp==0) {
	MessageBox(0,"Cannot find W32_UnionBank","Error",0);
	return -1;
	}
    short ret=CallProcEx32W(3|CPEX_DEST_STDCALL,0x4,(DWORD)fp,
	(DWORD)trantype,(DWORD)amount,(DWORD)response);
//    {FILE * f=fopen("c:\\sh.txt","a+t");
//    fprintf(f,"unionbank out 16\n");
//    fclose(f);}
    return ret;
}

short wincall remotePay(void * request, void * response)
{
    if (!request)
    {
    	return grLib?-1:0;
    }
    if (!grLib) {
	MessageBox(0,"Cannot load RMTPAY32.DLL","Error",0);
	return -1;
	}
    FARPROC fp=(FARPROC)GetProcAddress32W(grLib,"W32_RemotePay");
    if (fp==0) {
	MessageBox(0,"Cannot find W32_RemotePay","Error",0);
	return -1;
	}
    short ret=CallProcEx32W(2|CPEX_DEST_STDCALL,0x3,(DWORD)fp,
	(DWORD)request,(DWORD)response);
    return ret;
}
