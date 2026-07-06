# 32-Bit Ripple Carry Adder (RCA) Hardware Simulator

## Overview
This project is logic gate-level structural simulation of a 32-bit Ripple Carry Adder (RCA) implemented in C. Instead of abstracting arithmetic operations using high-level language operators (+, -, <, etc.), this simulator models actual digital logic gates at the hardware schematic level. It processes two 32-bit input streams bit-by-bit, evaluating intermediate combinational logic and propagating the carry bit down the chain exactly like physical silicon implementation.

## Architectural Implementation
The simulation mimics hardware structural design blocks by organizing logic into modular components:
* **`AdderResult` (Struct):** Simulates hardware buses by encapsulating multi-bit outputs (`sum` and `cout`) from standard logic blocks.
* **Half Adder Module (`bitwise_halfAdder`):** Modeled entirely with fundamental boolean algebra—generating a `sum` via `XOR` (`^`) and a `cout` via `AND` (`&`).
* **Full Adder Module (`bitwise_fullAdder`):** Chains half-adder logic together to accept an incoming `Carry-In` (`cin`), executing parallel bitwise conditions to solve the combinational logic for the carry propagation network.
* **Bit Manipulation Engine (`rippleCarryAdder`):** Utilizes shift operators (`>>`, `<<`) and bitwise masking (`& 1`) to isolate individual signals, feeding them into the logic gates sequentially and dynamically constructing the final 32-bit output register.
  
## How to Compile and Run
To compile the hardware simulator using the `gcc` compiler:
```bash
gcc -Wall ripple_carry_adder.c -o rca_sim
