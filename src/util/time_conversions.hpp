#ifndef TIME_CONVERSIONS
#define TIME_CONVERSIONS

float ticksToSeconds(unsigned ticks)
{
    return ticks / 1000.0f;
}

unsigned secondsToTicks(float seconds)
{
    return (unsigned)(seconds * 1000);
}

#endif // TIME_CONVERSIONS
