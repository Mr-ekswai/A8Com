
#include "A8Com.h"

void InitComm(HWND hMainWnd)
{
	SendMessage(GetDlgItem(hMainWnd, IDC_DATABIT), (UINT)CB_RESETCONTENT, (UINT)NULL, (LPARAM)0);
	SendMessage(GetDlgItem(hMainWnd, IDC_DATABIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"5");
	SendMessage(GetDlgItem(hMainWnd, IDC_DATABIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"6");
	SendMessage(GetDlgItem(hMainWnd, IDC_DATABIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"7");
	SendMessage(GetDlgItem(hMainWnd, IDC_DATABIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"8");
	SendMessage(GetDlgItem(hMainWnd, IDC_DATABIT), (UINT)CB_SELECTSTRING, (UINT)NULL, (LPARAM)"8");

	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_RESETCONTENT, (UINT)NULL, (LPARAM)0);
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"110");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"300");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"600");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"1200");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"2400");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"4800");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"9600");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"14400");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"19200");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"38400");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"56000");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"57600");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"115200");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"128000");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"256000");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"230400");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"460800");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"921600");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"1228800");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"2457600");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"3000000");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"3686400");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"6000000");
	SendMessage(GetDlgItem(hMainWnd, IDC_BAUDRATE), (UINT)CB_SELECTSTRING, (UINT)NULL, (LPARAM)"115200");

	SendMessage(GetDlgItem(hMainWnd, IDC_STOPBIT), (UINT)CB_RESETCONTENT, (UINT)NULL, (LPARAM)0);
	SendMessage(GetDlgItem(hMainWnd, IDC_STOPBIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"1.5");
	SendMessage(GetDlgItem(hMainWnd, IDC_STOPBIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"1");
	SendMessage(GetDlgItem(hMainWnd, IDC_STOPBIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)"2");
	SendMessage(GetDlgItem(hMainWnd, IDC_STOPBIT), (UINT)CB_SELECTSTRING, (UINT)NULL, (LPARAM)"1");

	SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_RESETCONTENT, (UINT)NULL, (LPARAM)0);
	SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)GetStrByID(IDS_PARITY_NONE));
	SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)GetStrByID(IDS_PARITY_ODD));
	SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)GetStrByID(IDS_PARITY_EVEN));
	SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)GetStrByID(IDS_PARITY_MARK));
	SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)GetStrByID(IDS_PARITY_SPACE));
	SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_SELECTSTRING, (UINT)NULL, (LPARAM)GetStrByID(IDS_PARITY_NONE));

	SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_RESETCONTENT, (UINT)NULL, (LPARAM)0);
	SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)GetStrByID(IDS_PARITY_NONE));
	SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)GetStrByID(IDS_PARITY_ODD));
	SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)GetStrByID(IDS_PARITY_EVEN));
	SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)GetStrByID(IDS_PARITY_MARK));
	SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)GetStrByID(IDS_PARITY_SPACE));
	SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_SELECTSTRING, (UINT)NULL, (LPARAM)GetStrByID(IDS_PARITY_NONE));
}


HANDLE OpenComPort(HWND hMainWnd)
{
   DCB dcb;
   bool bSuccess;
   char buf[128];
   char name[256];
   char fileName[256];
   DWORD errorCode;

   GetDlgItemText(hMainWnd,IDC_COMPORT,name,30);
   sprintf(fileName,"\\\\.\\%s",name);
   hCom = CreateFile( fileName,
                    GENERIC_READ | GENERIC_WRITE,
                    0,
                    NULL,
                    OPEN_EXISTING,
                    0,
                    NULL
                    );

   if (hCom == INVALID_HANDLE_VALUE) 
   {
       errorCode=GetLastError();
       MessageBox(hMainWnd,GetStrByID(IDS_OPEN_PORT_ERROR),GetStrByID(IDS_ERROR_FOUND),MB_ICONERROR);
       return 0;
   }

   bSuccess = GetCommState(hCom, &dcb);

   if (!bSuccess) 
   {
      MessageBox(hMainWnd,GetStrByID(IDS_PORT_STATE_ERROR),GetStrByID(IDS_ERROR_FOUND),MB_ICONERROR);
      CloseHandle(hCom);
      return 0;
   }

   GetDlgItemText(hMainWnd,IDC_BAUDRATE,buf,30);
   dcb.BaudRate = atoi(buf);

   GetDlgItemText(hMainWnd,IDC_DATABIT,buf,30);
   dcb.ByteSize = atoi(buf);

   GetDlgItemText(hMainWnd,IDC_PARITYBIT,buf,30);
   if(!strcmp(buf,GetStrByID(IDS_PARITY_NONE)))   
	   dcb.Parity = NOPARITY;
   if(!strcmp(buf,GetStrByID(IDS_PARITY_ODD)))   
	   dcb.Parity = ODDPARITY;
   if(!strcmp(buf,GetStrByID(IDS_PARITY_EVEN)))   
	   dcb.Parity = EVENPARITY;
   if(!strcmp(buf,GetStrByID(IDS_PARITY_MARK)))   
	   dcb.Parity = MARKPARITY;
   if(!strcmp(buf,GetStrByID(IDS_PARITY_SPACE)))   
	   dcb.Parity = SPACEPARITY;

   GetDlgItemText(hMainWnd,IDC_STOPBIT,buf,30);
   if(!strcmp(buf,"1"))  
	   dcb.StopBits = ONESTOPBIT;
   if(!strcmp(buf,"1.5"))  
	   dcb.StopBits = ONE5STOPBITS;
   if(!strcmp(buf,"2"))  
	   dcb.StopBits = TWOSTOPBITS;

   bSuccess = SetCommState(hCom, &dcb);

   if (!bSuccess) 
   {
      MessageBox(hMainWnd,GetStrByID(IDS_SET_COM_ERR),GetStrByID(IDS_ERROR_FOUND),MB_ICONERROR);
      CloseHandle(hCom);
      return 0;
   }
   return hCom;
}

void ClosePort(void)
{
    CloseHandle(hCom);
}