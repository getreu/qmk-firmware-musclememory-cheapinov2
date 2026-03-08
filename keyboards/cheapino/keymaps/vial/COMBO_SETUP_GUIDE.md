# Combo Setup Guide for Cheapino Vial Keymap

This guide explains how to configure key combos using the Vial GUI for the Cheapino keyboard.

## Why Configure Combos in Vial?

Unlike standard QMK, **Vial uses a dynamic combo system** where combos are configured through the GUI application, not hardcoded in C. This means:

- ✅ **No recompiling needed** - Change combos instantly
- ✅ **Visual configuration** - Click keys to create combos
- ✅ **Save/load configurations** - Export and share your setup
- ❌ **Cannot use hardcoded combos** - The C code `key_combos[]` array conflicts with Vial

## Prerequisites

1. **Flash the Vial firmware** to your Cheapino keyboard
2. **Download and install Vial** from [get.vial.today](https://get.vial.today/)
3. **Connect your keyboard** - Vial should auto-detect it

## Opening the Combo Configuration

1. **Launch Vial** application
2. Your Cheapino should appear in the device list
3. Click the **"Combos"** tab at the top of the window

You'll see 8 empty combo slots (numbered 0-7).

## Understanding the Combo Interface

Each combo slot has:
- **Keys field**: Click keyboard keys to add them to the combo
- **Output field**: Set what happens when the combo is triggered
- **Timing**: Optional delay setting (leave default unless needed)

## Recommended Combos (Based on musclememory Keymap)

Here are the combos from the original musclememory keymap, recreated for Vial:

### Combo 1: Middle Thumb Keys → Layer 7 (RGB Controls)

**Purpose**: Quick access to RGB and media controls

**Keys to press together**: 
- **Left Middle Thumb** (Space/GUI when held)
- **Right Middle Thumb** (Enter/GUI when held)

**Configuration**:
1. Select combo slot **0**
2. Click the **left middle thumb key** (Space) on the virtual keyboard
3. Click the **right middle thumb key** (Enter) on the virtual keyboard
4. In the **Output** dropdown, select `MO(_L7)` or use the "Layers" section and choose "Momentary Layer 7"

**Result**: Pressing both middle thumb keys together activates Layer 7 for RGB and media controls

---

### Combo 2: V + Space → Layer 7

**Purpose**: Alternative way to access RGB controls from left hand

**Keys**:
- **V** key (bottom row, 4th key from left)
- **Space** (left middle thumb)

**Configuration**:
1. Select combo slot **1**
2. Click **V** key
3. Click **Space** key
4. Output: `MO(_L7)` (Momentary Layer 7)

---

### Combo 3: M + Enter → Layer 7

**Purpose**: Alternative way to access RGB controls from right hand

**Keys**:
- **M** key (bottom row, 4th key from right)
- **Enter** (right middle thumb)

**Configuration**:
1. Select combo slot **2**
2. Click **M** key
3. Click **Enter** key
4. Output: `MO(_L7)` (Momentary Layer 7)

---

### Combo 4: ESC + Backspace → Toggle Layer 3

**Purpose**: Toggle numbers/navigation layer on/off

**Keys**:
- **ESC** (left inner thumb - has Layer 6 tap)
- **Backspace** (right inner thumb - has Layer 5 tap)

**Configuration**:
1. Select combo slot **3**
2. Click **ESC** key (left inner thumb)
3. Click **Backspace** key (right inner thumb)
4. Output: `TG(_L3)` - Look for "Toggle Layer 3" in the layers section

---

### Combo 5: Q+W+E+T → Bootloader (Left Hand)

**Purpose**: Enter bootloader mode for flashing firmware (emergency access from left hand)

**Keys**:
- **Q, W, E, T** (top row, first 4 keys on left half)

**Configuration**:
1. Select combo slot **4**
2. Click **Q** key
3. Click **W** key
4. Click **E** key
5. Click **T** key
6. Output: Search for `QK_BOOT` or look in "Quantum" section for "Bootloader"

⚠️ **Warning**: This will immediately put your keyboard into bootloader mode!

---

### Combo 6: Y+I+O+P → Bootloader (Right Hand)

**Purpose**: Enter bootloader mode for flashing firmware (emergency access from right hand)

**Keys**:
- **Y, I, O, P** (top row, first 4 keys on right half)

**Configuration**:
1. Select combo slot **5**
2. Click **Y** key
3. Click **I** key
4. Click **O** key
5. Click **P** key
6. Output: `QK_BOOT` (Bootloader)

⚠️ **Warning**: This will immediately put your keyboard into bootloader mode!

---

### Combo 7: OSL(L4) + APP → Caps Lock

**Purpose**: Toggle Caps Lock (since there's no dedicated key)

**Keys**:
- **OSL(L4)** key (left outer thumb)
- **APP** key (Menu key, right outer thumb)

**Configuration**:
1. Select combo slot **6**
2. Click the **left outer thumb** key
3. Click the **right outer thumb** key (APP/Menu)
4. Output: `KC_CAPS` (Caps Lock)

---

### Combo 8: (Available)

Slot 7 is available for your custom combo!

---

## Combo Tips & Best Practices

### Timing Considerations

- **Default combo term**: 50ms (keys must be pressed within this window)
- **For thumb combos**: Consider increasing to 75-100ms for easier triggering
- **For same-hand combos**: 50ms usually works well
- **For cross-hand combos**: May need 75-100ms

### Key Selection Tips

1. **Use keys you don't often press together accidentally**
2. **Thumb combos work great** - they're easy to trigger intentionally
3. **Adjacent keys** can be tricky (easy to trigger by accident)
4. **Home row combos** - be careful, might trigger during normal typing

### Testing Your Combos

After setting up each combo:

1. **Press the keys simultaneously** (within the timing window)
2. **Watch for the expected behavior** (layer change, etc.)
3. **If it doesn't work**:
   - Try pressing the keys more simultaneously
   - Increase the combo timing
   - Verify the output action is correct
   - Check that the keys are correctly selected

### Combo Priority

- If multiple combos share keys, the **more specific combo** (more keys) takes priority
- Example: If you have both "Space" and "V+Space" combos, "V+Space" will trigger when both are pressed

## Troubleshooting

### "Combo isn't triggering"

**Possible causes**:
1. **Keys not pressed simultaneously enough** → Increase combo timing
2. **Wrong keys selected** → Double-check the key positions in Vial
3. **Combo conflicts** → Check if another combo shares those keys
4. **Tap-hold keys** → Make sure you're tapping, not holding (which activates the hold function)

### "Combo triggers accidentally"

**Solutions**:
1. **Decrease combo timing** → Make it more strict
2. **Choose different keys** → Pick keys that aren't adjacent or commonly pressed together
3. **Add more keys** → 3-4 key combos are less likely to trigger accidentally

### "Middle thumb combo doesn't work"

**Common issue**: The Space and Enter keys have `LGUI_T()` modifiers (GUI when held)

**Solution**:
1. Make sure you're **tapping** both keys, not holding
2. Press them **very quickly** and **simultaneously**
3. Try **increasing the combo timing** to 75-100ms
4. Verify in Vial that you selected the correct thumb key positions

### "Can't find the output action"

In Vial's combo output field:
- **Layers**: Look in the dropdown for "Momentary Layer X" or "Toggle Layer X"
- **Special keys**: Check the "Quantum" tab for bootloader, reset, etc.
- **Normal keys**: All standard keys are available in the main tabs

## Saving Your Configuration

Your combos are **automatically saved** to the keyboard's EEPROM. This means:
- ✅ Combos persist across reboots
- ✅ Combos work even after unplugging the keyboard
- ✅ No need to "save" or "flash" - changes are immediate

### Backing Up Your Configuration

To save your combo setup:
1. In Vial, go to **File → Save current layout**
2. Choose a location and filename
3. Save as `.vil` file

To restore:
1. **File → Load saved layout**
2. Select your `.vil` file
3. Combos and all settings will be restored

## Advanced: Creating Custom Combos

Beyond the recommended combos above, you can create your own:

### Example: Quick Layer Switch
- **Keys**: `A + S` (home row)
- **Output**: `TO(_L2)` (Switch to Layer 2)
- **Use case**: Quickly switch to numpad layer

### Example: Common Shortcut
- **Keys**: `Z + C` (bottom left)
- **Output**: `LCTL(KC_C)` (Ctrl+C)
- **Use case**: Copy without moving to Ctrl key

### Example: Macro Trigger
- **Keys**: `J + K + L`
- **Output**: Assign a macro from the Macros tab
- **Use case**: Type a long string or execute a sequence

## FAQ

**Q: Why can't I have more than 8 combos?**  
A: The firmware is configured with `VIAL_COMBO_ENTRIES 8` to save space. If you need more, you'd need to recompile with a higher value.

**Q: Do combos work on all layers?**  
A: Yes! Combos trigger based on physical key positions, regardless of layer. However, the output can be layer-specific if you want.

**Q: Can a combo output multiple keys or a sequence?**  
A: Not directly, but you can create a **Macro** in the Macros tab and then assign that macro as the combo output.

**Q: Will combos slow down my typing?**  
A: No. The combo detection happens in parallel with normal key processing. The only effect is a slight delay (combo term) before single keys register, but this is only 50ms by default.

**Q: Can I disable combos temporarily?**  
A: Yes! Either:
1. Delete the combo definitions in Vial (they'll be empty slots)
2. Or use a layer-based approach where combos only work on specific layers

## Getting Help

If you have issues:

1. **Check the Vial docs**: [get.vial.today/docs](https://get.vial.today/docs)
2. **Vial Discord**: Community support available
3. **Test in a text editor**: Type slowly to see what triggers
4. **Enable debugging**: Some Vial versions show combo detection in logs

## Related Guides

- See `readme.md` for general Vial keymap information
- See `KEYMAP_COMPARISON.md` for differences between vial and musclememory keymaps
- See QMK Combo docs for technical details: [docs.qmk.fm/#/feature_combo](https://docs.qmk.fm/#/feature_combo)

---

**Last updated**: March 2024  
**Keymap version**: Cheapino Vial v1.0  
**Compatible with**: Vial 0.7+