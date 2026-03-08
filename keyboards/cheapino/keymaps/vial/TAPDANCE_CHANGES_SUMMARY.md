# Tap Dance Implementation Summary for cheapino/vial

## What Was Implemented

Tap dance functionality has been implemented for the **right outer thumb key** (TD(0)) in the `cheapino/vial` keymap, matching the behavior from `cheapino/musclememory`.

## Implementation Method

Following the same pattern used for **combo defaults**, the tap dance is configured using **Vial's dynamic tap dance system**:

### 1. Configuration (`config.h`)
```c
#define VIAL_TAP_DANCE_ENTRIES 4
```

### 2. Default Setup (`eeconfig_init_user()` in `keymap.c`)
```c
#ifdef VIAL_TAP_DANCE_ENABLE
    {
        vial_tap_dance_entry_t td = {0};
        td.on_tap = KC_APP;           // Single tap: Context menu
        td.on_hold = KC_APP;          // Hold: Context menu
        td.on_double_tap = TG(_L2);   // Double tap: Toggle Layer 2
        td.on_tap_hold = KC_APP;      // Tap then hold: Context menu
        td.custom_tapping_term = 350; // Match musclememory's 350ms
        dynamic_keymap_set_tap_dance(0, &td);
    }
#endif
```

### 3. Keymap Usage
```c
[_BASE] = LAYOUT_split_3x5_3(
    // ... other keys ...
    OSL(_L4), LT(_L6,KC_ESC), LGUI_T(KC_SPC),
    LGUI_T(KC_ENT), LT(_L5,KC_BSPC), TD(0)  // Right outer thumb
),
```

## Key Features

✓ **GUI Configurable**: Can be customized via Vial GUI without reflashing  
✓ **Sensible Defaults**: Loaded automatically on EEPROM reset  
✓ **Pattern Consistency**: Uses the same approach as combo defaults  
✓ **Matching Timing**: 350ms tapping term matches musclememory  
✓ **Core Functionality**: Single tap (menu) and double tap (layer toggle) work as expected  

## Behavior

| Action | Result |
|--------|--------|
| **Single tap** | KC_APP (Context menu) |
| **Hold** | KC_APP (Context menu) |
| **Double tap** | Toggle Layer 2 (Numpad layer, Red LED) |
| **Tap then hold** | KC_APP (Context menu) |

## Differences from musclememory

### musclememory (Custom QMK Tap Dance)
- Single tap on base layer: KC_APP
- Double tap on base layer: Toggle Layer 2
- **Any interaction on other layers: Clear all layers (return to base)**
- Not configurable without reflashing

### vial (Vial Dynamic Tap Dance)
- Single tap: KC_APP
- Double tap: Toggle Layer 2
- **No layer-aware "clear layers" behavior**
- Fully configurable via Vial GUI

**Note**: Vial's dynamic tap dance system cannot implement the advanced layer-aware "clear layers on non-base layer" logic from musclememory. This would require custom QMK tap dance code, which conflicts with Vial's dynamic system (linker errors).

## How to Use

### First Time Setup
1. Flash the `cheapino_vial.uf2` firmware
2. Reset EEPROM to load defaults:
   - Press QK_CLEAR_EEPROM (Layer 7 → Q key), OR
   - Use Vial GUI → "Reset EEPROM" option
3. The tap dance defaults will be loaded automatically

### Testing
- **Single tap right thumb**: Context menu should appear
- **Double tap right thumb**: Layer 2 should toggle (Red LED indicator)
- **Toggle back**: Double tap again to return to base layer

### Customization via Vial GUI
1. Open Vial application
2. Navigate to "Tap Dance" tab
3. Modify tap dance slots (0-3)
4. Changes save to EEPROM immediately
5. No reflashing required!

## Files Modified

| File | Changes |
|------|---------|
| `keymap.c` | Added tap dance default setup in `eeconfig_init_user()` |
| `config.h` | Already had `VIAL_TAP_DANCE_ENTRIES 4` |
| `rules.mk` | No changes needed (Vial includes tap dance by default) |

## Build Information

- **Firmware**: `cheapino_vial.uf2`
- **Size**: 113KB
- **Build Status**: ✓ Success (no errors or warnings)
- **Commit**: ebbd959a41

## Architecture Decision

### Why Vial Dynamic Instead of Custom QMK?

#### Option A: Custom QMK Tap Dance (Not Chosen)
- ✓ Full musclememory behavior (layer-aware logic)
- ✗ Conflicts with Vial's system (linker errors)
- ✗ Not GUI configurable
- ✗ Requires reflashing for changes

#### Option B: Vial Dynamic Tap Dance (CHOSEN) ✓
- ✓ GUI configurable
- ✓ No conflicts
- ✓ Consistent with combo pattern
- ✓ User-friendly
- ✗ Cannot do layer-aware "clear layers" logic

**Decision**: Use Vial's dynamic system for consistency with the combo implementation and to maintain GUI configurability.

## Related Documentation

- `TAP_DANCE_IMPLEMENTATION.md` - Detailed technical documentation
- `COMBO_SETUP_GUIDE.md` - Similar pattern used for combos
- `DEFAULT_COMBOS.md` - Combo defaults reference

## Next Steps

1. Flash the firmware
2. Reset EEPROM (QK_CLEAR_EEPROM or Vial GUI)
3. Test tap dance behavior
4. Verify in Vial GUI Tap Dance tab
5. Optionally customize via GUI

## Troubleshooting

### Tap dance not working after flash
- **Solution**: Reset EEPROM to load defaults (QK_CLEAR_EEPROM on Layer 7 → Q)

### GUI shows no tap dance configured
- **Solution**: EEPROM reset needed - defaults are loaded in `eeconfig_init_user()`

### Want the layer-aware behavior from musclememory
- **Option**: Use the `musclememory` keymap instead of `vial`
- **Trade-off**: Lose GUI configurability, gain advanced tap dance logic

## Summary

The tap dance implementation successfully matches the core functionality of `cheapino/musclememory` while maintaining Vial's GUI configurability. The implementation follows the established pattern used for combo defaults, making the codebase consistent and maintainable.