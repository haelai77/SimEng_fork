#include "AArch64RegressionTest.hh"

namespace {

using InstConditional = AArch64RegressionTest;

TEST_P(InstConditional, csinc) {
  // 32-bit
  RUN_AARCH64(R"(
    mov w0, wzr
    mov w1, 42
    mov w2, 7
    cmp w0, w0
    csinc w3, w1, w2, eq
    csinc w4, w1, w2, ne
    csinc w5, w1, w2, lt
    csinc w6, w1, w2, le

    # Check cinc alias as well
    cinc w7, w1, gt
    cinc w8, w1, ge
  )");
  EXPECT_EQ(getGeneralRegister<uint32_t>(3), 42u);
  EXPECT_EQ(getGeneralRegister<uint32_t>(4), 8u);
  EXPECT_EQ(getGeneralRegister<uint32_t>(5), 8u);
  EXPECT_EQ(getGeneralRegister<uint32_t>(6), 42u);
  EXPECT_EQ(getGeneralRegister<uint32_t>(7), 42u);
  EXPECT_EQ(getGeneralRegister<uint32_t>(8), 43u);

  // 64-bit
  RUN_AARCH64(R"(
    mov x0, xzr
    mov x1, 42
    mov x2, 7
    cmp x0, x0
    csinc x3, x1, x2, eq
    csinc x4, x1, x2, ne
    csinc x5, x1, x2, lt
    csinc x6, x1, x2, le

    # Check cinc alias as well
    cinc x7, x1, gt
    cinc x8, x1, ge
  )");
  EXPECT_EQ(getGeneralRegister<uint64_t>(3), 42u);
  EXPECT_EQ(getGeneralRegister<uint64_t>(4), 8u);
  EXPECT_EQ(getGeneralRegister<uint64_t>(5), 8u);
  EXPECT_EQ(getGeneralRegister<uint64_t>(6), 42u);
  EXPECT_EQ(getGeneralRegister<uint64_t>(7), 42u);
  EXPECT_EQ(getGeneralRegister<uint64_t>(8), 43u);
}

INSTANTIATE_TEST_SUITE_P(AArch64, InstConditional, ::testing::Values(EMULATION),
                         coreTypeToString);

}  // namespace
