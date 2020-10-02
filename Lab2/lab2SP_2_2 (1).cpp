
//#include <stdafx.h>
#include <Windows.h>

HDC hdc;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT Rect;
	GetWindowRect(hWnd, &Rect);
    switch (message)
    {
	case WM_USER + 1:
	{
		MoveWindow(hWnd, 0, 0, 500, 500, 0); // обычно перемещение окна по координатам, 0 и 0 это х и у верхней левой точки окна, потом 500 и 500 это на сколько растягивается окно вниз и вправо
		break;
	}
	case WM_USER + 2:
	{
	//	PlaySound(TEXT("1.wav"), NULL, SND_FILENAME | SND_SYSTEM ); в теории это должно проигрывать системные звуки, но у меня ничего не работает
		ShowWindow(hWnd, SW_SHOWMAXIMIZED); //ставит окно на фулл экран
		MessageBox(hWnd, TEXT("Различные звуковые сигналы!"), TEXT(""), MB_OK); //замена не работющей функции 
		break;
	}
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow) {
	MSG msg{};
	HWND hwnd{};
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 125));
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
	hwnd = CreateWindow(wc.lpszClassName, L"Lab_1", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, 0, 0, 1000, 1000, NULL, NULL, wc.hInstance, NULL);
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
