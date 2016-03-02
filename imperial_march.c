// SYSTEM BUS RADIO
// https://github.com/fulldecent/system-bus-radio
// Copyright 2016 William Entriken

#include <stdio.h>
#include <emmintrin.h>
#include <mach/mach_traps.h>
#include <mach/mach_time.h>
#include <math.h>

__m128i reg;
__m128i reg_zero;
__m128i reg_one;
mach_port_t clock_port;
mach_timespec_t remain;

static inline void square_am_signal(float time, float frequency) {
    printf("Playing / %0.3f seconds / %4.0f Hz\n", time, frequency);
    uint64_t period = NSEC_PER_SEC / frequency;

    uint64_t start = mach_absolute_time();
    uint64_t end = start + time * NSEC_PER_SEC;

    while (mach_absolute_time() < end) {
        uint64_t mid = start + period / 2;
        uint64_t reset = start + period;
        while (mach_absolute_time() < mid) {
            _mm_stream_si128(&reg, reg_one);
            _mm_stream_si128(&reg, reg_zero);
        }
        clock_sleep_trap(clock_port, TIME_ABSOLUTE, reset / NSEC_PER_SEC, reset % NSEC_PER_SEC, &remain);
        start = reset;
    }
}

int main()
{
    mach_timebase_info_data_t theTimeBaseInfo;
    mach_timebase_info(&theTimeBaseInfo);
    puts("TESTING TIME BASE: the following should be 1 / 1");
    printf("  Mach base: %u / %u nanoseconds\n\n", theTimeBaseInfo.numer, theTimeBaseInfo.denom);

    uint64_t start = mach_absolute_time();
    uint64_t end = mach_absolute_time();
    printf("TESTING TIME TO EXECUTE mach_absolute_time()\n  Result: %lld nanoseconds\n\n", end - start);

    reg_zero = _mm_set_epi32(0, 0, 0, 0);
    reg_one = _mm_set_epi32(-1, -1, -1, -1);

    while (1) {
        square_am_signal(0.500, 1760);
        square_am_signal(0.500, 1760);
        square_am_signal(0.500, 1760);
        square_am_signal(0.375, 1337);
        square_am_signal(0.125, 2093);
        square_am_signal(0.500, 1760);
        square_am_signal(0.375, 1337);
        square_am_signal(0.125, 2093);
        square_am_signal(1.000, 1760);
        square_am_signal(0.500, 2637);
        square_am_signal(0.500, 2637);
        square_am_signal(0.500, 2637);
        square_am_signal(0.375, 2794);
        square_am_signal(0.125, 2093);
        square_am_signal(0.500, 1661);
        square_am_signal(0.375, 1337);
        square_am_signal(0.125, 2093);
        square_am_signal(1.000, 1760);
        square_am_signal(0.500, 3520);
        square_am_signal(0.375, 1760);
        square_am_signal(0.125, 1760);
        square_am_signal(0.500, 3520);
        square_am_signal(0.375, 3322);
        square_am_signal(0.125, 3136);
        square_am_signal(0.125, 2960);
        square_am_signal(0.125, 2637);
        square_am_signal(0.250, 2794);
        square_am_signal(0.250, 1865);
        square_am_signal(0.500, 2489);
        square_am_signal(0.375, 2349);
        square_am_signal(0.125, 2217);
        square_am_signal(0.125, 2093);
        square_am_signal(0.125, 1976);
        square_am_signal(0.250, 2093);
        square_am_signal(0.250, 1337);
        square_am_signal(0.500, 1661);
        square_am_signal(0.375, 1337);
        square_am_signal(0.125, 1760);
        square_am_signal(0.500, 2093);
        square_am_signal(0.375, 1760);
        square_am_signal(0.125, 2093);
        square_am_signal(1.000, 2637);
        square_am_signal(0.500, 3520);
        square_am_signal(0.375, 1760);
        square_am_signal(0.125, 1760);
        square_am_signal(0.500, 3520);
        square_am_signal(0.375, 3322);
        square_am_signal(0.125, 3136);
        square_am_signal(0.125, 2960);
        square_am_signal(0.125, 2637);
        square_am_signal(0.250, 2794);
        square_am_signal(0.250, 1865);
        square_am_signal(0.500, 2489);
        square_am_signal(0.375, 2349);
        square_am_signal(0.125, 2217);
        square_am_signal(0.125, 2093);
        square_am_signal(0.125, 1976);
        square_am_signal(0.250, 2093);
        square_am_signal(0.250, 1337);
        square_am_signal(0.500, 1661);
        square_am_signal(0.375, 1337);
        square_am_signal(0.125, 2093);
        square_am_signal(0.500, 1760);
        square_am_signal(0.375, 1337);
        square_am_signal(0.125, 2093);
        square_am_signal(1.000, 1760);
    }
}
