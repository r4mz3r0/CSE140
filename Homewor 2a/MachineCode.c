// Collaboators: Ramiro G, Jamal B.  
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// structure of Rformat
typedef struct rFormat{
	char opcode[8];
	char rs[5];
	char rt[5];
	char rd[5];
	char shamt[5];
	char funct[6];
	int i; 
}RFormat;

// gets the function code from opcode respectively
int getFunCode(char* opcode){
	if (strcmp(opcode, "add") == 0) return 0b100000;
    if (strcmp(opcode, "addu") == 0) return 0b100001;
    if (strcmp(opcode, "and") == 0) return 0b100100;
    if (strcmp(opcode, "jr") == 0) return 0b001000;
    if (strcmp(opcode, "nor") == 0) return 0b100111;
    if (strcmp(opcode, "or") == 0) return 0b100101;
    if (strcmp(opcode, "slt") == 0) return 0b101010;
    if (strcmp(opcode, "sltu") == 0) return 0b101011;
    if (strcmp(opcode, "sll") == 0) return 0b000000;
    if (strcmp(opcode, "srl") == 0) return 0b000010;
    if (strcmp(opcode, "sub") == 0) return 0b100010;
    if (strcmp(opcode, "subu") == 0) return 0b100011;
    if (strcmp(opcode, "div") == 0) return 0b011010;
    if (strcmp(opcode, "divu") == 0) return 0b011011;
    if (strcmp(opcode, "mfhi") == 0) return 0b010000;
    if (strcmp(opcode, "mflo") == 0) return 0b010010;
    if (strcmp(opcode, "mult") == 0) return 0b011000;
    if (strcmp(opcode, "multu") == 0) return 0b011001;
    if (strcmp(opcode, "sra") == 0) return 0b000011;
    if (strcmp(opcode, "break"  ) == 0) return 0b001101;
    if (strcmp(opcode, "jalr") == 0) return 0b001001;
    if (strcmp(opcode, "mthi") == 0) return 0b010001;
    if (strcmp(opcode, "mtlo") == 0) return 0b010011;
    if (strcmp(opcode, "sllv") == 0) return 0b000100;
    if (strcmp(opcode, "srav") == 0) return 0b000111;
    if (strcmp(opcode, "srlv") == 0) return 0b000110;
    if (strcmp(opcode, "syscall") == 0) return 0b001100;
    if (strcmp(opcode, "xor") == 0) return 0b100110;
	return 1;
}

// gets register values
int regVal(char* r){
	if (strcmp(r,"0") == 0) return 0;
	if(strcmp(r,"zero") == 0) return 0;
	if(strcmp(r,"at") == 0) return 1;
	if(strcmp(r,"v0") == 0) return 2;
	if(strcmp(r,"v1") == 0) return 3;
	if(strcmp(r,"a0") == 0) return 4;
	if(strcmp(r,"a1") == 0) return 5;
	if(strcmp(r,"a2") == 0) return 6;
	if(strcmp(r,"a3") == 0) return 7;
	if(strcmp(r,"t0") == 0) return 8;
	if(strcmp(r,"t1") == 0) return 9;
	if(strcmp(r,"t2") == 0) return 10;
	if(strcmp(r,"t3") == 0) return 11;
	if(strcmp(r,"t4") == 0) return 12;
	if(strcmp(r,"t5") == 0) return 13;
	if(strcmp(r,"t6") == 0) return 14;
	if(strcmp(r,"t7") == 0) return 15;
	if(strcmp(r,"s0") == 0) return 16;
	if(strcmp(r,"s1") == 0) return 17;
	if(strcmp(r,"s2") == 0) return 18;
	if(strcmp(r,"s3") == 0) return 19;
	if(strcmp(r,"s4") == 0) return 20;
	if(strcmp(r,"s5") == 0) return 21;
	if(strcmp(r,"s6") == 0) return 22;
	if(strcmp(r,"s7") == 0) return 23;
	if(strcmp(r,"t8") == 0) return 24;
	if(strcmp(r,"t9") == 0) return 25;
	if(strcmp(r,"k0") == 0) return 26;
	if(strcmp(r,"k1") == 0) return 27;
	if(strcmp(r,"gp") == 0) return 28;
	if(strcmp(r,"sp") == 0) return 29;
	if(strcmp(r,"fp") == 0) return 30;
	if(strcmp(r,"ra") == 0) return 31;
	return 1;
}

// gets each field of struct and combines them into 32 bit
int putTogether(RFormat *instruct){
	return getFunCode(instruct->opcode) + (instruct->i << 6) + (regVal(instruct->rd) << 11) + (regVal(instruct->rt) << 16) + (regVal(instruct->rs) << 21);
}

// goes through 32bits and makes a 1|0 conversion
void setInt2Bin(int num, char* MC){
	for(int i = 0; i < 32; i++){
		int ask = 0x1 << i;
		MC[31 - i] = num & ask ? '1' : '0';
	}
	MC[32] = 0;
}

// Prints
void printFormat(RFormat *instruct){
	char MC[32];
	setInt2Bin(putTogether(instruct),MC);
	printf("Operation: %s\n""Rs: %s (R%d)\n""Rt: %s (R%d)\n""Rd: %s (R%d)\n""Shamt: %d\n""Funct: %d\n""Machine code: %s\n",
			instruct->opcode, 
			instruct->rs, 
			regVal(instruct->rs), 
			instruct->rt,
			regVal(instruct->rt),
			instruct->rd,
			regVal(instruct->rd),
			instruct->i,
			getFunCode(instruct->opcode),
			MC);
}

// gets register mapping for a specific operation
int getFieldLocation(char* opcode){
	if (strcmp(opcode, "add") == 0)
		return 0x312;	
    if (strcmp(opcode, "addu") == 0) 
		return 0x312;
    if (strcmp(opcode, "and") == 0) 
		return 0x312;
    if (strcmp(opcode, "break") == 0) 
		return 0x000;
    if (strcmp(opcode, "div") == 0) 
		return 0x120;
    if (strcmp(opcode, "divu") == 0) 
		return 0x120;
    if (strcmp(opcode, "jalr") == 0) 
		return 0x310;
    if (strcmp(opcode, "jr") == 0) 
		return 0x100;
    if (strcmp(opcode, "mfhi") == 0) 
		return 0x300;
    if (strcmp(opcode, "mflo") == 0) 
		return 0x300;
    if (strcmp(opcode, "mthi") == 0) 
		return 0x100;
    if (strcmp(opcode, "mtlo") == 0) 
		return 0x100;
    if (strcmp(opcode, "mult") == 0) 
		return 0x120;
    if (strcmp(opcode, "multu") == 0) 
		return 0x120;
    if (strcmp(opcode, "nor")== 0) 
		return 0x312;
    if (strcmp(opcode, "or") == 0) 
		return 0x312;
    if (strcmp(opcode, "sll") == 0) 
		return 0x324;
    if (strcmp(opcode, "sllv") == 0) 
		return 0x321;
    if (strcmp(opcode, "slt") == 0) 
		return 0x312;
    if (strcmp(opcode, "sltu") == 0) 
		return 0x312;
    if (strcmp(opcode, "sra") == 0) 
		return 0x324;
    if (strcmp(opcode, "srav") == 0) 
		return 0x321;
    if (strcmp(opcode, "srl") == 0) 
		return 0x324;
    if (strcmp(opcode, "srlv") == 0) 
		return 0x321;
    if (strcmp(opcode, "sub") == 0) 
		return 0x312;
    if (strcmp(opcode, "subu") == 0) 
		return 0x312;
    if (strcmp(opcode, "syscall") == 0) 
		return 0x000;
    if (strcmp(opcode, "xor") == 0) 
		return 0x312;
    return 1;
}

// scans user input
void scanInput(RFormat *instruct){
	scanf("%s", instruct->opcode);

	const char c[2] = ",";
	char regsisters[32];
	char *pnt;
	int ask =  0xf00;

	scanf("%[^\n]", regsisters);

	pnt = strtok(regsisters, c);

	for(int i = 0; i < 3; i++){
		int location = (ask & getFieldLocation(instruct->opcode)) >> (2-i) * 4;
		if(location == 1){
			sscanf(pnt, "%s", instruct->rs);
		}else if(location == 2){
			sscanf(pnt, "%s", instruct->rt);
		}else if(location == 3){
			sscanf(pnt, "%s", instruct->rd);
		}else if(location == 4){
			sscanf(pnt, "%d", &(instruct->i));
		}
		pnt = strtok(NULL, c);
		ask = ask >> 4; 
	}
}

// Starts
int main(void){
	//properly setting up the instruction struct to be used
	RFormat* instruction, instruct;
	instruction = &instruct;
	printf("Enter an R-format instruction:\n");
	//initializing object
	instruction->i = 0;
	for(int i = 0; i < 2; i++){
		if(i == 0){
			instruction->rs[i] = '0';
			instruction->rt[i] = '0';
			instruction->rd[i] = '0';
		}else{
			instruction->rs[i] = 0;
			instruction->rt[i] = 0;
			instruction->rd[i] = 0;		
		}
	}
	scanInput(instruction);
	printFormat(instruction);
	return 0;
}
// test instruction
// add $t0 $t1 $t2

// R-Format instructions
/*	Operation	opcode: 	Fucnt:
	add			0			20
	addu		0			21
	and			0			24
	jr			0			08
	nor			0			27
	or			0			25
	slt			0			2a
	sltu		0			2b
	sll			0			00
	srl			0			02
	sub			0			22
	subu		0			23
	div			0			1a
	divu		0			1b
	mfhi		0			10
	mflo		0			12
	mfcO		0			0
	mult		0			18
	multu		0			19
	sra			0			3
*/
// Register values
/* 
	$zero	0
	$at		1
	$v0		2
	$v1		3
	$a0		4
	$a1		5
	$a2		6
	$a3		7
	$t0		8
	$t1		9
	$t2		10
	$t3		11
	$t4		12
	$t5		13
	$t6		14
	$t7		15
	$s0		16
	$s1		17
	$s2		18
	$s3		19
	$s4		20
	$s5		21
	$s6		22
	$s7		23
	$t8		24
	$t9		25
	$k0		26
	$k1		27
	$gp		28
	$sp		29
	$fp		30
	$ra		31
*/