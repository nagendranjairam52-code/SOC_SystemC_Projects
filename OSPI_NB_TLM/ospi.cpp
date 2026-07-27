#include "ospi.hpp"
void OSPI::ddr_opr()
{
	while (true)
	{
		wait(ospi_ev);
		//stack allocation of transaction dies within the return of nb_transport and cant be queued in flash module, so using heap allocation for transaction to make sure it persists until the response is received back from flash module
		//below heap allocation uses memory manager of systemc and is more efficient than normal heap allocation using new operator as it pools memory and reduces fragmentation
		auto* trans = new tlm::tlm_generic_payload();
		tlm::tlm_phase phase;
		sc_time delay;
		ospi_frame frame_data;
		cout << "Simulation Reached at ddr: " << sc_time_stamp() << endl;

		/* Non blocking transport*/

		frame_data.ddr = 0xFEDF;
		frame_data.addr = 0x8;
		frame_data.cmd = WRITE;

		cout << "Simulation Reached at OSPI REQ1: " << sc_time_stamp() << endl;
		trans->set_data_ptr((unsigned char*)&frame_data);  //casting frame_data to unsigned char pointer as set_data_ptr expects unsigned
		trans->set_data_length(sizeof(frame_data));  //setting data length as size of frame_data
		trans->set_streaming_width(2);          //setting streaming width as 2 bytes as we are transmitting 16 bits data in one for ddr
		phase = tlm::BEGIN_REQ;  //setting phase as BEGIN_REQ for non blocking transport
		sc_time start = sc_time_stamp();  //recording start time of transaction
		initiator_socket->nb_transport_fw(*trans, phase, delay);  //initiator socket calls b_transport of flash module to send transaction



		cout << "Simulation Reached at OSPI REQ2: " << sc_time_stamp() << endl;
		auto* trans1 = new tlm::tlm_generic_payload();
		ospi_frame frame_data1;
		frame_data1.ddr = 0xDEAD;
		frame_data1.addr = 0x6;
		frame_data1.cmd = WRITE;
		trans1->set_data_ptr((unsigned char*)&frame_data1);  //casting frame_data to unsigned char pointer as set_data_ptr expects unsigned
		trans1->set_data_length(sizeof(frame_data1));  //setting data length as size of frame_data
		trans1->set_streaming_width(2);          //setting streaming width as 2 bytes as we are transmitting 16 bits data in one for ddr*/
		phase = tlm::BEGIN_REQ;  //setting phase as BEGIN_REQ for non blocking transport
		initiator_socket->nb_transport_fw(*trans1, phase, delay);  //initiator socket calls b_transport of flash module to send transaction
		//wait(delay);  //wait for the delay added in b_transport of flash module to elapse
		sc_time end = sc_time_stamp();  //recording end time of transaction
		//initiator_socket->nb_transport_fw(trans, phase, delay);  //initiator socket calls b_transport of flash module to send transaction
		double bandwidth = sizeof(frame_data) * 8 / (end - start).to_seconds();  //calculating bandwidth in bits per second
		cout << "Bandwidth of transaction: " << bandwidth << " bits/s at time: " << sc_time_stamp() << endl;
		ospi_frame* recv_frame = (ospi_frame*)trans1->get_data_ptr();  //casting received data pointer to ospi_frame pointer to access the data
		cout << "Received data at OSPI: " << hex << recv_frame->ddr << " at time: " << sc_time_stamp() << endl;
	}
}

tlm::tlm_sync_enum OSPI::nb_transport_bw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& delay)
{
	if (phase == tlm::END_REQ)
	{
		cout << "Received END_REQ at OSPI at time: " << sc_time_stamp() << endl;
		return tlm::tlm_sync_enum::TLM_ACCEPTED;  //returning TLM_ACCEPTED to indicate that the request has been accepted and is being processed
	}
	else if (phase == tlm::BEGIN_RESP)
	{
		auto _data = trans.get_data_ptr();
		ospi_frame* recv_frame = reinterpret_cast<ospi_frame*>(_data);  //casting received data pointer to ospi_frame pointer to access the data
		cout << "Received END_RESP at OSPI at time: " << sc_time_stamp() << endl;
		cout << "Received data at OSPI: " << hex << recv_frame->ddr << " at time: " << sc_time_stamp() << endl;
		cout << "Received addr at OSPI: " << hex << recv_frame->addr << " at time: " << sc_time_stamp() << endl;
		phase = tlm::END_RESP;  //setting phase to END_RESP to indicate end of response
		return tlm::tlm_sync_enum::TLM_UPDATED;  //returning TLM_UPDATED to indicate that the response has been processed and is ready to be sent back to the initiator
	}
}

void OSPI::invalidate_direct_mem_ptr(
	sc_dt::uint64 start_range,
	sc_dt::uint64 end_range) {
};