
#define WINVER 0x0500
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main (void) {

    FILE *fp;
    int X, Y, A;
    char c;
    int XKey, YKey, AKey;
    unsigned char keys[15]={0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F};

    // This structure will be used to create the keyboard
    // input event.
    INPUT ip;
    Sleep(5000);
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;


    while (1)
    {
        fp = fopen("data.asc", "r" );
        fseek(fp, -30, SEEK_END);
        do {
            c=fgetc(fp);
        } while (c!='\n');
        fscanf(fp, "%d %d %d", &X, &Y, &A);
        fclose(fp);

        XKey=keys[X];
        YKey=keys[Y+5];
        AKey=keys[A+10];

        // Press and release a key
        ip.ki.wVk = XKey; 
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));

	Sleep(33);

        ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
        SendInput(1, &ip, sizeof(INPUT));

        // Press and release a key
        ip.ki.wVk = YKey; 
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));

	Sleep(33);

        ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
        SendInput(1, &ip, sizeof(INPUT));

        // Press and release a key
        ip.ki.wVk = AKey; 
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));

	Sleep(33);

        ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
        SendInput(1, &ip, sizeof(INPUT));

    }

    return 0;
}
