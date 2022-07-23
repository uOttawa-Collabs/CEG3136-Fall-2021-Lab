*
*
*  HC12 i/o register locations (9s12dp256)
*

	ifndef REG9S12	; include only if not yet included

REG9S12	EQU	1	; for testing inclusion of this file
*
PORTA:	EQU	0  	; port a = address lines a8 - a15
PORTB:	EQU	1  	; port b = address lines a0 - a7
DDRA:	EQU	2  	; port a direction register
DDRB:	EQU	3  	; port a direction register

PORTE:	EQU	8  	; port e = mode,irqandcontrolsignals
DDRE:	EQU	9  	; port e direction register
PEAR:	EQU	$a 	; port e assignments
MODE:	EQU	$b 	; mode register
PUCR:	EQU	$c 	; port pull-up control register
RDRIV:	EQU	$d 	; port reduced drive control register
EBICTL:	EQU	$e 	; e stretch control

INITRM:	EQU	$10	; ram location register
INITRG:	EQU	$11	; register location register
INITEE:	EQU	$12	; eeprom location register
MISC:	EQU	$13	; miscellaneous mapping control
MTST0:	EQU	$14	; reserved
ITCR:	EQU	$15	; interrupt test control register
ITEST:	EQU	$16	; interrupt test register
MTST1:	EQU	$17	; reserved

PARTIDH:	EQU	$1a	; part id high
PARTIDL:	EQU	$1b	; part id low
MEMSIZ0:	EQU	$1c	; memory size
MEMSIZ1:	EQU	$1d	; memory size
INTCR:	EQU	$1e	; interrupt control register
HPRIO:	EQU	$1f	; high priority reg

BKPCT0:	EQU	$28	; break control register
BKPCT1:	EQU	$29	; break control register
BKP0X:	EQU	$2a	; break 0 index register
BKP0H:	EQU	$2b	; break 0 pointer high
BRP0L:	EQU	$2c	; break 0 pointer low
BKP1X:	EQU	$2d	; break 1 index register
BKP1H:	EQU	$2e	; break 1 pointer high
BRP1L:	EQU	$2f	; break 1 pointer low
PPAGE:	EQU	$30	; program page register

PORTK:	EQU	$32	; port k data
DDRK:	EQU	$33	; port k direction
SYNR:	EQU	$34	; synthesizer / multiplier register
REFDV:	EQU	$35	; reference divider register
CTFLG:	EQU	$36	; reserved
CRGFLG:	EQU	$37	; pll flags register
CRGINT:	EQU	$38	; pll interrupt register
CLKSEL:	EQU	$39	; clock select register
PLLCTL:	EQU	$3a	; pll control register
RTICTL:	EQU	$3b	; real time interrupt control
COPCTL:	EQU	$3c	; watchdog control
FORBYP:	EQU	$3d	; 
CTCTL:	EQU	$3e	; 
ARMCOP:	EQU	$3f	; cop reset register

TIOS:	EQU	$40	; timer input/output select
CFORC:	EQU	$41	; timer compare force
OC7M:	EQU	$42	; timer output compare 7 mask
OC7D:	EQU	$43	; timer output compare 7 data
TCNT:	EQU	$44	; timer counter register hi
*TCNT:	EQU	$45	; timer counter register lo
TSCR:	EQU	$46	; timer system control register
TTOV:	EQU	$47	; reserved
TCTL1:	EQU	$48	; timer control register 1
TCTL2:	EQU	$49	; timer control register 2
TCTL3:	EQU	$4a	; timer control register 3
TCTL4:	EQU	$4b	; timer control register 4
TMSK1:	EQU	$4c	; timer interrupt mask 1
TMSK2:	EQU	$4d	; timer interrupt mask 2
TFLG1:	EQU	$4e	; timer flags 1
TFLG2:	EQU	$4f	; timer flags 2
TC0:	EQU	$50	; timer capture/compare register 0
TC1:	EQU	$52	; timer capture/compare register 1
TC2:	EQU	$54	; timer capture/compare register 2
TC3:	EQU	$56	; timer capture/compare register 3
TC4:	EQU	$58	; timer capture/compare register 4
TC5:	EQU	$5a	; timer capture/compare register 5
TC6:	EQU	$5c	; timer capture/compare register 6
TC7:	EQU	$5e	; timer capture/compare register 7
PACTL:	EQU	$60	; pulse accumulator controls
PAFLG:	EQU	$61	; pulse accumulator flags
PACN3:	EQU	$62	; pulse accumulator counter 3
PACN2:	EQU	$63	; pulse accumulator counter 2
PACN1:	EQU	$64	; pulse accumulator counter 1
PACN0:	EQU	$65	; pulse accumulator counter 0
MCCTL:	EQU	$66	; modulus down conunter control
MCFLG:	EQU	$67	; down counter flags
ICPAR:	EQU	$68	; input pulse accumulator control
DLYCT:	EQU	$69	; delay count to down counter
ICOVW:	EQU	$6a	; input control overwrite register
ICSYS:	EQU	$6b	; input control system control

TIMTST:	EQU	$6d	; timer test register

PBCTL:	EQU	$70	; pulse accumulator b control
PBFLG:	EQU	$71	; pulse accumulator b flags
PA3H:	EQU	$72	; pulse accumulator holding register 3
PA2H:	EQU	$73	; pulse accumulator holding register 2
PA1H:	EQU	$74	; pulse accumulator holding register 1
PA0H:	EQU	$75	; pulse accumulator holding register 0
MCCNT:	EQU	$76	; modulus down counter register
*MCCNTL:	EQU	$77	; low byte
TCOH:	EQU	$78	; capture 0 holding register
TC1H:	EQU	$7a	; capture 1 holding register
TC2H:	EQU	$7c	; capture 2 holding register
TC3H:	EQU	$7e	; capture 3 holding register

ATD0CTL0:	EQU	$80	; adc control 0 (reserved)
ATD0CTL1:	EQU	$81	; adc control 1 (reserved)
ATD0CTL2:	EQU	$82	; adc control 2
ATD0CTL3:	EQU	$83	; adc control 3
ATD0CTL4:	EQU	$84	; adc control 4
ATD0CTL5:	EQU	$85	; adc control 5
ATD0STAT:	EQU	$86	; adc status register hi
*ATD0STAT	EQU	$87	; adc status register lo
ATD0TEST:	EQU	$88	; adc test (reserved)
*ATD0TEST	EQU	$89	; 

ATD0DIEN:	EQU	$8d	; 

PORTAD0:	EQU	$8f	; port adc = input only
ADR00H:	EQU	$90	; adc result 0 register
ADR01H:	EQU	$92	; adc result 1 register
ADR02H:	EQU	$94	; adc result 2 register
ADR03H:	EQU	$96	; adc result 3 register
ADR04H:	EQU	$98	; adc result 4 register
ADR05H:	EQU	$9a	; adc result 5 register
ADR06H:	EQU	$9c	; adc result 6 register
ADR07H:	EQU	$9e	; adc result 7 register

PWME:	EQU	$a0	; pwm enable
PWMPOL:	EQU	$a1	; pwm polarity
PWMCLK:	EQU	$a2	; pwm clock select register
PWMPRCLK:	EQU	$a3	; pwm prescale clock select register
PWMCAE:	EQU	$a4	; pwm center align select register
PWMCTL:	EQU	$a5	; pwm control register
PWMTST:	EQU	$a6	; reserved
PWMPRSC:	EQU	$a7	; reserved
PWMSCLA:	EQU	$a8	; pwm scale a
PWMSCLB:	EQU	$a9	; pwm scale b
PWMSCNTA:	EQU	$aa	; reserved
PWMSCNTB:	EQU	$ab	; reserved
PWMCNT0:	EQU	$ac	; pwm channel 0 counter
PWMCNT1:	EQU	$ad	; pwm channel 1 counter
PWMCNT2:	EQU	$ae	; pwm channel 2 counter
PWMCNT3:	EQU	$af	; pwm channel 3 counter
PWMCNT4:	EQU	$b0	; pwm channel 4 counter
PWMCNT5:	EQU	$b1	; pwm channel 5 counter
PWMCNT6:	EQU	$b2	; pwm channel 6 counter
PWMCNT7:	EQU	$b3	; pwm channel 7 counter
PWMPER0:	EQU	$b4	; pwm channel 0 period
PWMPER1:	EQU	$b5	; pwm channel 1 period
PWMPER2:	EQU	$b6	; pwm channel 2 period
PWMPER3:	EQU	$b7	; pwm channel 3 period
PWMPER4:	EQU	$b8	; pwm channel 4 period
PWMPER5:	EQU	$b9	; pwm channel 5 period
PWMPER6:	EQU	$ba	; pwm channel 6 period
PWMPER7:	EQU	$bb	; pwm channel 7 period
PWMDTY0:	EQU	$bc	; pwm channel 0 duty cycle
PWMDTY1:	EQU	$bd	; pwm channel 1 duty cycle
PWMDTY2:	EQU	$be	; pwm channel 2 duty cycle
PWMDTY3:	EQU	$bf	; pwm channel 3 duty cycle
PWMDTY4:	EQU	$c0	; pwm channel 0 duty cycle
PWMDTY5:	EQU	$c1	; pwm channel 1 duty cycle
PWMDTY6:	EQU	$c2	; pwm channel 2 duty cycle
PWMDTY7:	EQU	$c3	; pwm channel 3 duty cycle
PWMSDN:	EQU	$c4	; pwm shutdown register

SC0BDH:	EQU	$c8	; sci 0 baud reg hi byte
SC0BDL:	EQU	$c9	; sci 0 baud reg lo byte
SC0CR1:	EQU	$ca	; sci 0 control1 reg
SC0CR2:	EQU	$cb	; sci 0 control2 reg
SC0SR1:	EQU	$cc	; sci 0 status reg 1
SC0SR2:	EQU	$cd	; sci 0 status reg 2
SC0DRH:	EQU	$ce	; sci 0 data reg hi
SC0DRL:	EQU	$cf	; sci 0 data reg lo
SC1BDH:	EQU	$d0	; sci 1 baud reg hi byte
SC1BDL:	EQU	$d1	; sci 1 baud reg lo byte
SC1CR1:	EQU	$d2	; sci 1 control1 reg
SC1CR2:	EQU	$d3	; sci 1 control2 reg
SC1SR1:	EQU	$d4	; sci 1 status reg 1
SC1SR2:	EQU	$d5	; sci 1 status reg 2
SC1DRH:	EQU	$d6	; sci 1 data reg hi
SC1DRL:	EQU	$d7	; sci 1 data reg lo
SPI0CR1:	EQU	$d8	; spi 0 control1 reg
SPI0CR2:	EQU	$d9	; spi 0 control2 reg
SPI0BR:	EQU	$da	; spi 0 baud reg
SPI0SR:	EQU	$db	; spi 0 status reg hi

SP0DR:	EQU	$dd	; spi 0 data reg

IBAD:	EQU	$e0	; i2c bus address register
IBFD:	EQU	$e1	; i2c bus frequency divider
IBCR:	EQU	$e2	; i2c bus control register
IBSR:	EQU	$e3	; i2c bus status register
IBDR:	EQU	$e4	; i2c bus message data register

DLCBCR1:	EQU	$e8	; bdlc control regsiter 1
DLCBSVR:	EQU	$e9	; bdlc state vector register
DLCBCR2:	EQU	$ea	; bdlc control register 2
DLCBDR:	EQU	$eb	; bdlc data register
DLCBARD:	EQU	$ec	; bdlc analog delay register
DLCBRSR:	EQU	$ed	; bdlc rate select register
DLCSCR:	EQU	$ee	; bdlc control register
DLCBSTAT:	EQU	$ef	; bdlc status register
SPI1CR1:	EQU	$f0	; spi 1 control1 reg
SPI1CR2:	EQU	$f1	; spi 1 control2 reg
SPI1BR:	EQU	$f2	; spi 1 baud reg
SPI1SR:	EQU	$f3	; spi 1 status reg hi

SP1DR:	EQU	$f5	; spi 1 data reg

SPI2CR1:	EQU	$f8	; spi 2 control1 reg
SPI2CR2:	EQU	$f9	; spi 2 control2 reg
SPI2BR:	EQU	$fa	; spi 2 baud reg
SPI2SR:	EQU	$fb	; spi 2 status reg hi

SP2DR:	EQU	$fd	; spi 2 data reg

FCLKDIV:	EQU	$100	; flash clock divider
FSEC:	EQU	$101	; flash security register

FCNFG:	EQU	$103	; flash configuration register
FPROT:	EQU	$104	; flash protection register
FSTAT:	EQU	$105	; flash status register
FCMD:	EQU	$106	; flash command register

ECLKDIV:	EQU	$110	; eeprom clock divider

ECNFG:	EQU	$113	; eeprom configuration register
EPROT:	EQU	$114	; eeprom protection register
ESTAT:	EQU	$115	; eeprom status register
ECMD:	EQU	$116	; eeprom command register

ATD1CTL0:	EQU	$120	; adc1 control 0 (reserved)
ATD1CTL1:	EQU	$121	; adc1 control 1 (reserved)
ATD1CTL2:	EQU	$122	; adc1 control 2
ATD1CTL3:	EQU	$123	; adc1 control 3
ATD1CTL4:	EQU	$124	; adc1 control 4
ATD1CTL5:	EQU	$125	; adc1 control 5
ATD1STAT:	EQU	$126	; adc1 status register hi
*ATD1STAT	EQU	$127	; adc1 status register lo
ATD1TEST:	EQU	$128	; adc1 test (reserved)
*ATD1TEST	EQU	$129	; 

ATD1DIEN:	EQU	$12d	; adc1 input enable register

PORTAD1:	EQU	$12f	; port adc1 = input only
ADR10H:	EQU	$130	; adc1 result 0 register
ADR11H:	EQU	$132	; adc1 result 1 register
ADR12H:	EQU	$134	; adc1 result 2 register
ADR13H:	EQU	$136	; adc1 result 3 register
ADR14H:	EQU	$138	; adc1 result 4 register
ADR15H:	EQU	$13a	; adc1 result 5 register
ADR16H:	EQU	$13c	; adc1 result 6 register
ADR17H:	EQU	$13e	; adc1 result 7 register
CAN0CTL0:	EQU	$140	; can0 control register 0
CAN0CTL1:	EQU	$141	; can0 control register 1
CAN0BTR0:	EQU	$142	; can0 bus timing register 0
CAN0BTR1:	EQU	$143	; can0 bus timing register 1
CAN0RFLG:	EQU	$144	; can0 receiver flags
CAN0RIER:	EQU	$145	; can0 receiver interrupt enables
CAN0TFLG:	EQU	$146	; can0 transmit flags
CAN0TIER:	EQU	$147	; can0 transmit interrupt enables
CAN0TARQ:	EQU	$148	; can0 transmit message abort control
CAN0TAAK:	EQU	$149	; can0 transmit message abort status
CAN0TBEL:	EQU	$14a	; can0 transmit buffer select
CAN0IDAC:	EQU	$14b	; can0 identfier acceptance control

CAN0RERR:	EQU	$14e	; can0 receive error counter
CAN0TERR:	EQU	$14f	; can0 transmit error counter
CAN0IDA0:	EQU	$150	; can0 identifier acceptance register 0
CAN0IDA1:	EQU	$151	; can0 identifier acceptance register 1
CAN0IDA2:	EQU	$152	; can0 identifier acceptance register 2
CAN0IDA3:	EQU	$153	; can0 identifier acceptance register 3
CAN0IDM0:	EQU	$154	; can0 identifier mask register 0
CAN0IDM1:	EQU	$155	; can0 identifier mask register 1
CAN0IDM2:	EQU	$156	; can0 identifier mask register 2
CAN0IDM3:	EQU	$157	; can0 identifier mask register 3
CAN0IDA4:	EQU	$158	; can0 identifier acceptance register 4
CAN0IDA5:	EQU	$159	; can0 identifier acceptance register 5
CAN0IDA6:	EQU	$15a	; can0 identifier acceptance register 6
CAN0IDA7:	EQU	$15b	; can0 identifier acceptance register 7
CAN0IDM4:	EQU	$15c	; can0 identifier mask register 4
CAN0IDM5:	EQU	$15d	; can0 identifier mask register 5
CAN0IDM6:	EQU	$15e	; can0 identifier mask register 6
CAN0IDM7:	EQU	$15f	; can0 identifier mask register 7
CAN0RXFG:	EQU	$160	; can0 rx foreground buffer thru +$16f
CAN0TXFG:	EQU	$170	; can0 tx foreground buffer thru +$17f

CAN1CTL0:	EQU	$180	; can1 control register 0
CAN1CTL1:	EQU	$181	; can1 control register 1
CAN1BTR0:	EQU	$182	; can1 bus timing register 0
CAN1BTR1:	EQU	$183	; can1 bus timing register 1
CAN1RFLG:	EQU	$184	; can1 receiver flags
CAN1RIER:	EQU	$185	; can1 receiver interrupt enables
CAN1TFLG:	EQU	$186	; can1 transmit flags
CAN1TIER:	EQU	$187	; can1 transmit interrupt enables
CAN1TARQ:	EQU	$188	; can1 transmit message abort control
CAN1TAAK:	EQU	$189	; can1 transmit message abort status
CAN1TBEL:	EQU	$18a	; can1 transmit buffer select
CAN1IDAC:	EQU	$18b	; can1 identfier acceptance control

CAN1RERR:	EQU	$18e	; can1 receive error counter
CAN1TERR:	EQU	$18f	; can1 transmit error counter
CAN1IDA0:	EQU	$190	; can1 identifier acceptance register 0
CAN1IDA1:	EQU	$191	; can1 identifier acceptance register 1
CAN1IDA2:	EQU	$192	; can1 identifier acceptance register 2
CAN1IDA3:	EQU	$193	; can1 identifier acceptance register 3
CAN1IDM0:	EQU	$194	; can1 identifier mask register 0
CAN1IDM1:	EQU	$195	; can1 identifier mask register 1
CAN1IDM2:	EQU	$196	; can1 identifier mask register 2
CAN1IDM3:	EQU	$197	; can1 identifier mask register 3
CAN1IDA4:	EQU	$198	; can1 identifier acceptance register 4
CAN1IDA5:	EQU	$199	; can1 identifier acceptance register 5
CAN1IDA6:	EQU	$19a	; can1 identifier acceptance register 6
CAN1IDA7:	EQU	$19b	; can1 identifier acceptance register 7
CAN1IDM4:	EQU	$19c	; can1 identifier mask register 4
CAN1IDM5:	EQU	$19d	; can1 identifier mask register 5
CAN1IDM6:	EQU	$19e	; can1 identifier mask register 6
CAN1IDM7:	EQU	$19f	; can1 identifier mask register 7
CAN1RXFG:	EQU	$1a0	; can1 rx foreground buffer thru +$1af
CAN1TXFG:	EQU	$1b0	; can1 tx foreground buffer thru +$1bf

CAN2CTL0:	EQU	$1c0	; can2 control register 0
CAN2CTL1:	EQU	$1c1	; can2 control register 1
CAN2BTR0:	EQU	$1c2	; can2 bus timing register 0
CAN2BTR1:	EQU	$1c3	; can2 bus timing register 1
CAN2RFLG:	EQU	$1c4	; can2 receiver flags
CAN2RIER:	EQU	$1c5	; can2 receiver interrupt enables
CAN2TFLG:	EQU	$1c6	; can2 transmit flags
CAN2TIER:	EQU	$1c7	; can2 transmit interrupt enables
CAN2TARQ:	EQU	$1c8	; can2 transmit message abort control
CAN2TAAK:	EQU	$1c9	; can2 transmit message abort status
CAN2TBEL:	EQU	$1ca	; can2 transmit buffer select
CAN2IDAC:	EQU	$1cb	; can2 identfier acceptance control

CAN2RERR:	EQU	$1ce	; can2 receive error counter
CAN2TERR:	EQU	$1cf	; can2 transmit error counter
CAN2IDA0:	EQU	$1d0	; can2 identifier acceptance register 0
CAN2IDA1:	EQU	$1d1	; can2 identifier acceptance register 1
CAN2IDA2:	EQU	$1d2	; can2 identifier acceptance register 2
CAN2IDA3:	EQU	$1d3	; can2 identifier acceptance register 3
CAN2IDM0:	EQU	$1d4	; can2 identifier mask register 0
CAN2IDM1:	EQU	$1d5	; can2 identifier mask register 1
CAN2IDM2:	EQU	$1d6	; can2 identifier mask register 2
CAN2IDM3:	EQU	$1d7	; can2 identifier mask register 3
CAN2IDA4:	EQU	$1d8	; can2 identifier acceptance register 4
CAN2IDA5:	EQU	$1d9	; can2 identifier acceptance register 5
CAN2IDA6:	EQU	$1da	; can2 identifier acceptance register 6
CAN2IDA7:	EQU	$1db	; can2 identifier acceptance register 7
CAN2IDM4:	EQU	$1dc	; can2 identifier mask register 4
CAN2IDM5:	EQU	$1dd	; can2 identifier mask register 5
CAN2IDM6:	EQU	$1de	; can2 identifier mask register 6
CAN2IDM7:	EQU	$1df	; can2 identifier mask register 7
CAN2RXFG:	EQU	$1e0	; can2 rx foreground buffer thru +$1ef
CAN2TXFG:	EQU	$1f0	; can2 tx foreground buffer thru +$1ff

CAN3CTL0:	EQU	$200	; can3 control register 0
CAN3CTL1:	EQU	$201	; can3 control register 1
CAN3BTR0:	EQU	$202	; can3 bus timing register 0
CAN3BTR1:	EQU	$203	; can3 bus timing register 1
CAN3RFLG:	EQU	$204	; can3 receiver flags
CAN3RIER:	EQU	$205	; can3 receiver interrupt enables
CAN3TFLG:	EQU	$206	; can3 transmit flags
CAN3TIER:	EQU	$207	; can3 transmit interrupt enables
CAN3TARQ:	EQU	$208	; can3 transmit message abort control
CAN3TAAK:	EQU	$209	; can3 transmit message abort status
CAN3TBEL:	EQU	$20a	; can3 transmit buffer select
CAN3IDAC:	EQU	$20b	; can3 identfier acceptance control

CAN3RERR:	EQU	$20e	; can3 receive error counter
CAN3TERR:	EQU	$20f	; can3 transmit error counter
CAN3IDA0:	EQU	$210	; can3 identifier acceptance register 0
CAN3IDA1:	EQU	$211	; can3 identifier acceptance register 1
CAN3IDA2:	EQU	$212	; can3 identifier acceptance register 2
CAN3IDA3:	EQU	$213	; can3 identifier acceptance register 3
CAN3IDM0:	EQU	$214	; can3 identifier mask register 0
CAN3IDM1:	EQU	$215	; can3 identifier mask register 1
CAN3IDM2:	EQU	$216	; can3 identifier mask register 2
CAN3IDM3:	EQU	$217	; can3 identifier mask register 3
CAN3IDA4:	EQU	$218	; can3 identifier acceptance register 4
CAN3IDA5:	EQU	$219	; can3 identifier acceptance register 5
CAN3IDA6:	EQU	$21a	; can3 identifier acceptance register 6
CAN3IDA7:	EQU	$21b	; can3 identifier acceptance register 7
CAN3IDM4:	EQU	$21c	; can3 identifier mask register 4
CAN3IDM5:	EQU	$21d	; can3 identifier mask register 5
CAN3IDM6:	EQU	$21e	; can3 identifier mask register 6
CAN3IDM7:	EQU	$21f	; can3 identifier mask register 7
CAN3RXFG:	EQU	$220	; can3 rx foreground buffer thru +$22f
CAN3TXFG:	EQU	$230	; can3 tx foreground buffer thru +$23f

PTT:	EQU	$240	; portt data register
PTIT:	EQU	$241	; portt input register
DDRT:	EQU	$242	; portt direction register
RDRT:	EQU	$243	; portt reduced drive register
PERT:	EQU	$244	; portt pull device enable
PPST:	EQU	$245	; portt pull polarity select

PTS:	EQU	$248	; ports data register
PTIS:	EQU	$249	; ports input register
DDRS:	EQU	$24a	; ports direction register
RDRS:	EQU	$24b	; ports reduced drive register
PERS:	EQU	$24c	; ports pull device enable
PPSS:	EQU	$24d	; ports pull polarity select
WOMS:	EQU	$24e	; ports wired or mode register

PTM:	EQU	$250	; portm data register
PTIM:	EQU	$251	; portm input register
DDRM:	EQU	$252	; portm direction register
RDRM:	EQU	$253	; portm reduced drive register
PERM:	EQU	$254	; portm pull device enable
PPSM:	EQU	$255	; portm pull polarity select
WOMM:	EQU	$256	; portm wired or mode register
MODRR:	EQU	$257	; portm module routing register
PTP:	EQU	$258	; portp data register
PTIP:	EQU	$259	; portp input register
DDRP:	EQU	$25a	; portp direction register
RDRP:	EQU	$25b	; portp reduced drive register
PERP:	EQU	$25c	; portp pull device enable
PPSP:	EQU	$25d	; portp pull polarity select
PIEP:	EQU	$25e	; portp interrupt enable register
PIFP:	EQU	$25f	; portp interrupt flag register
PTH:	EQU	$260	; porth data register
PTIH:	EQU	$261	; porth input register
DDRH:	EQU	$262	; porth direction register
RDRH:	EQU	$263	; porth reduced drive register
PERH:	EQU	$264	; porth pull device enable
PPSH:	EQU	$265	; porth pull polarity select
PIEH:	EQU	$266	; porth interrupt enable register
PIFH:	EQU	$267	; porth interrupt flag register
PTJ:	EQU	$268	; portp data register
PTIJ:	EQU	$269	; portp input register
DDRJ:	EQU	$26a	; portp direction register
RDRJ:	EQU	$26b	; portp reduced drive register
PERJ:	EQU	$26c	; portp pull device enable
PPSJ:	EQU	$26d	; portp pull polarity select
PIEJ:	EQU	$26e	; portp interrupt enable register
PIFJ:	EQU	$26f	; portp interrupt flag register

CAN4CTL0:	EQU	$280	; can4 control register 0
CAN4CTL1:	EQU	$281	; can4 control register 1
CAN4BTR0:	EQU	$282	; can4 bus timing register 0
CAN4BTR1:	EQU	$283	; can4 bus timing register 1
CAN4RFLG:	EQU	$284	; can4 receiver flags
CAN4RIER:	EQU	$285	; can4 receiver interrupt enables
CAN4TFLG:	EQU	$286	; can4 transmit flags
CAN4TIER:	EQU	$287	; can4 transmit interrupt enables
CAN4TARQ:	EQU	$288	; can4 transmit message abort control
CAN4TAAK:	EQU	$289	; can4 transmit message abort status
CAN4TBEL:	EQU	$28a	; can4 transmit buffer select
CAN4IDAC:	EQU	$28b	; can4 identfier acceptance control

CAN4RERR:	EQU	$28e	; can4 receive error counter
CAN4TERR:	EQU	$28f	; can4 transmit error counter
CAN4IDA0:	EQU	$290	; can4 identifier acceptance register 0
CAN4IDA1:	EQU	$291	; can4 identifier acceptance register 1
CAN4IDA2:	EQU	$292	; can4 identifier acceptance register 2
CAN4IDA3:	EQU	$293	; can4 identifier acceptance register 3
CAN4IDM0:	EQU	$294	; can4 identifier mask register 0
CAN4IDM1:	EQU	$295	; can4 identifier mask register 1
CAN4IDM2:	EQU	$296	; can4 identifier mask register 2
CAN4IDM3:	EQU	$297	; can4 identifier mask register 3
CAN4IDA4:	EQU	$298	; can4 identifier acceptance register 4
CAN4IDA5:	EQU	$299	; can4 identifier acceptance register 5
CAN4IDA6:	EQU	$29a	; can4 identifier acceptance register 6
CAN4IDA7:	EQU	$29b	; can4 identifier acceptance register 7
CAN4IDM4:	EQU	$29c	; can4 identifier mask register 4
CAN4IDM5:	EQU	$29d	; can4 identifier mask register 5
CAN4IDM6:	EQU	$29e	; can4 identifier mask register 6
CAN4IDM7:	EQU	$29f	; can4 identifier mask register 7
CAN4RXFG:	EQU	$2a0	; can4 rx foreground buffer thru +$2af
CAN4TXFG:	EQU	$2b0	; can4 tx foreground buffer thru +$2bf

* end registers

	endif   ; end of conditional assembly
