#include <windows.h>
#include <iostream>
using namespace std;

DWORD WINAPI internal_loop(LPVOID lpParam)
{

    INT HP_MAX = 10000;
    INT DRIVE_MAX = 60000;
    INT SUPER_MAX = 30000;
    CHAR TIMER_INF= 1;
    CHAR TIMER_NORMAL = 2;
    INT P1HP = HP_MAX;
    INT P2HP = HP_MAX;
    INT P1DRIVE = DRIVE_MAX;
    INT P2DRIVE = DRIVE_MAX;
    INT P1SUPER = SUPER_MAX;
    INT P2SUPER = SUPER_MAX;
    LPVOID TIMER_ADDRESS = (void*)(0x20003AB655C);
    LPVOID P1HPADDRESS = (void*)(0x20001431D20);
    LPVOID P2HPADDRESS = (void*)(0x20001432720);
    LPVOID P1DRIVEADDRESS = (void*)(0x20001431D30);
    LPVOID P2DRIVEADDRESS = (void*)(0x20001432730);
    LPVOID P1SUPERADDRESS = (void*)(0x20003B55300);
    LPVOID P2SUPERADDRESS = (void*)(0x20003B553E0);

    bool TimerInfEnabled = false;
    bool HPFreeze = false;
    bool DriveFreeze = false;
    bool SuperFreeze = false;

    HANDLE sf6 = GetCurrentProcess();

    while (1) {
        if (GetAsyncKeyState(VK_F1) & 0x80000) {
            Beep(523, 100);
            TimerInfEnabled = !TimerInfEnabled;
        }
        if (GetAsyncKeyState(VK_F2) & 0x80000) {
            HPFreeze = !HPFreeze;
            Beep(523, 100);
            if (HPFreeze == true) {
                P1HP = *(uint32_t*)P1HPADDRESS;
                P2HP = *(uint32_t*)P2HPADDRESS;
            }
        }
        if (GetAsyncKeyState(VK_F3) & 0x80000) {
            Beep(523, 100);
            DriveFreeze = !DriveFreeze;
            if (DriveFreeze == true) {
                P1DRIVE = *(uint32_t*)P1DRIVEADDRESS;
                P2DRIVE = *(uint32_t*)P2DRIVEADDRESS;
            }
        }
        if (GetAsyncKeyState(VK_F4) & 0x80000) {
            Beep(523, 100);
            SuperFreeze = !SuperFreeze;
            if (SuperFreeze == true) {
                P1SUPER = *(uint32_t*)P1SUPERADDRESS;
                P2SUPER = *(uint32_t*)P2SUPERADDRESS;
            }
        }
        if (GetAsyncKeyState(VK_F5) & 0x80000) {
            Beep(523, 100);
            *(uint32_t*)P1HPADDRESS = HP_MAX;
            *(uint32_t*)P2HPADDRESS = HP_MAX;
            *(uint32_t*)P1DRIVEADDRESS = DRIVE_MAX;
            *(uint32_t*)P2DRIVEADDRESS = DRIVE_MAX;
            *(uint32_t*)P1SUPERADDRESS = SUPER_MAX;
            *(uint32_t*)P2SUPERADDRESS = SUPER_MAX;
        }

        if (TimerInfEnabled == true) {
            *(uint8_t*)TIMER_ADDRESS = TIMER_INF;
        }
        if (HPFreeze == true) {
            *(uint32_t*)P1HPADDRESS = P1HP;
            *(uint32_t*)P2HPADDRESS = P2HP;
        }
        if (DriveFreeze == true) {
            *(uint32_t*)P1DRIVEADDRESS = P1DRIVE;
            *(uint32_t*)P2DRIVEADDRESS = P2DRIVE;
        }
        if (SuperFreeze == true) {
            *(uint32_t*)P1SUPERADDRESS = P1SUPER;
            *(uint32_t*)P2SUPERADDRESS = P2SUPER;
        }
        Sleep(200);
    }
}


BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwAttached, LPVOID lpvReserved)
{
    if (dwAttached == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, &internal_loop, NULL, 0, NULL);
    }
    return 1;
}