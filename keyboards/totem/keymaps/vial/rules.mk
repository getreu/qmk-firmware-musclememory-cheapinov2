LTO_ENABLE = yes
VIA_ENABLE = yes
VIAL_ENABLE = yes
# P3(a): source is authoritative for tap-hold behaviour. Also required so
# that chordal_hold.c's get_chordal_hold() does not collide with the strong,
# unconditional definition qmk_settings.c compiles in when this is "yes".
QMK_SETTINGS = no
DYNAMIC_KEYMAP_LAYER_COUNT = 16
SPLIT_KEYBOARD = yes

# Enable features
COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
MACRO_ENABLE = yes         # standard QMK macros
DYNAMIC_MACRO_ENABLE = yes # dynamic macros (record on the keyboard)
MOUSEKEY_ENABLE = yes

