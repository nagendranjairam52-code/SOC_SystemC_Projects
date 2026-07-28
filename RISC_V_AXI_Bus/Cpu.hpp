#include "Interface.hpp"
struct Cpu:public sc_module, public tlm::tlm_fw_transport_if<>
{
    tlm::tlm_initiator_socket<32,tlm::tlm_fw_transport_if<>, 1> cpu_to_axi_out;
	sc_in<bool> clk;
	SC_CTOR(Cpu)
	{
		SC_THREAD(pipelining);
		SC_THREAD(send_write_trans);
		sensitive << clk.pos();
		SC_THREAD(send_read_trans);
		sensitive << clk.neg();
	}
private:
	void send_write_trans();
	void send_read_trans();
	uint32_t* fetch_instruction(uint32_t* pc);
	riscv_instruction decode(uint32_t bytes);
	void execute(riscv_instruction& alu_opr);
	void mem_acess(riscv_instruction& mem_val);
	void write_back(riscv_instruction& wb);
	void pipelining();
	void fill_mem();
	std::array<uint32_t, 16> mem{};
};