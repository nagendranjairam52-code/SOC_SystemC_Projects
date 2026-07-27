#include "interface.hpp"
class OSPI :sc_module, tlm::tlm_bw_transport_if<>
{
public:
	
	tlm::tlm_initiator_socket<> initiator_socket;  //initiator socket to send transaction to flash module
	//Always use sc_has_process if sc_ctor is used only for declaration but not for registration of process( SC_THREAD(func())
	// SC_CTOR(OSPI){ SC_THREAD(ddr_opr);} in ospi.cpp is there means, it will take care of registration of process
	//Still SC_has_process should be used with or without sc_ctor
	//compiler should support either sc_ctor with registration or sc_has_process
	//SC_HAS_PROCESS(OSPI);
	/*OSPI(sc_module_name name) : sc_module(name)
	{
		SC_THREAD(ddr_opr);
	};*/
	sc_event ospi_ev;
	SC_CTOR(OSPI) : initiator_socket("initiator_socket")
	{
		initiator_socket.bind(*this);   // registers BW interface
		// It is registering processes to the systemc kernel
		SC_THREAD(ddr_opr);            //include "/vmg" in additional options of all options tab under c++ in properties of the project
	};
private:
	void ddr_opr();
	// ---------- BW INTERFACE (REQUIRED) ----------
	tlm::tlm_sync_enum nb_transport_bw(
		tlm::tlm_generic_payload& trans,
		tlm::tlm_phase& phase,
		sc_core::sc_time& delay);

	void invalidate_direct_mem_ptr(
		sc_dt::uint64,
		sc_dt::uint64);
};