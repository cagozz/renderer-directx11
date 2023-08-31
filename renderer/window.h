#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>

#include <sstream>
#include <iostream>


class Window 
{
protected:
	HWND hWnd;

	int width, height;
private:
	void createWndClass();
	void createWindow(int&,int&);
public:
	Window(int width, int height);

	HWND gethWnd() { return hWnd; }
	int getWidth() { return width; }
	int getHeight() { return height; }

	friend class DX;
};


#endif // !WINDOW_H
