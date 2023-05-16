#ifndef DRA_H
#define DRA_H

#include "game.h"

typedef enum {
    SimFileType_System,
    SimFileType_StagePrg,
    SimFileType_Vh,
    SimFileType_Vb,
    SimFileType_Seq,
    SimFileType_StageChr,
    SimFileType_Unused6,
    SimFileType_Weapon0Prg,
    SimFileType_Weapon1Prg,
    SimFileType_Weapon0Chr,
    SimFileType_Weapon1Chr,
    SimFileType_FamiliarPrg,
    SimFileType_FamiliarChr,
    SimFileType_Monster,
} SimFileType;

typedef struct {
    const char* path; // file name
    u8* addr;         // where to load the file to
    s32 size;         // file size
    s32 type;         // file type
} SimFile;

typedef enum {
    CdStep_None,
    CdStep_LoadInit,
    CdStep_SetSpeed,
    CdStep_SetPos,
    CdStep_Seek,
    CdStep_5,
    CdStep_6,
    CdStep_Complete = 10,
    CdStep_DmaErr = 0xC0,
    CdStep_SdHeaderErr = 0xC1,
    CdStep_DiskErr = 0xC2,
    CdStep_Retry = 0xD0,
    CdStep_RetryXa = 0xD1,
    CdStep_CdShellOpenErr = 0xF0,
    CdStep_F1 = 0xF1,
    CdStep_F2 = 0xF2,
    CdStep_F3 = 0xF3,
} CdStep;

typedef enum {
    CdFile_None,
    CdFile_Sel,
    CdFile_GameChr,
    CdFile_StageChr,
    CdFile_4,
    CdFile_Seq = 12,
    CdFile_StageSfx,
    CdFile_14,
    CdFile_15,
    CdFile_16,
    CdFile_Weapon0,
    CdFile_Weapon1,
    CdFile_19,
    CdFile_24 = 24,
    CdFile_25,
    CdFile_26,
    CdFile_Servant,
    CdFile_28,
    CdFile_ServantPrg,
    CdFile_30,
    CdFile_31,
    CdFile_DemoKey,
    CdFile_NoNext = 0xFF,
    CdFile_StagePrg = 0x100,
} CdFileType;

typedef enum {
    CdCallback_0,        // func_801080DC
    CdCallback_1,        // func_801080DC
    CdCallback_2,        // func_801080DC
    CdCallback_3,        // func_801080DC
    CdCallback_4,        // CopyStageOvlCallback
    CdCallback_5,        // func_801080DC
    CdCallback_6,        // func_801080DC
    CdCallback_7,        // func_801080DC
    CdCallback_StagePrg, // CopyStageOvlCallback
    CdCallback_9,        // CopyStageOvlCallback
    CdCallback_Ric,      // CopyRicOvlCallback
    CdCallback_11,       // func_801080DC
    CdCallback_12,       // func_801078C4
    CdCallback_13,       // func_801078C4
    CdCallback_14,       // func_80107B04
    CdCallback_Familiar, // func_801078C4
    CdCallback_16,       // func_80107DB4
    CdCallback_17,       // func_80107C6C
    CdCallback_Seq,      // func_80107DB4
    CdCallback_Vh,       // func_80107EF0
} CdCallbacks;

// Info necessary to load a file from the Cd in func_80108448
typedef struct {
    s32 loc;        // lba offset, might be a s32
    CdCallbacks cb; // sets g_CdCallback
    s32 size;       // file size
    u8 unkC;        // index for D_800BD1C8, between 0 and 5?
    u8 unkD;        // index for D_800ACD10, between 0 and 6?
    u8 nextCdFileType;
    u8 unkF;
} CdFile;

// Used for SEQ_LIB.SEQ and SEQ_DAI.SEQ
typedef struct {
    s32 loc;
    s32 size;
    u32 unk8;
} CdFileSeq;

typedef struct {
    CdCallbacks cb;
    CdlLOC loc;
} CdMgr;

typedef struct {
    RECT D_800ACD80;
    RECT D_800ACD88;
    RECT D_800ACD90;
    RECT D_800ACD98;
    RECT D_800ACDA0;
    RECT D_800ACDA8;
    RECT D_800ACDB0;
    RECT D_800ACDB8;
    RECT D_800ACDC0;
    RECT D_800ACDC8;
    RECT D_800ACDD0;
    RECT D_800ACDD8;
    RECT D_800ACDE0;
    RECT D_800ACDE8;
    RECT D_800ACDF0;
} Vram;

typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ const char* combo;
    /* 0x08 */ const char* description;
    /* 0x0C */ s8 mpUsage;
    /* 0x0D */ s8 unk0D;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u16 attackElement;
    /* 0x18 */ s16 attack;
    /* 0x1A */ s16 unk1A;
} SpellDef;

typedef struct {
    void (*func_8017A000)(void);
    void* unk04;
    void* unk08;
    void* unk0C;
    void* unk10;
    void* unk14;
    s32 (*func_8017A018)();
    void (*func_8017A01C)(u8);
} WeaponOvl;

extern void (*D_800A0004)(); // TODO pointer to 0x50 array of functions
extern s32 D_800A0144[];
extern u32 D_800A0158;
extern s32 D_800A015C;
extern s16 D_800A0160[];
extern u8 D_800A0170[];
extern s32 D_800A0248;
extern SimFile D_800A024C[];
extern SimFile D_800A036C[];
extern SimFile D_800A04AC[];
extern s32 D_800A04EC;
extern s32 D_800A04F8;
extern s32 D_800A0510[];
extern u16 g_saveIconPalette[0x10][0x10];
extern u8* g_saveIconTexture[0x10];
extern s32 D_800A2438;
extern u8 D_800A243C[];
extern RoomBossTeleport D_800A297C[];
extern s32 D_800A2D68;
extern s32 D_800A2D6C;
extern u8 c_chPlaystationButtons[];
extern u8 c_chShoulderButtons[];
extern Unkstruct_800A2D98 D_800A2D98[];
extern u8 D_800A2EE8[];
extern u8 D_800A2EED;
extern u8 D_800A2EF8[];
extern u8 D_800A2EFD;
extern u8 D_800A2F08[];
extern u8 D_800A2F18[];
extern u8 D_800A2F28[];
extern u8 D_800A2F2D;
extern u8 D_800A2F38[];
extern u8 D_800A2F3D;
extern u16 D_800A2F48[];
extern u16 D_800A2F64[];
extern s32 D_800A2FBC[];
extern s32 D_800A2FC0[];

extern RoomTeleport D_800A245C[];
extern s32 D_800A2464[]; // D_800A245C[0].stageId
extern const char* c_strALUCARD;
extern const char** c_strSTR;
extern const char* c_strCON;
extern const char* c_strINT;
extern const char* c_strLCK;
extern const char* c_strEXP;
extern const char* c_strNEXT;
extern const char* c_strGOLD[];
extern const char* c_strLEVEL;
extern const char* c_strTIME;
extern const char* c_strROOMS;
extern const char* c_strKILLS;
extern const char* c_strHP;
extern const char* c_strMP;
extern const char* c_strHEART;
extern const char* c_strSTATUS;
extern const char* c_strButton;
extern const char* c_strCloak;
extern const char* c_strCloak2;
extern const char* c_strExterior;
extern const char* c_strLining;
extern const char* c_strButtonRightHand[];
extern const char* c_strButtonLeftHand;
extern const char* c_strButtonJump;
extern const char* c_strButtonSpecial;
extern const char* c_strButtonWolf;
extern const char* c_strButtonMist;
extern const char* c_strButtonBat;
extern const char* c_strNormal;
extern const char* c_strReversal;
extern const char* c_strSound;
extern const char* c_strStereo;
extern const char* c_strMono;
extern const char* c_strWindow;
extern const char* c_strTime;
extern const char* c_strALUCART;
extern const char* D_800A83AC[];
extern const char* c_strSSword;
extern s32 D_800A3194[];
extern Unkstruct_801092E8 D_800A37D8;
extern Lba g_StagesLba[];
extern Unsktruct_800EAF28* D_800A3B5C[];
extern SubweaponDef g_Subweapons[];
extern SpellDef g_SpellDefs[];
extern EnemyDef g_EnemyDefs[];
extern s32 c_arrExpNext[];
extern Equipment D_800A4B04[];
extern Accessory D_800A7718[];
extern Unkstruct_800A7734 D_800A7734[];
extern s8 D_800A841C[]; // related to player MP
extern u16 D_800AC958[];
extern s32 D_800ACC64[]; // probably a struct
extern Vram g_Vram;
extern CdFile* D_800ACC74[];
extern u8 D_800ACFB4[][4];
extern s32 D_800ACE48[];
extern Unkstruct_800ACEC6 D_800ACEC6;
extern u8 D_800ACF4C[];
extern s16 D_800ACF8A[]; // collection of sounds?
extern s16 D_800ACF60[]; // collection of sounds?
extern s32 D_800ADC44;
extern s32 D_800AE270[];
extern AnimationFrame* D_800AE294;
extern s16 D_800AFDA6;
extern const char* c_strEquip;
extern const char* c_strSpells;
extern const char* c_strRelics;
extern const char* c_strSystem;
extern const char* c_strFamiliars;
extern const char* c_strFamiliar;
extern const char* c_strSpecial2;
extern RECT c_backbufferClear;
extern s32 D_800B0130[];
extern s32 D_800B01B8[];
extern s32 D_800B0798[];
extern s32 D_800B07C8;
extern s32 D_800B0830[];
extern s32 D_800B083C[];
extern s32 D_800B0914;
extern s32 D_800B0918;
extern const char aPbav[];
extern const char aPbav_0[];
extern const char aPbav_1[];
extern const char aPbav_2[];
extern s16 D_800BD07C[];
extern s16 D_800BD19C[];
extern s32 D_800BD1C0;
extern s32 D_800BD1C4;
extern const char D_800DB524[];
extern const char a0104x04x;
extern const char a2304x04x;
extern const char aBlue;
extern u8 g_GfxEquipIcon[][16 * 16 / 2];
extern s16 g_PalEquipIcon[];
extern const char aDr03x;
extern const char aEff03x;
extern const char aEnv03x;
extern const char aG403x;
extern const char aGreen;
extern const char aGt303x;
extern const char aGt403x;
extern const char aHalfOff;
extern const char aHalfOn;
extern const char aLine03x;
extern const char aRed;
extern const char aRgb02x02x02x;
extern const char aSp03x;
extern const char aSp1603x;
extern const char aTile03x;
extern Unkstruct_800BF554 D_800BF554[];
extern s32 D_801362AC;
extern s32 D_801362B0;
extern s32 D_801362B4;
extern s32 D_801362B8;
extern s32 D_801362BC;
extern s32 g_DebugPalIdx;
extern u32 D_801362C4;
extern s32 D_801362C8;
extern u32* g_CurrentOT;
extern s32 D_801362D0[];
extern s32 D_801362D4;
extern s32 D_801362D8;
extern GpuUsage g_GpuMaxUsage;
extern s32 g_softResetTimer;
extern s32 D_80136300;
extern s16 D_80136308[];
extern s32 D_8013640C;
extern s32 D_80136414[];
extern SimFile* D_8013644C;
extern SimFile D_80136450;
extern s16 D_80136460[];
extern s16 D_80136C60[];
extern u8 D_80137460[]; // button timers
extern s32 D_80137470;
extern s32 D_80137474;
extern u16 D_80137478[];
extern u16 D_801374B8[];
extern u16 D_801374F8[];
extern u16 D_80137538[];
extern u8* g_DecSrcPtr;
extern u8* g_DecDstPtr;
extern s32 g_DecReadNibbleFlag;
extern s32 g_DecWriteNibbleFlag;
extern u8* D_80137590;
extern s32 D_80137594; // g_DemoKeyIdx
extern RoomLoadDef* D_801375BC;
extern s32 D_801375C8;
extern Unkstruct_800A2D98 D_801375CC;
extern s32 D_801375D4;
extern s32* D_801375D8;
extern s32 D_801375DC;
extern s32 D_801375FC;
extern s32 D_80137608;
extern s32 g_IsCloakLiningUnlocked;
extern s32 g_IsCloakColorUnlocked;
extern s32 g_IsSelectingEquipment;
extern s32 g_EquipmentCursor;
extern s32 D_80137614;
extern s32 D_80137618;

/**
 * can't use "extern MenuContext D_8013761C[]";
 * as it's 2-byte aligned
 */
extern u8 D_8013761C[];
extern s32* D_8013763A; // type MenuContext ?
extern s16 D_8013767C;
extern s16 D_80137688;
extern u16 D_8013768C;
extern u8 D_80137692;
extern u8 D_801376B0;
extern s32 D_8013783C;
extern s32 D_801377FC[];
extern s32 D_80137840;
extern s32 D_80137844[];
extern s32 D_80137848[];
extern s32 D_8013784C;
extern s32 g_StatusAttackRightHand;
extern s32 g_StatusAttackLeftHand;
extern s32 g_StatusDefenseEquip;
extern s32 g_StatusPlayerStatsTotal[];
extern s8* D_8013794C; // Pointer to texture pattern
extern s32 D_80137950;
extern s32 D_80137954;
extern s32 D_80137960;
extern s32 D_80137964;
extern s32 D_80137968;
extern s32 D_8013796C;
extern s32 D_80137970;
extern s32 D_80137974;
extern u32 D_80137978;
extern u32 D_8013797C;
extern s32 D_80137980;
extern s32 D_80137984;
extern u32 D_80137988;
extern u32 D_8013798C;
extern Unkstruct_80137990 D_80137990;
extern s32 D_80137994;
extern s32 D_80137998;
extern u32 D_8013799C;
extern s32 D_801379A0;
extern s32 D_801379A4;
extern s32 D_801379A8;
extern u16 D_801379AC[2];
extern s32 D_801379B0;
extern s32 D_80137E40;
extern s32 D_80137E44;
extern s32 D_80137E48;
extern s32 D_80137E4C;
extern s32 D_80137E50;
extern s32 D_80137E58;
extern s32 D_80137E5C;
extern s32 D_80137E60; // most likely part of the g_Cd struct
extern s32 D_80137E64; // most likely part of the g_Cd struct
extern s32 D_80137E68; // most likely part of the g_Cd struct
extern s32 D_80137F6C; // most likely part of the g_Cd struct
extern void* D_80137F7C;
extern s32 D_80137F9C;
extern s32 D_80137FB4;
extern s32 D_80138008;
extern u8 D_8013803C;
extern u8 D_80138040;
extern u8 D_80138044;
extern u8 D_80138048;
extern s32 D_8013808C;
extern s32 D_8013841C;
extern s32 D_80138430;
extern s32 D_80138438;
extern s32 D_80138440;
extern s32 D_80138444;
extern s32 D_80138454;
extern s32 D_80138460;
extern const char* D_80138784[487];
extern s32 D_80138F20;
extern u8 D_80138F24[]; // Confirmed part of an array / struct
extern u8 D_80138F2C[];
extern s32 D_80138F28;
extern s32 D_80138F7C;
extern s16 D_80138F80;
extern s32 D_80138F84[];
extern s16 D_80138FAC;
extern s32 D_80138FB0;
extern s16 D_80138FB8; // vol_l
extern s16 D_80138FBC;
extern s16 D_80138FC4;
extern s16 g_sfxRingBufferPos1; // D_80139000
extern s16 D_80139004;          // vol_r
extern s32 D_80139008;
extern s16 D_80139010;
extern s8 D_80139014;
extern s8 D_80139018[];
extern s32 g_DebugCurPal;
extern s16 D_8013901C;
extern u8 D_80139020;
extern s8 D_80139058[];
extern s16 D_8013909C;
extern u8 D_801390A0;
extern s16 D_801390A4;
extern u8 D_801390A8;
extern s16 D_801390AC[];
extern s32 D_801390B4[];
extern s8 D_801390C4;
extern GpuBuffer* g_BackBuffer;
extern u8 D_801390D8;
extern SfxRingBufferItem g_sfxRingBuffer1[]; // D_801390DC
extern u16 D_801396E4;
extern Multi D_801396E6;
extern u16 D_801396E8;
extern s16 D_801396EA;
extern s32 D_801396F0;
extern volatile s16 D_801396F4;
extern s32 D_801397FC;
extern s16 D_80139800;
extern s16 D_80139804;
extern s32 D_8013980C;
extern u8 D_80139810;
extern s16 D_80139814[];
extern s16 D_80139820;
extern s32 D_80139828[];
extern s32 D_80139834[];
extern s16 D_80139868[];
extern s16 D_80139A68;
extern s16 D_80139A6C;
extern s16 g_sfxRingBufferPos2; // D_80139A70
extern s16 D_80139A74;
extern s16 D_80139A78;
extern u16 D_8013AE7C;
extern volatile unsigned char D_8013AE80;
extern s16 D_8013AE84[];
extern s16 D_8013AE8C;
extern s16 D_8013AEA0[];
extern s16 D_8013AE94;
extern s32 D_8013AE9C;
extern s16 D_8013AED4[];
extern s16 g_volumeL;
extern s16 g_volumeR;
extern s16 D_8013B678[];
extern s16 D_8013B698;
extern s16 D_8013AEE0;
extern s8 D_8013AEE8;
extern u8 D_8013AEEC;
extern s16 D_8013AEF0;
extern s32 D_8013B158;
extern Unkstruct_8013B160 D_8013B160[];
extern s32 D_8013B3D0;
extern s16 g_sfxRingBuffer2[]; // D_8013B3E8
extern s32 D_8013B5E8;
extern s8 D_8013B5EC[];
extern s8 D_8013B614[];
extern s8 D_8013B618;
extern s32 D_8013B61C;
extern s16 D_8013B620[];
extern s32 D_8013B628[];
extern s16 D_8013B648[];
extern s16 D_8013B650[];
extern s16 D_8013B658;
extern s32 D_8013B660;
extern s16 D_8013B664;
extern s16 D_8013B668;
extern s16 D_8013B66C[];
extern u8 D_8013B680;
extern s8 D_8013B684;
extern s8 D_8013B690;
extern s32 D_8013B694;
extern s32 D_8013B69C;
extern s32 D_8016FCC0[];
extern void (*D_8013C00C)(void);
extern WeaponOvl D_8017A000;
extern WeaponOvl D_8017D000;
extern void (*D_80170000)(void);
extern ImgSrc* g_imgUnk8013C200;
extern ImgSrc* g_imgUnk8013C270;
extern u8 D_801EC000[];

void InitializePads(void);
void ReadPads(void);
void ClearBackbuffer(void);
void SetRoomForegroundLayer(LayerDef2* layerDef);
void SetRoomBackgroundLayer(s32 index, LayerDef2* layerDef);
void CheckCollision(s32 x, s32 y, Collider* res, s32 unk);
void DemoInit(s32 arg0);
void DemoUpdate(void);
void func_800209B4(s32*, s32, s32);
void func_80021E38(s32);
void func_80021EEC(void);
void func_80028D3C(s32, s32);
void func_80029FBC(s32);
void func_8002A09C(void*);
void func_8002ABF4(s32);
void func_800E346C(void);
void func_800E34A4(s8 arg0);
void func_800E34DC(s32 arg0);
void SetGameState(GameState gameState);
void func_800E4970(void);
s32 func_800E81FC(s32 id, SimFileType type);
void func_800E8D24(void);
void func_800E8DF0(void);
s32 func_800E912C(void);
s32 func_800E9208(void);
void func_800E928C(void);
void func_800E92E4(void);
void func_800E92F4(void);
void func_800EA5E4(s32);
void func_800EA538(s32);
void func_800EAD7C(void);
void func_800EAEEC(void);
void func_800EB534(s32 equipIcon, s32 palette, s32 index);
void func_800ECE2C(void);
void func_800EDA70(Primitive* prim);
void func_800EDA94(void);
void func_800EDAE4(void);
s32 AllocPrimitives(u8 type, s32 count);
s32 func_800EDD9C(u8 primitives, s32 count);
void func_800EFBF8(s32 arg0);
void FreePrimitives(s32 index);
void DemoOpenFile(s32);
void DemoInit(s32 arg0);
s32 func_800F087C(u32, u32);
bool SetNextRoomToLoad(u32 chunkX, u32 chunkY);
void func_800F1868(s32, s32, u8*);
void func_800F18C4(s32, s32);
void func_800F1954(s32, s32, s32);
void func_800F1EB0(s32, s32, s32);
void func_800F2120(void);
void func_800F223C(void);
void func_800F4994(void);
s32 func_800F4D38(s32, s32);
void func_800F4F48(void);
void func_800F4FD0(void);
bool IsAlucart(void);
void func_800F53A4(void);
bool ScissorSprite(SPRT* arg0, MenuContext* arg1);
void func_800F5904(void*, s32 x, s32 y, s32 w, u32 h, s32 u, s32 v, s32 unk1,
                   s32 unk2, bool disableTexShade, s32 unk4);
void DrawMenuSprite(MenuContext* context, s32 x, s32 y, s32 width, s32 height,
                    s32 u, s32 v, s32 clut, s32 tpage, s32 arg9,
                    s32 colorIntensity, s32 argB);
void DrawMenuRect(MenuContext* context, s32 posX, s32 posY, s32 width,
                  s32 height, s32 r, s32 g, s32 b);
s32 func_800F62E8(s32 arg0);
void func_800FF7B8(s32 arg0);
void func_800F98AC(s32 arg0, s32 arg1);
void func_800F99B8(s32 arg0, s32 arg1, s32 arg2);
void DrawMenuChar(u8 ch, int x, int y, MenuContext* context);
void DrawMenuStr(const char* str, s32 x, s32 y, MenuContext* context);
void DrawMenuInt(s32 value, s32 x, s32 y, MenuContext*);
void DrawSettingsReverseCloak(MenuContext* context);
void DrawSettingsSound(MenuContext* context);
void DrawPauseMenu(s32 arg0);
void func_800F82F4(void);
void func_800F8858(MenuContext* context);
void func_800FA7E8(void);
void func_800FABEC(s32 arg0);
void func_800FAC30(void);
void func_800FAF44(s32);
s32 func_800FD4C0(s32 bossId, s32 action);
s32 func_800FD664(s32 arg0);
s32 func_800FD6C4(s32 equipTypeFilter);
u8* func_800FD744(s32 equipTypeFilter);
u8* func_800FD760(s32 equipTypeFilter);
const char* GetEquipmentName(s32 equipTypeFilter, s32 equipId);
u32 CheckEquipmentItemCount(u32 itemId, u32 equipType);
void AddToInventory(u16 itemId, s32 itemCategory);
void func_800FD9D4(SpellDef* spell, s32 id);
s16 func_800FDB18(s32, s32);
void func_800FDCE0(s32);
void func_800FDE00(void);
s32 func_800FE3C4(SubweaponDef* subwpn, s32 subweaponId, bool useHearts);
void GetEquipProperties(s32 handId, Equipment* res, s32 equipId);
s32 func_800FE97C(s32*, s32, s32, s32);
s32 func_800FEEA4(s32, s32);
void func_800FF0A0(s32 arg0);
void func_80102CD8(s32);
void func_80102DEC(s32 arg0);
void func_80103EAC(void);
void DestroyEntity(Entity*);
void func_801065F4(s16 startIndex);
void func_801071CC(POLY_GT4* poly, u32 colorIntensity, s32 vertexIndex);
void func_80107250(POLY_GT4* poly, s32 colorIntensity);
void func_80107360(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height, s32 u,
                   s32 v);
void func_801073C0(void);
void func_801092E8(s32);
void SetPolyRect(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height);
void func_8010D584(s16 arg0);
void UpdateAnim(FrameProperty* frameProps, s32*);
void func_8010DFF0(s32, s32);
void func_8010E0A8(void);
void func_8010E0B8(void);
void func_8010E470(s32, s32);
void func_8010E570(s32);
void func_8010E83C(s32 arg0);
s32 func_801104D0();
s32 func_801106A4();
s32 func_8011081C();
s32 func_80110968();
s32 func_80110BC8();
void func_8010DBFC(s32*, s32*);
s32 func_80110DF8();
s32 func_80111018();
s32 func_801112AC();
s32 func_8011151C();
void func_80111928(void);
void func_80111CC0(void);
bool func_80111D24(void);
void func_80115394(s32*, s16, s16);
void func_80115C50(void);
void func_80118894(Entity*);
void func_80118C28(s32 arg0);
void func_80118D0C(Entity* entity);
void func_80119588(Entity* entity);
void func_80119D3C(Entity* entity);
void func_80119F70(Entity* entity);
void func_8011A3AC(Entity* entity, s32 arg1, s32 arg2,
                   Unkstruct_8011A3AC* arg3);
void func_8011A4C8(Entity* entity);
Entity* func_8011AAFC(Entity* entity, u32, s32);
void func_8011AC3C(Entity* entity);
void func_8011B190(Entity* entity);
void func_8011B334(Entity* entity);
void func_8011B480(Entity* entity);
void func_8011B530(Entity* entity);
void func_8011B5A4(Entity* entity);
void func_8011BBE0(Entity* entity);
void func_8011BDA4(Entity* entity);
void func_8011D9F8(Entity* entity);
void func_8011E0E4(Entity* entity);
void func_8011E0EC(Entity* entity);
void func_8011E390(Entity* entity);
void func_8011E4BC(Entity* entity);
void func_8011EDA0(Entity* entity);
void func_8011EDA8(Entity* entity);
void func_8011F074(Entity* entity);
void func_8011F24C(Entity* entity);
void func_8011F934(Entity* entity);
void func_801200AC(Entity* entity);
void func_80120AF8(Entity* entity);
void func_80120DD0(Entity* entity);
void func_80121980(Entity* entity);
void func_8012231C(Entity* entity);
void func_80123788(Entity* entity);
void func_801238CC(Entity* entity);
void func_80123A60(Entity* entity);
void func_80123B40(Entity* entity);
void func_80123F78(Entity* entity);
void func_801243B0(Entity* entity);
void func_80124A8C(Entity* entity);
void func_80124B88(Entity* entity);
void func_80125330(Entity* entity);
void func_80125C2C(Entity* entity);
void func_80125E68(Entity* entity);
void func_801262AC(Entity* entity);
void func_801267B0(Entity* entity);
void func_80126C48(Entity* entity);
void func_80126ECC(Entity* entity);
void func_801274DC(Entity* entity);
void func_8012768C(Entity* entity);
void func_80127840(Entity* entity);
void func_801279FC(Entity* entity);
void func_80127CC8(Entity* entity);
void func_80127F40(Entity* entity);
void func_80128714(Entity* entity);
void func_80128C2C(Entity* entity);
void func_801291C4(Entity* entity);
void func_80129864(Entity* entity);
void func_8012A0A4(Entity* entity);
void func_8012A528(Entity* entity);
void func_8012A89C(Entity* entity);
void func_8012B78C(Entity* entity);
void func_8012B990(Entity* entity);
void func_8012BEF8(Entity* entity);
void func_8012CA64(void);
void func_8012CB4C(void);
void func_8012CCE4(void);
void func_8012CFA8(void);
void func_8012F894(Entity* entity);
void func_80130264(Entity* entity);
void func_80130618(Entity* entity);
void func_801309B4(Entity* entity);
void func_80130E94(Entity* entity);
void func_8013136C(Entity* entity);
void func_801315F8(Entity* entity);
// commented as a requirement for func_80108448 to match
// void func_80131EBC(const char* str, s16 arg1);
void func_80131ED8(s32 value);
void func_80131EE8(void);
void func_80131F04(void);
s32 func_80131F28(void);
u16 func_80131F38(void);
bool func_80131F68(void);
s16 func_80131F94(void);
void func_80132134(void);
void func_8013216C(void);
void func_801321FC(void);
void func_80132264(void);
s32 func_801326D8(void);
void func_80132C2C(s16);
u8 func_80132028(u_char com, u_char* param, u_char* result);
void func_8013271C(void);
void func_80132760(void);
void func_80132A04(s16 voice, s16 vabId, s16 prog, s16 tone, s16 note,
                   s16 volume, s16 distance);
void func_801337B4(void);
bool func_80133940(void);
bool func_80133950(void);
void func_80133FCC(void);
void func_8013415C(void);
void func_801361F8(void);

#endif