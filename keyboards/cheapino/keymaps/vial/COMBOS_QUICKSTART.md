# Quick Start: Configuring Combos in Vial

## Important: Combos Must Be Configured in Vial GUI

**This Vial keymap does NOT include hardcoded combos.** You must configure them using the Vial application.

### Why?
- Vial uses a dynamic combo system that conflicts with hardcoded C combos
- The firmware has `"combo": false` in keyboard.json to avoid conflicts
- You get 8 configurable combo slots in the Vial GUI

## Setup Steps

### 1. Install and Open Vial
1. Download from [get.vial.today](https://get.vial.today/)
2. Flash `cheapino_vial.uf2` to your keyboard
3. Launch Vial - your keyboard should be detected
4. Click the **"Combos"** tab

### 2. Configure Middle Thumb Keys Combo (Most Important)

This gives you quick access to Layer 7 (RGB & media controls):

1. **Select combo slot 0**
2. **Click left middle thumb** (the Space key)
3. **Click right middle thumb** (the Enter key)
4. **In Output dropdown**: Select `MO(7)` or "Momentary Layer 7"
5. **Done!** Press both middle thumbs together to test

### 3. Other Recommended Combos

Configure these in the remaining slots:

| Slot | Keys | Output | Purpose |
|------|------|--------|---------|
| 1 | V + Space | MO(7) | Layer 7 from left hand |
| 2 | M + Enter | MO(7) | Layer 7 from right hand |
| 3 | ESC + Backspace | TG(3) | Toggle numbers/nav layer |
| 4 | Q+W+E+T | QK_BOOT | Bootloader (left) ⚠️ |
| 5 | Y+I+O+P | QK_BOOT | Bootloader (right) ⚠️ |
| 6 | Outer Left Thumb + Outer Right Thumb | KC_CAPS | Caps Lock |
| 7 | (empty) | - | Your custom combo |

⚠️ Bootloader combos will immediately enter flashing mode!

## Quick Tips

### Combo Not Triggering?
- **Press keys more simultaneously** - within 50ms
- **Increase timing**: In Vial combo settings, try 75-100ms
- **Tap, don't hold**: Especially for thumb keys with dual functions

### Combo Triggering Accidentally?
- **Decrease timing** to 30-40ms
- **Pick different keys** that aren't adjacent

### Middle Thumbs Not Working?
- Keys have `GUI` when held - you must **tap quickly**
- Try **increasing combo timing to 100ms**
- Press **very simultaneously**

## How to Use Layer 7 (RGB Controls)

Once configured, Layer 7 combo gives you:
- **RGB controls**: Toggle, mode, hue, saturation, brightness
- **Media keys**: Play/pause, next/previous, volume
- **Brightness**: Screen brightness controls

## Configuration is Saved Automatically

Changes in Vial are saved to keyboard EEPROM immediately. No need to flash again!

## Need More Details?

See `COMBO_SETUP_GUIDE.md` for comprehensive instructions and troubleshooting.

---

**Quick Reference Card**

```
Middle Thumbs Together → Layer 7 (RGB/Media)
V + Space → Layer 7
M + Enter → Layer 7
ESC + Backspace → Toggle Layer 3
```
