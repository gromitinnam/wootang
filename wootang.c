#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <wooting-analog-sdk.h>

#define M_PI 3.1415926
#define PROP 100.0f
#define KEY_W 0x1a
#define KEY_A 0x04
#define KEY_S 0x16
#define KEY_D 0x07

int main() {
    float dx, dy, accel;

    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;

    wooting_analog_initialise();
    if (!wooting_analog_is_initialised()) {return 1;}

    while (1) {
        wooting_analog_read_full_buffer_device(*analog_buffer);
        dx = wooting_analog_read_analog(analog_buffer[KEY_D]) - wooting_analog_read_analog(analog_buffer[KEY_A]);
        dy = wooting_analog_read_analog(analog_buffer[KEY_W]) - wooting_analog_read_analog(analog_buffer[KEY_S]);


        input.mi.dx = (LONG)(dx * PROP * accel);
        input.mi.dy = (LONG)(dy * PROP * accel);
        
        SendInput(1, &input, sizeof(INPUT));

        Sleep(5);
    }
    return 0;
}

