#include "CPU.h"

C_VOID startCPU(START_CPU_PARAMETERS)
{
  cpu->Reset = Reset;
  cpu->Execute = Execute;
}

C_S_VOID Reset(RESET_PARAMETERS)
{
  cpu->PC = 0xFFFC;
  cpu->SP = (uint8_t)0x0100;
  cpu->D = 0;
  cpu->C = cpu->Z = cpu->I = cpu->D = cpu->B = cpu->O = cpu->N = 0;
  cpu->AC = cpu->X = cpu->Y = 0;
  mem->Initialize(mem);
}

S_VOID LDA_set_status(CPU_BASE)
{
  cpu->Z = (cpu->AC == 0);
  cpu->N = (cpu->AC & 0b10000000) > 0;
}

C_S_S32 Execute(EXECUTE_PARAMETERS)
{
  C_U32 cycles_requested = cycles;
  while (cycles > 0)
  {
    uint8_t Ins = FetchByte(cpu, mem, &cycles);
    switch (Ins)
    {
    case INS_LDA_IM:
      uint8_t value = FetchByte(cpu, mem, &cycles);
      cpu->AC = value;
      LDA_set_status(cpu);
      break;

    case INS_LDA_ZP:
      uint8_t zero_page_address = FetchByte(cpu, mem, &cycles);
      cpu->AC = ReadByte(cpu, mem, &cycles, &zero_page_address);
      LDA_set_status(cpu);
      break;

    case INS_LDA_ZPX:
      uint8_t zero_pagex_address = FetchByte(cpu, mem, &cycles);
      zero_pagex_address += cpu->X;
      cycles--;
      cpu->AC = ReadByte(cpu, mem, &cycles, &zero_pagex_address);
      LDA_set_status(cpu);
      break;

    case INS_JSR:
      uint16_t sub_addr = FetchWord(cpu, mem, &cycles);
      mem->WriteWord(mem, cpu->PC - 1, cpu->SP, &cycles);
      cpu->SP += 2;
      cpu->PC = sub_addr;
      cycles--;
      break;

    default:
      printf("Instrucion not handle %d\n", Ins);
      break;
    }
  }
  C_S32 cycles_used = cycles_requested - cycles;
  return cycles_used;
}

C_S_U8 FetchByte(FETCH_BYTE_PARAMETERS)
{
  uint8_t Data = mem->Data[cpu->PC];
  cpu->PC++;
  (*cycles)--;
  return Data;
}

C_S_U16 FetchWord(FETCH_WORD_PARAMETERS)
{
  uint16_t Data = mem->Data[cpu->PC];
  cpu->PC++;

  Data |= (mem->Data[cpu->PC] << 8);
  cpu->PC++;
  (*cycles) -= 2;

  return Data;
}

C_S_U8 ReadByte(READ_BYTE_PARAMETERS)
{
  uint8_t Data = mem->Data[*address];
  (*cycles)--;
  return Data;
}