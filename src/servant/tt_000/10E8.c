#include "servant.h"
#include "sfx.h"

#define SFX_BAT_SCREECH SOUND_BAT_SCREECH
#define SFX_BAT_NOTIFY SE_UI_OVERWRITE_MSG

extern s32 D_801748D8[0x80];
extern Collider D_80174AD8;
extern s16 D_80174AFC;
extern s16 D_80174B00;
extern s16 D_80174B04;
extern s16 D_80174B08;
extern s16 D_80174B0C;
extern s16 D_80174B10;
extern s16 D_80174B14;
extern s16 D_80174B18;
extern s32 D_80174B1C;
extern s32 D_80174B20;
extern s32 D_80174B24;
extern s32 D_80174B28;
extern s32 D_80174B2C;
extern s32 D_80174B2C;
extern s32 D_80174B30;
extern s32 D_80174B34;
extern s16 D_80174B38;
extern s16 D_80174B3C;
extern s16 D_80174B40;
extern s16 D_80174B44;
extern Primitive* D_80174B48;
extern s32 D_80174B4C[16];
extern Point16 D_80174B8C[16];
extern s16 D_80174BCC[16];
extern s16 D_80174BEC[16];
extern s16 D_80174C0C[16];
extern s32 D_80174C2C;
extern Unkstruct_8011A3AC D_80174C30;
extern Point16 D_80174C3C[4][16];
extern s32 D_80174D3C;
extern s32 D_80174D40;
extern s32 D_80170514[];

void func_80171ED4(s32 arg0);
void func_80172120(Entity* self);
void func_80172C30(Entity* self);
void func_8017339C(void);
void func_801733A4(void);
void func_801733AC(void);
void func_801733B4(void);
void func_801733BC(void);
void func_801733C4(void);
void func_801733CC(void);
void func_801733D4(Entity* self);
void func_80173C0C(void);
void func_80173C14(void);
void func_80173C1C(void);
void func_80173C24(void);
void func_80173C2C(Entity* self);

ServantDesc g_ServantDesc = {
    func_80171ED4, func_80172120, func_80172C30, func_8017339C,
    func_801733A4, func_801733AC, func_801733B4, func_801733BC,
    func_801733C4, func_801733CC, func_801733D4, func_80173C0C,
    func_80173C14, func_80173C1C, func_80173C24, func_80173C2C,
};

void func_801710E8(Entity* entity, s32* arg1) {
    if (entity->unk4C != arg1) {
        entity->unk4C = arg1;
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
    }
}

Entity* func_8017110C(Entity* self) {
    const int EntitySearchCount = 128;
    s32 foundIndex;
    s32 i;
    u32 found;
    Entity* e;
    s32 distance;
    s32 entityX;
    s32 selfX;

    found = 0;
    e = &g_Entities[STAGE_ENTITY_START];
    for (i = 0; i < EntitySearchCount; i++, e++) {
        D_801748D8[i] = 0;
        if (e->entityId == 0) {
            continue;
        }
        if (e->hitboxState == 0) {
            continue;
        }
        if (e->flags & FLAG_UNK_00200000) {
            continue;
        }

        entityX = e->posX.i.hi;
        if (entityX < -0x10) {
            continue;
        }
        if (entityX > 0x110) {
            continue;
        }
        if (e->posY.i.hi > 0xF0) {
            continue;
        }
        if (e->posY.i.hi < 0) {
            continue;
        }
        if (e->hitboxState & 8 && D_80170658[D_80174C30.unk0 / 10][4] == 0) {
            continue;
        }

        selfX = self->posX.i.hi;
        distance = self->posX.i.hi - entityX;
        if (distance < 0) {
            distance = -distance;
        }
        if (distance < 64) {
            distance = self->posY.i.hi - e->posY.i.hi;
            if (distance < 0) {
                distance = -distance;
            }
            if (distance < 64) {
                continue;
            }
        }

        if ((self->facingLeft ? entityX < selfX : selfX < entityX) != 0) {
            continue;
        }
        if (e->hitPoints >= 0x7000) {
            continue;
        }

        if (!(e->flags & FLAG_UNK_80000)) {
            e->flags |= FLAG_UNK_80000;
            return e;
        }
        if (e->hitPoints >= D_80170658[D_80174C30.unk0 / 10][3]) {
            found++;
            D_801748D8[i] = 1;
        }
    }

    if (found > 0) {
        foundIndex = D_80174D40 % EntitySearchCount;
        for (i = 0; i < 0x80; i++) {
            if (D_801748D8[foundIndex] != 0) {
                e = &g_Entities[STAGE_ENTITY_START + foundIndex];
                D_80174D40 = (foundIndex + 1) % EntitySearchCount;
                return e;
            }
            foundIndex = (foundIndex + 1) % EntitySearchCount;
        }
    }

    return NULL;
}

s32 func_801713C8(Entity* entity) {
    if (entity->hitboxState == 0)
        return 0;
    if (entity->posX.i.hi < -16)
        return 0;
    if (entity->posX.i.hi > 272)
        return 0;
    if (entity->posY.i.hi > 240)
        return 0;
    if (entity->posY.i.hi < 0)
        return 0;
    if (entity->hitPoints >= 0x7000)
        return 0;
    return entity->hitPoints > 0;
}

bool func_80171434(s16 x, s16 y, s16* outX, s16* outY) {
    s32 curY;

    g_api.CheckCollision(x, y, &D_80174AD8, 0);
    if (D_80174AD8.effects & 1) {
        return 0;
    }

    for (curY = y - 16; curY > 0; curY -= 16) {
        g_api.CheckCollision(x, curY, &D_80174AD8, 0);
        switch (D_80174AD8.effects & 0x801) {
        case 0:
            break;
        case 1:
            *outX = x;
            *outY = curY + D_80174AD8.unk10;
            return 1;
        default:
            return 0;
        }
    }
    return 0;
}

void func_80171560(Entity* self) {}

void func_80171568(Entity* self) {
    Entity* entity;
    s32 i;

    for (i = 0; i < 3; i++) {
        entity = &g_Entities[5 + i];
        if (entity->entityId == 0) {
            goto init_entity;
        }
    }
    return;

init_entity:
    DestroyEntity(entity);
    entity->entityId = 0xDA;
    entity->zPriority = self->zPriority;
    entity->facingLeft = self->facingLeft;
    entity->flags = FLAG_UNK_04000000;
    entity->posX.val = self->posX.val;
    entity->posY.val = self->posY.val;
    entity->ext.generic.unk8C.entityPtr = self;
}

void func_8017160C(s32 amount, s32 entityId) {
    s32 i;
    Entity* entity;
    s16 facing;

    if (amount > 3) {
        amount = 3;
    }

    for (i = 0; i < amount; i++) {
        entity = &g_Entities[5 + i];
        if (entity->entityId == entityId) {
            entity->step = 0;
        } else {
            DestroyEntity(entity);
            entity->unk5A = 0x6C;
            entity->palette = 0x140;
            entity->entityId = entityId;
            entity->animSet = ANIMSET_OVL(20);
            entity->zPriority = g_Entities[0].zPriority - 2;
            facing = (g_Entities[0].facingLeft + 1) & 1;
            entity->params = i + 1;
            entity->facingLeft = facing;
        }
        entity->ext.bat.cameraX = g_Tilemap.cameraX.i.hi;
        entity->ext.bat.cameraY = g_Tilemap.cameraY.i.hi;
    }
}

void func_8017170C(Entity* entity, s32 frameIndex) {
    POLY_GT4* poly;
    s32 tpage;
    s32 x;
    s32 y;
    s32 index;

    poly = &g_PrimBuf[entity->primIndex];
    if (frameIndex == 0) {
        poly->pad3 = 8;
        return;
    }
    index = frameIndex - 1;
    if (entity->facingLeft != 0) {
        x = entity->posX.i.hi + 2;
    } else {
        x = entity->posX.i.hi - 16;
    }
    y = entity->posY.i.hi - 16;

    poly->x0 = poly->x2 = x - D_80170608[index].x;
    poly->y0 = poly->y1 = y - D_80170608[index].y;
    poly->x1 = poly->x3 = poly->x0 + D_80170608[index].width;
    poly->y2 = poly->y3 = poly->y0 + D_80170608[index].height;
    poly->clut = D_80170608[index].clut;
    tpage = D_80170608[index].tpage;
    if (tpage < 0) {
        tpage += 3;
    }
    poly->tpage = tpage >> 2;
    poly->u0 = poly->u2 = D_80170608[index].texLeft;
    poly->v0 = poly->v1 = D_80170608[index].texTop;
    poly->u1 = poly->u3 = D_80170608[index].texRight;
    poly->v2 = poly->v3 = D_80170608[index].texBottom;
    poly->pad2 = entity->zPriority + 1;
    poly->pad3 = 0x102;
}

void func_801718A0(Entity* entity) {
    POLY_GT4* poly;
    s32 frame;
    s32 y;
    s32 x;

    frame = 2;
    if (entity->facingLeft != 0) {
        x = entity->posX.i.hi + 2;
    } else {
        x = entity->posX.i.hi - 16;
    }
    y = entity->posY.i.hi - 16;

    x += (rsin(entity->ext.bat.unk8C << 7) * 8) >> 12;
    y -= entity->ext.bat.unk8C / 2;

    poly = &g_PrimBuf[entity->primIndex];
    poly->x0 = poly->x2 = x - D_80170608[frame].x;
    poly->y0 = poly->y1 = y - D_80170608[frame].y;
    poly->x1 = poly->x3 = poly->x0 + D_80170608[frame].width;
    poly->y2 = poly->y3 = poly->y0 + D_80170608[frame].height;
}

void func_801719E0(Entity* self) {
    s32 i;

    if (self->ext.bat.unk80 == 0) {
        self->ext.bat.unk8E = 0;
        self->ext.bat.unk82 = self->params;
        switch (self->entityId) {
        case 0xD1:
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (self->primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            func_8017170C(self, 0);
            self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 |
                          FLAG_HAS_PRIMS | FLAG_UNK_20000;
            func_801710E8(self, &D_801704A8);
            self->ext.bat.unk84 = rand() % 4096;
            self->ext.bat.unk86 = 0;
            self->ext.bat.unk88 = 0xC;
            self->ext.bat.unk8C = rand() % 4096;
            self->ext.bat.unk8A = 0x20;
            self->step++;
            break;
        case 0xD2:
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (self->primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            func_8017170C(self, 0);
            self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 |
                          FLAG_UNK_02000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
            func_801710E8(self, &D_801704A8);
            if (self->ext.bat.unk82 == 0) {
                self->ext.bat.follow = &PLAYER;
            } else {
                self->ext.bat.follow = &g_Entities[3 + self->ext.bat.unk82];
            }
            self->ext.bat.cameraX = g_Tilemap.cameraX.i.hi;
            self->ext.bat.cameraY = g_Tilemap.cameraY.i.hi;

            if (self->ext.bat.unk82 == 0) {
                for (i = 0; i < 16; i++) {
                    D_80174C3C[self->ext.bat.unk82][i].x =
                        self->ext.bat.follow->posX.i.hi + self->ext.bat.cameraX;
                    D_80174C3C[self->ext.bat.unk82][i].y =
                        self->ext.bat.follow->posY.i.hi + self->ext.bat.cameraY;
                }
            } else {
                for (i = 0; i < 16; i++) {
                    if (PLAYER.facingLeft) {
                        D_80174C3C[self->ext.bat.unk82][i].x =
                            PLAYER.posX.i.hi +
                            ((self->ext.bat.unk82 + 1) * 0x10) +
                            self->ext.bat.cameraX;

                    } else {
                        D_80174C3C[self->ext.bat.unk82][i].x =
                            PLAYER.posX.i.hi -
                            ((self->ext.bat.unk82 + 1) * 0x10) +
                            self->ext.bat.cameraX;
                    }
                    D_80174C3C[self->ext.bat.unk82][i].y =
                        PLAYER.posY.i.hi + self->ext.bat.cameraY;
                }
                self->posX.i.hi = PLAYER.facingLeft ? 0x180 : -0x80;
                self->posY.i.hi = rand() % 256;
            }
            self->ext.bat.unkA8 = 0;
            self->step++;
            break;
        }
    } else {
        self->ext.bat.unk8E = 0;
        switch (self->entityId) {
        case 0xD1:
            self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 |
                          FLAG_HAS_PRIMS | FLAG_UNK_20000;
            func_801710E8(self, &D_801704A8);
            self->ext.bat.unk8C = rand() % 4096;
            self->step++;
            break;
        case 0xD2:
            self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 |
                          FLAG_UNK_02000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
            func_801710E8(self, &D_801704A8);
            if (self->ext.bat.unk82 == 0) {
                self->ext.bat.follow = &PLAYER;
            } else {
                self->ext.bat.follow = &g_Entities[3 + self->ext.bat.unk82];
            }
            self->ext.bat.cameraX = g_Tilemap.cameraX.i.hi;
            self->ext.bat.cameraY = g_Tilemap.cameraY.i.hi;

            for (i = 0; i < 16; i++) {
                if (PLAYER.facingLeft) {
                    D_80174C3C[self->ext.bat.unk82][i].x =
                        PLAYER.posX.i.hi + ((self->ext.bat.unk82 + 1) * 0x10) +
                        self->ext.bat.cameraX;
                } else {
                    D_80174C3C[self->ext.bat.unk82][i].x =
                        PLAYER.posX.i.hi - ((self->ext.bat.unk82 + 1) * 0x10) +
                        self->ext.bat.cameraX;
                }
                D_80174C3C[self->ext.bat.unk82][i].y =
                    PLAYER.posY.i.hi + self->ext.bat.cameraY;
            }
            self->ext.bat.unkA8 = 0;
            self->step++;
            break;
        }
    }
    self->ext.bat.unk80 = self->entityId;
    g_api.func_8011A3AC(self, 0, 0, &D_80174C30);
}

void func_80171ED4(s32 arg0) {
    RECT rect;
    s32 i;
    s32 x;
    u16* spriteBanks;
    s16* src;
    s16* dst;
    Entity* e;

    if (arg0 == 1 || arg0 == 3)
        func_80174210(0, 1);

    if (arg0 == 3)
        return;

    dst = D_8006F3CC;
    src = D_80170448;
    for (i = 0; i < 0x100; i++) {
        *dst++ = *src++;
    }

    dst = D_8006F42C;
    spriteBanks = D_80170720;
    src = spriteBanks;
    for (i = 0; i < 0x20; i++) {
        *dst++ = *src++;
    }

    rect.w = 0x100;
    rect.h = 1;
    rect.x = 0;
    rect.y = 0xF4;
    dst = D_8006F3CC;
    LoadImage(&rect, dst);

    spriteBanks = D_80170040;
    g_api.o.spriteBanks[0x14] = spriteBanks;

    e = &g_Entities[4];
    DestroyEntity(e);
    e->unk5A = 0x6C;
    e->palette = 0x140;
    e->animSet = ANIMSET_OVL(20);
    e->params = 0;
    e->zPriority = PLAYER.zPriority - 2;
    e->facingLeft = (PLAYER.facingLeft + 1) & 1;
    e->posX.val = PLAYER.posX.val;
    e->posY.val = PLAYER.posY.val;
    if (arg0 == 1) {
        e->entityId = 0xD1;
        e->posX.val = 0x800000;
        e->posY.val = 0xFFE00000;
    } else {
        Entity* p;
        e->entityId = 0xD1;
        if (D_8003C708.flags & 0x20) {
            if (func_80174864() != 0) {
                x = 0xC00000;
            } else {
                x = 0x400000;
            }
            e->posX.val = x;
            e->posY.val = 0xA00000;
        } else {
            if (PLAYER.facingLeft == 0) {
                e->posX.val = PLAYER.posX.val - 0x120000;
            } else {
                e->posX.val = PLAYER.posX.val + 0x120000;
            }
            e->posY.val = PLAYER.posY.val - 0x220000;
        }
    }
    D_80174D3C = 0;
    e->ext.bat.cameraX = g_Tilemap.cameraX.i.hi;
    e->ext.bat.cameraY = g_Tilemap.cameraY.i.hi;
}

void func_80172120(Entity* self) {
    s32 var_v0;
    s32 var_v1;

    g_api.func_8011A3AC(self, 0, 0, &D_80174C30);
    if (D_80174D3C != 0) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    if (D_8003C708.flags & 0x20) {
        switch (func_80174864()) {
        case 0:
            D_80174B04 = 0x40;
            break;
        case 1:
            D_80174B04 = 0xC0;
            break;
        case 2:
            var_v1 = 0x40;
            if (self->posX.i.hi > 0x80) {
                var_v1 += 0x80;
            }
            D_80174B04 = var_v1;
            break;
        }
        D_80174B08 = 0xA0;
    } else {
        D_80174B18 = -0x12;
        if (PLAYER.facingLeft != 0) {
            D_80174B18 = 0x12;
        }
        D_80174B04 = PLAYER.posX.i.hi + D_80174B18;
        D_80174B08 = PLAYER.posY.i.hi - 0x22;
    }
    D_80174B0C = self->ext.bat.unk84;
    self->ext.bat.unk84 += 0x10;
    D_80174B14 = self->ext.bat.unk88;
    D_80174AFC = D_80174B04 + ((rcos(D_80174B0C) >> 4) * D_80174B14 >> 8);
    D_80174B00 = D_80174B08 - ((rsin(D_80174B0C / 2) >> 4) * D_80174B14 >> 8);
    switch (self->step) {
    case 0:
        func_801719E0(self);
        break;
    case 1:
        if (g_Player.unk0C & 1) {
            self->ext.bat.unk8C = 0;
            self->step = 5;
        } else {
            if (D_8003C708.flags & 0x20) {
                if (PLAYER.posX.i.hi < self->posX.i.hi) {
                    self->facingLeft = false;
                } else {
                    self->facingLeft = true;
                }
            } else {
                if (PLAYER.facingLeft == self->facingLeft) {
                    var_v0 = D_80174AFC - self->posX.i.hi;
                    if (var_v0 < 0) {
                        var_v0 = -var_v0;
                    }
                    if (var_v0 <= 0) {
                        self->facingLeft = !self->facingLeft;
                    } else {
                        if (self->facingLeft) {
                            if (D_80174AFC < self->posX.i.hi) {
                                self->facingLeft = !self->facingLeft;
                            }
                        } else if (self->posX.i.hi < D_80174AFC) {
                            self->facingLeft = 1;
                        }
                    }
                } else if (self->facingLeft) {
                    var_v0 = self->posX.i.hi - D_80174AFC;
                    if (var_v0 >= 0x20) {
                        self->facingLeft = PLAYER.facingLeft;
                    }
                } else {
                    var_v0 = D_80174AFC - self->posX.i.hi;
                    if (var_v0 >= 0x20) {
                        self->facingLeft = PLAYER.facingLeft;
                    }
                }
            }
            D_80174B0C = func_80173F30(self, D_80174AFC, D_80174B00);
            D_80174B10 = func_80173F74(
                D_80174B0C, self->ext.bat.unk86, self->ext.bat.unk8A);
            self->ext.bat.unk86 = D_80174B10;
            D_80174B04 = D_80174AFC - self->posX.i.hi;
            D_80174B08 = D_80174B00 - self->posY.i.hi;
            D_80174B14 =
                SquareRoot12((D_80174B04 * D_80174B04 + D_80174B08 * D_80174B08)
                             << 0xC) >>
                0xC;
            if (D_80174B14 < 0x1E) {
                self->velocityY = -(rsin(D_80174B10) * 8);
                self->velocityX = rcos(D_80174B10) * 8;
                self->ext.bat.unk8A = 0x20;
            } else if (D_80174B14 < 0x3C) {
                self->velocityY = -(rsin(D_80174B10) * 0x10);
                self->velocityX = rcos(D_80174B10) * 0x10;
                self->ext.bat.unk8A = 0x40;
            } else if (D_80174B14 < 0x64) {
                self->velocityY = -(rsin(D_80174B10) << 5);
                self->velocityX = rcos(D_80174B10) << 5;
                self->ext.bat.unk8A = 0x60;
            } else if (D_80174B14 < 0x100) {
                self->velocityY = -(rsin(D_80174B10) << 6);
                self->velocityX = rcos(D_80174B10) << 6;
                self->ext.bat.unk8A = 0x80;
            } else {
                self->ext.bat.unk8A = 0x80;
                self->velocityX = (D_80174AFC - self->posX.i.hi) << 0xE;
                self->velocityY = (D_80174B00 - self->posY.i.hi) << 0xE;
            }
            if (self->velocityY > FIX(1.0)) {
                func_801710E8(self, D_801705EC);
            } else if (D_80174B14 < 0x3C) {
                func_801710E8(self, D_801704A8);
            } else if (D_80174B14 >= 0x65) {
                func_801710E8(self, D_80170514);
            }
            self->posX.val += self->velocityX;
            self->posY.val += self->velocityY;
            if (D_8003C704 == 0) {
                D_80174B24 = D_80174AFC - self->posX.i.hi;
                D_80174B28 = D_80174B00 - self->posY.i.hi;
                D_80174B2C =
                    SquareRoot12(
                        (D_80174B24 * D_80174B24 + D_80174B28 * D_80174B28)
                        << 0xC) >>
                    0xC;
                if (D_80174B2C < 0x18) {
                    if (self->ext.bat.unk8E != 0) {
                        self->ext.bat.unk8E = 0;
                        func_801710E8(self, D_8017054C);
                    }
                    self->ext.bat.unk8C++;
                    if (D_80170658[D_80174C30.unk0 / 10][0] <
                        self->ext.bat.unk8C) {
                        self->ext.bat.unk8C = 0;
                        self->ext.bat.target = func_8017110C(self);
                        if (self->ext.bat.target != 0) {
                            self->step++;
                        }
                    }
                } else {
                    self->ext.bat.unk8E = 1;
                }
            }
        }
        break;
    case 2:
        self->ext.bat.unk8C++;
        if (self->ext.bat.unk8C == 1) {
            g_api.PlaySfx(SFX_BAT_NOTIFY);
            func_8017170C(self, 1);
        } else if (self->ext.bat.unk8C >= 0x1F) {
            self->ext.bat.unk8C = 0;
            func_8017170C(self, 0);
            D_80174B1C = self->ext.bat.target->posX.i.hi;
            D_80174B20 = self->ext.bat.target->posY.i.hi;
            self->hitboxWidth = 5;
            self->hitboxHeight = 5;
            g_api.func_8011A3AC(self, 0xF, 1, &D_80174C30);
            self->ext.bat.unk86 = 0xC00;
            func_801710E8(self, D_801705EC);
            func_80171568(self);
            self->step++;
        }
        break;
    case 3:
        D_80174B1C = self->ext.bat.target->posX.i.hi;
        D_80174B20 = self->ext.bat.target->posY.i.hi;
        D_80174B0C = func_80173F30(self, (s16)D_80174B1C, (s16)D_80174B20);
        D_80174B10 = func_80173F74(D_80174B0C, self->ext.bat.unk86,
                                   (s16)D_80170658[D_80174C30.unk0 / 10][1]);
        self->ext.bat.unk86 = D_80174B10;
        self->velocityX = rcos(D_80174B10) << 6;
        self->velocityY = -(rsin(D_80174B10) << 6);
        if (self->velocityX > 0) {
            self->facingLeft = 1;
        }
        if (self->velocityX < 0) {
            self->facingLeft = 0;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        D_80174B24 = D_80174B1C - self->posX.i.hi;
        D_80174B28 = D_80174B20 - self->posY.i.hi;
        D_80174B2C =
            SquareRoot12(
                (D_80174B24 * D_80174B24 + D_80174B28 * D_80174B28) << 0xC) >>
            0xC;
        if (!func_801713C8(self->ext.bat.target) || D_80174B2C < 8) {
            self->ext.bat.unk8C = 0;
            self->step++;
            func_801710E8(self, D_8017054C);
        }
        break;
    case 4:
        D_80174B0C = func_80173F30(self, D_80174AFC, D_80174B00);
        D_80174B10 = func_80173F74(D_80174B0C, self->ext.bat.unk86, 0x10);
        self->ext.bat.unk86 = D_80174B10;
        self->velocityX = rcos(D_80174B10) << 6;
        self->velocityY = -(rsin(D_80174B10) << 6);
        self->facingLeft = self->velocityX >= 0;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->ext.bat.unk8C++;
        if (self->ext.bat.unk8C >= 0x1F) {
            self->hitboxWidth = 0;
            self->hitboxHeight = 0;
            self->step = 1;
        }
        break;
    case 5:
        self->ext.bat.unk8C++;
        if (self->ext.bat.unk8C == 1) {
            g_api.PlaySfx(SFX_BAT_SCREECH);
            func_8017170C(self, 3);
        } else if (self->ext.bat.unk8C >= 0x1F) {
            func_8017170C(self, 0);
            self->entityId = 0xD2;
            self->step = 0;
        }
        func_801718A0(self);
        break;
    }
    func_80174210(self, 0);
    func_80171560(self);
    g_api.UpdateAnim(NULL, D_801705F4);
}

void func_80172C30(Entity* self) {
    if (self->step == 1 && self->flags & FLAG_UNK_00200000) {
        D_80174B38 = (self->ext.bat.cameraX - g_Tilemap.cameraX.i.hi) +
                     (self->ext.bat.unkB0 - PLAYER.posX.i.hi);
        D_80174B3C = (self->ext.bat.cameraY - g_Tilemap.cameraY.i.hi) +
                     (self->ext.bat.unkB2 - PLAYER.posY.i.hi);

        for (D_80174B30 = 0; D_80174B30 < 0x10; D_80174B30++) {
            D_80174C3C[self->ext.bat.unk82][D_80174B30].x -= D_80174B38;
            D_80174C3C[self->ext.bat.unk82][D_80174B30].y -= D_80174B3C;
        }
        return;
    }

    g_api.func_8011A3AC(self, 0, 0, &D_80174C30);
    if (D_80174D3C != 0) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    switch (self->step) {
    case 0:
        func_801719E0(self);
        if (self->ext.bat.unk82 == 0) {
            func_8017160C(D_80170658[D_80174C30.unk0 / 10][2], 0xD2);
        }
        break;
    case 1:
        self->ext.bat.unkB0 = PLAYER.posX.i.hi;
        self->ext.bat.unkB2 = PLAYER.posY.i.hi;
        self->ext.bat.cameraX = g_Tilemap.cameraX.i.hi;
        self->ext.bat.cameraY = g_Tilemap.cameraY.i.hi;
        D_80174B40 =
            D_80174C3C[self->ext.bat.unk82][0].x - self->ext.bat.cameraX;
        D_80174B44 =
            D_80174C3C[self->ext.bat.unk82][0].y - self->ext.bat.cameraY;
        self->velocityX = (D_80174B40 - self->posX.i.hi) << 0xC;
        self->velocityY = (D_80174B44 - self->posY.i.hi) << 0xC;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if ((self->velocityX == 0) && (self->velocityY == 0)) {
            if (self->ext.bat.unk8E != 0) {
                func_801710E8(self, D_8017054C);
                self->ext.bat.unk8E = 0;
            }
        } else {
            if (self->velocityY > FIX(1)) {
                func_801710E8(self, &D_801705EC);
            } else {
                func_801710E8(self, &D_801704A8);
            }
            self->ext.bat.unk8E = 1;
        }
        self->facingLeft = PLAYER.facingLeft == 0;
        if (self->ext.bat.unkA8 == 0) {
            if (g_Player.unk0C & 0x800) {
                // This causes the bat familiar to shoot a fireball when the
                // player does so in bat form.
                g_api.CreateEntFactoryFromEntity(self, FACTORY(0x100, 81), 0);
                self->ext.bat.unkA8 = 1;
            }
        } else if (!(g_Player.unk0C & 0x800)) {
            self->ext.bat.unkA8 = 0;
        }
        D_80174B38 = self->ext.bat.follow->posX.i.hi - self->posX.i.hi;
        D_80174B3C = self->ext.bat.follow->posY.i.hi - self->posY.i.hi;
        D_80174B34 =
            SquareRoot12(((D_80174B38 * D_80174B38) + (D_80174B3C * D_80174B3C))
                         << 0xC) >>
            0xC;
        if ((func_801746A0(0) != 0) || (D_80174B34 >= 0x19)) {
            for (D_80174B30 = 0; D_80174B30 < 0xF; D_80174B30++) {
                D_80174C3C[self->ext.bat.unk82][D_80174B30].x =
                    D_80174C3C[self->ext.bat.unk82][D_80174B30 + 1].x;
                D_80174C3C[self->ext.bat.unk82][D_80174B30].y =
                    D_80174C3C[self->ext.bat.unk82][D_80174B30 + 1].y;
            }
            D_80174C3C[self->ext.bat.unk82][D_80174B30].x =
                self->ext.bat.follow->posX.i.hi + self->ext.bat.cameraX;
            D_80174C3C[self->ext.bat.unk82][D_80174B30].y =
                self->ext.bat.follow->posY.i.hi + self->ext.bat.cameraY;
        }
        if (!(g_Player.unk0C & 1)) {
            self->ext.bat.unk8C = 0;
            self->step++;
        }
        break;
    case 2:
        if (++self->ext.bat.unk8C == 1) {
            if (self->ext.bat.unk82 == 0) {
                g_api.PlaySfx(SFX_BAT_SCREECH);
            }
            func_8017170C(self, 2);
        } else if (self->ext.bat.unk8C >= 0x1F) {
            func_8017170C(self, 0);
            if (self->ext.bat.unk82 == 0) {
                self->entityId = 0xD1;
                self->step = 0;
                break;
            }
            self->step++;
            D_80174C3C[self->ext.bat.unk82][0].x =
                PLAYER.facingLeft ? -0x80 : 0x180;
            D_80174C3C[self->ext.bat.unk82][0].y = rand() % 256;
            func_801710E8(self, &D_801704A8);
        }
        break;
    case 3:
        D_80174B40 = D_80174C3C[self->ext.bat.unk82][0].x;
        D_80174B44 = D_80174C3C[self->ext.bat.unk82][0].y;
        self->velocityX = (D_80174B40 - self->posX.i.hi) << 0xA;
        self->velocityY = (D_80174B44 - self->posY.i.hi) << 0xA;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->posX.i.hi < -0x20 || 0x120 < self->posX.i.hi) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    func_80174210(self, 0);
    func_80171560(self);
    g_api.UpdateAnim(NULL, D_801705F4);
}

void func_8017339C(void) {}

void func_801733A4(void) {}

void func_801733AC(void) {}

void func_801733B4(void) {}

void func_801733BC(void) {}

void func_801733C4(void) {}

void func_801733CC(void) {}

void func_801733D4(Entity* self) {
    const s32 nPrim = 16;
    const s32 XS = 11; // X start, left
    const s32 XE = 13; // X end, right
    const s32 YS = 24; // Y start, top
    const s32 YE = 8;  // Y end, bottom
    s32 i;
    s32 isEntityAlive;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, nPrim);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        } else {
            self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
            D_80174B48 = &g_PrimBuf[self->primIndex];
            for (i = 0; i < nPrim; i++) {
                D_80174B48->tpage = 0x1B;
                D_80174B48->clut = 0x143;
                D_80174B48->u0 = D_80174B48->u2 = 64;
                D_80174B48->v0 = D_80174B48->v1 = 0;
                D_80174B48->u1 = D_80174B48->u3 = 88;
                D_80174B48->v2 = D_80174B48->v3 = 32;
                D_80174B48->priority = self->zPriority;
                D_80174B48->blendMode = 0x15 | BLEND_VISIBLE;
                D_80174B48 = D_80174B48->next;
                D_80174B4C[i] = 0;
            }
            D_80174C2C = 0;
            self->step++;
        }
        break;
    case 1:
        if (self->ext.factory.parent->step != 3) {
            self->step++;
        }
        D_80174B8C[D_80174C2C].x = self->ext.factory.parent->posX.i.hi;
        D_80174B8C[D_80174C2C].y = self->ext.factory.parent->posY.i.hi;
        D_80174BCC[D_80174C2C] = self->ext.factory.parent->facingLeft;
        D_80174BEC[D_80174C2C] = 256;
        D_80174C0C[D_80174C2C] = 192;
        D_80174B4C[D_80174C2C] = 1;
        D_80174C2C++;
        D_80174C2C = D_80174C2C >= nPrim ? 0 : D_80174C2C;
        D_80174B48 = &g_PrimBuf[self->primIndex];
        for (i = 0; i < nPrim; i++) {
            if (D_80174B4C[i]) {
                if (D_80174BCC[i]) {
                    D_80174B48->x0 = D_80174B48->x2 =
                        D_80174B8C[i].x + D_80174BEC[i] * XS / 256;
                    D_80174B48->x1 = D_80174B48->x3 =
                        D_80174B8C[i].x - D_80174BEC[i] * XE / 256;
                } else {
                    D_80174B48->x0 = D_80174B48->x2 =
                        D_80174B8C[i].x - D_80174BEC[i] * XS / 256;
                    D_80174B48->x1 = D_80174B48->x3 =
                        D_80174B8C[i].x + D_80174BEC[i] * XE / 256;
                }
                D_80174B48->y0 = D_80174B48->y1 =
                    D_80174B8C[i].y - D_80174BEC[i] * YS / 256;
                D_80174B48->y2 = D_80174B48->y3 =
                    D_80174B8C[i].y + D_80174BEC[i] * YE / 256;
                D_80174B48->r0 = D_80174B48->r1 = D_80174B48->r2 =
                    D_80174B48->r3 = D_80174B48->g0 = D_80174B48->g1 =
                        D_80174B48->g2 = D_80174B48->g3 = D_80174B48->b0 =
                            D_80174B48->b1 = D_80174B48->b2 = D_80174B48->b3 =
                                D_80174C0C[i];
                D_80174BEC[i] -= 8;
                D_80174C0C[i] -= 8;
                if (D_80174C0C[i] < 81) {
                    D_80174B48->blendMode |= BLEND_VISIBLE;
                    D_80174B4C[i] = 0;
                } else {
                    D_80174B48->blendMode ^= BLEND_VISIBLE;
                }
            }
            D_80174B48 = D_80174B48->next;
        }
        break;
    case 2:
        isEntityAlive = false;
        D_80174B48 = &g_PrimBuf[self->primIndex];
        for (i = 0; i < nPrim; i++) {
            if (D_80174B4C[i]) {
                if (D_80174BCC[i]) {
                    D_80174B48->x0 = D_80174B48->x2 =
                        D_80174B8C[i].x + D_80174BEC[i] * XS / 256;
                    D_80174B48->x1 = D_80174B48->x3 =
                        D_80174B8C[i].x - D_80174BEC[i] * XE / 256;
                } else {
                    D_80174B48->x0 = D_80174B48->x2 =
                        D_80174B8C[i].x - D_80174BEC[i] * XS / 256;
                    D_80174B48->x1 = D_80174B48->x3 =
                        D_80174B8C[i].x + D_80174BEC[i] * XE / 256;
                }
                D_80174B48->y0 = D_80174B48->y1 =
                    D_80174B8C[i].y - D_80174BEC[i] * YS / 256;
                D_80174B48->y2 = D_80174B48->y3 =
                    D_80174B8C[i].y + D_80174BEC[i] * YE / 256;
                D_80174B48->r0 = D_80174B48->r1 = D_80174B48->r2 =
                    D_80174B48->r3 = D_80174B48->g0 = D_80174B48->g1 =
                        D_80174B48->g2 = D_80174B48->g3 = D_80174B48->b0 =
                            D_80174B48->b1 = D_80174B48->b2 = D_80174B48->b3 =
                                D_80174C0C[i];
                D_80174B48->r0 = D_80174B48->r1 = D_80174B48->r2 =
                    D_80174B48->r3 = D_80174B48->g0 = D_80174B48->g1 =
                        D_80174B48->g2 = D_80174B48->g3 = D_80174B48->b0 =
                            D_80174B48->b1 = D_80174B48->b2 = D_80174B48->b3 =
                                D_80174C0C[i];
                D_80174BEC[i] -= 8;
                D_80174C0C[i] -= 8;
                if (D_80174C0C[i] < 81) {
                    D_80174B48->blendMode |= BLEND_VISIBLE;
                    D_80174B4C[i] = 0;
                } else {
                    D_80174B48->blendMode ^= BLEND_VISIBLE;
                }
            }
            isEntityAlive |= D_80174B4C[i];
            D_80174B48 = D_80174B48->next;
        }

        if (isEntityAlive == false) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

void func_80173C0C(void) {}

void func_80173C14(void) {}

void func_80173C1C(void) {}

void func_80173C24(void) {}

void func_80173C2C(Entity* entity) {
    if (entity->params == 0xF) {
        D_80174D3C = 1;
    }
    DestroyEntity(entity);
}

u32 UpdateAnim(Entity* self, s8* frameProps, AnimationFrame** frames) {
    AnimationFrame* animFrame;
    s32 ret;

    ret = 0;
    if (self->animFrameDuration == -1) {
        ret = -1;
    } else if (self->animFrameDuration == 0) {
        self->animFrameDuration = self->unk4C[self->animFrameIdx].duration;
    } else if (--self->animFrameDuration == 0) {
        self->animFrameIdx++;
        animFrame = &self->unk4C[self->animFrameIdx];
        // Effectively a switch statement, but breaks if I actually use one.
        if (animFrame->duration == 0) {
            self->animFrameIdx = animFrame->unk2;
            self->animFrameDuration = self->unk4C[self->animFrameIdx].duration;
            ret = 0;
        } else if (animFrame->duration == 0xFFFF) {
            self->animFrameIdx--;
            self->animFrameDuration = -1;
            ret = -1;
        } else if (animFrame->duration == 0xFFFE) {
            self->unk4C = frames[animFrame->unk2];
            self->animFrameIdx = 0;
            ret = -2;
            self->animFrameDuration = self->unk4C->duration;
        } else {
            self->animFrameDuration = animFrame->duration;
        }
    }
    if (frameProps != NULL) {
        // This is ugly - theoretically the type for frameProps should be
        // FrameProperty* but anything besides this where we assign this big
        // expression fails.
        frameProps =
            &frameProps[(self->unk4C[self->animFrameIdx].unk2 >> 9) << 2];
        self->hitboxOffX = *frameProps++;
        self->hitboxOffY = *frameProps++;
        self->hitboxWidth = *frameProps++;
        self->hitboxHeight = *frameProps++;
    }
    self->animCurFrame = self->unk4C[self->animFrameIdx].unk2 & 0x1FF;
    return ret;
}

void DestroyEntity(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->flags & FLAG_HAS_PRIMS) {
        g_api.FreePrimitives(entity->primIndex);
    }

    ptr = (u32*)entity;
    length = sizeof(Entity) / sizeof(u32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

s32 func_80173E78(s32 arg0, s32 arg1) {
    if (arg0 < 0) {
        arg0 += arg1;
        if (arg0 > 0) {
            arg0 = 0;
        }
    } else {
        arg0 -= arg1;
        if (arg0 < 0) {
            arg0 = 0;
        }
    }

    return arg0;
}

Entity* func_80173EB0(s32 rangeIndex, s32 entityId) {
    volatile u32 pad; // fake?
    s16 start = D_80171094[rangeIndex].start;
    s16 end = D_80171094[rangeIndex].end;
    Entity* entity = &g_Entities[start];
    s32 i;

    for (i = start; end >= i; i++, entity++) {
        if (entity->entityId == entityId) {
            return entity;
        }
    }

    return NULL;
}

s32 func_80173F30(Entity* entity, s16 x, s16 y) {
    s16 diffx = x - entity->posX.i.hi;
    return ratan2(-(s16)(y - entity->posY.i.hi), diffx) & 0xFFF;
}

s16 func_80173F74(s16 arg0, s16 arg1, s16 arg2) {
    s32 diffTmp = arg1 - arg0;
    s16 diff = ABS(diffTmp);
    s16 res;

    if (arg2 > diff) {
        arg2 = diff;
    }

    if (arg1 < arg0) {
        if (diff < 0x800) {
            res = arg1 + arg2;
        } else {
            res = arg1 - arg2;
        }
    } else {
        if (diff < 0x800) {
            res = arg1 - arg2;
        } else {
            res = arg1 + arg2;
        }
    }
    return res & 0xFFF;
}

s32 func_80173FE8(Entity* entity, s32 x, s32 y) {
    s32 diffX = x - entity->posX.i.hi;
    s32 diffY = y - entity->posY.i.hi;

    return SquareRoot12((SQ(diffX) + SQ(diffY)) << 12) >> 12;
}

void func_80174038(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_20000 | FLAG_UNK_04000000;
        if (D_8003C704 != 0) {
            D_80171090 = 99;
            DestroyEntity(entity);
            return;
        }
        if (g_api.CdSoundCommandQueueEmpty() != 0) {
            g_api.PlaySfx(SET_UNK_10);
            entity->step++;
        }
        break;

    case 1:
        if (g_api.func_80133950() != 0) {
            entity->step++;
        }
        break;
    case 2:
        g_api.PlaySfx(entity->params);
        entity->step++;
        break;

    case 3:
        if (g_api.func_80131F68() != 0) {
            entity->step++;
        }
        break;

    case 4:
        if (g_api.func_80131F68() == 0) {
            entity->step++;
        }
        break;

    case 5:
        if ((*(s32*)&D_8003C708.flags & 0x60) != 0) {
            D_80171090 = 99;
            DestroyEntity(entity);
            return;
        }
        if (g_api.CdSoundCommandQueueEmpty() != 0) {
            g_api.PlaySfx(SET_UNK_11);
            entity->step++;
        }
        break;

    case 6:
        if (g_api.func_80133950() != 0) {
            D_80171090 = 99;
            DestroyEntity(entity);
            return;
        }
        break;

    case 7:
        g_api.PlaySfx(SET_STOP_MUSIC);
        entity->step = 4;
        break;

    case 8:
        D_80171090 = 99;
        DestroyEntity(entity);
        return;
    }

    D_80171090 = entity->step;
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/servant/tt_000/nonmatchings/10E8", func_80174210);
#else
typedef struct {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    s32 unkC;
    u32 unk10;
    u32 cameraX;
    u32 cameraY;
    s32 unk1C;
    u32 unk20;
    u32 entityId;
    u32 params;
    u32 unk2C;
} Unkstruct_80174210;

extern Unkstruct_80174210 D_80170760[];
extern s32* D_8017109C;
extern s32 D_801710A0;
extern s32 D_801710A4;
extern s32 D_801710A8;

void func_80174210(Entity* self, s32 arg1) {
    Unkstruct_80174210* temp_s0;
    Unkstruct_80174210** var_s1_2;
    Unkstruct_80174210* temp_v1_5;
    Unkstruct_80174210* temp_v1_4;
    s32* var_s1;
    s32 cameraY;
    s32 cameraX;
    s32 var_s2;
    s32 var_v0_2;

    if (arg1 != 0) {
        D_801710A8 = 0;
        D_801710A4 = 0;
        D_801710A0 = 0;
        return;
    }
    cameraX = g_Tilemap.cameraX.i.hi;
    cameraY = g_Tilemap.cameraY.i.hi;
    if (D_801710A0 != g_Servant || D_801710A4 != g_Tilemap.left ||
        D_801710A8 != g_Tilemap.top) {
        var_s1 = D_8017109C;
        D_801710A0 = g_Servant;
        D_801710A4 = g_Tilemap.left;
        D_801710A8 = g_Tilemap.top;
        if (D_80170760[1].unkC != -1) {
            var_s2 = 1;
            do {
                temp_s0 = &D_80170760[var_s2];
                if (temp_s0->unk8 == -1 || temp_s0->unk8 == D_801710A0) {
                    if ((temp_s0->unkC < 0 &&
                         !(g_StageId & STAGE_INVERTEDCASTLE_FLAG)) ||
                        !(g_StageId & STAGE_INVERTEDCASTLE_FLAG)) {
                        if (ABS(temp_s0->unkC) == D_801710A4 &&
                            temp_s0->unk10 == D_801710A8) {
                            if (temp_s0->cameraX == cameraX &&
                                temp_s0->cameraY == cameraY &&
                                (temp_s0->unk1C == -1 ||
                                 (temp_s0->unk1C >= 0 ||
                                  g_CastleFlags[temp_s0->unk1C & 0xFFFF] ==
                                      0) &&
                                     (!(temp_s0->unk1C & 0x40000000) ||
                                      !(g_Status
                                            .relics[temp_s0->unk1C & 0xFFFF] &
                                        1)))) {
                                temp_s0->unk4 = 0;
                                if (temp_s0->unk20 == 0) {
                                    func_801745E4(self, temp_s0->entityId,
                                                  temp_s0->params);
                                    if (temp_s0->unk2C == 0) {
                                        goto block_26;
                                    }
                                } else {
                                    goto block_27;
                                }
                            } else {
                            block_26:
                                if (temp_s0->unk20 != 0) {
                                block_27:
                                    temp_s0->unk4 = (s32)(temp_s0->unk20 - 1);
                                }
                                *var_s1 = temp_s0;
                                var_s1 = temp_s0;
                            }
                        }
                    }
                }
            } while (D_80170760[++var_s2].unkC != -1);
        }
        *var_s1 = NULL;
    } else {
        var_s1_2 = D_8017109C;
        while (*var_s1_2 != NULL) {
            temp_v1_5 = *var_s1_2;
            if (temp_v1_5->cameraX == cameraX &&
                temp_v1_5->cameraY == cameraY &&
                (temp_v1_5->unk1C == -1 ||
                 (temp_v1_5->unk1C >= 0 ||
                  g_CastleFlags[temp_v1_5->unk1C & 0xFFFF] == 0) &&
                     (!(temp_v1_5->unk1C & 0x40000000) ||
                      !(g_Status.relics[temp_v1_5->unk1C & 0xFFFF] & 1)))) {
                temp_v1_5 = *var_s1_2;
                var_v0_2 = temp_v1_5->unk4 - 1;
                if (temp_v1_5->unk4 == 0) {
                    func_801745E4(self, temp_v1_5->entityId, temp_v1_5->params);
                    temp_v1_4 = *var_s1_2;
                    if (temp_v1_4->unk2C != 0) {
                        *var_s1_2 = temp_v1_4->unk0;
                        continue;
                    } else {
                        var_v0_2 = temp_v1_4->unk20;
                    }
                }
                temp_v1_5->unk4 = var_v0_2;
            }
            var_s1_2 = *var_s1_2;
        }
    }
}
#endif

void func_801745E4(Entity* entityParent, s32 entityId, s32 params) {
    Entity* entity;
    s32 i;

    for (i = 0; i < 3; i++) {
        entity = &g_Entities[5 + i];
        if (entity->entityId == 0) {
            goto init_entity;
        }
    }
    return;

init_entity:
    DestroyEntity(entity);
    entity->entityId = entityId;
    entity->zPriority = entityParent->zPriority;
    entity->facingLeft = entityParent->facingLeft;
    entity->flags = FLAG_UNK_04000000;
    entity->posX.val = entityParent->posX.val;
    entity->posY.val = entityParent->posY.val;
    entity->ext.generic.unk8C.entityPtr = entityParent;
    entity->params = params;
}

s32 func_801746A0(s32 arg0) {
    s32 tmp;

    if (PLAYER.velocityY < 0) {
        if (!(g_Player.pl_vram_flag & 1)) {
            return 1;
        }
    }

    tmp = PLAYER.velocityY;
    if (tmp > 0) {
        if (!(g_Player.pl_vram_flag & 2)) {
            return 1;
        }
    }

    if (PLAYER.velocityX < 0 && !(g_Player.pl_vram_flag & 8))
        return 1;

    tmp = PLAYER.velocityX;
    if (PLAYER.velocityX > 0 && !(g_Player.pl_vram_flag & 4))
        return 1;

    if (arg0 == 0)
        return 0;

    if (g_Player.unk50 != PLAYER.step)
        return 1;

    if (g_Player.unk50 != 0)
        return 1;

    if (g_Player.unk52 != PLAYER.step_s)
        return 1;

    return g_Player.unk52 != 0 && g_Player.unk52 != 4;
}

s32 func_801747B8(void) {
    Entity* entity;
    s32 i;

    entity = &g_Entities[STAGE_ENTITY_START];
    for (i = 0; i < 0x80; i++, entity++) {
        if (entity->entityId == 0)
            continue;
        if (entity->hitboxState == 0)
            continue;
        if (entity->flags & FLAG_UNK_00200000)
            continue;
        if (entity->posX.i.hi < -16)
            continue;
        if (entity->posX.i.hi > 272)
            continue;
        if (entity->posY.i.hi > 240)
            continue;
        if (entity->posY.i.hi < 0)
            continue;
        if (entity->hitPoints < 0x7000)
            return 1;
    }
    return 0;
}

s32 func_80174864(void) {
    int tmp;

    if (g_StageId >= STAGE_RNO0 && g_StageId < STAGE_RNZ1_DEMO) {
        if (D_8003C708.flags == 0x22) {
            return 1;
        }

        tmp = (D_8003C708.flags != 0x20) * 2;
        return tmp;
    }

    if (D_8003C708.flags == 0x22) {
        return 0;
    }

    tmp = 0x20;
    return D_8003C708.flags != tmp ? 2 : 1;
}
