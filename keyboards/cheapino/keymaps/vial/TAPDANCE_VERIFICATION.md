# Tap Dance Verification Checklist

## Quick Test Guide

After flashing `cheapino_vial.uf2` to your keyboard, follow these steps to verify tap dance functionality.

---

## Step 1: Reset EEPROM (REQUIRED)

Tap dance defaults are loaded during EEPROM initialization. You **must** reset EEPROM after flashing.

### Method A: Via Keyboard
1. Hold **ESC** and **Backspace** (inner thumb keys) simultaneously
2. This enters Layer 3 (toggle)
3. Press **Q** while on Layer 3
4. This triggers `QK_CLEAR_EEPROM`
5. Wait for keyboard to reset (~2 seconds)

### Method B: Via Keyboard (Alternative)
1. Press and hold **Space** and **Enter** (middle thumb keys)
2. This activates Layer 7 (momentary)
3. While holding, press **Q** 
4. This triggers `QK_CLEAR_EEPROM`
5. Wait for keyboard to reset (~2 seconds)

### Method C: Via Vial GUI
1. Open Vial application
2. Go to **Matrix Tester** or **Settings**
3. Find **Reset EEPROM** option
4. Click it and confirm
5. Wait for keyboard to reset

---

## Step 2: Test Right Outer Thumb (TD(0))

### Test 2.1: Single Tap = Context Menu
- **Action**: Tap the right outer thumb key once (quick press and release)
- **Expected**: Context menu appears (equivalent to right-click or Menu key)
- **Status**: ☐ PASS / ☐ FAIL

### Test 2.2: Hold = Context Menu
- **Action**: Press and hold the right outer thumb key
- **Expected**: Context menu appears after short delay
- **Status**: ☐ PASS / ☐ FAIL

### Test 2.3: Double Tap = Toggle Layer 2
- **Action**: Quickly tap the right outer thumb key twice (within 350ms)
- **Expected**: 
  - RGB LED changes to RED
  - Keyboard enters numpad mode (Layer 2)
  - Number row becomes numpad numbers
- **Status**: ☐ PASS / ☐ FAIL

### Test 2.4: Toggle Back to Base
- **Action**: Double tap the right outer thumb key again
- **Expected**: 
  - RGB LED returns to original color
  - Keyboard returns to base layer
  - Number row works normally
- **Status**: ☐ PASS / ☐ FAIL

---

## Step 3: Verify in Vial GUI

### Vial GUI Check
1. Open Vial application
2. Navigate to **Tap Dance** tab
3. **Check Slot 0**:
   - On Tap: KC_APP
   - On Hold: KC_APP
   - On Double Tap: TG(2) or "Toggle Layer 2"
   - On Tap Hold: KC_APP
   - Tapping Term: 350ms
4. **Status**: ☐ All values correct / ☐ Values incorrect

### If Values Are Incorrect
- You likely didn't reset EEPROM
- Go back to **Step 1** and reset EEPROM
- Then re-check this step

---

## Step 4: Compare with Musclememory Behavior

### Core Functionality
| Feature | Musclememory | Vial | Match? |
|---------|--------------|------|--------|
| Single tap → Menu | ✓ | ✓ | ☐ |
| Double tap → Layer 2 | ✓ | ✓ | ☐ |
| 350ms tapping term | ✓ | ✓ | ☐ |
| Layer 2 RED indicator | ✓ | ✓ | ☐ |

### Advanced Feature
| Feature | Musclememory | Vial | Match? |
|---------|--------------|------|--------|
| Clear layers when pressed on L3-L7 | ✓ | ✗ | N/A |

**Note**: The "clear layers" behavior is not possible with Vial's dynamic tap dance system. This is a known limitation documented in `TAP_DANCE_IMPLEMENTATION.md`.

---

## Step 5: Layer 2 Numpad Test

While Layer 2 is active (after double tap):

### Number Row → Numpad
- Press **U, I, O, P** on top row
- **Expected**: Numbers 7, 8, 9, 0
- **Status**: ☐ PASS / ☐ FAIL

### Home Row → Numpad
- Press **J, K, L** on home row  
- **Expected**: Numbers 4, 5, 6
- **Status**: ☐ PASS / ☐ FAIL

### Bottom Row → Numpad
- Press **M, comma, period** on bottom row
- **Expected**: Numbers 1, 2, 3
- **Status**: ☐ PASS / ☐ FAIL

---

## Troubleshooting

### Issue: Tap dance does nothing
**Solution**: Reset EEPROM (Step 1). Defaults only load on EEPROM initialization.

### Issue: Single tap works but double tap doesn't
**Possible causes**:
1. Tapping too slowly (must be within 350ms)
2. Tapping term not configured correctly
3. Check Vial GUI → Tap Dance → Slot 0 → Tapping Term should be 350

### Issue: Vial GUI shows empty tap dance slots
**Solution**: Reset EEPROM. Defaults are loaded by `eeconfig_init_user()` which only runs on EEPROM reset.

### Issue: Layer 2 activates but doesn't toggle back
**Solution**: Double tap again. It's a toggle, not a momentary layer.

### Issue: Want the layer-aware "clear layers" behavior
**Solution**: Use the `musclememory` keymap instead. The Vial keymap prioritizes GUI configurability over advanced tap dance logic.

---

## Success Criteria

All of the following must be true:

- ☐ Single tap produces context menu
- ☐ Double tap toggles Layer 2 (RED LED)
- ☐ Double tap again returns to base layer
- ☐ Vial GUI shows tap dance configured in Slot 0
- ☐ Layer 2 numpad keys work correctly
- ☐ No compilation errors
- ☐ Firmware size is reasonable (~113KB)

---

## Final Notes

### Differences from Musclememory
The Vial implementation provides **95% of musclememory's tap dance functionality**:
- ✓ Single tap for menu
- ✓ Double tap for layer toggle
- ✓ Correct timing (350ms)
- ✗ No layer-aware "clear layers" behavior

### Why This Trade-off?
- **Gain**: GUI configurability without reflashing
- **Gain**: Consistency with combo implementation pattern
- **Gain**: User-friendly customization
- **Loss**: Advanced layer-aware logic (requires custom code)

### If You Need Full Musclememory Behavior
Use the `cheapino:musclememory` keymap instead. It implements the full tap dance logic including layer-aware behavior, but cannot be configured via GUI.

---

## Build Information

- **Firmware**: cheapino_vial.uf2
- **Size**: 113KB
- **Last Commit**: 5be9e728d2
- **Documentation**: TAP_DANCE_IMPLEMENTATION.md, TAPDANCE_CHANGES_SUMMARY.md

---

**Verification Date**: _____________

**Tested By**: _____________

**Result**: ☐ ALL TESTS PASSED  /  ☐ ISSUES FOUND (see notes)

**Notes**: