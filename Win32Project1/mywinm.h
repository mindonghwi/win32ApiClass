#pragma once

#include <Windows.h>

class C_MYWINDOW {
private:
	HWND				m_hWnd;
	HINSTANCE			m_hInstance;



	WCHAR				m_szStr[30];
	int					m_nPosX;
	int					m_nPosY;

public:
	void init(HINSTANCE hInstance);
	void updataMsg();
private:
	C_MYWINDOW();

private:
	static	C_MYWINDOW*	m_pMyWin;
	LRESULT CALLBACK myProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	static	void		createInstance();
	static C_MYWINDOW*	getInstance();
	static	void		releaseInstance();
private:
	void render();
	void updata();
	void load();
};