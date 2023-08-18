#ifndef _MEM_H_
#define _MEM_H_

#include <inttypes.h>
#include <string.h>
#include "type_definitions.h"

// Main type definition
typedef struct MEM MEM;
#define MEM_BASE MEM *mem

// Consts
#define MAX_MEM 1024 * 64

// Functions parameters
#define INITIALIZE_PARAMETERS MEM_BASE
#define WRITE_WORD_PARAMETERS MEM_BASE, const uint16_t data, const uint8_t address, uint32_t *cycles

// Functions definitions
C_VOID startMEM(MEM_BASE);
C_S_VOID Initialize(INITIALIZE_PARAMETERS);
C_S_VOID WriteWord(WRITE_WORD_PARAMETERS);

// Main struct definition
typedef struct MEM
{
  uint8_t Data[MAX_MEM];

  C_VOID(*Initialize)
  (INITIALIZE_PARAMETERS);
  C_VOID(*WriteWord)
  (WRITE_WORD_PARAMETERS);
} MEM;

#endif