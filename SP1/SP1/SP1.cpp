
//#include <stdafx.h>
#include <Windows.h>


wchar_t alphabet[8] = { 'a','b','c','d','e','f','g','h' };

bool globalPaint = false;

void DrawRectAngle(HWND hWnd) {
	PAINTSTRUCT ps;
	BeginPaint(hWnd, &ps);
	HDC hdc = GetDC(hWnd);
	RECT rect;
	RECT window;
	bool paint = globalPaint;
	GetWindowRect(hWnd, &window);
	FillRect(hdc, &window, CreateSolidBrush(RGB(255, 255, 255)));
	for (int i = 0; i <= 8; i++) {
		for (int j = 0; j <= 8; j++) {
			if (paint) {
				rect.bottom = 40 + 40 * i;
				rect.right = 40 + 40 * j;
				rect.top = 0 + 40 * i;
				rect.left = 0 + 40 * j;
				FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));
				paint = false;
			}
			else {
				paint = true;
			}

		}
	}

	ReleaseDC(hWnd, hdc);
	EndPaint(hWnd, &ps);
}



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
	case WM_LBUTTONDOWN:
	{
		POINT tochka;
		GetCursorPos(&tochka);
		int firstpart = ((360 - tochka.y) / 40) + 1;
		int secondpart = (tochka.x / 40);
		wchar_t point[3] = { alphabet[secondpart], wchar_t('0' + firstpart),'\0' };
		MessageBox(hWnd, point, point, MB_OK);
	}
	return 0;
	case WM_RBUTTONDOWN:
	{
		globalPaint = !globalPaint;
		DrawRectAngle(hWnd);
	}
	return 0;
	case WM_CREATE:
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
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
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
	hwnd = CreateWindow(wc.lpszClassName, L"Lab_1", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, 0, 0, 335, 360, NULL, NULL, wc.hInstance, NULL);
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
