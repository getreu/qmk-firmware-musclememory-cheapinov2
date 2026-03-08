# Tap Dance Implementation in Vial Keymap

## Overview

The `cheapino/vial` keymap implements tap dance functionality using **Vial's dynamic tap dance system**, following the same pattern as the combo implementation. This allows the tap dance to:
- Have sensible defaults loaded on EEPROM reset
- Be reconfigured via the Vial GUI without reflashing
- Match the core behavior of `cheapino/musclememory`

## Implementation Pattern

The implementation follows the same pattern used for combos:

### 1. Enable Vial Tap Dance in `config.h`
```c
#define VIAL_TAP_DANCE_ENTRIES 4
```

This allocates 4 tap dance slots in EEPROM (only slot 0 is used by default).

### 2. Include Vial Headers in `keymap.c`
```c
#ifdef VIAL_TAP_DANCE_ENABLE
#include "vial.h"
#include "dynamic_keymap.h"
#endif
```

### 3. Set Default Values in `eeconfig_init_user()`
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

### 4. Use in Keymap
```c
[_BASE] = LAYOUT_split_3x5_3(
    // ... other keys ...
    OSL(_L4), LT(_L6,KC_ESC), LGUI_T(KC_SPC),
    LGUI_T(KC_ENT), LT(_L5,KC_BSPC), TD(0)  // Right outer thumb
),
```

## Behavior Comparison

### Musclememory Tap Dance (Custom QMK)
```c
// Advanced layer-aware logic
- Base layer: Single tap = KC_APP, Double tap = Toggle L2
- Other layers: Any interaction = layer_clear() (return to base)
```

### Vial Tap Dance (Dynamic)
```c
// Simplified but configurable
- Single tap = KC_APP
- Hold = KC_APP
- Double tap = Toggle L2
- Tap then hold = KC_APP
```

**Key Difference**: Vial's dynamic tap dance cannot implement the layer-aware "clear layers on non-base" behavior from musclememory. This advanced logic requires custom QMK tap dance code which conflicts with Vial's dynamic system.

## Why This Approach?

### Alternative 1: Custom QMK Tap Dance
- ✓ Can implement full musclememory behavior (layer-aware logic)
- ✗ Conflicts with Vial's dynamic tap dance system (linker errors)
- ✗ Not configurable via Vial GUI
- ✗ Requires reflashing to change behavior

### Alternative 2: Vial Dynamic Tap Dance (CHOSEN)
- ✓ Configurable via Vial GUI
- ✓ No linker conflicts
- ✓ Follows the same pattern as combos
- ✓ Provides sensible defaults via eeconfig_init_user()
- ✗ Cannot implement layer-aware "clear layers" logic
- ✗ Slightly less flexible than custom code

## Configuration

### Loading Defaults
1. Flash the firmware
2. Trigger EEPROM reset using one of these methods:
   - Press the QK_CLEAR_EEPROM key (Layer 7, Q key)
   - Use Vial GUI's "Reset EEPROM" function
3. The default tap dance will be loaded automatically

### Customizing via Vial GUI
1. Open Vial GUI
2. Navigate to the "Tap Dance" tab
3. Configure tap dance slots 0-3
4. Changes are saved to EEPROM immediately

### Slot Allocation
- **Slot 0**: Right outer thumb (default: KC_APP / TG(_L2))
- **Slots 1-3**: Reserved for user customization

## Technical Details

### Tapping Term
The default tap dance uses a 350ms tapping term to match musclememory:
```c
td.custom_tapping_term = 350;
```

### Actions Available
Vial's dynamic tap dance supports:
- `on_tap`: Action on single tap
- `on_hold`: Action when held
- `on_double_tap`: Action on double tap
- `on_tap_hold`: Action when tapped then held

### EEPROM Storage
Tap dance settings are stored in EEPROM alongside:
- Keymap layers (DYNAMIC_KEYMAP_LAYER_COUNT = 8)
- Combos (VIAL_COMBO_ENTRIES = 8)
- Tap dances (VIAL_TAP_DANCE_ENTRIES = 4)
- RGB settings
- Other QMK/Vial configuration

## Testing Checklist

After flashing and resetting
 EEPROM:

- [ ] Single tap right outer thumb → Context menu (KC_APP)
- [ ] Double tap right outer thumb → Toggle Layer 2
- [ ] Hold right outer thumb → Context menu (KC_APP)
- [ ] Verify Layer 2 indicator (Red LED)
- [ ] Open Vial GUI and check Tap Dance tab shows configured values

## Future Improvements

If the layer-aware "clear layers on non-base" behavior is critical, it could be implemented by:
1. Disabling Vial's tap dance (`VIAL_TAP_DANCE_ENTRIES` = 0)
2. Enabling native QMK tap dance (`TAP_DANCE_ENABLE = yes`)
3. Implementing custom tap dance code in keymap.c
4. Trade-off: Lose GUI configurability for this specific tap dance

However, this would break the consistency with the combo implementation pattern and make the keymap harder to maintain.