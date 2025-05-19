-- Pull in the wezterm API
local wezterm = require 'wezterm'

-- This will hold the configuration.
local config = wezterm.config_builder()

-- This is where you actually apply your config choices.

-- For example, changing the initial geometry for new windows:
config.initial_cols = 120
config.initial_rows = 28

-- or, changing the font size and color scheme.
config.font_size = 10
-- config.color_scheme = 'AdventureTime'
config.color_scheme = "Catppuccin Mocha"
config.text_background_opacity = 0.3
config.window_background_opacity = 0.5
config.window_background_image = '/path/to/image'

config.default_prog = { "wsl.exe" }
config.font = wezterm.font("Hack Nerd Font", { weight = "Regular", italic = false })
-- Finally, return the configuration to wezterm:
return config
