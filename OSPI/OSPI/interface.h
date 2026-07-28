#pragma once
//#define SC_ALLOW_DEPRECATED_IEEE_API          //dont put this after <systemc> as this should be visible to systemc headers
#include <systemc>
using namespace std;
using namespace sc_core;
using namespace sc_dt;       //for using sc_data types

enum ospi_command
{
	READ = 0,
	WRITE = 1,
};
struct ospi_frame {
	uint32_t addr;
	uint32_t cmd;
	uint32_t sdr;
	uint64_t ddr;
};