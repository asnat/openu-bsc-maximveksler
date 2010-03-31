LABEL: .string "C massivly sucks"

mov #0, LABEL
mov #0, @LABEL
mov #0, r0

mov LABEL, LABEL
mov LABEL, @LABEL
mov LABEL, r0

mov @LABEL, LABEL
mov @LABEL, @LABEL
mov @LABEL, r0

mov r0, LABEL
mov r0, @LABEL
mov r0, r0
; ===========================================

cmp #0, #0
cmp #0, LABEL
cmp #0, @LABEL
cmp #0, r0

cmp LABEL, #0
cmp LABEL, LABEL
cmp LABEL, @LABEL
cmp LABEL, r0

cmp @LABEL, #0
cmp @LABEL, LABEL
cmp @LABEL, @LABEL
cmp @LABEL, r0

cmp r0, #0
cmp r0, LABEL
cmp r0, @LABEL
cmp r0, r0
; ===========================================

add #0, LABEL
add #0, @LABEL
add #0, r0

add LABEL, LABEL
add LABEL, @LABEL
add LABEL, r0

add @LABEL, LABEL
add @LABEL, @LABEL
add @LABEL, r0

add r0, LABEL
add r0, @LABEL
add r0, r0
; ===========================================

sub #0, LABEL
sub #0, @LABEL
sub #0, r0

sub LABEL, LABEL
sub LABEL, @LABEL
sub LABEL, r0

sub @LABEL, LABEL
sub @LABEL, @LABEL
sub @LABEL, r0

sub r0, LABEL
sub r0, @LABEL
sub r0, r0
; ===========================================

mul #0, LABEL
mul #0, @LABEL
mul #0, r0

mul LABEL, LABEL
mul LABEL, @LABEL
mul LABEL, r0

mul @LABEL, LABEL
mul @LABEL, @LABEL
mul @LABEL, r0

mul r0, LABEL
mul r0, @LABEL
mul r0, r0
; ===========================================

div #0, LABEL
div #0, @LABEL
div #0, r0

div LABEL, LABEL
div LABEL, @LABEL
div LABEL, r0

div @LABEL, LABEL
div @LABEL, @LABEL
div @LABEL, r0

div r0, LABEL
div r0, @LABEL
div r0, r0
; ===========================================

lea LABEL, LABEL
lea LABEL, @LABEL
lea LABEL, r0
; ===========================================

inc LABEL
inc @LABEL
inc r0
; ===========================================

dec LABEL
dec @LABEL
dec r0
; ===========================================

jmp LABEL
jmp @LABEL
; ===========================================

bne LABEL
bne @LABEL
; ===========================================

red LABEL
red @LABEL
red r0
; ===========================================

prn #0
prn LABEL
prn @LABEL
prn r0
; ===========================================

jsr LABEL
jsr @LABEL
; ===========================================

rts
; ===========================================

hlt
; ===========================================
