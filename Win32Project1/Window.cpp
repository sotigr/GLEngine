
#include "Window.h" 

using namespace std ;

char* FloatToString(float num)
{
	char carray[10];
	sprintf(carray, "%f", num);
	return carray;
}
char* IntToString(int num)
{
	char carray[10];
	sprintf(carray, "%d", num);
	return carray;
}
int _wposx = 100;
int _wposy = 100;
int _wwdth = 200;
int _whght = 200;
vector< Window*>* Window::OPENED_WINDOWS = new vector< Window*>();
float deltatime = 0;
int framerate = 0;
void Window::gen_random(char *s, const int len) {
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	s[len] = 0;
}
const wchar_t *GetWC(const char *c)
{
	size_t size = strlen(c) + 1;
	wchar_t* portName = new wchar_t[size];

	size_t outSize;
	mbstowcs_s(&outSize, portName, size, c, size - 1);
	return portName;
}
Window::Window()
{
	WNDCLASSEX wc;
	char* winclass = (char*)malloc(sizeof(char) * 6);
	this->gen_random(winclass, 6);
	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = Window::WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = GetWC(winclass);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Window Registration Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// Step 2: Creating the Window
	winhandle = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		GetWC(winclass),
		L"Window",
		WS_DLGFRAME | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, GetModuleHandle(NULL), NULL);

	if (winhandle == NULL)
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return;
	}
	RECT rect;
	if (GetWindowRect(this->winhandle, &rect))
	{
		this->_wwdth = rect.right - rect.left;
		this->_whght = rect.bottom - rect.top;
		this->_wposx = rect.left;
		this->_wposy = rect.top;
	}
	this->Viewport = new OpenGL::Viewport(0, 0, this->_wwdth, this->_whght);

	Window::OPENED_WINDOWS->push_back(this);

	this->msglptmr = new Timer();
}
#include <iostream>;
#include "Timer.h";
void Window::InitGL()
{
	using namespace std::chrono;
	m_hdc = GetDC(this->winhandle);
	
	if ((m_hglrc = CreateOGLContext(m_hdc)))
	{	refresh_viewport();
		glClearColor(0, 0, 0, 1.0f);
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH);
		glClearDepth(1.0f);        // Set background depth to farthest
		glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
		glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
		glShadeModel(GL_SMOOTH);   // Enable smooth shading
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
		Timer t;
		
		t.Start();
		 
		int frames = 0;
		while (!stopGL)
		{ 
			steady_clock::time_point begin = steady_clock::now();

			glMatrixMode(GL_MODELVIEW);
			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLoadIdentity();

			gluLookAt(2, 2, 5, 0, 0, 0, 0, 1, 0);
			//draw


			glBegin(GL_QUADS);

			glColor3f(0.0f, 1.0f, 0.0f);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);

			glEnd();

			glFlush();
			SwapBuffers(m_hdc);

			frames += 1;
			
			steady_clock::time_point end = steady_clock::now();
			duration<float> delta = end.time_since_epoch()  - begin.time_since_epoch() ;
		    deltatime = delta.count();

			if (t.GetTicks() >= 1000)
			{
				t.Stop();
				framerate = frames;
				frames = 0;
				t.Start();
			}
	 
			Sleep((1000 / 30) - deltatime);
	 
			//cout << deltatime << endl;
			 
		}
	}
}
void Window::refresh_viewport() {
 
	glViewport(0, 0, this->GetWidth(), this->GetHeight());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(62, (float)this->GetWidth() / this->GetHeight(), 0.01, 100);
	 
	glMatrixMode(GL_MODELVIEW);	 
	glLoadIdentity();

}


void Window::Show() {
	ShowWindow(winhandle, SW_SHOW);
	UpdateWindow(winhandle);
}
void Window::MsgLoop()
{

}
 
void Window::ShowDialog()
{
	this->Show();
	// Step 3: The Message Loop
	stopGL = false;

	//auto hand = async(launch::async, &Window::InitGL, this);


	thread t(&Window::InitGL, this);
	t.detach();
	
	while (PeekMessage(&Msg, 0, 0, 0, PM_REMOVE)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
		if (Window::OPENED_WINDOWS->size() < 1) {
			stopGL = true;

			break;
		}

		Sleep(33.333);
	} 



	/*	*/

}


void Window::SetPosition(int x, int y) {
	this->_wposx = x;
	this->_wposy = y;
	RECT rect;
	if (GetWindowRect(this->winhandle, &rect))
	{
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		MoveWindow(this->winhandle, x, y, width, height, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
	}

}
void Window::SetWidth(int w) {
	this->_wwdth = w;
	RECT rect;
	if (GetWindowRect(this->winhandle, &rect))
	{
		//int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		MoveWindow(this->winhandle, rect.left, rect.top, w, height, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
	}

}
void Window::SetHeight(int h) {
	this->_whght = h;
	RECT rect;
	if (GetWindowRect(this->winhandle, &rect))
	{
		int width = rect.right - rect.left;
		//int height = rect.bottom - rect.top;

		MoveWindow(this->winhandle, rect.left, rect.top, width, h, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
	}
}
int Window::GetWidth() {
	RECT rect;
	GetWindowRect(this->winhandle, &rect);
	return  rect.right - rect.left;
}
int Window::GetHeight() {
	RECT rect;
	GetWindowRect(this->winhandle, &rect);
	return  rect.bottom - rect.top;
}
WindowPosition Window::GetPosition() {
	RECT rect;
	GetWindowRect(this->winhandle, &rect);
	WindowPosition _winpos;
	_winpos.x = rect.left;
	_winpos.y = rect.top;
	return _winpos;
}
char* Window::GetTitle()
{
	wchar_t wnd_title[256];
	GetWindowText(this->winhandle, wnd_title, sizeof(wnd_title));
	wstring wstr = wnd_title;
	string str(wstr.begin(), wstr.end());
	return (char*)str.c_str();
}
void Window::SetTitle(char* title) {
	SetWindowText(this->winhandle, GetWC(title));
}
void Window::Hide() {
	ShowWindow(this->winhandle, SW_HIDE);
}
void Window::Minimize() {
	ShowWindow(this->winhandle, SW_MINIMIZE);
}
void Window::Maximize() {
	ShowWindow(this->winhandle, SW_MAXIMIZE);
}
void Window::Restore() {
	ShowWindow(this->winhandle, SW_RESTORE);
}
void Window::Close() {
	DestroyWindow(this->winhandle);
	for (std::vector<Window*>::iterator iter = Window::OPENED_WINDOWS->begin(); iter != Window::OPENED_WINDOWS->end(); ++iter)
	{
		if (*iter == this)
		{
			Window::OPENED_WINDOWS->erase(iter);
			break;
		}
	}
}

Window::~Window()
{
}

HGLRC Window::CreateOGLContext(HDC hdc)
{
	unsigned int pixelformat;
	HGLRC hglrc;

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Support Window
		PFD_SUPPORT_OPENGL |						// Format Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request RGBA Format
		32,											// Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits mask
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		32,											// Z-Buffer depth
		0,											// Stencil Buffer
		0,											// Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(pixelformat = ChoosePixelFormat(hdc, &pfd)))
	{
		return 0;
	}

	if (!SetPixelFormat(hdc, pixelformat, &pfd))
	{
		return 0;
	}

	if (!(hglrc = wglCreateContext(hdc)))
	{
		return 0;
	}

	if (!wglMakeCurrent(hdc, hglrc))
	{
		return 0;
	}

	return hglrc;
}
BOOL Window::DestroyOGLContext()
{
	if (m_hglrc)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_hglrc);
		m_hglrc = NULL;
	}
	return TRUE;
}