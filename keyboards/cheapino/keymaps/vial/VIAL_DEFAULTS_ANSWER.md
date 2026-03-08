# Does Vial Provide a Way to Ship Defaults for Combos and Tap Dances?

## Short Answer

**YES!** Vial supports shipping default combos and tap dances using the `eeconfig_init_user()` function.

## How It Works

Vial's dynamic combo and tap dance systems store configurations in EEPROM. When EEPROM is initialized (first flash or reset), the `eeconfig_init_user()` function is called, allowing you to programmatically set default values.

## Implementation Example

### Default Combos

```c
#ifdef VIAL_COMBO_ENABLE
#include "vial.h"
#include "dynamic_keymap.h"

void eeconfig_init_user(void) {
    // Combo 0: Space + Enter -> Layer 7
    {
        vial_combo_entry_t combo = {0};
        combo.input[0] = KC_SPC;
        combo.input[1] = KC_ENT;
        combo.output = MO(7);
        dynamic_keymap_set_combo(0, &combo);
    }
    
    // Combo 1: Q+W+E+R -> Bootloader
    {
        vial_combo_entry_t combo = {0};
        combo.input[0] = KC_Q;
        combo.input[1] = KC_W;
        combo.input[2] = KC_E;
        combo.input[3] = KC_R;
        combo.output = QK_BOOT;
        dynamic_keymap_set_combo(1, &combo);
    }
    
    // Reload combos to activate
    vial_init();
}
#endif
```

### Default Tap Dances

```c
#ifdef VIAL_TAP_DANCE_ENABLE
void eeconfig_init_user(void) {
    // Tap dance 0: Single tap = ESC, Double tap = Caps Lock
    {
        vial_tap_dance_entry_t td = {0};
        td.on_tap = KC_ESC;
        td.on_double_tap = KC_CAPS;
        td.on_hold = KC_LCTL;
        td.on_tap_hold = KC_LCTL;
        td.custom_tapping_term = 200;
        dynamic_keymap_set_tap_dance(0, &td);
    }
    
    // Reload tap dances
    vial_init();
}
#endif
```

## When Defaults Are Applied

Defaults load when EEPROM is initialized:

1. **First flash** - When flashing Vial firmware for the first time
2. **EEPROM reset** - Manual reset via Vial GUI or `QK_CLEAR_EEPROM`
3. **Corrupted EEPROM** - Automatic reset if EEPROM data is invalid

## Important Characteristics

### One-Time Application
- ✅ Defaults are applied **only during EEPROM initialization**
- ✅ User modifications via Vial GUI **persist** across reboots
- ✅ User changes are **not overwritten** on subsequent boots
- ❌ Defaults do **not re-apply** every time the keyboard starts

### User Customization Preserved
```
First Boot:          User Edits Combo:      Next Boot:
EEPROM Init          Via Vial GUI           EEPROM Preserved
   ↓                      ↓                       ↓
Defaults Load  →  User Combo Saved  →  User Combo Remains
```

## Data Structures

### Combo Entry
```c
typedef struct {
    uint16_t input[4];   // Up to 4 keys
    uint16_t output;     // Output keycode
} vial_combo_entry_t;
```

### Tap Dance Entry
```c
typedef struct {
    uint16_t on_tap;           // Single tap action
    uint16_t on_hold;          // Hold action
    uint16_t on_double_tap;    // Double tap action
    uint16_t on_tap_hold;      // Tap then hold action
    uint16_t custom_tapping_term;  // Timing in ms
} vial_tap_dance_entry_t;
```

## API Functions

### Combos
```c
// Set a combo (index 0-7 by default)
int dynamic_keymap_set_combo(uint8_t index, const vial_combo_entry_t *entry);

// Get a combo
int dynamic_keymap_get_combo(uint8_t index, vial_combo_entry_t *entry);

// Number of combo slots
#define VIAL_COMBO_ENTRIES 8
```

### Tap Dances
```c
// Set a tap dance (index 0-3 by default)
int dynamic_keymap_set_tap_dance(uint8_t index, const vial_tap_dance_entry_t *entry);

// Get a tap dance
int dynamic_keymap_get_tap_dance(uint8_t index, vial_tap_dance_entry_t *entry);

// Number of tap dance slots
#define VIAL_TAP_DANCE_ENTRIES 4
```

## Configuration

### Enable Features
```c
// config.h
#define VIAL_KEYBOARD_UID {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0}
#define VIAL_COMBO_ENTRIES 8
#define VIAL_TAP_DANCE_ENTRIES 4
```

### Enable in Rules
```make
# rules.mk
VIA_ENABLE = yes
VIAL_ENABLE = yes
```

### Disable Conflicting Features
```json
// keyboard.json
"features": {
    "combo": false,        // Disable QMK combos (conflicts with Vial)
    "tap_dance": true      // Enable for Vial
}
```

## Best Practices

### Do ✅
- Set sensible defaults for essential functions
- Leave some slots empty for user customization
- Document your defaults in code comments
- Test after EEPROM reset to verify defaults
- Use `vial_init()` after setting defaults

### Don't ❌
- Fill all slots (leave room for users)
- Use dangerous defaults without documentation
- Assume defaults persist after user edits
- Mix hardcoded QMK combos with Vial's dynamic system
- Forget to wrap in `#ifdef VIAL_COMBO_ENABLE`

## Comparison: Vial vs Standard QMK

| Aspect | Standard QMK | Vial with Defaults |
|--------|-------------|-------------------|
| **Definition** | Hardcoded C arrays | `eeconfig_init_user()` |
| **Storage** | Program memory (Flash) | EEPROM |
| **User editing** | Requires recompile | Via GUI |
| **Defaults** | Always active | Applied on init only |
| **Persistence** | Fixed in firmware | User changes persist |
| **Conflicts** | Can have duplicates | Single system |

## Practical Example: Cheapino Keyboard

The Cheapino Vial keymap ships with 7 default combos:

```c
void eeconfig_init_user(void) {
    // Combo 0: Middle thumbs -> Layer 7 (RGB/Media)
    // Combo 1: V + Space -> Layer 7
    // Combo 2: M + Enter -> Layer 7
    // Combo 3: ESC + Backspace -> Toggle Layer 3
    // Combo 4: Q+W+E+T -> Bootloader
    // Combo 5: Y+I+O+P -> Bootloader
    // Combo 6: Outer thumbs -> Caps Lock
    // Slot 7: Empty for user customization
    
    vial_init();  // Activate all defaults
}
```

Users get working combos immediately, but can customize any of them via the Vial GUI.

## Restoring Defaults

Users can restore defaults by resetting EEPROM:

**Via Vial GUI:**
- Settings → Security → Reset EEPROM

**Via Keycode:**
- Map a key to `QK_CLEAR_EEPROM`

**Via Reflash:**
- Flash firmware again (triggers init)

## Troubleshooting

### Defaults Not Loading

**Check:**
1. `VIAL_COMBO_ENABLE` or `VIAL_TAP_DANCE_ENABLE` defined?
2. Headers included (`vial.h`, `dynamic_keymap.h`)?
3. Called `vial_init()` after setting defaults?
4. EEPROM actually reset? (try forcing reset)

### Compile Errors

```c
// ❌ Missing headers
void eeconfig_init_user(void) {
    vial_combo_entry_t combo = {0};  // Error: unknown type
}

// ✅ Correct
#ifdef VIAL_COMBO_ENABLE
#include "vial.h"
#include "dynamic_keymap.h"

void eeconfig_init_user(void) {
    vial_combo_entry_t combo = {0};  // OK
}
#endif
```

## Limitations

1. **Combo keys**: Maximum 4 keys per combo
2. **Combo slots**: Default 8 (configurable)
3. **Tap dance slots**: Default 4 (configurable)
4. **Keycode matching**: Must match exactly (including modifiers)
5. **One-time load**: Only on EEPROM init, not every boot

## Advantages of This Approach

1. **Best of both worlds**
   - Useful defaults out-of-the-box
   - Full user customization available

2. **No compilation needed**
   - Users can modify without toolchain
   - Changes take effect immediately

3. **Portable configurations**
   - Users can save/load via Vial GUI
   - Share configurations as .vil files

4. **Backward compatible**
   - Works with all Vial versions
   - Standard Vial API, no hacks

## Conclusion

**YES, Vial fully supports shipping defaults** for both combos and tap dances through the `eeconfig_init_user()` function. This provides manufacturers and keyboard designers with the ability to ship sensible defaults while still giving users the full power of Vial's GUI-based customization.

The implementation is straightforward, well-documented, and follows standard Vial patterns. It's the recommended approach for providing default combos and tap dances in Vial-enabled keyboards.

---

**Related Documentation:**
- `DEFAULT_COMBOS.md` - Detailed default combo implementation
- `COMBO_SETUP_GUIDE.md` - How to configure combos in Vial GUI  
- `COMBOS_QUICKSTART.md` - Quick reference guide

**Vial Resources:**
- https://get.vial.today/docs/
- https://github.com/vial-kb/vial-qmk