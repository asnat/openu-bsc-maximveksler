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

add #0, #0
add #0, LABEL
add #0, @LABEL
add #0, r0

add LABEL, #0
add LABEL, LABEL
add LABEL, @LABEL
add LABEL, r0

add @LABEL, #0
add @LABEL, LABEL
add @LABEL, @LABEL
add @LABEL, r0

add r0, #0
add r0, LABEL
add r0, @LABEL
add r0, r0
; ===========================================

sub #0, #0
sub #0, LABEL
sub #0, @LABEL
sub #0, r0

sub LABEL, #0
sub LABEL, LABEL
sub LABEL, @LABEL
sub LABEL, r0

sub @LABEL, #0
sub @LABEL, LABEL
sub @LABEL, @LABEL
sub @LABEL, r0

sub r0, #0
sub r0, LABEL
sub r0, @LABEL
sub r0, r0
; ===========================================

mul #0, #0
mul #0, LABEL
mul #0, @LABEL
mul #0, r0

mul LABEL, #0
mul LABEL, LABEL
mul LABEL, @LABEL
mul LABEL, r0

mul @LABEL, #0
mul @LABEL, LABEL
mul @LABEL, @LABEL
mul @LABEL, r0

mul r0, #0
mul r0, LABEL
mul r0, @LABEL
mul r0, r0
; ===========================================

div #0, #0
div #0, LABEL
div #0, @LABEL
div #0, r0

div LABEL, #0
div LABEL, LABEL
div LABEL, @LABEL
div LABEL, r0

div @LABEL, #0
div @LABEL, LABEL
div @LABEL, @LABEL
div @LABEL, r0

div r0, #0
div r0, LABEL
div r0, @LABEL
div r0, r0
; ===========================================

lea #0, #0
lea #0, LABEL
lea #0, @LABEL
lea #0, r0

lea LABEL, #0
lea LABEL, LABEL
lea LABEL, @LABEL
lea LABEL, r0

lea @LABEL, #0
lea @LABEL, LABEL
lea @LABEL, @LABEL
lea @LABEL, r0

lea r0, #0
lea r0, LABEL
lea r0, @LABEL
lea r0, r0
; ===========================================

inc #0, #0
inc #0, LABEL
inc #0, @LABEL
inc #0, r0

inc LABEL, #0
inc LABEL, LABEL
inc LABEL, @LABEL
inc LABEL, r0

inc @LABEL, #0
inc @LABEL, LABEL
inc @LABEL, @LABEL
inc @LABEL, r0

inc r0, #0
inc r0, LABEL
inc r0, @LABEL
inc r0, r0
; ===========================================

dec #0, #0
dec #0, LABEL
dec #0, @LABEL
dec #0, r0

dec LABEL, #0
dec LABEL, LABEL
dec LABEL, @LABEL
dec LABEL, r0

dec @LABEL, #0
dec @LABEL, LABEL
dec @LABEL, @LABEL
dec @LABEL, r0

dec r0, #0
dec r0, LABEL
dec r0, @LABEL
dec r0, r0
; ===========================================

jmp #0, #0
jmp #0, LABEL
jmp #0, @LABEL
jmp #0, r0

jmp LABEL, #0
jmp LABEL, LABEL
jmp LABEL, @LABEL
jmp LABEL, r0

jmp @LABEL, #0
jmp @LABEL, LABEL
jmp @LABEL, @LABEL
jmp @LABEL, r0

jmp r0, #0
jmp r0, LABEL
jmp r0, @LABEL
jmp r0, r0
; ===========================================

bne #0, #0
bne #0, LABEL
bne #0, @LABEL
bne #0, r0

bne LABEL, #0
bne LABEL, LABEL
bne LABEL, @LABEL
bne LABEL, r0

bne @LABEL, #0
bne @LABEL, LABEL
bne @LABEL, @LABEL
bne @LABEL, r0

bne r0, #0
bne r0, LABEL
bne r0, @LABEL
bne r0, r0
; ===========================================

red #0, #0
red #0, LABEL
red #0, @LABEL
red #0, r0

red LABEL, #0
red LABEL, LABEL
red LABEL, @LABEL
red LABEL, r0

red @LABEL, #0
red @LABEL, LABEL
red @LABEL, @LABEL
red @LABEL, r0

red r0, #0
red r0, LABEL
red r0, @LABEL
red r0, r0
; ===========================================

prn #0, #0
prn #0, LABEL
prn #0, @LABEL
prn #0, r0

prn LABEL, #0
prn LABEL, LABEL
prn LABEL, @LABEL
prn LABEL, r0

prn @LABEL, #0
prn @LABEL, LABEL
prn @LABEL, @LABEL
prn @LABEL, r0

prn r0, #0
prn r0, LABEL
prn r0, @LABEL
prn r0, r0
; ===========================================

jsr #0, #0
jsr #0, LABEL
jsr #0, @LABEL
jsr #0, r0

jsr LABEL, #0
jsr LABEL, LABEL
jsr LABEL, @LABEL
jsr LABEL, r0

jsr @LABEL, #0
jsr @LABEL, LABEL
jsr @LABEL, @LABEL
jsr @LABEL, r0

jsr r0, #0
jsr r0, LABEL
jsr r0, @LABEL
jsr r0, r0
; ===========================================

rts #0, #0
rts #0, LABEL
rts #0, @LABEL
rts #0, r0

rts LABEL, #0
rts LABEL, LABEL
rts LABEL, @LABEL
rts LABEL, r0

rts @LABEL, #0
rts @LABEL, LABEL
rts @LABEL, @LABEL
rts @LABEL, r0

rts r0, #0
rts r0, LABEL
rts r0, @LABEL
rts r0, r0
; ===========================================

hlt #0, #0
hlt #0, LABEL
hlt #0, @LABEL
hlt #0, r0

hlt LABEL, #0
hlt LABEL, LABEL
hlt LABEL, @LABEL
hlt LABEL, r0

hlt @LABEL, #0
hlt @LABEL, LABEL
hlt @LABEL, @LABEL
hlt @LABEL, r0

hlt r0, #0
hlt r0, LABEL
hlt r0, @LABEL
hlt r0, r0
; ===========================================
