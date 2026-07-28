#include "Interface.hpp"
struct AXI_Bus: public sc_module, public tlm::tlm_fw_transport_if<>
{
	tlm::tlm_target_socket<32, tlm::tlm_fw_transport_if<>, 1> cpu_to_axi_in;
	//Write Address Channel
	sc_out<uint32_t> AWADDR_out;
	sc_out<uint8_t> AWLEN_out;
	sc_out<uint8_t> AWSIZE_out;
	sc_out<burst_type> AWBURST_out;
	sc_out<uint8_t> AWID_out;
	sc_out<bool> AWVALID_out;
	sc_in<bool> AWREADY_in;
	//Write Data Channel
	sc_out<uint32_t> WDATA_out;
	sc_out<uint8_t> WSTRB_out;
	sc_out<uint8_t> WLAST_out;
	sc_out<uint8_t> WVALID_out;
	sc_in<uint8_t> WREADY_in;
	//Write Response Channel
	sc_in<uint8_t> BRESP_in;
	sc_in<bool> BVALID_in;
	sc_out<bool> BREADY_out;
	sc_in<uint8_t> BID_in;
	//Read Address Channel
	sc_out<uint32_t> ARADDR_out;
	sc_out<uint8_t> ARLEN_out;
	sc_out<uint8_t> ARSIZE_out;
	sc_out<burst_type> ARBURST_out;
	sc_out<bool> ARVALID_out;
	sc_in<uint8_t> ARREADY_in;
	sc_out<uint8_t> ARID_out;
	//Read Data Channel
	sc_in<uint32_t> RDATA_in;
	sc_in<uint8_t> RRESP_in;
	sc_in<bool> RLAST_in;
	sc_in<bool> RVALID_in;
	sc_out<bool> RREADY_out;
	sc_in<uint8_t> RID_in;
	sc_event trans_ev;
	sc_signal<cpu_trans*> cpu_signal;
	SC_CTOR(AXI_Bus) {
		SC_THREAD(Bus_adapter);
	}
private:
	void Bus_adapter();
	void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay);
};