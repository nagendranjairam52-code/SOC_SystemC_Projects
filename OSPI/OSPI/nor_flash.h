#pragma once
#include "interface.h"

SC_MODULE(NOR_FLASH)
{
	//signals for binding the ports to drive these kind of signals
	//Note: same signals and clock are in main.cpp but those are with values
	//Here same signals are given to let ports know that these signal types should be driven by the ports
	//since values flow from ospi, dont want to take the same initial value signal in main.cpp as we want ospi processed signals
	//sc_signal<bool> nor_d1, nor_d2, nor_d3, nor_d4, nor_d5, nor_d6, nor_d7, nor_d8;
	/*ports*/
	sc_in<bool> slave_clock;
	sc_uint<64> rx_shift_reg;
	sc_in<bool> nor1, nor2, nor3, nor4, nor5, nor6, nor7, nor8;            //declared bool to receive one bit
	sc_uint<1> rx_data1, rx_data2, rx_data3, rx_data4, rx_data5, rx_data6, rx_data7, rx_data8,
		rx_data9, rx_data10, rx_data11, rx_data12, rx_data13, rx_data14, rx_data15, rx_data16;
	SC_CTOR(NOR_FLASH)
	{
		SC_THREAD(flash_decode);
	};
	void flash_decode();
};

