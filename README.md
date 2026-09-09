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

## Application Flow

On power-up, the firmware initializes the display and starts the main loop:

1. **Counter Mode**: The 7-segment display shows a counter (00-99) that increments every second
2. **Switch Detection**: When any switch (S1-S7) is pressed, the display immediately shows the switch number (1-7)
3. **Resume Counter**: When no switch is pressed, the counter resumes from where it left off

### Switch Mapping

| Switch | Segment Pin | Display Value |
|--------|-------------|---------------|
| S1     | B (PA00)    | 1             |
| S2     | F (PA04)    | 2             |
| S3     | G (PA22)    | 3             |
| S4     | DP (PA10)   | 4             |
| S5     | E (PA11)    | 5             |
| S6     | D (PA18)    | 6             |
| S7     | C (PA19)    | 7             |

### Timing

- Display refresh: 6ms per digit (12ms full cycle)
- Switch scan: Every 24ms with debounce
- Counter update: Every 1 second

## License

Proprietary - Microchip Technology Inc.
