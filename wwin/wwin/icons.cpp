#include <Windows.h>

#include <vector>

#include <thread>
#include <chrono>
#include "wrandom.h"

using namespace std;

#define SCREEN_WIDTH GetSystemMetrics(SM_CXVIRTUALSCREEN)
#define SCREEN_HEIGHT GetSystemMetrics(SM_CXVIRTUALSCREEN)

vector<HICON> icons = {
    LoadIcon(NULL, IDI_ERROR), LoadIcon(NULL, IDI_WARNING), LoadIcon(NULL, IDI_QUESTION), LoadIcon(NULL, IDI_INFORMATION)
};

namespace Wwin
{
    void IconNoise(int number, int delay)
    {
        for (int i = 0; i < number; i++)
        {
            HWND hWnd = GetDesktopWindow();
            HDC hdc = GetWindowDC(hWnd);

            DrawIcon(hdc, RandomGenerator::screenX(), RandomGenerator::screenY(), icons[RandomGenerator::range(0, icons.size() - 1)]);

            ReleaseDC(hWnd, hdc);
            this_thread::sleep_for(chrono::nanoseconds(delay));
        }
    }

    void IconSizebleNoise(int number, int maxIconSize, int delay)
    {
        for (int i = 0; i < number; i++)
        {
            HWND hWnd = GetDesktopWindow();
            HDC hdc = GetWindowDC(hWnd);

            int x = RandomGenerator::screenX();
            int y = RandomGenerator::screenY();

            HICON icon = icons[RandomGenerator::range(0, icons.size() - 1)];
            int iconSize = RandomGenerator::range(0, maxIconSize);

            DrawIconEx(hdc, x, y, icon, iconSize, iconSize, 0, NULL, DI_NORMAL);

            ReleaseDC(hWnd, hdc);
            this_thread::sleep_for(chrono::nanoseconds(delay));
        }
    }

    void IconCursorNoise(int number, int delay)
    {
        for (int i = 0; i < number; i++)
        {
            HWND hWnd = GetDesktopWindow();
            HDC hdc = GetWindowDC(hWnd);

            POINT cursorPos;
            GetCursorPos(&cursorPos);

            DrawIcon(hdc, cursorPos.x, cursorPos.y, icons[RandomGenerator::range(0, icons.size() - 1)]);

            ReleaseDC(hWnd, hdc);
            this_thread::sleep_for(chrono::nanoseconds(delay));
        }
    }
}
