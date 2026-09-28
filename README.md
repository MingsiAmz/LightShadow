# LightShadow

A small 2D light and shadow simulation built with SDL2. The program draws a light source and a target circle in the window. The light source emits rays in all directions, and the rays are blocked when they hit the target circle, casting a shadow behind it.

## Features

- Real-time ray casting: rays are emitted uniformly in all directions from the light source
- Shadow occlusion: rays stop propagating when they hit the target circle, forming a shadow
- Distance attenuation: rays grow dimmer the farther they travel from the light source (grayscale gradient)
- Mouse dragging: drag the target circle or the light source to reposition them
- Keyboard exit: press `Q` to quit

## Dependencies

- A C compiler (e.g. `gcc`)
- SDL2 development library
- Math library `libm`

### Installing SDL2

**Ubuntu / Debian:**
```bash
sudo apt install libsdl2-dev
```

**macOS (Homebrew):**
```bash
brew install sdl2
```

**Windows (MSYS2):**
```bash
pacman -S mingw-w64-x86_64-SDL2
```

## Build

```bash
gcc main.c circle.c ray.c -o lightshadow -lSDL2 -lm
```

## Run

```bash
./lightshadow
```

## Controls

| Action | Effect |
| --- | --- |
| Hold and drag the target circle | Move the illuminated circle |
| Hold and drag the light source | Move the light source |
| Press `Q` / close the window | Quit the program |

## Known Issues / Possible Improvements

- Ray steps are a fixed 1 pixel, so circle edges may appear jagged; sub-pixel sampling or anti-aliasing could improve this.
- Ray angles are regenerated every frame, causing slight jitter; the `angle` accumulation could be moved out of `fillRays`.
- Only a single occluding circle is supported; this could be extended to multiple circles or arbitrary polygons.
- The grayscale falloff is based on `step / width`, so the ratio may be inconsistent in non-square windows.

## License

No license is specified for this project. It is free to use for learning and personal purposes.
