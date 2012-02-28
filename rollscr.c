#include <windows.h>

#define MIN 4
#define MAX 30
#define INTERVAL 3
#define LAST 50

enum Speed {Up, Down};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	HDC hdcScr, hdcMem;
	int cxScreen, cyScreen, div, len;
	int i, count;
	int last;
	enum Speed speed;
	HBITMAP hBitmap;
	HWND hwnd;
/*	TCHAR szbuf[100];*/
	if (LockWindowUpdate(hwnd = GetDesktopWindow())) {
		hdcScr = GetDCEx(hwnd, NULL, DCX_CACHE | DCX_LOCKWINDOWUPDATE);
		hdcMem = CreateCompatibleDC(hdcScr);
		cxScreen = GetSystemMetrics(SM_CXSCREEN);
		cyScreen = GetSystemMetrics(SM_CYSCREEN);
		hBitmap = CreateCompatibleBitmap(hdcScr, cxScreen, cyScreen);
		SelectObject(hdcMem, hBitmap);

		div = MAX;
		last = LAST;
		speed = Up;
		count = ((MAX - MIN) * 2 - 1) * INTERVAL + LAST;
		len = cxScreen / div;

		for (i = 0; i < count; i++) {
			if (GetAsyncKeyState(VK_ESCAPE) < 0)
				goto EXIT;

			BitBlt(hdcMem, 0, 0, cxScreen - len, cyScreen, hdcScr, len, 0, SRCCOPY);
			BitBlt(hdcMem, cxScreen - len, 0, len, cyScreen, hdcScr, 0, 0, SRCCOPY);
			BitBlt(hdcScr, 0, 0, cxScreen, cyScreen, hdcMem, 0, 0, SRCCOPY);

			if (speed == Up && div > MIN) {
				if (!(i % INTERVAL))
					len = cxScreen / div--;
			}
			else
				speed = Down;

			if (speed == Down && div == MIN && last-- > 0)
				continue;
			
			if (speed == Down && div < MAX) {
				if (!(i % INTERVAL))
					len = cxScreen / div++;

			}
		}

		speed = Up;
		last = LAST;
		len = cxScreen / div;
		for (i = 0; i < count; i++) {
			if (GetAsyncKeyState(VK_ESCAPE) < 0)
				goto EXIT;

			BitBlt(hdcMem, len, 0, cxScreen - len, cyScreen, hdcScr, 0, 0, SRCCOPY);
			BitBlt(hdcMem, 0, 0, len, cyScreen, hdcScr, cxScreen - len, 0, SRCCOPY);
			BitBlt(hdcScr, 0, 0, cxScreen, cyScreen, hdcMem, 0, 0, SRCCOPY);
			
			if (speed == Up && div > MIN) {
				if (!(i % INTERVAL))
					len = cxScreen / div--;
			}
			else
				speed = Down;
			
			if (speed == Down && div == MIN && last-- > 0)
				continue;
			
			if (speed == Down && div < MAX) {
				if (!(i % INTERVAL))
					len = cxScreen / div++;
				
			}
		}
		
		InvalidateRect(hwnd, NULL, TRUE);
		speed = Up;
		last = LAST;
		len = cyScreen / div;
		for (i = 0; i < count; i++) {
			if (GetAsyncKeyState(VK_ESCAPE) < 0)
				goto EXIT;

			BitBlt(hdcMem, 0, 0, cxScreen, cyScreen - len, hdcScr, 0, len, SRCCOPY);
			BitBlt(hdcMem, 0, cyScreen - len, cxScreen, len, hdcScr, 0, 0, SRCCOPY);
			BitBlt(hdcScr, 0, 0, cxScreen, cyScreen, hdcMem, 0, 0, SRCCOPY);
			
			if (speed == Up && div > MIN) {
				if (!(i % INTERVAL))
					len = cxScreen / div--;
			}
			else
				speed = Down;
			
			if (speed == Down && div == MIN && last-- > 0)
				continue;
			
			if (speed == Down && div < MAX) {
				if (!(i % INTERVAL))
					len = cxScreen / div++;
				
			}
		}

		speed = Up;
		last = LAST;
		len = cyScreen / div;
		for (i = 0; i < count; i++) {
			if (GetAsyncKeyState(VK_ESCAPE) < 0)
				goto EXIT;

			BitBlt(hdcMem, 0, 0, cxScreen, len, hdcScr, 0, cyScreen - len, SRCCOPY);
			BitBlt(hdcMem, 0, len, cxScreen, cyScreen - len, hdcScr, 0, 0, SRCCOPY);
			BitBlt(hdcScr, 0, 0, cxScreen, cyScreen, hdcMem, 0, 0, SRCCOPY);
			
			if (speed == Up && div > MIN) {
				if (!(i % INTERVAL))
					len = cxScreen / div--;
			}
			else
				speed = Down;
			
			if (speed == Down && div == MIN && last-- > 0)
				continue;
			
			if (speed == Down && div < MAX) {
				if (!(i % INTERVAL))
					len = cxScreen / div++;
				
			}
		}

EXIT:
		InvalidateRect(hwnd, NULL, TRUE);
// 		wsprintf(szbuf, "The div is %d.", div);
// 		MessageBox(NULL, szbuf, NULL, 0);
		DeleteDC(hdcMem);
		ReleaseDC(hwnd, hdcScr);
		DeleteObject(hBitmap);
		LockWindowUpdate(NULL);
	}

	return 0;
}

                    
