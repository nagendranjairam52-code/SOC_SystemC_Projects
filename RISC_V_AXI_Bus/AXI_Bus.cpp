#include "AXI_Bus.hpp"
void AXI_Bus::Bus_adapter()
{
	cout << "AXI_Bus is adapting data at time " << sc_time_stamp() << endl;
	cpu_trans *cpu_trans_in;
	wait(trans_ev);
	cpu_trans_in = cpu_signal.read();
	while (true)
	{
		if (cpu_trans_in->type = WRITE)
		{
			cout << "AXI_Bus is writing data at time " << sc_time_stamp() << endl;
			/*Write Address channel*/
			AWVALID_out.write(true);
			wait(AWREADY_in.value_changed_event());
			//Handshake met as valid and ready are both high
			if (AWREADY_in.read() == true)
			{
				AWLEN_out.write(sizeof(cpu_trans_in->address));
				AWSIZE_out.write(2);
				AWBURST_out.write(INCR);
				AWID_out.write(0);   //Assuming only one master, so ID
				AWADDR_out.write(cpu_trans_in->address);
			}
			/*Write data channel*/
			WVALID_out.write(true);
			wait(WREADY_in.value_changed_event());
			//Handshake met as valid and ready are both high
			if (WREADY_in.read() == true)
			{
				WDATA_out.write(cpu_trans_in->data[0]);
				WSTRB_out.write(0xF); //All 4 bytes are valid
			}
			/*Write Response Channel Reception*/
			wait(BVALID_in.value_changed_event());
			if (BVALID_in.read() == true)
			{
				BREADY_out.write(true);
			}
			if (BRESP_in.read())
			{
				cout << "AXI_Bus received write response at time " << sc_time_stamp() << endl;
			}
		}
		else {
			/*Read Address channel*/
			ARVALID_out.write(true);
			wait(ARREADY_in.value_changed_event());
			if (ARREADY_in.read() == true)
			{
				ARID_out.write(0);   //Assuming only one master, so ID
				ARLEN_out.write(sizeof(cpu_trans_in->address));
				ARSIZE_out.write(2);
				ARBURST_out.write(INCR);
				ARID_out.write(0);   //Assuming only one master, so ID
				ARADDR_out.write(cpu_trans_in->address);
			}

			/*Read data channel*/
			wait(RVALID_in.value_changed_event());
			if (RVALID_in.read() == true)
			{
				RREADY_out.write(true);
			}
			wait(RDATA_in.value_changed_event());
			for (int i = 0; i < ARLEN_out.read(); i++)
			{
				cpu_trans_in->data[i] = RDATA_in.read();
				if(RLAST_in.read())
				{
					break;
				}
			}
			if (RRESP_in.read())
			{
				cout << "AXI_Bus received read response at time " << sc_time_stamp() << endl;
			}
		}
	}
}

void AXI_Bus::b_transport(tlm::tlm_generic_payload& trans, sc_time& delay)
{
	trans_ev.notify(5, SC_NS);
	cpu_trans *trans1 = reinterpret_cast<cpu_trans*>(trans.get_data_ptr());
	cpu_signal.write(trans1);
}