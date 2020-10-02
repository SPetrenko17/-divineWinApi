
#include <stdafx.h>
#include <Windows.h>
#include <float.h>
#include <vector> 
#include <commctrl.h>
#include <math.h>
#include <cmath>
#include <cstdio>
#include <windowsx.h>
#include <string>
#include <stdio.h>
#include <vector>
#include <ctime>
#include "GraphicDZ.h"
#include <complex>


#define QUALITY	50000 //количество отрисовываемых точек, повышать их число почти не имеет смысла,так как график итак нормально рисуется



HANDLE hThread1; //управление потоками 
HANDLE hThread2;	//потоки нужны для более быстрой работы программы 
HANDLE hThread4;
HANDLE hThread5;

COLORREF COLOR = RGB(0, 0, 0);	//изначальный цвет фона 

float size = 0.75; //начальный размер

int offsetx=0;		//сдвиг по x
int offsety=0;		//сдвиг по y

COLORREF Color = RGB(255, 255, 255);				//изначальный цвет координатных прямых 

int r = 255, 
	g = 255,
	b = 255;

void UpdateColor() {
	Color = RGB(r, g, b);
}



std::vector<POINT> Data(QUALITY);			//вектор , в котором хранятся все точки , можно было бы использовать массив ,но вектор тупо лучше

HWND off1;

HWND off2;

HWND zoom3;

HWND r4;

HWND g5;

HWND b6;





DWORD WINAPI Thread2(LPVOID t) {			//функция для первого потока
	int pos = 0;			//текущая заполняемая точка в векторе
	float x = -10;			//начальное значение x (меньше -4 данная функция не принимает значений. 
	for (pos = 0; pos < QUALITY; pos++)
	{
		x+=20.0/QUALITY; //за QUALITY итераций , в данном случае при QUALITY = 1000 x увеличится на 8 (1000* (8/1000) = 8) и достигнет максимума в 4 (при x>4 график не принимает значения)
		Data[pos].x = x * 50 + 500;						
		//x домножается на 50 и увеличивается на 500 для получения значения точки на экране, находящейся по центру. 
	
		Data[pos].y = (pow(5.3,x) - pow(cos(5.35*x),0.6))*400+750;
		//y домножается на 50 и увеличивается на 500 для получения значения точки на экране, находящейся по центру. 
		// также при вычислении y используется изначальное значение X (не точки на экране , не Data[pos].x, а x из 59 строчки.
	}
	return 0;
}




DWORD WINAPI Thread1(LPVOID t) {  //функция ,выполняемая первым потоком 

	HDC hdc = GetDC((HWND)t);
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));					//создание пера заданного цвета и толщины
	//PS_SOLID - сплошное , 1 - толщина , RGB(200, 200, 200) - светло серый цвет 
	SelectObject(hdc, pen);//когда дальше LineTo будет рисовать прямую линию он будет использовать созданное перо 
	// выбор пера для hdc 
	for (int i = -30; i < 30; i++) {
		MoveToEx(hdc, 480+ offsetx, 500 + (i * 150 * size) + offsety, NULL);	//60 черточек на графике к изменяемому y прибавляется offsety
		LineTo(hdc, 520 + offsetx, 500 + (i * 150 * size) + offsety);
	}
	for (int i = -30; i < 30; i++) {
		MoveToEx(hdc, 500 + (i * 150 * size) + offsetx, 480 + offsety, NULL);//60 черточек на графике к изменяемому x прибавляется offsetx
		LineTo(hdc, 500 + (i * 150 * size) + offsetx, 520 + offsety);
	}
	//offsetx и offsety - глобальные переменные и меняются при нажатии на клавиши W A S D  - навигация по графику. 
	// просто все координаты изменяются на offsetx и offsety и картинка сдвигается 
	pen = CreatePen(PS_SOLID, 4, RGB(255, 255, 255));			//создание пера заданного цвета и толщины 
	SelectObject(hdc, pen);
	MoveToEx(hdc, 0, 500 + offsety, NULL);			//большие толстые черные прямые линии 
	LineTo(hdc, 1000, 500 + offsety);
	MoveToEx(hdc, 500 + offsetx, 0, NULL);
	LineTo(hdc, 500 + offsetx, 1000);
	//такая же фишка с offsetx и offsety как с черточками. 
	ReleaseDC((HWND)t, hdc);



	return 0;
}

DWORD WINAPI Thread4(LPVOID t) {
	HDC hdc = GetDC((HWND)t);
	for (int i = 0; i < (QUALITY / 2); i++) { 
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 500 + offsetx, Data[i].y * size - (500 * size) + 500 + offsety, Color); 
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 500 + offsetx, Data[i].y * size - (500 * size) + 501 + offsety, Color);
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 501 + offsetx, Data[i].y * size - (500 * size) + 501 + offsety, Color);
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 501 + offsetx, Data[i].y * size - (500 * size) + 501 + offsety, Color);
	}
	return 0;
}



DWORD WINAPI Thread5(LPVOID t) {
	HDC hdc = GetDC((HWND)t);

	for (int i = QUALITY  / 2; i < (QUALITY ); i++) {
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 500 + offsetx, Data[i].y * size - (500 * size) + 500 + offsety, Color);
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 500 + offsetx, Data[i].y * size - (500 * size) + 501 + offsety, Color);
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 501 + offsetx, Data[i].y * size - (500 * size) + 501 + offsety, Color);
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 501 + offsetx, Data[i].y * size - (500 * size) + 501 + offsety, Color);
	}
	return 0;
}

void StartDrawing(HWND hWnd) {									//начало отрисовки - запускаются все потоки для отрисовки графика 
	hThread1 = CreateThread(NULL, 0, Thread1, hWnd, 0, NULL); //координатные прямые
	hThread4 = CreateThread(NULL, 0, Thread4, hWnd, 0, NULL); //первая половина графика
	hThread5 = CreateThread(NULL, 0, Thread5, hWnd, 0, NULL); //вторая половина графика
}

void StopDrawing(HWND hWnd) {
	TerminateThread(hThread1, 0);			//прервать отрисовку , заканчиваются все соответсвующие потоки
	TerminateThread(hThread4, 0);
	TerminateThread(hThread5, 0);
}

void reDraw(HWND hWindow) {
	StopDrawing(hWindow);
	RECT Window;
	HDC hdc = GetDC(hWindow);
	GetWindowRect(hWindow, &Window);
	FillRect(hdc, &Window, CreateSolidBrush(COLOR));
	StartDrawing(hWindow);
}
BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_INITDIALOG: {
		RECT ActualSize;
		off1 = GetDlgItem(hWnd, IDC_SLIDER1);
		off2 = GetDlgItem(hWnd, IDC_SLIDER2);
		zoom3 = GetDlgItem(hWnd, IDC_SLIDER3);
		r4 = GetDlgItem(hWnd, IDC_SLIDER4);
		g5 = GetDlgItem(hWnd, IDC_SLIDER5);
		b6 = GetDlgItem(hWnd, IDC_SLIDER6);
		SendMessage(off1, TBM_SETRANGE, (WPARAM)1, (LPARAM)MAKELONG(-200, 200));
		SendMessage(off2, TBM_SETRANGE, (WPARAM)1, (LPARAM)MAKELONG(-200, 200));
		SendMessage(r4, TBM_SETRANGE, (WPARAM)1, (LPARAM)MAKELONG(0, 255));
		SendMessage(g5, TBM_SETRANGE, (WPARAM)1, (LPARAM)MAKELONG(0, 255));
		SendMessage(b6, TBM_SETRANGE, (WPARAM)1, (LPARAM)MAKELONG(0, 255));
		SendMessage(zoom3, TBM_SETRANGE, (WPARAM)1, (LPARAM)MAKELONG(0, 5));
		SendMessage(r4, TBM_SETPOS, (WPARAM)1, r);
		SendMessage(g5, TBM_SETPOS, (WPARAM)1, g);
		SendMessage(b6, TBM_SETPOS, (WPARAM)1, b);
		SendMessage(off1, TBM_SETPOS, (WPARAM)1, offsetx);
		SendMessage(off2, TBM_SETPOS, (WPARAM)1, offsety);
		GetClientRect(hWnd, &ActualSize);
	}
						return 0;

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK) {
			r = SendMessage(r4, TBM_GETPOS, 0, 0);
			g = SendMessage(g5, TBM_GETPOS, 0, 0);
			b = SendMessage(b6, TBM_GETPOS, 0, 0);
			UpdateColor();
			offsetx = SendMessage(off1, TBM_GETPOS, 0, 0);
			offsety = SendMessage(off2, TBM_GETPOS, 0, 0);
			EndDialog(hWnd, 0);
			return 0;
		}
		if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hWnd, 0);
			return 0;
		}
	}
	return 0;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return 0;

	}
	return 0;
}


LRESULT CALLBACK WindowProcess(HWND hWindow,
	UINT uMessage,
	WPARAM wParameter,
	LPARAM lParameter)
{

	switch (uMessage) {
	case WM_CREATE:
	{
		
		hThread2 = CreateThread(NULL, 0, Thread2, hWindow, 0, NULL); //поток для вычисления значений точек на экране , запускается сразу.
		//больше данный поток нигде не вызывается ,так как масштабирование и навигация происходят лишь с помощью изменения параметров отрисовки графика
		reDraw(hWindow);
	}
	return 0;

	case WM_KEYDOWN:
	{
		switch (wParameter) {
		case 0x44:// клаивша D
		{
			DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DlgProc), 0);
		}
		case 0x45: //клавиша E
		{
			reDraw(hWindow);
		}
		}
	}
	return 0;
	case WM_DESTROY:
		//StopDrawing(hWindow);
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWindow, uMessage, wParameter, lParameter);
	}
	return NULL;
}




int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow) {
	MSG msg{};
	HWND hwnd{};
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = CreateSolidBrush(RGB(125, 125, 125)); //изначальный цвет окна 
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;

	wc.lpfnWndProc = WindowProcess;
	wc.lpszClassName = L"Class";
	wc.lpszMenuName = NULL;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	if (!RegisterClassEx(&wc)) {
		return EXIT_FAILURE;
	}
	hwnd = CreateWindow(wc.lpszClassName, L"dz",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX /*запрет на изменение размера окна*/
		, 0, 0, 1000, 1000, NULL, NULL, wc.hInstance, NULL);
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

