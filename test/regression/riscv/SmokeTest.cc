#include "RISCVRegressionTest.hh"

namespace {

using SmokeTest = RISCVRegressionTest;

// Test that a trivial instruction will execute
TEST_P(SmokeTest, instruction) {
  RUN_RISCV(R"(
    addi a5,a5,32
  )");
  EXPECT_EQ(getGeneralRegister<uint64_t>(15), 32u);
}

INSTANTIATE_TEST_SUITE_P(
    RISCV, SmokeTest,
    ::testing::Values(std::make_tuple(EMULATION, "{}"),
                      std::make_tuple(INORDER, "{}"),
                      std::make_tuple(OUTOFORDER,
                                      "{L1-Data-Memory: "
                                      "{Interface-Type: Fixed}}")),
    paramToString);

}  // namespace
