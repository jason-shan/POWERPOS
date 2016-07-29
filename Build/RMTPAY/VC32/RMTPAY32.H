#ifndef __RMTPAY32_H__
#define __RMTPAY32_H__

#pragma pack(push)
#pragma pack(1)
struct strTransUp {
	char eventType[2]; 
	char posId[6]; 
	char amount[12];
	char posOrderId[20];
	char originalExternalOrderId[20];
	char reserved[48];
};

struct strTransDown {
	char eventType[2];
	char paymentType[2];
	char paymentCode[48];
	char returnCode[2];
	char returnMsg[40];
	char posId[6];
	char amount[12];
	char merchantId[6];
	char merchantIp[15];
	char merchantName[40];
	char paymentDate[8];
	char paymentTime[6];
	char externalOrderId[20];
	char posOrderId[20];
	char originalPosOrderId[20];
	char originalExternalOrderId[20];
	char reserved[48];
};
#pragma pack(pop)

extern struct strTransUp * pUp;
extern struct strTransDown * pDown;
typedef int (__cdecl *PFN_lpay)(char * downData, char * upData);
extern PFN_lpay lpay;

int loadLib(BOOL showMsg);
void freeLib();

#endif