#include "Cpu.hpp"
void Cpu::fill_mem()
{
	mem[0] = 0x007302B3;
}
uint32_t* Cpu::fetch_instruction(uint32_t* pc)
{
	pc = &mem[0];
	return pc;
}
riscv_instruction Cpu::decode(uint32_t raw_bytes)
{
	riscv_instruction instr;
	instr.funct7 = raw_bytes & 0xEF000000;
	instr.rs2 = raw_bytes & 0x01F00000;
	instr.rs1 = raw_bytes & 0x000F8000;
	instr.funct3 = raw_bytes & 0x00007000;
	instr.rd = raw_bytes & 0x00000F800;
	instr.opcode = raw_bytes & 0x0000007F;
	return instr;
}
void Cpu::execute(riscv_instruction& instr)
{
	if (instr.opcode == 0x6C)
	{
		cout << "instr belongs to register - register operation" << endl;
		//Arithmetic Logic Unit
		//ADD operation
		if (instr.funct3 == 0x0 && instr.funct7 == 0x0) 
		{
			instr.alu_result = instr.rs1 + instr.rs2;
		}
	}
	//LOAD operation
	if (instr.opcode == 0x3)
	{
		instr.alu_result = instr.rs1;                 //register1 has address
	}
	//STORE operation
	if (instr.opcode == 0x23)
	{
		instr.alu_result = instr.rs1;
	}
}
void Cpu::mem_acess(riscv_instruction& instr)
{
		cout << "mem access stage is triggered" << endl;
		//ADD opr
		if (instr.opcode == 0x6C)
		{
			cout << "register - register operation" << endl;
			return;
		}
		//LOAD operation
		if (instr.opcode == 0x3)
		{
			instr.mem_result = mem[(instr.alu_result)/4];             //divided by 4 as to calculate index...register2 has value now
		}
		//STORE operation
		if (instr.opcode == 0x23)
		{
			mem[(instr.alu_result) / 4] = instr.rs2;          
		}
}
void Cpu::write_back(riscv_instruction& instr)
{
	cout << "write back stage is triggered" << endl;
	//ADD opr
	if (instr.opcode == 0x6C)
	{
		cout << "register - register operation" << endl;
		return;
	}
	//LOAD operation
	if (instr.opcode == 0x3)
	{
		instr.rd = instr.mem_result;            
	}
	//STORE operation
	if (instr.opcode == 0x23)
	{
		instr.rd = instr.alu_result;               //just saving address in destination register as dummy
	}
}
void Cpu::pipelining()
{   
	fill_mem();
	uint32_t* pc = nullptr;
	fetch_instruction(pc);
	uint32_t raw_bytes = *pc;
	pc += 4;
	riscv_instruction instr = decode(raw_bytes);
	execute(instr);
	mem_acess(instr);
	write_back(instr);

}
void Cpu::send_write_trans()
{
	cpu_trans trans;
	int n = 10;
	trans.data = (new uint32_t[n]);
	trans.address = 0x10000000;
	trans.data[0] = 0xAD;
	trans.type = WRITE;
	sc_time delay = sc_time(10, SC_NS);
	while (true)
	{
		tlm::tlm_generic_payload write_payload;
		if (trans.type == WRITE)
		{
			write_payload.set_command(tlm::TLM_WRITE_COMMAND);
		}
		write_payload.set_data_ptr((unsigned char*)(&trans));
		cout << "Cpu is writing data through AXI_Bus at time " << sc_time_stamp() << endl;
		cpu_to_axi_out->b_transport(trans, delay);
		wait(2, SC_NS);
	}
}
void Cpu::send_read_trans()
{
	cpu_trans trans;
	trans.address = 0x10000000;
	trans.data[0] = 0xDE;
	trans.type = READ;
	sc_time delay = sc_time(10, SC_NS);
	while (true)
	{
		tlm::tlm_generic_payload read_payload;
		if(trans.type == READ)
		{
			read_payload.set_command(tlm::TLM_READ_COMMAND);
		}
		read_payload.set_data_ptr((unsigned char*)(&trans));
		cout << "Cpu is reading data through AXI_Bus at time " << sc_time_stamp() << endl;
		cpu_to_axi_out->b_transport(trans, delay);
		wait(2, SC_NS);
	}
}