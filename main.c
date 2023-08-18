#include <stdio.h>
#include "CPU.h"
#include "MEM.h"
#include "opcodes.h"

int main(int argc, char **argv)
{
  CPU cpu;
  MEM mem;
  startCPU(&cpu);
  startMEM(&mem);
  cpu.Reset(&cpu, &mem);
  mem.Data[0xFFFC] = INS_JSR;
  mem.Data[0xFFFD] = 0x42;
  mem.Data[0xFFFE] = 0x42;
  mem.Data[0x4242] = INS_LDA_IM;
  mem.Data[0x4243] = 0x84;
  cpu.Execute(&cpu, &mem, 9);
  return 0;
}