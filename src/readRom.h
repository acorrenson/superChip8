
int readRom(unsigned char * memory, char const * fileName);
void printMemory(unsigned char * memory, int size);
unsigned short getOpCodeAt(unsigned char * memoryPtr, unsigned char programCounter);
void desasembler(unsigned short const opCode, 
                 unsigned char *pProgramCounter, 
                 unsigned char V[16], 
                 unsigned short *pI, 
                 unsigned char stack[48], 
                 unsigned short *pStackPtr,
                 SDL_Renderer *renderer,
                 unsigned char keyBoardState[16],
                 unsigned char memory[4096],
                 unsigned short * pDelayTimer,
                 unsigned short * pSoundTimer);
