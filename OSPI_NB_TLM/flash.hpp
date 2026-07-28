#include "interface.hpp"
#include <queue>
class FLASH : public sc_module, public tlm::tlm_fw_transport_if<>
{
public:
	//1st param - bus_width, 2nd param - put whether this target socket impelements fw_transport or not
	//3rd param - put bw_transport_if if it implementes/ call those functions too, 4th param - 1 means one intiator sockets can be binded to this target socket
	// if its 0, multiple initiator sockets can be binded to it, 5th param is binding policy like enum for 4th param (how many initiators are allowed to bind)
	//defining tlm::tlm_target_socket<> target_socket without paramaters will take defualt values
	tlm::tlm_target_socket<> target_socket;
	queue<tlm::tlm_generic_payload*> req_queue;
	//sc_event does not queue notifications. 
	//Multiple timed notify() calls overwrite previous ones. To model multiple independent events, 
	// use sc_event_queue or explicitly manage queues(like with one event, but remove all transaction pointers and send backwards).
	/*sc_event_queue:
	    can store multiple timed notifications
		schedules them internally
		triggers one event per scheduled notification
		needs constructor initialization as it looks for default event() first...but sc_event dont need constructor initialization
	 sc_event_queue is a channel (like sc_module child)
      Internally it needs:
         kernel registration, name, event handle
      If not initialized properly
         default_event() → invalid reference → crash*/
	sc_event_queue send_resp_ev;
	/*sc_event_queue is a channel that internally manages multiple timed notifications. 
	Since it does not expose its internal event directly, we use default_event() to obtain a reference to the event and wait on it. 
	Unlike sc_event, it supports queuing multiple notifications.*/
	//tlm::tlm_generic_payload TRANS;
	SC_CTOR(FLASH) : target_socket("target_socket"), send_resp_ev("send_resp_ev")
	{
		target_socket.bind(*this);
		SC_THREAD(send_response);
	};
private:
	void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay);
	tlm::tlm_sync_enum nb_transport_fw(
		tlm::tlm_generic_payload& trans,
		tlm::tlm_phase& phase,
		sc_core::sc_time& delay);
	bool get_direct_mem_ptr(
		tlm::tlm_generic_payload& trans,
		tlm::tlm_dmi& dmi_data);
	unsigned int transport_dbg(
		tlm::tlm_generic_payload& trans);
	void send_response();
};
