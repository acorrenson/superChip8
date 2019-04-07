void CLS(unsigned short const opCode, unsigned char *pProgramCounter, SDL_Renderer *renderer, unsigned char screen[32][64]);

void RET(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char stack[48], unsigned short *pStack);

void JP_addr(unsigned short const opCode, unsigned char *pProgramCounter);

void CALL_addr(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char stack[48], unsigned short *pStack);

void SE_Vx_byte(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16]);

void SNE_Vx_byte(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16]);

void SE_Vx_Vy(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16]);

void LD_Vx_byte(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16]);

void ADD_Vx_byte(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16]);

void LD_Vx_Vy(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16]);

void OR_Vx_Vy(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16]);

void AND_Vx_Vy(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16]);

void XOR_Vx_Vy(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16]);

void ADD_Vx_Vy(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16]);

void SUB_Vx_Vy(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16]);

void SHR_Vx(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16]);

void SUBN_Vx_Vy(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16]);

void SHL_Vx(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16]);

void SNE_Vx_Vy(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16]);

void LD_I_addr(unsigned short const opCode, unsigned char *pProgramCounter, unsigned short *pI);

void JP_V0_addr(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16]);

void RND_Vx_byte(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16]);

void DRW_Vx_Vy_nibble(unsigned short const opCode, unsigned char * pProgramCounter, unsigned char V[16], unsigned short *pI,
  unsigned char screen[32][64], unsigned char memory[4096]);

void SKP_Vx(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16], unsigned char keyboardState[16]);

void SKNP_Vx(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16], unsigned char keyboardState[16]);

void LD_Vx_DT(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16], unsigned short *pDelayTimer);

void LD_Vx_K(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16], unsigned char keyboardState[16]);

void LD_DT_Vx(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16], unsigned short *pDelayTimer);

void LD_ST_Vx(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16], unsigned short *pSoundTimer);

void ADD_I_Vx(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16], unsigned short *pI);

void LD_F_Vx(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16], unsigned short *pI);

void LD_B_Vx(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16], unsigned short *pI, unsigned char memory[4096]);

void LD_I_Vx(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16], unsigned short *pI, unsigned char memory[4096]);

void LD_Vx_I(unsigned short const opCode, unsigned char *pProgramCounter, unsigned char V[16], unsigned short *pI, unsigned char memory[4096]);