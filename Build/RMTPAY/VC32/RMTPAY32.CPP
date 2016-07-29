#include <stdio.h>
#include <windows.h>
#include "rmtpay32.h"
#include "inputbox.h"

#pragma pack(push)
#pragma pack(1)
struct ylrequest {
	int TransAmount;
	short trantype;
	char posnumber[4];
	char xsdanjuhao[20];
	char yxsdanjuhao[20];
};

struct ylresponse {
	double	TransAmount;
	char	RejCode[4];
	char	CardNumber[20];
	char	RejCodeExplain[100];
	long	CardType;
};
#pragma pack(pop)

void clearPara(ylresponse * p)
{
	if (pUp) memset(pUp,0,sizeof(struct strTransUp));
	if (pDown) memset(pDown,0,sizeof(struct strTransDown));
	if (p)
	{
		memset(p,0,sizeof(struct ylresponse)); strcpy(p->RejCode,"00");
	}
}

short WINAPI W32_RemotePay_1(void * req,void * resp)
{
	if (lpay==NULL) return -1;
	if (pUp==NULL||pDown==NULL) return -4;
	//char t[100]; 

	InputBox("Test");

	ylresponse * p=(ylresponse*)resp; clearPara(p);
	ylrequest * r=(ylrequest*)req;
	char am[20];

	switch (r->trantype) {
	case 2:		//消费
		memcpy(pUp->eventType,"10",2);
		memset(pUp->posId,0x20,sizeof(pUp->posId));
		memcpy(pUp->posId,r->posnumber,3);
		sprintf(am,"%012ld",r->TransAmount);
		memcpy(pUp->amount,am,12);
		memset(pUp->posOrderId,0x20,sizeof(pUp->posOrderId));
		memcpy(pUp->posOrderId,r->xsdanjuhao,13);
		break;
	case 3:		//退货
		/*
		memcpy(pUp->eventType,"40",2);	//查询
		memset(pUp->posId,0x20,sizeof(pUp->posId));
		memcpy(pUp->posId,r->posnumber,3);
		sprintf(am,"%012ld",1);
		memcpy(pUp->amount,am,12);
		memset(pUp->posOrderId,0x20,sizeof(pUp->posOrderId));
		memcpy(pUp->posOrderId,r->yxsdanjuhao,13);
		lpay((char*)pDown,(char*)pUp);
		if (memcmp(pDown->returnCode,"10",2))		//查询错误
		{
			memcpy(p->RejCode,pDown->returnCode,2);
			memcpy(p->CardNumber,pDown->paymentType,2);
			memcpy(p->RejCodeExplain,pDown->returnMsg,40);
			return 0;
		}
		*/
		memcpy(pUp->eventType,"30",2);	//退货
		memset(pUp->posId,0x20,sizeof(pUp->posId));
		memcpy(pUp->posId,r->posnumber,3);
		sprintf(am,"%012ld",r->TransAmount);
		memcpy(pUp->amount,am,12);
		memset(pUp->posOrderId,0x20,sizeof(pUp->posOrderId));
		memcpy(pUp->posOrderId,r->xsdanjuhao,13);
		//memcpy(pUp->originalExternalOrderId,pDown->externalOrderId,20);
		memset(pUp->originalExternalOrderId,0x20,sizeof(pUp->originalExternalOrderId));
		memcpy(pUp->originalExternalOrderId,r->yxsdanjuhao,13);
		memset(pDown,0,sizeof(struct strTransDown));
		break;
	default:
		return -2;
	}
		//sprintf(t,"参数1长度%d,参数2长度%d",sizeof(strTransDown),sizeof(strTransUp)); MessageBox(NULL,t,"",NULL);
	lpay((char*)pDown,(char*)pUp);
	memcpy(am,pDown->amount,12); am[12]=0;
		//sprintf(t,"amount=%s",am); MessageBox(NULL,t,"",NULL);	
	p->TransAmount=atof(am)/100;
	memcpy(p->RejCode,pDown->returnCode,2);
		//sprintf(t,"RejCode=%s",p->RejCode); MessageBox(NULL,t,"",NULL);	
	memcpy(p->CardNumber,pDown->paymentType,2);
		//sprintf(t,"CardNumber=%s",p->CardNumber); MessageBox(NULL,t,"",NULL);	
	memcpy(p->RejCodeExplain,pDown->returnMsg,40);
		//sprintf(t,"RejCodeExplain=%s",p->RejCodeExplain); MessageBox(NULL,t,"",NULL);	
	p->CardType=90;
		//MessageBox(NULL,"返回","",NULL);
	return 0;
}

short WINAPI W32_RemotePay(void * req,void * resp)
{
	if (loadLib(FALSE)==0) return -1;
	HWND hWnd=GetForegroundWindow(),hWnd1=GetActiveWindow();
	short ret=W32_RemotePay_1(req,resp);
	freeLib();
	SetForegroundWindow(hWnd); SetActiveWindow(hWnd1);
	return ret;
}
