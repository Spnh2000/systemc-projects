# SystemC Projects

A collection of hardware simulation projects built with [SystemC](https://systemc.org/), covering combinational logic, sequential logic, channels, and digital signal processing.

## Projects

| Project | Description |
|---|---|
| [XOR](XOR/) | XOR gate built from 4 NAND gates (structural composition) |
| [RSLatch](RSLatch/) | RS Latch using cross-coupled NOR gates (sequential/feedback logic) |
| [FIFO](FIFO/) | Generic FIFO channel with blocking Producer/Consumer modules |
| [Moving_Average](Moving_Average/) | 4-tap moving average filter (clocked synchronous design) |

## Prerequisites

- CMake 3.10+
- A C++17 compiler (GCC/Clang)
- SystemC library installed (e.g., to `/usr/local/systemc`)

Set the environment variable before building:

```bash
export SYSTEMC_HOME=/usr/local/systemc
```

## Build & Run

Each project builds independently:

```bash
cd <project_dir>        # e.g., cd XOR
mkdir -p build && cd build
cmake ..
make
./<executable>          # e.g., ./exor
```

| Project | Executable |
|---|---|
| XOR | `./exor` |
| RSLatch | `./rslatch` |
| FIFO | `./simple_fifo` |
| Moving_Average | `./moving_average` |

## Project Details

### XOR
Implements an XOR gate by composing four NAND gate instances. Demonstrates hierarchical `SC_MODULE` design with internal `sc_signal` interconnects.

```
A ──┬──[NAND a]──h1──┬──[NAND b]──h2──┐
    │                │                 [NAND d]── Z
    └────────────────┴──[NAND c]──h3──┘
```

### RSLatch
Models an RS latch using a single `SC_METHOD` sensitive to all four ports (S, R, Q, N). The feedback loop settles via SystemC delta cycles.

```
S ──[NOR]── Q
       ↑↘
       ↓ ↗
R ──[NOR]── N
```

### FIFO
A generic template FIFO channel (`SimpleFifo<T>`) implementing a custom `sc_interface`. The Producer writes every 1 ns; the Consumer reads every 4 ns. Blocking is handled with `sc_event` (not OS mutexes).

### Moving Average
A 4-tap FIR filter: `yn = (xn + x0 + x1 + x2) / 4`. The shift register advances on the positive clock edge (`SC_METHOD` sensitive to `clk.pos()`); the sum is computed asynchronously whenever inputs change.

## Notes

These projects were developed as part of the **SystemC and Virtual Prototyping (SCVP)** course at the University of Kaiserslautern (Dr.-Ing. Matthias Jung).

