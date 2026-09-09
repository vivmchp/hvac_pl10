# HVAC Controller

Firmware for HVAC controller based on PIC32CM6408PL10032 (Cortex-M0+) microcontroller.

## Features

- 2-digit 7-segment display with multiplexing
- Timer-driven display refresh (4ms period)
- Status LED indicator

## Hardware

- **MCU**: PIC32CM6408PL10032 @ 24MHz
- **Display**: Common-anode 7-segment, 2 digits
- **Programmer**: PICkit Basic

## Building

Requires:
- MPLAB X IDE or VS Code with MPLAB extension
- XC32 Compiler v6.00
- CMake and Ninja

```bash
cd firmware
cmake --preset HVAC_default_conf -S cmake/HVAC/default
cmake --build _build/HVAC/default
```

Output: `firmware/out/HVAC/default.elf`

## Project Structure

```
firmware/
├── config.mcc/src/       # Source code
│   ├── main.c            # Application entry point
│   ├── seven_seg.c/h     # 7-segment display driver
│   ├── segment_pins.c/h  # Segment pin control
│   └── config/default/   # MCC-generated peripheral libraries
├── cmake/                # CMake build files
└── .vscode/              # VS Code/MPLAB project files

hardware/
├── IT-886_HVAC.pdf       # PCB documentation
└── PINMAPPING.xlsx       # Pin assignment spreadsheet
```

## License

Proprietary - Microchip Technology Inc.
