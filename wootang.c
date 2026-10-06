#include <stdio.h>
#include <windows.h>
#include "wooting-analog-sdk.h"

#define PROP 2.0f
#define POLL_RATE 5
#define ACCEL_MAX 30.0f
#define KEY_W 0x1a
#define KEY_A 0x04
#define KEY_S 0x16
#define KEY_D 0x07

#define CURVE 4.0f
#define LIN2EXPO(x) (x * x * x * CURVE) //3rd order exponential curve, looks like theres a deadzone for small values, fix low gain on low values


typedef struct keyput
{
    float prev;
    float current;
} keyput;


int main(void) {
    //initialize variables
    float dx, dy, accel;
    float analog_w, analog_a, analog_s, analog_d;
    int init_result;
    keyput x = {0.0f, 0.0f};
    keyput y = {0.0f, 0.0f};
    //windows stuff
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;

    //code
    init_result = wooting_analog_initialise();
    if (init_result < 0 || !wooting_analog_is_initialised()) {
        fprintf(stderr, "Failed to initialize Wooting Analog SDK: %d\n", init_result);
        return 1;
    }

    while (1) {
        //get analog values
        analog_w = wooting_analog_read_analog(KEY_W);
        analog_a = wooting_analog_read_analog(KEY_A);
        analog_s = wooting_analog_read_analog(KEY_S);
        analog_d = wooting_analog_read_analog(KEY_D);

        //error check
        if (analog_w < 0.0f || analog_a < 0.0f ||
            analog_s < 0.0f || analog_d < 0.0f) {
            fprintf(stderr, "Failed to read analog key values.\n");
            wooting_analog_uninitialise();
            return 1;
        }

        dx = analog_d - analog_a;
        dy = analog_s - analog_w;

        //mouse accel
        x.prev = x.current;
        y.prev = y.current;
        x.current = dx;
        y.current = dy;

        accel = 1 + ((x.current - x.prev) + (y.current - y.prev)) / (float)POLL_RATE;

        dx = LIN2EXPO(dx);
        dy = LIN2EXPO(dy);

        input.mi.dx = (LONG)(dx * PROP * accel);
        input.mi.dy = (LONG)(dy * PROP * accel);

        SendInput(1, &input, sizeof(input));
        if (SendInput(1, &input, sizeof(input)) == 0) {
            fprintf(stderr, "SendInput failed: %lu\n", GetLastError());
            wooting_analog_uninitialise();
            return 1;
        }

        Sleep(POLL_RATE);
    }
}
