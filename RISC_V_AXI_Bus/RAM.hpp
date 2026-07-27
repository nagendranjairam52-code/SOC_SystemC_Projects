#include "Interface.hpp"
constexpr uint32_t RAM_REGION_SIZE = 1024; //1KB of RAM region, which means the address will wrap around when it reaches 1024 bytes (256 words)
SC_MODULE(RAM)
{
	//Write Address Channel from AXI
	sc_in<uint32_t> AWADDR_in;
	sc_in<uint8_t> AWLEN_in;
	sc_in<uint8_t> AWSIZE_in;
	sc_in<burst_type> AWBURST_in;
	sc_in<uint8_t> AWID_in;
	sc_in<bool> AWVALID_in;
	sc_out<bool> AWREADY_out;              //Slave should be ready (not be busy) to accept response. So, Slave sends that
	//Write Data Channel from AXI
	sc_in<uint32_t> WDATA_in;
	sc_in<uint8_t> WSTRB_in;
	sc_in<uint8_t> WLAST_in;
	sc_in<uint8_t> WVALID_in;
	sc_out<uint8_t> WREADY_out;           //Slave should be ready (not be busy) to accept response. So, Slave sends that
	//Write Response Channel from AXI
	sc_out<uint8_t> BRESP_out;
	sc_out<bool> BVALID_out;
	sc_in<bool> BREADY_in;                //Master should be ready (not be busy) to accept response. So, Master sends that
	sc_out<uint8_t> BID_out;
	//Read Address Channel from AXI
	sc_in<uint32_t> ARADDR_in;
	sc_in<uint8_t> ARLEN_in;
	sc_in<uint8_t> ARSIZE_in;
	sc_in<burst_type> ARBURST_in;
	sc_in<bool> ARVALID_in;
	sc_out<uint8_t> ARREADY_out;         //Slave should be ready (not be busy) to accept response. So, Slave sends that
	sc_in<uint8_t> ARID_in;
	//Read Data Channel from AXI
	sc_out<uint32_t> RDATA_out;
	sc_out<uint8_t> RRESP_out;
	sc_out<bool> RLAST_out;
	sc_out<bool> RVALID_out;
	sc_in<bool> RREADY_in;               //Master should be ready (not be busy) to accept response. So, Master sends that
	sc_out<uint8_t> RID_out;
	SC_CTOR(RAM)
	{
		SC_THREAD(receive_trans);
		SC_THREAD(send_resp);
	}
private:
	uint32_t ram[4096];             //16KB of RAM (4K words, each word is 4 bytes)
	void receive_trans();
	void send_resp();
};