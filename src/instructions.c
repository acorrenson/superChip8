#include <stdio.h>
#include <stdlib.h>

// -- CHIP-8 INSTRUCTIONS --

void CLS(unsigned short const opCode)
{
    // Print assembler code
    printf("%04x - CLS\n", opCode);
    // var: renderer
}

void RET(unsigned short const opCode)
{
    // Print assembler code
    printf("%04x - RET\n", opCode);
    // var: programmeCounter, stack, stackPtr 
}

void JP_addr(unsigned short const opCode)
{
    // Filter
    unsigned short addr;
    addr = opCode & 0x0FFF;
    // Print assembler code
    printf("%04x - JP    #%04x\n", opCode, addr);
    // Op
    // var: programCounter 
}

void CALL_addr(unsigned short const opCode)
{
    // Filter
    unsigned short addr;
    addr = opCode & 0x0FFF;
    // Print assembler code
    printf("%04x - CALL  #%04x\n", opCode, addr);
    // Op
    // var: programCounter, stack, stackPtr
}

void SE_Vx_byte(unsigned short const opCode)
{
    //Filter
    unsigned char Vx;
    unsigned short kk;
    Vx = (opCode & 0x0F00) >> 8;
    kk = opCode & 0x00FF;
    // Print assembler code
    printf("%04x - SE    V%u, #%x\n", opCode, Vx, kk);
    // Op
    // var: programCounter, V
}

void SNE_Vx_byte(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    unsigned short kk;
    Vx = (opCode & 0x0F00) >> 8;
    kk = opCode & 0x00FF;
    // Print assembler code
    printf("%04x - SNE   V%u, #%x\n", opCode, Vx, kk);
    // Op
    // var: programCounter, V
}

void SE_Vx_Vy(unsigned short const opCode)
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Print assembler code
    printf("%04x - SE    V%u, V%u\n", opCode, Vx, Vy);
    // Op
    // var: programCounter, V
}

void LD_Vx_byte(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    unsigned short kk;
    Vx = (opCode & 0x0F00) >> 8; 
    kk = opCode & 0x00FF;
    // Print assembler code
    printf("%04x - LD    V%u, #%x\n", opCode, Vx, kk);
    // Op
    // var: V
}

void ADD_Vx_byte(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    unsigned short kk;
    Vx = (opCode & 0x0F00) >> 8;
    kk = opCode & 0x00FF;
    // Print assembler code
    printf("%04x - ADD   V%u, #%x\n", opCode, Vx, kk);
    // Op
    // var: V
}

void LD_Vx_Vy(unsigned short const opCode)
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Print assembler code
    printf("%04x - LD    V%u, V%u\n", opCode, Vx, Vy);
    // Op
    // var: V
}

void OR_Vx_Vy(unsigned short const opCode)
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Print assembler code
    printf("%04x - OR    V%u, V%u\n", opCode, Vx, Vy);
    // Op
    // var: V
}

void AND_Vx_Vy(unsigned short const opCode)
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Print assembler code
    printf("%04x - AND   V%u, V%u\n", opCode, Vx, Vy);
    // Op
    // var: V
}

void XOR_Vx_Vy(unsigned short const opCode)
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8; 
    Vy = (opCode & 0x00F0) >> 4;
    // Print assembler code
    printf("%04x - XOR   V%u, V%u\n", opCode, Vx, Vy);
    // Op
    // var: V
}

void ADD_Vx_Vy(unsigned short const opCode)
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Print assembler code
    printf("%04x - ADD   V%u, V%u\n", opCode, Vx, Vy);
    // Op
    // var: V
}

void SUB_Vx_Vy(unsigned short const opCode)
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Print assembler code
    printf("%04x - SUB   V%u, V%u\n", opCode, Vx, Vy);
    // Op
    // var: V
}

void SHR_Vx(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04x - SHR   V%u\n", opCode, Vx);
    // Op
    // var: V
}

void SUBN_Vx_Vy(unsigned short const opCode)
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Print assembler code
    printf("%04x - SUBN  V%u, V%u\n", opCode, Vx, Vy);
    // Op
    // var: V
}

void SHL_Vx(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04x - SHL   V%u\n", opCode, Vx);
    // Op
    // var: V
}

void SNE_Vx_Vy(unsigned short const opCode)
{  
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8; 
    Vy = (opCode & 0x00F0) >> 4; 
    // Print assembler code
    printf("%04x - SNE   V%u, V%u\n", opCode, Vx, Vy);
    // Op
    // var: programCounter, V
}

void LD_I_addr(unsigned short const opCode)
{
    // Filter
    unsigned short addr;
    addr = opCode & 0x0FFF;
    // Print assembler code
    printf("%04x - LD    I, #%04x\n", opCode, addr);
    // Op
    // var: I
}

void JP_V0_addr(unsigned short const opCode)
{
    // Filter
    unsigned short addr;
    addr = opCode & 0x0FFF;
    // Print assembler code
    printf("%04x - JP    V0, #%04x\n", opCode, addr);
    // Op
    // var: V, I
}

void RND_Vx_byte(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    unsigned short kk;
    Vx = (opCode & 0x0F00) >> 8;
    kk = opCode & 0x00FF;
    // Print assembler code
    printf("%04x - RND   V%u, #%x\n", opCode, Vx, kk);
    // Op
    // var: random, V
}

void DRW_Vx_Vy_nibble(unsigned short const opCode)
{
    // Filter
    unsigned char Vx, Vy, nibble;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    nibble = opCode & 0x000F;
    // Print assembler code
    printf("%04x - DRW   V%u, V%u, %u\n", opCode, Vx, Vy, nibble);
    // Op
    // var: renderer, V, I
}

void SKP_Vx(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04x - SKP   V%u\n", opCode, Vx);
    // Op
    // var: keyboard event, programCounter, V
}

void SKNP_Vx(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04x - SKNP  V%u\n", opCode, Vx);
    // Op
    // var: keyboard event, programCounter, V
}

void LD_Vx_DT(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04x - LD    V%u, DT\n", opCode, Vx);
    // Op
    // var: delay timer value, V
}

void LD_Vx_K(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04x - LD    V%u, K\n", opCode, Vx);
    // Op
    // var: key press, V
}

void LD_DT_Vx(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04x - LD    DT, V%u\n", opCode, Vx);
    // Op
    // var: delay timer, V
}

void LD_ST_Vx(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04x - LD    ST, V%u\n", opCode, Vx);
    // Op
    // var: sound timer, V
}

void ADD_I_Vx(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04x - ADD   I, V%u\n", opCode, Vx);
    // Op
    // var: V, I
}

void LD_F_Vx(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04x - LD    F, V%u\n", opCode, Vx);
    // Op
    // var: V, I
}

void LD_B_Vx(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04x - LD    B, V%u\n", opCode, Vx);
    // Op
    // var: (BCD representation ?), V, I
}

void LD_I_Vx(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04x - LD    [I], V%u\n", opCode, Vx);
    // Op
    // var: V, I
}

void LD_Vx_I(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04x - LD    V%u, [I]\n", opCode, Vx);
    // Op
    // var: V, I
}

