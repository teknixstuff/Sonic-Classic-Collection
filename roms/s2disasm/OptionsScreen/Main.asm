    include "OptionsScreen/Data.asm"


; ||||||||||||||| S U B R O U T I N E |||||||||||||||||||||||||||||||||||||||

; a1 = Pointer to text
OptionsScreen_DrawLabelDeselected:
	move.w	#palette_line_1,d0
	lea	(Chunk_Table+$160+(39*1*2)+(1*2)).l,a2 ; Label location
	bra.w	MenuScreenTextToRAM

; a1 = Pointer to text
OptionsScreen_DrawLabelSelected:
	move.w	#palette_line_3,d0
	lea	(Chunk_Table+(39*1*2)+(1*2)).l,a2 ; Label location
	bra.w	MenuScreenTextToRAM


; a1 = Pointer to text
OptionsScreen_DrawValueDeselected:
	move.w	#palette_line_1,d0
	lea	(Chunk_Table+$160+(39*1*2)+(18*2)).l,a2 ; Value location
	bra.w	MenuScreenTextToRAM

; a1 = Pointer to text
OptionsScreen_DrawValueSelected:
	move.w	#palette_line_3,d0
	lea	(Chunk_Table+(39*1*2)+(18*2)).l,a2 ; Value location
	bra.w	MenuScreenTextToRAM


; d0 = #vdpComm(VRAM_Plane_A_Name_Table+planeLocH40(x,y),VRAM,WRITE) [long]
OptionsScreen_DrawBoxDeselected:
	lea		(Chunk_Table+$160).l,a1
	bra.s	OptionsScreen_DrawBox

; d0 = #vdpComm(VRAM_Plane_A_Name_Table+planeLocH40(x,y),VRAM,WRITE) [long]
OptionsScreen_DrawBoxSelected:
	lea		(Chunk_Table).l,a1

; [internal]
OptionsScreen_DrawBox:
	moveq	#38,d1 ; Box width - 1
	moveq	#3,d2 ; Box height - 1
	jmpto	(PlaneMapToVRAM_H40).l, JmpTo_PlaneMapToVRAM_H40

; ===========================================================================

OptionsScreen_DrawMenu:
	move.l	(Options_menu_pointer).l,a0
	move.w	(a0)+,d5	; d5 = max list index
	moveq	#0,d6	; d6 = current item to draw
-
	bsr.s	OptionsScreen_DrawMenuItem

	addi.w	#1,d6 ; increment current item

	cmpi.w	#7,d6 ; limit number of items drawn
	bge.s	+
	cmp.b	d5,d6 ; make sure we don't overflow (TODO: scroll)
	bhi.s	+
	bra.s	-
+
	rts

; ===========================================================================

OptionsScreen_BoxLocations:
	dc.l vdpComm(VRAM_Plane_A_Name_Table+planeLocH40(1,1),VRAM,WRITE)
	dc.l vdpComm(VRAM_Plane_A_Name_Table+planeLocH40(1,5),VRAM,WRITE)
	dc.l vdpComm(VRAM_Plane_A_Name_Table+planeLocH40(1,9),VRAM,WRITE)
	dc.l vdpComm(VRAM_Plane_A_Name_Table+planeLocH40(1,13),VRAM,WRITE)
	dc.l vdpComm(VRAM_Plane_A_Name_Table+planeLocH40(1,17),VRAM,WRITE)
	dc.l vdpComm(VRAM_Plane_A_Name_Table+planeLocH40(1,21),VRAM,WRITE)
	dc.l vdpComm(VRAM_Plane_A_Name_Table+planeLocH40(1,25),VRAM,WRITE)

OptionsScreen_DrawMenuItem_GetLoc:
	lea		(OptionsScreen_BoxLocations).l,a1
	moveq	#0,d0
	move.w	d6,d0
	lsl.l	#2,d0
	add.l	d0,a1
	move.l	(a1),d0
	rts

OptionsScreen_DrawMenuItem:
	move.w	(a0)+,d4	; d4 = item type
	cmp.w	#18,d4
	beq.s OptionsScreen_DrawMenuItem_Flip
	; Draw Label Text
	move.l	(a0)+,a1 ; a1 = item label text
	cmp.w	(Options_menu_selection).l,d6
	bne.s	OptionsScreen_DrawMenuItemDeselected

OptionsScreen_DrawMenuItemSelected:
	bsr.w	OptionsScreen_DrawLabelSelected
	bsr.w	OptionsScreen_GetValTextPtr
	bsr.w	OptionsScreen_DrawValueSelected
	bsr.s	OptionsScreen_DrawMenuItem_GetLoc
	bra.w	OptionsScreen_DrawBoxSelected

OptionsScreen_DrawMenuItemDeselected:
	bsr.w	OptionsScreen_DrawLabelDeselected
	bsr.w	OptionsScreen_GetValTextPtr
	bsr.w	OptionsScreen_DrawValueDeselected
	bsr.s	OptionsScreen_DrawMenuItem_GetLoc
	bra.w	OptionsScreen_DrawBoxDeselected
	
OptionsScreen_DrawMenuItem_Flip:
	; Draw Label Text
	move.l	(a0)+,a1 ; a1 = item label text
	cmp.w	(Options_menu_selection).l,d6
	bne.s	OptionsScreen_DrawMenuItemDeselected_Flip
	
OptionsScreen_DrawMenuItemSelected_Flip:
	bsr.w	OptionsScreen_DrawValueSelected
	bsr.w	OptionsScreen_GetValTextPtr
	bsr.w	OptionsScreen_DrawLabelSelected
	bsr.s	OptionsScreen_DrawMenuItem_GetLoc
	bra.w	OptionsScreen_DrawBoxSelected

OptionsScreen_DrawMenuItemDeselected_Flip:
	bsr.w	OptionsScreen_DrawValueDeselected
	bsr.w	OptionsScreen_GetValTextPtr
	bsr.w	OptionsScreen_DrawLabelDeselected
	bsr.w	OptionsScreen_DrawMenuItem_GetLoc
	bra.w	OptionsScreen_DrawBoxDeselected

; ===========================================================================

OptionsScreen_GetValTextPtr:
	moveq	#0,d0
	move.w	d4,d0
	move.w	OptionsScreen_GetValTextPtr_Index(pc,d0.w),d1
	jsr	OptionsScreen_GetValTextPtr_Index(pc,d1.w)
	addi.l	#4,a0	; increment to next menu item pointer
	rts

OptionsScreen_GetValTextPtr_Index:	offsetTable
	offsetTableEntry.w	OptionsScreen_GetValTextPtr_Null ; 0
	offsetTableEntry.w	OptionsScreen_GetValTextPtr_Null ; 2 (MenuItemLabel)
	offsetTableEntry.w	OptionsScreen_GetValTextPtr_MenuItemValue ; 4 (MenuItemValue)
	offsetTableEntry.w	OptionsScreen_GetValTextPtr_Null ; 6 (MenuItemSub)
	offsetTableEntry.w	OptionsScreen_GetValTextPtr_MenuItemSound ; 8 (MenuItemSound)
	offsetTableEntry.w	OptionsScreen_GetValTextPtr_MenuItemValue ; 10 (MenuItemValuePlayer)
	offsetTableEntry.w	OptionsScreen_GetValTextPtr_MenuItemValue ; 12 (MenuItemValue2P)
	offsetTableEntry.w	OptionsScreen_GetValTextPtr_Null ; 14 (MenuItemBack)
	offsetTableEntry.w	OptionsScreen_GetValTextPtr_Null ; 16 (MenuItemCredits)
	offsetTableEntry.w	OptionsScreen_GetValTextPtr_MenuItemValue ; 18 (MenuItemSave)
	offsetTableEntry.w	OptionsScreen_GetValTextPtr_MenuItemValue ; 20 (MenuItemNewSave)
	offsetTableEntry.w	OptionsScreen_GetValTextPtr_MenuItemValue ; 22 (MenuItemDeleteSave)

OptionsScreen_GetValTextPtr_Null:
	move.l	#Txt_Empty,a1
	rts

OptionsScreen_GetValTextPtr_MenuItemSound:
	lea	(Chunk_Table+$160+(39*1*2)+(35*2)).l,a2
	bsr.w	OptionScreen_HexDumpSoundTest
	lea	(Chunk_Table+(39*1*2)+(35*2)).l,a2
	move.w	#palette_line_3,d0
	bsr.w	OptionScreen_HexDumpSoundTest
	move.l	#Txt_NoDraw,a1
	rts

OptionsScreen_GetValTextPtr_MenuItemValue:
	move.l	(a0),a1	 ; (a0)/a1 = otherdataptr
	moveq	#0,d0
	move.w 	(a1)+,d0 ; d0 = max val
	move.l	(a1)+,a2 ; a2 = value address
	move.b	(a2),d1 ; d1 = current value

	cmp.b	d0,d1
	bhi.s	OptionsScreen_GetValTextPtr_MenuItemValue_UnkVal

	lsl.l	#2,d1	; get relative address in text list
	move.l	(a1),a1	; a1 = text list
	add.l	d1,a1
	move.l	(a1),a1	; a1 = text ptr
	rts

OptionsScreen_GetValTextPtr_MenuItemValue_UnkVal:
	move.l	#Txt_Unknown,a1
	rts

; ===========================================================================

OptionsScreen_Input:
	move.l	(Options_menu_pointer).l,a0
	move.w	(a0)+,d1

	move.b	(Ctrl_1_Press).w,d0
	or.b	(Ctrl_2_Press).w,d0
	btst	#button_up,d0
	beq.s	+
	subq.w	#1,(Options_menu_selection).l
	bcc.s	++
	move.w	d1,(Options_menu_selection).l
+
	btst	#button_down,d0
	beq.s	+
	addq.w	#1,(Options_menu_selection).l
	move.w	(Options_menu_selection).l,d2
	subi.w	#1,d2
	cmp.w	d1,d2 ; Number of options
	blo.s	+
	move.w	#0,(Options_menu_selection).l
+
	moveq	#0,d0
	move.w	(Options_menu_selection).l,d0
	mulu.w	#menuitemdata_len,d0
	add.l	d0,a0
	moveq	#0,d0
	move.w	(a0)+,d0 ; d0 = type
	addi.l	#4,a0 ; increment past text label and padding
	move.l	(a0),a0 ; a0 = other data pointer

	move.w	OptionsScreen_Input_Index(pc,d0.w),d1
	jmp	OptionsScreen_Input_Index(pc,d1.w)

OptionsScreen_Input_Index:	offsetTable
	offsetTableEntry.w	OptionsScreen_Input_Null ; 0
	offsetTableEntry.w	OptionsScreen_Input_Null ; 2 (MenuItemLabel)
	offsetTableEntry.w	OptionsScreen_Input_MenuItemValue ; 4 (MenuItemValue)
	offsetTableEntry.w	OptionsScreen_Input_MenuItemSub ; 6 (MenuItemSub)
	offsetTableEntry.w	OptionsScreen_Input_MenuItemSound ; 8 (MenuItemSound)
	offsetTableEntry.w	OptionsScreen_Input_MenuItemValuePlayer ; 10 (MenuItemValuePlayer)
	offsetTableEntry.w	OptionsScreen_Input_MenuItemValue2P ; 12 (MenuItemValue2P)
	offsetTableEntry.w	OptionsScreen_Input_MenuItemBack ; 14 (MenuItemBack)
	offsetTableEntry.w	OptionsScreen_Input_MenuItemCredits ; 16 (MenuItemCredits)
	offsetTableEntry.w	OptionsScreen_Input_MenuItemSave ; 18 (MenuItemSave)
	offsetTableEntry.w	OptionsScreen_Input_MenuItemNewSave ; 20 (MenuItemNewSave)
	offsetTableEntry.w	OptionsScreen_Input_MenuItemDeleteSave ; 22 (MenuItemDeleteSave)

OptionsScreen_Input_Null:
	rts
	
OptionsScreen_Input_MenuItemDeleteSave:
	move.b	(Ctrl_1_Press).w,d0
	or.b	(Ctrl_2_Press).w,d0
	btst	#button_start,d0
	beq.l	OptionsScreen_Input_MenuItemValue
	cmpa.l	#OptionsMenu_DeleteFile,a0
	bne.s	OptionsScreen_Input_MenuItemDeleteSave_Confirm
	cmp.b	#0,(Option_Save_DeleteSelect).l
	beq.s	OptionsScreen_Input_MenuItemDeleteSave_Skip
	move.b	(Option_Save_DeleteSelect).l,(Current_save_file).l
	move.l	#OptionsMenu_DeleteFileConf,(OptionsMenu_DeleteFile_MenuOption).l
	move.b	#0,(Option_Save_DeleteSelect).l
	
OptionsScreen_Input_MenuItemDeleteSave_Skip:
	rts
	
OptionsScreen_Input_MenuItemDeleteSave_Confirm:
	clr.l	d0
	cmp.b	#0, (Option_Save_DeleteSelect).l
	beq.s	OptionsScreen_Input_MenuItemDeleteSave_Cancel
	clr.w	d0
	move.b	(Current_save_file).l,d0
	subi.w	#1,d0
	lsl.w	#2,d0
	move.l	#DataFile_Headers,a0
	move.l	(a0,d0.w),a0
	move.b	#0,(a0)
	
OptionsScreen_Input_MenuItemDeleteSave_Cancel:
	move.l	#OptionsMenu_DeleteFile,(OptionsMenu_DeleteFile_MenuOption).l
	move.b	#0,(Option_Save_DeleteSelect).l
	bsr.w	MenuScreen_DataSelect_LoadItems
	rts

OptionsScreen_Input_MenuItemSave:
	move.b	(Ctrl_1_Press).w,d0
	or.b	(Ctrl_2_Press).w,d0
	btst	#button_start,d0
	beq.l	OptionsScreen_Input_MenuItemValue
	; Set save index
	clr.l	d0
	move.b	$A(a0),d0
	move.b	d0,(Current_save_file).l
	; Set player
	move.l	#DataFile_Headers, a0
	move.l	(a0, d0.w),a0
	adda.l	#1,a0
	move.b	(a0),(Player_option).l
	; Start a single player game
	move.w	#0,(Two_player_mode).w
	move.w	#0,(Two_player_mode_copy).w
	
	move.l	#DataFile_Headers, a0
	move.l	(a0, d0.w),a0
	clr.w	d1
	move.b	(a0),d1
	subi.b	#1,d1
	lsl.b	#1,d1
	move.l	#DataFile_Zones,a0
	move.w	(a0, d1.w),d1
	move.w	d1,(Current_ZoneAndAct).w
	move.w	d1,(Apparent_ZoneAndAct).w
	move.b	#GameModeID_Level,(Game_Mode).w ; => Level (Zone play mode)
	rts
	
OptionsScreen_Input_MenuItemNewSave:
	move.b	(Ctrl_1_Press).w,d0
	or.b	(Ctrl_2_Press).w,d0
	btst	#button_start,d0
	beq.l	OptionsScreen_Input_MenuItemValue
	; Set save index
	clr.w	d0
	move.b	$A(a0),d0
	move.b	d0,(Current_save_file).l
	; Set player
	move.l	$2(a0),a1
	move.b	(a1),(Player_option).l
	; Start a single player game
	move.w	#0,(Two_player_mode).w
	move.w	#0,(Two_player_mode_copy).w
	
	cmp.b	#0,(Current_save_file).l	; is saving disabled?
	bne.s	+			; if not, branch
	btst	#button_A,(Ctrl_1_Held).w ; is A held down?
	beq.s	+	 		; if not, branch
	move.b	#GameModeID_LevelSelect,(Game_Mode).w ; => LevelSelectMen
	rts
+
	move.w	#0,(Current_ZoneAndAct).w	; emerald_hill_zone_act_1
	move.w	#0,(Apparent_ZoneAndAct).w
	move.b	#GameModeID_Level,(Game_Mode).w ; => Level (Zone play mode)
	rts

OptionsScreen_Input_MenuItemValuePlayer:
	move.b	(Ctrl_1_Press).w,d0
	or.b	(Ctrl_2_Press).w,d0
	btst	#button_start,d0
	beq.s	OptionsScreen_Input_MenuItemValue
	; No save file
	move.b	#0,(Current_save_file).l
	; Start a single player game
	move.w	#0,(Two_player_mode).w
	move.w	#0,(Two_player_mode_copy).w

	move.b	#1,(Level_select_flag).w	; REMOVE THIS
	tst.b	(Level_select_flag).w	; has level select cheat been entered?
	beq.s	+			; if not, branch
	btst	#button_A,(Ctrl_1_Held).w ; is A held down?
	beq.s	+	 		; if not, branch
	move.b	#GameModeID_LevelSelect,(Game_Mode).w ; => LevelSelectMen
	rts
+
	move.w	#0,(Current_ZoneAndAct).w	; emerald_hill_zone_act_1
	move.w	#0,(Apparent_ZoneAndAct).w
	move.b	#GameModeID_Level,(Game_Mode).w ; => Level (Zone play mode)
	rts

OptionsScreen_Input_MenuItemValue2P:
	move.b	(Ctrl_1_Press).w,d0
	or.b	(Ctrl_2_Press).w,d0
	btst	#button_start,d0
	beq.s	OptionsScreen_Input_MenuItemValue
	; REMOVE THIS ONCE 2P IS READY
	;sfx		sfx_Error
	;rts
	
	; Start a 2P VS game
	move.w	#1,(Two_player_mode).w
	move.w	#1,(Two_player_mode_copy).w
	move.b	#GameModeID_2PLevelSelect,(Game_Mode).w ; => LevelSelectMenu2P
	move.b	#0,(Current_Zone_2P).w
	move.b	#0,(Player_mode).w
	rts

OptionsScreen_Input_MenuItemValue:
	moveq	#0,d1
	move.w	(a0)+,d1 ; d1 = max val
	move.l	(a0),a0

	move.b	(Ctrl_1_Press).w,d0
	or.b	(Ctrl_2_Press).w,d0
	btst	#button_left,d0
	beq.s	+
	sfx		sfx_Beep
	subq.b	#1,(a0)
	bcc.s	++
	move.b	d1,(a0)
+
	btst	#button_right,d0
	beq.s	+
	sfx		sfx_Beep
	addq.b	#1,(a0)
	move.b	(a0),d2
	subi.b	#1,d2
	cmp.b	d1,d2 ; Number of options
	blo.s	+
	move.b	#0,(a0)
+
	jsr		SaveSRAM
	rts

OptionsScreen_Input_MenuItemBack:
	move.b	(Ctrl_1_Press).w,d0
	or.b	(Ctrl_2_Press).w,d0
	btst	#button_start,d0
	beq.s	+
	bsr.w	OptionsScreen_Input_MenuItemSubEnter
	sfx		sfx_InstaAttack
+
	rts

OptionsScreen_Input_MenuItemSub:
	move.b	(Ctrl_1_Press).w,d0
	or.b	(Ctrl_2_Press).w,d0
	btst	#button_start,d0
	beq.s	+
	bsr.w	OptionsScreen_Input_MenuItemSubEnter
	sfx		sfx_Starpost
+
	rts

OptionsScreen_Input_MenuItemSubEnter:
	move.w	#0,(Options_menu_selection).l
	move.l	a0,(Options_menu_pointer).l
	dmaFillVRAM 0,VRAM_Plane_A_Name_Table,VRAM_Plane_Table_Size	; Clear Plane A pattern name table
	bsr.w	OptionsScreen_DrawMenu
+
	rts

OptionsScreen_Input_MenuItemSound:
	move.b	(Ctrl_1_Press).w,d0
	or.b	(Ctrl_2_Press).w,d0
	btst	#button_start,d0
	beq.s	+
	move.b	#GameModeID_SegaScreen,(Game_Mode).w ; => SegaScreen
+
	bsr.w	OptionsScreen_Input_MenuItemValue

	btst	#button_A,d0
	beq.s	+
	addi.b	#$10,(a0)
	move.b	(a0),d2
	subi.b	#1,d2
	cmp.b	d1,d2 ; Number of options
	blo.s	+
	move.b	#0,(a0)
+
	andi.w	#button_B_mask|button_C_mask,d0
	beq.s	+	; rts
	move.w	(Sound_test_sound).w,d0
	musicreg	d0
	lea	(level_select_cheat).l,a0
	lea	(continues_cheat).l,a2
	lea	(Level_select_flag).w,a1	; Also Slow_motion_flag
	moveq	#0,d2	; flag to tell the routine to enable the continues cheat
	bsr.w	CheckCheats
+
	rts

OptionsScreen_Input_MenuItemCredits:
	move.b	(Ctrl_1_Press).w,d0
	or.b	(Ctrl_2_Press).w,d0
	btst	#button_start,d0
	beq.s	+
	move.b	#GameModeID_EndingSequence,(Game_Mode).w
	clr.b	(Ending_PalCycle_flag).w
	move.b	#1,(Credits_Trigger).w
	jmp		EndgameCredits_Loop
+
	rts

; ===========================================================================

MenuScreen_DataSelect_LoadItems:
	move.w	#6, (OptionsMenu_Saves_Mem).l
	
	move.w	#MenuItemNewSave, (OptionsMenu_Save0_MenuType).l
	move.l	#Txt_NoSave, (OptionsMenu_Save0_MenuLabel).l
	move.l	#OptionsMenu_Save_0, (OptionsMenu_Save0_MenuOption).l
	
MenuScreen_DataSelect_Save1Init:
	move.l	#OptionsMenu_Save1_ItemCount, (OptionsMenu_Save1_MenuOption).l
	cmpi.b	#0, (DataFile_Save1_Zone).l
	bne.s	MenuScreen_DataSelect_Save1Valid
	move.w	#MenuItemNewSave, (OptionsMenu_Save1_MenuType).l
	move.l	#Txt_NewFile, (OptionsMenu_Save1_MenuLabel).l
	move.w	#4, (OptionsMenu_Save1_ItemCount).l
	move.l	#TxtList_CharacterUE, (OptionsMenu_Save1_ItemList).l
	bra.s	MenuScreen_DataSelect_Save2Init
	
MenuScreen_DataSelect_Save1Valid:
	move.w	#MenuItemSave, (OptionsMenu_Save1_MenuType).l
	move.l	#TxtList_CharacterUE, a0
	clr.l	d0
	move.b	(DataFile_Save1_Player).l, d0
	lsl.l	#2, d0
	move.l	(a0, d0), (OptionsMenu_Save1_MenuLabel).l
	move.l	#TxtList_SaveZones, a0
	move.b	(DataFile_Save1_Zone).l, d0
	subi.b	#1, d0
	lsl.l	#2, d0
	cmp.l	#Txt_Clear,(a0, d0)
	beq.s	MenuScreen_DataSelect_Save1Clear
	adda.l	d0, a0
	move.l	a0, (OptionsMenu_Save1_ItemList).l
	move.w	#0, (OptionsMenu_Save1_ItemCount).l
	bra.s	MenuScreen_DataSelect_Save2Init
	
MenuScreen_DataSelect_Save1Clear:
	move.l	#TxtList_SaveZones, (OptionsMenu_Save1_ItemList).l
	move.w	#11, (OptionsMenu_Save1_ItemCount).l
	
MenuScreen_DataSelect_Save2Init:
	move.l	#OptionsMenu_Save2_ItemCount, (OptionsMenu_Save2_MenuOption).l
	cmpi.b	#0, (DataFile_Save2_Zone).l
	bne.s	MenuScreen_DataSelect_Save2Valid
	move.w	#MenuItemNewSave, (OptionsMenu_Save2_MenuType).l
	move.l	#Txt_NewFile, (OptionsMenu_Save2_MenuLabel).l
	move.w	#4, (OptionsMenu_Save2_ItemCount).l
	move.l	#TxtList_CharacterUE, (OptionsMenu_Save2_ItemList).l
	bra.s	MenuScreen_DataSelect_Save3Init
	
MenuScreen_DataSelect_Save2Valid:
	move.w	#MenuItemSave, (OptionsMenu_Save2_MenuType).l
	move.l	#TxtList_CharacterUE, a0
	clr.l	d0
	move.b	(DataFile_Save2_Player).l, d0
	lsl.l	#2, d0
	move.l	(a0, d0), (OptionsMenu_Save2_MenuLabel).l
	move.l	#TxtList_SaveZones, a0
	move.b	(DataFile_Save2_Zone).l, d0
	subi.b	#1, d0
	lsl.l	#2, d0
	cmp.l	#Txt_Clear,(a0, d0)
	beq.s	MenuScreen_DataSelect_Save2Clear
	adda.l	d0, a0
	move.l	a0, (OptionsMenu_Save2_ItemList).l
	move.w	#0, (OptionsMenu_Save2_ItemCount).l
	bra.s	MenuScreen_DataSelect_Save3Init
	
MenuScreen_DataSelect_Save2Clear:
	move.l	#TxtList_SaveZones, (OptionsMenu_Save2_ItemList).l
	move.w	#11, (OptionsMenu_Save2_ItemCount).l

MenuScreen_DataSelect_Save3Init:	
	move.l	#OptionsMenu_Save3_ItemCount, (OptionsMenu_Save3_MenuOption).l
	cmpi.b	#0, (DataFile_Save3_Zone).l
	bne.s	MenuScreen_DataSelect_Save3Valid
	move.w	#MenuItemNewSave, (OptionsMenu_Save3_MenuType).l
	move.l	#Txt_NewFile, (OptionsMenu_Save3_MenuLabel).l
	move.w	#4, (OptionsMenu_Save3_ItemCount).l
	move.l	#TxtList_CharacterUE, (OptionsMenu_Save3_ItemList).l
	bra.s	MenuScreen_DataSelect_Save4Init
	
MenuScreen_DataSelect_Save3Valid:
	move.w	#MenuItemSave, (OptionsMenu_Save3_MenuType).l
	move.l	#TxtList_CharacterUE, a0
	clr.l	d0
	move.b	(DataFile_Save3_Player).l, d0
	lsl.l	#2, d0
	move.l	(a0, d0), (OptionsMenu_Save3_MenuLabel).l
	move.l	#TxtList_SaveZones, a0
	move.b	(DataFile_Save3_Zone).l, d0
	subi.b	#1, d0
	lsl.l	#2, d0
	cmp.l	#Txt_Clear,(a0, d0)
	beq.s	MenuScreen_DataSelect_Save3Clear
	adda.l	d0, a0
	move.l	a0, (OptionsMenu_Save3_ItemList).l
	move.w	#0, (OptionsMenu_Save3_ItemCount).l
	bra.s	MenuScreen_DataSelect_Save4Init
	
MenuScreen_DataSelect_Save3Clear:
	move.l	#TxtList_SaveZones, (OptionsMenu_Save3_ItemList).l
	move.w	#11, (OptionsMenu_Save3_ItemCount).l

MenuScreen_DataSelect_Save4Init:
	move.l	#OptionsMenu_Save4_ItemCount, (OptionsMenu_Save4_MenuOption).l
	cmpi.b	#0, (DataFile_Save4_Zone).l
	bne.s	MenuScreen_DataSelect_Save4Valid
	move.w	#MenuItemNewSave, (OptionsMenu_Save4_MenuType).l
	move.l	#Txt_NewFile, (OptionsMenu_Save4_MenuLabel).l
	move.w	#4, (OptionsMenu_Save4_ItemCount).l
	move.l	#TxtList_CharacterUE, (OptionsMenu_Save4_ItemList).l
	bra.s	MenuScreen_DataSelect_Save5Init
	
MenuScreen_DataSelect_Save4Valid:
	move.w	#MenuItemSave, (OptionsMenu_Save4_MenuType).l
	move.l	#TxtList_CharacterUE, a0
	clr.l	d0
	move.b	(DataFile_Save4_Player).l, d0
	lsl.l	#2, d0
	move.l	(a0, d0), (OptionsMenu_Save4_MenuLabel).l
	move.l	#TxtList_SaveZones, a0
	move.b	(DataFile_Save4_Zone).l, d0
	subi.b	#1, d0
	lsl.l	#2, d0
	cmp.l	#Txt_Clear,(a0, d0)
	beq.s	MenuScreen_DataSelect_Save4Clear
	adda.l	d0, a0
	move.l	a0, (OptionsMenu_Save4_ItemList).l
	move.w	#0, (OptionsMenu_Save4_ItemCount).l
	bra.s	MenuScreen_DataSelect_Save5Init
	
MenuScreen_DataSelect_Save4Clear:
	move.l	#TxtList_SaveZones, (OptionsMenu_Save4_ItemList).l
	move.w	#11, (OptionsMenu_Save4_ItemCount).l

MenuScreen_DataSelect_Save5Init:
	move.l	#OptionsMenu_Save5_ItemCount, (OptionsMenu_Save5_MenuOption).l
	cmpi.b	#0, (DataFile_Save5_Zone).l
	bne.s	MenuScreen_DataSelect_Save5Valid
	move.w	#MenuItemNewSave, (OptionsMenu_Save5_MenuType).l
	move.l	#Txt_NewFile, (OptionsMenu_Save5_MenuLabel).l
	move.w	#4, (OptionsMenu_Save5_ItemCount).l
	move.l	#TxtList_CharacterUE, (OptionsMenu_Save5_ItemList).l
	bra.s	MenuScreen_DataSelect_SaveInitEnd
	
MenuScreen_DataSelect_Save5Valid:
	move.w	#MenuItemSave, (OptionsMenu_Save5_MenuType).l
	move.l	#TxtList_CharacterUE, a0
	clr.l	d0
	move.b	(DataFile_Save5_Player).l, d0
	lsl.l	#2, d0
	move.l	(a0, d0), (OptionsMenu_Save5_MenuLabel).l
	move.l	#TxtList_SaveZones, a0
	move.b	(DataFile_Save5_Zone).l, d0
	subi.b	#1, d0
	lsl.l	#2, d0
	cmp.l	#Txt_Clear,(a0, d0)
	beq.s	MenuScreen_DataSelect_Save5Clear
	adda.l	d0, a0
	move.l	a0, (OptionsMenu_Save5_ItemList).l
	move.w	#0, (OptionsMenu_Save5_ItemCount).l
	bra.s	MenuScreen_DataSelect_SaveInitEnd
	
MenuScreen_DataSelect_Save5Clear:
	move.l	#TxtList_SaveZones, (OptionsMenu_Save5_ItemList).l
	move.w	#11, (OptionsMenu_Save5_ItemCount).l

MenuScreen_DataSelect_SaveInitEnd:
	move.w	#MenuItemDeleteSave, (OptionsMenu_DeleteFile_MenuType).l
	move.l	#Txt_DeleteFile, (OptionsMenu_DeleteFile_MenuLabel).l
	move.l	#OptionsMenu_DeleteFile, (OptionsMenu_DeleteFile_MenuOption).l
	
	move.w	#1, (OptionsMenu_Save1_ItemIndex).l
	move.w	#2, (OptionsMenu_Save2_ItemIndex).l
	move.w	#3, (OptionsMenu_Save3_ItemIndex).l
	move.w	#4, (OptionsMenu_Save4_ItemIndex).l
	move.w	#5, (OptionsMenu_Save5_ItemIndex).l
	move.l	#Option_Save1_UserSelect, (OptionsMenu_Save1_ItemValue).l
	move.l	#Option_Save2_UserSelect, (OptionsMenu_Save2_ItemValue).l
	move.l	#Option_Save3_UserSelect, (OptionsMenu_Save3_ItemValue).l
	move.l	#Option_Save4_UserSelect, (OptionsMenu_Save4_ItemValue).l
	move.l	#Option_Save5_UserSelect, (OptionsMenu_Save5_ItemValue).l
	rts

MenuScreen_DataSelect:
	move.l	#OptionsMenu_Saves_Mem,(Options_menu_pointer).l
	move.b	#GameModeID_OptionsMenu,(Game_Mode).w ; => OptionsMenu
	bsr.w	MenuScreen_DataSelect_LoadItems
	bra.s MenuScreen_Init

; loc_8FCC:
MenuScreen_Options:
	move.l	#OptionsMenu_Main,(Options_menu_pointer).l
MenuScreen_Init:
	clr.b	(Options_menu_selection).w

	; Load tile graphics
	lea	(Chunk_Table).l,a1
	lea	(MapEng_Options).l,a0
	move.w	#make_art_tile(ArtTile_ArtNem_MenuBox,0,0),d0
	jsr		EniDec
	lea	(Chunk_Table+$160).l,a1
	lea	(MapEng_Options).l,a0
	move.w	#make_art_tile(ArtTile_ArtNem_MenuBox,1,0),d0
	jsr		EniDec
	clr.b	(Level_started_flag).w
	clr.w	(Anim_Counters).w
	lea	(Anim_SonicMilesBG).l,a2
	jsrto	(Dynamic_Normal).l, JmpTo2_Dynamic_Normal
	moveq	#PalID_Menu,d0
	jsr		PalLoad_ForFade
	clr.w	(Two_player_mode).w
	clr.l	(Camera_X_pos).w
	clr.l	(Camera_Y_pos).w
	clr.w	(Correct_cheat_entries).w
	clr.w	(Correct_cheat_entries_2).w
	bsr.w	OptionsScreen_DrawMenu
	move.b	#VintID_Menu,(Vint_routine).w
	bsr.w	WaitForVint
	music	mus_Options

	move.w	#4,(Vscroll_Factor_FG).w

	move.w	(VDP_Reg1_val).w,d0
	ori.b	#$40,d0
	move.w	d0,(VDP_control_port).l
	jsr		Pal_FadeFromBlack
; loc_9060:
OptionScreen_Main:
	move.b	#VintID_Menu,(Vint_routine).w
	bsr.w	WaitForVint

	bsr.w	OptionsScreen_Input
	bsr.w	OptionsScreen_DrawMenu

	; Animated BG
	lea	(Anim_SonicMilesBG).l,a2
	jsrto	(Dynamic_Normal).l, JmpTo2_Dynamic_Normal

	cmpi.b	#GameModeID_OptionsMenu,(Game_Mode).w 
	beq.w	OptionScreen_Main
; ===========================================================================
;loc_9296
OptionScreen_HexDumpSoundTest:
	move.w	(Sound_test_sound).w,d1
	move.b	d1,d2
	lsr.b	#4,d1
	bsr.s	+
	move.b	d2,d1

+
	andi.w	#$F,d1
	cmpi.b	#$A,d1
	blo.s	+
	addi.b	#4,d1

+
	addi.b	#$10,d1
	move.b	d1,d0
	move.w	d0,(a2)+
	rts