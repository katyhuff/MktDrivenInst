#ifndef CYCLUS_MKTDRIVEN_MKTDRIVENINST_H_
#define CYCLUS_MKTDRIVEN_MKTDRIVENINST_H_

#include <string>

#include "cyclus.h"

namespace mktdriveninst {

typedef std::map<int, std::vector<std::string> > DecommSched;
/// @class MktDrivenInst
///
/// This Institution is specifically designed for market-driven 
/// building/decommissioning of facilities. It utlizes manager mixin classes to 
/// assist in this task, and was created for the specific purpose of runing the 
/// fco code-to-code comparison. However, it was designed to be sufficiently 
/// generic for general use.
/// 
/// The MktDrivenInst class inherits from the Institution class and is dynamically
/// loaded by the Agent class when requested.
///
/// @section intro Introduction
/// The MktDrivenInst builds/decommissions facilities of a particular type if and when a
/// material criteria occurs in the markets.
///
/// @section agentparams Agent Parameters
/// The facilities that are governed by this institution
/// the target facility to build or decommission
/// the number to build or decommission when the logic is triggered
/// the target commodity on which to base the logic
/// the amount of the target commodity that will trigger the logic
///
/// @section optionalparams Optional Parameters
/// Place a description of the optional input parameters to define the
/// agent implementation.
///
/// @section detailed Detailed Behavior
/// Place a description of the detailed behavior of the agent. Consider
/// describing the behavior at the tick and tock as well as the behavior
/// upon sending and receiving materials and messages.
class MktDrivenInst : public cyclus::Institution,
  public cyclus::toolkit::CommodityProducerManager,
  public cyclus::toolkit::Builder {
 public:
  /// Default constructor
  MktDrivenInst(cyclus::Context* ctx);

  /// every agent should be destructable
  virtual ~MktDrivenInst();

  /// The Prime Directive
  /// Generates code that handles all input file reading and restart operations
  /// (e.g., reading from the database, instantiating a new object, etc.).
  /// @warning The Prime Directive must have a space before it! (A fix will be
  /// in 2.0 ^TM)

  #pragma cyclus


  #pragma cyclus note {"doc": "An institution that owns, and operates facilities "\
                              "decommissioning them based on a material "\
                               "availability rule in the input file."}

  /// on the tick, the institution checks the supply and demand
  /// of the target commodity. Then, based on the decision logic,
  /// determines the number of facilities that need to have been 
  /// built/mktdriveninstissioned 
  virtual void Tick();

  /// enter the simulation and register any children present
  virtual void EnterNotify();

  /// register a new child
  virtual void BuildNotify(Agent* m);

  /// unregister a child
  virtual void DecomNotify(Agent* m);
  
  /// mktdriveninstission a child
  void Decommission(Agent* m);

  /// mktdriveninstission a number of children
  void Decommission(int n);

  /// schedule the builds for a number of children
  void Build(int n);

  /// return the number to build based on availability
  int NToBuild(double avail);
  
  /// return the material available in the commodity of interest
  double MaterialAvailable(cyclus::toolkit::Commodity commod);

  /// Conduct action based on rule?
  bool DecisionLogic(double avail);
  
  /// This is a manager that keeps track of supply and demand for the commodity
  /// of interest
  inline cyclus::toolkit::SupplyDemandManager* sdmanager() {
    return &sdmanager_;
  }

  inline std::string target_fac_(){return target_fac;};

  inline int num_to_build_(){return num_to_build;};

  inline std::string target_commod_(){return target_commod;};

  inline std::vector<std::string> prototypes_(){return prototypes;};

  inline int n_built_(){return n_built;};

  inline double amt_req_(){return amt_req;};

 protected:
  /// register a child
  void Register_(cyclus::Agent* agent);

  /// unregister a child
  void Unregister_(cyclus::Agent* agent);

  /// a list of target facilities that can be mktdriveninstissioned by this inst
  std::set<cyclus::Agent*> target_facs;

  /// manager for building things
  cyclus::toolkit::BuildingManager buildmanager_;

  /// manager for Supply and demand
  cyclus::toolkit::SupplyDemandManager sdmanager_;

  int n_built;

  #pragma cyclus var {"tooltip": "facility prototype to build or mktdriveninstission", \
                      "doc": "a facility to be built or mktdriveninstissioned " \
                      "based on decision logic"}
  std::string target_fac;

  #pragma cyclus var {"tooltip": "number of facilities to build (negative "\
                      "to mktdriveninstision)", \
                      "doc": "number of facilities to build/mktdriveninst at a time."}
  int num_to_build;

  #pragma cyclus var {"tooltip": "the commodity on which to base the logic", \
                      "doc": "The commodity for which supply/demand determines "\
                      "builds/decommissionings."}
  std::string target_commod;

  #pragma cyclus var {"tooltip": "facility prototypes", \
                      "doc": "facilities to be managed by the institution"}
  std::vector<std::string> prototypes;


  #pragma cyclus var {"tooltip": "Amount of material required for decision logic", \
                      "doc": "Amount required for decision logic"}
  double amt_req;

  friend class MktDrivenInstTest;

};

}  // namespace mktdriveninst

#endif  // CYCLUS_MKTDRIVEN_MKTDRIVENINST_INST_H_


