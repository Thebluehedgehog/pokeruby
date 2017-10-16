#include "global.h"
#include "secret_base.h"
#include "decoration.h"
#include "event_data.h"
#include "field_camera.h"
#include "field_effect.h"
#include "field_fadetransition.h"
#include "field_player_avatar.h"
#include "field_specials.h"
#include "field_weather.h"
#include "fieldmap.h"
#include "main.h"
#include "map_constants.h"
#include "map_name_popup.h"
#include "menu.h"
#include "menu_helpers.h"
#include "metatile_behavior.h"
#include "palette.h"
#include "pokemon.h"
#include "overworld.h"
#include "script.h"
#include "sound.h"
#include "species.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "vars.h"


extern void DoDecorationSoundEffect(s16 metatileId);
extern void sub_80C6A54(s16 x, s16 y);
extern void sub_80C68A4(s16 metatileId, s16 x, s16 y);
extern void DoYellowCave4Sparkle(void);
extern void sub_80BCBF8(u8 taskId);
extern void sub_80BCC54(u8 taskId);
extern void sub_80BC824(u8 taskId);
extern void sub_80BC7D8(u8 taskId);
static void sub_80BCAEC(u8 taskId);
static void sub_80BC980(u8 taskId);
static void sub_80BC9E4(u8 taskId);
static u8 sub_80BC948(u8 a);
static void Task_SecretBasePC_Registry(u8 taskId);

extern struct YesNoFuncTable gUnknown_083D13E4;
extern struct MenuAction gUnknown_083D13D4[];
extern u8 gUnknown_020387DC;
extern u16 gSpecialVar_0x8004;
extern u16 gSpecialVar_0x8005;
extern u16 gSpecialVar_0x8006;
extern u16 gSpecialVar_0x8007;
extern u16 gScriptResult;
extern const struct
{
    u16 unk_083D1358_0;
    u16 unk_083D1358_1;
} gUnknown_083D1358[7];
extern const u8 gUnknown_083D1374[4 * 16];
extern void *gUnknown_0300485C;
extern const u8 gUnknown_083D13EC[12];
extern u8 gUnknown_0815F399[];
extern u8 gUnknown_0815F49A[];
extern u8 gUnknown_081A2E14[];
extern u8 UnknownString_81A1BB2[];
extern u8 UnknownString_81A1F67[];
extern u8 UnknownString_81A2254[];
extern u8 UnknownString_81A25C3[];
extern u8 UnknownString_81A2925[];
extern u8 UnknownString_81A1D74[];
extern u8 UnknownString_81A20C9[];
extern u8 UnknownString_81A2439[];
extern u8 UnknownString_81A2B2A[];
extern u8 UnknownString_81A2754[];


void sub_80BB4AC(struct SecretBaseRecord *record) // 080bb4ac
{
    u16 i;
    u16 j;
    record->secretBaseId = 0;
    for (i=0; i<7; i++)
        record->sbr_field_2[i] = 0xff;
    for (i=0; i<4; i++)
        record->trainerId[i] = 0x00;
    record->sbr_field_e = 0;
    record->sbr_field_10 = 0;
    record->sbr_field_11 = 0;
    record->sbr_field_1_0 = 0;
    record->gender = 0;
    record->sbr_field_1_5 = 0;
    record->sbr_field_1_6 = 0;
    for (i=0; i<16; i++) {
        record->decorations[i] = 0;
        record->decorationPos[i] = 0;
    }
    for (i=0; i<6; i++) {
        for (j=0; j<4; j++) {
            record->partyMoves[i * 4 + j] = 0;
        }
        record->partyPersonality[i] = 0;
        record->partyEVs[i] = 0;
        record->partySpecies[i] = 0;
        record->partyHeldItems[i] = 0;
        record->partyLevels[i] = 0;
    }
}

void ResetSecretBase(u8 idx) // 80bb594
{
    sub_80BB4AC(&(gSaveBlock1.secretBases[idx]));
}

void ResetSecretBases(void) // 080bb5b4
{
    u16 i;
    for (i=0; i<20; i++)
        ResetSecretBase(i);
}

void sub_80BB5D0(void) // 080bb5d0
{
    gUnknown_020387DC = gSpecialVar_0x8004;
}

void sub_80BB5E4(void) // 80bb5e4
{
    u16 idx;
    gScriptResult = 0;
    for (idx=0; idx<20; idx++) {
        if (gUnknown_020387DC != gSaveBlock1.secretBases[idx].secretBaseId)
            continue;
        gScriptResult = 1;
        VarSet(VAR_0x4054, idx);
        break;
    }
}

void sub_80BB63C(void) // 80bb63c
{
    if (gSaveBlock1.secretBases[0].secretBaseId)
        gScriptResult = 1;
    else
        gScriptResult = 0;
}

u8 sub_80BB66C(void) // 80bb66c
{
    s16 x, y;
    s16 v0;
    GetXYCoordsOneStepInFrontOfPlayer(&x, &y);
    v0 = MapGridGetMetatileBehaviorAt(x, y) & 0xFFF;
    if (v0 == 0x90 || v0 == 0x91)
        return 1;
    else if (v0 == 0x92 || v0 == 0x93)
        return 2;
    else if (v0 == 0x9a || v0 == 0x9b)
        return 3;
    else if (v0 == 0x94 || v0 == 0x95)
        return 4;
    else if (v0 == 0x96 || v0 == 0x97 || v0 == 0x9c || v0 == 0x9d)
        return 5;
    else if (v0 == 0x98 || v0 == 0x99)
        return 6;
    return 0;
}

void sub_80BB70C(void) // 80bb70c
{
    gSpecialVar_0x8007 = sub_80BB66C();
}

s16 unref_sub_80BB724(u16 *a0, u8 a1)
{
    u16 v2;
    for (v2=0; v2<0x200; v2++) {
        if ((a0[v2] & 0xFFF) == a1)
            return (s16)v2;
    }
    return -1;
}

void sub_80BB764(s16 *arg1, s16 *arg2, u16 arg3)
{
    s16 x, y;
    for (y=0; y<gMapHeader.mapData->height; y++) {
        for (x=0; x<gMapHeader.mapData->width; x++) {
            if ((gMapHeader.mapData->map[y * gMapHeader.mapData->width + x] & 0x3ff) == arg3) {
                *arg1 = x;
                *arg2 = y;
                return;
            }
        }
    }
}

void sub_80BB800(void)
{
    s16 x, y;
    s16 tile_id;
    u16 idx;
    GetXYCoordsOneStepInFrontOfPlayer(&x, &y);
    tile_id = MapGridGetMetatileIdAt(x, y);
    for (idx=0; idx<7; idx++) {
        if (gUnknown_083D1358[idx].unk_083D1358_0 == tile_id) {
            MapGridSetMetatileIdAt(x, y, gUnknown_083D1358[idx].unk_083D1358_1 | 0xc00);
            CurrentMapDrawMetatileAt(x, y);
            return;
        }
    }
    for (idx=0; idx<7; idx++) {
        if (gUnknown_083D1358[idx].unk_083D1358_1 == tile_id) {
            MapGridSetMetatileIdAt(x, y, gUnknown_083D1358[idx].unk_083D1358_0 | 0xc00);
            CurrentMapDrawMetatileAt(x, y);
            return;
        }
    }
}

u8 sub_80BB8A8(u8 *arg1)
{
    u8 idx;
    for (idx=0; idx<7; idx++) {
        if (arg1[idx] == EOS)
            return idx;
    }
    return 7;
}

void sub_80BB8CC(void)
{
    u8 nameLength;
    u16 idx;
    gSaveBlock1.secretBases[0].secretBaseId = gUnknown_020387DC;
    for (idx=0; idx<4; idx++) {
        gSaveBlock1.secretBases[0].trainerId[idx] = gSaveBlock2.playerTrainerId[idx];
    }
    VarSet(VAR_0x4054, 0);
    nameLength = sub_80BB8A8(gSaveBlock2.playerName);
    memset(gSaveBlock1.secretBases[0].sbr_field_2, 0xFF, 7);
    StringCopyN(gSaveBlock1.secretBases[0].sbr_field_2, gSaveBlock2.playerName, nameLength);
    gSaveBlock1.secretBases[0].gender = gSaveBlock2.playerGender;
    VarSet(VAR_SECRET_BASE_MAP, gMapHeader.regionMapSectionId);
}

void sub_80BB970(struct MapEvents *events)
{
    u16 bgevidx, idx, jdx;
    s16 tile_id;
    for (bgevidx=0; bgevidx<events->bgEventCount; bgevidx++) {
        if (events->bgEvents[bgevidx].kind == 8) {
            for (jdx=0; jdx<20; jdx++) {
                if (gSaveBlock1.secretBases[jdx].secretBaseId == events->bgEvents[bgevidx].bgUnion.secretBaseId) {
                    tile_id = MapGridGetMetatileIdAt(events->bgEvents[bgevidx].x + 7, events->bgEvents[bgevidx].y + 7);
                    for (idx=0; idx<7; idx++) {
                        if (gUnknown_083D1358[idx].unk_083D1358_0 == tile_id) {
                            MapGridSetMetatileIdAt(events->bgEvents[bgevidx].x + 7, events->bgEvents[bgevidx].y + 7, gUnknown_083D1358[idx].unk_083D1358_1 | 0xc00);
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
}

void sub_80BBA14(void)
{
    s8 idx = 4 * (gUnknown_020387DC / 10);
    warp1_set_2(MAP_GROUP_SECRET_BASE_RED_CAVE1, gUnknown_083D1374[idx], gUnknown_083D1374[idx + 1]);
}

void sub_80BBA48(u8 taskid)
{
    u16 curbaseid;
    switch (gTasks[taskid].data[0]) {
    case 0:
        gTasks[taskid].data[0] = 1;
        break;
    case 1:
        if (!gPaletteFade.active) {
            gTasks[taskid].data[0] = 2;
        }
        break;
    case 2:
        curbaseid = VarGet(VAR_0x4054);
        if (gSaveBlock1.secretBases[curbaseid].sbr_field_10 < 0xff)
            gSaveBlock1.secretBases[curbaseid].sbr_field_10 ++;
        sub_80BBA14();
        warp_in();
        gFieldCallback = sub_8080990;
        SetMainCallback2(CB2_LoadMap);
        DestroyTask(taskid);
        break;
    }
}

void sub_80BBAF0(void)
{
    CreateTask(sub_80BBA48, 0);
    fade_screen(1, 0);
    saved_warp2_set(0, gSaveBlock1.location.mapGroup, gSaveBlock1.location.mapNum, -1);
}

bool8 sub_80BBB24(void)
{
    if (gMapHeader.mapType == MAP_TYPE_SECRET_BASE && VarGet(VAR_0x4097) == 0)
        return FALSE;
    return TRUE;
}

void sub_80BBB50(u8 taskid)
{
    FieldObjectTurn(&(gMapObjects[gPlayerAvatar.mapObjectId]), 2);
    if (sub_807D770() == 1) {
        EnableBothScriptContexts();
        DestroyTask(taskid);
    }
}

void sub_80BBB90(void)
{
    s16 x, y;
    ScriptContext2_Enable();
    HideMapNamePopup();
    sub_80BB764(&x, &y, 0x220);
    MapGridSetMetatileIdAt(x + 7, y + 7, 0xe20);
    CurrentMapDrawMetatileAt(x + 7, y + 7);
    pal_fill_black();
    CreateTask(sub_80BBB50, 0);
}

void sub_80BBBEC(u8 taskid)
{
    s8 idx;
    if (!gPaletteFade.active) {
        idx = 4 * (gUnknown_020387DC / 10);
        Overworld_SetWarpDestination(gSaveBlock1.location.mapGroup, gSaveBlock1.location.mapNum, -1, gUnknown_083D1374[idx + 2], gUnknown_083D1374[idx + 3]);
        warp_in();
        gFieldCallback = sub_80BBB90;
        SetMainCallback2(CB2_LoadMap);
        DestroyTask(taskid);
    }
}

void sub_80BBC78(void)
{
    u8 taskid = CreateTask(sub_80BBBEC, 0);
    gTasks[taskid].data[0] = 0;
    fade_screen(1, 0);
}

bool8 CurrentMapIsSecretBase(void)
{
    if (gSaveBlock1.location.mapGroup == MAP_GROUP_SECRET_BASE_SHRUB4 && (u8)(gSaveBlock1.location.mapNum) <= MAP_ID_SECRET_BASE_SHRUB4)
        return TRUE;
    return FALSE;
}

#ifdef NONMATCHING
void sub_80BBCCC(u8 flagIn)
{
    u16 curBaseId;
    u16 x, y;
    if (CurrentMapIsSecretBase()) {
        curBaseId = VarGet(VAR_0x4054);
        for (x=0; x<16; x++) {
            if ((u8)(gSaveBlock1.secretBases[curBaseId].decorations[x] - 1) <= 0x77 && gDecorations[gSaveBlock1.secretBases[curBaseId].decorations[x]].decor_field_11 != 4) {
                sub_80FF394((gSaveBlock1.secretBases[0].decorationPos[x] >> 4) + 7, (gSaveBlock1.secretBases[0].decorationPos[x] & 0xF) + 7, gSaveBlock1.secretBases[curBaseId].decorations[x]);
            }
        }
        if (curBaseId != 0) {
            sub_80BB764(&x, &y, 0x220);
            MapGridSetMetatileIdAt(x + 7, y + 7, 0xe21);
        } else if (flagIn == 1 && VarGet(VAR_0x4089) == 1) {
            sub_80BB764(&x, &y, 0x220);
            MapGridSetMetatileIdAt(x + 7, y + 7, 0xe0a);
        }
    }
}

void sub_80BBDD0(void)
{
    u8 *roomdecor;
    u8 *roomdecorpos;
    u8 ndecor;
    u8 decidx;
    u8 objid = 0;
    u8 metatile;
    u16 curBase = VarGet(VAR_0x4054);
    if (!CurrentMapIsSecretBase()) {
        roomdecor = gSaveBlock1.playerRoomDecor;
        roomdecorpos = gSaveBlock1.playerRoomDecorPos;
        ndecor = 12;
    } else {
        roomdecor = gSaveBlock1.secretBases[curBase].decorations;
        roomdecorpos = gSaveBlock1.secretBases[curBase].decorationPos;
        ndecor = 16;
    }
    for (decidx=0; decidx<ndecor; decidx++) {
        if (roomdecor[decidx] == 0)
            continue;
        if (gDecorations[roomdecor[decidx]].decor_field_11 != 4)
            continue;
        for (objid=0; objid<gMapHeader.events->mapObjectCount; objid++) {
            if (gMapHeader.events->mapObjects[objid].flagId == gSpecialVar_0x8004 + 0xAE)
                break;
        }
        if (objid != gMapHeader.events->mapObjectCount) {
            gSpecialVar_0x8006 = roomdecorpos[decidx] >> 4;
            gSpecialVar_0x8007 = roomdecorpos[decidx] & 0xF;
            metatile = MapGridGetMetatileBehaviorAt(gSpecialVar_0x8006 + 7, gSpecialVar_0x8007 + 7);
            if (sub_80572D8(metatile) == 1 || sub_80572EC(metatile) == 1) {
                gScriptResult = gMapHeader.events->mapObjects[objid].graphicsId + 0x3f20;
                VarSet(gScriptResult, gDecorations[roomdecor[decidx]].tiles[0]);
                gScriptResult = gMapHeader.events->mapObjects[objid].localId;
                FlagClear(gSpecialVar_0x8004 + 0xAE);
                show_sprite(gScriptResult, gSaveBlock1.location.mapNum, gSaveBlock1.location.mapGroup);
                sub_805C0F8(gScriptResult, gSaveBlock1.location.mapNum, gSaveBlock1.location.mapGroup, gSpecialVar_0x8006, gSpecialVar_0x8007);
                sub_805C78C(gScriptResult, gSaveBlock1.location.mapNum, gSaveBlock1.location.mapGroup);
                gSpecialVar_0x8004 ++;
            }
        }
    }
}

#else
__attribute__((naked))
void sub_80BBCCC(u8 flagIn)
{
    asm(".syntax unified\n\
    push {r4-r7,lr}\n\
    mov r7, r8\n\
    push {r7}\n\
    sub sp, 0x4\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    mov r8, r0\n\
    bl CurrentMapIsSecretBase\n\
    lsls r0, 24\n\
    cmp r0, 0\n\
    beq _080BBDBC\n\
    ldr r0, _080BBD70 @ =0x00004054\n\
    bl VarGet\n\
    lsls r0, 16\n\
    lsrs r5, r0, 16\n\
    movs r1, 0\n\
    mov r0, sp\n\
    strh r1, [r0]\n\
    ldr r6, _080BBD74 @ =gSaveBlock1\n\
    mov r4, sp\n\
    ldr r0, _080BBD78 @ =0x00001a2a\n\
    adds r7, r6, r0\n\
_080BBCFC:\n\
    lsls r0, r5, 2\n\
    adds r0, r5\n\
    lsls r0, 5\n\
    ldrh r1, [r4]\n\
    adds r2, r0, r1\n\
    ldr r1, _080BBD7C @ =0x00001a1a\n\
    adds r0, r6, r1\n\
    adds r1, r2, r0\n\
    ldrb r0, [r1]\n\
    subs r0, 0x1\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    cmp r0, 0x77\n\
    bhi _080BBD3A\n\
    ldr r0, _080BBD80 @ =gDecorations\n\
    ldrb r3, [r1]\n\
    lsls r1, r3, 5\n\
    adds r1, r0\n\
    ldrb r0, [r1, 0x11]\n\
    cmp r0, 0x4\n\
    beq _080BBD3A\n\
    adds r0, r2, r7\n\
    ldrb r2, [r0]\n\
    lsrs r0, r2, 4\n\
    adds r0, 0x7\n\
    movs r1, 0xF\n\
    ands r1, r2\n\
    adds r1, 0x7\n\
    adds r2, r3, 0\n\
    bl sub_80FF394\n\
_080BBD3A:\n\
    ldrh r0, [r4]\n\
    adds r0, 0x1\n\
    lsls r0, 16\n\
    lsrs r0, 16\n\
    strh r0, [r4]\n\
    cmp r0, 0xF\n\
    bls _080BBCFC\n\
    cmp r5, 0\n\
    beq _080BBD88\n\
    mov r4, sp\n\
    adds r4, 0x2\n\
    movs r2, 0x88\n\
    lsls r2, 2\n\
    mov r0, sp\n\
    adds r1, r4, 0\n\
    bl sub_80BB764\n\
    mov r0, sp\n\
    ldrh r0, [r0]\n\
    adds r0, 0x7\n\
    ldrh r1, [r4]\n\
    adds r1, 0x7\n\
    ldr r2, _080BBD84 @ =0x00000e21\n\
    bl MapGridSetMetatileIdAt\n\
    b _080BBDBC\n\
    .align 2, 0\n\
_080BBD70: .4byte 0x00004054\n\
_080BBD74: .4byte gSaveBlock1\n\
_080BBD78: .4byte 0x00001a2a\n\
_080BBD7C: .4byte 0x00001a1a\n\
_080BBD80: .4byte gDecorations\n\
_080BBD84: .4byte 0x00000e21\n\
_080BBD88:\n\
    mov r0, r8\n\
    cmp r0, 0x1\n\
    bne _080BBDBC\n\
    ldr r0, _080BBDC8 @ =0x00004089\n\
    bl VarGet\n\
    lsls r0, 16\n\
    lsrs r0, 16\n\
    cmp r0, 0x1\n\
    bne _080BBDBC\n\
    mov r4, sp\n\
    adds r4, 0x2\n\
    movs r2, 0x88\n\
    lsls r2, 2\n\
    mov r0, sp\n\
    adds r1, r4, 0\n\
    bl sub_80BB764\n\
    mov r0, sp\n\
    ldrh r0, [r0]\n\
    adds r0, 0x7\n\
    ldrh r1, [r4]\n\
    adds r1, 0x7\n\
    ldr r2, _080BBDCC @ =0x00000e0a\n\
    bl MapGridSetMetatileIdAt\n\
_080BBDBC:\n\
    add sp, 0x4\n\
    pop {r3}\n\
    mov r8, r3\n\
    pop {r4-r7}\n\
    pop {r0}\n\
    bx r0\n\
    .align 2, 0\n\
_080BBDC8: .4byte 0x00004089\n\
_080BBDCC: .4byte 0x00000e0a\n\
.syntax divided\n");
}

__attribute__((naked))
void sub_80BBDD0(void)
{
    asm(".syntax unified\n\
    push {r4-r7,lr}\n\
    mov r7, r10\n\
    mov r6, r9\n\
    mov r5, r8\n\
    push {r5-r7}\n\
    sub sp, 0x14\n\
    ldr r0, _080BBE00 @ =0x00004054\n\
    bl VarGet\n\
    lsls r0, 16\n\
    lsrs r4, r0, 16\n\
    bl CurrentMapIsSecretBase\n\
    lsls r0, 24\n\
    cmp r0, 0\n\
    bne _080BBE08\n\
    ldr r0, _080BBE04 @ =gSaveBlock1 + 0x2688\n\
    str r0, [sp, 0x4]\n\
    adds r0, 0xC\n\
    str r0, [sp, 0x8]\n\
    movs r1, 0xC\n\
    str r1, [sp, 0xC]\n\
    b _080BBE1E\n\
    .align 2, 0\n\
_080BBE00: .4byte 0x00004054\n\
_080BBE04: .4byte gSaveBlock1 + 0x2688\n\
_080BBE08:\n\
    lsls r1, r4, 2\n\
    adds r1, r4\n\
    lsls r1, 5\n\
    ldr r0, _080BBF7C @ =gSaveBlock1 + 0x1A1A\n\
    adds r2, r1, r0\n\
    str r2, [sp, 0x4]\n\
    adds r0, 0x10\n\
    adds r1, r0\n\
    str r1, [sp, 0x8]\n\
    movs r3, 0x10\n\
    str r3, [sp, 0xC]\n\
_080BBE1E:\n\
    movs r6, 0\n\
    ldr r4, [sp, 0xC]\n\
    cmp r6, r4\n\
    bcc _080BBE28\n\
    b _080BBF6C\n\
_080BBE28:\n\
    ldr r5, _080BBF80 @ =gSaveBlock1\n\
    mov r10, r5\n\
_080BBE2C:\n\
    ldr r1, [sp, 0x4]\n\
    adds r0, r1, r6\n\
    ldrb r1, [r0]\n\
    mov r9, r0\n\
    adds r2, r6, 0x1\n\
    str r2, [sp, 0x10]\n\
    cmp r1, 0\n\
    bne _080BBE3E\n\
    b _080BBF5E\n\
_080BBE3E:\n\
    ldrb r0, [r0]\n\
    lsls r0, 5\n\
    ldr r3, _080BBF84 @ =gDecorations\n\
    adds r0, r3\n\
    ldrb r0, [r0, 0x11]\n\
    cmp r0, 0x4\n\
    beq _080BBE4E\n\
    b _080BBF5E\n\
_080BBE4E:\n\
    movs r5, 0\n\
    ldr r0, _080BBF88 @ =gMapHeader\n\
    ldr r2, [r0, 0x4]\n\
    ldrb r3, [r2]\n\
    mov r8, r0\n\
    cmp r5, r3\n\
    bcs _080BBE8E\n\
    ldr r0, [r2, 0x4]\n\
    ldrh r1, [r0, 0x14]\n\
    ldr r4, _080BBF8C @ =gSpecialVar_0x8004\n\
    ldrh r0, [r4]\n\
    adds r0, 0xAE\n\
    adds r7, r4, 0\n\
    cmp r1, r0\n\
    beq _080BBE8E\n\
    adds r4, r2, 0\n\
    adds r2, r3, 0\n\
_080BBE70:\n\
    adds r0, r5, 0x1\n\
    lsls r0, 24\n\
    lsrs r5, r0, 24\n\
    cmp r5, r2\n\
    bcs _080BBE8E\n\
    ldr r1, [r4, 0x4]\n\
    lsls r0, r5, 1\n\
    adds r0, r5\n\
    lsls r0, 3\n\
    adds r0, r1\n\
    ldrh r1, [r0, 0x14]\n\
    ldrh r0, [r7]\n\
    adds r0, 0xAE\n\
    cmp r1, r0\n\
    bne _080BBE70\n\
_080BBE8E:\n\
    mov r1, r8\n\
    ldr r0, [r1, 0x4]\n\
    ldrb r0, [r0]\n\
    cmp r5, r0\n\
    beq _080BBF5E\n\
    ldr r7, _080BBF90 @ =gSpecialVar_0x8006\n\
    ldr r2, [sp, 0x8]\n\
    adds r1, r2, r6\n\
    ldrb r0, [r1]\n\
    lsrs r0, 4\n\
    strh r0, [r7]\n\
    ldr r6, _080BBF94 @ =gSpecialVar_0x8007\n\
    ldrb r1, [r1]\n\
    movs r0, 0xF\n\
    ands r0, r1\n\
    strh r0, [r6]\n\
    ldrh r0, [r7]\n\
    adds r0, 0x7\n\
    ldrh r1, [r6]\n\
    adds r1, 0x7\n\
    bl MapGridGetMetatileBehaviorAt\n\
    lsls r0, 24\n\
    lsrs r4, r0, 24\n\
    adds r0, r4, 0\n\
    bl sub_80572D8\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    cmp r0, 0x1\n\
    beq _080BBEDA\n\
    adds r0, r4, 0\n\
    bl sub_80572EC\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    cmp r0, 0x1\n\
    bne _080BBF5E\n\
_080BBEDA:\n\
    mov r3, r8\n\
    ldr r0, [r3, 0x4]\n\
    ldr r1, [r0, 0x4]\n\
    lsls r4, r5, 1\n\
    adds r4, r5\n\
    lsls r4, 3\n\
    adds r1, r4, r1\n\
    ldr r5, _080BBF98 @ =0x00003f20\n\
    adds r0, r5, 0\n\
    ldrb r1, [r1, 0x1]\n\
    adds r0, r1\n\
    ldr r1, _080BBF9C @ =gScriptResult\n\
    strh r0, [r1]\n\
    ldrh r0, [r1]\n\
    mov r2, r9\n\
    ldrb r1, [r2]\n\
    lsls r1, 5\n\
    ldr r3, _080BBFA0 @ =gDecorations + 0x1C\n\
    adds r1, r3\n\
    ldr r1, [r1]\n\
    ldrh r1, [r1]\n\
    bl VarSet\n\
    mov r5, r8\n\
    ldr r0, [r5, 0x4]\n\
    ldr r0, [r0, 0x4]\n\
    adds r4, r0\n\
    ldrb r0, [r4]\n\
    ldr r1, _080BBF9C @ =gScriptResult\n\
    strh r0, [r1]\n\
    ldr r2, _080BBF8C @ =gSpecialVar_0x8004\n\
    ldrh r0, [r2]\n\
    adds r0, 0xAE\n\
    lsls r0, 16\n\
    lsrs r0, 16\n\
    bl FlagClear\n\
    ldr r3, _080BBF9C @ =gScriptResult\n\
    ldrb r0, [r3]\n\
    mov r4, r10\n\
    ldrb r1, [r4, 0x5]\n\
    ldrb r2, [r4, 0x4]\n\
    bl show_sprite\n\
    ldr r5, _080BBF9C @ =gScriptResult\n\
    ldrb r0, [r5]\n\
    ldrb r1, [r4, 0x5]\n\
    ldrb r2, [r4, 0x4]\n\
    movs r4, 0\n\
    ldrsh r3, [r7, r4]\n\
    movs r5, 0\n\
    ldrsh r4, [r6, r5]\n\
    str r4, [sp]\n\
    bl sub_805C0F8\n\
    ldr r1, _080BBF9C @ =gScriptResult\n\
    ldrb r0, [r1]\n\
    mov r2, r10\n\
    ldrb r1, [r2, 0x5]\n\
    ldrb r2, [r2, 0x4]\n\
    bl sub_805C78C\n\
    ldr r3, _080BBF8C @ =gSpecialVar_0x8004\n\
    ldrh r0, [r3]\n\
    adds r0, 0x1\n\
    strh r0, [r3]\n\
_080BBF5E:\n\
    ldr r4, [sp, 0x10]\n\
    lsls r0, r4, 24\n\
    lsrs r6, r0, 24\n\
    ldr r5, [sp, 0xC]\n\
    cmp r6, r5\n\
    bcs _080BBF6C\n\
    b _080BBE2C\n\
_080BBF6C:\n\
    add sp, 0x14\n\
    pop {r3-r5}\n\
    mov r8, r3\n\
    mov r9, r4\n\
    mov r10, r5\n\
    pop {r4-r7}\n\
    pop {r0}\n\
    bx r0\n\
    .align 2, 0\n\
_080BBF7C: .4byte gSaveBlock1 + 0x1A1A\n\
_080BBF80: .4byte gSaveBlock1\n\
_080BBF84: .4byte gDecorations\n\
_080BBF88: .4byte gMapHeader\n\
_080BBF8C: .4byte gSpecialVar_0x8004\n\
_080BBF90: .4byte gSpecialVar_0x8006\n\
_080BBF94: .4byte gSpecialVar_0x8007\n\
_080BBF98: .4byte 0x00003f20\n\
_080BBF9C: .4byte gScriptResult\n\
_080BBFA0: .4byte gDecorations + 0x1C\n\
.syntax divided\n");
}
#endif

void sub_80BBFA4(void)
{
    int curBase = VarGet(VAR_0x4054);
    VarSet(VAR_0x401F, gUnknown_083D13EC[sub_80BCCA4(curBase)]);
}

void sub_80BBFD8(s16 *position, struct MapEvents *events)
{
    s16 bgevtidx;
    for (bgevtidx=0; bgevtidx<events->bgEventCount; bgevtidx++) {
        if (events->bgEvents[bgevtidx].kind == 8 && position[0] == events->bgEvents[bgevtidx].x + 7 && position[1] == events->bgEvents[bgevtidx].y + 7) {
            gUnknown_020387DC = events->bgEvents[bgevtidx].bgUnion.secretBaseId;
            break;
        }
    }
}

void sub_80BC038(s16 *position, struct MapEvents *events)
{
    sub_80BBFD8(position, events);
    sub_80BB5E4();
    ScriptContext1_SetupScript(gUnknown_081A2E14);
}

bool8 sub_80BC050(void)
{
    sub_80BB5D0();
    sub_80BB5E4();
    if (gScriptResult == 1)
        return FALSE;
    return TRUE;
}

void sub_80BC074(u8 taskid)
{
    switch (gTasks[taskid].data[0]) {
    case 0:
        ScriptContext2_Enable();
        gTasks[taskid].data[0] = 1;
        break;
    case 1:
        if (!gPaletteFade.active) {
            gTasks[taskid].data[0] = 2;
        }
        break;
    case 2:
        copy_saved_warp2_bank_and_enter_x_to_warp1(0x7E);
        warp_in();
        gFieldCallback = mapldr_default;
        SetMainCallback2(CB2_LoadMap);
        ScriptContext2_Disable();
        DestroyTask(taskid);
        break;
    }
}

void sub_80BC0F8(void) {
    CreateTask(sub_80BC074, 0);
    fade_screen(1, 0);
}

void sub_80BC114(void) {
    if (gSaveBlock1.secretBases[0].secretBaseId != gUnknown_020387DC)
        gScriptResult = 1;
    else
        gScriptResult = 0;
}

u8 sub_80BC14C(u8 sbid)
{
    s16 idx;
    for (idx=0; idx<20; idx++) {
        if (gSaveBlock1.secretBases[idx].secretBaseId == sbid)
            return idx;
    }
    return 0;
}

u8 *sub_80BC190(u8 *dest, u8 arg1) { // 80bc190
    u8 local1;
    u8 *str;

    local1 = sub_80BB8A8(gSaveBlock1.secretBases[arg1].sbr_field_2);

    str = StringCopyN(dest, gSaveBlock1.secretBases[arg1].sbr_field_2, local1);
    str[0] = EOS;

#if ENGLISH
    return StringAppend(dest, gOtherText_PlayersBase);
#elif GERMAN
    return de_sub_8073174(dest, gOtherText_PlayersBase);
#endif
}

u8 *GetSecretBaseMapName(u8 *dest) {
    gUnknown_020387DC = gSaveBlock1.secretBases[VarGet(VAR_0x4054)].secretBaseId;
    return sub_80BC190(dest, VarGet(VAR_0x4054));
}

void sub_80BC224(void) {
    u8 *var0 = gSaveBlock1.secretBases[(u8)VarGet(VAR_0x4054)].sbr_field_2;
    u8 *var1 = gStringVar1;
    u8 var2 = sub_80BB8A8(var0);
    u8 *var3 = StringCopyN(var1, var0, var2);
    *var3 = EOS;
}

bool8 sub_80BC268(u8 i) { // 80bc268
    if (gSaveBlock1.secretBases[i].sbr_field_1_6)
        return TRUE;
    return FALSE;
}

u8 sub_80BC298(struct Pokemon *mon) { // 80bc298
    u16 evsum = GetMonData(mon, MON_DATA_HP_EV);
    evsum += GetMonData(mon, MON_DATA_ATK_EV);
    evsum += GetMonData(mon, MON_DATA_DEF_EV);
    evsum += GetMonData(mon, MON_DATA_SPD_EV);
    evsum += GetMonData(mon, MON_DATA_SPATK_EV);
    evsum += GetMonData(mon, MON_DATA_SPDEF_EV);
    return (u8)(evsum / 6);
}

#ifdef NONMATCHING
void sub_80BC300(void)
{
    u16 moveidx;
    u16 sbpartyidx = 0;
    int resetVal = 0;
    u16 partyidx = 0;
    while (partyidx < 6) {
        partyidx ++;
        for (moveidx=0; moveidx<4; moveidx++) {
            gSaveBlock1.secretBases[0].partyMoves[(partyidx - 1) * 6 + moveidx] = resetVal;
        }
        gSaveBlock1.secretBases[0].partySpecies[partyidx - 1] = resetVal;
        gSaveBlock1.secretBases[0].partyHeldItems[partyidx - 1] = resetVal;
        gSaveBlock1.secretBases[0].partyLevels[partyidx - 1] = resetVal;
        gSaveBlock1.secretBases[0].partyPersonality[partyidx - 1] = resetVal;
        gSaveBlock1.secretBases[0].partyEVs[partyidx - 1] = resetVal;
        if (GetMonData(&(gPlayerParty[partyidx - 1]), MON_DATA_SPECIES) != 0 && !GetMonData(&(gPlayerParty[partyidx - 1]), MON_DATA_IS_EGG)) {
            sbpartyidx ++;
            for (moveidx=0; moveidx<4; moveidx++) {
                gSaveBlock1.secretBases[0].partyMoves[(sbpartyidx - 1) * 6 + moveidx] = GetMonData(&(gPlayerParty[partyidx - 1]), MON_DATA_MOVE1 + moveidx);
            }
            gSaveBlock1.secretBases[0].partySpecies[sbpartyidx - 1] = GetMonData(&(gPlayerParty[partyidx - 1]), MON_DATA_SPECIES);
            gSaveBlock1.secretBases[0].partyHeldItems[sbpartyidx - 1] = GetMonData(&(gPlayerParty[partyidx - 1]), MON_DATA_HELD_ITEM);
            gSaveBlock1.secretBases[0].partyLevels[sbpartyidx - 1] = GetMonData(&(gPlayerParty[partyidx - 1]), MON_DATA_LEVEL);
            gSaveBlock1.secretBases[0].partyPersonality[sbpartyidx - 1] = GetMonData(&(gPlayerParty[partyidx - 1]), MON_DATA_PERSONALITY);
            gSaveBlock1.secretBases[0].partyEVs[sbpartyidx - 1] = sub_80BC298(&(gPlayerParty[partyidx - 1]));
        }
    }
}
#else
__attribute__((naked))
void sub_80BC300(void)
{
    asm(".syntax unified\n\
    push {r4-r7,lr}\n\
    mov r7, r10\n\
    mov r6, r9\n\
    mov r5, r8\n\
    push {r5-r7}\n\
    sub sp, 0xC\n\
    movs r0, 0\n\
    mov r10, r0\n\
    movs r6, 0\n\
    mov r9, r6\n\
_080BC314:\n\
    movs r4, 0\n\
    lsls r3, r6, 2\n\
    lsls r2, r6, 1\n\
    ldr r7, _080BC424 @ =gPlayerParty\n\
    adds r1, r6, 0x1\n\
    str r1, [sp]\n\
    adds r1, r3, 0\n\
_080BC322:\n\
    adds r0, r1, r4\n\
    lsls r0, 1\n\
    ldr r5, _080BC428 @ =gSaveBlock1 + 0x1A54\n\
    adds r0, r5, r0\n\
    mov r5, r9\n\
    strh r5, [r0]\n\
    adds r0, r4, 0x1\n\
    lsls r0, 16\n\
    lsrs r4, r0, 16\n\
    cmp r4, 0x3\n\
    bls _080BC322\n\
    ldr r1, _080BC42C @ =gSaveBlock1 + 0x1A84\n\
    adds r0, r1, r2\n\
    strh r5, [r0]\n\
    ldr r5, _080BC430 @ =gSaveBlock1 + 0x1A90\n\
    adds r0, r5, r2\n\
    mov r1, r9\n\
    strh r1, [r0]\n\
    ldr r2, _080BC434 @ =gSaveBlock1 + 0x1A9C\n\
    adds r0, r2, r6\n\
    mov r5, r9\n\
    strb r5, [r0]\n\
    ldr r1, _080BC438 @ =gSaveBlock1 + 0x1A3C\n\
    adds r0, r1, r3\n\
    mov r2, r9\n\
    str r2, [r0]\n\
    ldr r3, _080BC43C @ =gSaveBlock1 + 0x1AA2\n\
    adds r0, r3, r6\n\
    strb r2, [r0]\n\
    movs r0, 0x64\n\
    adds r5, r6, 0\n\
    muls r5, r0\n\
    adds r4, r5, r7\n\
    adds r0, r4, 0\n\
    movs r1, 0xB\n\
    bl GetMonData\n\
    cmp r0, 0\n\
    beq _080BC408\n\
    adds r0, r4, 0\n\
    movs r1, 0x2D\n\
    bl GetMonData\n\
    cmp r0, 0\n\
    bne _080BC408\n\
    movs r4, 0\n\
    mov r0, r10\n\
    lsls r0, 2\n\
    mov r8, r0\n\
    mov r1, r10\n\
    lsls r7, r1, 1\n\
    adds r1, 0x1\n\
    str r1, [sp, 0x4]\n\
    ldr r2, _080BC424 @ =gPlayerParty\n\
_080BC38E:\n\
    adds r1, r4, 0\n\
    adds r1, 0xD\n\
    adds r0, r5, r2\n\
    str r2, [sp, 0x8]\n\
    bl GetMonData\n\
    mov r3, r8\n\
    adds r1, r3, r4\n\
    lsls r1, 1\n\
    ldr r3, _080BC428 @ =gSaveBlock1 + 0x1A54\n\
    adds r1, r3, r1\n\
    strh r0, [r1]\n\
    adds r0, r4, 0x1\n\
    lsls r0, 16\n\
    lsrs r4, r0, 16\n\
    ldr r2, [sp, 0x8]\n\
    cmp r4, 0x3\n\
    bls _080BC38E\n\
    movs r0, 0x64\n\
    adds r4, r6, 0\n\
    muls r4, r0\n\
    ldr r0, _080BC424 @ =gPlayerParty\n\
    adds r4, r0\n\
    adds r0, r4, 0\n\
    movs r1, 0xB\n\
    bl GetMonData\n\
    ldr r5, _080BC42C @ =gSaveBlock1 + 0x1A84\n\
    adds r1, r5, r7\n\
    strh r0, [r1]\n\
    adds r0, r4, 0\n\
    movs r1, 0xC\n\
    bl GetMonData\n\
    ldr r2, _080BC430 @ =gSaveBlock1 + 0x1A90\n\
    adds r1, r2, r7\n\
    strh r0, [r1]\n\
    adds r0, r4, 0\n\
    movs r1, 0x38\n\
    bl GetMonData\n\
    ldr r1, _080BC434 @ =gSaveBlock1 + 0x1A9C\n\
    add r1, r10\n\
    strb r0, [r1]\n\
    adds r0, r4, 0\n\
    movs r1, 0\n\
    bl GetMonData\n\
    ldr r1, _080BC438 @ =gSaveBlock1 + 0x1A3C\n\
    add r1, r8\n\
    str r0, [r1]\n\
    adds r0, r4, 0\n\
    bl sub_80BC298\n\
    ldr r1, _080BC43C @ =gSaveBlock1 + 0x1AA2\n\
    add r1, r10\n\
    strb r0, [r1]\n\
    ldr r3, [sp, 0x4]\n\
    lsls r0, r3, 16\n\
    lsrs r0, 16\n\
    mov r10, r0\n\
_080BC408:\n\
    ldr r5, [sp]\n\
    lsls r0, r5, 16\n\
    lsrs r6, r0, 16\n\
    cmp r6, 0x5\n\
    bls _080BC314\n\
    add sp, 0xC\n\
    pop {r3-r5}\n\
    mov r8, r3\n\
    mov r9, r4\n\
    mov r10, r5\n\
    pop {r4-r7}\n\
    pop {r0}\n\
    bx r0\n\
    .align 2, 0\n\
_080BC424: .4byte gPlayerParty\n\
_080BC428: .4byte gSaveBlock1 + 0x1A54\n\
_080BC42C: .4byte gSaveBlock1 + 0x1A84\n\
_080BC430: .4byte gSaveBlock1 + 0x1A90\n\
_080BC434: .4byte gSaveBlock1 + 0x1A9C\n\
_080BC438: .4byte gSaveBlock1 + 0x1A3C\n\
_080BC43C: .4byte gSaveBlock1 + 0x1AA2\n\
.syntax divided\n");
}
#endif

void sub_80BC440(void)
{
    u16 backupValue = gSaveBlock1.secretBases[0].sbr_field_e;
    ResetSecretBase(0);
    gSaveBlock1.secretBases[0].sbr_field_e = backupValue;
    sub_80BC0F8();
}

void SecretBasePC_PackUp(void)
{
    IncrementGameStat(GAME_STAT_MOVED_SECRET_BASE);
    sub_80BC440();
}

void sub_80BC474(void)
{
    u16 eventId;
    struct MapEvents *mapEvents = gMapHeader.events;
    for (eventId = 0; eventId < mapEvents->bgEventCount; eventId++)
    {
        if (mapEvents->bgEvents[eventId].kind == 8
            && gSaveBlock1.secretBases[0].secretBaseId == mapEvents->bgEvents[eventId].bgUnion.secretBaseId)
        {
            u16 i;
            s16 tileId = MapGridGetMetatileIdAt(mapEvents->bgEvents[eventId].x + 7, mapEvents->bgEvents[eventId].y + 7);

            for (i = 0; i < 7; i++)
            {
                if (gUnknown_083D1358[i].unk_083D1358_1 == tileId)
                {
                    MapGridSetMetatileIdAt(
                        mapEvents->bgEvents[eventId].x + 7,
                        mapEvents->bgEvents[eventId].y + 7,
                        gUnknown_083D1358[i].unk_083D1358_0 | 0xc00);
                    break;
                }
            }

            DrawWholeMapView();
            break;
        }
    }
}

void sub_80BC50C(void)
{
    u16 backupValue;
    sub_80BC474();
    IncrementGameStat(GAME_STAT_MOVED_SECRET_BASE);

    backupValue = gSaveBlock1.secretBases[0].sbr_field_e;
    ResetSecretBase(0);
    gSaveBlock1.secretBases[0].sbr_field_e = backupValue;
}

u8 sub_80BC538(void)
{
    s16 secretBaseIndex;
    u8 retVal = 0;
    
    for (secretBaseIndex = 1; secretBaseIndex < 20; secretBaseIndex++)
    {
        if (sub_80BC268(secretBaseIndex) == TRUE)
        {
            retVal++;
        }
    }

    return retVal;
}

void sub_80BC56C(void)
{
    u8 secretBaseIndex = sub_80BC14C(gUnknown_020387DC);
    if (sub_80BC268(secretBaseIndex) == TRUE)
    {
        gScriptResult = 1;
    }
    else if (sub_80BC538() > 9)
    {
        gScriptResult = 2;
    }
    else
    {
        gScriptResult = 0;
    }
}

void sub_80BC5BC(void)
{
    gSaveBlock1.secretBases[sub_80BC14C(gUnknown_020387DC)].sbr_field_1_6 ^= 1;
    FlagSet(0x10C);
}

void SecretBasePC_Decoration(void)
{
    CreateTask(Task_SecretBasePC_Decoration, 0);
}

void SecretBasePC_Registry(void)
{
    CreateTask(Task_SecretBasePC_Registry, 0);
}

void Task_SecretBasePC_Registry(u8 taskId)
{
    s16 *taskData;

    ScriptContext2_Enable();
    sub_80F944C();
    LoadScrollIndicatorPalette();
    
    taskData = &gTasks[taskId].data[0];
    taskData[0] = sub_80BC538();
    if (taskData[0] != 0)
    {
        if (taskData[0] > 7) {
            taskData[3] = 7;
        }
        else
        {
            taskData[3] = taskData[0];
        }

        taskData[1] = 0;
        taskData[2] = 0;

        MenuZeroFillWindowRect(0, 0, 29, 19);
        sub_80BC7D8(taskId);

        gTasks[taskId].func = sub_80BC824;
    }
    else
    {
        DisplayItemMessageOnField(taskId, gSecretBaseText_NoRegistry, sub_80BCC54, 0);
    }
}

#ifdef NONMATCHING
void sub_80BC6B0(u8 taskId)
{
    s16 *taskData = gTasks[taskId].data;
    u8 count = 0;
    u8 var1 = 0;
    u8 i = 1;

    if (var1 == taskData[2])
    {
        count = 1;
    }
    else
    {
        while (1)
        {
            if (sub_80BC268(i) == TRUE)
            {
                count++;
            }

            i++;
            if (i > 19)
            {
                break;
            }

            if (count == taskData[2])
            {
                count = i;
                break;
            }
        }
    }

    while (count < 20)
    {
        if (sub_80BC268(count) == TRUE)
        {
            sub_80BC190(gStringVar1, count);
            MenuFillWindowRectWithBlankTile(18, var1 * 2 + 2, 28, var1 * 2 + 3);
            MenuPrint(gStringVar1, 18, var1 * 2 + 2);

            var1++;
            if (var1 == 8)
            {
                break;
            }
        }

        count++;
    }

    if (var1 < 8)
    {
        MenuFillWindowRectWithBlankTile(18, var1 * 2 + 2, 28, var1 * 2 + 3);
        MenuPrint(gUnknownText_Exit, 18, var1 * 2 + 2);
        DestroyVerticalScrollIndicator(1);

        if (var1 != 7)
        {
            MenuFillWindowRectWithBlankTile(18, (((var1 << 25) + 0x4000000)) >> 24, 28, 18);
        }
    }
    else
    {
        CreateVerticalScrollIndicators(1, 188, 152);
    }

    if (taskData[2] == 0)
    {
        DestroyVerticalScrollIndicator(0);
    }
    else
    {
        CreateVerticalScrollIndicators(0, 188, 8);
    }
}
#else
__attribute__((naked))
void sub_80BC6B0(u8 taskId)
{
    asm(".syntax unified\n\
    push {r4-r7,lr}\n\
    mov r7, r8\n\
    push {r7}\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    lsls r1, r0, 2\n\
    adds r1, r0\n\
    lsls r1, 3\n\
    ldr r0, _080BC6D8 @ =gTasks + 0x8\n\
    adds r1, r0\n\
    mov r8, r1\n\
    movs r4, 0\n\
    movs r6, 0\n\
    movs r5, 0x1\n\
    movs r2, 0x4\n\
    ldrsh r0, [r1, r2]\n\
    cmp r6, r0\n\
    bne _080BC6DC\n\
    movs r4, 0x1\n\
    b _080BC706\n\
    .align 2, 0\n\
_080BC6D8: .4byte gTasks + 0x8\n\
_080BC6DC:\n\
    adds r0, r5, 0\n\
    bl sub_80BC268\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    cmp r0, 0x1\n\
    bne _080BC6F0\n\
    adds r0, r4, 0x1\n\
    lsls r0, 24\n\
    lsrs r4, r0, 24\n\
_080BC6F0:\n\
    adds r0, r5, 0x1\n\
    lsls r0, 24\n\
    lsrs r5, r0, 24\n\
    cmp r5, 0x13\n\
    bhi _080BC706\n\
    mov r1, r8\n\
    movs r2, 0x4\n\
    ldrsh r0, [r1, r2]\n\
    cmp r4, r0\n\
    bne _080BC6DC\n\
    adds r4, r5, 0\n\
_080BC706:\n\
    adds r5, r4, 0\n\
    cmp r5, 0x13\n\
    bhi _080BC75A\n\
    ldr r7, _080BC7A0 @ =gStringVar1\n\
_080BC70E:\n\
    adds r0, r5, 0\n\
    bl sub_80BC268\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    cmp r0, 0x1\n\
    bne _080BC750\n\
    adds r0, r7, 0\n\
    adds r1, r5, 0\n\
    bl sub_80BC190\n\
    lsls r3, r6, 1\n\
    adds r4, r3, 0x2\n\
    lsls r4, 24\n\
    lsrs r4, 24\n\
    adds r3, 0x3\n\
    lsls r3, 24\n\
    lsrs r3, 24\n\
    movs r0, 0x12\n\
    adds r1, r4, 0\n\
    movs r2, 0x1C\n\
    bl MenuFillWindowRectWithBlankTile\n\
    adds r0, r7, 0\n\
    movs r1, 0x12\n\
    adds r2, r4, 0\n\
    bl MenuPrint\n\
    adds r0, r6, 0x1\n\
    lsls r0, 24\n\
    lsrs r6, r0, 24\n\
    cmp r6, 0x8\n\
    beq _080BC75A\n\
_080BC750:\n\
    adds r0, r5, 0x1\n\
    lsls r0, 24\n\
    lsrs r5, r0, 24\n\
    cmp r5, 0x13\n\
    bls _080BC70E\n\
_080BC75A:\n\
    cmp r6, 0x7\n\
    bhi _080BC7A8\n\
    lsls r3, r6, 1\n\
    adds r4, r3, 0x2\n\
    lsls r4, 24\n\
    lsrs r4, 24\n\
    adds r3, 0x3\n\
    lsls r3, 24\n\
    lsrs r3, 24\n\
    movs r0, 0x12\n\
    adds r1, r4, 0\n\
    movs r2, 0x1C\n\
    bl MenuFillWindowRectWithBlankTile\n\
    ldr r0, _080BC7A4 @ =gUnknownText_Exit\n\
    movs r1, 0x12\n\
    adds r2, r4, 0\n\
    bl MenuPrint\n\
    movs r0, 0x1\n\
    bl DestroyVerticalScrollIndicator\n\
    cmp r6, 0x7\n\
    beq _080BC7B2\n\
    lsls r1, r6, 25\n\
    movs r0, 0x80\n\
    lsls r0, 19\n\
    adds r1, r0\n\
    lsrs r1, 24\n\
    movs r0, 0x12\n\
    movs r2, 0x1C\n\
    movs r3, 0x12\n\
    bl MenuFillWindowRectWithBlankTile\n\
    b _080BC7B2\n\
    .align 2, 0\n\
_080BC7A0: .4byte gStringVar1\n\
_080BC7A4: .4byte gUnknownText_Exit\n\
_080BC7A8:\n\
    movs r0, 0x1\n\
    movs r1, 0xBC\n\
    movs r2, 0x98\n\
    bl CreateVerticalScrollIndicators\n\
_080BC7B2:\n\
    mov r1, r8\n\
    movs r2, 0x4\n\
    ldrsh r0, [r1, r2]\n\
    cmp r0, 0\n\
    bne _080BC7C4\n\
    movs r0, 0\n\
    bl DestroyVerticalScrollIndicator\n\
    b _080BC7CE\n\
_080BC7C4:\n\
    movs r0, 0\n\
    movs r1, 0xBC\n\
    movs r2, 0x8\n\
    bl CreateVerticalScrollIndicators\n\
_080BC7CE:\n\
    pop {r3}\n\
    mov r8, r3\n\
    pop {r4-r7}\n\
    pop {r0}\n\
    bx r0\n\
    .syntax divided\n");
}
#endif

void sub_80BC7D8(u8 taskId)
{
    u16 *taskData = &gTasks[taskId].data[0];
    MenuDrawTextWindow(17, 0, 29, 19);
    InitMenu(0, 18, 2, taskData[3] + 1, taskData[1], 11);
    sub_80BC6B0(taskId);
}

void sub_80BC824(u8 taskId)
{
    s16 *taskData = gTasks[taskId].data;

    if (gMain.newAndRepeatedKeys & DPAD_UP)
    {
        if (taskData[1])
        {
            PlaySE(5);
            taskData[1] = MoveMenuCursor(-1);
        }
        else if (taskData[2])
        {
            PlaySE(5);
            taskData[2]--;
            sub_80BC6B0(taskId);
        }
        else
        {
            return;
        }
    }
    else if (gMain.newAndRepeatedKeys & DPAD_DOWN)
    {
        if (taskData[1] == taskData[3])
        {
            if (taskData[2] + taskData[1] != taskData[0])
            {
                PlaySE(5);
                taskData[2]++;
                sub_80BC6B0(taskId);
            }
        }
        else
        {
            PlaySE(5);
            taskData[1] = MoveMenuCursor(1);
        }
    }
    else if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(5);
        if (taskData[1] + taskData[2] == taskData[0])
        {
            HandleDestroyMenuCursors();
            MenuZeroFillWindowRect(0, 0, 29, 19);
            sub_80BCC54(taskId);
        }
        else
        {
            HandleDestroyMenuCursors();
            taskData[4] = sub_80BC948(taskData[1] + taskData[2]);
            sub_80BC980(taskId);
        }
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        PlaySE(5);
        HandleDestroyMenuCursors();
        MenuZeroFillWindowRect(0, 0, 29, 19);
        sub_80BCC54(taskId);
    }
}

u8 sub_80BC948(u8 a)
{
    u8 secretBaseIndex;
    u8 count = 0;

    for (secretBaseIndex = 1; secretBaseIndex < 20; secretBaseIndex++)
    {
        if (sub_80BC268(secretBaseIndex) == TRUE)
        {
            if (a == count)
            {
                return secretBaseIndex;
            }
            else
            {
                count++;
            }
        }
    }

    return 0;
}

void sub_80BC980(u8 taskId)
{
    PauseVerticalScrollIndicator(0);
    PauseVerticalScrollIndicator(1);
    MenuDrawTextWindow(1, 0, 12, 5);
    PrintMenuItems(2, 1, 2, gUnknown_083D13D4);
    InitMenu(0, 2, 1, 2, 0, 10);
    gTasks[taskId].func = sub_80BC9E4;
}

void sub_80BC9E4(u8 taskId)
{
    if (gMain.newAndRepeatedKeys & DPAD_UP)
    {
        if (GetMenuCursorPos())
        {
            PlaySE(5);
            MoveMenuCursor(-1);
        }
    }
    else if (gMain.newAndRepeatedKeys & DPAD_DOWN)
    {
        if (GetMenuCursorPos() != 1)
        {
            PlaySE(5);
            MoveMenuCursor(1);
        }
    }
    else if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(5);
        gUnknown_083D13D4[GetMenuCursorPos()].func(taskId);
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        PlaySE(5);
        sub_80BCBF8(taskId);
    }
}

void sub_80BCA84(u8 taskId)
{
    s16 *taskData = gTasks[taskId].data;

    DestroyVerticalScrollIndicator(0);
    DestroyVerticalScrollIndicator(1);
    HandleDestroyMenuCursors();
    MenuZeroFillWindowRect(0, 0, 29, 19);

    sub_80BC190(gStringVar1, taskData[4]);
    StringExpandPlaceholders(gStringVar4, gOtherText_OkayToDeleteFromRegistry);
    DisplayItemMessageOnField(taskId, gStringVar4, sub_80BCAEC, 0);
}

void sub_80BCAEC(u8 taskId)
{
    DisplayYesNoMenu(20, 8, 1);
    DoYesNoFuncWithChoice(taskId, &gUnknown_083D13E4);
}

void sub_80BCB10(u8 taskId)
{
    s16 *taskData = gTasks[taskId].data;

    MenuZeroFillWindowRect(0, 0, 29, 19);

    gSaveBlock1.secretBases[taskData[4]].sbr_field_1_6 = 0;
    taskData[0]--;

    if (taskData[2] > 0)
    {
        taskData[2]--;
    }

    if (taskData[0] < 8)
    {
        taskData[3]--;
    }

    sub_80BC7D8(taskId);
    gTasks[taskId].func = sub_80BC824;
}

void sub_80BCB90(u8 taskId)
{
    MenuZeroFillWindowRect(20, 8, 26, 13);
    DisplayItemMessageOnField(taskId, gOtherText_RegisteredDataDeleted, sub_80BCB10, 0);
}

void sub_80BCBC0(u8 taskId)
{
    MenuZeroFillWindowRect(0, 0, 29, 19);

    sub_80BC7D8(taskId);
    gTasks[taskId].func = sub_80BC824;
}

void sub_80BCBF8(u8 taskId)
{
    s16 *taskData = gTasks[taskId].data;

    InitMenu(0, 18, 2, taskData[3] + 1, taskData[1], 11);
    MenuZeroFillWindowRect(1, 0, 12, 5);
    StartVerticalScrollIndicators(0);
    StartVerticalScrollIndicators(1);

    gTasks[taskId].func = sub_80BC824;
}

void sub_80BCC54(u8 taskId)
{
    u16 curBaseIndex = VarGet(VAR_0x4054);

    BuyMenuFreeMemory();
    DestroyVerticalScrollIndicator(0);
    DestroyVerticalScrollIndicator(1);

    if (curBaseIndex == 0)
    {
        ScriptContext1_SetupScript(gUnknown_0815F399);
    }
    else
    {
        ScriptContext1_SetupScript(gUnknown_0815F49A);
    }

    DestroyTask(taskId);
}

u8 sub_80BCCA4(u8 secretBaseIndex)
{
    return (gSaveBlock1.secretBases[secretBaseIndex].sbr_field_2[7] % 5) 
        + gSaveBlock1.secretBases[secretBaseIndex].gender * 5;
}

u8 *sub_80BCCE8(void)
{
    u8 var1 = sub_80BCCA4(VarGet(VAR_0x4054));

    if (var1 == 0)
    {
        return UnknownString_81A1BB2;
    }
    else if (var1 == 1)
    {
        return UnknownString_81A1F67;
    }
    else if (var1 == 2)
    {
        return UnknownString_81A2254;
    }
    else if (var1 == 3)
    {
        return UnknownString_81A25C3;
    }
    else if (var1 == 4)
    {
        return UnknownString_81A2925;
    }
    else if (var1 == 5)
    {
        return UnknownString_81A1D74;
    }
    else if (var1 == 6)
    {
        return UnknownString_81A20C9;
    }
    else if (var1 == 7)
    {
        return UnknownString_81A2439;
    }
    else if (var1 == 8)
    {
        return UnknownString_81A2754;
    }
    else
    {
        return UnknownString_81A2B2A;
    }
}

// Debugging function to test secret base battles.
void unref_sub_80BCD7C(u8 secretBaseIndex)
{
    u16 i;
    for (i = 0; i == 0; i++)
    {
        gSaveBlock1.secretBases[secretBaseIndex].partyPersonality[i] = i + 1;
        gSaveBlock1.secretBases[secretBaseIndex].partyMoves[i * 4] = i + 1;
        gSaveBlock1.secretBases[secretBaseIndex].partySpecies[i] = SPECIES_TREECKO;
        gSaveBlock1.secretBases[secretBaseIndex].partyHeldItems[i] = i + 1;
        gSaveBlock1.secretBases[secretBaseIndex].partyLevels[i] = i + 5;
        gSaveBlock1.secretBases[secretBaseIndex].partyEVs[i] = i * 5;
    }
}

void sub_80BCE1C(void)
{
    u16 curBaseIndex = VarGet(VAR_0x4054);
    sub_810FB10(1);

    CreateSecretBaseEnemyParty(&gSaveBlock1.secretBases[curBaseIndex]);
}

void sub_80BCE4C()
{
    gSaveBlock1.secretBases[VarGet(VAR_0x4054)].sbr_field_1_5 = gScriptResult;
}

void sub_80BCE90()
{
    u16 curBaseIndex = VarGet(VAR_0x4054);

    if (!FlagGet(0x8C2))
    {
        u8 i;

        for (i = 0; i < 20; i++)
        {
            gSaveBlock1.secretBases[i].sbr_field_1_5 = 0;
        }

        FlagSet(0x8C2);
    }

    gSpecialVar_0x8004 = sub_80BCCA4(curBaseIndex);
    gScriptResult = gSaveBlock1.secretBases[curBaseIndex].sbr_field_1_5;
}

void sub_80BCF1C(u8 taskId)
{
    s16 x, y;
    u32 behavior;
    s16 *taskData = gTasks[taskId].data;

    switch (taskData[1])
    {
    case 0:
        PlayerGetDestCoords(&taskData[2], &taskData[3]);
        taskData[1] = 1;
        break;
    case 1:
        PlayerGetDestCoords(&x, &y);
        if (x != taskData[2] || y != taskData[3])
        {
            taskData[2] = x;
            taskData[3] = y;

            behavior = MapGridGetMetatileBehaviorAt(x, y);
            if (sub_8057350(behavior) == TRUE)
            {
                DoYellowCave4Sparkle();
            }
            else if (sub_8057314(behavior) == TRUE)
            {
                sub_80C68A4(MapGridGetMetatileIdAt(x, y), x, y);
            }
            else if (sub_8057328(behavior) == TRUE)
            {
                sub_80C6A54(x, y);
            }
            else if (sub_805733C(behavior) == TRUE)
            {
                DoDecorationSoundEffect(MapGridGetMetatileIdAt(x, y));
            }
        }
        break;
    case 2:
        if (!FieldEffectActiveListContains(taskData[4]))
        {
            taskData[1] = 1;
        }
        break;
    }
}

void sub_80BD034(u8 i, struct SecretBaseRecord *secretBase)
{
    gSaveBlock1.secretBases[i] = *secretBase;
    gSaveBlock1.secretBases[i].sbr_field_1_6 = 2;
}

bool8 sub_80BD070(struct SecretBaseRecord *baseA, struct SecretBaseRecord *baseB)
{
    u8 i;

    for (i = 0; i < 4; i++)
    {
        if (baseA->trainerId[i] != baseB->trainerId[i])
        {
            return FALSE;
        }
    }

    return TRUE;
}

bool8 sub_80BD0A0(struct SecretBaseRecord *baseA, struct SecretBaseRecord *baseB)
{
    u8 i;

    for (i = 0; i < 7 && (baseA->sbr_field_2[i] != 0xFF || baseB->sbr_field_2[i] != 0xFF); i++)
    {
        if (baseA->sbr_field_2[i] != baseB->sbr_field_2[i])
        {
            return FALSE;
        }
    }

    return TRUE;
}

bool8 sub_80BD0EC(struct SecretBaseRecord *baseA, struct SecretBaseRecord *baseB)
{
    if (baseA->gender == baseB->gender && sub_80BD070(baseA, baseB) && sub_80BD0A0(baseA, baseB))
    {
        return TRUE;
    }


    return FALSE;
}

s16 sub_80BD12C(u8 secretBaseId)
{
    s16 i;

    for (i = 0; i < 20; i++)
    {
        if (gSaveBlock1.secretBases[i].secretBaseId == secretBaseId)
        {
            return i;
        }
    }

    return -1;
}

u8 sub_80BD170(void)
{
    s16 i;

    for (i = 1; i < 20; i++)
    {
        if (gSaveBlock1.secretBases[i].secretBaseId == 0)
        {
            return i;
        }
    }

    return 0;
}

u8 sub_80BD1B0(void)
{
    s16 i;

    for (i = 1; i < 20; i++)
    {
        if (gSaveBlock1.secretBases[i].sbr_field_1_6 == 0 && gSaveBlock1.secretBases[i].sbr_field_1_0 == 0)
        {
            return i;
        }
    }

    return 0;
}
