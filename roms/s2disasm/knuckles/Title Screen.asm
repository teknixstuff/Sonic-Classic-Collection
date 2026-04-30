
Obj_IntroStars_Knux:	
	moveq	#0,d0
	move.b	routine(a0),d0
	move.w	Obj_IntroStars_Knux_Index(pc,d0.w),d1
	jmp	Obj_IntroStars_Knux_Index(pc,d1.w)
; ---------------------------------------------------------------------------
;off_30FE66:
Obj_IntroStars_Knux_Index:	offsetTable
	offsetTableEntry.w Obj_IntroStars_Knux_Init
	offsetTableEntry.w Obj_IntroStars_Knux_Knux
	offsetTableEntry.w loc_3100B8
	offsetTableEntry.w loc_310124
	offsetTableEntry.w loc_3101E4
	offsetTableEntry.w loc_3102A4
	offsetTableEntry.w loc_3103BC
	offsetTableEntry.w loc_310196
	offsetTableEntry.w loc_310374
	offsetTableEntry.w loc_310434
	offsetTableEntry.w loc_310474
	offsetTableEntry.w loc_31052A
	offsetTableEntry.w loc_31056A
; ---------------------------------------------------------------------------

;loc_30FE80:
Obj_IntroStars_Knux_Init:
    addq.b	#2,routine(a0)
    move.w	#$150,art_tile(a0)
    move.b	#4,priority(a0)
    move.b	subtype(a0),routine(a0)
    bra.s	Obj_IntroStars_Knux
; ---------------------------------------------------------------------------

Obj_IntroStars_Knux_Knux:
	addq.w	#1,objoff_34(a0)
	cmpi.w	#$120,objoff_34(a0)
    bcc.s	+
	bsr.w	TitleScreen_SetFinalState
+
	moveq	#0,d0
	move.b	routine_secondary(a0),d0
    move.w	off_30FEB6(pc,d0.w),d1
    jmp	off_30FEB6(pc,d1.w)
; ---------------------------------------------------------------------------
off_30FEB6: offsetTable
    offsetTableEntry.w Obj_IntroStars_Knux_Knux_Init
    offsetTableEntry.w loc_30FF1E
    offsetTableEntry.w loc_30FF46
    offsetTableEntry.w loc_30FF76
    offsetTableEntry.w loc_30FFD0
    offsetTableEntry.w loc_30FFDE
    offsetTableEntry.w loc_310000
    offsetTableEntry.w loc_310040
    offsetTableEntry.w loc_310082
; ---------------------------------------------------------------------------

Obj_IntroStars_Knux_Knux_Init:
    addq.b	#2,routine_secondary(a0)
    move.l	#Map_Obj0E,mappings(a0)
    move.w	#$8150,art_tile(a0)
    move.b	#0,mapping_frame(a0)
	move.w	#$110,x_pixel(a0)
	move.w	#$E0,Obj_IntroStars_Dest(a0)
	lea	(IntroLargeStar).w,a1
	move.l	#Obj_IntroStars,id(a1)		; load Obj_IntroStars (flashing intro stars)
	move.b	#8,subtype(a1)			; large star
	lea	(IntroEmblemTop).w,a1
	move.l	#Obj_IntroStars,id(a1)		; load Obj_IntroStars (flashing intro stars)
	move.b	#6,subtype(a1)			; logo top
    lea	(IntroTextBanner).w,a1
	move.l	#Obj_IntroStars,id(a1)		; load Obj_IntroStars (flashing intro stars)
    move.b	#$12,subtype(a1)
	sfx	sfx_Sparkle

; ---------------------------------------------------------------------------

loc_30FF1E:
	cmpi.w	#$38,objoff_34(a0)
    bcc.s	+
    rts
; ---------------------------------------------------------------------------

+
	addq.b	#2,routine_secondary(a0)
	lea	(TitleScreenPaletteChanger3).w,a1
	move.l	#Obj_TitleScreenPalChanger,id(a1)	; load Obj_TitleScreenPalChanger (palette change)
	move.b	#0,subtype(a1)
	st.b	objoff_30(a0)
	music	mus_Title			 ; title music
    rts
; ---------------------------------------------------------------------------

loc_30FF46:
	cmpi.w	#$80,objoff_34(a0)
	bhs.s	+
	rts
; ---------------------------------------------------------------------------

+
    addq.b	#2,routine_secondary(a0)
    lea	(Pal_TitleKnuckles).l,a1
    lea	(Normal_palette).w,a2
    
    moveq	#$F,d6
-   move.w	(a1)+,(a2)+
    dbf	d6,-

	lea	(IntroSmallStar1).w,a1
	move.l	#Obj_IntroStars,id(a1) ; load Obj_IntroStars (flashing intro star) at $FFFFB180
	move.b	#$E,subtype(a1)				; piece of sky
	rts
; ---------------------------------------------------------------------------

loc_30FF76:
    ;moveq	#word_30FFB0_end-word_30FFB0+4,d2 
	moveq	#$24,d2
    lea	(word_30FFB0).l,a1

loc_30FF7E:
    move.w	objoff_2A(a0),d0
    addq.w	#1,d0
    move.w	d0,objoff_2A(a0)
    and.w	#3,d0
    bne.s	+
    move.w	objoff_2C(a0),d1
    addq.w	#4,d1
    cmp.w	d2,d1
    bcc.w	loc_3103A0
    move.w	d1,objoff_2C(a0)
    move.l	-4(a1,d1.w),d0
    move.w	d0,x_sub(a0)
    swap	d0
    move.w	d0,x_pos(a0)
+
	rts
    bra.w	DisplaySprite
; ---------------------------------------------------------------------------
word_30FFB0:	dc.w   $F4,  $D0,  $F8,	 $C0,  $FC,  $B2, $100,	 $A6, $104,  $9E,  $FE,	 $98,  $F8,  $94,  $F4,	 $92
word_30FFB0_end
; ---------------------------------------------------------------------------

loc_30FFD0:
	rts

    lea	(Ani_Obj0E).l,a1
    bsr.w	AnimateSprite
    bra.w	DisplaySprite
; ---------------------------------------------------------------------------

loc_30FFDE:
    addq.b	#2,routine_secondary(a0)
    move.b	#4,mapping_frame(a0)
    move.w	x_sub(a0),objoff_2A(a0)
    lea	(IntroSonicHand).w,a1
    move.l	#Obj_IntroStars,id(a1) ; load Obj_IntroStars (flashing intro star) at $FFFFB1C0
    move.b	#$A,subtype(a1)
    bra.w	DisplaySprite
; ---------------------------------------------------------------------------

loc_310000:
    cmpi.w	#$120,objoff_34(a0)
    bcs.s	+
    addq.b	#2,routine_secondary(a0)
    clr.w	objoff_2C(a0)
	st	objoff_2F(a0)
	lea	(Normal_palette_line3).w,a1
    move.w	#$EEE,d0

-   moveq	#$F,d6
    move.w	d0,(a1)+
    dbf	d6,-

	lea	(TitleScreenPaletteChanger2).w,a1
	move.l	#Obj_TitleScreenPalChanger,id(a1) ; load Obj_TitleScreenPalChanger (palette change handler) at $FFFFB240
	move.b	#2,subtype(a1)
	move.l	#Obj_TitleMenu,(TitleScreenMenu+id).w ; load Obj_TitleMenu (title screen menu) at $FFFFB400
+
    bsr.w	sub_31017E
    bra.w	DisplaySprite
; ---------------------------------------------------------------------------

loc_310040:
    btst	#6,(Graphics_Flags).w
    beq.s	+
    cmp.w	#$190,objoff_34(a0)
    beq.s	++
    bsr.w	sub_31017E
    bra.w	DisplaySprite
; ---------------------------------------------------------------------------
+
    cmp.w	#$1D0,objoff_34(a0)
    beq.s	+
    bsr.w	sub_31017E
    bra.w	DisplaySprite
; ---------------------------------------------------------------------------

+
	lea	(IntroSmallStar2).w,a1
	move.l	#Obj_IntroStars,id(a1) ; load Obj_IntroStars (flashing intro star) at $FFFFB440
	move.b	#$C,subtype(a1)				; small star
	addq.b	#2,routine_secondary(a0)
    bsr.w	sub_31017E
    bra.w	DisplaySprite
; ---------------------------------------------------------------------------

loc_310082:
	move.b	(Vint_runcount+3).w,d0
    and.b	#7,d0
    bne.s	++
    move.w	objoff_2C(a0),d0
    addq.w	#2,d0
	cmpi.w	#CyclingPal_TitleStar_Knux_End-CyclingPal_TitleStar_Knux,d0
    bcs.s	+
    moveq	#0,d0
+
    move.w	d0,objoff_2C(a0)
    move.w	CyclingPal_TitleStar_Knux(pc,d0.w),(Normal_palette_line3+$A).w
+
    bsr.w	sub_31017E
    bra.w	DisplaySprite
; ---------------------------------------------------------------------------
CyclingPal_TitleStar_Knux:	dc.w  $E64, $E86, $E64,	$EA8, $E64, $ECA; 0 ; ...
CyclingPal_TitleStar_Knux_End
; ---------------------------------------------------------------------------

loc_3100B8:
    moveq	#0,d0
    move.b	routine_secondary(a0),d0
    move.w	off_3100C6(pc,d0.w),d1
    jmp	off_3100C6(pc,d1.w)
; ---------------------------------------------------------------------------
off_3100C6:	
    dc.w loc_3100CA-off_3100C6
    dc.w return_310122-off_3100C6
; ---------------------------------------------------------------------------

loc_3100CA:
    subq.w	#1,objoff_2A(a0)
    bpl.s	+
    move.w	#1,objoff_2A(a0)
    move.w	objoff_2C(a0),d0
    move.w	word_3100F8(pc,d0.w),d1
    move.w	d1,(Vscroll_Factor).w
    move.w	d1,(Title_TextBanner).w
    addq.w	#2,d0
    move.w	d0,objoff_2C(a0)
    cmp.w	#$2A,d0
    bcs.s	+
    addq.b	#2,routine_secondary(a0)
+
    rts
; ---------------------------------------------------------------------------
word_3100F8:	dc.w	  0,	-1,    -3,    -6,   -$A,  -$10,	 -$18; 0 ; ...
    dc.w   -$14,  -$12,   -$E,   -$D,   -$C,   -$D,	  -$E; 7
    dc.w   -$10,  -$14,  -$18,  -$16,  -$15,  -$16,	 -$18; 14
; ---------------------------------------------------------------------------

return_310122:
    rts
; ---------------------------------------------------------------------------

loc_310124:
    moveq	#0,d0
    move.b	routine_secondary(a0),d0
    move.w	off_310136(pc,d0.w),d1
    jsr	off_310136(pc,d1.w)
    bra.w	DisplaySprite
; ---------------------------------------------------------------------------
off_310136:	dc.w loc_31013C-off_310136	  ; 0 ;	...
		dc.w sub_31017E-off_310136	  ; 1
		dc.w return_3101E2-off_310136	  ; 2
; ---------------------------------------------------------------------------

loc_31013C:
		addq.b	#2,routine_secondary(a0)
		lea	(IntroEmblemTop).w,a1

; =============== S U B	R O U T	I N E =======================================


sub_310144:
		move.l	#Map_Obj0E_0,mappings(a1)
		move.w	#0,art_tile(a1)
		move.b	#1,mapping_frame(a1)
		tst.b	(Graphics_Flags).w
		bmi.s	loc_310164
		move.b	#0,mapping_frame(a1)

loc_310164:
		move.b	#2,priority(a1)
		move.w	#$120,x_pos(a1)
		move.w	#$E8,d0
		move.w	d0,x_sub(a1)
		move.w	d0,objoff_2A(a1)
		rts
; End of function sub_310144


; =============== S U B	R O U T	I N E =======================================


sub_31017E:
		tst.b	(Title_EnableTextBanner).w
		bne.s	return_310194
		move.w	(Title_TextBanner).w,d0
		neg.w	d0
		move.w	objoff_2A(a0),d1
		add.w	d0,d1
		move.w	d1,x_sub(a0)

return_310194:
		rts
; End of function sub_31017E

; ---------------------------------------------------------------------------

loc_310196:
		moveq	#0,d0
		move.b	routine_secondary(a0),d0
		move.w	off_3101A8(pc,d0.w),d1
		jsr	off_3101A8(pc,d1.w)
		bra.w	DisplaySprite
; ---------------------------------------------------------------------------
off_3101A8:	dc.w loc_3101AE-off_3101A8	  ; 0 ;	...
		dc.w sub_31017E-off_3101A8
		dc.w return_3101E2-off_3101A8
; ---------------------------------------------------------------------------

loc_3101AE:
		addq.b	#2,routine_secondary(a0)
		lea	(IntroSmallStar1).w,a1

; =============== S U B	R O U T	I N E =======================================


sub_3101B6:
		move.l	#Map_Obj0E_0,mappings(a1)
		move.w	#0,art_tile(a1)
		move.b	#2,mapping_frame(a1)
		move.b	#2,priority(a1)
		move.w	#$100,x_pos(a1)
		move.w	#$F0,d0
		move.w	d0,x_sub(a1)
		move.w	d0,objoff_2A(a1)

return_3101E2:
		rts
; End of function sub_3101B6

; ---------------------------------------------------------------------------

loc_3101E4:
		moveq	#0,d0
		move.b	routine_secondary(a0),d0
		move.w	off_3101F2(pc,d0.w),d1
		jmp	off_3101F2(pc,d1.w)
; ---------------------------------------------------------------------------
off_3101F2:	dc.w loc_3101FA-off_3101F2	  ; ...
		dc.w loc_30FFD0-off_3101F2
		dc.w loc_310232-off_3101F2
		dc.w loc_310240-off_3101F2
; ---------------------------------------------------------------------------

loc_3101FA:
		addq.b	#2,routine_secondary(a0)
		move.b	#0,mapping_frame(a0)
		move.l	#Map_Obj0E_1,mappings(a0)
		move.w	#$A3C0,art_tile(a0)
		move.b	#2,anim(a0)
		move.b	#1,priority(a0)
		move.w	#$100,x_pos(a0)
		move.w	#$A8,x_sub(a0)
		move.w	#4,objoff_2A(a0)
		rts
; ---------------------------------------------------------------------------

loc_310232:
		subq.w	#1,objoff_2A(a0)
		bmi.s	loc_31023A
		rts
; ---------------------------------------------------------------------------

loc_31023A:
		addq.b	#2,routine_secondary(a0)
		rts
; ---------------------------------------------------------------------------

loc_310240:
		move.b	#2,routine_secondary(a0)
		move.b	#0,anim_frame(a0)
		move.b	#0,anim_frame_duration(a0)
		move.w	#6,objoff_2A(a0)
		move.w	objoff_2C(a0),d0
		addq.w	#4,d0
		cmp.w	#$28,d0
		bcc.w	DeleteObject
		move.w	d0,objoff_2C(a0)
		move.l	word_310280-4(pc,d0),d0
		move.w	d0,x_sub(a0)
		swap	d0
		move.w	d0,x_pos(a0)
		moveq	#-$59,d0
		;jmp	PlaySound
		rts
; ---------------------------------------------------------------------------
word_310280:	dc.w   $DA,  $F2, $170,	 $F8, $132, $131, $19E,	 $A2,  $C0,  $E3, $180,	 $E0, $10D, $13B,  $C0,	 $AB, $165, $107; 0 ; ...
; ---------------------------------------------------------------------------

loc_3102A4:
		moveq	#0,d0
		move.b	routine_secondary(a0),d0
		move.w	off_3102B6(pc,d0.w),d1
		jsr	off_3102B6(pc,d1.w)
		bra.w	DisplaySprite
; ---------------------------------------------------------------------------
off_3102B6:	dc.w loc_3102C6-off_3102B6	  ; 0 ;	...
		dc.w sub_310306-off_3102B6
		dc.w loc_30FFD0-off_3102B6
		dc.w sub_310322-off_3102B6
		dc.w sub_310346-off_3102B6
		dc.w loc_30FFD0-off_3102B6
		dc.w sub_31035E-off_3102B6
		dc.w nullsub_2-off_3102B6
; ---------------------------------------------------------------------------

loc_3102C6:
		addq.b	#2,routine_secondary(a0)
		move.w	#3,objoff_2A(a0)

; =============== S U B	R O U T	I N E =======================================


sub_3102D0:
		lea	(IntroSonicHand).w,a1
		move.l	#Map_Obj0E,mappings(a1)
		move.w	#$8150,art_tile(a1)
		move.b	#5,mapping_frame(a1)
		move.b	#3,priority(a1)
		lea	(IntroSonic).w,a2
		move.w	x_pos(a2),x_pos(a1)
		move.w	x_sub(a2),d0
		add.w	#$30,d0
		move.w	d0,x_sub(a1)
		rts
; End of function sub_3102D0


; =============== S U B	R O U T	I N E =======================================


sub_310306:
		subq.w	#2,x_sub(a0)
		subq.w	#1,objoff_2A(a0)
		bpl.s	return_310320
		addq.b	#2,routine_secondary(a0)
		move.b	#4,anim(a0)
		move.w	#3,objoff_2A(a0)

return_310320:
		rts
; End of function sub_310306


; =============== S U B	R O U T	I N E =======================================


sub_310322:
		addq.w	#2,x_sub(a0)
		subq.w	#1,objoff_2A(a0)
		bpl.s	return_310344
		addq.b	#2,routine_secondary(a0)
		move.w	x_sub(a0),objoff_2A(a0)
		lea	(IntroTextBanner).w,a1
        move.l	#Obj_IntroStars,id(a1) ; load Obj_IntroStars (flashing intro star) at $FFFFB440
		move.b	#4,subtype(a1)

return_310344:
		rts
; End of function sub_310322


; =============== S U B	R O U T	I N E =======================================


sub_310346:
		bsr.w	sub_31017E
		cmpi.w	#$125,(IntroSonic+objoff_34).w
		bne.s	return_31035C
		addq.b	#2,routine_secondary(a0)
		move.w	#$400,anim(a0)

return_31035C:
		rts
; End of function sub_310346


; =============== S U B	R O U T	I N E =======================================


sub_31035E:
		addq.b	#2,routine_secondary(a0)
		lea	(IntroTails).w,a1
        move.l	#Obj_IntroStars,id(a1) ; load Obj_IntroStars (flashing intro star) at $FFFFB440
		move.b	#$14,subtype(a1)
		rts
; End of function sub_31035E


; =============== S U B	R O U T	I N E =======================================


nullsub_2:
		rts
; End of function nullsub_2

; ---------------------------------------------------------------------------

loc_310374:
		moveq	#0,d0
		move.b	routine_secondary(a0),d0
		move.w	off_310382(pc,d0.w),d1
		jmp	off_310382(pc,d1.w)
; ---------------------------------------------------------------------------
off_310382:	dc.w loc_310388-off_310382	  ; 0 ;	...
		dc.w loc_3103A8-off_310382	  ; 1
		dc.w loc_3103A4-off_310382	  ; 2
; ---------------------------------------------------------------------------

loc_310388:
		move.b	#$13,mapping_frame(a0)
		move.b	#3,priority(a0)
		move.w	#$10F,x_pos(a0)
		move.w	#$D5,x_sub(a0)

loc_3103A0:
		addq.b	#2,routine_secondary(a0)

loc_3103A4:
	rts

		bra.w	DisplaySprite
; ---------------------------------------------------------------------------

loc_3103A8:
		moveq	#$C,d2
		lea	(loc_3103B4).l,a1
		bra.w	loc_30FF7E
; ---------------------------------------------------------------------------

loc_3103B4:
		movep.w	$D0(a4),d0
		movep.w	$D1(a5),d0

loc_3103BC:
		moveq	#0,d0
		move.b	routine_secondary(a0),d0
		move.w	off_3103CA(pc,d0.w),d1
		jmp	off_3103CA(pc,d1.w)
; ---------------------------------------------------------------------------
off_3103CA:	dc.w loc_3103CE-off_3103CA	  ; 0 ;	...
		dc.w loc_310408-off_3103CA	  ; 1
; ---------------------------------------------------------------------------

loc_3103CE:
		addq.b	#2,routine_secondary(a0)
		move.l	#Map_Obj0E_1,mappings(a0)
		move.w	#$23C0,art_tile(a0)
		move.b	#0,mapping_frame(a0)
		move.b	#5,priority(a0)
		move.w	#$170,x_pos(a0)
		move.w	#$80,x_sub(a0)
		move.b	#3,anim(a0)
		move.w	#$8C,objoff_2A(a0)
		bra.w	DisplaySprite
; ---------------------------------------------------------------------------

loc_310408:
		subq.w	#1,objoff_2A(a0)
		bmi.w	DeleteObject
		cmp.w	#$3C,objoff_2A(a0)
		bne.s	loc_31041E
		move.b	#1,priority(a0)

loc_31041E:
		subq.w	#2,x_pos(a0)
		addq.w	#1,x_sub(a0)
		lea	(Ani_Obj0E).l,a1
		bsr.w	AnimateSprite
		bra.w	DisplaySprite
; ---------------------------------------------------------------------------

loc_310434:
		moveq	#0,d0
		move.b	routine_secondary(a0),d0
		move.w	off_310442(pc,d0.w),d1
		jmp	off_310442(pc,d1.w)
; ---------------------------------------------------------------------------
off_310442:	dc.w loc_310446-off_310442	  ; 0 ;	...
		dc.w loc_310470-off_310442	  ; 1
; ---------------------------------------------------------------------------

loc_310446:
		addq.b	#2,routine_secondary(a0)
		move.l	#Map_Obj0E_2,mappings(a0)
		move.w	#$E3DD,art_tile(a0)
		move.b	#1,mapping_frame(a0)
		move.b	#1,priority(a0)
		move.w	#$160,x_pos(a0)
		move.w	#$148,x_sub(a0)

loc_310470:
		bra.w	DisplaySprite
; ---------------------------------------------------------------------------

loc_310474:
		moveq	#0,d0
		move.b	routine_secondary(a0),d0
		move.w	off_310486(pc,d0.w),d1
		jsr	off_310486(pc,d1.w)
		bra.w	DisplaySprite
; ---------------------------------------------------------------------------
off_310486:	dc.w loc_31048C-off_310486	  ; 0 ;	...
		dc.w sub_3104CC-off_310486	  ; 1
		dc.w byte_3201E2-off_310486	  ; 2
; ---------------------------------------------------------------------------

loc_31048C:
		addq.b	#2,routine_secondary(a0)
		move.w	#$200,y_vel(a0)
		lea	(IntroTails).w,a1

; =============== S U B	R O U T	I N E =======================================


sub_31049A:
		move.l	#Map_Obj0E_3,mappings(a1)
		move.w	#$8000,art_tile(a1)
		clr.b	mapping_frame(a1)
		move.b	#1,priority(a1)
		move.w	#$120,d0
		move.w	d0,x_pos(a1)
		move.w	d0,objoff_2A(a1)
		move.w	#$68,d0
		move.w	d0,x_sub(a1)
		move.w	d0,objoff_2E(a1)
		rts
; End of function sub_31049A


; =============== S U B	R O U T	I N E =======================================


sub_3104CC:
		move.l	objoff_2A(a0),d2
		move.l	objoff_2E(a0),d3
		move.w	$10(a0),d0
		ext.l	d0
		asl.l	#8,d0
		add.l	d0,d2
		move.w	y_vel(a0),d0
		add.w	#$38,y_vel(a0)
		ext.l	d0
		asl.l	#8,d0
		add.l	d0,d3
		move.l	d2,objoff_2A(a0)
		move.l	d3,objoff_2E(a0)
		swap	d2
		swap	d3
		move.w	d2,x_pos(a0)
		move.w	d3,x_sub(a0)
		move.w	y_vel(a0),d0
		bmi.s	return_310528
		move.w	#$A4,d1
		cmp.w	x_sub(a0),d1
		bhi.s	return_310528
		move.w	d1,x_sub(a0)
		asr.w	#2,d0
		neg.w	d0
		move.w	d0,y_vel(a0)
		cmp.w	#$FF00,d0
		blt.s	return_310528
		addq.b	#2,routine_secondary(a0)

return_310528:
		rts
; End of function sub_3104CC

; ---------------------------------------------------------------------------

loc_31052A:
		moveq	#0,d0
		move.b	routine_secondary(a0),d0
		move.w	off_31053C(pc,d0.w),d1
		jsr	off_31053C(pc,d1.w)
		bra.w	DisplaySprite
; ---------------------------------------------------------------------------
off_31053C:	dc.w loc_310540-off_31053C	  ; 0 ;	...
		dc.w byte_3201E2-off_31053C	  ; 1
; ---------------------------------------------------------------------------

loc_310540:
		addq.b	#2,routine_secondary(a0)
		move.l	#Map_Obj0E_3,mappings(a0)
		move.w	#$8000,art_tile(a0)
		clr.b	mapping_frame(a0)
		move.b	#1,priority(a0)
		move.w	#$120,x_pos(a0)
		move.w	#$C4,x_sub(a0)
		rts
; ---------------------------------------------------------------------------

loc_31056A:
		moveq	#0,d0
		move.b	routine_secondary(a0),d0
		move.w	off_31057C(pc,d0.w),d1
		jsr	off_31057C(pc,d1.w)
		bra.w	DisplaySprite
; ---------------------------------------------------------------------------
off_31057C:	dc.w loc_310580-off_31057C	  ; 0 ;	...
		dc.w return_3101E2-off_31057C
; ---------------------------------------------------------------------------

loc_310580:
		addq.b	#2,routine_secondary(a0)
		move.l	#Map_Obj0E_2,mappings(a0)
		move.w	#$E3DD,art_tile(a0)
		move.b	#2,mapping_frame(a0)
		move.b	#1,priority(a0)
		move.w	#$1A4,x_pos(a0)
		move.w	#$B0,x_sub(a0)
		rts
; ---------------------------------------------------------------------------
Ani_Obj0E:	dc.w byte_3108F0-Ani_Obj0E	  ; 0 ;	...
		dc.w byte_3108F6-Ani_Obj0E	  ; 1
		dc.w byte_3108FE-Ani_Obj0E	  ; 2
		dc.w byte_310906-Ani_Obj0E	  ; 3
		dc.w byte_31090A-Ani_Obj0E	  ; 4
byte_3108F0:	dc.b   3,  0,  1,  2,  3,$FA	  ; 0 ;	...
byte_3108F6:	dc.b   1,  0,  1,  2,  3,  4,$FA,  0
byte_3108FE:	dc.b   1,  0,  1,  2,  1,  0,$FA,  0
byte_310906:	dc.b   3,  0,  3,$FF		  ; 0 ;	...
byte_31090A:	dc.b   3,  5,  6,  7,  7,  6,  5,$FA
; ---------------------------------------------------------------------------
Map_Obj0E_1:	
	dc.w byte_31091A-Map_Obj0E_1
	dc.w byte_310922-Map_Obj0E_1
	dc.w byte_31092A-Map_Obj0E_1
	dc.w byte_310932-Map_Obj0E_1
byte_31091A:	dc.b   0,  1,$FC,  0,  0,  0,$FF,$FC
byte_310922:	dc.b   0,  1,$F8,  5,  0,  1,$FF,$F8
byte_31092A:	dc.b   0,  1,$F4, $A,  0,  5,$FF,$F4
byte_310932:	dc.b   0,  1,$FC,  0,  0, $E,$FF,$FC
; ---------------------------------------------------------------------------
Map_Obj0E_0:	dc.b   0,  6,  0,$2C,  0,$58,  0,  6,  0
				dc.b  $C,$E3,$CF,$FF,$B0,  0,  8,$E3,$D3
				dc.b $FF,$D0,  0, $C,$E3,$D6,  0,$18,  0
				dc.b   8,$E3,$DA,  0,$38,  0, $C,  0,$10
				dc.b $FF,$E8,  0,  4,  0,$10,  0,  8,  0
				dc.b   7,  0, $C,$E3,$CF,$FF,$B0,  0,  8
				dc.b $E3,$D3,$FF,$D0,  0, $C,$E3,$D6,  0
				dc.b $18,  0,  8,$E3,$DA,  0,$38,  0, $C
				dc.b   0,$10,$FF,$E8,  0,  4,  0,$10,  0
				dc.b   8,  8,  4,$E3,$FC,  0,$58,  0,  6
				dc.b   0,  3,  0,  0,  0,  8,  0,  3,  0
				dc.b   0,  0,  0,$20,  3,  0,  0,  0,  8
				dc.b $20,  3,  0,  0,  0,  0,$40,  3,  0
				dc.b   0,  0,  8,$40,  3,  0,  0,  0,  0
; ---------------------------------------------------------------------------
Map_Obj0E:
	dc.w byte_3109C8-Map_Obj0E
	dc.w byte_310A0C-Map_Obj0E
	dc.w byte_310A5C-Map_Obj0E
	dc.w byte_310AAC-Map_Obj0E
	dc.w byte_310AEA-Map_Obj0E
	dc.w byte_310B28-Map_Obj0E
	dc.w byte_310B42-Map_Obj0E
	dc.w byte_310B5C-Map_Obj0E
byte_3109C8:	dc.b   0, $B,$18, $F,  0,  0,  0,$48,$38
				dc.b  $F,  0,$10,  0,$48,$38, $F,  0,$20
				dc.b   0,$28,$18, $F,  0,$30,  0,$28,$10
				dc.b   4,  0,$40,  0,$50,  8,  9,  0,$42
				dc.b   0,$38,$10, $C,  0,$48,  0,$18,$18
				dc.b  $D,  0,$4C,  0,  8,$30,  5,  0,$54
				dc.b   0,  0,$30,  0,  0,$58,  0,$20,$38
				dc.b  $B,  0,$59,  0,$10
byte_310A0C:	dc.b   0, $D,$10, $F,  0,$65,  0,$40,$30
				dc.b  $F,  0,$75,  0,$40,$10, $F,  0,$85
				dc.b   0,$20,$30, $F,  0,$95,  0,$20,  8
				dc.b  $C,  0,$A5,  0,$20,  8,  8,  0,$A9
				dc.b   0,$40,$10, $A,  0,$AC,  0,  8,$20
				dc.b   3,  0,$B5,  0,  0,$28,  0,  0,$B9
				dc.b   0,$18,$30, $A,  0,$BA,  0,  8,$48
				dc.b   5,  0,$C3,  0,$10,$50, $C,  0,$C7
				dc.b   0,$20,$50,  8,  0,$CB,  0,$40
byte_310A5C:	dc.b   0, $D,$40,  6,  0,$CE,  0,$60,$38
				dc.b  $F,  0,$D4,  0,$40,$18, $F,  0,$E4
				dc.b   0,$40,$18, $F,  0,$F4,  0,$20,$38
				dc.b  $F,  1,  4,  0,$20,  8,  5,  1,$14
				dc.b   0,$48,  0, $A,  1,$18,  0,$30,  8
				dc.b   5,  1,$21,  0,$20,$10,  9,  1,$25
				dc.b   0,  8,$20, $C,  1,$2B,  0,  0,$28
				dc.b   7,  1,$2F,  0,$10,$30,  6,  1,$37
				dc.b   0,  0,$48,  9,  1,$3D,  0,  8
byte_310AAC:	dc.b   0, $A,$38, $F,  1,$43,  0,  0,$18
				dc.b  $F,  1,$53,  0,  0,$18, $F,  1,$63
				dc.b   0,$20,$38, $F,  1,$73,  0,$20,  8
				dc.b   9,  1,$83,  0,  8,  0, $E,  1,$89
				dc.b   0,$20,  8,  7,  1,$95,  0,$40,$28
				dc.b   5,  1,$9D,  0,$40,$38, $F,  1,$A1
				dc.b   0,$40,$48,  1,  1,$B1,  0,$60
byte_310AEA:	dc.b   0, $A,  8,  7,  1,$B3,  0,$40,$28
				dc.b   6,  1,$BB,  0,$40,$40, $E,  1,$C1
				dc.b   0,$40,  0, $F,  1,$CD,  0,$20,$20
				dc.b  $F,  1,$DD,  0,$20,$40, $E,  1,$ED
				dc.b   0,$20,  0, $A,  1,$F9,  0,  8,$18
				dc.b  $F,  2,  2,  0,  0,$38, $D,  2,$12
				dc.b   0,  0,$48,  9,  2,$1A,  0,  8
byte_310B28:	dc.b   0,  4,$10, $F,  2,$20,  0,  8,  0
				dc.b   9,  2,$30,  0,$10,  8,  3,  2,$36
				dc.b   0,$28,$10,  0,  2,$3A,  0,$30
byte_310B42:	dc.b   0,  4,  0,  0,  2,$3B,  0,$18,  8
				dc.b  $F,  2,$3C,  0,$10,$10,  2,  2,$4C
				dc.b   0,  8,$28, $D,  2,$4F,  0,  8
byte_310B5C:	dc.b   0,  4,  8, $F,  2,$57,  0,  8,  8
				dc.b   3,  2,$67,  0,$28,$28, $C,  2,$6B
				dc.b   0,  8,$28,  0,  2,$6F,  0,$28
; ---------------------------------------------------------------------------
Map_Obj0E_3:	dc.w byte_310B78-Map_Obj0E_3	  ; ...
byte_310B78:	dc.b   0,$1F,$E8,  2,$63,$FE,$FF,$84,  0
				dc.b   2,$64,  1,$FF,$84,$E8, $C,$64,  4
				dc.b $FF,$8C,$F0, $F,$64,  8,$FF,$8C,$10
				dc.b  $C,$64,$18,$FF,$8C,$E8, $C,$64,  4
				dc.b $FF,$AC,$F0, $F,$64,$1C,$FF,$AC,$10
				dc.b  $C,$64,$18,$FF,$AC,$E8, $C,$64,  4
				dc.b $FF,$CC,$F0, $F,$64,$2C,$FF,$CC,$10
				dc.b  $C,$64,$18,$FF,$CC,$E8, $C,$64,  4
				dc.b $FF,$EC,$F0, $F,$64,$3C,$FF,$EC,$10
				dc.b  $C,$64,$18,$FF,$EC,$E8, $C,$64,  4
				dc.b   0, $C,$F0, $F,$64,$4C,  0, $C,$10
				dc.b  $C,$64,$18,  0, $C,$E8, $C,$64,  4
				dc.b   0,$2C,$F0, $F,$64,$5C,  0,$2C,$10
				dc.b  $C,$64,$18,  0,$2C,$E8, $C,$64,  4
				dc.b   0,$4C,$F0, $F,$64,$6C,  0,$4C,$10
				dc.b  $C,$64,$18,  0,$4C,$E8,  2,$64,$7C
				dc.b   0,$6C,  0,  2,$64,$7F,  0,$6C,$E8
				dc.b   2,$64,$82,  0,$74,  0,  2,$64,$85
				dc.b   0,$74,$18,  9,$64,$88,$FF,$A8,$18
				dc.b  $D,$64,$8E,$FF,$C8,$18,  9,$64,$96
				dc.b $FF,$E8,$18, $A,$64,$9C,  0,$28
; ---------------------------------------------------------------------------
Map_Obj0E_2:
	dc.w byte_310C3A-Map_Obj0E_2
	dc.w byte_310C4E-Map_Obj0E_2
	dc.w byte_310C62-Map_Obj0E_2
byte_310C3A:	dc.b   0,  3,$FC, $C,  0,  0,$FF,$D4,$FC
				dc.b   8,  0,  4,$FF,$F4,$FC, $C,  0,  7
				dc.b   0, $C
byte_310C4E:	dc.b   0,  3,  0, $D,  0, $B,  0,  0,  0
				dc.b   9,  0,$13,  0,$20,  0,  9,  0,$19
				dc.b   0,$38
byte_310C62:	dc.b   0,  1,  0,  4,  0,$1F,  0,  0
; ---------------------------------------------------------------------------

Pal_TitleKnuckles:dc.w	$E20,	 0,   $A, $82E,	$40E,	$E,    8, $868,	$68A; 0	; ...
		dc.w  $ACE, $AA8, $EEE,	   0, $24A, $8AE,    0;	9

; ???????????????????????????????? no fucking clue what this is about
byte_3201E2:	dc.b   $E,  $E,	 $D,  $D,  $D,	$D,  $D,  $D,  $D,  $D;	0 ; ...
