
//#include <stdafx.h>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <float.h>
#include <vector> 
#include <commctrl.h>
#include <math.h>
#include <windowsx.h>
#include <string>
#include <stdio.h>
#include <sstream>


HANDLE hThread1, hThread2;


#define BLACKCOLOR RGB(0,0,0)

int dates[3];
std::string datesS[3];
HFONT font = CreateFont(120, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);


void DrawArrow(HWND hWnd, float angle, COLORREF color, int thicc) {
	HDC hdc = GetDC(hWnd);
	HPEN pen = CreatePen(PS_SOLID, thicc, color);
	SelectObject(hdc, pen);
	POINT vertices[] = { {200,200},{200 + 200 * cos(angle),200 + 200 * sin(angle)} };
	Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
}


DWORD WINAPI Thread2(LPVOID t) {
	SYSTEMTIME TIME;
	HDC hdc = GetDC((HWND)t);

	SelectObject(hdc, font);
	SetTextColor(hdc, RGB(255, 0, 0));
	SetBkColor(hdc, BLACKCOLOR);
	while (true) {
		GetLocalTime(&TIME);

		dates[0] = TIME.wHour;
		dates[1] = TIME.wMinute;
		dates[2] = TIME.wSecond;
		std::wstringstream b;
		for (int i = 0; i < 3; i++) {

			if (dates[i] < 10) {
				b << '0';
			}
			b << dates[i];
			if (i != 2) { b << ':'; }
		}
		std::wstring w = b.str();
		const WCHAR * wLine = w.c_str();
		TextOut(hdc, 0, 400, wLine, 9);
		Sleep(1000);
	}
	return 0;
}

HPEN Blackpen = CreatePen(PS_SOLID, 1, BLACKCOLOR);
HBRUSH Blackbrush = CreateSolidBrush(BLACKCOLOR),
		Greybrush = CreateSolidBrush(RGB(50, 50, 50));
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg) {
	case WM_PAINT:
	{
		HDC hdc = GetDC(hWnd);
		SYSTEMTIME chas;
		GetLocalTime(&chas);
		SelectObject(hdc, Blackpen);
		GetLocalTime(&chas);
		SelectObject(hdc, Blackbrush);
		Rectangle(hdc, 0, 0, 400, 400);
		DrawArrow(hWnd, ((((chas.wSecond*1000.0 - 1000.0) + chas.wMilliseconds) / 9500.0) - 1.57), RGB(0, 255, 255), 1);
		DrawArrow(hWnd, (chas.wMinute / 9.5) - 1.57, RGB(255, 0, 255), 3);
		DrawArrow(hWnd, (chas.wHour / 1.91) - 1.57, RGB(255, 255, 0), 5);
		Sleep(100);
		return 0;
		
	}
	case WM_TIMER:
	{
		RECT rect;
		rect.top = 0;
		rect.right = 1000;
		rect.left = 0;
		rect.bottom = 400;
		InvalidateRect(hWnd, &rect, TRUE);
		return 0;
	}
	case WM_CREATE:
	{
		hThread2 = CreateThread(NULL, 0, Thread2, hWnd, 0, NULL);
		SetTimer(hWnd, 1, 1, NULL);
	}
	return 0;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
};




int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow) {
	MSG msg{};
	HWND hwnd{};
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = CreateSolidBrush(BLACKCOLOR);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;

	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"Class";
	wc.lpszMenuName = NULL;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	if (!RegisterClassEx(&wc)) {
		return EXIT_FAILURE;
	}
	hwnd = CreateWindow(wc.lpszClassName, L"Время", WS_OVERLAPPEDWINDOW, 0, 0, 500, 550, NULL, NULL, wc.hInstance, NULL);
	if (hwnd == INVALID_HANDLE_VALUE)
	{
		return EXIT_FAILURE;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0)) {
		DispatchMessage(&msg);
		TranslateMessage(&msg);
	}
	return static_cast<int>(msg.wParam);
}

