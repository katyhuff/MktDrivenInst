INCLUDE_DIRECTORIES(${CYCLUS_CORE_INCLUDE_DIRS} ${CYCLUS_CORE_TEST_INCLUDE_DIR})
install_cyclus_standalone("DecommFacility" "decomm_facility" "decomm")
install_cyclus_standalone("DecommInst" "decomm_inst" "decomm")
install_cyclus_standalone("DecommRegion" "decomm_region" "decomm")