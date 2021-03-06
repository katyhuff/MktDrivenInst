#include "mktdriveninst.h"

using mktdriveninst::MktDrivenInst;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
MktDrivenInst::MktDrivenInst(cyclus::Context* ctx)
    : cyclus::Institution(ctx),
    target_commod(""),
    target_fac(""),
    num_to_build(0),
    amt_req(0),
    n_built(0) {
    //  sdmanager_ = cyclus::toolkit::SupplyDemandManager(); 
    cyclus::Warn<cyclus::EXPERIMENTAL_WARNING>("the Market Driven Institution is experimental."); 
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
MktDrivenInst::~MktDrivenInst() {}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void MktDrivenInst::Tick(){
  using cyclus::toolkit::Commodity;
 
  Commodity commod = Commodity(target_commod);

  double mat_avail = MaterialAvailable(commod);

  LOG(cyclus::LEV_INFO3, "DcmIst") << "MktDrivenInst: " << prototype()
                                 << " at time: " << context()->time()
                                 << " has the following values regarding "
                                 << " commodity: " << target_commod;
  LOG(cyclus::LEV_INFO3, "DcmIst") << "  *mat_avail = " << mat_avail;

  int n = NToBuild(mat_avail);

  if( n < 0 ) {
    Decommission(n);
  } else if (n > 0) {
    Build(n);
  }

  n_built += n;
  cyclus::Institution::Tick();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void MktDrivenInst::EnterNotify(){
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
void MktDrivenInst::BuildNotify(Agent* m){
  /// register a new child
  Register_(m);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void MktDrivenInst::DecomNotify(Agent* m){
  /// unregister a decommissioned child
  Unregister_(m);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void MktDrivenInst::Decommission(Agent* to_decomm) {
  context()->SchedDecom(to_decomm, context()->time() + 1);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void MktDrivenInst::Decommission(int n){
  n = abs(n);
  std::set<cyclus::Agent*>::iterator next;
  for (int i = 0; i < n; ++i ){
    next = target_facs.begin();
    target_facs.erase(next);
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void MktDrivenInst::Build(int n) {
  for( int i = 0; i != n; ++i ){
    context()->SchedBuild(this, target_fac, context()->time() + 1);
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int MktDrivenInst::NToBuild(double avail) {
  // convert material availability to a number of facilities to build.
  int n = 0;
  if (DecisionLogic(avail)) {
    n += num_to_build;
  }
  // need some logic to decrement avail.
  
  return n;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
double MktDrivenInst::MaterialAvailable(cyclus::toolkit::Commodity commod){
  // use the commodityproducermanager to determine material available
  double amt = 0;
  double demand = n_built*amt_req;
  double supply = sdmanager_.Supply(commod);
  amt = supply - demand;
  return amt;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void MktDrivenInst::Register_(cyclus::Agent* agent){
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

  // if it's one of the facilities to decommission, register that
  cyclus::Facility* fac_cast = dynamic_cast<cyclus::Facility*>(agent);
  if (fac_cast != NULL && agent->prototype() == target_fac) {
    LOG(cyclus::LEV_INFO3, "DcmIst") << "Registering agent "
                                   << agent->prototype() << agent->id()
                                   << " as a target facility.";
    target_facs.insert(fac_cast);
  }

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void MktDrivenInst::Unregister_(cyclus::Agent* agent){
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
bool MktDrivenInst::DecisionLogic(double avail){
  bool d = false;
  if( avail >= amt_req) {
    d = true;
  }
  return d;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
extern "C" cyclus::Agent* ConstructMktDrivenInst(cyclus::Context* ctx) {
  return new MktDrivenInst(ctx);
}
