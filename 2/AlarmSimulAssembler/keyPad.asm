;----------------------------------------------------------------------
; File: Keypad.asm
; Author:

; Description:
;  This contains the code for reading the
;  16-key keypad attached to Port A
;  See the schematic of the connection in the
;  design document.
;
;  The following subroutines are provided by the module
;
; char pollReadKey(): to poll keypad for a keypress
;                 Checks keypad for 2 ms for a keypress, and
;                 returns NOKEY if no keypress is found, otherwise
;                 the value returned will correspond to the
;                 ASCII code for the key, i.e. 0-9, *, # and A-D
; void initkey(): Initialises Port A for the keypad
;
; char readKey(): to read the key on the keypad
;                 The value returned will correspond to the
;                 ASCII code for the key, i.e. 0-9, *, # and A-D
;---------------------------------------------------------------------

; Include header files
    include "sections.inc"
    include "reg9s12.inc"  ; Defines EQU's for Peripheral Ports

**************EQUATES**********


;-----Conversion table
NUMKEYS	EQU	16	; Number of keys on the keypad
BADCODE 	EQU	$FF 	; returned of translation is unsuccessful
NOKEY		EQU 	$00   ; No key pressed during poll period
POLLCOUNT	EQU	1     ; Number of loops to create 1 ms poll time

    SWITCH globalConst  ; Constant data

    OFFSET 0
keycodeToCharTable_keycode           ds.b 1
keycodeToCharTable_character         ds.b 1
keycodeToCharTable_structLength      ds.b 1

keycodeToCharTable: dc.b $ee,'1'
    dc.b $ed,'2'
    dc.b $eb,'3'
    dc.b $e7,'A'
    dc.b $de,'4'
    dc.b $dd,'5'
    dc.b $db,'6'
    dc.b $d7,'B'
    dc.b $be,'7'
    dc.b $bd,'8'
    dc.b $bb,'9'
    dc.b $b7,'C'
    dc.b $7e,'*'
    dc.b $7d,'0'
    dc.b $7b,'#'
    dc.b $77,'D'
    
    SWITCH code_section  ; place in code section
;-----------------------------------------------------------	
; Subroutine: initKeyPad
;
; Description: 
; 	Initiliases PORT A
;-----------------------------------------------------------	
initKeyPad: movb #$f0,DDRA
    movb #$01,PUCR
    rts

;-----------------------------------------------------------    
; Subroutine: ch <- pollReadKey
; Parameters: none
; Local variable:
;   c - ASCII Code in accumulator B
; Returns
;   c: NOKEY when no key pressed,
;       otherwise, ASCII Code in accumulator B

; Description:
;  Loops for a period of 2ms, checking to see if
;  key is pressed. Calls readKey to read key if keypress 
;  detected (and debounced) on Port A and get ASCII code for
;  key pressed.
;-----------------------------------------------------------
; Stack Usage
    OFFSET 0  ; to setup offset into stack
PRK_count   DS.B    1
PRK_VARSIZE:
PRK_PR_A    DS.B    1
PRK_RA      DS.W    1

PRK_PORTA_CONST EQU $0f

pollReadKey: psha
    leas -PRK_VARSIZE,SP
    
    ldd #1                        ; setDelay(1);
    jsr setDelay
    
    ldaa #PRK_PORTA_CONST
    staa PORTA                    ; PORTA = 0x0f;
    clrb                          ; c = '\0';
    
    movb #2,PRK_count,SP          ; count = 2;
PRK_DO:                           ; do
                                  ; {
    cmpa PORTA                    ;     if (PORTA != 0x0f)
    beq PRK_IF_1_END              ;     {
PRK_IF_1:
    jsr pollDelay                 ;         pollDelay();
    cmpa PORTA
    beq PRK_IF_2_END              ;         if (PORTA != 0x0f)
PRK_IF_2:                         ;         {
    jsr readKey                   ;             c = readKey();
    bra PRK_DO_END                ;             break;
PRK_IF_2_END:                     ;         }
PRK_IF_1_END:                     ;     }
    dec PRK_count,SP              ; }
    bne PRK_DO                    ; while (--count);
PRK_DO_END:

    leas PRK_VARSIZE,SP
    pula
    rts                           ; return c;

;-----------------------------------------------------------	
; Subroutine: ch <- readKey
; Arguments: none
; Local variable: 
;   c - ASCII Code in accumulator B

; Description:
;  Main subroutine that reads a code from the
;  keyboard using the subroutine readKeybrd.  The
;  code is then translated with the subroutine
;  translate to get the corresponding ASCII code.
;-----------------------------------------------------------	
; Stack Usage
    OFFSET 0  ; to setup offset into stack
RK_code     DS.B    1
RK_VARSIZE:
RK_PR_A     DS.B    1
RK_RA       DS.W    1

RK_PORTA_CONST EQU $0f

readKey: psha
    leas -RK_VARSIZE,SP
    
    ldd #$10                        ; setDelay(10);
    jsr setDelay
    
    clrb                            ; code = 0x00;
RK_DO:                              ; do
                                    ; {
    movb #RK_PORTA_CONST, PORTA     ;     PORTA = 0x0f;
RK_WHILE_1:                         ;     while (PORTA == 0x0f);
    ldaa #RK_PORTA_CONST
    cmpa PORTA
    beq RK_WHILE_1
RK_WHILE_1_END:
    movb PORTA,RK_code,SP           ;     code = PORTA;
    jsr pollDelay                   ;     pollDelay();
RK_DO_END:                          ; }
    ldaa RK_code,SP
    cmpa PORTA                      ; while (code != PORTA);
    bne RK_DO
    
    jsr readKeybrd                  ; c = readKeybrd();
    ldaa #RK_PORTA_CONST
    staa PORTA                      ; PORTA = 0x0f;
RK_WHILE_2:                         ; while (c != PORTA);
    cmpb PORTA
    bne RK_WHILE_2
RK_WHILE_2_END:
    jsr pollDelay                   ; pollDelay();
    jsr translate                   ; c = translate(code);

    leas RK_VARSIZE,SP
    pula
    rts                             ; return code; 


;-----------------------------------------------------------	
; Subroutine: ch <- readKeybrd
; Arguments: none
; Local variable: 
;   code - Keycode in accumulator B

; Description:
;   Read a keycode from the keyboard in accumulator B
;-----------------------------------------------------------	
; Stack Usage
    OFFSET 0  ; to setup offset into stack
RKB_VARSIZE:
RKB_PR_A    DS.W    1
RKB_RA      DS.W    1

RKB_ROW1    EQU    $ef
RKB_ROW2    EQU    $df
RKB_ROW3    EQU    $bf
RKB_ROW4    EQU    $7f

readKeybrd: psha
    ;leas -RKB_VARSIZE,SP

    ldaa #RKB_ROW1
    staa PORTA                      ; PORTA = ROW1;
    cmpa PORTA                      ; if (PORTA == ROW1)
    bne RKB_IF_1_END
RKB_IF_1:                           ; {
    ldaa #RKB_ROW2
    staa PORTA                      ;     PORTA = ROW2;
    cmpa PORTA                      ;     if (PORTA == ROW2)
    bne RKB_IF_2_END
RKB_IF_2:                           ;     {
    ldaa #RKB_ROW3
    staa PORTA                      ;         PORTA = ROW3;
    cmpa PORTA                      ;         if (PORTA == ROW3)
    bne RKB_IF_3_END
RKB_IF_3:
    movb #RKB_ROW4,PORTA            ;             PORTA = ROW4;
RKB_IF_3_END:
RKB_IF_2_END:                       ;     }
RKB_IF_1_END:                       ; }
    ldab PORTA                      ; code = PORTA;
    
    ;leas RKB_VARSIZE,SP
    pula
    rts                             ; return code;

;-----------------------------------------------------------	
; Subroutine: ch <- translate
; Arguments:
;   code - keycode in accumulator B
; Local variable: 
;   code - ASCII Code in accumulator B
;   

; Description:
;   Translate the keycode in accumulator B and return it back
;-----------------------------------------------------------	
; Stack Usage
    OFFSET 0  ; to setup offset into stack
TRS_VARSIZE: 
TRS_PR_X    DS.W    1
TRS_PR_A    DS.B    1

translate: psha
    pshx
    ;leas -TRS_VARSIZE,SP
    
    ldaa #NUMKEYS
    ldx #keycodeToCharTable                       ; keycodeToCharTablePointer = keycodeToCharTable;
   
TRS_LOOP:                                         ; for (int i = 0; i < NUMKEYS; ++i)
TRS_IF:                                           ; {
    cmpb keycodeToCharTable_keycode,X             ;     if (keycodeToCharTablePointer->keycode == code)
    bne TRS_IF_FALSE
TRS_IF_TRUE:                                      ;     {
    ldab keycodeToCharTable_character,X           ;         return keycodeToCharTablePointer->character;
    bra TRS_LOOP_END
TRS_IF_FALSE:                                     ;     }
    leax keycodeToCharTable_structLength,X        ;     ++keycodeToCharTablePointer;
    dbne A,TRS_LOOP
TRS_IF_END:                                       ; }
    ldab #BADCODE                                 ; return BADCODE;
TRS_LOOP_END:
    
    ;leas TRS_VARSIZE,SP
    pulx
    pula
    rts

