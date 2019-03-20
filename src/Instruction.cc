#include "Instruction.hh"

namespace simeng {

void Instruction::setInstructionAddress(uint64_t address) {
  instructionAddress_ = address;
}
uint64_t Instruction::getInstructionAddress() const {
  return instructionAddress_;
}
void Instruction::setBranchPrediction(BranchPrediction prediction) {
  prediction_ = prediction;
}
uint64_t Instruction::getBranchAddress() const { return branchAddress_; }
bool Instruction::wasBranchTaken() const { return branchTaken_; }
bool Instruction::wasBranchMispredicted() const {
  assert(executed_ &&
         "Branch misprediction check requires instruction to have executed");

  // Flag as mispredicted if taken state was wrongly predicted, or taken and
  // predicted target is wrong
  return (branchTaken_ != prediction_.taken ||
          (branchTaken_ && prediction_.target != branchAddress_));
}

void Instruction::setSequenceId(uint64_t seqId) { sequenceId_ = seqId; };
uint64_t Instruction::getSequenceId() const { return sequenceId_; };

void Instruction::setFlushed() { flushed_ = true; }
bool Instruction::isFlushed() const { return flushed_; }

bool Instruction::hasExecuted() const { return executed_; }
void Instruction::setCommitReady() { canCommit_ = true; }
bool Instruction::canCommit() const { return canCommit_; }

}  // namespace simeng