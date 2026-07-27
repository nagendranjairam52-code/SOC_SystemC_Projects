#include "AXI_Bus.hpp"
#include "Cpu.hpp"
#include "RAM.hpp"
int sc_main(int agrc, char* argv[]) {
	sc_clock clk("clk", 1, 0.5, 0, true);
	sc_signal<uint32_t> AWADDR, WDATA, ARADDR, RDATA;
	sc_signal<uint8_t> AWLEN, AWSIZE, AWID, WSTRB, WLAST, WVALID, WREADY, BRESP, BID, ARLEN, ARSIZE, ARREADY, ARID, RRESP, RID;
	sc_signal<burst_type> AWBURST, ARBURST, ARBURST;
	sc_signal<bool> AWVALID, AWREADY, BVALID, BREADY, ARADDR, ARVALID, RLAST, RVALID, RREADY;
	//Module Instantiation
	AXI_Bus axi_bus("axi_bus");
	Cpu cpu("cpu");
	RAM ram("ram");
	//Port Binding
	cpu.clk(clk);
	cpu.cpu_to_axi_out(cpu_to_axi_signal);
	axi_bus.cpu_to_axi_in(cpu_to_axi_signal);
	axi_bus.AWADDR_out(AWADDR);
	ram.AWADDR_in(AWADDR);
	axi_bus.AWLEN_out(AWLEN);
	ram.AWLEN_in(AWLEN);
	axi_bus.AWSIZE_out(AWSIZE);
	ram.AWSIZE_in(AWSIZE);
	axi_bus.AWBURST_out(AWBURST);
	ram.AWBURST_in(AWBURST);
	axi_bus.AWID_out(AWID);
	ram.AWID_in(AWID);
	axi_bus.AWVALID_out(AWVALID);
	ram.AWVALID_in(AWVALID);
	axi_bus.AWREADY_in(AWREADY);
	ram.AWREADY_out(AWREADY);
	axi_bus.WDATA_out(WDATA);
	ram.WDATA_in(WDATA);
	axi_bus.WSTRB_out(WSTRB);
	ram.WSTRB_in(WSTRB);
	axi_bus.WLAST_out(WLAST);
	ram.WLAST_in(WLAST);
	axi_bus.WVALID_out(WVALID);
	ram.WVALID_in(WVALID);
	axi_bus.WREADY_in(WREADY);
	ram.WREADY_out(WREADY);
	axi_bus.BRESP_in(BRESP);
	ram.BRESP_out(BRESP);
	axi_bus.BVALID_in(BVALID);
	ram.BVALID_out(BVALID);
	axi_bus.BREADY_out(BREADY);
	ram.BREADY_in(BREADY);
	axi_bus.BID_in(BID);
	ram.BID_out(BID);
	axi_bus.ARADDR_out(ARADDR);
	ram.ARADDR_in(ARADDR);
	axi_bus.ARLEN_out(ARLEN);
	ram.ARLEN_in(ARLEN);
	axi_bus.ARSIZE_out(ARSIZE);
	ram.ARSIZE_in(ARLEN);
	axi_bus.ARBURST_out(ARBURST);
	ram.ARBURST_in(ARBURST);
	axi_bus.ARVALID_out(ARVALID);
	ram.ARVALID_in(ARVALID);
	axi_bus.ARREADY_in(ARREADY);
	ram.ARREADY_out(ARREADY);
	axi_bus.ARID_out(ARID);
	ram.ARID_in(ARID);
	axi_bus.RDATA_in(RDATA);
	ram.RDATA_out(RDATA);
	axi_bus.RRESP_in(RRESP);
	ram.RRESP_out(RRESP);
	axi_bus.RLAST_in(RLAST);
	ram.RLAST_out(RLAST);
	axi_bus.RVALID_in(RVALID);
	ram.RVALID_out(RVALID);
	axi_bus.RREADY_out(RREADY);
	ram.RREADY_in(RREADY);
	axi_bus.RID_in(RID);
	ram.RID_out(RID);
	sc_start();
}