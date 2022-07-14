.global sumS32
.global sumS8
.global countNegative
.global countNonNegative
.global countMatches
.global uint8ToBinaryString
.global int16ToBinaryString
.global getParity
.global returnMax
.global returnMin

.text

sumS32:
	MOV R2, R0
	MOV R0, #0
sumS32_loop:
	LDRH R3, [R2], #4
	ADD R0, R0, R3
	SUBS R1, R1, #1
	BNE sumS32_loop
	B end

sumS8:
	MOV R2, R0
	MOV R0, #0
sumS8_loop: 
	LDRB R3, [R2], #1
	ADD R0, R0, R3
	SUBS R1, R1, #1
	BNE sumS8_loop
	B end

countNegative:
	MOV R2, R0
	MOV R0, #0
	PUSH {LR}
countNegative_loop:
	LDR R3, [R2], #4
	CMP R3, #0
	BLLT increase_counter
	SUBS R1, R1, #1
	BNE countNegative_loop
	POP {LR}
	B end

countNonNegative:
	MOV R2, R0
	MOV R0, #0
	PUSH {LR}
countNonNegative_loop:
	LDR R3, [R2], #4
	CMP R3, #0
	BLPL increase_counter
	SUBS R1, R1, #1
	BNE countNonNegative_loop
	POP {LR}
	B end

countMatches:
	MOV R2, R0
	MOV R0, #0
	PUSH {LR}
countMatches_loop:
	LDRB R3, [R2], #1
	CMP R3, R1
	BLEQ increase_counter
	CMP R3, #0
	BNE countMatches_loop
	POP {LR}
	B end

uint8ToBinaryString:
	MOV R2, #0x80
uint8ToBinaryString_loop:
	TST R1, R2
	MOVNE R3, #'1'
	MOVEQ R3, #'0'
	STRB R3, [R0], #1
	MOVS R2, R2, LSR #1
	BNE uint8ToBinaryString_loop
	MOV R3, #0
	STRB R3, [R0]
	B end

int16ToBinaryString:
	MOV R2, #0x8000
int16ToBinaryString_loop:
	TST R1, R2
	MOVNE R3, #'1'
	MOVEQ R3, #'0'
	STRB R3, [R0], #1
	MOVS R2, R2, LSR #1
	BNE int16ToBinaryString_loop
	MOV R3, #0
	STRB R3, [R0]
	B end

getParity:
	MOV R2, R0
	MOV R0, #0
	MOV R1, #32
	PUSH {LR}
getParity_loop:
	TST R2, #1
	BLEQ increase_counter
	MOV R2, R2, LSR #1
	SUBS R1, R1, #1
	BNE getParity_loop
	AND R0, R0, #1
	POP {LR}
	B end

returnMax:
	MOV R2, R0
	LDRB R0, [R2]
	PUSH {LR}
returnMax_loop:
	LDRSH R3, [R2], #4
	CMP R3, R0
	BLPL store_new
	SUBS R1, R1, #1
	BNE returnMax_loop
	POP {LR}
	B end

returnMin:
	MOV R2, R0
	LDRB R0, [R2]
	PUSH {LR}
returnMin_loop:
	LDRSH R3, [R2], #4
	CMP R3, R0
	BLMI store_new
	SUBS R1, R1, #1
	BNE returnMin_loop
	POP {LR}
	B end

increase_counter:
	ADD R0, R0, #1
	BX LR
store_new:
	MOV R0, R3
	BX LR
end:
	BX LR
