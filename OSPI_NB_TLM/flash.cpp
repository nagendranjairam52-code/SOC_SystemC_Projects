#include "flash.hpp"
void FLASH::b_transport(tlm::tlm_generic_payload& trans, sc_time& delay)
{
}
tlm::tlm_sync_enum FLASH::nb_transport_fw(
	tlm::tlm_generic_payload& trans,
	tlm::tlm_phase& phase,
	sc_core::sc_time& delay)
{
	if (phase == tlm::BEGIN_REQ)
	{
		cout << "Received BEGIN_REQ at FLASH at time: " << sc_time_stamp() << endl;
		phase = tlm::END_REQ;
		// As per TLM-2.0 standard, the target module should respond with END_REQ phase to indicate that it has accepted the request and is processing it.
		target_socket->nb_transport_bw(trans, phase, delay);
		cout << "saving transaction req at FLASH at time: " << sc_time_stamp() << endl;
		//note:trans should be dynamically allocated in initiator module to make sure it persists until the response is received back from flash module, so using heap allocation for transaction to make sure it persists until the response is received back from flash module
		// or else , here while pushing &trans to the queue, will raise an error as stack allocation dies within the nb_transport_fw and cant be saved for long time
		req_queue.push(&trans);              //saving transactions
		cout << "Trigerring event at FLASH at time: " << sc_time_stamp() << endl;
		//As we have 2 nb_transport_fw calls in OSPI, we will have 2 event notifications will be registered in the kernel...
		//As 2 event notifications have same time, both will be triggered in different delta cycle but at same simulation time, 
		// so one event is enough here which will give 2 event notify() calls getting registered with the kernel
		send_resp_ev.notify(5,SC_NS);               //timed event to trigger send_response after 10 ns to send response back to OSPI
		/*cout << "Trigerring 2nd event at FLASH at time: " << sc_time_stamp() << endl;
		send_resp_ev.notify(10, SC_NS);               //timed event to trigger send_response after 10 ns to send response back to OSPI */
		return tlm::tlm_sync_enum::TLM_UPDATED;
	}
	
	
}
void FLASH::send_response()
{
	//for (int i = 0; i < req_queue.size(); i++)
	//{
	while (true)
	{
		cout << "send response waiting for event\n";
		wait(send_resp_ev.default_event());  //wait for the event to be triggered by nb_transport_fw when a request is received and saved in the queue
		//pop only when the queue is not empty....or else runtime error comes as this is a thread and always will be running
		if (!req_queue.empty())
		{
			cout << req_queue.size() << " transactions in the queue at FLASH at time: " << sc_time_stamp() << endl;
			auto trans = req_queue.front();
			req_queue.pop();
			tlm::tlm_phase phase = tlm::BEGIN_RESP;
			sc_time delay = SC_ZERO_TIME;
			target_socket->nb_transport_bw(*trans, phase, delay);
		}
		
	}
	//}
	
}
bool FLASH::get_direct_mem_ptr(
	tlm::tlm_generic_payload&,
	tlm::tlm_dmi&)
{
	return false;
}

unsigned int FLASH::transport_dbg(
	tlm::tlm_generic_payload&)
{
	return 0;
}
