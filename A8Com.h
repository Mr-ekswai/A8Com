
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <dbt.h>
#include <string.h>
#include <commctrl.h>
#include "resource.h"

#pragma warning(disable:4996)

#define bool int
#define true 1
#define false 0

extern HWND hMainWnd;
extern HANDLE hCom;
extern bool portOpened;
extern bool dispHex;
extern bool sendHex;
extern bool sendNewline;

void InitComm(HWND hMainWnd);
HANDLE OpenComPort(HWND hMainWnd);
DWORD WINAPI ReadCom(LPVOID lpParam);
void ClosePort(void);
void InitReadWrite(void);
void DeInitReadWrite(void);
void ClearReadWrite(void);
int WriteComm(void);
void SaveData(void);
void ChangeDisplay(void);
char* GetStrByID(int id);
void EnablePortWindow(bool enable);
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK DlgFunc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

