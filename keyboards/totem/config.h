// Copyright 2022 GEIST @geigeigeist
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define MATRIX_ROWS 8
#define MATRIX_COLS 5

#define SERIAL_USART_FULL_DUPLEX  // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN GP0   // USART TX pin
#define SERIAL_USART_RX_PIN GP1   // USART RX pin
#define SERIAL_USART_PIN_SWAP     // Swap TX and RX pins if keyboard is master halve.
#define EE_HANDS // Split handedness via eeprom

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

// Home row mods resolve by the opposite-hands rule: a tap-hold key settles
// as TAPPED when the next key is on the same hand. Handedness map and the
// same-hand exceptions are in chordal_hold.c. Ported from
// qmk-vial-src-musclememory-cheapino2 v1.5.0.
#define CHORDAL_HOLD
