# Spotipi
Tugas Responshit 2 KP buat spotify-spotify an.

Program pakai header:
```
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
```

Download masing-masing header tambahan dan path /bin/ masukkan ke windows environment.

Link Download
- [SDL2](https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-devel-2.28.5-mingw.zip)
- [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.6.3/SDL2_mixer-devel-2.6.3-mingw.zip)
- [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-devel-2.20.2-mingw.zip)
- [SDL2_image](https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.1/SDL2_image-devel-2.8.1-mingw.zip)

Cara Compile:
```shell
g++ spotipi.c -IC:\mingw_dev_lib\include -LC:\mingw_dev_lib\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -o spotipi
```

`mingw_dev_lib` sesuain nama folder buat simpan mingw.
