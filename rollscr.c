#include <windows.h>

#define MIN 4
#define MAX 30
#define INTERVAL 3
#define LAST 50

enum Speed {Up, Down};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	HDC hdcScr, hdcMem;
	//cScreen[0] = cxScreen, cScreen[1] = cyScreen
	int cScreen[2], div, len;
	int i, count;
	int last;
	int direction, dirdiv2;
	enum Speed speed;
	HBITMAP hBitmap;
	HWND hwnd;

	if (LockWindowUpdate(hwnd = GetDesktopWindow())) {
		hdcScr = GetDCEx(hwnd, NULL, DCX_CACHE | DCX_LOCKWINDOWUPDATE);
		hdcMem = CreateCompatibleDC(hdcScr);
		cScreen[0] = GetSystemMetrics(SM_CXSCREEN);
		cScreen[1] = GetSystemMetrics(SM_CYSCREEN);
		hBitmap = CreateCompatibleBitmap(hdcScr, cScreen[0], cScreen[1]);
		SelectObject(hdcMem, hBitmap);

		div = MAX;
		count = ((MAX - MIN) * 2 - 1) * INTERVAL + LAST;
		for (direction = 0; direction < 4; direction++) {
			last = LAST;
			speed = Up;
			
			dirdiv2 = direction / 2;

			len = cScreen[dirdiv2] / div;
			
			for (i = 0; i < count; i++) {
				if (GetAsyncKeyState(VK_ESCAPE) < 0)
					goto EXIT;

				if (dirdiv2) {
					
					BitBlt(hdcMem, 0, 0, cScreen[0], (cScreen[1] - len) % cScreen[1], hdcScr, 0, (cScreen[1] + len) % cScreen[1], SRCCOPY);
					BitBlt(hdcMem, 0, (cScreen[1] - len) % cScreen[1], cScreen[0], (cScreen[1] + len) % cScreen[1], hdcScr, 0, 0, SRCCOPY);
					BitBlt(hdcScr, 0, 0, cScreen[0], cScreen[1], hdcMem, 0, 0, SRCCOPY);
				}
				else {
					BitBlt(hdcMem, 0, 0, (cScreen[0] - len) % cScreen[0], cScreen[1], hdcScr, (cScreen[0] + len) % cScreen[0], 0, SRCCOPY);
					BitBlt(hdcMem, (cScreen[0] - len) % cScreen[0], 0, (cScreen[0] + len) % cScreen[0], cScreen[1], hdcScr, 0, 0, SRCCOPY);
					BitBlt(hdcScr, 0, 0, cScreen[0], cScreen[1], hdcMem, 0, 0, SRCCOPY);
				}

				if (speed == Up && div > MIN) {
					if (!(i % INTERVAL))
						len = ((direction % 2)? -1 : 1) * cScreen[dirdiv2] / div--;
				}
				else
					speed = Down;
				
				if (speed == Down && div == MIN && last-- > 0)
					continue;
				
				if (speed == Down && div < MAX) {
					if (!(i % INTERVAL))
						len = ((direction % 2)? -1 : 1) * cScreen[dirdiv2] / div++;				
				}
			}
		}

EXIT:
		InvalidateRect(hwnd, NULL, TRUE);
		DeleteDC(hdcMem);
		ReleaseDC(hwnd, hdcScr);
		DeleteObject(hBitmap);
		LockWindowUpdate(NULL);
	}

	return 0;
}

                    
