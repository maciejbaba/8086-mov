# 8086 Instruction Decoder

A C-based decoder for 8086 assembly instructions that disassembles binary machine code back to human-readable assembly language.

## Overview

This project implements a decoder for 8086 16-bit machine code, specifically targeting the `MOV` instruction with register-to-register addressing. The decoder takes binary files containing 8086 machine code and outputs the corresponding assembly instructions.

## Features

- **MOV Instruction Support**: Decodes register-to-register MOV instructions
- **8-bit and 16-bit Registers**: Supports both byte and word register operations
- **Binary File Input**: Reads machine code from binary files
- **Assembly Output**: Generates human-readable assembly code

## Supported Instructions

Currently supports:
- `MOV` instruction (opcode: `100010`) with register-to-register addressing mode

## Supported Registers

### 8-bit Registers (w=0)
- `AL`, `CL`, `DL`, `BL` (low bytes)
- `AH`, `CH`, `DH`, `BH` (high bytes)

### 16-bit Registers (w=1)
- `AX`, `CX`, `DX`, `BX` (general purpose)
- `SP`, `BP` (stack and base pointers)
- `SI`, `DI` (index registers)

## Building

### Prerequisites
- GCC compiler
- NASM assembler (for creating test files)

### Compilation
```bash
gcc -o decoder decoder.c
```

## Usage

```bash
./decoder <binary_file>
```

### Example
```bash
# Assemble test file
nasm -f bin listing_37.asm -o listing_37.bin

# Decode the binary
./decoder listing_37.bin
```

**Output:**
```
mov cx, bx
```

## File Structure

```
.
├── decoder.c          # Main decoder implementation
├── listing_37.asm     # Simple test case (mov cx, bx)
├── listing_38.asm     # Complex test case (multiple mov instructions)
└── README.md          # This file
```

## How It Works

The decoder operates by:

1. **Reading Binary Input**: Opens and reads the entire binary file into memory
2. **Instruction Parsing**: Processes the binary data in 2-byte chunks (typical for 8086 MOV instructions)
3. **Opcode Extraction**: Extracts the 6-bit opcode from the first byte
4. **Flag Decoding**: Decodes the direction (d) and width (w) flags
5. **ModR/M Byte Processing**: Parses the second byte for mod, reg, and r/m fields
6. **Register Lookup**: Maps register codes to their string representations
7. **Assembly Generation**: Outputs the corresponding assembly instruction

### Instruction Format

The decoder handles the 8086 MOV instruction format:
```
Byte 1: |100010|d|w|
Byte 2: |mod|reg|r/m|
```

Where:
- `100010`: MOV opcode
- `d`: Direction flag (0 = reg is source, 1 = reg is destination)
- `w`: Width flag (0 = 8-bit, 1 = 16-bit)
- `mod`: Addressing mode (currently supports 11 = register mode)
- `reg`: Register field
- `r/m`: Register/memory field

## Test Cases

### listing_37.asm
Simple test with a single MOV instruction:
```assembly
bits 16
mov cx, bx
```

### listing_38.asm
Complex test with multiple MOV instructions:
```assembly
bits 16
mov cx, bx
mov ch, ah
mov dx, bx
mov si, bx
mov bx, di
mov al, cl
mov ch, ch
mov bx, ax
mov bx, si
mov sp, di
mov bp, ax
```

## Creating Test Files

To create your own test binary files:

1. Write assembly code in a `.asm` file with `bits 16` directive
2. Assemble using NASM: `nasm -f bin yourfile.asm -o yourfile.bin`
3. Decode using: `./decoder yourfile.bin`

## Limitations

- Currently only supports MOV instructions
- Only handles register-to-register addressing mode
- No support for immediate values or memory addressing
- No support for other 8086 instructions (ADD, SUB, etc.)

## Future Enhancements

Potential improvements could include:
- Support for additional instructions (ADD, SUB, CMP, JMP, etc.)
- Memory addressing modes
- Immediate value handling
- 32-bit register support
- More sophisticated disassembly formatting

## Technical Details

### Register Encoding

The decoder uses lookup tables to map 3-bit register codes to register names:

**8-bit registers (w=0):**
- 000: AL, 001: CL, 010: DL, 011: BL
- 100: AH, 101: CH, 110: DH, 111: BH

**16-bit registers (w=1):**
- 000: AX, 001: CX, 010: DX, 011: BX
- 100: SP, 101: BP, 110: SI, 111: DI

### Error Handling

The decoder includes error handling for:
- Invalid command line arguments
- File opening failures
- Memory allocation failures

## License

This project is part of educational material for understanding 8086 assembly language and instruction decoding.