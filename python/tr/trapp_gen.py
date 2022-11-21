# This module facilitates the generation of tr DAQModules within tr apps


# Set moo schema search path                                                                              
from dunedaq.env import get_moo_model_path
import moo.io
moo.io.default_load_path = get_moo_model_path()

# Load configuration types                                                                                
import moo.otypes
moo.otypes.load_types("tr/trsender.jsonnet")

import dunedaq.tr.trsender as trsender

from daqconf.core.app import App, ModuleGraph
from daqconf.core.daqmodule import DAQModule
#from daqconf.core.conf_utils import Endpoint, Direction

def get_tr_app(nickname, number_of_run = 1234, index_of_file = 0, number_of_trigger = 1, size_of_data = 1000, subsystem_type = "Recorded_data",
        subdetector_type = "HD_TPC", fragment_type = "WIB", number_of_elements = 10, n_wait_ms=100, host = "localhost"):
    """
    Here the configuration for an entire daq_application instance using DAQModules from tr is generated.
    """

    modules = []
    modules += [DAQModule(name="ts", plugin="TrSender", conf=trsender.Conf(runNumber=number_of_run, fileIndex=index_of_file, triggerCount = number_of_trigger,
     dataSize = size_of_data, stypeToUse=subsystem_type, dtypeToUse = subdetector_type, ftypeToUse=fragment_type,
      elementCount = number_of_elements, waitBetweenSends = n_wait_ms))]
    modules += [DAQModule(name="r", plugin="Receiver")]


    mgraph = ModuleGraph(modules)
    mgraph.connect_modules("ts.output", "r.input", "trigger_record", 10)
    tr_app = App(modulegraph = mgraph, host = host, name = nickname)

    return tr_app
