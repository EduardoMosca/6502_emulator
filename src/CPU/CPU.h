#ifndef _CPU_H_
#define _CPU_H_

#include <inttypes.h>
#include <stdio.h>
#include "MEM.h"
#include "type_definitions.h"
#include "opcodes.h"

// Main type definition
typedef struct CPU CPU;
#define CPU_BASE CPU *cpu

// Functions parameters
#define START_CPU_PARAMETERS CPU_BASE
#define RESET_PARAMETERS CPU_BASE, MEM_BASE
#define EXECUTE_PARAMETERS CPU_BASE, MEM_BASE, uint32_t cycles
#define FETCH_BYTE_PARAMETERS CPU_BASE, MEM_BASE, uint32_t *cycles
#define READ_BYTE_PARAMETERS CPU_BASE, MEM_BASE, uint32_t *cycles, const uint8_t *address
#define FETCH_WORD_PARAMETERS CPU_BASE, MEM_BASE, uint32_t *cycles

// Functions definitions
C_VOID startCPU(START_CPU_PARAMETERS);
C_S_VOID Reset(RESET_PARAMETERS);
C_S_S32 Execute(EXECUTE_PARAMETERS);
C_S_U8 FetchByte(FETCH_BYTE_PARAMETERS);
C_S_U8 ReadByte(READ_BYTE_PARAMETERS);
S_VOID LDA_set_status(CPU_BASE);
C_S_U16 FetchWord(FETCH_WORD_PARAMETERS);

// Main struct definition
typedef struct CPU
{
  uint8_t AC;   // Acumulator
  uint8_t X, Y; // Index Register X and Y
  uint8_t SP;   // Stack Pointer
  uint16_t PC;  // Program Counter

  uint8_t C : 1; // Carry Flag
  uint8_t Z : 1; // Zero Flag
  uint8_t I : 1; // Interrupt Disable
  uint8_t D : 1; // Decimal Mode
  uint8_t B : 1; // Breakk Command
  uint8_t O : 1; // Overflow Flag
  uint8_t N : 1; // Negative Flag

  // Functions
  C_VOID(*Reset)
  (RESET_PARAMETERS);
  C_S32(*Execute)
  (EXECUTE_PARAMETERS);
} CPU;

#endif