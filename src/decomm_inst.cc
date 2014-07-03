#include "decomm_inst.h"

using decomm::DecommInst;
enum buildtype_t { BUILD = 1, DECOMM = 2};


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
DecommInst::DecommInst(cyclus::Context* ctx)
    : cyclus::Institution(ctx) {};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
DecommInst::~DecommInst() {}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void DecommInst::Decommission(Agent* parent) {
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void DecommInst::Build(Agent* parent) {
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int DecommInst::NToBuild(double avail) {
  // convert material availability to a number of facilities to build.
  int n = 0;
  if (DecisionLogic(avail)) {
    switch (buildtype) {
    case DECOMM :
      n -= 1;
      break;
    case BUILD :
      n += 1;
      break;
    default :
      throw cyclus::ValueError("Incorrect buildtype: "\
          "The options are 'decommission' or 'build'.");
    }
  } 
  // need some logic to decrement avail.
  
  return n;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
double DecommInst::MaterialAvailable(cyclus::toolkit::Commodity commod){
  // use the commodityproducermanager to determine material available
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void DecommInst::EnterNotify(){
  /// enter the simulation and register any children present
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void DecommInst::BuildNotify(Agent* m){
  /// register a new child
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void DecommInst::DecomNotify(Agent* m){
  /// unregister a decommissioned child
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Register_(cyclus::Agent* agent){
  /// register a child
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Unregister_(cyclus::Agent* agent){
/// unregister a child
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool DecisionLogic(double avail){
  bool d = false;
  return d;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
extern "C" cyclus::Agent* ConstructDecommInst(cyclus::Context* ctx) {
  return new DecommInst(ctx);
}
