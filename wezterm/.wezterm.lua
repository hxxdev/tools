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
config.window_background_image = '\\\\wsl.localhost\\Ubuntu-24.04\\home\\hxxdev\\dev\\tools\\wallpapers\\jp.png'

config.default_prog = { "wsl.exe" }
config.font = wezterm.font("Hack Nerd Font", { weight = "Regular", italic = false })
-- Finally, return the configuration to wezterm:
config.keys = {
    {
      key = '"',
      mods = 'CTRL|SHIFT',
      action = wezterm.action.SplitHorizontal { domain = 'CurrentPaneDomain' },
    },
    {
      key = '%',
      mods = 'CTRL|SHIFT',
      action = wezterm.action.SplitVertical { domain = 'CurrentPaneDomain' },
    },
    {
      key = 'x',
      mods = 'CTRL|SHIFT',
      action = wezterm.action.CloseCurrentPane { confirm = true },
    },
    {
      key = 'h',
      mods = 'CTRL|SHIFT',
      action = wezterm.action.AdjustPaneSize { 'Left', 5 },
    },
    {
      key = 'l',
      mods = 'CTRL|SHIFT',
      action = wezterm.action.AdjustPaneSize { 'Right', 5 },
    },
    {
      key = 'k',
      mods = 'CTRL|SHIFT',
      action = wezterm.action.AdjustPaneSize { 'Up', 2 },
    },
    {
      key = 'j',
      mods = 'CTRL|SHIFT',
      action = wezterm.action.AdjustPaneSize { 'Down', 2 },
    },
    {
      key = 'h',
      mods = 'ALT',
      action = wezterm.action.ActivatePaneDirection 'Left',
    },
    {
      key = 'l',
      mods = 'ALT',
      action = wezterm.action.ActivatePaneDirection 'Right',
    },
    {
      key = 'k',
      mods = 'ALT',
      action = wezterm.action.ActivatePaneDirection 'Up',
    },
    {
      key = 'j',
      mods = 'ALT',
      action = wezterm.action.ActivatePaneDirection 'Down',
    },
  }
return config
