
#include "A8Com.h"

#define LOOP_BUFFER_SIZE 10000
#define LOOP_BUFFER_WINDOW_SIZE 1000
static char* loopBuf;
static char* loopBufText;
static char* loopBufHex;
static int binarypos;
static int textPos;
static int hexPos;

void InitReadWrite(void)
{ 
    loopBuf=(char*)malloc(LOOP_BUFFER_SIZE);
    loopBufText =(char*)malloc(LOOP_BUFFER_SIZE);
    loopBufHex= (char*)malloc(3*LOOP_BUFFER_SIZE);
    *loopBuf=0;
    *loopBufText=0;
    *loopBufHex=0;
}

void ClearReadWrite(void)
{
	binarypos=0;
	textPos=0;
	hexPos=0;
	*loopBuf=0;
	*loopBufText=0;
	*loopBufHex=0;
	if(dispHex)
		SetDlgItemText(hMainWnd,IDC_REVEDIT,loopBufHex);
	else
		SetDlgItemText(hMainWnd,IDC_REVEDIT,loopBufText);
}

DWORD WINAPI ReadCom(LPVOID lpParam)
{
    int i;
	COMMTIMEOUTS timeOut;
	DWORD byteToRead,byteRead;
	int result;
	byteToRead=128;
	timeOut.ReadIntervalTimeout=0;
	timeOut.ReadTotalTimeoutConstant=100;
	timeOut.ReadTotalTimeoutMultiplier=0;
	SetCommTimeouts(hCom,&timeOut);

    while(1)
    {
        if(!portOpened)
            return 0;

        result=ReadFile(hCom, loopBuf+binarypos, byteToRead, &byteRead, NULL);
		if(result<=0)
		{
			portOpened=false;
			ClosePort();
			EnablePortWindow(true);
		}
        if(byteRead>0)
        {
            for(i=0;i<(int)byteRead;i++)
            {
                if(*(loopBuf+binarypos+i)!=0)
                {
                    *(loopBufText+textPos)=*(loopBuf+binarypos+i);
					if((textPos>0)&&(*(loopBufText+textPos-1)!='\r')&&(*(loopBufText+textPos)=='\n'))
					{
						*(loopBufText+textPos)='\r';
						*(loopBufText+textPos+1)='\n';
                        textPos+=2;
					}
					else
					{
                        textPos++;
					}
                }
            }
            
            for(i=0;i<(int)byteRead;i++)
            {
                sprintf(loopBufHex+hexPos,"%02X ",(unsigned char)*(loopBuf+binarypos+i));
                hexPos+=3;
            }

            binarypos+=byteRead;            

            if(binarypos>(LOOP_BUFFER_SIZE-LOOP_BUFFER_WINDOW_SIZE))
            {
                memcpy(loopBuf,loopBuf+LOOP_BUFFER_WINDOW_SIZE,LOOP_BUFFER_SIZE-LOOP_BUFFER_WINDOW_SIZE);

                binarypos-=LOOP_BUFFER_WINDOW_SIZE;

                textPos=0;
                for(i=0;i<(int)binarypos;i++)
                {                    
                    if(*(loopBuf+i)!=0)
                    {
                        *(loopBufText+textPos)=*(loopBuf+i);
                        textPos++;
                    }
                }
                
                hexPos=0;
                for(i=0;i<(int)binarypos;i++)
                {
                    sprintf(loopBufHex+hexPos,"%02X ",(unsigned char)*(loopBuf+i));
                    hexPos+=3;
                }
            }

            *(loopBuf+binarypos)=0;
            *(loopBufText+textPos)=0;
            *(loopBufHex+hexPos)=0;

            if(dispHex)
                SetDlgItemText(hMainWnd,IDC_REVEDIT,loopBufHex);
            else
                SetDlgItemText(hMainWnd,IDC_REVEDIT,loopBufText);
            
            SendMessage(GetDlgItem(hMainWnd,IDC_REVEDIT),EM_LINESCROLL,0,SendMessage(GetDlgItem(hMainWnd,IDC_REVEDIT),EM_GETLINECOUNT,0,0));
        }
    }
	return 0;
}

void ChangeDisplay(void)
{
    if(dispHex)
        SetDlgItemText(hMainWnd,IDC_REVEDIT,loopBufHex);
    else
        SetDlgItemText(hMainWnd,IDC_REVEDIT,loopBufText);
}

int Hex2Bin(char* bin, char* hex){
	unsigned char* pHex;
	unsigned char* pBin;
	unsigned char byte;
	unsigned char highByte;
	unsigned char lowByte;
	bool pingpang;
	bool validData;

	pHex=(unsigned char*)hex;
	pBin=(unsigned char*)bin;

	pingpang=true;
	while(1)
	{
	    validData=false;
		if((*pHex>='0')&&(*pHex<='9')){
			pingpang?(highByte=*pHex-'0'):(lowByte=*pHex-'0');
			validData=true;
		}else if((*pHex>='A')&&(*pHex<='F')){
			pingpang?(highByte=*pHex-'A'+10):(lowByte=*pHex-'A'+10);
			validData=true;
		}else if((*pHex>='a')&&(*pHex<='f')){
			pingpang?(highByte=*pHex-'a'+10):(lowByte=*pHex-'a'+10);
			validData=true;
		}else if(*pHex<=32){ //no printable control chars
			if(*pHex==0){
				if(pingpang){
					*pBin=0;
				    return (int)((char*)pBin-bin);
				}
				else{
					return -1;
				}
			}
		}else{
			return -1;
		}
		if((!pingpang)&&validData){
			highByte=highByte<<4;
			byte=highByte+lowByte;
			*(pBin++)=byte;
		}
		if(validData)
		    pingpang=!pingpang;
		pHex++;
	}
}


int WriteComm(void)
{
    DWORD byteWritten;
    int len;
    static char str[102400];
    static char hexStr[102400];
    GetDlgItemText(hMainWnd,IDC_SENDEDIT,str,1000);
	len=0;
	if(sendHex)
	{		
		len=Hex2Bin(hexStr, str);
		if(len<0)
		{
			return -1;
		}
		if(len>0)
		    WriteFile(hCom, hexStr, len,&byteWritten, NULL);
	}
	else
	{
		len=(int)strlen(str);
		if(sendNewline)
		{
			str[len]=0xd;
			str[len+1]=0xa;
			str[len+2]=0;
		}
		if(strlen(str)>0)
		    WriteFile(hCom, str, (DWORD)strlen(str),&byteWritten, NULL);
	}
	return 1;
}
void DeInitReadWrite(void)
{
    free(loopBuf);
    free(loopBufText);
    free(loopBufHex);
}

void SaveData(void)
{
    DWORD byteWritten;
    HANDLE hFile;
	char saveFileName[1024];
	OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hMainWnd;
    ofn.lpstrFile = saveFileName;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(saveFileName);
    ofn.lpstrFilter = "All(*.*)\0*.*\0Hex(*.hex)\0*.hex\0Bin(*.bin)\0*.bin\0A8(*.a8)\0*.a8\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |OFN_OVERWRITEPROMPT;

    if (GetSaveFileName(&ofn)==TRUE) 
	{
        hFile = CreateFile(saveFileName,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
        WriteFile(hFile, loopBuf, binarypos,&byteWritten, NULL);
        CloseHandle(hFile);
	}
}