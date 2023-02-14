
#include "A8Com.h"

static HINSTANCE hInst;

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow)
{
    hInst = hInstance;
    InitReadWrite();
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DlgFunc);
    DeInitReadWrite();
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void InitPortList(void)
{
    HKEY hKey;
    char Name[25];
    char portName[80];
    LONG status;
    DWORD index = 0;
    DWORD name;
    DWORD sizeofPortName;
    DWORD type;

    LPCTSTR data_Set = "HARDWARE\\DEVICEMAP\\SERIALCOMM\\";
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
    {
        return;
    }
    SendMessage(GetDlgItem(hMainWnd, IDC_COMPORT), (UINT)CB_RESETCONTENT, (UINT)NULL, (LPARAM)portName);
    do
    {
        name = sizeof(Name);
        sizeofPortName = sizeof(portName);
        status = RegEnumValue(hKey, index, Name, &name, NULL, &type, (unsigned char*)portName, &sizeofPortName);
        index++;
        if ((status == ERROR_SUCCESS) || (status == ERROR_MORE_DATA))
        {
            SendMessage(GetDlgItem(hMainWnd, IDC_COMPORT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)portName);
        }
    } while ((status == ERROR_SUCCESS) || (status == ERROR_MORE_DATA));
    SendMessage(GetDlgItem(hMainWnd, IDC_COMPORT), (UINT)CB_SELECTSTRING, (UINT)NULL, (LPARAM)portName);
    RegCloseKey(hKey);
}

char* GetStrByID(int id)
{
    static char str[256];
    LoadString(hInst, id, str, 255);
    return str;
}

void GoForHelp(void)
{
    if (!strcmp(GetStrByID(IDS_LANG), "english"))
        ShellExecute(0, NULL, "http://www.a8blog.com/en_uart_rs232_debug.htm", NULL, NULL, SW_NORMAL);
    else if (!strcmp(GetStrByID(IDS_LANG), "chinese"))
        ShellExecute(0, NULL, "http://www.a8blog.com/uart_rs232_debug.htm", NULL, NULL, SW_NORMAL);
    else
        ShellExecute(0, NULL, "http://www.a8blog.com", NULL, NULL, SW_NORMAL);
}

void EnablePortWindow(bool enable)
{
    if(enable)
        SetDlgItemText(hMainWnd, IDC_OPENCOM, GetStrByID(IDS_OPEN_PORT));
    else
        SetDlgItemText(hMainWnd, IDC_OPENCOM, GetStrByID(IDS_CLOSE_PORT));
    EnableWindow(GetDlgItem(hMainWnd, IDC_COMPORT), enable);
    EnableWindow(GetDlgItem(hMainWnd, IDC_BAUDRATE), enable);
    EnableWindow(GetDlgItem(hMainWnd, IDC_STOPBIT), enable);
    EnableWindow(GetDlgItem(hMainWnd, IDC_DATABIT), enable);
    EnableWindow(GetDlgItem(hMainWnd, IDC_PARITYBIT), enable);
}

INT_PTR CALLBACK DlgFunc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HANDLE hCom;
    char portName[8] = "com";
    DWORD threadIDRead;
    HCURSOR hCursor;
    int xPos, yPos;
    RECT rc;
    static int timerOn = 0;

    hMainWnd = hwnd;
    switch (msg)
    {
    case WM_INITDIALOG:
        hMainWnd = hwnd;
        InitComm(hwnd);
        InitPortList();
        SetDlgItemText(hwnd, IDC_OPENCOM, GetStrByID(IDS_OPEN_PORT));
        SetDlgItemText(hwnd, IDC_CLEARWINDOW, GetStrByID(IDS_CLEAR_DATA));
        SetDlgItemText(hwnd, IDC_SAVEWINDOW, GetStrByID(IDS_SAVE_DATA));
        SetDlgItemText(hwnd, IDC_TIMERSEND, GetStrByID(IDS_AUTO_SEND));
        SetDlgItemText(hwnd, IDC_STATIC_MS, GetStrByID(IDS_SEND_PERIAD));
        SetDlgItemText(hwnd, IDC_SENDNEWLINE, GetStrByID(IDS_SEND_NEW_LINE));
        SetDlgItemText(hwnd, IDC_SENDHEX, GetStrByID(IDS_HEX_SEND));
        SetDlgItemText(hwnd, IDC_SEND, GetStrByID(IDS_SEND));
        SetDlgItemText(hwnd, IDC_DISPLAYHEX, GetStrByID(IDS_HEX_DISPLAY));
        SetDlgItemText(hwnd, IDC_STATIC_PORT_NUM, GetStrByID(IDS_PORT_NUMBER));
        SetDlgItemText(hwnd, IDC_STATIC_BAUD_RATE, GetStrByID(IDS_BAUD_RATE));
        SetDlgItemText(hwnd, IDC_STATIC_BYTE_BITS, GetStrByID(IDS_BYTE_SIZE));
        SetDlgItemText(hwnd, IDC_STATIC_STOP_BITS, GetStrByID(IDS_STOP_BITS));
        SetDlgItemText(hwnd, IDC_STATIC_PARITY, GetStrByID(IDS_PARITY));
        SetDlgItemText(hwnd, IDC_STATIC_PORT_SETTING, GetStrByID(IDS_PORT_SETTINGS));
        SetDlgItemText(hwnd, IDC_BUTTON_HELP, GetStrByID(IDS_HELP));
        SetDlgItemText(hwnd, IDC_BUTTON_ABOUT, GetStrByID(IDS_ABOUT));
        SetDlgItemText(hwnd, IDC_STATIC_HELP, GetStrByID(IDS_HELP_DISCUSS));
        SetDlgItemText(hwnd, IDC_STATIC_DOMAIN, GetStrByID(IDS_A8BLOG_COM));
        SetWindowText(hwnd, GetStrByID(IDS_APP_NAME));
        SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_RESETCONTENT, (UINT)NULL, (LPARAM)0);
        SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)GetStrByID(IDS_PARITY_NONE));
        SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)GetStrByID(IDS_PARITY_ODD));
        SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)GetStrByID(IDS_PARITY_EVEN));
        SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)GetStrByID(IDS_PARITY_MARK));
        SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_ADDSTRING, (UINT)NULL, (LPARAM)GetStrByID(IDS_PARITY_SPACE));
        SendMessage(GetDlgItem(hMainWnd, IDC_PARITYBIT), (UINT)CB_SELECTSTRING, (UINT)NULL, (LPARAM)GetStrByID(IDS_PARITY_NONE));
        break;

    case WM_TIMER:
        PostMessage(hwnd, WM_COMMAND, IDC_SEND, 0);
        break;

    case WM_MOUSEMOVE:
        xPos = GET_X_LPARAM(lParam);
        yPos = GET_Y_LPARAM(lParam);
        GetWindowRect(hwnd, &rc);
        if ((xPos > (rc.right - rc.left - 280)) && (yPos > (rc.bottom - rc.top - 150)))
        {
            hCursor = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR));
            SetCursor(hCursor);
        }
        break;

    case WM_LBUTTONDOWN:
        xPos = GET_X_LPARAM(lParam);
        yPos = GET_Y_LPARAM(lParam);
        GetWindowRect(hwnd, &rc);
        if ((xPos > (rc.right - rc.left - 280)) && (yPos > (rc.bottom - rc.top - 150)))
        {
            GoForHelp();
        }

    case WM_DEVICECHANGE:
        if (portOpened)
            break;
        switch (wParam)
        {

        case DBT_DEVICEARRIVAL:
            InitPortList();
            break;

        case DBT_DEVICEREMOVECOMPLETE:
            InitPortList();
            break;

        default:
            break;
        }
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_DISPLAYHEX:
            if (IsDlgButtonChecked(hwnd, IDC_DISPLAYHEX))
                dispHex = true;
            else
                dispHex = false;
            ChangeDisplay();
            break;

        case IDC_SENDHEX:
            if (IsDlgButtonChecked(hwnd, IDC_SENDHEX))
                sendHex = true;
            else
                sendHex = false;
            break;

        case IDC_SENDNEWLINE:
            if (IsDlgButtonChecked(hwnd, IDC_SENDNEWLINE))
                sendNewline = true;
            else
                sendNewline = false;
            break;
        case IDC_SAVEWINDOW:
            SaveData();
            break;

        case IDC_CLEARWINDOW:
            ClearReadWrite();
            break;

        case IDC_TIMERSEND:
            if (IsDlgButtonChecked(hwnd, IDC_TIMERSEND))
            {
                if (GetDlgItemInt(hwnd, IDC_EDIT_TIMER, 0, 0) == 0)
                {
                    MessageBox(hwnd, GetStrByID(IDS_SET_CORR_TIME), GetStrByID(IDS_ERROR_FOUND), MB_ICONERROR);
                    CheckDlgButton(hwnd, IDC_TIMERSEND, BST_UNCHECKED);
                }
                else
                {
                    SetTimer(hwnd, 1, GetDlgItemInt(hwnd, IDC_EDIT_TIMER, 0, 0), NULL);
                    timerOn = 1;
                }
            }
            else
            {
                KillTimer(hwnd, 1);
                timerOn = 0;
            }
            break;

        case IDC_SEND:
            if (portOpened)
            {
                if (WriteComm() < 0)
                {
                    if (timerOn)
                    {
                        CheckDlgButton(hwnd, IDC_TIMERSEND, BST_UNCHECKED);
                        KillTimer(hwnd, 1);
                    }
                    MessageBox(hwnd, GetStrByID(IDS_HEX_ERROR), GetStrByID(IDS_ERROR_FOUND), MB_OK);
                }
            }
            break;

        case IDC_BUTTON_HELP:
            GoForHelp();
            break;

        case IDC_BUTTON_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
            break;

        case IDC_OPENCOM:
            if (!portOpened)
            {
                hCom = OpenComPort(hwnd);
                if (hCom)
                {
                    portOpened = true;
                    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReadCom,
                        0, 0, (LPDWORD)&threadIDRead);
                    EnablePortWindow(false);
                }
            }
            else
            {
                portOpened = false;
                ClosePort();
                EnablePortWindow(true);
            }
            break;

        case IDCANCEL:
            EndDialog(hwnd, FALSE);
            break;

        default:
            break;
        }

        break;
    }
    return FALSE;
}
