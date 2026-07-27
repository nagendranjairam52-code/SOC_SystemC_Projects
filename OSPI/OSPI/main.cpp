#include "nor_flash.h"

SC_MODULE(OSPI)
{
	ospi_frame frame_data;
	sc_in<bool> clock;
	sc_out<bool> spi_clock, data1, data2, data3, data4, data5, data6, data7, data8;        //declared bool to transmit 0 or 1 (only one bit per lane)
	//declare sc_uint<N> instead of bool to transmitt N bits per lane
	sc_uint<64> tx_shift_reg;
	sc_uint<1> dat1, dat2, dat3, dat4, dat5, dat6, dat7, dat8, dat9, dat10, dat11, dat12, dat13, dat14, dat15, dat16;  //declared one bit integer
	//Always use sc_has_process if sc_ctor is used only for declaration but not for registration of process( SC_THREAD(func())
	// SC_CTOR(OSPI){ SC_THREAD(ddr_opr);} in ospi.cpp is there means, it will take care of registration of process
	//Still SC_has_process should be used with or without sc_ctor
	//compiler should support either sc_ctor with registration or sc_has_process
	//SC_HAS_PROCESS(OSPI);
	/*OSPI(sc_module_name name) : sc_module(name)
	{
		SC_THREAD(ddr_opr);
	};*/
	SC_CTOR(OSPI): frame_data{0, 0, 0, 0}
	{
		SC_THREAD(ddr_opr);            //include "/vmg" in additional options of all options tab under c++ in properties of the project
		                               // It is registering processes to the systemc kernel
	};
	void ddr_opr()
	{
		cout << "Simulation Reached at ddr: " << sc_time_stamp() << endl;
		spi_clock.write(0);   //initializing clock to 0 to avoid unknown state
		//wait(SC_ZERO_TIME);
		frame_data.ddr = 0xABCD;
		frame_data.addr = 0x4;
		frame_data.cmd = WRITE;
		tx_shift_reg = frame_data.ddr;
		//Initialize dat1 to dat16 to avoid garbage values
		dat1 = 0, dat2 = 0, dat3 = 0, dat4 = 0, dat5 = 0, dat6 = 0, dat7 = 0, dat8 = 0,
			dat9 = 0, dat10 = 0, dat11 = 0, dat12 = 0, dat13 = 0, dat14 = 0, dat15 = 0, dat16 = 0;
		int bit_index = 15;
		dat1 = tx_shift_reg[bit_index--];   //transmitt MSB first   16th bit...index starts from 0
		dat2 = tx_shift_reg[bit_index--];   //transmitt MSB first
		dat3 = tx_shift_reg[bit_index--];   //transmitt MSB first
		dat4 = tx_shift_reg[bit_index--];   //transmitt MSB first
		dat5 = tx_shift_reg[bit_index--];   //transmitt MSB first
		dat6 = tx_shift_reg[bit_index--];   //transmitt MSB first
		dat7 = tx_shift_reg[bit_index--];   //transmitt MSB first
		dat8 = tx_shift_reg[bit_index--];   //transmitt MSB first
		dat9 = tx_shift_reg[bit_index--];   //transmitt MSB first
		dat10 = tx_shift_reg[bit_index--];   //transmitt MSB first
		dat11 = tx_shift_reg[bit_index--];   //transmitt MSB first
		dat12 = tx_shift_reg[bit_index--];   //transmitt MSB first
		dat13 = tx_shift_reg[bit_index--];   //transmitt MSB first
		dat14 = tx_shift_reg[bit_index--];   //transmitt MSB first
		dat15 = tx_shift_reg[bit_index--];   //transmitt MSB first
		dat16 = tx_shift_reg[bit_index--];   //transmitt MSB first

		while (true)
		{
			cout << "Simulation Reached at OSPI: " << sc_time_stamp() << endl;
			//TC1
			//DDR capability..sending first 8 bits at positive edge and next 8 bits at negative edge in 8 lines
			//In one positive edge, 8 lanes transmit 8 bits together
			wait(clock.posedge_event());
			//cant do clock.read() inside write of spi_clock as 0->1 transition only detects edges by systemc kernel
			//if spi_clock was 1 before, edges wont be detected in slave clock of nor flash
			//wait(SC_ZERO_TIME);
			spi_clock.write(1);       //forwarding 200mhz clock signal to spi_clock port
			data1.write(dat1);
			data2.write(dat2);
			data3.write(dat3);
			data4.write(dat4);
			data5.write(dat5);
			data6.write(dat6);
			data7.write(dat7);
			data8.write(dat8);
			//wait(SC_ZERO_TIME);
			cout << "DDR pos edge data transmitted at: " << sc_time_stamp() << endl;
			cout << "tx_data1 transmitted " << dat1 << " at : " << sc_time_stamp() << endl;
			cout << "tx_data2 transmitted " << dat2 << " at : " << sc_time_stamp() << endl;
			cout << "tx_data3 transmitted " << dat3 << " at : " << sc_time_stamp() << endl;
			cout << "tx_data4 transmitted " << dat4 << " at : " << sc_time_stamp() << endl;
			cout << "tx_data5 transmitted " << dat5 << " at : " << sc_time_stamp() << endl;
			cout << "tx_data6 transmitted " << dat6 << " at : " << sc_time_stamp() << endl;
			cout << "tx_data7 transmitted " << dat7 << " at : " << sc_time_stamp() << endl;
			cout << "tx_data8 transmitted " << dat8 << " at : " << sc_time_stamp() << endl;
			//In one negative edge, 8 lanes transmit 8 bits together
			wait(clock.negedge_event());
			spi_clock.write(0);   //toggling clock to generate edges for data transmission
			data1.write(dat9);
			data2.write(dat10);
			data3.write(dat11);
			data4.write(dat12);
			data5.write(dat13);
			data6.write(dat14);
			data7.write(dat15);
			data8.write(dat16);
			cout << "DDR neg edge data transmitted at: " << sc_time_stamp() << endl;
			cout << "tx_data9 transmitted " << dat9 << " at : " << sc_time_stamp() << endl;
			cout << "tx_data10 transmitted " << dat10 << " at : " << sc_time_stamp() << endl;
			cout << "tx_data11 transmitted " << dat11 << " at : " << sc_time_stamp() << endl;
			cout << "tx_data12 transmitted " << dat12 << " at : " << sc_time_stamp() << endl;
			cout << "tx_data13 transmitted " << dat13 << " at : " << sc_time_stamp() << endl;
			cout << "tx_data14 transmitted " << dat14 << " at : " << sc_time_stamp() << endl;
			cout << "tx_data15 transmitted " << dat15 << " at : " << sc_time_stamp() << endl;
			cout << "tx_data16 transmitted " << dat16 << " at : " << sc_time_stamp() << endl;

			
			if (bit_index < 0)
			{
				cout << "Frame complete at " << sc_time_stamp() << endl;
				bit_index = 15;  // or load next word
			}
		}
	}
};




int sc_main(int agrc, char* argv[])
{
	//200mhz as system clock
	sc_clock clk_200mhz("clk_200mhz", 5, SC_NS, 0.5);        //for 200mhz clock, 5ns is period and 0.5 is 50% duty cycle
	sc_signal<bool> spi_clk_sig;     //sc_clock generates clock with duty cycle...but sc_signal can drive values and bool values too(which is nothing but clock behaviour)
	sc_signal<bool> d1, d2, d3, d4, d5, d6, d7, d8;
	OSPI OSPI_MODULE("OSPI_MODULE");
	NOR_FLASH FLASH_MODULE("FLASH_MODULE");

	//Port - signal (channel) binding
	//signal - OSPI connection
	OSPI_MODULE.clock(clk_200mhz);    //200mhz clock as input clock to OSPI module
	OSPI_MODULE.spi_clock(spi_clk_sig);   //OSPI module generates its own clock signal from 200mhz clock to drive data at both edges
	//spi_clock -> spi_clk_sig (signal interfac) -> slave_clock (sc_in,sc_out or any ports must be connected through interfaces)
								// so need to bind ports with that interface in both spi and slave
	OSPI_MODULE.data1(d1);
	OSPI_MODULE.data2(d2);
	OSPI_MODULE.data3(d3);
	OSPI_MODULE.data4(d4);
	OSPI_MODULE.data5(d5);
	OSPI_MODULE.data6(d6);
	OSPI_MODULE.data7(d7);
	OSPI_MODULE.data8(d8);

	//Port - Port (channel) binding
	//OSPI-FLASH connection
	FLASH_MODULE.slave_clock(spi_clk_sig);   //spi_clock -> spi_clk_sig (signal interfac) -> slave_clock
	                                   // spi_clock writes to spi_clk_signal and slave_clock reads from spi_clk_signal. 
									   // Thats how signal channel (nothing but clk_sig) connects two ports
	//same for data lines....data1->d1->nor1
	FLASH_MODULE.nor1(d1);
	FLASH_MODULE.nor2(d2);
	FLASH_MODULE.nor3(d3);
	FLASH_MODULE.nor4(d4);
	FLASH_MODULE.nor5(d5);
	FLASH_MODULE.nor6(d6);
	FLASH_MODULE.nor7(d7);
	FLASH_MODULE.nor8(d8);
	
	//Tracing expects objects of the modules, which will be cleaned up by kernel at end of simulation
	//so adding this before simulation start
	sc_trace_file* tf = sc_create_vcd_trace_file("ospi_data");
	// Trace top-level ports
	sc_trace(tf, clk_200mhz, "clk_200mhz");
	sc_trace(tf, d1, "D1");
	sc_trace(tf, d2, "D2");
	sc_trace(tf, d3, "D3");
	sc_trace(tf, d4, "D4");
	sc_trace(tf, d5, "D5");
	sc_trace(tf, d6, "D6");
	sc_trace(tf, d7, "D7");
	sc_trace(tf, d8, "D8"); 
	cout << "OSPI clock bound = " << OSPI_MODULE.clock.get_interface() << endl;  //this will show whether that port is bound or not
	cout << "Starting Simulation" << endl;
	sc_report_handler::set_actions(SC_ERROR, SC_ABORT);
	cout << "starting time: " << sc_time_stamp() << endl;
	sc_time start_time = sc_time_stamp();
	sc_start(20, SC_NS);
	sc_time end_time = sc_time_stamp();
	cout << "latency: " << (end_time - start_time) / sc_time(5, SC_NS) << " cycles" << endl;
	cout << "ending time: " << sc_time_stamp() << endl;
	sc_close_vcd_trace_file(tf);
	return 0;
}