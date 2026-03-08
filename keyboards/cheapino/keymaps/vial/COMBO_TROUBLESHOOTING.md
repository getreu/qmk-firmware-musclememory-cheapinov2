# Combo Troubleshooting Guide - Cheapino Vial Keymap

## Problem: Combos Not Triggering After Flash

If you've flashed the firmware but combos aren't working, this guide will help you diagnose and fix the issue.

## Quick Diagnosis Checklist

Before diving into fixes, check these common issues:

- [ ] Did you reset EEPROM after flashing? (Defaults only load on EEPROM reset)
- [ ] Is the Vial GUI showing empty combo slots? (Means EEPROM wasn't reset)
- [ ] Are you pressing keys simultaneously enough? (Default: 50ms window)
- [ ] Are you tapping the keys? (Don't hold mod-tap keys)
- [ ] Is `COMBO_ENABLE = true` in keyboard.json?

## Root Cause: EEPROM Not Reset

**The most common issue**: Default combos are set in `eeconfig_init_user()`, which **ONLY runs when EEPROM is initialized**, not on every boot.

### When EEPROM Gets Reset

✅ **EEPROM is reset in these cases:**
- First time flashing Vial firmware (fresh install)
- Manually triggering EEPROM reset (see below)
- EEPROM corruption detected by firmware

❌ **EEPROM is NOT reset when:**
- Reflashing the same or newer firmware
- Unplugging and replugging keyboard
- Rebooting computer
- Opening Vial GUI

## Solution 1: Force EEPROM Reset via Bootloader Combo

The firmware includes bootloader combos that will help you reset EEPROM.

### Steps:

1. **Enter bootloader mode** using one of these combos:
   - **Left hand**: Press Q+W+E+T simultaneously
   - **Right hand**: Press Y+I+O+P simultaneously
   
2. **Your keyboard enters bootloader mode** (appears as USB drive)

3. **Flash the firmware again**:
   - Copy `cheapino_vial.uf2` to the USB drive
   - Keyboard will reboot

4. **EEPROM should reset** on first boot with new firmware

5. **Test the combos**:
   - Try pressing Space + Enter together
   - Should activate Layer 7 (LED changes to pink)

### If bootloader combos don't work either:

Use the hardware reset button:
- Unplug keyboard
- Hold the BOOTSEL button on the RP2040
- Plug in keyboard while holding BOOTSEL
- Release BOOTSEL
- Flash firmware
- EEPROM will reset on first boot

## Solution 2: Reset EEPROM via Vial GUI

If you can open Vial GUI:

1. **Open Vial application**
2. **Connect your keyboard** (should be detected)
3. **Go to the "Combos" tab**
4. **Check if combos are empty** 
   - If empty slots 0-5 → EEPROM wasn't reset
   - If you see combos → Defaults loaded correctly

5. **If combos are empty**, go to Security/Settings
6. **Click "Reset EEPROM"** or similar option
7. **Confirm the reset**
8. **Unplug and replug keyboard**
9. **Check Combos tab again** - defaults should now be there

## Solution 3: Add a Reset Key to Your Keymap

For future convenience, map a key to EEPROM reset:

### Via Vial GUI:
1. Go to any layer
2. Find an unused key position
3. In the keycode selector, find `QK_CLEAR_EEPROM` or "Clear EEPROM"
4. Assign it to the key
5. Press that key to reset EEPROM anytime

### Recommended location:
- Layer 7 (RGB layer) since it's rarely used
- Or create a dedicated "reset" layer

## Solution 4: Manually Configure Combos

If automatic defaults won't load, configure manually:

### Via Vial GUI:

**Combo 0: Space + Enter → Layer 7**
1. Click Combos tab → Slot 0
2. Click the Space key on virtual keyboard
3. Click the Enter key on virtual keyboard
4. In Output dropdown: Select "Momentary Layer 7" or `MO(7)`

**Combo 1: V + Space → Layer 7**
1. Slot 1
2. Click V key
3. Click Space key
4. Output: `MO(7)`

**Combo 2: M + Enter → Layer 7**
1. Slot 2
2. Click M key
3. Click Enter key
4. Output: `MO(7)`

**Combo 3: ESC + Backspace → Toggle Layer 3**
1. Slot 3
2. Click ESC key (left inner thumb)
3. Click Backspace key (right inner thumb)
4. Output: `TG(3)` or "Toggle Layer 3"

**Combo 4: Q+W+E+T → Bootloader**
1. Slot 4
2. Click Q, W, E, T keys
3. Output: `QK_BOOT` or "Bootloader"
⚠️ Warning: Will immediately enter bootloader mode!

**Combo 5: Y+I+O+P → Bootloader**
1. Slot 5
2. Click Y, I, O, P keys
3. Output: `QK_BOOT`
⚠️ Warning: Will immediately enter bootloader mode!

## Understanding Combo Timing

Default combo term is **50ms** - keys must be pressed within this window.

### Too Strict? Increase Timing:

In Vial GUI:
1. Go to Combos tab
2. Select your combo
3. Look for "Timing" or "Term" setting
4. Try 75ms or 100ms

### Tips for Triggering Combos:

- **Press keys as simultaneously as possible**
- **Tap quickly** - don't hold (especially important for mod-tap keys)
- **Practice the motion** - muscle memory helps
- **Thumb combos**: Use "rolling" motion, press both thumbs together

## Verifying Combo Feature Is Enabled

Check that combo support is compiled in:

### In keyboard.json:
```json
"features": {
    "combo": true,  // Must be true!
}
```

### In config.h:
```c
#define VIAL_COMBO_ENTRIES 8  // Should be defined
```

If `"combo": false`, combos won't work at all - needs recompile.

## Testing Individual Combos

### Test Combo 0 (Space + Enter):

1. **Open a text editor**
2. **Press Space alone** → Should type a space (may activate GUI if held)
3. **Press Enter alone** → Should type enter (may activate GUI if held)
4. **Press both together quickly** → Should activate Layer 7
5. **Verify Layer 7 active**: RGB LED turns pink
6. **While holding combo**: Press RGB keys (top row, right side)
7. **Should control RGB** (toggle, mode, brightness, etc.)

### Test Combo 1 (V + Space):

1. **Type 'v'** alone first (verify V key works)
2. **Press Space** alone (verify it works)
3. **Press V + Space together** → Layer 7 should activate (pink LED)

### Test Combo 3 (ESC + Backspace):

1. **Press ESC** alone (should output ESC or activate Layer 6 on hold)
2. **Press Backspace** alone (should delete or activate Layer 5 on hold)
3. **Press both together** → Should toggle Layer 3 on/off
4. **Verify Layer 3**: LED turns cyan (if it was off) or returns to base color (if it was on)

## Advanced Debugging

### Check EEPROM State

In Vial GUI:
1. Go to Matrix Tester (if available)
2. Or check VIA protocol version
3. Look for EEPROM size/usage information

### Verify Firmware Version

Make sure you're running the correct firmware:
- File: `cheapino_vial.uf2`
- Size: ~109KB
- Built with: vial-qmk (not standard qmk)

### Re-flash from Scratch

1. **Enter bootloader mode** (BOOTSEL button or combo)
2. **Delete all files** from USB drive (if any)
3. **Copy ONLY cheapino_vial.uf2** to the drive
4. **Wait for automatic reboot**
5. **First boot should reset EEPROM**
6. **Test combos immediately**

## Still Not Working?

### Verify You're Tapping, Not Holding

**Problem**: Mod-tap keys behave differently on tap vs hold.

**Example**:
- Space key: Tap = Space, Hold = GUI
- If you HOLD Space, it sends GUI modifier, not Space
- Combo needs SPACE keycode, not GUI

**Solution**: 
- Press and release quickly (tap)
- Don't hold the keys down
- Press both keys in quick succession (within 50ms)

### Check for Conflicting Keycodes

The combo system matches keycodes. Make sure:
- You're on the **base layer** (Layer 0)
- Not holding any other keys
- Not in a special mode (Caps Word, Num Lock, etc.)

### Mod-Tap Key Issue

If you have `LGUI_T(KC_SPC)` in your keymap:
- **Combo uses**: `KC_SPC` (base keycode)
- **Tap the key**: Outputs `KC_SPC` → combo works ✅
- **Hold the key**: Outputs `KC_LGUI` → combo doesn't work ❌

## Expected Behavior Summary

| Combo | Keys | Expected Result | Visual Feedback |
|-------|------|----------------|-----------------|
| 0 | Space + Enter | Layer 7 active | LED → Pink |
| 1 | V + Space | Layer 7 active | LED → Pink |
| 2 | M + Enter | Layer 7 active | LED → Pink |
| 3 | ESC + Backspace | Toggle Layer 3 | LED → Cyan (on) or Base (off) |
| 4 | Q+W+E+T | Bootloader mode | USB drive appears |
| 5 | Y+I+O+P | Bootloader mode | USB drive appears |

## Getting Help

If you've tried everything and combos still don't work:

1. **Document what you tried**:
   - Firmware file used
   - EEPROM reset method attempted
   - What Vial GUI shows in Combos tab
   - Which specific combo you're testing

2. **Check these files**:
   - `DEFAULT_COMBOS.md` - How defaults work
   - `COMBO_SETUP_GUIDE.md` - Manual configuration
   - `VIAL_DEFAULTS_ANSWER.md` - Technical details

3. **Verify firmware was built correctly**:
   - Run `make cheapino:vial`
   - Check for compilation errors
   - Verify output file exists

4. **Last resort**: Configure all combos manually via Vial GUI
   - Skip the automatic defaults
   - Create combos one by one using the GUI
   - Save your configuration

## Summary: Most Likely Fix

**90% of the time, the issue is**: EEPROM wasn't reset.

**Quick fix**:
1. Press Q+W+E+T (or Y+I+O+P) to enter bootloader
2. Reflash firmware
3. Test Space+Enter combo immediately
4. If working, you're done! ✅

**If that doesn't work**:
1. Use Vial GUI → Reset EEPROM
2. Unplug/replug keyboard
3. Check Combos tab - should show configured combos
4. Test Space+Enter again

Good luck! 🎹✨