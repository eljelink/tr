

# This is a skeleton CMakeLists.txt file, auto-generated on
# Wed Nov 16 13:37:15 CET 2022.  The developer(s) of this package should delete
# this comment as well as adding dependent targets, packages,
# etc. specific to the package. For details on how to write a package,
# please see
# https://dune-daq-sw.readthedocs.io/en/latest/packages/daq-cmake/

cmake_minimum_required(VERSION 3.12)
project(tr VERSION 0.0.0)

find_package(daq-cmake REQUIRED)

daq_setup_environment()


find_package(logging REQUIRED)
find_package(ers REQUIRED)
find_package(HighFive REQUIRED)
find_package(daqdataformats REQUIRED)
find_package(detdataformats REQUIRED)
find_package(detchannelmaps REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(hdf5libs REQUIRED)
find_package(cetlib REQUIRED)   # Uses the daq-buildtools/cmake/Findcetlib.cmake
find_package(Boost COMPONENTS iostreams unit_test_framework REQUIRED)
find_package(appfwk REQUIRED)
find_package(opmonlib REQUIRED)
find_package(iomanager REQUIRED)
find_package(daqconf REQUIRED)

##############################################################################


# See https://dune-daq-sw.readthedocs.io/en/latest/packages/daq-cmake/#daq_codegen

daq_codegen(trsender.jsonnet TEMPLATES Structs.hpp.j2 Nljs.hpp.j2)
daq_codegen(trsenderinfo.jsonnet DEP_PKGS opmonlib TEMPLATES opmonlib/InfoStructs.hpp.j2 opmonlib/InfoNljs.hpp.j2)
daq_codegen(receiverinfo.jsonnet DEP_PKGS opmonlib TEMPLATES opmonlib/InfoStructs.hpp.j2 opmonlib/InfoNljs.hpp.j2)

##############################################################################
# Main library
daq_add_library (LINK_LIBRARIES stdc++fs ers::ers hdf5libs::hdf5libs appfwk::appfwk HighFive daqdataformats::daqdataformats detdataformats::detdataformats detchannelmaps::detchannelmaps logging::logging nlohmann_json::nlohmann_json ${CETLIB} ${CETLIB_EXCEPT})

##############################################################################


# See https://dune-daq-sw.readthedocs.io/en/latest/packages/daq-cmake/#daq_add_plugin

daq_add_plugin(TrSender duneDAQModule LINK_LIBRARIES tr) # Replace appfwk library with a more specific library when appropriate
daq_add_plugin(Receiver duneDAQModule LINK_LIBRARIES tr) # Replace appfwk library with a more specific library when appropriate

##############################################################################

daq_install()

