# Cheapino Vial Configuration (musclememory v1.1.1)

## Compiling and Flashing

1.  **Clone and Setup:**
    ```bash
    git clone [https://github.com/vial-kb/vial-qmk](https://github.com/vial-kb/vial-qmk)
    cd vial-qmk
    git submodule update --init --recursive
    ```

2.  **Copy Keyboard Folder:**
    ```bash
    cp -r /path/to/this/keyboards/cheapino vial-qmk/keyboards/
    ```

3.  **Compile:**
    ```bash
    make cheapino:vial
    ```

4.  **Flash to Cheapino (RP2040):**
    * **Method 1 (Physical Button):** Hold the `BOOTSEL` button while plugging in the USB cable.
    * **Method 2 (Keycode):** Press the `QK_BOOT` combination (**Q+W+E+T** or **Y+I+O+P**).
    * Drag and drop the `.uf2` file onto the `RPI-RP2` drive.

---

## Clearing EEPROM

Clearing the EEPROM resets all persistent settings (RGB configurations, Vial keymaps, tap dances, and combos) to the firmware defaults.

### Method 1: Using the Vial GUI
1.  Connect the Cheapino and open the Vial GUI.
2.  Go to the **Settings** tab (gear icon).
3.  Click on **EEPROM Reset** and confirm.

### Method 2: Using the QK_CLEAR_EEPROM Keycode
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

---

## RGB Lighting & Layer Feedback

The underglow changes color based on the active layer:

| Layer | Color | Purpose |
|-------|-------|-------|
| Base (_L0) | Custom | Main layer (restores the last saved color) |
| L1 | (inherit) | Reserved / Unused |
| L2 | **Red** | Numpad Layer |
| L3 | Cyan | Numbers & Navigation |
| L4 | Lavender | Function keys (F1-F24) |
| L5 | Amber | Navigation & Editing |
| L6 | Mint | Mouse control |
| L7 | Pink | RGB & Media control |

---

## Using Vial GUI

1.  **Download:** Download Vial from [get.vial.today](https://get.vial.today/).
2.  **Security Unlock:** To change security-relevant settings, you must press the **Security Unlock Combo**: **Q + P** (top-left key + top-right key).
3.  **Configuration:** Use the tabs for **Tap Dance** and **Combos** to customize the layout.

---

## Troubleshooting

* **Not recognized:** Ensure that you compiled with `vial-qmk`.
* **Not saving:** Check if the keyboard was unlocked with **Q + P**.
* **Firmware too large:** Activate `LTO_ENABLE = yes` in the `rules.mk`.

---

## Credits
* **Original musclememory keymap:** Custom home-row-mods layout Jens Getreu.
* **Cheapino keyboard:** Thomas Haukland (@tompi).
* **License:** GPL-2.0-or-later.
