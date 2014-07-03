#ifndef CYCLUS_DECOMMS_DECOMM_INST_H_
#define CYCLUS_DECOMMS_DECOMM_INST_H_

#include <string>

#include "cyclus.h"

namespace decomm {

typedef enum buildtype_t { 
  BUILD = 1, 
  DECOMM = 2
} buildtype_t;

typedef std::map<int, std::vector<std::string> > DecommSched;
/// @class DecommInst
///
/// This Institution is specifically designed for market-driven decommissioning
/// of reactors. It utlizes manager mixin classes to assist in this task. It was
/// created for the specific purpose of runing the fco code-to-code comparison.
/// However, it was designed to be sufficiently generic for general use.
/// 
/// The DecommInst class inherits from the Institution class and is dynamically
/// loaded by the Agent class when requested.
///
/// @section intro Introduction
/// The DecommInst decommissions facilities of a particular type if and when a
/// material criteria occurs in the markets.
///
/// @section agentparams Agent Parameters
/// The facilities that are governed by this institution, the material availability 
///
/// @section optionalparams Optional Parameters
/// Place a description of the optional input parameters to define the
/// agent implementation.
///
/// @section detailed Detailed Behavior
/// Place a description of the detailed behavior of the agent. Consider
/// describing the behavior at the tick and tock as well as the behavior
/// upon sending and receiving materials and messages.
class DecommInst : public cyclus::Institution,
  public cyclus::toolkit::CommodityProducerManager,
  public cyclus::toolkit::Builder {
 public:
  /// Default constructor
  DecommInst(cyclus::Context* ctx);

  /// every agent should be destructable
  virtual ~DecommInst();

  /// The Prime Directive
  /// Generates code that handles all input file reading and restart operations
  /// (e.g., reading from the database, instantiating a new object, etc.).
  /// @warning The Prime Directive must have a space before it! (A fix will be
  /// in 2.0 ^TM)

  #pragma cyclus


  #pragma cyclus note {"doc": "An institution that owns, and operates facilities "\
                              "decommissioning them based on a material "\
                               "availability rule in the input file."}

  /// enter the simulation and register any children present
  virtual void EnterNotify();

  /// register a new child
  virtual void BuildNotify(Agent* m);

  /// unregister a child
  virtual void DecomNotify(Agent* m);
  
  /// decommission a child
  void Decommission(Agent* m);

  /// decommission a child
  void Build(Agent* m);

  /// return the number to build based on availability
  int NToBuild(double avail);

  /// return the material available in the commodity of interest
  double MaterialAvailable(cyclus::toolkit::Commodity commod);

  /// Conduct action based on rule?
  bool DecisionLogic(double avail);

 private:
  /// register a child
  void Register_(cyclus::Agent* agent);

  /// unregister a child
  void Unregister_(cyclus::Agent* agent);

  #pragma cyclus var {"tooltip": "facility prototypes", \
                      "doc": "a facility to be managed by the institution"}
  std::vector<std::string> prototypes;

  buildtype_t buildtype;
};

}  // namespace decomm

#endif  // CYCLUS_DECOMMS_DECOMM_INST_H_


