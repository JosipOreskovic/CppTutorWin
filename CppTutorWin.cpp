// Program koji kreira jednostavan prozor

#include <Windows.h>

// Prototip funkcije s Windows procedurama

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

// Ime klase prozora

static wchar_t gszClassName[] = L"MojaKlasaProzora";

// Funkcija WinMain

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
	WNDCLASSEX WndClass;
	HWND hwnd;
	MSG Msg;

	// Registriranje klase prozora

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = NULL;
	WndClass.lpfnWndProc = WindowProcedure;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = gszClassName;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// Provjera je li klasa registrirana

	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(0, L"Registriranje prozora nije uspjelo", L"Greska!", MB_ICONSTOP | MB_OK);
		return 0;
	}

	// Kreiranje prozora

	hwnd = CreateWindowEx(WS_EX_STATICEDGE, gszClassName, L"Naslov", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 400, NULL, NULL, hInstance, NULL);

	// Provjera je li prozor uspjesno kreiran

	if (hwnd == NULL)
	{
		MessageBox(0, L"Kreiranje prozora nije uspjelo", L"Greska!", MB_ICONSTOP | MB_OK);
		return 0;
	}

	// Prikazivanje prozora na ekranu

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Petlja koja obradjuje poruke

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	// Odjava klase prozora

	UnregisterClass(L"MojaKlasaProzora", hInstance);

	return Msg.wParam;

}

// Funkcija s Windows procedurama

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
		break;
	}
	return 0;
}