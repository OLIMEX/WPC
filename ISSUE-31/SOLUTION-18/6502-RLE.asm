; 
; Since the WPC did not realy specify what data to be encoded,
; I just picked something for easy handling. So this is 100%
; 6502 Assembly, but no real target machine. Encoder/Decoder
; are invoked with 4 parameters defining source address and
; and destination address/length (no, wo don't like buffer
; overruns).
;
; Unencoded data is seen as a series of pixel data, where every
; input byte represents one pixel with a possible value of 0..F
;
; Encoding is done by crating (8 bit) bytes with the lower 4 bits
; representing a colour, while the upper 4 Bit contain a repeat
; counter (run length) up to 17.
;
; Not beautiful, but working
;
; (c) H.Franke - vcfe.org
;

start:
  jsr Logo     ; Create Some Picture Data


; Call Encoder(Start,Length,Dest,Length) Parameterblock at $0008..F
; Put Start Address ($0200) for Source/Image in $0008/0009
  lda #$00
  sta $08
  lda #$02
  sta $09
; Put Destination Address ($1200) for Encoded Data in $000C/000D
  lda #$00
  sta $0C
  lda #$12
  sta $0D
; Put Source Length ($0400) in $000A/000B
  lda #$00
  sta $0A
  lda #$04
  sta $0B
; Put Destination Length ($0400) in $000E/000F
  lda #$00
  sta $0E
  lda #$04
  sta $0F

  jsr Comp

; Call Decoder(Start,Length,Dest,Length) Parameterblock at $0008..F
; Put Start Address ($1200) for Encoded Data in $0008/0009
  lda #$00
  sta $08
  lda #$12
  sta $09
; Put Destination Address ($0200) for Encoded Data in $000C/000D
  lda #$00
  sta $0C
  lda #$02
  sta $0D
; Copy Source Length from Encoding Call to $000A/000B
  lda $0E
  sta $0A
  lda $0F
  sta $0B
; Put Destination Length ($0400) in $000E/000F
  lda #$00
  sta $0E
  lda #$04
  sta $0F

  jsr DeComp


  RTS

Comp:
; Parameters
; $0008/0009 IC  Source Address (Data)
; $000A/000B IC  Source Length
; $000C/000D IC  Destination Address (RLE Encoded Data)
; $000E/000F IO  Destination Length
;
; Return:
; Carry set if successful
; Resulting Length in $000A/000B

  LDX #$00     ; Clear
  LDY #$00
cget:

  LDA $0A      ; Source Length Zero?
  BNE cl0
  LDA $0B
  BEQ cdone
cl0:

  LDA ($08),Y
cnext:
  INC $08      ; Increment Source Address
  BNE cl1
  INC $09
cl1:
  LDY $0A      ; Decrement Source Length
  BNE cl2
  DEC $0B
cl2:
  DEC $0A
  LDY #$00     ; Clear Y again

  CMP ($08),Y  ; Same Data Item?
  BNE cmake    ; No -> Make RLE-Item
  CPX #$0F     ; Already 17 Repetions?
  BEQ cl3      ; yes -> Store Intermediate RLE-Item
  INX          ; Increment Data Count
  JMP cnext
cl3:
  ORA #$F0     ; No Need to Calc
  BMI cstore
cmake:
  STA ($0C),Y
  TXA          ; Load Counter
  clc
  ROL          ; Move Up
  ROL
  ROL
  ROL
  ORA ($0C),Y
cstore:
  STA ($0C),Y
  INC $0C      ; Increment Destination Address
  BNE cl4
  INC $0D
cl4:
  LDX #$00     ; Reset Data Count
  JMP cget     ; continue

cdone:
  SEC
  rts

DeComp:
; Parameters
; $0008/0009 IC  Source Address (RLE Encoded Data)
; $000A/000B IC  Source Length
; $000C/000D IC  Destination Address (Data)
; $000E/000F IO  Destination Length
;
; Return:
; Carry set if successful
; Resulting Length in $000A/000B

  LDY #$00     ; Clear
  LDA $0A      ; Source Length Zero?
  BNE dl0
  LDA $0B
  BEQ ddone
dl0:

dnext:
  LDA ($08),Y
  TAY
  LSR
  LSR
  LSR
  LSR
  TAX
  INX
  TYA
  AND #$0F
  LDY #$00
dl1:
  STA ($0C),Y
  INC $0C
  BNE dl11
  INC $0D
dl11:
  DEX
  BNE dl1

  INC $08      ; Increment Source Address
  BNE dl2
  INC $09
dl2:
  LDA $0A      ; Decrement Source Length
  BNE dl3
  DEC $0B
dl3:
  DEC $0A      ; Source Length Zero?
  BNE dnext
  LDA $0B
  BNE dnext

ddone:
  SEC
  RTS

Logo:
; Prepare Image Data
; Well Known Logo
; $00..$03 Used as Scratch
  LDA #<logo
  STA $0
  LDA #>logo
  STA $1

  LDA #$00
  STA $2
  LDA #$02
  STA $3

  LDY #$0
ll1:
  LDA ($0),Y
  BMI ldone
  STA ($2),Y
  INC $00
  BNE ll2
  INC $01
ll2:
  INC $02
  BNE ll1
  INC $03
  jmp ll1
ldone:
  rts

logo:
 dcb 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,1,1,1,1,1,1,1,1,6,6,6
 dcb 6,6,6,6,1,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,1,1,1,1,1,6,6,6,6,6,6
 dcb 6,6,6,6,6,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,1,1,1,6,6,6,6,6,6,6,6
 dcb 6,6,6,6,6,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,1,1,6,6,6,6,6,6,6,6,6
 dcb 6,6,6,6,6,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,1,6,6,6,6,6,6,6,6,6,6
 dcb 6,6,6,6,6,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,6,6,6,6,6,6,6,6,6,6,6
 dcb 6,6,6,6,6,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,1,6,6,6,6,6,6,6,6,6,6,6,6
 dcb 6,6,6,6,6,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,6,6,6,6,6,6,6,6,6,6,6,6,1
 dcb 1,1,1,6,6,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,6,6,6,6,6,6,6,6,6,6,1,1,1
 dcb 1,1,1,1,1,6,6,6,6,6,6,6,6,6,6,6
 dcb 1,1,6,6,6,6,6,6,6,6,6,1,1,1,1,1
 dcb 1,1,1,1,1,6,6,6,6,6,6,6,6,6,6,1
 dcb 1,1,6,6,6,6,6,6,6,6,1,1,1,1,1,1
 dcb 1,1,1,1,1,6,6,6,6,6,6,6,6,6,1,1
 dcb 1,1,6,6,6,6,6,6,6,6,1,1,1,1,1,1
 dcb 1,1,1,1,1,6,6,6,6,6,6,6,6,1,1,1
 dcb 1,6,6,6,6,6,6,6,6,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,6,6,6,6,6,6,6,1,1,1,1
 dcb 1,6,6,6,6,6,6,6,6,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,6,6,6,6,6,6,1,1,1,1,1
 dcb 1,6,6,6,6,6,6,6,6,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,6,6,6,6,6,1,1,1,1,1,1
 dcb 1,6,6,6,6,6,6,6,6,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1
 dcb 1,6,6,6,6,6,6,6,6,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,2,2,2,2,2,2,1,1,1,1,1
 dcb 1,6,6,6,6,6,6,6,6,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,2,2,2,2,2,2,2,1,1,1,1
 dcb 1,6,6,6,6,6,6,6,6,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,2,2,2,2,2,2,2,2,1,1,1
 dcb 1,1,6,6,6,6,6,6,6,6,1,1,1,1,1,1
 dcb 1,1,1,1,1,2,2,2,2,2,2,2,2,2,1,1
 dcb 1,1,6,6,6,6,6,6,6,6,6,1,1,1,1,1
 dcb 1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,1
 dcb 1,1,1,6,6,6,6,6,6,6,6,6,1,1,1,1
 dcb 1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2
 dcb 1,1,1,6,6,6,6,6,6,6,6,6,6,1,1,1
 dcb 1,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,1,6,6,6,6,6,6,6,6,6,6,6,6
 dcb 6,6,6,6,6,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,1,6,6,6,6,6,6,6,6,6,6,6,6
 dcb 6,6,6,6,6,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,6,6,6,6,6,6,6,6,6,6,6
 dcb 6,6,6,6,6,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,1,6,6,6,6,6,6,6,6,6,6
 dcb 6,6,6,6,6,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,1,1,1,6,6,6,6,6,6,6,6
 dcb 6,6,6,6,6,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,1,1,1,1,6,6,6,6,6,6,6
 dcb 6,6,6,6,6,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,1,1,1,1,1,1,1,6,6,6,6
 dcb 6,6,6,6,6,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
 dcb 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
 dcb $80

