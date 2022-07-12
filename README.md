![Image](https://blog.apnic.net/wp-content/uploads/2021/04/Linux-icon-magnifying-glass-768x281.png?v=7942c88983856a0fe9e1afac13675caa)
# MemPenguin
A process information gathering tool.  View and inspect memory mappings and loaded module information.

## About

Uses [LinuxOverlay](https://github.com/Rwkeith/LinuxOverlay) for the UI.

## Features

* Console window


* Process window

<img src="https://i.imgur.com/SJuEBaT.png" width="300">

## Usage
Position overlay using arrow keys.  Use Numpad +/- for changing the position interval.  Default size is 2560, 1440.  This can be changed with Numpad 1/2 and 4/5. Press insert key to toggle the overlay.

## Building

Uses Meson with Ninja to build.

```
meson builddir
ninja -C builddir
```

Then Run
```
sudo ./builddir/MemPenguin
```
