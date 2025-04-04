/*=============================================================================
*       win32-unicode.c
*       timwking1
*       10-Mar 2025
=============================================================================*/

/*
*       Be sure to set compiler flags!
*       For Unicode Win32 apps in gcc: -mwindows -municode
*/
#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*=============================================================================
*   wWinMain 
*       The entry point of a Unicode win32 application
=============================================================================*/
int FAR PASCAL WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevious, LPWSTR pCmdLine, int nCmdShow)
{
    static const wchar_t CLASS_NAME[]= L"Main";

    static WNDCLASSEXW wc = { };
    wc.cbSize = sizeof(WNDCLASSEX);                    //class struct size in bytes
    wc.style = CS_HREDRAW | CS_VREDRAW;                //class style (CS_)
    wc.lpfnWndProc = WindowProc;                       //long pointer to window procedure function
    wc.cbClsExtra = 0;                                 //extra bytes to allocate for the class
    wc.cbWndExtra = 0;                                 //extra bytes to allocate for the window instance
    wc.hInstance = hInstance;                          //instance handle
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);        //icon (IDI_)
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);          //curosr (IDC_)
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW +1);      //background brush handle
    wc.lpszMenuName = NULL;                            //resource name of class menu
    wc.lpszClassName = CLASS_NAME;                     //class name string
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);      //small version of the icon (IDI_)

    /*
    *   The Window class only needs to be registered once.
    *   If there is a previous instance handle we do not register the class again.
    */
    if (!hPrevious)
    {
        //Register the window class we just initialized (wc)
        if(!RegisterClassEx(&wc))
        {
            //This should never happen, but we inform the user and return gracefully in case it does.
            MessageBox(NULL, L"Window Registration Failed", L"Error", MB_ICONERROR | MB_OK);
            return 0;
        }
    }

    HWND hwnd = CreateWindowEx
    (
        0,                      //dwExStyle
        CLASS_NAME,		        //lpClassName
        L"Window Title",	    //lpWindowName
        WS_OVERLAPPEDWINDOW,	//dwStyle
        CW_USEDEFAULT, 		    //X
        CW_USEDEFAULT, 		    //Y
        640, 		            //nWidth
        480,		            //nHeight
        NULL,			        //hWndParent
        NULL,			        //hMenu
        hInstance,		        //hInstance
        NULL			        //lpParam
    );

    if (hwnd == NULL) 
    {
        //Again, this should never happen since we just created hWnd, but just in case, inform the user and return gracefully.
        MessageBox(NULL, L"Window Creation Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    //Finally, now that the window is fully initialized, we can show it and begin ticking the message loop.
    static MSG msg;
    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    
    switch(uMsg)
    {
        case WM_CREATE:
        {
            return 0;
        }
        case WM_SIZE:
        {
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);
            return 0;
        }
        case WM_DESTROY:
        {
            //Free any resources allocated for the window here
            PostQuitMessage(0);
            return 0;
        }
        case WM_PAINT:
        {
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
            EndPaint(hwnd, &ps);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}