/*
*       win32-narrow.c
*       timwking1
*       10-Mar 2025
*
*/

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int FAR PASCAL WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevious, PSTR pCmdLine, int nCmdShow)
{
    static const char CLASS_NAME[]= "Main";

    static WNDCLASS wc = { };
    wc.lpfnWndProc      =WindowProc;
    wc.hInstance        =hInstance;
    wc.lpszClassName    =CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx
    (
        0,                      //dwExStyle
        CLASS_NAME,		        //lpClassName
        "Window Title",	        //lpWindowName
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

    if(hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

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
    switch(uMsg)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
            EndPaint(hwnd, &ps);
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}