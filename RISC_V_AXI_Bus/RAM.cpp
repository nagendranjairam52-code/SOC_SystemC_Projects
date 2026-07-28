#include "RAM.hpp"

void RAM::receive_trans()
{
	cout << "RAM is receiving transaction at time " << sc_time_stamp() << endl;
	while (true)
	{
		//Note: Dont check cpu transaction type here as the slaves doesnt care about it, it will just respond to whatever the master sends. The master is responsible for sending the correct transaction type.
		/* Write Address Channel Reception*/
		wait(AWVALID_in.posedge_event());
		if(AWVALID_in.read() == true)
		{
			AWREADY_out.write(true);
		}
		//Afer handshake is met, we can read the address and burst information
		wait(AWADDR_in.value_changed_event());
		uint32_t address = AWADDR_in.read();
		uint8_t len = AWLEN_in.read();
		burst_type burst = AWBURST_in.read();
		/*Write Data Channel Reception*/
		wait(WVALID_in.value_changed_event());
		if(WVALID_in.read() == true)
		{
			WREADY_out.write(true);
		}
		//After handshake is met, we can read the data and strobe information
		wait(WDATA_in.value_changed_event());
		if (burst == FIXED)
		{
			ram[address] = (WDATA_in.read() & WSTRB_in.read());         //masking and writing the data to the RAM at the specified address
		}
		else if (burst == INCR)
		{
			for (int i = 0; i < len; i++)
			{
				ram[address + i] = (WDATA_in.read() & WSTRB_in.read());  //masking and writing the data to the RAM at the specified address
			}
		}
		else      //WRAP
		{
			for (int i = 0; i < len; i++)
			{
				ram[address + i] = WDATA_in.read();
				if ((address + i) > RAM_REGION_SIZE)
				{
					i = 0;    //Address will wrap around when it reaches the boundary of the RAM region
				}
				if(WLAST_in.read())   //WLAST signal indicates the last data of the burst, so we can break the loop
				{
					break;
				}
			}
		}
		/*Write Response Channel*/
		BID_out.write(AWID_in.read());    //Write response ID is same as the write address ID
		BVALID_out.write(true);
		wait(BREADY_in.value_changed_event());
		BRESP_out.write(1);   //Write response is OKAY

		/*Read Address Channel Reception*/
		wait(ARVALID_in.value_changed_event());
		if(ARVALID_in.read() == true)
		{
			ARREADY_out.write(true);
		}
		wait(ARADDR_in.value_changed_event());
		uint32_t len = ARLEN_in.read();
		uint32_t address = ARADDR_in.read();
		uint32_t burst = ARBURST_in.read();
		uint32_t size = ARSIZE_in.read();

	    /* Read Data Channel*/
		RVALID_out.write(true);
		wait(RREADY_in.value_changed_event());
		if(RREADY_in.read() == true)
		{
			for (int i = 0; i < len; i++)
			{
				RDATA_out.write(ram[address + i]);

			}
			if(burst == WRAP)
			{
				for (int i = 0; i < len; i++)
				{
					if ((address + i) > RAM_REGION_SIZE)
					{
						i = 0;    //Address will wrap around when it reaches the boundary of the RAM region
					}
					RDATA_out.write(ram[address + i]);
					RLAST_out.write(true);
					if(RLAST_out.read())   //RLAST signal indicates the last data of the burst, so we can break the loop
					{
						break;
					}
				}
			}
			RLAST_out.write(true);
			RRESP_out.write(1);   //Read response is OKAY
		}	
	}
}