
#include "ric.h"

void func_8015C2A8(void) {
    bool loadAnim = 0;
    s32 temp;

    FntPrint("pl_vram_flag:%04x\n", g_Player.pl_vram_flag);
    FntPrint("pl_high_jump_timer:%04x\n", g_Player.pl_high_jump_timer);
    FntPrint("pl_step_s:%02x\n", PLAYER.step_s);
    g_Player.pl_high_jump_timer++;

    switch (PLAYER.step_s) {
    case 0:
        if (g_Player.padPressed & (PAD_LEFT | PAD_RIGHT)) {
            if (PLAYER.facingLeft == 0) {
                temp = g_Player.padPressed & PAD_RIGHT;
            } else {
                temp = g_Player.padPressed & PAD_LEFT;
            }
            if (temp == 0) {
                func_8015C93C(0x1000);
            }
        } else {
            func_8015C93C(0x1000);
        }

        if (g_Player.pl_vram_flag & 2) {
            func_80158B04(3);
            g_Player.pl_high_jump_timer = 0;
            PLAYER.step_s = 2;
        } else if (g_Player.pl_high_jump_timer >= 0x1D) {
            PLAYER.step_s = 1;
            PLAYER.velocityY = -0x60000;
        }
        break;

    case 1:
        if (g_Player.pl_vram_flag & 2) {
            PLAYER.step_s = 2;
            func_80158B04(3);
            g_Player.pl_high_jump_timer = 0;
        } else {
            PLAYER.velocityY += 0x6000;
            if (PLAYER.velocityY > 0x8000) {
                loadAnim = true;
            }
        }
        break;

    case 2:
        if (g_Player.pl_high_jump_timer >= 5) {
            loadAnim = true;
        }
        break;
    }

    if (loadAnim) {
        func_8015C920(&D_80155534);
        SetPlayerStep(4);
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/202A8", func_8015C4AC);

INCLUDE_ASM("asm/us/ric/nonmatchings/202A8", func_8015C6D4);

void SetPlayerStep(PlayerSteps step) {
    PLAYER.step = step;
    PLAYER.step_s = 0;
}
