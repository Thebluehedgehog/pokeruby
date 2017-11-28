	.include "constants/gba_constants.inc"
	.include "asm/macros.inc"

	.syntax unified

	.text

	@ bug

	thumb_func_start sub_80DC824
sub_80DC824: @ 80DC824
	push {r4-r6,lr}
	adds r6, r0, 0
	bl NotInBattle
	lsls r0, 24
	cmp r0, 0
	beq _080DC850
	adds r0, r6, 0
	movs r1, 0x2
	bl StartSpriteAffineAnim
	ldr r0, _080DC84C @ =gBattleAnimArgs
	ldrh r1, [r0, 0x4]
	negs r1, r1
	strh r1, [r0, 0x4]
	ldrh r1, [r0]
	negs r1, r1
	strh r1, [r0]
	b _080DC880
	.align 2, 0
_080DC84C: .4byte gBattleAnimArgs
_080DC850:
	ldr r0, _080DC8E4 @ =gBattleAnimBankTarget
	ldrb r0, [r0]
	bl GetBankSide
	lsls r0, 24
	cmp r0, 0
	bne _080DC880
	adds r0, r6, 0
	movs r1, 0x1
	bl StartSpriteAffineAnim
	ldr r1, _080DC8E8 @ =gBattleAnimArgs
	ldrh r0, [r1, 0x2]
	negs r0, r0
	strh r0, [r1, 0x2]
	ldrh r0, [r1, 0x4]
	negs r0, r0
	strh r0, [r1, 0x4]
	ldrh r0, [r1, 0x6]
	negs r0, r0
	strh r0, [r1, 0x6]
	ldrh r0, [r1]
	negs r0, r0
	strh r0, [r1]
_080DC880:
	ldr r5, _080DC8E4 @ =gBattleAnimBankTarget
	ldrb r0, [r5]
	movs r1, 0x2
	bl sub_8077EE4
	lsls r0, 24
	ldr r4, _080DC8E8 @ =gBattleAnimArgs
	lsrs r0, 24
	ldrh r1, [r4]
	adds r0, r1
	strh r0, [r6, 0x20]
	ldrb r0, [r5]
	movs r1, 0x3
	bl sub_8077EE4
	lsls r0, 24
	lsrs r0, 24
	ldrh r1, [r4, 0x2]
	adds r0, r1
	strh r0, [r6, 0x22]
	ldrh r0, [r4, 0x8]
	strh r0, [r6, 0x2E]
	ldrb r0, [r5]
	movs r1, 0x2
	bl sub_8077ABC
	lsls r0, 24
	lsrs r0, 24
	ldrh r1, [r4, 0x4]
	adds r0, r1
	strh r0, [r6, 0x32]
	ldrb r0, [r5]
	movs r1, 0x3
	bl sub_8077ABC
	lsls r0, 24
	lsrs r0, 24
	ldrh r4, [r4, 0x6]
	adds r0, r4
	strh r0, [r6, 0x36]
	ldr r0, _080DC8EC @ =sub_8078B34
	str r0, [r6, 0x1C]
	ldr r1, _080DC8F0 @ =move_anim_8072740
	adds r0, r6, 0
	bl StoreSpriteCallbackInData
	pop {r4-r6}
	pop {r0}
	bx r0
	.align 2, 0
_080DC8E4: .4byte gBattleAnimBankTarget
_080DC8E8: .4byte gBattleAnimArgs
_080DC8EC: .4byte sub_8078B34
_080DC8F0: .4byte move_anim_8072740
	thumb_func_end sub_80DC824

	thumb_func_start sub_80DC8F4
sub_80DC8F4: @ 80DC8F4
	push {r4-r6,lr}
	adds r6, r0, 0
	bl NotInBattle
	lsls r0, 24
	cmp r0, 0
	beq _080DC918
	ldr r1, _080DC914 @ =gBattleAnimArgs
	ldrh r0, [r1]
	negs r0, r0
	strh r0, [r1]
	adds r0, r6, 0
	movs r1, 0x2
	bl StartSpriteAffineAnim
	b _080DC934
	.align 2, 0
_080DC914: .4byte gBattleAnimArgs
_080DC918:
	ldr r0, _080DC990 @ =gBattleAnimBankTarget
	ldrb r0, [r0]
	bl GetBankSide
	lsls r0, 24
	cmp r0, 0
	bne _080DC934
	ldr r0, _080DC994 @ =gBattleAnimArgs
	ldrh r1, [r0, 0x2]
	negs r1, r1
	strh r1, [r0, 0x2]
	ldrh r1, [r0]
	negs r1, r1
	strh r1, [r0]
_080DC934:
	ldr r5, _080DC990 @ =gBattleAnimBankTarget
	ldrb r0, [r5]
	movs r1, 0x2
	bl sub_8077EE4
	lsls r0, 24
	ldr r4, _080DC994 @ =gBattleAnimArgs
	lsrs r0, 24
	ldrh r1, [r4]
	adds r0, r1
	strh r0, [r6, 0x20]
	ldrb r0, [r5]
	movs r1, 0x3
	bl sub_8077EE4
	lsls r0, 24
	lsrs r0, 24
	ldrh r1, [r4, 0x2]
	adds r0, r1
	strh r0, [r6, 0x22]
	ldrh r0, [r4, 0x4]
	strh r0, [r6, 0x2E]
	ldrb r0, [r5]
	movs r1, 0x2
	bl sub_8077ABC
	lsls r0, 24
	lsrs r0, 24
	strh r0, [r6, 0x32]
	ldrb r0, [r5]
	movs r1, 0x3
	bl sub_8077ABC
	lsls r0, 24
	lsrs r0, 24
	strh r0, [r6, 0x36]
	ldr r0, _080DC998 @ =sub_8078B34
	str r0, [r6, 0x1C]
	ldr r1, _080DC99C @ =move_anim_8072740
	adds r0, r6, 0
	bl StoreSpriteCallbackInData
	pop {r4-r6}
	pop {r0}
	bx r0
	.align 2, 0
_080DC990: .4byte gBattleAnimBankTarget
_080DC994: .4byte gBattleAnimArgs
_080DC998: .4byte sub_8078B34
_080DC99C: .4byte move_anim_8072740
	thumb_func_end sub_80DC8F4

	thumb_func_start sub_80DC9A0
sub_80DC9A0: @ 80DC9A0
	push {r4,r5,lr}
	adds r5, r0, 0
	bl NotInBattle
	lsls r0, 24
	cmp r0, 0
	beq _080DC9BC
	ldr r0, _080DC9FC @ =gBattleAnimArgs
	movs r2, 0x4
	ldrsh r1, [r0, r2]
	lsrs r2, r1, 31
	adds r1, r2
	asrs r1, 1
	strh r1, [r0, 0x4]
_080DC9BC:
	adds r0, r5, 0
	movs r1, 0x1
	bl sub_80787B0
	ldr r1, _080DC9FC @ =gBattleAnimArgs
	ldrh r0, [r1, 0x4]
	strh r0, [r5, 0x2E]
	ldrh r0, [r5, 0x20]
	strh r0, [r5, 0x30]
	ldrh r0, [r5, 0x22]
	strh r0, [r5, 0x34]
	movs r2, 0x8
	ldrsh r0, [r1, r2]
	cmp r0, 0
	bne _080DCA04
	ldr r4, _080DCA00 @ =gBattleAnimBankTarget
	ldrb r0, [r4]
	movs r1, 0x2
	bl sub_8077ABC
	lsls r0, 24
	lsrs r0, 24
	strh r0, [r5, 0x32]
	ldrb r0, [r4]
	movs r1, 0x3
	bl sub_8077ABC
	lsls r0, 24
	lsrs r0, 24
	strh r0, [r5, 0x36]
	b _080DCA16
	.align 2, 0
_080DC9FC: .4byte gBattleAnimArgs
_080DCA00: .4byte gBattleAnimBankTarget
_080DCA04:
	ldr r0, _080DCA2C @ =gBattleAnimBankTarget
	ldrb r0, [r0]
	adds r2, r5, 0
	adds r2, 0x32
	adds r3, r5, 0
	adds r3, 0x36
	movs r1, 0x1
	bl sub_807A3FC
_080DCA16:
	adds r0, r5, 0
	bl sub_8078BD4
	ldr r0, _080DCA30 @ =gBattleAnimArgs
	ldrh r0, [r0, 0x6]
	strh r0, [r5, 0x38]
	ldr r0, _080DCA34 @ =sub_80DCA38
	str r0, [r5, 0x1C]
	pop {r4,r5}
	pop {r0}
	bx r0
	.align 2, 0
_080DCA2C: .4byte gBattleAnimBankTarget
_080DCA30: .4byte gBattleAnimArgs
_080DCA34: .4byte sub_80DCA38
	thumb_func_end sub_80DC9A0

	thumb_func_start sub_80DCA38
sub_80DCA38: @ 80DCA38
	push {r4,lr}
	adds r4, r0, 0
	bl sub_8078B5C
	lsls r0, 24
	cmp r0, 0
	beq _080DCA4E
	adds r0, r4, 0
	bl move_anim_8072740
	b _080DCA6A
_080DCA4E:
	movs r1, 0x3A
	ldrsh r0, [r4, r1]
	movs r2, 0x38
	ldrsh r1, [r4, r2]
	bl Sin
	ldrh r1, [r4, 0x24]
	adds r0, r1
	strh r0, [r4, 0x24]
	ldrh r0, [r4, 0x3A]
	adds r0, 0xD
	movs r1, 0xFF
	ands r0, r1
	strh r0, [r4, 0x3A]
_080DCA6A:
	pop {r4}
	pop {r0}
	bx r0
	thumb_func_end sub_80DCA38

	thumb_func_start sub_80DCA70
sub_80DCA70: @ 80DCA70
	push {r4,lr}
	adds r4, r0, 0
	ldr r0, _080DCAA0 @ =gBattleAnimBankTarget
	ldrb r0, [r0]
	adds r2, r4, 0
	adds r2, 0x20
	adds r3, r4, 0
	adds r3, 0x22
	movs r1, 0
	bl sub_807A3FC
	ldr r0, _080DCAA4 @ =gBattleAnimBankAttacker
	ldrb r0, [r0]
	bl GetBankSide
	lsls r0, 24
	cmp r0, 0
	beq _080DCAAC
	ldr r0, _080DCAA8 @ =gBattleAnimArgs
	ldrh r1, [r4, 0x20]
	ldrh r2, [r0]
	subs r1, r2
	strh r1, [r4, 0x20]
	b _080DCAB8
	.align 2, 0
_080DCAA0: .4byte gBattleAnimBankTarget
_080DCAA4: .4byte gBattleAnimBankAttacker
_080DCAA8: .4byte gBattleAnimArgs
_080DCAAC:
	ldr r1, _080DCAE0 @ =gBattleAnimArgs
	ldrh r0, [r1]
	ldrh r2, [r4, 0x20]
	adds r0, r2
	strh r0, [r4, 0x20]
	adds r0, r1, 0
_080DCAB8:
	ldrh r0, [r0, 0x2]
	ldrh r1, [r4, 0x22]
	adds r0, r1
	strh r0, [r4, 0x22]
	ldr r0, _080DCAE4 @ =gBattleAnimBankTarget
	ldrb r0, [r0]
	bl GetBankSide
	lsls r0, 24
	cmp r0, 0
	bne _080DCAD4
	ldrh r0, [r4, 0x22]
	adds r0, 0x8
	strh r0, [r4, 0x22]
_080DCAD4:
	ldr r0, _080DCAE8 @ =sub_80DCAEC
	str r0, [r4, 0x1C]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080DCAE0: .4byte gBattleAnimArgs
_080DCAE4: .4byte gBattleAnimBankTarget
_080DCAE8: .4byte sub_80DCAEC
	thumb_func_end sub_80DCA70

	thumb_func_start sub_80DCAEC
sub_80DCAEC: @ 80DCAEC
	push {lr}
	adds r3, r0, 0
	ldrh r0, [r3, 0x2E]
	adds r0, 0x1
	strh r0, [r3, 0x2E]
	lsls r0, 16
	asrs r0, 16
	cmp r0, 0x3
	bne _080DCB20
	movs r0, 0
	strh r0, [r3, 0x2E]
	movs r0, 0x3E
	adds r0, r3
	mov r12, r0
	ldrb r2, [r0]
	lsls r0, r2, 29
	lsrs r0, 31
	movs r1, 0x1
	eors r1, r0
	lsls r1, 2
	movs r0, 0x5
	negs r0, r0
	ands r0, r2
	orrs r0, r1
	mov r1, r12
	strb r0, [r1]
_080DCB20:
	ldrh r0, [r3, 0x30]
	adds r0, 0x1
	strh r0, [r3, 0x30]
	lsls r0, 16
	asrs r0, 16
	cmp r0, 0x33
	bne _080DCB34
	adds r0, r3, 0
	bl move_anim_8072740
_080DCB34:
	pop {r0}
	bx r0
	thumb_func_end sub_80DCAEC

	thumb_func_start sub_80DCB38
sub_80DCB38: @ 80DCB38
	ldr r2, _080DCB54 @ =REG_BLDCNT
	movs r3, 0xFD
	lsls r3, 6
	adds r1, r3, 0
	strh r1, [r2]
	adds r2, 0x2
	movs r1, 0x10
	strh r1, [r2]
	movs r1, 0x10
	strh r1, [r0, 0x2E]
	ldr r1, _080DCB58 @ =sub_80DCB5C
	str r1, [r0, 0x1C]
	bx lr
	.align 2, 0
_080DCB54: .4byte REG_BLDCNT
_080DCB58: .4byte sub_80DCB5C
	thumb_func_end sub_80DCB38

	thumb_func_start sub_80DCB5C
sub_80DCB5C: @ 80DCB5C
	push {lr}
	adds r3, r0, 0
	ldrh r1, [r3, 0x32]
	movs r2, 0x32
	ldrsh r0, [r3, r2]
	cmp r0, 0x13
	bgt _080DCB70
	adds r0, r1, 0x1
	strh r0, [r3, 0x32]
	b _080DCBA8
_080DCB70:
	ldrh r1, [r3, 0x30]
	adds r0, r1, 0x1
	strh r0, [r3, 0x30]
	movs r0, 0x1
	ands r0, r1
	cmp r0, 0
	beq _080DCBA8
	ldrh r1, [r3, 0x2E]
	subs r1, 0x1
	strh r1, [r3, 0x2E]
	ldr r2, _080DCBAC @ =REG_BLDALPHA
	movs r0, 0x10
	subs r0, r1
	lsls r0, 8
	orrs r1, r0
	strh r1, [r2]
	movs r1, 0x2E
	ldrsh r0, [r3, r1]
	cmp r0, 0
	bne _080DCBA8
	adds r2, r3, 0
	adds r2, 0x3E
	ldrb r0, [r2]
	movs r1, 0x4
	orrs r0, r1
	strb r0, [r2]
	ldr r0, _080DCBB0 @ =sub_80DCBB4
	str r0, [r3, 0x1C]
_080DCBA8:
	pop {r0}
	bx r0
	.align 2, 0
_080DCBAC: .4byte REG_BLDALPHA
_080DCBB0: .4byte sub_80DCBB4
	thumb_func_end sub_80DCB5C

	thumb_func_start sub_80DCBB4
sub_80DCBB4: @ 80DCBB4
	push {lr}
	ldr r1, _080DCBC8 @ =REG_BLDCNT
	movs r2, 0
	strh r2, [r1]
	adds r1, 0x2
	strh r2, [r1]
	bl move_anim_8072740
	pop {r0}
	bx r0
	.align 2, 0
_080DCBC8: .4byte REG_BLDCNT
	thumb_func_end sub_80DCBB4

	thumb_func_start sub_80DCBCC
sub_80DCBCC: @ 80DCBCC
	push {r4-r7,lr}
	sub sp, 0x4
	adds r7, r0, 0
	bl NotInBattle
	lsls r0, 24
	cmp r0, 0
	beq _080DCBEC
	ldr r1, _080DCBE8 @ =gBattleAnimArgs
	ldrh r0, [r1, 0x4]
	negs r0, r0
	strh r0, [r1, 0x4]
	b _080DCC0E
	.align 2, 0
_080DCBE8: .4byte gBattleAnimArgs
_080DCBEC:
	ldr r0, _080DCCE8 @ =gBattleAnimBankAttacker
	ldrb r0, [r0]
	bl GetBankSide
	lsls r0, 24
	cmp r0, 0
	beq _080DCC0E
	ldr r1, _080DCCEC @ =gBattleAnimArgs
	ldrh r0, [r1, 0x4]
	negs r0, r0
	strh r0, [r1, 0x4]
	ldrh r0, [r1, 0x2]
	negs r0, r0
	strh r0, [r1, 0x2]
	ldrh r0, [r1, 0x6]
	negs r0, r0
	strh r0, [r1, 0x6]
_080DCC0E:
	bl NotInBattle
	lsls r0, 24
	cmp r0, 0
	bne _080DCC5E
	ldr r0, _080DCCE8 @ =gBattleAnimBankAttacker
	ldrb r0, [r0]
	bl GetBankSide
	adds r4, r0, 0
	ldr r5, _080DCCF0 @ =gBattleAnimBankTarget
	ldrb r0, [r5]
	bl GetBankSide
	lsls r4, 24
	lsls r0, 24
	cmp r4, r0
	bne _080DCC5E
	ldrb r0, [r5]
	bl GetBankIdentity
	lsls r0, 24
	cmp r0, 0
	beq _080DCC4C
	ldrb r0, [r5]
	bl GetBankIdentity
	lsls r0, 24
	lsrs r0, 24
	cmp r0, 0x1
	bne _080DCC5E
_080DCC4C:
	ldr r0, _080DCCEC @ =gBattleAnimArgs
	movs r2, 0x4
	ldrsh r1, [r0, r2]
	negs r1, r1
	strh r1, [r0, 0x4]
	movs r2, 0
	ldrsh r1, [r0, r2]
	negs r1, r1
	strh r1, [r0]
_080DCC5E:
	adds r0, r7, 0
	movs r1, 0x1
	bl sub_80787B0
	ldr r5, _080DCCF0 @ =gBattleAnimBankTarget
	ldrb r0, [r5]
	movs r1, 0x2
	bl sub_8077ABC
	adds r4, r0, 0
	lsls r4, 24
	ldr r6, _080DCCEC @ =gBattleAnimArgs
	lsrs r4, 24
	ldrh r0, [r6, 0x4]
	adds r4, r0
	lsls r4, 16
	lsrs r4, 16
	ldrb r0, [r5]
	movs r1, 0x3
	bl sub_8077ABC
	adds r1, r0, 0
	lsls r1, 24
	lsrs r1, 24
	ldrh r2, [r6, 0x6]
	adds r1, r2
	lsls r1, 16
	ldrh r2, [r7, 0x20]
	lsls r0, r4, 16
	asrs r0, 16
	subs r0, r2
	lsls r0, 16
	asrs r0, 16
	ldrh r2, [r7, 0x22]
	lsrs r5, r1, 16
	asrs r1, 16
	subs r1, r2
	lsls r1, 16
	asrs r1, 16
	bl sub_80790F0
	lsls r0, 16
	movs r1, 0xC0
	lsls r1, 24
	adds r0, r1
	lsrs r0, 16
	movs r3, 0x80
	lsls r3, 1
	str r0, [sp]
	adds r0, r7, 0
	movs r1, 0
	adds r2, r3, 0
	bl sub_8078FDC
	ldrh r0, [r6, 0x8]
	strh r0, [r7, 0x2E]
	strh r4, [r7, 0x32]
	strh r5, [r7, 0x36]
	ldr r0, _080DCCF4 @ =sub_8078B34
	str r0, [r7, 0x1C]
	ldr r1, _080DCCF8 @ =move_anim_8072740
	adds r0, r7, 0
	bl StoreSpriteCallbackInData
	add sp, 0x4
	pop {r4-r7}
	pop {r0}
	bx r0
	.align 2, 0
_080DCCE8: .4byte gBattleAnimBankAttacker
_080DCCEC: .4byte gBattleAnimArgs
_080DCCF0: .4byte gBattleAnimBankTarget
_080DCCF4: .4byte sub_8078B34
_080DCCF8: .4byte move_anim_8072740
	thumb_func_end sub_80DCBCC

	thumb_func_start sub_80DCCFC
sub_80DCCFC: @ 80DCCFC
	push {r4-r6,lr}
	adds r6, r0, 0
	movs r1, 0x1
	bl sub_80787B0
	ldr r0, _080DCD68 @ =gBattleAnimBankAttacker
	ldrb r0, [r0]
	bl GetBankSide
	lsls r0, 24
	cmp r0, 0
	beq _080DCD1C
	ldr r1, _080DCD6C @ =gBattleAnimArgs
	ldrh r0, [r1, 0x4]
	negs r0, r0
	strh r0, [r1, 0x4]
_080DCD1C:
	ldr r4, _080DCD6C @ =gBattleAnimArgs
	ldrh r0, [r4, 0x8]
	strh r0, [r6, 0x2E]
	ldr r5, _080DCD70 @ =gBattleAnimBankTarget
	ldrb r0, [r5]
	movs r1, 0x2
	bl sub_8077ABC
	lsls r0, 24
	lsrs r0, 24
	ldrh r1, [r4, 0x4]
	adds r0, r1
	strh r0, [r6, 0x32]
	ldrb r0, [r5]
	movs r1, 0x3
	bl sub_8077ABC
	lsls r0, 24
	lsrs r0, 24
	ldrh r1, [r4, 0x6]
	adds r0, r1
	strh r0, [r6, 0x36]
	ldrh r0, [r4, 0xA]
	strh r0, [r6, 0x38]
	adds r0, r6, 0
	bl sub_80786EC
	ldr r0, _080DCD74 @ =sub_80DCD78
	str r0, [r6, 0x1C]
	adds r2, r6, 0
	adds r2, 0x3E
	ldrb r0, [r2]
	movs r1, 0x4
	orrs r0, r1
	strb r0, [r2]
	pop {r4-r6}
	pop {r0}
	bx r0
	.align 2, 0
_080DCD68: .4byte gBattleAnimBankAttacker
_080DCD6C: .4byte gBattleAnimArgs
_080DCD70: .4byte gBattleAnimBankTarget
_080DCD74: .4byte sub_80DCD78
	thumb_func_end sub_80DCCFC

	thumb_func_start sub_80DCD78
sub_80DCD78: @ 80DCD78
	push {r4-r7,lr}
	mov r7, r8
	push {r7}
	sub sp, 0x14
	adds r4, r0, 0
	adds r2, r4, 0
	adds r2, 0x3E
	ldrb r0, [r2]
	movs r1, 0x5
	negs r1, r1
	ands r1, r0
	strb r1, [r2]
	adds r0, r4, 0
	bl sub_8078718
	lsls r0, 24
	cmp r0, 0
	beq _080DCDA4
	adds r0, r4, 0
	bl move_anim_8072740
	b _080DCE34
_080DCDA4:
	movs r0, 0x2E
	adds r0, r4
	mov r8, r0
	ldrh r7, [r4, 0x20]
	ldrh r5, [r4, 0x24]
	ldrh r1, [r4, 0x22]
	mov r12, r1
	ldrh r6, [r4, 0x26]
	mov r2, r8
	add r1, sp, 0x4
	movs r3, 0x7
_080DCDBA:
	ldrh r0, [r2]
	strh r0, [r1]
	adds r2, 0x2
	adds r1, 0x2
	subs r3, 0x1
	cmp r3, 0
	bge _080DCDBA
	adds r0, r7, r5
	lsls r0, 16
	lsrs r5, r0, 16
	mov r2, r12
	adds r0, r2, r6
	lsls r0, 16
	lsrs r6, r0, 16
	adds r0, r4, 0
	bl sub_8078718
	lsls r0, 24
	cmp r0, 0
	bne _080DCE34
	ldrh r0, [r4, 0x24]
	ldrh r1, [r4, 0x20]
	adds r0, r1
	lsls r1, r5, 16
	asrs r1, 16
	subs r0, r1
	lsls r0, 16
	asrs r0, 16
	ldrh r1, [r4, 0x26]
	ldrh r2, [r4, 0x22]
	adds r1, r2
	lsls r2, r6, 16
	asrs r2, 16
	subs r1, r2
	lsls r1, 16
	asrs r1, 16
	bl sub_80790F0
	lsls r0, 16
	movs r1, 0xC0
	lsls r1, 24
	adds r0, r1
	lsrs r0, 16
	movs r3, 0x80
	lsls r3, 1
	str r0, [sp]
	adds r0, r4, 0
	movs r1, 0
	adds r2, r3, 0
	bl sub_8078FDC
	add r2, sp, 0x4
	mov r1, r8
	movs r3, 0x7
_080DCE26:
	ldrh r0, [r2]
	strh r0, [r1]
	adds r2, 0x2
	adds r1, 0x2
	subs r3, 0x1
	cmp r3, 0
	bge _080DCE26
_080DCE34:
	add sp, 0x14
	pop {r3}
	mov r8, r3
	pop {r4-r7}
	pop {r0}
	bx r0
	thumb_func_end sub_80DCD78

	thumb_func_start sub_80DCE40
sub_80DCE40: @ 80DCE40
	push {r4,r5,lr}
	adds r5, r0, 0
	ldr r0, _080DCE54 @ =gBattleAnimArgs
	movs r1, 0
	ldrsh r0, [r0, r1]
	cmp r0, 0
	bne _080DCE5C
	ldr r4, _080DCE58 @ =gBattleAnimBankAttacker
	b _080DCE5E
	.align 2, 0
_080DCE54: .4byte gBattleAnimArgs
_080DCE58: .4byte gBattleAnimBankAttacker
_080DCE5C:
	ldr r4, _080DCE90 @ =gBattleAnimBankTarget
_080DCE5E:
	ldrb r0, [r4]
	movs r1, 0x2
	bl sub_8077ABC
	lsls r0, 24
	lsrs r0, 24
	strh r0, [r5, 0x20]
	ldrb r0, [r4]
	movs r1, 0x3
	bl sub_8077ABC
	lsls r0, 24
	lsrs r0, 24
	adds r0, 0x12
	strh r0, [r5, 0x22]
	ldr r1, _080DCE94 @ =move_anim_8074EE0
	adds r0, r5, 0
	bl StoreSpriteCallbackInData
	ldr r0, _080DCE98 @ =sub_80785E4
	str r0, [r5, 0x1C]
	pop {r4,r5}
	pop {r0}
	bx r0
	.align 2, 0
_080DCE90: .4byte gBattleAnimBankTarget
_080DCE94: .4byte move_anim_8074EE0
_080DCE98: .4byte sub_80785E4
	thumb_func_end sub_80DCE40
	
	.align 2, 0 @ Don't pad with nop.
