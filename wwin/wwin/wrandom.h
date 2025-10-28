#pragma once

namespace Wwin
{
    class RandomGenerator
    {
    public:
        static int range(int min, int max);

        static float range(float min, float max);

        static int screenX();

        static int screenY();

        static int shakeAmount();

        static int noiseSize();
    };
}
