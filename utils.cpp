#include <stdlib.h>
#include <time.h>

#define RAND_MIN 32767

float map(float x, float minx, float maxx, float miny, float maxy)
{
    return (x - minx) * (maxy - miny) / (maxx - minx) + miny;
}

bool pileOuFace(float p_de_face)
    {
        srand(time(NULL));
        
        if (map(rand(), RAND_MIN, RAND_MAX, 0.0f, 1.0f) > p_de_face)
        {
            return false;
        }
        return true;
    }

int randomInt(int min, int max)
{
    srand(time(NULL));
    return (int)map(rand(), RAND_MIN, RAND_MAX, min, max);
}

float randomFloat(float min, float max)
{
    srand(time(NULL));
    return map(rand(), RAND_MIN, RAND_MAX, min, max);
}