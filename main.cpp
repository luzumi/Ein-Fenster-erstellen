#include <windows.h>
#include <cassert>

//Funktion zum abfangen und auswerten der Events (z.B. Tatstaureingaben)
LRESULT CALLBACK MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	HWND hWnd;
	WNDCLASS wc;
	MSG msg;

	wc = {};							//setzt alle Einstellungen für das Fenster auf 0 (standard)
	wc.style = CS_HREDRAW | CS_VREDRAW;				//Bei FenstergrößenAENDERUNG ZEICHNET WIN DAS KOMPLETTE FENSTER NEU
	wc.lpfnWndProc = MessageHandler;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;						//Infos unter https://docs.microsoft.com/de-de/windows/win32/api/
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			//Standard logo (verkürzt geschrieben "= NULL")
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			//Standard Cursor (verkürzt geschrieben "= NULL")
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		//bei "= NULL" muss man selber den backgorund erstellen 
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"WINAPI-TEST";

	assert(RegisterClass(&wc));

	hWnd = CreateWindow(L"WINAPI-TEST", L"WinApiTutorial", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	ShowCursor (true);
	UpdateWindow(hWnd);

	while (true) 
	{

		BOOL result = GetMessage(&msg, NULL, NULL, NULL);
		if (result > 0) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			return result;
		}
	}
}



