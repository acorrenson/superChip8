#include <stdio.h>
#include <stdlib.h>

// -- CHIP-8 INSTRUCTIONS --

void CLS()
{
    // var: renderer
}

void RET()
{
    // var: programmeCounter, stack, stackPtr 
}

void JP_addr()
{
    // Filter
    unsigned short addr;
    addr = opCode & 0x0FFF;
    // Op
    // var: programCounter 
}

void CALL_addr()
{
    // Filter
    unsigned short addr;
    addr = opCode & 0x0FFF;
    // Op
    // var: programCounter, stack, stackPtr
}

void SE_Vx_byte()
{
    //Filter
    unsigned char Vx;
    unsigned short kk;
    Vx = (opCode & 0x0F00) >> 8;
    kk = opCode & 0x00FF;
    // Op
    // var: programCounter, V
}

void SNE_Vx_byte()
{
    // Filter
    unsigned char Vx;
    unsigned short kk;
    Vx = (opCode & 0x0F00) >> 8;
    kk = opCode & 0x00FF;
    // Op
    // var: programCounter, V
}

void SE_Vx_Vy()
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Op
    // var: programCounter, V
}

void LD_Vx_byte()
{
    // Filter
    unsigned char Vx;
    unsigned short kk;
    Vx = (opCode & 0x0F00) >> 8; 
    kk = opCode & 0x00FF;
    // Op
    // var: V
}

void ADD_Vx_byte()
{
    // Filter
    unsigned char Vx;
    unsigned short kk;
    Vx = (opCode & 0x0F00) >> 8;
    kk = opCode & 0x00FF;
    // Op
    // var: V
}

void LD_Vx_Vy()
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    kk = (opCode & 0x00F0) >> 4;
    // Op
    // var: V
}

void OR_Vx_Vy()
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Op
    // var: V
}

void AND_Vx_Vy()
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Op
    // var: V
}

void XOR_Vx_Vy()
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8; 
    Vy = (opCode & 0x00F0) >> 4;
    // Op
    // var: V
}

void ADD_Vx_Vy()
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Op
    // var: V
}

void SUB_Vx_Vy()
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Op
    // var: V
}

void SHR_Vx()
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Op
    // var: V
}

void SUBN_Vx_Vy()
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Op
    // var: V
}

void SHL_Vx()
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Op
    // var: V
}

void SNE_Vx_Vy()
{  
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8; 
    Vy = (opCode & 0x00F0) >> 4; 
    // Op
    // var: programCounter, V
}

void LD_I_addr()
{
    // Filter
    unsigned short addr;
    addr = opCode & 0x0FFF;
    // Op
    // var: I
}

void JP_V0_addr()
{
    // Filter
    unsigned short addr;
    addr = opCode & 0x0FFF;
    // Op
    // var: V, I
}

void RND_Vx_byte()
{
    // Filter
    unsigned char Vx;
    unsigned short kk;
    Vx = (opCode & 0x0F00) >> 8;
    kk = opCode & 0x00FF;
    // Op
    // var: random, V
}

void DRW_Vx_Vy_nibble()
{
    // Filter
    unsigned char Vx, Vy, nibble;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    nibble = opCode & 0x000F;
    // Op
    // var: renderer, V, I
}

void SKP_Vx()
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Op
    // var: keyboard event, programCounter, V
}

void SKNP_Vx()
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Op
    // var: keyboard event, programCounter, V
}

void LD_Vx_DT()
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Op
    // var: delay timer value, V
}

void LD_Vx_K()
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Op
    // var: key press, V
}

void LD_DT_Vx()
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Op
    // var: delay timer, V
}

void LD_ST_Vx()
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Op
    // var: sound timer, V
}

void ADD_I_Vx()
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Op
    // var: V, I
}

void LD_F_Vx()
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Op
    // var: V, I
}

void LD_B_Vx()
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Op
    // var: (BCD representation ?), V, I
}

void LD_I_Vx()
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Op
    // var: V, I
}

void LD_Vx_I()
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Op
    // var: V, I
}

