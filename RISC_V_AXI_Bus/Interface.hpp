#pragma once
#include <systemc>
#include <tlm.h>
#include <array>
#include <unordered_map>
using namespace sc_core;
using namespace std;
enum trans_type : int
{
	READ,
	WRITE
};
struct cpu_trans {
	uint32_t address;
	uint32_t *data;
	trans_type type;
};
struct riscv_instruction {
	uint8_t opcode;
	uint8_t rs1;
	uint8_t rs2;
	uint8_t rd;
	uint8_t funct3;               //funct3 and 7 are subopcodes
	uint8_t funct7;
	uint32_t alu_result;
	uint32_t mem_result;
};
enum burst_type : int
{
	FIXED,          //base_address wont change, all beats will be accessed to the same address .ex: useful for writing to a FIFO/peripheral register
	INCR,           //base_address will be updated to the next address for each beat, the address of the first beat is the base_address  .ex: useful for accessing memory
	WRAP           //base_address will be updated to the next address for each beat, the address of the first beat is the base_address, but when the address reaches the boundary of the burst length, it will wrap around to the initial base_address. ex: useful for accessing cache lines (when cache boundary reaches, it jumps to first base address again(first cache line)
};
/*struct axi_write_addr
{
	sc_signal<uint32_t> AWADDR;
	sc_signal<uint8_t> AWLEN;
	sc_signal<uint8_t> AWSIZE;
	sc_signal<burst_type> AWBURST;
	sc_signal<uint8_t> AWID;
	sc_signal<bool> AWVALID;
	sc_signal<bool> AWREADY;
};
struct axi_write_data
{
	sc_signal<uint32_t> WDATA;
	sc_signal<uint8_t> WSTRB;          //Write strobe, indicates which byte lanes are valid in the write data bus (like byte enable mask). For example, if WSTRB is 0b1111, it means all 4 bytes of WDATA are valid; if WSTRB is 0b0011, it means only the lower 2 bytes of WDATA are valid.
	sc_signal<uint8_t> WLAST;
	sc_signal<uint8_t> WVALID;
	sc_signal<uint8_t> WREADY;
};
struct axi_write_resp
{
	sc_signal<uint8_t> BRESP;
	sc_signal<bool> BVALID;
	sc_signal<bool> BREADY;
	sc_signal<uint8_t> BID;
};
struct axi_read_addr
{
	sc_signal<uint32_t> ARADDR;
	sc_signal<uint8_t> ARLEN;
	sc_signal<uint8_t> ARSIZE;
	sc_signal<burst_type> ARBURST;
	sc_signal<bool> ARVALID;
	sc_signal<bool> ARREADY;
	sc_signal<uint8_t> ARID;
};
struct axi_read_data
{
	sc_signal<uint32_t> RDATA;
	sc_signal<bool> RRESP;
	sc_signal<bool> RLAST;
	sc_signal<bool> RVALID;
	sc_signal<bool> RREADY;
	sc_signal<uint8_t> RID;
}; */
sc_signal<cpu_trans> cpu_to_axi_signal;