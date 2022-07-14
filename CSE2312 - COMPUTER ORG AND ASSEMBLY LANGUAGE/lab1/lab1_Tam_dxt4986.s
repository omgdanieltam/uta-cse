.global add64
.global sub64
.global minU8
.global minS8
.global isLessThanU32
.global isLessThanS32
.global shiftLeftU32
.global shiftU32
.global shiftS32
.global isEqualU16
.global isEqualS16
.global stringCopy
.global stringCat

.text

add64:
	ADDS R0, R0, R2
	ADC R1, R1, R3
	B end

sub64:
	SUBS R0, R0, R2
	SBC R1, R1, R3
	B end

minU8:
	CMP R0, R1
	BMI end
	MOV R0, R1
	B end

minS8:
	CMP R0, R1
	BMI end
	MOV R0, R1
	B end

isLessThanU32:
	CMP R0, R1
	MOV R0, #1
	BMI end
	MOV R0, #0
	B end

isLessThanS32:
	CMP R0, R1
	MOV R0, #1
	BMI end
	MOV R0, #0
	B end

shiftLeftU32:
	MOV R0, R0, LSL R1
	B end

shiftU32:
	MOV R0, R0, LSL R1
	B end

shiftS32:
	CMP R1, #0
	BMI shiftS32_negative
	MOV R0, R0, ASL R1
	B end
shiftS32_negative:
	MVN R1, R1
	ADD R1, #1
	MOV R0, R0, ASR R1
	B end

isEqualU16:
	CMP R0, R1
	MOV R0, #1
	BEQ end
	MOV R0, #0
	B end

isEqualS16:
	CMP R0, R1
	MOV R0, #1
	BEQ end
	MOV R0, #0
	B end

stringCopy:
	LDRB R2, [R1], #1
	CMP R2, #0
	BEQ end
	STRB R2, [R0], #1
	B stringCopy

stringCat:
	MOV R2, R1
stringCat_loop1:
	LDRB R3, [R2], #1
	CMP R3, #0
	BNE stringCat_loop1
	SUB R2, R2, #1
stringCat_loop2:
	LDRB R3, [R0], #1
	STRB R3, [R2], #1
	CMP R3, #0
	BNE stringCat_loop2
	B end

end:
	BX LR
