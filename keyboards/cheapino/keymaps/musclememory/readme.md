# Cheapino Configuration

This firmware implements the [Muscle memory friendly home row mods layout](https://blog.getreu.net/20250826-muscle-memory-friendly-home-row-mods/). 

## Compiling and Flashing

### Using the QMK/QMK repository

1.  **Clone and Setup:**
    ```bash
    git clone https://github.com/qmk/qmk_firmware.git
    cd qmk-qmk
    git submodule update --init --recursive
    ```

2.  **Copy Keyboard Folder:**
    ```bash
    cp -r /path/to/this/keyboards/cheapino qmk-qmk/keyboards/
    ```

3.  **Compile:**
    ```bash
    qmk compile -kb cheapino -km musclememory 
    ```

4.  **Flash to Cheapino (RP2040):**
    * **Method 1 (Physical Button):** Hold the right button on the RP2040 controller while 
      plugging in the USB cable.
    * **Method 2 (Keycode):** Press the `QK_BOOT` combination (**Q+W+E+T** or **Y+I+O+P**).
    * Drag and drop the `.uf2` file onto the `RPI-RP2` drive.


### Using the Vial/QMK repository

Alternatively, you can use the Vial/QMK repository to compile and flash.

1.  **Clone and Setup:**
    ```bash
    git clone https://github.com/vial-kb/vial-qmk
    cd vial-qmk
    git submodule update --init --recursive
    ```

2.  **Copy Keyboard Folder:**
    ```bash
    cp -r /path/to/this/keyboards/cheapino vial-qmk/keyboards/
    ```

3.  **Compile:**
    ```bash
    make cheapino:musclememory
    ```

### Using the QMK/QMK repository

## Clearing EEPROM

Clearing the EEPROM resets all persistent settings (RGB configurations, Vial keymaps, tap dances, and combos) to the firmware defaults.

In this firmware, the clear function is hard-mapped to specific keys to enable a reset without the GUI:

1.  **Keycode Position:**
    * **Layer 7:** The top-left key (corresponds to `Q` on the base layer).
    * **Layer 5:** The **Rotary Encoder Press** (the physical button between the halves).
2.  **Accessing the Layer:**
    * **Layer 7:** Via a thumb combo: `Space + Enter`, `V + Space`, or `M + Enter`.
    * **Layer 5:** Hold the **Backspace** thumb key on the right half.
3.  **Triggering the Reset:**
    * **Via Layer 7:** Hold the Layer 7 combo and tap **Q**.
    * **Via Layer 5:** Hold the **Backspace** key and press the **Rotary Encoder** down.
4.  **Verification:**
    The device will **not** reboot automatically. To confirm that the reset was successful, watch for the RGB underglow to return to the default color **bright red**.



## RGB Lighting & Layer Feedback

The underglow changes color based on the active layer:

| Layer | Color | Purpose |
|-------|-------|-------|
| Base (_L0) | Custom | Main layer (restores the last saved color) |
| L1 | (inherit) | Reserved / Unused |
| L2 | Red | Numpad Layer |
| L3 | Cyan | Numbers & Navigation |
| L4 | Lavender | Function keys (F1-F24) |
| L5 | Amber | Navigation & Editing |
| L6 | Mint | Mouse control |
| L7 | Pink | RGB & Media control |

If whished for, the led can be switched off for all layers(`RGB_TOG`, layer 7),
or for the base layer only (`RGB_VAD`, layer 7).


## Troubleshooting

* **Firmware too large:** Activate `LTO_ENABLE = yes` in the `rules.mk`.


## Credits

* **Original musclememory keymap:** Custom home-row-mods layout Jens Getreu.
* **Cheapino keyboard:** Thomas Haukland (@tompi).
