#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <objbase.h>
#include <CommCtrl.h>
using namespace std;
#define File_menu_item_new_window   1
#define File_menu_item_Open         2
#define File_menu_item_Save         3
#define File_menu_item_Save_as      4
#define File_menu_item_Save_all     5
#define File_menu_item_page_setup   6
#define File_menu_item_print        7
#define File_menu_item_close_window 8
#define File_menu_item_exit         9


void addMenu(HWND hwnd);
void AddButtons(HWND hwnd);
void fileWrite(wchar_t text[100]);
HWND hwnd_for_text_input;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_WINDOWFRAME;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               544,                 /* The programs width */
               600,                 /* and height in pixels 374*/
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
    case WM_COMMAND:
        switch(wParam)
        {
        case File_menu_item_new_window:
            MessageBeep(MB_OK);
            break;
        case File_menu_item_Open:
            break;
        case File_menu_item_Save:
            wchar_t text[100];
            GetWindowTextW(hwnd_for_text_input,text,100);
            fileWrite(text);
            //SetWindowTextW(hwnd,text);
            break;
        case File_menu_item_Save_as:
            break;
        case File_menu_item_Save_all:
            break;
        case File_menu_item_print:
            break;
        case File_menu_item_close_window:
            break;
        case File_menu_item_exit:
            DestroyWindow(hwnd);
            break;
        }
        break;
    case WM_CREATE:
        POINT point;
        if (GetCursorPos(&point))
        {
            cout << point.x << "," << point.y << "\n";
        }
        addMenu(hwnd);
        AddButtons(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
void fileWrite(wchar_t text[100])
{
    ofstream myfile;
    myfile.open ("example.txt");
    for(int i =0; i < 100; i++)
        myfile << text;
    myfile.close();

};

void addMenu(HWND hwnd)
{

    HMENU hMenu, hFileSubMenu, hEditSubMenu, hViewSubMenu;
    hMenu = CreateMenu();
    hFileSubMenu = CreateMenu();
    hEditSubMenu = CreateMenu();
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hFileSubMenu,"File");
    AppendMenu(hMenu,MF_POPUP, (UINT_PTR)hEditSubMenu,"Edit");
    AppendMenu(hMenu,MF_POPUP, (UINT_PTR)hViewSubMenu,"View");

    //File Sub Menu Items

    AppendMenu(hFileSubMenu,MF_STRING, File_menu_item_new_window,"New Window");
    AppendMenu(hFileSubMenu,MF_STRING, File_menu_item_Open,"Open");
    AppendMenu(hFileSubMenu,MF_STRING, File_menu_item_Save,"Save");
    AppendMenu(hFileSubMenu,MF_STRING, File_menu_item_Save_as,"Save as");
    AppendMenu(hFileSubMenu,MF_STRING, File_menu_item_Save_all,"Save all");
    AppendMenu(hFileSubMenu,MF_SEPARATOR, NULL,NULL);
    AppendMenu(hFileSubMenu,MF_STRING, File_menu_item_page_setup,"Page Setup");
    AppendMenu(hFileSubMenu,MF_STRING, File_menu_item_print,"Print");
    AppendMenu(hFileSubMenu,MF_SEPARATOR, NULL,NULL);
    AppendMenu(hFileSubMenu,MF_STRING, File_menu_item_close_window,"Close Window");
    AppendMenu(hFileSubMenu,MF_STRING, File_menu_item_exit,"Exit");

    //Edit SubMenu Items
    AppendMenu(hEditSubMenu,MF_STRING, NULL,"Undo");
    AppendMenu(hEditSubMenu,MF_SEPARATOR, NULL,NULL);
    AppendMenu(hEditSubMenu,MF_STRING, NULL,"Cut");
    AppendMenu(hEditSubMenu,MF_STRING, NULL,"Copy");
    AppendMenu(hEditSubMenu,MF_STRING, NULL,"Paste");
    AppendMenu(hEditSubMenu,MF_STRING, NULL,"Delete");
    AppendMenu(hEditSubMenu,MF_SEPARATOR, NULL,NULL);
    AppendMenu(hEditSubMenu,MF_STRING, NULL,"Find");
    AppendMenu(hEditSubMenu,MF_STRING, NULL,"Find Next");
    AppendMenu(hEditSubMenu,MF_STRING, NULL,"Find Previous");
    AppendMenu(hEditSubMenu,MF_STRING, NULL,"Replace");
    AppendMenu(hEditSubMenu,MF_STRING, NULL,"Go to");
    AppendMenu(hEditSubMenu,MF_SEPARATOR, NULL,NULL);
    AppendMenu(hEditSubMenu,MF_STRING, NULL,"Select All");
    AppendMenu(hEditSubMenu,MF_STRING, NULL,"Time/Date");
    AppendMenu(hEditSubMenu,MF_SEPARATOR, NULL,NULL);
    AppendMenu(hEditSubMenu,MF_STRING, NULL,"Font");

    SetMenu(hwnd,hMenu);
}
void AddButtons(HWND hwnd)
{

    hwnd_for_text_input= CreateWindow(WC_EDIT,TEXT("Hi"), WS_VISIBLE | WS_CHILD,10,10,534,365,hwnd,NULL,NULL,NULL);


};


void addComboBox(HWND hwnd)
{
    int xpos = 100;            // Horizontal position of the window.
    int ypos = 100;            // Vertical position of the window.
    int nwidth = 200;          // Width of the window
    int nheight = 200;         // Height of the window
    HWND hwndParent =  hwnd; // Handle to the parent window

    HWND hWndComboBox = CreateWindow(WC_COMBOBOX, TEXT(""),
                                     CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
                                     xpos, ypos, nwidth, nheight, hwndParent, NULL,NULL,
                                     NULL);

    TCHAR Planets[9][10] =
    {
        TEXT("Mercury"), TEXT("Venus"), TEXT("Terra"), TEXT("Mars"),
        TEXT("Jupiter"), TEXT("Saturn"), TEXT("Uranus"), TEXT("Neptune"),
        TEXT("Pluto??")
    };

    TCHAR A[16];
    int  k = 0;

    memset(&A,0,sizeof(A));
    for (k = 0; k <= 8; k += 1)
    {
//        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)Planets[k]);

        // Add string to combobox.
        SendMessage(hWndComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A);
    }


    SendMessage(hWndComboBox, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);


}
