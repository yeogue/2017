	.text
	.arm 
	.global primeNumber_L

RESET:  B      MAIN

	.org    0x100
MAIN:	b main

primeNumber_L:
	MOV R1, #2
while1_L:
	CMP R1, #101
	BGE main
	
	MOV R2, #2
	BL while2_L
backWhile1_L:
	ADD R1, R1, #1
	BL while1_L

while2_L:
	CMP R2, R1
	MOVEQ R0, R1
	BGT backWhile1_L

	MOV R4, #2
	MOV R3, R2
	BL mod_L
backWhile2_L:
	ADD R2, R2, #1
	BEQ backWhile1_L
	BL while2_L

mod_L:
	CMP R1, R3
	BLE backWhile2_L
	MUL R3, R2, R4
	ADD R4, R4, #1
	BL mod_L
	
        .end
