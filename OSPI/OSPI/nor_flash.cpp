#include "nor_flash.h"


void NOR_FLASH::flash_decode()
{
	cout << "Simulation Reached at NOR_FLASH: " << sc_time_stamp() << endl;
	//wait(SC_ZERO_TIME);
	while (true)
	{
		int bit_index = 15;
		//wait for positive edge of spi_clock to sample 1st 8 bits in 8 lanes
		wait(slave_clock.posedge_event());
		rx_data1 = nor1.read();
		rx_shift_reg[bit_index--] = rx_data1;  //moving msb bit from master to msb and other bit following that.         
		rx_data2 = nor2.read();
		rx_shift_reg[bit_index--] = rx_data2;

		rx_data3 = nor3.read();
		rx_shift_reg[bit_index--] = rx_data3;

		rx_data4 = nor4.read();
		rx_shift_reg[bit_index--] = rx_data4;

		rx_data5 = nor5.read();
		rx_shift_reg[bit_index--] = rx_data5;

		rx_data6 = nor6.read();
		rx_shift_reg[bit_index--] = rx_data6;

		rx_data7 = nor7.read();
		rx_shift_reg[bit_index--] = rx_data7;

		rx_data8 = nor8.read();
		rx_shift_reg[bit_index--] = rx_data8;

		cout << "DDR pos edge data Received at: " << sc_time_stamp() << endl;
		cout << "rx_data1 Received " << rx_data1 << " at: " << sc_time_stamp() << endl;
		cout << "rx_data2 Received " << rx_data2 << " at: " << sc_time_stamp() << endl;
		cout << "rx_data3 Received " << rx_data3 << " at: " << sc_time_stamp() << endl;
		cout << "rx_data4 Received " << rx_data4 << " at: " << sc_time_stamp() << endl;
		cout << "rx_data5 Received " << rx_data5 << " at: " << sc_time_stamp() << endl;
		cout << "rx_data6 Received " << rx_data6 << " at: " << sc_time_stamp() << endl;
		cout << "rx_data7 Received " << rx_data7 << " at: " << sc_time_stamp() << endl;
		cout << "rx_data8 Received " << rx_data8 << " at: " << sc_time_stamp() << endl;
		//wait for negative edge of spi_clock to sample 2nd 8 bits in 8 lanes
		wait(slave_clock.negedge_event());
		rx_data9 = nor1.read();
		rx_shift_reg[bit_index--] = rx_data9;

		rx_data10 = nor2.read();
		rx_shift_reg[bit_index--] = rx_data10;

		rx_data11 = nor3.read();
		rx_shift_reg[bit_index--] = rx_data11;

		rx_data12 = nor4.read();
		rx_shift_reg[bit_index--] = rx_data12;

		rx_data13 = nor5.read();
		rx_shift_reg[bit_index--] = rx_data13;

		rx_data14 = nor6.read();
		rx_shift_reg[bit_index--] = rx_data14;

		rx_data15 = nor7.read();
		rx_shift_reg[bit_index--] = rx_data15;

		rx_data16 = nor8.read();
		rx_shift_reg[bit_index--] = rx_data16;
		
		cout << "DDR neg edge data Received at: " << sc_time_stamp() << endl;
		cout << "rx_data9 Received " << rx_data9 << " at: " << sc_time_stamp() << endl;
		cout << "rx_data10 Received " << rx_data10 << " at: " << sc_time_stamp() << endl;
		cout << "rx_data11 Received " << rx_data11 << " at: " << sc_time_stamp() << endl;
		cout << "rx_data12 Received " << rx_data12 << " at: " << sc_time_stamp() << endl;
		cout << "rx_data13 Received " << rx_data13 << " at: " << sc_time_stamp() << endl;
		cout << "rx_data14 Received " << rx_data14 << " at: " << sc_time_stamp() << endl;
		cout << "rx_data15 Received " << rx_data15 << " at: " << sc_time_stamp() << endl;
		cout << "rx_data16 Received " << rx_data16 << " at: " << sc_time_stamp() << endl;

		
	}
}
