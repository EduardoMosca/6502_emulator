#include "MEM.h"

C_VOID startMEM(MEM_BASE)
{
  mem->Initialize = Initialize;
  mem->WriteWord = WriteWord;
}

C_S_VOID Initialize(INITIALIZE_PARAMETERS)
{
  memset(mem->Data, 0, sizeof(mem->Data));
}

C_S_VOID WriteWord(WRITE_WORD_PARAMETERS)
{
  mem->Data[address] = (data & 0xFF);
  mem->Data[address + 1] = (data >> 8);
  (*cycles) -= 2;
}