#include "window.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch (message)
    {
        // this message is read when the window is closed
    case WM_DESTROY:
    {
        // close the application entirely
        PostQuitMessage(0);
        return 0;
    } break;
    case WM_KEYDOWN:
    {
        if (wParam == 'W')
        {
            SetWindowText(hWnd, L"renderer2");
        }
    } break;
    case WM_KEYUP:
    {
        if (wParam == 'W')
        {
            SetWindowText(hWnd, L"renderer");
        }
    } break;
    case WM_LBUTTONDOWN:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        std::ostringstream oss;
        oss << pt.x << "," << pt.y;
        std::cout << oss.str().c_str();
        SetWindowTextA(hWnd, oss.str().c_str());
    } break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc(hWnd, message, wParam, lParam);
}

void Window::createWndClass()
{
    // this struct holds information for the window class
    WNDCLASSEX wc;

    // clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    //wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    //wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"MainWindow";

    // register the window class
    RegisterClassEx(&wc);
}

void Window::createWindow(int &width, int &height)
{
    RECT wr = { 0, 0, width, height };    // set the size, but not the position
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size

    // create the window and use the result as the handle
    hWnd = CreateWindowEx(NULL,
        L"MainWindow",    // name of the window class
        L"renderer",   // title of the window
        WS_OVERLAPPEDWINDOW,    // window style
        0,    // x-position of the window
        0,    // y-position of the window
        wr.right - wr.left,    // width of the window
        wr.bottom - wr.top,    // height of the window
        NULL,    // we have no parent window, NULL
        NULL,    // we aren't using menus, NULL
        NULL,    // application handle
        NULL);    // used with multiple windows, NULL
}

Window::Window(int width, int height) : width(width), height(height)
{
    createWndClass();
    createWindow(width, height);
    ShowWindow(hWnd, 1);
}
