#include "decomm_inst.h"

using decomm::DecommInst;
enum buildtype_t { BUILD = 1, DECOMM = 2};


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
DecommInst::DecommInst(cyclus::Context* ctx)
    : cyclus::Institution(ctx),
    target_commod(""),
    target_fac(""),
    num_to_build(0){
      sdmanager_ = cyclus::toolkit::SupplyDemandManager(); 
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
DecommInst::~DecommInst() {}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void DecommInst::Tick(){
  using cyclus::toolkit::Commodity;
  
  Commodity commod = Commodity(target_commod);
  int time = context()->time();
//  double demand = sdmanager_.Demand(commod, time);
  double demand = 2;
  double supply = sdmanager_.Supply(commod);
//  double unmetdemand = demand - supply;
//
//  LOG(cyclus::LEV_INFO3, "DcmIst") << "DecommInst: " << prototype()
//                                 << " at time: " << time
//                                 << " has the following values regaring "
//                                 << " commodity: " << target_commod;
//  LOG(cyclus::LEV_INFO3, "DcmIst") << "  *demand = " << demand;
//  LOG(cyclus::LEV_INFO3, "DcmIst") << "  *supply = " << supply;
//  LOG(cyclus::LEV_INFO3, "DcmIst") << "  *unmetdemand = " << unmetdemand;
//
//  int n = NToBuild(unmetdemand);
//
//  if( n < 0 ) {
//    Decommission(n);
//  } else if (n > 0) {
//    Build(n);
//  }
  cyclus::Institution::Tick();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void DecommInst::EnterNotify(){
  /// enter the simulation and register any children present
  cyclus::Institution::EnterNotify();
  std::set<cyclus::Agent*>::iterator it;
  for (it = cyclus::Agent::children().begin();
       it != cyclus::Agent::children().end();
       ++it) {
    Agent* a = *it;
    Register_(a);
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void DecommInst::BuildNotify(Agent* m){
  /// register a new child
  Register_(m);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void DecommInst::DecomNotify(Agent* m){
  /// unregister a decommissioned child
  Unregister_(m);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void DecommInst::Decommission(Agent* to_decomm) {
  context()->SchedDecom(to_decomm, context()->time() + 1);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void DecommInst::Decommission(int n){
  n = abs(n);
  std::set<cyclus::Agent*>::iterator next;
  for (int i = 0; i < n; ++i ){
    next = target_facs.begin();
    target_facs.erase(next);
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void DecommInst::Build(int n) {
  for( int i = 0; i != n; ++i ){
    context()->SchedBuild(this, target_fac, context()->time() + 1);
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int DecommInst::NToBuild(double avail) {
  // convert material availability to a number of facilities to build.
  int n = 0;
  if (DecisionLogic(avail)) {
    n += num_to_build;
  }
  // need some logic to decrement avail.
  
  return n;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
double DecommInst::MaterialAvailable(cyclus::toolkit::Commodity commod){
  // use the commodityproducermanager to determine material available
  double n = 0;
  return n;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void DecommInst::Register_(cyclus::Agent* agent){
  /// register a child
  using cyclus::toolkit::CommodityProducerManager;
  using cyclus::toolkit::Builder;

  // if it's a commodity producer manager register it that way
  CommodityProducerManager* cpm_cast =
      dynamic_cast<CommodityProducerManager*>(agent);
  if (cpm_cast != NULL) {
    LOG(cyclus::LEV_INFO3, "DcmIst") << "Registering agent "
                                   << agent->prototype() << agent->id()
                                   << " as a commodity producer manager.";
    sdmanager_.RegisterProducerManager(cpm_cast);
  }

  // if it's a builder, register it that way
  Builder* b_cast = dynamic_cast<Builder*>(agent);
  if (b_cast != NULL) {
    LOG(cyclus::LEV_INFO3, "DcmIst") << "Registering agent "
                                   << agent->prototype() << agent->id()
                                   << " as a builder.";
    buildmanager_.Register(b_cast);
  }

  // if it's one of the facilities to decommision, register that
  cyclus::Facility* fac_cast = dynamic_cast<cyclus::Facility*>(agent);
  if (fac_cast != NULL && agent->prototype() == target_fac) {
    LOG(cyclus::LEV_INFO3, "DcmIst") << "Registering agent "
                                   << agent->prototype() << agent->id()
                                   << " as a target facility.";
    target_facs.insert(fac_cast);
  }

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void DecommInst::Unregister_(cyclus::Agent* agent){
/// unregister a child
  using cyclus::toolkit::CommodityProducerManager;
  using cyclus::toolkit::Builder;

  CommodityProducerManager* cpm_cast =
    dynamic_cast<CommodityProducerManager*>(agent);
  if (cpm_cast != NULL){
    sdmanager_.UnregisterProducerManager(cpm_cast);
  }

  Builder* b_cast = dynamic_cast<Builder*>(agent);
  if (b_cast != NULL){
    buildmanager_.Unregister(b_cast);
  }

  cyclus::Facility* fac_cast = dynamic_cast<cyclus::Facility*>(agent);
  if (fac_cast != NULL && agent->prototype() == target_fac){
    target_facs.erase(agent); 
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool DecommInst::DecisionLogic(double avail){
  bool d = false;
  return d;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
extern "C" cyclus::Agent* ConstructDecommInst(cyclus::Context* ctx) {
  return new DecommInst(ctx);
}
