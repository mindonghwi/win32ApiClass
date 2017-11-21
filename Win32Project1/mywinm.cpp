#include "stdafx.h"

C_MYWINDOW* C_MYWINDOW::m_pMyWin(nullptr);

C_MYWINDOW::C_MYWINDOW() :
	m_hWnd(NULL),
	m_hInstance(NULL),
	m_nPosX(0),
	m_nPosY(0),
	m_szStr{}
{
}

void C_MYWINDOW::init(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = L"asdf";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassExW(&wcex);

	m_hWnd = CreateWindowW(L"asdf", nullptr, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	m_hInstance = hInstance;

	if (!m_hWnd)
	{
		return ;
	}

	load();

	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hWnd);
}

void C_MYWINDOW::updataMsg()
{

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			updata();
			render();
		}
	}
}

LRESULT C_MYWINDOW::myProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
		m_nPosX = (int)(short)(lParam & 0x0000ffff);
		m_nPosY = (int)(short)((lParam>>16) & 0x0000ffff);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT C_MYWINDOW::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return m_pMyWin->myProc(hWnd, message, wParam, lParam);
}

void C_MYWINDOW::createInstance()
{
	if (!m_pMyWin)
		m_pMyWin = new C_MYWINDOW();
}

C_MYWINDOW * C_MYWINDOW::getInstance()
{
	return m_pMyWin;
}

void C_MYWINDOW::releaseInstance()
{
	if (m_pMyWin) {
		delete m_pMyWin;
		m_pMyWin = nullptr;
	}
}

void C_MYWINDOW::render()
{
	HDC hDcMain = GetDC(m_hWnd);

	swprintf_s(m_szStr, 30, L"XPos: %d YPos: %d", m_nPosX, m_nPosY);

	TextOut(hDcMain, 100, 100, m_szStr, 20);

	ReleaseDC(m_hWnd, hDcMain);
}

void C_MYWINDOW::updata()
{
	
}

void C_MYWINDOW::load()
{

}
