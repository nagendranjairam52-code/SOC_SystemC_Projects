#include "ospi.hpp"
#include "flash.hpp"
int sc_main(int argc, char* argv[])
{
	OSPI ospi("ospi");
	FLASH flash("flash");
	ospi.initiator_socket.bind(flash.target_socket); //binding initiator socket of OSPI to target socket of FLASH
	sc_start(2, SC_NS);
	ospi.ospi_ev.notify(SC_ZERO_TIME);  //triggering event to start the transaction from OSPI to FLASH at time 0
	sc_start();
	
	return 0;
}