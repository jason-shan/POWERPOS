#include <windows.h>
#include "wownt16.h"

DWORD ghLib=0;
DWORD grLib=0;

//int FAR PASCAL LibMain(HINSTANCE, WORD, WORD wHeapSize, LPSTR){
int CALLBACK LibMain( HINSTANCE , WORD ,WORD wHeapSize, LPSTR ){
    if ( wHeapSize != 0 )
       UnlockData( 0 );
    ghLib=LoadLibraryEx32W("SHUMS32.DLL",NULL,0);
    if (ghLib==0) ghLib=LoadLibraryEx32W("SAND32.DLL",NULL,0);
    if (ghLib==0) {
	MessageBox(0,"Cannot open SHUMS32.DLL or SAND32.DLL","Error",0);
	return 0;
	}
    grLib=LoadLibraryEx32W("RMTPAY32.DLL",NULL,0);
    return 1;
}

short CALLBACK WEP (short){
    return 1;
}

class dllStartEnd{
public:
  dllStartEnd();
  ~dllStartEnd();
}se;

dllStartEnd::dllStartEnd(){
}

dllStartEnd::~dllStartEnd(){
    if (ghLib) FreeLibrary32W(ghLib); ghLib=0;
    if (grLib) FreeLibrary32W(grLib); grLib=0;
}

