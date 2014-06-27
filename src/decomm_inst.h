#ifndef CYCLUS_DECOMMS_DECOMM_INST_H_
#define CYCLUS_DECOMMS_DECOMM_INST_H_

#include <string>

#include "cyclus.h"

namespace decomm {

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
class DecommInst : public cyclus::Institution {
 public:
  /// Constructor for DecommInst Class
  /// @param ctx the cyclus context for access to simulation-wide parameters
  explicit  DecommInst(cyclus::Context* ctx);

  /// every agent should be destructable
  virtual ~DecommInst();
  
  /// The Prime Directive
  /// Generates code that handles all input file reading and restart operations
  /// (e.g., reading from the database, instantiating a new object, etc.).
  /// @warning The Prime Directive must have a space before it! (A fix will be
  /// in 2.0 ^TM)
  
  #pragma cyclus

  #pragma cyclus note {"doc": "A decomm institution is provided as a " \
                              "skeleton for the design of new " \
                              "institution agents."}

  /// every agent should be able to print a verbose description
  virtual std::string str();

  // and away we go!
};

}  // namespace decomm

#endif  // CYCLUS_DECOMMS_DECOMM_INST_H_




// Deployinst.h
#ifndef _DEPLOYINST_H
#define _DEPLOYINST_H

#include "cyclus.h"

#include <utility>
#include <set>
#include <map>

namespace cycamore {

typedef std::map<int, std::vector<std::string> > BuildSched;

///  @class DeployInst
///  The DeployInst class inherits from the Institution
///  class and is dynamically loaded by the Agent class when requested.
///
///  This agent implements a simple institution agent that deploys
///  specific facilities as defined explicitly in the input file.
class DeployInst : public cyclus::Institution {
 public:
  DeployInst(cyclus::Context* ctx);

  virtual ~DeployInst();

  #pragma cyclus decl clone

  #pragma cyclus decl schema

  #pragma cyclus decl infiletodb

  #pragma cyclus decl initfromdb

  #pragma cyclus decl initfromcopy

  #pragma cyclus decl snapshot

  #pragma cyclus def annotations

  #pragma cyclus note {"doc": "An institution that owns, operates, and " \
                              "deploys facilities manually defined in " \
                              "the input file."}

  virtual void Build(cyclus::Agent* parent);

 protected:
  /// a collection of orders to build
  BuildSched build_sched_;
};
