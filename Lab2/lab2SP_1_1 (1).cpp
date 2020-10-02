
//#include <stdafx.h>
#include <Windows.h>

HDC hdc;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hWnd2 = FindWindow(0, _T("lab2_2")); //функция которая ищет открытые приложения, в данном случае по названию приложения 
    switch (message)
    {
	case WM_LBUTTONDOWN: //кейс который активируется при нажатии  левой кнопки мыши
	{
		if (hWnd2)
		{
			MessageBox(hWnd, TEXT("Дескриптор найден!"), TEXT("Сообщение из первого приложения"), MB_OK); //если приложение №2 открыто выдается сообщение после чего идет отправка дескриптора во второе приложение
			PostMessage(hWnd2, WM_USER + 1, (WPARAM)hWnd, lParam);  //функция передает в кейс вм_юзер+1, во втором приложении свой дескриптор
			MessageBox(hWnd, TEXT("Дескриптор передан!"), TEXT("Сообщение из первого приложения"), MB_OK);
		}
		else
			MessageBox(hWnd, TEXT("Дескриптор не найден!"), TEXT("Сообщение из первого приложения"), MB_OK);// если приложение №2 не открыто 

		break;
	}
	case WM_RBUTTONDOWN:
	{
		PostMessage(hWnd2, WM_USER + 2, (WPARAM)hWnd, lParam);// отправка сообщения во второе приложение в кейс юзер + 2
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
