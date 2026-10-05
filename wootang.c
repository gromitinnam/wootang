#include <stdio.h>
#include <windows.h>
#include "wooting-analog-sdk.h"

#define PROP 10.0f
#define KEY_W 0x1a
#define KEY_A 0x04
#define KEY_S 0x16
#define KEY_D 0x07

#define curve 1.0f
#define lin2expo(x) (x * (1.0f - curve) + (x * x * x) * curve)

int main(void) {
    float dx, dy;
    float analog_w, analog_a, analog_s, analog_d;
    int init_result;
    
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;

    init_result = wooting_analog_initialise();
    if (init_result < 0 || !wooting_analog_is_initialised()) {
        fprintf(stderr, "Failed to initialize Wooting Analog SDK: %d\n", init_result);
        return 1;
    }

    while (1) {
        analog_w = wooting_analog_read_analog(KEY_W);
        analog_a = wooting_analog_read_analog(KEY_A);
        analog_s = wooting_analog_read_analog(KEY_S);
        analog_d = wooting_analog_read_analog(KEY_D);

        if (analog_w < 0.0f || analog_a < 0.0f ||
            analog_s < 0.0f || analog_d < 0.0f) {
            fprintf(stderr, "Failed to read analog key values.\n");
            wooting_analog_uninitialise();
            return 1;
        }

        dx = analog_d - analog_a;
        dy = analog_s - analog_w;

        dx = lin2expo(dx * PROP);
        dy = lin2expo(dy* PROP);

        input.mi.dx = (LONG)(dx);
        input.mi.dy = (LONG)(dy);

        if (SendInput(1, &input, sizeof(input)) == 0) {
            fprintf(stderr, "SendInput failed: %lu\n", GetLastError());
            wooting_analog_uninitialise();
            return 1;
        }

        Sleep(5);
    }
}
