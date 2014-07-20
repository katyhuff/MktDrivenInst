#include <gtest/gtest.h>

#include <string>

#include "decomm_inst.h"

#include "institution_tests.h"
#include "agent_tests.h"

using decomm::DecommInst;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
class DecommInstTest : public ::testing::Test {
 protected:
  cyclus::TestContext tc_;
  DecommInst* src_inst_;
  std::string target_commod, target_fac;
  int num_to_build;
  std::vector<std::string> prototypes;
  virtual void SetUp() {
    InitParameters();
    src_inst_ = new DecommInst(tc_.get());
  }

  virtual void TearDown() {}

  void InitParameters() {
    target_fac = "BatchReactor";
    target_commod = "fresh_sfr_fuel";
    prototypes.push_back("target_fac");
    num_to_build = 2;
    cyclus::Context* ctx = tc_.get();
  }
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
TEST_F(DecommInstTest, clone) {
  DecommInst* cloned_inst =
      dynamic_cast<DecommInst*> (src_inst_->Clone());

  EXPECT_EQ("", cloned_inst->target_fac_());
  EXPECT_EQ("", cloned_inst->target_commod_()); 
  EXPECT_EQ(0, cloned_inst->num_to_build_()); 
  EXPECT_EQ(0, cloned_inst->n_built_()); 
  EXPECT_EQ(0, cloned_inst->amt_req_()); 
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
TEST_F(DecommInstTest, InitialState) {
  // Test things about the initial state of the inst here
  EXPECT_EQ("", src_inst_->target_fac_());
  EXPECT_EQ("", src_inst_->target_commod_()); 
  EXPECT_EQ(0, src_inst_->num_to_build_()); 
  EXPECT_EQ(0, src_inst_->n_built_()); 
  EXPECT_EQ(0, src_inst_->amt_req_()); 
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
TEST_F(DecommInstTest, Print) {
  EXPECT_NO_THROW(std::string s = src_inst_->str());
  // Test DecommInst specific aspects of the print method here
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
TEST_F(DecommInstTest, Tick) {
  int time = 1;
  EXPECT_NO_THROW(src_inst_->Tick());
  // Test DecommInst specific behaviors of the handleTick function here
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
TEST_F(DecommInstTest, Tock) {
  int time = 1;
  EXPECT_NO_THROW(src_inst_->Tick());
  // Test DecommInst specific behaviors of the handleTock function here
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
cyclus::Agent* DecommInstitutionConstructor(cyclus::Context* ctx) {
  return new DecommInst(ctx);
}

// required to get functionality in cyclus agent unit tests library
#ifndef CYCLUS_AGENT_TESTS_CONNECTED
int ConnectAgentTests();
static int cyclus_agent_tests_connected = ConnectAgentTests();
#define CYCLUS_AGENT_TESTS_CONNECTED cyclus_agent_tests_connected
#endif // CYCLUS_AGENT_TESTS_CONNECTED

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
INSTANTIATE_TEST_CASE_P(DecommInst, InstitutionTests,
                        ::testing::Values(&DecommInstitutionConstructor));
INSTANTIATE_TEST_CASE_P(DecommInst, AgentTests,
                        ::testing::Values(&DecommInstitutionConstructor));
