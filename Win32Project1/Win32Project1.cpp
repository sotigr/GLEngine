
 
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
#include <windows.h>;
#include <stdlib.h>;
#include <stdio.h>;
#include <gl\GL.h>;
#include <gl\GLU.h>;
 
#include "MainWindow.h";

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{ 	
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	MainWindow* win1 = new MainWindow();
	win1->SetWidth(1024);
	win1->SetHeight(768);
	win1->SetTitle("hello win");
	win1->ShowDialog(); 


	return 0;
}


 
