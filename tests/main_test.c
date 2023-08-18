#include <inttypes.h>
#include "CUnit/CUnitCI.h"
#include "MEM.h"
#include "CPU.h"

CPU cpu;
MEM mem;

CU_TEST_SETUP()
{
  startCPU(&cpu);
  startMEM(&mem);
  cpu.Reset(&cpu, &mem);
}

void test_lda_im(void)
{
  mem.Data[0xFFFC] = INS_LDA_IM;
  mem.Data[0xFFFD] = 0x84;

  CPU cpu_copy = cpu;
  C_S32 cycles_used = cpu.Execute(&cpu, &mem, 2);

  CU_ASSERT_EQUAL(cpu.AC, 0x84);
  CU_ASSERT_EQUAL(cycles_used, 2);
  CU_ASSERT_FALSE(cpu.Z);
  CU_ASSERT_TRUE(cpu.N);
  CU_ASSERT_EQUAL(cpu.C, cpu_copy.C);
  CU_ASSERT_EQUAL(cpu.I, cpu_copy.I);
  CU_ASSERT_EQUAL(cpu.D, cpu_copy.D);
  CU_ASSERT_EQUAL(cpu.B, cpu_copy.B);
  CU_ASSERT_EQUAL(cpu.O, cpu_copy.O);
}

void test_lda_zp(void)
{
  mem.Data[0xFFFC] = INS_LDA_ZP;
  mem.Data[0xFFFD] = 0x42;
  mem.Data[0x0042] = 0x37;

  CPU cpu_copy = cpu;
  C_S32 cycles_used = cpu.Execute(&cpu, &mem, 3);

  CU_ASSERT_EQUAL(cpu.AC, 0x37);
  CU_ASSERT_EQUAL(cycles_used, 3);
  CU_ASSERT_FALSE(cpu.Z);
  CU_ASSERT_FALSE(cpu.N);
  CU_ASSERT_EQUAL(cpu.C, cpu_copy.C);
  CU_ASSERT_EQUAL(cpu.I, cpu_copy.I);
  CU_ASSERT_EQUAL(cpu.D, cpu_copy.D);
  CU_ASSERT_EQUAL(cpu.B, cpu_copy.B);
  CU_ASSERT_EQUAL(cpu.O, cpu_copy.O);
}

void test_lda_zpx(void)
{
  cpu.X = 5;
  mem.Data[0xFFFC] = INS_LDA_ZPX;
  mem.Data[0xFFFD] = 0x42;
  mem.Data[0x0047] = 0x37;

  CPU cpu_copy = cpu;
  C_S32 cycles_used = cpu.Execute(&cpu, &mem, 4);

  CU_ASSERT_EQUAL(cpu.AC, 0x37);
  CU_ASSERT_EQUAL(cycles_used, 4);
  CU_ASSERT_FALSE(cpu.Z);
  CU_ASSERT_FALSE(cpu.N);
  CU_ASSERT_EQUAL(cpu.C, cpu_copy.C);
  CU_ASSERT_EQUAL(cpu.I, cpu_copy.I);
  CU_ASSERT_EQUAL(cpu.D, cpu_copy.D);
  CU_ASSERT_EQUAL(cpu.B, cpu_copy.B);
  CU_ASSERT_EQUAL(cpu.O, cpu_copy.O);
}

void test_lda_zpx_wrapping(void)
{
  cpu.X = 0xFF;
  mem.Data[0xFFFC] = INS_LDA_ZPX;
  mem.Data[0xFFFD] = 0x80;
  mem.Data[0x007F] = 0x37;

  CPU cpu_copy = cpu;
  C_S32 cycles_used = cpu.Execute(&cpu, &mem, 4);

  CU_ASSERT_EQUAL(cpu.AC, 0x37);
  CU_ASSERT_EQUAL(cycles_used, 4);
  CU_ASSERT_FALSE(cpu.Z);
  CU_ASSERT_FALSE(cpu.N);
  CU_ASSERT_EQUAL(cpu.C, cpu_copy.C);
  CU_ASSERT_EQUAL(cpu.I, cpu_copy.I);
  CU_ASSERT_EQUAL(cpu.D, cpu_copy.D);
  CU_ASSERT_EQUAL(cpu.B, cpu_copy.B);
  CU_ASSERT_EQUAL(cpu.O, cpu_copy.O);
}

CUNIT_CI_RUN("test_processor",
             CUNIT_CI_TEST(test_lda_im),
             CUNIT_CI_TEST(test_lda_zp),
             CUNIT_CI_TEST(test_lda_zpx),
             CUNIT_CI_TEST(test_lda_zpx_wrapping));