
//#include <stdafx.h>
#include <Windows.h>
#include <cmath>
#include <stdio.h>


#define IDM_COLOR 1234

//currency

#define USDRUB 1500
#define RUBUSD 1501
#define EURRUB 1502
#define RUBEUR 1503
#define JPYRUB 1504
#define RUBJPY 1505
#define GBPRUB 1506
#define RUBGBP 1507
#define CADRUB 1508
#define RUBCAD 1509

//metrics
#define KMMILE 1600
#define MILEKM 1601
#define LYKM   1602
#define KMLY   1603
#define LYMILE 1604
#define MILELY 1605

//temp
#define CELFAR 1700
#define FARCEL 1701



COLORREF color = RGB(255, 0, 0);


wchar_t buffer[20];

float x = 0, a = 0, b = 0;

HWND hUSD,
hUSDR;

HWND label, label1;

HWND hEdit;



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{


	switch (uMsg) {

	case WM_PAINT:
	{

	}

	return 0;
	case WM_CTLCOLORSTATIC:
	{

	}
	return 0;
	case WM_CREATE:
	{
		//menu
		HMENU hMenubar = CreateMenu();
		HMENU hMenu = CreateMenu();
		HMENU hSubMenuCurrency = CreatePopupMenu();
		HMENU hSubMenuCurrencyFR = CreatePopupMenu();
		HMENU hSubMenuCurrencyRF = CreatePopupMenu();
		HMENU hSubMenuRange = CreatePopupMenu();
		HMENU hSubMenuText = CreatePopupMenu();
		HMENU hSubMenuTemp = CreatePopupMenu();
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"Convert");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenuCurrency, L"Currency");
		AppendMenu(hSubMenuCurrency, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenuCurrencyFR, L"Foreign->RUB");
		AppendMenu(hSubMenuCurrency, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenuCurrencyRF, L"RUB->Foreign");
		AppendMenu(hSubMenuCurrencyFR, MF_POPUP, USDRUB, L"USD->RUB");
		AppendMenu(hSubMenuCurrencyFR, MF_POPUP, EURRUB, L"EUR->RUB");
		AppendMenu(hSubMenuCurrencyFR, MF_POPUP, CADRUB, L"CAD->RUB");
		AppendMenu(hSubMenuCurrencyFR, MF_POPUP, JPYRUB, L"JPY->RUB");
		AppendMenu(hSubMenuCurrencyFR, MF_POPUP, GBPRUB, L"GBP->RUB");

		AppendMenu(hSubMenuCurrencyRF, MF_POPUP, RUBUSD, L"RUB->USD");
		AppendMenu(hSubMenuCurrencyRF, MF_POPUP, RUBEUR, L"RUB->EUR");
		AppendMenu(hSubMenuCurrencyRF, MF_POPUP, RUBCAD, L"RUB->CAD");
		AppendMenu(hSubMenuCurrencyRF, MF_POPUP, RUBJPY, L"RUB->JPY");
		AppendMenu(hSubMenuCurrencyRF, MF_POPUP, RUBGBP, L"RUB->GBP");

		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenuRange, L"Range");
		AppendMenu(hSubMenuRange, MF_POPUP, KMMILE, L"KM->MILE");
		AppendMenu(hSubMenuRange, MF_POPUP, KMLY, L"KM->LY");
		AppendMenu(hSubMenuRange, MF_POPUP, MILEKM, L"MILE->KM");
		AppendMenu(hSubMenuRange, MF_POPUP, MILELY, L"MILE->LY");
		AppendMenu(hSubMenuRange, MF_POPUP, LYMILE, L"LY->MILE");
		AppendMenu(hSubMenuRange, MF_POPUP, LYKM, L"LY->KM");


		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenuTemp, L"Temp");
		AppendMenu(hSubMenuTemp, MF_POPUP, CELFAR, L"CEL->FAR");
		AppendMenu(hSubMenuTemp, MF_POPUP, FARCEL, L"FAR->CEL");
		SetMenu(hWnd, hMenubar);

		// menu 
		hUSD = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"0", WS_CHILD | WS_VISIBLE, 60, 40, 90, 20, hWnd, (HMENU)0, NULL, NULL);
		hUSDR = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"0", WS_CHILD | WS_VISIBLE, 150, 40, 90, 20, hWnd, (HMENU)0, NULL, NULL);
		label = CreateWindow(L"STATIC", L"USD", WS_CHILD | WS_VISIBLE, 0, 40, 60, 20, hWnd, 0, 0, NULL);
		label1 = CreateWindow(L"STATIC", L"RUB", WS_CHILD | WS_VISIBLE, 240, 40, 60, 20, hWnd, 0, 0, NULL);
		HFONT font = CreateFont(20, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"Times New Roman MS");
		SendMessage(label, WM_SETFONT, WPARAM(font), NULL);
		SendMessage(label1, WM_SETFONT, WPARAM(font), NULL);
		HWND BUTTON = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"CONVERT!", WS_CHILD | WS_VISIBLE, 60, 60, 180, 30, hWnd, (HMENU)1000, 0, NULL);

	}
	return 0;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == USDRUB) {
			SendMessage(label, WM_SETTEXT, NULL, WPARAM(L"USD"));
			SendMessage(label1, WM_SETTEXT, NULL, WPARAM(L"RUB"));
			x = 74.89;
		}
		if (LOWORD(wParam) == RUBUSD) {
			SendMessage(label, WM_SETTEXT, NULL, WPARAM(L"RUB"));
			SendMessage(label1, WM_SETTEXT, NULL, WPARAM(L"USD"));
			x = (1 / 74.89);
		}
		if (LOWORD(wParam) == EURRUB) {
			SendMessage(label, WM_SETTEXT, NULL, WPARAM(L"EUR"));
			SendMessage(label1, WM_SETTEXT, NULL, WPARAM(L"RUB"));
			x = 88.68;
		}

		if (LOWORD(wParam) == RUBEUR) {
			SendMessage(label, WM_SETTEXT, NULL, WPARAM(L"RUB"));
			SendMessage(label1, WM_SETTEXT, NULL, WPARAM(L"EUR"));
			x = (1 / 88.68);
		}
		if (LOWORD(wParam) == CADRUB) {
			SendMessage(label, WM_SETTEXT, NULL, WPARAM(L"CAD"));
			SendMessage(label1, WM_SETTEXT, NULL, WPARAM(L"RUB"));
			x = 56.85;
		}

		if (LOWORD(wParam) == RUBCAD) {
			SendMessage(label, WM_SETTEXT, NULL, WPARAM(L"RUB"));
			SendMessage(label1, WM_SETTEXT, NULL, WPARAM(L"CAD"));
			x = (1 / 56.85);
		}
		if (LOWORD(wParam) == JPYRUB) {
			SendMessage(label, WM_SETTEXT, NULL, WPARAM(L"JPY"));
			SendMessage(label1, WM_SETTEXT, NULL, WPARAM(L"RUB"));
			x = 0.71;
		}

		if (LOWORD(wParam) == RUBJPY) {
			SendMessage(label, WM_SETTEXT, NULL, WPARAM(L"RUB"));
			SendMessage(label1, WM_SETTEXT, NULL, WPARAM(L"JPY"));
			x = (1 / 0.71);
		}
		if (LOWORD(wParam) == RUBGBP) {
			SendMessage(label, WM_SETTEXT, NULL, WPARAM(L"RUB"));
			SendMessage(label1, WM_SETTEXT, NULL, WPARAM(L"GBP"));
			x = 0.0104;
		}
		if (LOWORD(wParam) == GBPRUB) {
			SendMessage(label, WM_SETTEXT, NULL, WPARAM(L"GBP"));
			SendMessage(label1, WM_SETTEXT, NULL, WPARAM(L"RUB"));
			x = 96.05;
		}




		////////qq

		if (LOWORD(wParam) == KMMILE) {
			SendMessage(label, WM_SETTEXT, NULL, WPARAM(L"KM"));
			SendMessage(label1, WM_SETTEXT, NULL, WPARAM(L"MILE"));
			x = 0.621;
		}
		if (LOWORD(wParam) == KMLY) {
			SendMessage(label, WM_SETTEXT, NULL, WPARAM(L"KM"));
			SendMessage(label1, WM_SETTEXT, NULL, WPARAM(L"LY"));
			x = 1.057000834E-13;
		}
		if (LOWORD(wParam) == LYKM) {
			SendMessage(label, WM_SETTEXT, NULL, WPARAM(L"LY"));
			SendMessage(label1, WM_SETTEXT, NULL, WPARAM(L"KM"));
			x = 1.057000834E+13;
		}

		if (LOWORD(wParam) == LYMILE) {
			SendMessage(label, WM_SETTEXT, NULL, WPARAM(L"LY"));
			SendMessage(label1, WM_SETTEXT, NULL, WPARAM(L"MILE"));
			x = (1 / 0.621)*1.057000834E+13;
		}
		if (LOWORD(wParam) == MILEKM) {
			SendMessage(label, WM_SETTEXT, NULL, WPARAM(L"MILE"));
			SendMessage(label1, WM_SETTEXT, NULL, WPARAM(L"KM"));
			x = (1 / 0.621);
		}

		if (LOWORD(wParam) == MILELY) {
			SendMessage(label, WM_SETTEXT, NULL, WPARAM(L"MILE"));
			SendMessage(label1, WM_SETTEXT, NULL, WPARAM(L"LY"));
			x = (1 / ((1 / 0.621)*1.057000834E+13));
		}
		if (LOWORD(wParam) == FARCEL) {
			SendMessage(label, WM_SETTEXT, NULL, WPARAM(L"FAR"));
			SendMessage(label1, WM_SETTEXT, NULL, WPARAM(L"CEL"));
			x = FARCEL;
		}

		if (LOWORD(wParam) == CELFAR) {
			SendMessage(label, WM_SETTEXT, NULL, WPARAM(L"CEL"));
			SendMessage(label1, WM_SETTEXT, NULL, WPARAM(L"FAR"));
			x = CELFAR;
		}

		if (LOWORD(wParam) == 1000) {
			GetWindowText(hUSD, buffer, 20);
			a = (float)wcstod(buffer, NULL);

			if (x == CELFAR) {
				b = (a*(9 / 5)) + 32;
			}
			else if (x == FARCEL) {
				b = (a - 32) * 5 / 9;
			}
			else {
				b = a * x;

			}
			char vOutChar[17];
			_gcvt_s(vOutChar, sizeof(vOutChar), b, 8);
			mbstowcs_s(NULL, buffer, sizeof(buffer) / 2, vOutChar, sizeof(vOutChar));

			SetWindowText(hUSDR, buffer);
			UpdateWindow(hUSDR);
		}
	}
	return 0;
	case WM_LBUTTONDOWN:
	{
	}
	return 0;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	return 0;
	case WM_SYSCOMMAND: {
		int command = int(wParam) & 0xfff0;
		if (command == SC_MOVE)
			return 0;
		break;
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
	wc.hbrBackground = CreateSolidBrush(RGB(192, 192, 192));
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
	hwnd = CreateWindow(wc.lpszClassName, L"Lab_3", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, 0, 0, 310, 200, NULL, NULL, wc.hInstance, NULL);
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
