# SystemC Hardware Models
RISC-V | AXI | OSPI | SystemC | TLM-2.0 | Embedded Systems | Virtual Platforms | C++ | Processor &amp; Peripheral Modeling

> A collection of SystemC/TLM-2.0 models demonstrating processor architecture, on-chip communication, and embedded peripheral design.

## Overview

This repository contains a collection of SystemC models developed to explore various hardware components used in modern System-on-Chip (SoC) architectures. The projects focus on processor modeling, bus interconnects, and peripheral design using SystemC and C++.

The repository includes both integrated and standalone models. The RISC-V CPU model communicates with the AXI Bus through AXI transactions, while the remaining peripherals are developed as independent SystemC models to demonstrate their functionality and architecture.

---

## Repository Contents

### Integrated Models

#### RISC-V CPU

A SystemC implementation of a RISC-V processor capable of executing instructions and generating AXI read/write transactions for memory access.

**Features**
- Instruction fetch and decode
- Register file
- ALU operations
- Load/Store instructions
- Branch instructions
- AXI Master Interface

---

#### AXI Bus

A SystemC model of an AXI interconnect that receives transactions from the RISC-V CPU and performs address decoding and transaction routing.

**Features**
- AXI protocol modeling
- Read/Write channels
- Address decoding
- Transaction routing
- Modular design

---

### Standalone Peripheral Models

These peripherals are implemented as independent SystemC models for learning, experimentation, and future integration into larger virtual platforms.

#### OSPI Peripheral
- Register-level modeling
- Flash command handling
- Memory-mapped interface
- Configurable behavior

---

## Current Architecture

```
           +----------------+
           |   RISC-V CPU   |
           +--------+-------+
                    |
             AXI Transactions
                    |
                    ▼
             +--------------+
             |   AXI Bus    |
             +--------------+

Standalone Models
-----------------
OSPI
```

---

## Technologies Used

- C++
- SystemC
- TLM-2.0
- RISC-V ISA
- AMBA AXI Protocol
- Object-Oriented Design

---

## Project Goals

- Learn and model processor architectures
- Implement industry-standard communication protocols
- Design reusable SystemC components
- Explore virtual platform development
- Build a foundation for future SoC integration

---

## Future Work

- Integrate additional peripherals with the AXI Bus
- Expand RISC-V instruction support
- Add interrupt controller
- Implement memory subsystem
- Develop complete virtual SoC platform

---

## Skills Demonstrated

- SystemC Modeling
- C++
- Embedded Systems
- Virtual Platform Development
- Processor Architecture
- AXI Protocol
- Peripheral Modeling
- Hardware/Software Co-design

---

## License

This repository is intended for educational purpose, showcasing SystemC-based hardware modeling
