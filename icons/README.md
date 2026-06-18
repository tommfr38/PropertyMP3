# App icons

Drop your icon files here with these exact names, then re-run CMake:

| Platform | File                  | Used for                          |
|----------|-----------------------|-----------------------------------|
| macOS    | `PropertyMP3.icns`    | `.app` bundle / Dock icon         |
| Windows  | `PropertyMP3.ico`     | `.exe` icon (via `app.rc`)        |

`app.rc` is the Windows resource script that embeds `PropertyMP3.ico` into the
executable — don't rename it.

Both icons are optional: if a file is missing, the app still builds with the
default icon. After adding a file, regenerate the build so CMake picks it up:

```sh
cmake -S . -B build
cmake --build build
```

## Making the icon files (for reference)

**macOS `.icns`** from a 1024×1024 `icon.png`:
```sh
mkdir icon.iconset
sips -z 16 16     icon.png --out icon.iconset/icon_16x16.png
sips -z 32 32     icon.png --out icon.iconset/icon_16x16@2x.png
sips -z 32 32     icon.png --out icon.iconset/icon_32x32.png
sips -z 64 64     icon.png --out icon.iconset/icon_32x32@2x.png
sips -z 128 128   icon.png --out icon.iconset/icon_128x128.png
sips -z 256 256   icon.png --out icon.iconset/icon_128x128@2x.png
sips -z 256 256   icon.png --out icon.iconset/icon_256x256.png
sips -z 512 512   icon.png --out icon.iconset/icon_256x256@2x.png
sips -z 512 512   icon.png --out icon.iconset/icon_512x512.png
cp icon.png       icon.iconset/icon_512x512@2x.png
iconutil -c icns icon.iconset -o PropertyMP3.icns
```

**Windows `.ico`** (e.g. with ImageMagick), bundling several sizes:
```sh
magick icon.png -define icon:auto-resize=16,32,48,64,128,256 PropertyMP3.ico
```
