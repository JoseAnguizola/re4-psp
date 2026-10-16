#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>

PSP_MODULE_INFO("RE4", 0, 0, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

static volatile int running = 1;

static int exit_callback(int arg1, int arg2, void *common)
{
    (void)arg1;
    (void)arg2;
    (void)common;
    running = 0;
    return 0;
}

static int callback_thread(SceSize args, void *argp)
{
    (void)args;
    (void)argp;
    int cbid = sceKernelCreateCallback("exit_callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

static void setup_callbacks(void)
{
    int thid = sceKernelCreateThread("callback_thread", callback_thread, 0x11, 0xFA0, 0, NULL);
    if (thid >= 0)
        sceKernelStartThread(thid, 0, NULL);
}

int main(void)
{
    setup_callbacks();
    pspDebugScreenInit();

    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    SceCtrlData pad;
    while (running) {
        sceCtrlReadBufferPositive(&pad, 1);

        pspDebugScreenSetXY(0, 0);
        pspDebugScreenPrintf("Resident Evil 4 PSP - toolchain check\n\n");
        pspDebugScreenPrintf("Analog: %3d %3d\n", pad.Lx, pad.Ly);
        pspDebugScreenPrintf("Buttons: 0x%08X\n\n", pad.Buttons);
        pspDebugScreenPrintf("Press HOME to quit.\n");

        sceDisplayWaitVblankStart();
    }

    sceKernelExitGame();
    return 0;
}
