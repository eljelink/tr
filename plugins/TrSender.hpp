/**
 * @file TrSender.hpp
 *
 * Developer(s) of this DAQModule have yet to replace this line with a brief description of the DAQModule.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TR_PLUGINS_TRSENDER_HPP_
#define TR_PLUGINS_TRSENDER_HPP_

#include "appfwk/DAQModule.hpp"
#include "iomanager/Sender.hpp"
#include "iomanager/ConnectionId.hpp"
#include "ers/Issue.hpp"
#include "utilities/WorkerThread.hpp"
#include "tr/trsender/Structs.hpp"

#include "daqdataformats/Fragment.hpp"
#include "daqdataformats/TimeSlice.hpp"
#include "daqdataformats/TriggerRecord.hpp"
#include "detdataformats/DetID.hpp"

#include <atomic>
#include <memory>
#include <vector>
#include <limits>
#include <thread>
#include <string>
#include <fstream>
#include <iostream>
#include <utility>

//using namespace dunedaq::hdf5libs;
using namespace dunedaq::daqdataformats;
using namespace dunedaq::detdataformats;

namespace dunedaq::tr {

class TrSender : public dunedaq::appfwk::DAQModule
{
public:
  explicit TrSender(const std::string& name);

  void init(const data_t&) override;
  void get_info(opmonlib::InfoCollector&, int /*level*/) override;

  TrSender(const TrSender&) = delete;
  TrSender& operator=(const TrSender&) = delete;
  TrSender(TrSender&&) = delete;
  TrSender& operator=(TrSender&&) = delete;

  ~TrSender() = default;

private:
//Commands
  void do_conf(const nlohmann::json& obj);
  void do_start(const nlohmann::json& obj);
  void do_stop(const nlohmann::json& obj);
  void do_scrap(const nlohmann::json& obj);


//Threading
dunedaq::utilities::WorkerThread thread_;
void do_work(std::atomic<bool>&);


//Configuration
int runNumber;
int fileIndex;
int triggerCount;
int dataSize;
SourceID::Subsystem stypeToUse;
DetID::Subdetector dtypeToUse;
FragmentType ftypeToUse;
int elementCount;
int waitBetweenSends;

/*  // Configuration
  // size_t m_sleep_msec_while_running;
  std::chrono::milliseconds m_queue_timeout;
  dunedaq::daqdataformats::run_number_t m_run_number;
  daqdataformats::SourceID m_sourceid;
  uint64_t m_time_tick_diff; // NOLINT (build/unsigned)
  uint64_t m_frame_size;     // NOLINT (build/unsigned)
  uint64_t m_response_delay; // NOLINT (build/unsigned)
  daqdataformats::FragmentType m_fragment_type;
  std::string m_timesync_topic_name;
  uint32_t m_pid_of_current_process; // NOLINT (build/unsigned)*/


std::chrono::milliseconds queueTimeout_;

std::shared_ptr<iomanager::SenderConcept<std::unique_ptr<daqdataformats::TriggerRecord>>> m_sender;
//std::map<daqdataformats::SourceID, std::shared_ptr<data_req_sender_t>> m_map_sourceid_connections; 
trsender::Conf cfg_;

// Statistic counters
std::atomic<int64_t> receivedConfigurationCount {0};
std::atomic<int> sentCount {0};
};

} // namespace dunedaq::tr

#endif // TR_PLUGINS_TRSENDER_HPP_
