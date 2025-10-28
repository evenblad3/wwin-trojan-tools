#include <Windows.h>

#include <thread>
#include <chrono>
#include <random>

using namespace std;

#define SCREEN_WIDTH GetSystemMetrics(SM_CXVIRTUALSCREEN)
#define SCREEN_HEIGHT GetSystemMetrics(SM_CYVIRTUALSCREEN)

namespace Wwin
{
    class RandomGenerator
    {
        static std::mt19937 &get_rand_engine()
        {
            static thread_local std::mt19937 engine(std::random_device{}());
            return engine;
        }

    public:
        static int range(int min, int max)
        {
            std::uniform_int_distribution<int> int_dist(min, max);
            return int_dist(get_rand_engine());
        }

        static float range(float min, float max)
        {
            std::uniform_real_distribution<float> real_dist(min, max);
            return real_dist(get_rand_engine());
        }

        static int screenX()
        {
            return RandomGenerator::range(1, SCREEN_WIDTH -1);
        }

        static int screenY()
        {
            return RandomGenerator::range(1, SCREEN_HEIGHT -1);
        }

        static int shakeAmount()
        {
            return RandomGenerator::range(-256, 256);
        }

        static int noiseSize() {
            return RandomGenerator::range(1, 10);
        }

    };

    HDC InitializeMemoryDC(HDC& desktopDC, HBITMAP& hBitmap)
    {
        HDC memoryDC = CreateCompatibleDC(desktopDC);
        hBitmap = CreateCompatibleBitmap(desktopDC, SCREEN_WIDTH, SCREEN_HEIGHT);
        SelectObject(memoryDC, hBitmap);

        return memoryDC;
    }

    void CleanupMemoryDC(HBITMAP hBitmap, HDC memoryDC)
    {
        DeleteObject(hBitmap);
        DeleteDC(memoryDC);
    }

    void ScreenDistortion(const int number, const int delay)
    {
        HBITMAP hBitmap;

        HWND desktopWindow = GetDesktopWindow();
        HDC desktopDC = GetWindowDC(desktopWindow);
        HDC memoryDC = InitializeMemoryDC(desktopDC, hBitmap);

        for (int i = 0; i < number; i++)
        {
            BitBlt(memoryDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, desktopDC, 0, 0, SRCCOPY);
            BitBlt(desktopDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, memoryDC, 1, 1, SRCINVERT);
            UpdateWindow(desktopWindow);

            this_thread::sleep_for(chrono::nanoseconds(delay));
        }

        CleanupMemoryDC(hBitmap, memoryDC);
        ReleaseDC(desktopWindow, desktopDC);
    }

    void ScreenCrazyDistortion(const int number, const int delay)
    {
        HBITMAP hBitmap;

        HWND desktopWindow = GetDesktopWindow();
        HDC desktopDC = GetWindowDC(desktopWindow);
        HDC memoryDC = InitializeMemoryDC(desktopDC, hBitmap);

        for (int i = 0; i < number; i++)
        {
            BitBlt(memoryDC, 0, RandomGenerator::shakeAmount(), SCREEN_WIDTH, SCREEN_HEIGHT, desktopDC, 0, 0, SRCCOPY);
            BitBlt(desktopDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, memoryDC, 0, 0, SRCINVERT);
            PatBlt(desktopDC, RandomGenerator::screenX(), RandomGenerator::screenY(), 0, 0, PATINVERT);

            UpdateWindow(desktopWindow);

            this_thread::sleep_for(chrono::microseconds(delay));
        }

        CleanupMemoryDC(hBitmap, memoryDC);
        ReleaseDC(desktopWindow, desktopDC);
    }

    void ScreenBuffer(const int number, const int delay)
    {
        HBITMAP hBitmap;

        HWND desktopWindow = GetDesktopWindow();
        HDC desktopDC = GetWindowDC(desktopWindow);
        HDC memoryDC = InitializeMemoryDC(desktopDC, hBitmap);

        for (int i = 0; i < number; i++)
        {
            BitBlt(memoryDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, desktopDC, 0, 0, SRCCOPY);
            BitBlt(desktopDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, memoryDC, 0, 0, SRCCOPY);
            UpdateWindow(desktopWindow);

            this_thread::sleep_for(chrono::nanoseconds(delay));
        }

        CleanupMemoryDC(hBitmap, memoryDC);
        ReleaseDC(desktopWindow, desktopDC);
    }

    void ScreenBlink(const int number, const int delay)
    {
        HBITMAP hBitmap;

        HWND desktopWindow = GetDesktopWindow();
        HDC desktopDC = GetWindowDC(desktopWindow);
        HDC memoryDC = InitializeMemoryDC(desktopDC, hBitmap);

        for (int i = 0; i < number; i++)
        {
            BitBlt(memoryDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, desktopDC, 0, 0, SRCCOPY);
            BitBlt(desktopDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, memoryDC, 0, 0, PATINVERT);
            UpdateWindow(desktopWindow);

            this_thread::sleep_for(chrono::nanoseconds(delay));
        }

        CleanupMemoryDC(hBitmap, memoryDC);
        ReleaseDC(desktopWindow, desktopDC);
    }

    void ScreenSlice(const int number, const int delay)
    {
        HBITMAP hBitmap;

        for (int i = 0; i < number; i++)
        {
            HWND desktopWindow = GetDesktopWindow();
            HDC desktopDC = GetWindowDC(desktopWindow);

            BitBlt(desktopDC, RandomGenerator::shakeAmount(), RandomGenerator::shakeAmount(), SCREEN_WIDTH, SCREEN_HEIGHT, desktopDC, 0, 0, SRCCOPY);

            SetROP2(desktopDC, R2_NOTXORPEN);
            Rectangle(desktopDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

            PatBlt(desktopDC, RandomGenerator::screenX(), RandomGenerator::screenY(), RandomGenerator::noiseSize(), RandomGenerator::noiseSize(), PATINVERT);

            ReleaseDC(desktopWindow, desktopDC);
            this_thread::sleep_for(chrono::nanoseconds(delay));
        }
    }

    void ScreenZoom(const int number, const int delay)
    {
        HBITMAP hBitmap;

        HWND desktopWindow = GetDesktopWindow();
        HDC desktopDC = GetWindowDC(desktopWindow);
        HDC memoryDC = InitializeMemoryDC(desktopDC, hBitmap);

        for (int i = SCREEN_WIDTH; i > 0; i -= 10)
        {
            BitBlt(memoryDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, desktopDC, 0, 0, SRCCOPY);
            StretchBlt(desktopDC, i / 2, 0, SCREEN_WIDTH - i, SCREEN_HEIGHT, memoryDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SRCCOPY);

            UpdateWindow(desktopWindow);

            this_thread::sleep_for(chrono::nanoseconds(delay));
        }

        CleanupMemoryDC(hBitmap, memoryDC);
        ReleaseDC(desktopWindow, desktopDC);
    }
}
