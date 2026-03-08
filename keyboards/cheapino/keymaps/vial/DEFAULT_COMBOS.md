# Default Combos in Vial Keymap

## YES! Vial DOES Support Default Combos

Great news: **Vial supports shipping default combos** via the `eeconfig_init_user()` function.

## How It Works

When the keyboard's EEPROM is initialized (reset), the `eeconfig_init_user()` function runs and can programmatically set up default combos using Vial's dynamic combo API.

### When Are Defaults Applied?

Default combos are loaded in these situations:

1. **First time flashing** - When you flash Vial firmware for the first time
2. **EEPROM reset** - When you manually reset EEPROM settings in Vial
3. **QK_CLEAR_EEPROM** - If you press a key mapped to clear EEPROM

### What Defaults Are Included

This keymap ships with **7 pre-configured combos** (based on the musclememory keymap):

| Slot | Keys | Action | Description |
|------|------|--------|-------------|
| **0** | Left Middle Thumb + Right Middle Thumb | `MO(_L7)` | Access Layer 7 (RGB/Media) |
| **1** | V + Space | `MO(_L7)` | Layer 7 from left hand |
| **2** | M + Enter | `MO(_L7)` | Layer 7 from right hand |
| **3** | ESC + Backspace | `TG(_L3)` | Toggle numbers/nav layer |
| **4** | Q + W + E + T | `QK_BOOT` | Bootloader (left hand) ⚠️ |
| **5** | Y + I + O + P | `QK_BOOT` | Bootloader (right hand) ⚠️ |
| **6** | Outer Left Thumb + Outer Right Thumb | `KC_CAPS` | Caps Lock toggle |
| **7** | (empty) | - | Available for customization |

⚠️ **Warning**: The bootloader combos will immediately enter flashing mode!

## The Code

The defaults are set in `eeconfig_init_user()`:

```c
void eeconfig_init_user(void) {
    // Combo 0: Middle thumb keys -> Layer 7
    vial_combo_entry_t combo = {0};
    combo.input[0] = LGUI_T(KC_SPC);
    combo.input[1] = LGUI_T(KC_ENT);
    combo.output = MO(_L7);
    dynamic_keymap_set_combo(0, &combo);
    
    // ... more combos ...
    
    // Reload combos to activate them
    vial_init();
}
```

## Important Notes

### Defaults vs User Customization

- ✅ **Defaults are only applied once** - When EEPROM is initialized
- ✅ **User changes are preserved** - Editing combos in Vial GUI overwrites defaults
- ✅ **Can be restored** - Reset EEPROM to get defaults back
- ❌ **Not re-applied on every boot** - Only when EEPROM is reset

### How to Reset to Defaults

If you want to restore the default combos:

**Option 1: Via Vial GUI**
1. Open Vial application
2. Go to Settings/Security tab
3. Click "Reset EEPROM"
4. Confirm the action
5. Defaults will be reloaded

**Option 2: Via Key Combo** (if you set one up)
- Map a key to `QK_CLEAR_EEPROM`
- Press that key
- Keyboard will reset and reload defaults

**Option 3: Reflash Firmware**
- Flash the `cheapino_vial.uf2` file again
- This will reset EEPROM on first boot

### Customizing Defaults

To change what defaults are shipped:

1. **Edit the keymap.c file**
2. **Modify the `eeconfig_init_user()` function**
3. **Change the combo definitions**:
   ```c
   combo.input[0] = YOUR_KEY_1;
   combo.input[1] = YOUR_KEY_2;
   combo.output = YOUR_ACTION;
   ```
4. **Recompile**: `make cheapino:vial`
5. **Flash the new firmware**

## Technical Details

### Why This Works

Vial's combo system consists of:
- **Dynamic storage**: Combos stored in EEPROM (persistent)
- **Runtime API**: `dynamic_keymap_set_combo()` to modify combos
- **Initialization hook**: `eeconfig_init_user()` called on EEPROM reset

This design allows:
- Defaults set via code during initialization
- User customization via GUI during normal use
- Restoration of defaults when needed

### Combo Data Structure

```c
typedef struct {
    uint16_t input[4];   // Up to 4 keys in the combo
    uint16_t output;      // Action when combo triggers
} vial_combo_entry_t;
```

### Limitations

- **Maximum 4 keys per combo** - Due to `input[4]` array size
- **8 combo slots** - Configured via `VIAL_COMBO_ENTRIES 8`
- **Keycodes must match exactly** - Including modifiers like `LGUI_T()`

## Comparison with Standard QMK

| Feature | Standard QMK | Vial |
|---------|-------------|------|
| **Combo definition** | Hardcoded in C arrays | Dynamic via EEPROM |
| **Default combos** | Yes (hardcoded) | Yes (via `eeconfig_init_user`) |
| **Runtime editing** | No (requires recompile) | Yes (via GUI) |
| **Conflicts** | Multiple definitions possible | Single system only |
| **Storage** | Program memory (flash) | EEPROM |

## Best Practices

### Do:
- ✅ Set sensible defaults for essential combos (like Layer access)
- ✅ Document your defaults in comments
- ✅ Test defaults after EEPROM reset
- ✅ Provide a way to reset EEPROM (bootloader combos)

### Don't:
- ❌ Set too many defaults (leave room for user customization)
- ❌ Use dangerous defaults (like reset without confirmation)
- ❌ Assume defaults persist after user edits them
- ❌ Mix hardcoded combos with Vial's dynamic system

## Troubleshooting

### "Defaults aren't loading"

**Check**:
1. Is `VIAL_COMBO_ENABLE` defined? (should be automatic with Vial)
2. Is `eeconfig_init_user()` wrapped in `#ifdef VIAL_COMBO_ENABLE`?
3. Did you call `vial_init()` after setting combos?
4. Did EEPROM actually reset? (try forcing a reset)

### "Combos work but defaults don't"

**Likely causes**:
- EEPROM wasn't reset - defaults only load on initialization
- User already configured combos - user settings override defaults
- Solution: Reset EEPROM to trigger defaults

### "Getting compile errors"

**Common issues**:
```c
// ❌ Wrong - missing header
vial_combo_entry_t combo = {0};

// ✅ Correct - include headers
#ifdef VIAL_COMBO_ENABLE
#include "vial.h"
#include "dynamic_keymap.h"
#endif
```

## FAQ

**Q: Will defaults override my custom combos?**  
A: No. Defaults only load when EEPROM is initialized/reset. Your custom combos are safe.

**Q: Can I have more than 8 combos?**  
A: Not without recompiling. Change `VIAL_COMBO_ENTRIES` in config.h and rebuild.

**Q: Do I need to set all 8 slots?**  
A: No. Unset slots remain empty and available for user configuration.

**Q: Can defaults use macros or complex actions?**  
A: Yes, as long as the keycode is valid. However, macros need to be defined separately.

**Q: Why use defaults instead of hardcoded combos?**  
A: Defaults give users a starting point while still allowing full customization via GUI.

## Summary

The Vial keymap for Cheapino includes:
- ✅ **7 pre-configured default combos** for essential functions
- ✅ **User-editable via GUI** - change any combo without recompiling
- ✅ **Restorable** - reset EEPROM to get defaults back
- ✅ **1 empty slot** for user's custom combo

This provides the best of both worlds: useful defaults out of the box, with full flexibility for customization.

---

**See also**:
- `COMBO_SETUP_GUIDE.md` - How to configure combos in Vial GUI
- `COMBOS_QUICKSTART.md` - Quick reference for combo setup
- `readme.md` - General Vial keymap information