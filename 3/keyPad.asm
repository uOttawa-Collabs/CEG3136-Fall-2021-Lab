;----------------------------------------------------------------------
; File: Keypad.asm
; Author: Gilbert Arbez

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


; codes for scanning keyboard

ROW1 EQU %11101111
ROW2 EQU %11011111
ROW3 EQU %10111111
ROW4 EQU %01111111

;-----Conversion table
NUMKEYS	EQU	16	; Number of keys on the keypad
BADCODE 	EQU	$FF 	; returned of translation is unsuccessful
NOKEY		EQU 	$00   ; No key pressed during poll period
POLLCOUNT	EQU	1     ; Number of loops to create 1 ms poll time

 SWITCH globalConst  ; Constant data

; defnitions for structure cnvTbl_struct
 OFFSET 0
cnvTbl_code ds.b 1
cnvTbl_ascii  ds.b 1
cnvTbl_struct_len EQU *

; Conversion Table
cnvTbl  dc.b %11101110,'1'
	dc.b %11101101,'2'
	dc.b %11101011,'3'
	dc.b %11100111,'a'
	dc.b %11011110,'4'
	dc.b %11011101,'5'
	dc.b %11011011,'6'
	dc.b %11010111,'b'
	dc.b %10111110,'7'
	dc.b %10111101,'8'
	dc.b %10111011,'9'
	dc.b %10110111,'c'
	dc.b %01111110,'*'
	dc.b %01111101,'0'
	dc.b %01111011,'#'
	dc.b %01110111,'d'

 SWITCH code_section  ; place in code section
;-----------------------------------------------------------	
; Subroutine: initKeyPad
;
; Description: 
; 	Initiliases PORT A
; 	Bits 0-3 as inputs
; 	Bits 4-7 as ouputs
; 	Enable pullups 
;-----------------------------------------------------------	
initKeyPad:
	movb #%11110000,DDRA ; Data Direction Register
	bset PUCR,%00000001 ; Enable pullups
	rts

;-----------------------------------------------------------    
; Subroutine: ch <- pollReadKey
; Parameters: none
; Local variable: code - in accumulator B
;    ch - in accumulator B - char returned
;    count - index reg X - count to create
;                          10 ms delay
; Returns
;       ch: NOKEY when no key pressed,
;       otherwise, ASCII Code in accumulator B

; Description:
;  Loops for a period of 2ms, checking to see if
;  key is pressed. Calls readKey to read key if keypress 
;  detected (and debounced) on Port A.
;  When no key pressed, loop takes 11 cycles.
;       1 loop takes 11 X 41 2/3 nano-seconds = 458 1/3 ns
;       1 ms delay requires 2182 loops - set to POLLCOUNT
;-----------------------------------------------------------
; Stack Usage
	OFFSET 0  ; to setup offset into stack
PRK_CH         DS.B 1 ; return value, ASCII code
PRK_VARSIZE
PRK_PR_X	      DS.W 1 ; preserve X
PRK_RA         DS.W 1 ; return address 

pollReadKey: pshx   ; preserve register
   leas -PRK_VARSIZE,SP
   movb #NOKEY,PRK_CH,SP ; char ch = NOKEY;
   ldx #POLLCOUNT   ; int count = POLLCOUNT;
   movb #0x0f,PORTA ; PORTA = 0x0f; //set outputs to low
prk_loop:           ;           do {
prk_if1:
   ldb PORTA        ; 3 cycles     if(PORTA != 0x0f)
   cmpb #$0f        ; 1 cycle      {
   beq prk_endif1   ; 3 cycles
   ldd #1           ;                 delayms(1)
   jsr delayms     ;              
prk_if2:            ;             
   ldb PORTA        ;                 if(PORTA != 0x0f)
   cmpb #$0f        ;                 {
   beq prk_endif2
   jsr readKey      ;                     ch = readKey();
   stab PRK_CH,SP   ;
   bra prk_endloop  ;                     break;
prk_endif2:         ;                 }
prk_endif1:         ;              }
   dex              ; 1 cycle      count--;
   bne prk_loop     ; 3 cycles  } while(count!=0);
prk_endloop: 
   ldab PRK_CH,SP   ; return(ch);
   ; Restore stack and registers
   leas PRK_VARSIZE,SP
   pulx
   rts

;-----------------------------------------------------------	
; Subroutine: ch <- readKey
; Arguments: none
; Local variable: code - on stack
;                 ch - accumulator B
; Returns
;	ch - ASCII Code in accumulator B

; Description:
;  Main subroutine that reads a code from the
;  keyboard using the subroutine readKeyCode.  The
;  code is then translated with the subroutine
;  translate to get the corresponding ASCII code.
;-----------------------------------------------------------	
; Stack Usage
	OFFSET 0  ; to setup offset into stack
RDK_CODE       DS.B 1 ; code variable
RDK_VARSIZE
	      DS.B 1 ; Preseserve A
RDK_RA         DS.W 1 ; return address

readKey:psha		; byte code;
		; byte ch;	
    leas -RDK_VARSIZE,SP 
RDK_DO                     ; do
		           ; {
    movb $0F,PORTA         ;    PORTA = 0x0F;  // set all output pins to 0
RDK_LP1 ldab PORTA         ;    while(PORTA==0x0F) /* wait */;
    cmpb #$0F
    beq RDK_LP1
    movb PORTA,RDK_CODE,SP ;    code = PORTA
    ldd #10
    jsr delayms	           ;    delayms(10);
    ldab PORTA	           ; } while(code != PORTA);  // start again if PORTA has changed
    cmpb RDK_CODE,SP
    bne RDK_DO
    jsr readKeyCode        ; code = readKeyCode();  // get the keycode
    stab RDK_CODE,SP
    movb #$0F,PORTA        ; PORTA = 0x0F;  // set all output pins to 0
RDK_LP2 ldab PORTA         ; while(PORTA!=0F)  /* wait */;
    cmpb #$0F
    bne RDK_LP2
    ldd #10
    jsr delayms            ; delayms(10);  // Debouncing release of the key
    ldab RDK_CODE,SP
    jsr translate          ; ch = translate(code);
    leas RDK_VARSIZE,SP
    pula
    rts		           ;  return(ch); 

;-----------------------------------------------------------	
; Subroutine: key <- readKeyCode
; Arguments: none
; Local variables:  key: Accumulator B
; Returns: key - in Accumulator B - code corresponding to key pressed

; Description: Assume key is pressed. Set 0 on each output pin
;              to find row and hence code for the key.
;-----------------------------------------------------------	
; Stack Usage: none

readKeyCode: 
         movb #ROW1,PORTA  ; PORTA = ROW1;
RKY_IF1  ldab PORTA        ; if(PORTA == ROW1) // input pin is 0 if key in row 1
         cmpb #ROW1
         bne RKY_ENDIF1    ; {
         movb #ROW2,PORTA  ;   PORTA = ROW2
RKY_IF2  ldab PORTA        ;   if(PORTA == ROW2)
         cmpb #ROW2
         bne RKY_ENDIF2    ;   {
         movb #ROW3,PORTA  ;      PORTA = ROW3;
RKY_IF3  ldab PORTA        ;      if(PORTA == ROW3)
         cmpb #ROW3
         bne RKY_ENDIF3
         movb #ROW4,PORTA  ;          PORTA = ROW4;
RKY_ENDIF3                 ;         
RKY_ENDIF2                 ;   }
RKY_ENDIF1                 ; }
         ldab PORTA        ; key = PORTA;
         rts               ; return(key);
	      
;-----------------------------------------------------------	
; Subroutine:  ch <- translate(code)
; Arguments
;	code - in Acc B - code read from keypad port
; Returns
;	ch - saved on stack but returned in Acc B - ASCII code
; Local Variables
;    	ptr - in register X - pointer to the table
;	count - counter for loop in accumulator A
; Description:
;   Translates the code by using the conversion table
;   searching for the code.  If not found, then BADCODE
;   is returned.
;-----------------------------------------------------------	
; Stack Usage:
   OFFSET 0
TR_CH DS.B 1  ; for ch 
TR_PR_A DS.B 1 ; preserved regiters A
TR_PR_X DS.B 1 ; preserved regiters X
TR_RA DS.W 1 ; return address

translate: psha
	pshx	; preserve registers
	leas -1,SP 		    ; byte chascii;
	ldx #cnvTbl		    ; ptr = cnvTbl;
	clra			    ; ix = 0;
	movb #BADCODE,TR_CH,SP ; ch = BADCODE;

TR_loop 			    ; do {

	; IF code = [ptr]
	cmpb cnvTbl_code,X  	    ;     if(code == ptr->code)
	bne TR_endif
				    ;     {
	movb cnvTbl_ascii,X,TR_CH,SP ;        ch <- [ptr+1]
	bra TR_endwh  		    ;         break;
TR_endif  			    ;     }
				    ;     else {	
	leax cnvTbl_struct_len,X    ;           ptr++;
	inca ; increment count      ;           ix++;
                                    ;     }	
	cmpa #NUMKEYS               ;} WHILE count < NUMKEYS
	blo TR_LOOP	
tr_endwh ; ENDWHILE

	pulb ; move ch to Acc B
	; restore registres
	pulx
	pula
	rts


