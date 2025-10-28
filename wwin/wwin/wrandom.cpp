#include <Windows.h>

#include <random>
#include "wrandom.h"

#define SCREEN_WIDTH GetSystemMetrics(SM_CXVIRTUALSCREEN)
#define SCREEN_HEIGHT GetSystemMetrics(SM_CYVIRTUALSCREEN)

static std::mt19937 &get_rand_engine()
{
    static thread_local std::mt19937 engine(std::random_device{}());
    return engine;
}

int Wwin::RandomGenerator::range(int min, int max)
{
    std::uniform_int_distribution<int> int_dist(min, max);
    return int_dist(get_rand_engine());
}

float Wwin::RandomGenerator::range(float min, float max)
{
    std::uniform_real_distribution<float> real_dist(min, max);
    return real_dist(get_rand_engine());
}

int Wwin::RandomGenerator::screenX()
{
    return Wwin::RandomGenerator::range(1, SCREEN_WIDTH - 1);
}

int Wwin::RandomGenerator::screenY()
{
    return Wwin::RandomGenerator::range(1, SCREEN_HEIGHT - 1);
}

int Wwin::RandomGenerator::shakeAmount()
{
    return Wwin::RandomGenerator::range(-256, 256);
}

int Wwin::RandomGenerator::noiseSize()
{
    return Wwin::RandomGenerator::range(1, 10);
}
