#pragma once
#include "Viewport.h"; 
#include <Windows.h>; 
#include <gl\GL.h>;
#include <gl\GLU.h>;
#include <vector>;

#include <thread>;
#include <string>;
#include "Timer.h"; 
#include <chrono>; 
struct WindowPosition {
	int x, y;
};
class Window 
{
private:
	int _wposx;
	int _wposy;
	int _wwdth;
	int _whght;
	void gen_random(char *s, const int len);
	MSG Msg;
 
	
	void InitGL();
	void MsgLoop();
	bool stopGL;
	Timer* msglptmr; 
	HGLRC CreateOGLContext(HDC hdc);
	BOOL DestroyOGLContext();
	HGLRC		m_hglrc;
	HDC			m_hdc;
	void refresh_viewport();
protected:
	virtual 	void MouseMove() {};
	virtual  void MouseLeftButtonDown() {};
	  virtual  void MouseRigntButtonDown() {};

public:
	float deltatime;
	int framerate;
	static std::vector<Window*>* OPENED_WINDOWS;
	Window();
	~Window();
	
	void Show(void);

	void ShowDialog(void);
	void Hide(void);
	void Close(void);
	void Maximize(void);
	void Minimize(void);
	void Restore(void);

	void SetWidth(int w);
	void SetHeight(int h);
	void SetPosition(int x, int y);

	int GetWidth();
	int GetHeight();
	WindowPosition GetPosition();

	void SetTitle(char* title);
	char* GetTitle(void);
	HWND winhandle;
	OpenGL::Viewport* Viewport;
	
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		Window* currentw = nullptr;
		for (int i = 0; i < Window::OPENED_WINDOWS->size(); i++)
			if ((*Window::OPENED_WINDOWS)[i]->winhandle == hWnd)
				currentw = (*Window::OPENED_WINDOWS)[i];

		
			switch (message)
			{
			case WM_MOUSEMOVE:
				currentw->MouseMove();
				break;
			case WM_COMMAND: 
				break;
			case WM_PAINT:
	 
				break;
			case WM_SIZE:
				currentw->refresh_viewport();
				break;
			case WM_DESTROY: 
				currentw->Close();

				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		return 0;
	}
};