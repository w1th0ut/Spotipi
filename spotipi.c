// Bagas Rizki Gunardi
// L0123034

/*
Program SPOTIPI Music Player

Program C sederhana SPOTIPI yang digunakan untuk music player.
Program bisa menambahkan lagu yang terdiri dari judul lagu, artis, dan durasi lagu.
Program bisa menampilkan lagu yang sudah di tambah sebelumnya.
Program bisa memainkan lagu untuk diputar.
Program bisa membuat playlist yang terdiri dari judul dan lagu-lagu yang ingin dimasukkan.
Program bisa melihat history lagu yang sudah di mainkan sebelumnya.
Program bisa menampilkan GUI untuk program SPOTIPI yang dapat memainkan lagu Sudah - Ardhito Pramono.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#define MUS_PATH "music/sudah.wav"

typedef struct Lagu {
    char judul[50];
    char artis[50];
    int durasi;
    struct Lagu *next;
} Lagu;

typedef struct Playlist {
    char nama[50];
    Lagu *daftar_lagu;
} Playlist;

typedef struct History {
    Lagu *lagu;
    struct History *next;
} History;

Lagu *lagu_masuk(Lagu *head, Lagu *lagu_baru) {
    lagu_baru->next = head;
    return lagu_baru;
}

Lagu *buat_lagu(const char *judul, const char *artis, int durasi) {
    Lagu *lagu = (Lagu*)malloc(sizeof(Lagu));
    strcpy(lagu->judul, judul);
    strcpy(lagu->artis, artis);
    lagu->durasi = durasi;
    return lagu;
}

void masukkan_lagu(Lagu **head) {
    char judul[50], artis[50];
    int durasi;

    printf("\n\t\tMasukkan judul lagu: ");
    scanf("%s", judul);

    printf("\t\tMasukkan artis lagu: ");
    scanf("%s", artis);

    printf("\t\tMasukkan durasi lagu (detik): ");
    scanf("%d", &durasi);

    Lagu *lagu = buat_lagu(judul, artis, durasi);
    *head = lagu_masuk(*head, lagu);
    printf("\t\tLagu berhasil dimasukkan!\n");

    getchar();
    printf("\n\t\tPress Enter to continue...");
    getchar();
}

Playlist *buat_playlist(char *nama) {
    Playlist *playlist = (Playlist*)malloc(sizeof(Playlist));
    strcpy(playlist->nama, nama);
    playlist->daftar_lagu = NULL;
    return playlist;
}

History *history_masuk(History *head, Lagu *lagu) {
    History *history_baru = (History *)malloc(sizeof(History));
    history_baru->lagu = lagu;
    history_baru->next = head;
    return history_baru;
}

void putar_lagu(Lagu *head,  History **history) {
    if (head == NULL) {
        printf("\t\tDaftar lagu kosong\n");
        return;
    }

    int pilihan;
    printf("\t\tPilih lagu untuk diputar: ");
    scanf("%d", &pilihan);

    Lagu *lagu = head;
    for (int i = 1; i < pilihan && lagu != NULL; ++i) {
        lagu = lagu->next;
    }

    if (lagu == NULL) {
        printf("\t\tLagu tidak ditemukan\n");
    } else {
        printf("\n\t\tMemutar lagu: %s - %s (%d detik)\n\n", lagu->judul, lagu->artis, lagu->durasi);
        *history = history_masuk(*history, lagu);
        // Assume the progress bar should be divided into 10 segments
    	int totalSegments = 10;
    	int segmentDuration = lagu->durasi / totalSegments;

    	for (int i = 0; i < totalSegments; ++i) {
    	    printf("\t\t[");
    	    for (int j = 0; j < i; ++j) {
    	        printf("-");
    	    }
    	    for (int j = i; j < totalSegments; ++j) {
    	        printf(" ");
    	    }
    	    printf("] (Tekan [END] Untuk Mengakhiri)");

    	    fflush(stdout);

    	    Sleep(lagu->durasi * 100);

    	    printf("\r");
    	    fflush(stdout);
    	    if (GetAsyncKeyState(VK_END)) {
				break;
			}
    	}

    printf("\n\n\t\tLagu selesai!\n");

    }

    getchar();
    printf("\n\t\tPress Enter to continue...");
    getchar();
}

void lihat_playlist(Playlist *playlist) {
    printf("\n\t\tDaftar playlist: %s\n", playlist->nama);
    if (playlist->daftar_lagu == NULL) {
        printf("\t\tPlaylist kosong\n");
    } else {
        for (Lagu *lagu = playlist->daftar_lagu; lagu != NULL; lagu = lagu->next) {
            printf("\t\t- %s - %s (%d detik)\n", lagu->judul, lagu->artis, lagu->durasi);
        }
    }
    getchar();
    printf("\n\t\tPress Enter to continue...");
    getchar();
}

void tampilkan_daftar_lagu(Lagu *head) {
    int index = 1;
    printf("\t\tDaftar Lagu:\n");
    for (Lagu *lagu = head; lagu != NULL; lagu = lagu->next) {
        printf("\t\t%d. %s - %s (Durasi %d detik)\n", index++, lagu->judul, lagu->artis, lagu->durasi);
    }
}

void buat_playlist(Lagu **daftar_lagu, Playlist **playlist) {
    char nama_playlist[50];
    printf("\n\t\tMasukkan nama playlist: ");
    scanf("%s", nama_playlist);

    Playlist *playlist_baru = buat_playlist(nama_playlist);

    int pilihan;
    do {
        printf("\t\tPilih lagu untuk dimasukkan ke playlist (0 untuk keluar): ");
        scanf("%d", &pilihan);

        if (pilihan != 0) {
            Lagu *lagu = daftar_lagu[pilihan - 1];
            playlist_baru->daftar_lagu = lagu_masuk(playlist_baru->daftar_lagu, lagu);
        }
    } while (pilihan != 0);

    *playlist = playlist_baru;
    getchar();
    printf("\n\t\tPress Enter to continue...");
    getchar();
}

void lihat_history(History *history) {
    printf("\n\t\tDaftar lagu yang sudah diputar:\n");
    int index = 1;
    for (History *node = history; node != NULL; node = node->next) {
        Lagu *lagu = node->lagu;
        printf("\t\t%d. %s - %s (Durasi %d detik)\n", index++, lagu->judul, lagu->artis, lagu->durasi);
    }
    getchar();
    printf("\n\t\tPress Enter to continue...");
    getchar();
}

int banner() {

	printf("\t\t=========================\n");
	printf("\t\t= SPOTIPI Music Player  =\n");
	printf("\t\t=     Made by Bagas     =\n");
	printf("\t\t=========================\n");

}

void my_audio_callback(void *userdata, Uint8 *stream, int len);

static Uint8 *audio_pos;
static Uint32 audio_len;
static bool is_playing = false;
static Uint32 wav_length;
static Uint8 *wav_buffer;
static SDL_AudioSpec wav_spec;
static double totalDuration;
static double elapsedTime = 0;

SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
    if (texture == NULL) {
        fprintf(stderr, "Couldn't load texture: %s\n", SDL_GetError());
        return NULL;
    }
    return texture;
}

int play_GUI() {

    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
        return 1;
    }

    // Inisialisasi SDL_ttf
    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Buat window untuk menampilkan tombol
    SDL_Window *window = SDL_CreateWindow("SPOTIPI by Bagas", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, 0);
    if (window == NULL) {
        fprintf(stderr, "Couldn't create window: %s\n", SDL_GetError());
        return 1;
    }

    // Buat renderer untuk menggambar tombol
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL) {
        fprintf(stderr, "Couldn't create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return 1;
    }

  	// Inisialisasi SDL_mixer
  	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    	return 1;
  	}

    // Load audio
    if (SDL_LoadWAV(MUS_PATH, &wav_spec, &wav_buffer, &wav_length) == NULL) {
        return 1;
    }

    wav_spec.callback = my_audio_callback;
    wav_spec.userdata = NULL;
    audio_pos = wav_buffer;
    audio_len = wav_length;

    if (SDL_OpenAudio(&wav_spec, NULL) < 0) {
        fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_FreeWAV(wav_buffer);
        return -1;
    }

    // Load font
    TTF_Font *font = TTF_OpenFont("font/font.ttf", 24);
    if (font == NULL) {
        fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
        SDL_CloseAudio();
        SDL_FreeWAV(wav_buffer);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return 1;
    }

    // Main loop
    SDL_Texture *button_texture = NULL;
    SDL_Surface *button_surface = NULL;
    SDL_Color white = {255, 255, 255};
    SDL_Color black = {0, 0, 0};
    bool running = true;

// Load button texture
SDL_Texture* buttonTexture = loadTexture("assets/pause_button.png", renderer);
SDL_Texture* buttonTexturePrev = loadTexture("assets/prev_button.png", renderer);
SDL_Texture* buttonTextureNext = loadTexture("assets/next_button.png", renderer);
SDL_Texture* buttonTextureVolume = loadTexture("assets/volume.png", renderer);
SDL_Texture* buttonTextureProfile = loadTexture("assets/account.png", renderer);
SDL_Texture* buttonTextureSetting = loadTexture("assets/setting.png", renderer);
SDL_Texture* buttonTextureHome = loadTexture("assets/home.png", renderer);
SDL_Texture* buttonTextureSearch = loadTexture("assets/search.png", renderer);
SDL_Texture* buttonTextureNotif = loadTexture("assets/bell.png", renderer);
SDL_Texture* buttonTextureHeart = loadTexture("assets/heart.png", renderer);

// Load Image Music
SDL_Texture* imageTexture = loadTexture("images/sudah.jpg", renderer);
SDL_Texture* imageTexturePlaylist = loadTexture("images/playlist.png", renderer);
SDL_Texture* imageTexturePlaylist_2 = loadTexture("images/playlist_2.png", renderer);
SDL_Texture* imageTexturePlaylist_3 = loadTexture("images/playlist_3.png", renderer);

// Load Image History
SDL_Texture* imageTextureHistory = loadTexture("images/bitterlove.png", renderer);
SDL_Texture* imageTextureHistory_2 = loadTexture("images/itwillrain.png", renderer);
SDL_Texture* imageTextureHistory_3 = loadTexture("images/lethergo.png", renderer);

if (buttonTexture == NULL) {
    return 1;
}

SDL_Rect buttonRectHome;
buttonRectHome.x = 20;  // Letak horizontal tombol
buttonRectHome.y = 0; // Letak vertikal tombol
buttonRectHome.w = 25;  // Lebar tombol
buttonRectHome.h = 25;  // Tinggi tombol

SDL_Rect buttonRectSearch;
buttonRectSearch.x = 20;  // Letak horizontal tombol
buttonRectSearch.y = 30; // Letak vertikal tombol
buttonRectSearch.w = 25;  // Lebar tombol
buttonRectSearch.h = 25;  // Tinggi tombol

SDL_Rect buttonRectProfile;
buttonRectProfile.x = 540;  // Letak horizontal tombol
buttonRectProfile.y = 15; // Letak vertikal tombol
buttonRectProfile.w = 25;  // Lebar tombol
buttonRectProfile.h = 25;  // Tinggi tombol

SDL_Rect buttonRectSetting;
buttonRectSetting.x = 500;  // Letak horizontal tombol
buttonRectSetting.y = 15; // Letak vertikal tombol
buttonRectSetting.w = 25;  // Lebar tombol
buttonRectSetting.h = 25;  // Tinggi tombol

SDL_Rect buttonRectNotif;
buttonRectNotif.x = 460;  // Letak horizontal tombol
buttonRectNotif.y = 15; // Letak vertikal tombol
buttonRectNotif.w = 25;  // Lebar tombol
buttonRectNotif.h = 25;  // Tinggi tombol

SDL_Rect buttonRectHeart;
buttonRectHeart.x = 130;  // Letak horizontal tombol
buttonRectHeart.y = 340; // Letak vertikal tombol
buttonRectHeart.w = 15;  // Lebar tombol
buttonRectHeart.h = 15;  // Tinggi tombol

SDL_Rect buttonRect;
buttonRect.x = 275;  // Letak horizontal tombol
buttonRect.y = 320; // Letak vertikal tombol
buttonRect.w = 50;  // Lebar tombol
buttonRect.h = 50;  // Tinggi tombol

SDL_Rect buttonRectPrev;
buttonRectPrev.x = 200;  // Letak horizontal tombol
buttonRectPrev.y = 320; // Letak vertikal tombol
buttonRectPrev.w = 50;  // Lebar tombol
buttonRectPrev.h = 50;  // Tinggi tombol

SDL_Rect buttonRectNext;
buttonRectNext.x = 350;  // Letak horizontal tombol
buttonRectNext.y = 320; // Letak vertikal tombol
buttonRectNext.w = 50;  // Lebar tombol
buttonRectNext.h = 50;  // Tinggi tombol

SDL_Rect buttonRectVolume;
buttonRectVolume.x = 450;  // Letak horizontal tombol
buttonRectVolume.y = 330; // Letak vertikal tombol
buttonRectVolume.w = 25;  // Lebar tombol
buttonRectVolume.h = 25;  // Tinggi tombol

SDL_Rect imageTextureMusic;
imageTextureMusic.x = 200;  // Letak horizontal gambar
imageTextureMusic.y = 90; // Letak vertikal gambar
imageTextureMusic.w = 200;  // Lebar gambar
imageTextureMusic.h = 200;  // Tinggi gambar

SDL_Rect imageTexturePlay;
imageTexturePlay.x = 20;  // Letak horizontal gambar
imageTexturePlay.y = 110; // Letak vertikal gambar
imageTexturePlay.w = 50;  // Lebar gambar
imageTexturePlay.h = 50;  // Tinggi gambar

SDL_Rect imageTexturePlay_2;
imageTexturePlay_2.x = 20;  // Letak horizontal gambar
imageTexturePlay_2.y = 170; // Letak vertikal gambar
imageTexturePlay_2.w = 50;  // Lebar gambar
imageTexturePlay_2.h = 50;  // Tinggi gambar

SDL_Rect imageTexturePlay_3;
imageTexturePlay_3.x = 20;  // Letak horizontal gambar
imageTexturePlay_3.y = 230; // Letak vertikal gambar
imageTexturePlay_3.w = 50;  // Lebar gambar
imageTexturePlay_3.h = 50;  // Tinggi gambar

SDL_Rect imageTextureHis;
imageTextureHis.x = 530;  // Letak horizontal gambar
imageTextureHis.y = 110; // Letak vertikal gambar
imageTextureHis.w = 50;  // Lebar gambar
imageTextureHis.h = 50;  // Tinggi gambar

SDL_Rect imageTextureHis_2;
imageTextureHis_2.x = 530;  // Letak horizontal gambar
imageTextureHis_2.y = 170; // Letak vertikal gambar
imageTextureHis_2.w = 50;  // Lebar gambar
imageTextureHis_2.h = 50;  // Tinggi gambar

SDL_Rect imageTextureHis_3;
imageTextureHis_3.x = 530;  // Letak horizontal gambar
imageTextureHis_3.y = 230; // Letak vertikal gambar
imageTextureHis_3.w = 50;  // Lebar gambar
imageTextureHis_3.h = 50;  // Tinggi gambar

SDL_Rect bar_rect = {
  .x = 480,      // Position of the bar's top-left corner on the x-axis
  .y = 330,      // Position of the bar's top-left corner on the y-axis
  .w = 100,      // Width of the bar
  .h = 20       // Height of the bar
};

SDL_Rect knob_rect = {
  .x = bar_rect.x + bar_rect.w / 2, // Center on the bar
  .y = bar_rect.y,
  .w = 20,
  .h = 20
};

bool is_dragging_knob = false;
bool isButtonClicked = false;
int volume = 100;
totalDuration = (double)wav_length / wav_spec.freq;

// Main loop
while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                // Cek apakah klik pada tombol
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
                    mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h) {
                    is_playing = !is_playing;  // Toggle playback
                    if (is_playing) {
                        SDL_PauseAudio(0);  // Mulai audio
                    } else {
                        SDL_PauseAudio(1);  // Jeda audio
                    }
                    isButtonClicked = true;
                }
                SDL_Point mouse_point = {mouseX, mouseY};
                if (SDL_PointInRect(&mouse_point, &knob_rect)) {
                	is_dragging_knob = true; // Mulai drag
      				knob_rect.x = mouseX - knob_rect.w / 2; // Move knob with mouse
      				volume = (int)(((float)knob_rect.x - bar_rect.x) / bar_rect.w * 100);
            		volume = SDL_clamp(volume, 0, 100);  // Ensure volume is within the valid range
            		Mix_VolumeMusic(volume);
    			}
            }
        } else if (event.type == SDL_MOUSEMOTION && is_dragging_knob) {
        	int mouseX, mouseY; // Deklarasikan mouseX di sini
  			SDL_GetMouseState(&mouseX, &mouseY); // Dapatkan posisi mouse saat ini
    		knob_rect.x = mouseX - knob_rect.w / 2; // Perbarui posisi knob saat drag
    		knob_rect.x = SDL_clamp(knob_rect.x, bar_rect.x, bar_rect.x + bar_rect.w - knob_rect.w); // Clamp within bar
    		volume = (int)(((float)knob_rect.x - bar_rect.x) / bar_rect.w * 100);
            volume = SDL_clamp(volume, 0, 100);  // Ensure volume is within the valid range
            Mix_VolumeMusic(volume);
  		} else if (event.type == SDL_MOUSEBUTTONUP) {
    		is_dragging_knob = false; // Hentikan drag
  		}
    }

    // Render Warna Latar
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
    SDL_RenderFillRect(renderer, NULL);

    // Render Volume bar
    SDL_Surface* barTextureSurface = TTF_RenderText_Solid(font, "-", black);
    SDL_Texture* bar_texture = SDL_CreateTextureFromSurface(renderer, barTextureSurface);
    SDL_RenderCopy(renderer, bar_texture, NULL, &bar_rect);
    SDL_DestroyTexture(bar_texture);
    SDL_FreeSurface(barTextureSurface);

    SDL_Surface* knobTextureSurface = TTF_RenderText_Solid(font, "O", black);
	SDL_Texture* knob_texture = SDL_CreateTextureFromSurface(renderer, knobTextureSurface);
	SDL_RenderCopy(renderer, knob_texture, NULL, &knob_rect);
	SDL_DestroyTexture(knob_texture);
	SDL_FreeSurface(knobTextureSurface);

	// Render progres bar
	SDL_Rect progressBarRect;
	progressBarRect.x = 199;
	progressBarRect.y = 380;
	progressBarRect.w = (int)(200 * (elapsedTime / totalDuration));  // Panjang progres bar
	progressBarRect.h = 10;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(renderer, &progressBarRect);

	// Render the outline of the progress bar
	SDL_Rect outlineRect = {
    progressBarRect.x - 1,  // Shift the outline to the left
    progressBarRect.y - 1,  // Shift the outline upward
    200 + 2,  // Increase width to include the left and right outlines
    progressBarRect.h + 2   // Increase height to include the top and bottom outlines
	};

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Warna hitam untuk outline
	SDL_RenderDrawRect(renderer, &outlineRect);

    // Render tombol play/pause
    SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect);
    SDL_RenderCopy(renderer, buttonTexturePrev, NULL, &buttonRectPrev);
    SDL_RenderCopy(renderer, buttonTextureNext, NULL, &buttonRectNext);
    SDL_RenderCopy(renderer, buttonTextureVolume, NULL, &buttonRectVolume);
    SDL_RenderCopy(renderer, buttonTextureProfile, NULL, &buttonRectProfile);
    SDL_RenderCopy(renderer, buttonTextureSetting, NULL, &buttonRectSetting);
    SDL_RenderCopy(renderer, buttonTextureHome, NULL, &buttonRectHome);
    SDL_RenderCopy(renderer, buttonTextureSearch, NULL, &buttonRectSearch);
    SDL_RenderCopy(renderer, buttonTextureNotif, NULL, &buttonRectNotif);
    SDL_RenderCopy(renderer, buttonTextureHeart, NULL, &buttonRectHeart);

    // Render gambar
    SDL_RenderCopy(renderer, imageTexture, NULL, &imageTextureMusic);
    SDL_RenderCopy(renderer, imageTexturePlaylist, NULL, &imageTexturePlay);
    SDL_RenderCopy(renderer, imageTexturePlaylist_2, NULL, &imageTexturePlay_2);
    SDL_RenderCopy(renderer, imageTexturePlaylist_3, NULL, &imageTexturePlay_3);
    SDL_RenderCopy(renderer, imageTextureHistory, NULL, &imageTextureHis);
    SDL_RenderCopy(renderer, imageTextureHistory_2, NULL, &imageTextureHis_2);
    SDL_RenderCopy(renderer, imageTextureHistory_3, NULL, &imageTextureHis_3);
    
	// Render teks Home
    SDL_Surface* textSurfaceHome = TTF_RenderText_Solid(font, "Home", black);
    SDL_Texture* textTextureHome = SDL_CreateTextureFromSurface(renderer, textSurfaceHome);

    SDL_Rect textRectHome;
    textRectHome.x = 50;
    textRectHome.y = 5;
    textRectHome.w = 40;
    textRectHome.h = 20;

    SDL_RenderCopy(renderer, textTextureHome, NULL, &textRectHome);
    SDL_DestroyTexture(textTextureHome);
    SDL_FreeSurface(textSurfaceHome);

    // Render teks Search
    SDL_Surface* textSurfaceSearch = TTF_RenderText_Solid(font, "Search", black);
    SDL_Texture* textTextureSearch = SDL_CreateTextureFromSurface(renderer, textSurfaceSearch);

    SDL_Rect textRectSearch;
    textRectSearch.x = 50;
    textRectSearch.y = 30;
    textRectSearch.w = 45;
    textRectSearch.h = 22;

    SDL_RenderCopy(renderer, textTextureSearch, NULL, &textRectSearch);
    SDL_DestroyTexture(textTextureSearch);
    SDL_FreeSurface(textSurfaceSearch);

    // Render teks "SPOTIFI"
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "SPOTIPI Music", black);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect;
    textRect.x = (600 - textSurface->w) / 2;
    textRect.y = 10;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);

    // Render Pembatas 1
    SDL_Surface* textSurfaceGap = TTF_RenderText_Solid(font, "-", black);
    SDL_Texture* textTextureGap = SDL_CreateTextureFromSurface(renderer, textSurfaceGap);

    SDL_Rect textRectGap;
    textRectGap.x = -100;
    textRectGap.y = 50;
    textRectGap.w = 800;
    textRectGap.h = textSurfaceGap->h;

    SDL_RenderCopy(renderer, textTextureGap, NULL, &textRectGap);
    SDL_DestroyTexture(textTextureGap);
    SDL_FreeSurface(textSurfaceGap);

    // Render teks Judul Lagu
    SDL_Surface* textSurfaceTitle = TTF_RenderText_Solid(font, "Sudah", black);
    SDL_Texture* textTextureTitle = SDL_CreateTextureFromSurface(renderer, textSurfaceTitle);

    SDL_Rect textRectTitle;
    textRectTitle.x = 15;
    textRectTitle.y = 335;
    textRectTitle.w = 60;
    textRectTitle.h = 15;

    SDL_RenderCopy(renderer, textTextureTitle, NULL, &textRectTitle);
    SDL_DestroyTexture(textTextureTitle);
    SDL_FreeSurface(textSurfaceTitle);

    // Render teks Judul Lagu
    SDL_Surface* textSurfaceTitles = TTF_RenderText_Solid(font, "Ardhito Pramono", black);
    SDL_Texture* textTextureTitles = SDL_CreateTextureFromSurface(renderer, textSurfaceTitles);

    SDL_Rect textRectTitles;
    textRectTitles.x = 15;
    textRectTitles.y = 350;
    textRectTitles.w = 100;
    textRectTitles.h = 10;

    SDL_RenderCopy(renderer, textTextureTitles, NULL, &textRectTitles);
    SDL_DestroyTexture(textTextureTitles);
    SDL_FreeSurface(textSurfaceTitles);

    // Render teks history
    SDL_Surface* textSurfaceHistory = TTF_RenderText_Solid(font, "History", black);
    SDL_Texture* textTextureHistory = SDL_CreateTextureFromSurface(renderer, textSurfaceHistory);

    SDL_Rect textRectHistory;
    textRectHistory.x = 480;
    textRectHistory.y = 80;
    textRectHistory.w = 70;
    textRectHistory.h = 15;

    SDL_RenderCopy(renderer, textTextureHistory, NULL, &textRectHistory);
    SDL_DestroyTexture(textTextureHistory);
    SDL_FreeSurface(textSurfaceHistory);

    // Render teks Judul history 1
    SDL_Surface* textSurfaceHistoryMus = TTF_RenderText_Solid(font, "Bitterlove", black);
    SDL_Texture* textTextureHistoryMus = SDL_CreateTextureFromSurface(renderer, textSurfaceHistoryMus);

    SDL_Rect textRectHistoryMus;
    textRectHistoryMus.x = 470;
    textRectHistoryMus.y = 120;
    textRectHistoryMus.w = 50;
    textRectHistoryMus.h = 10;

    SDL_RenderCopy(renderer, textTextureHistoryMus, NULL, &textRectHistoryMus);
    SDL_DestroyTexture(textTextureHistoryMus);
    SDL_FreeSurface(textSurfaceHistoryMus);

    // Render teks artis
    SDL_Surface* textSurfaceArtist = TTF_RenderText_Solid(font, "Ardhito Pramono", black);
    SDL_Texture* textTextureArtist = SDL_CreateTextureFromSurface(renderer, textSurfaceArtist);

    SDL_Rect textRectArtist;
    textRectArtist.x = 440;
    textRectArtist.y = 130;
    textRectArtist.w = 80;
    textRectArtist.h = 10;

    SDL_RenderCopy(renderer, textTextureArtist, NULL, &textRectArtist);
    SDL_DestroyTexture(textTextureArtist);
    SDL_FreeSurface(textSurfaceArtist);

    // Render teks Judul history 2
    SDL_Surface* textSurfaceHistoryMus_2 = TTF_RenderText_Solid(font, "It Will Rain", black);
    SDL_Texture* textTextureHistoryMus_2 = SDL_CreateTextureFromSurface(renderer, textSurfaceHistoryMus_2);

    SDL_Rect textRectHistoryMus_2;
    textRectHistoryMus_2.x = 470;
    textRectHistoryMus_2.y = 180;
    textRectHistoryMus_2.w = 50;
    textRectHistoryMus_2.h = 10;

    SDL_RenderCopy(renderer, textTextureHistoryMus_2, NULL, &textRectHistoryMus_2);
    SDL_DestroyTexture(textTextureHistoryMus_2);
    SDL_FreeSurface(textSurfaceHistoryMus_2);

    // Render teks artis 2
    SDL_Surface* textSurfaceArtist_2 = TTF_RenderText_Solid(font, "Bruno Mars", black);
    SDL_Texture* textTextureArtist_2 = SDL_CreateTextureFromSurface(renderer, textSurfaceArtist_2);

    SDL_Rect textRectArtist_2;
    textRectArtist_2.x = 450;
    textRectArtist_2.y = 190;
    textRectArtist_2.w = 70;
    textRectArtist_2.h = 10;

    SDL_RenderCopy(renderer, textTextureArtist_2, NULL, &textRectArtist_2);
    SDL_DestroyTexture(textTextureArtist_2);
    SDL_FreeSurface(textSurfaceArtist_2);

    // Render teks Judul history 3
    SDL_Surface* textSurfaceHistoryMus_3 = TTF_RenderText_Solid(font, "Let Her Go", black);
    SDL_Texture* textTextureHistoryMus_3 = SDL_CreateTextureFromSurface(renderer, textSurfaceHistoryMus_3);

    SDL_Rect textRectHistoryMus_3;
    textRectHistoryMus_3.x = 470;
    textRectHistoryMus_3.y = 240;
    textRectHistoryMus_3.w = 50;
    textRectHistoryMus_3.h = 10;

    SDL_RenderCopy(renderer, textTextureHistoryMus_3, NULL, &textRectHistoryMus_3);
    SDL_DestroyTexture(textTextureHistoryMus_3);
    SDL_FreeSurface(textSurfaceHistoryMus_3);

    // Render teks artis 3
    SDL_Surface* textSurfaceArtist_3 = TTF_RenderText_Solid(font, "Passenger", black);
    SDL_Texture* textTextureArtist_3 = SDL_CreateTextureFromSurface(renderer, textSurfaceArtist_3);

    SDL_Rect textRectArtist_3;
    textRectArtist_3.x = 460;
    textRectArtist_3.y = 250;
    textRectArtist_3.w = 60;
    textRectArtist_3.h = 10;

    SDL_RenderCopy(renderer, textTextureArtist_3, NULL, &textRectArtist_3);
    SDL_DestroyTexture(textTextureArtist_3);
    SDL_FreeSurface(textSurfaceArtist_3);

    // Render teks playlist
    SDL_Surface* textSurfacePlaylist = TTF_RenderText_Solid(font, "Your Library", black);
    SDL_Texture* textTexturePlaylist = SDL_CreateTextureFromSurface(renderer, textSurfacePlaylist);

    SDL_Rect textRectPlaylist;
    textRectPlaylist.x = 15;
    textRectPlaylist.y = 80;
    textRectPlaylist.w = 100;
    textRectPlaylist.h = 20;

    SDL_RenderCopy(renderer, textTexturePlaylist, NULL, &textRectPlaylist);
    SDL_DestroyTexture(textTexturePlaylist);
    SDL_FreeSurface(textSurfacePlaylist);

    // Render teks Judul playlist 1
    SDL_Surface* textSurfacePlay = TTF_RenderText_Solid(font, "Terardhito-ardhito", black);
    SDL_Texture* textTexturePlay = SDL_CreateTextureFromSurface(renderer, textSurfacePlay);

    SDL_Rect textRectPlay;
    textRectPlay.x = 80;
    textRectPlay.y = 120;
    textRectPlay.w = 100;
    textRectPlay.h = 10;

    SDL_RenderCopy(renderer, textTexturePlay, NULL, &textRectPlay);
    SDL_DestroyTexture(textTexturePlay);
    SDL_FreeSurface(textSurfacePlay);

    // Render teks album
    SDL_Surface* textSurfaceAlbum = TTF_RenderText_Solid(font, "Playlist", black);
    SDL_Texture* textTextureAlbum = SDL_CreateTextureFromSurface(renderer, textSurfaceAlbum);

    SDL_Rect textRectAlbum;
    textRectAlbum.x = 80;
    textRectAlbum.y = 130;
    textRectAlbum.w = 50;
    textRectAlbum.h = 10;

    SDL_RenderCopy(renderer, textTextureAlbum, NULL, &textRectAlbum);
    SDL_DestroyTexture(textTextureAlbum);
    SDL_FreeSurface(textSurfaceAlbum);

    // Render teks Judul playlist 2
    SDL_Surface* textSurfacePlay_2 = TTF_RenderText_Solid(font, "Lofi Chill", black);
    SDL_Texture* textTexturePlay_2 = SDL_CreateTextureFromSurface(renderer, textSurfacePlay_2);

    SDL_Rect textRectPlay_2;
    textRectPlay_2.x = 80;
    textRectPlay_2.y = 180;
    textRectPlay_2.w = 70;
    textRectPlay_2.h = 10;

    SDL_RenderCopy(renderer, textTexturePlay_2, NULL, &textRectPlay_2);
    SDL_DestroyTexture(textTexturePlay_2);
    SDL_FreeSurface(textSurfacePlay_2);

    // Render teks album 2
    SDL_Surface* textSurfaceAlbum_2 = TTF_RenderText_Solid(font, "Playlist", black);
    SDL_Texture* textTextureAlbum_2 = SDL_CreateTextureFromSurface(renderer, textSurfaceAlbum_2);

    SDL_Rect textRectAlbum_2;
    textRectAlbum_2.x = 80;
    textRectAlbum_2.y = 190;
    textRectAlbum_2.w = 50;
    textRectAlbum_2.h = 10;

    SDL_RenderCopy(renderer, textTextureAlbum_2, NULL, &textRectAlbum_2);
    SDL_DestroyTexture(textTextureAlbum_2);
    SDL_FreeSurface(textSurfaceAlbum_2);

    // Render teks Judul playlist 3
    SDL_Surface* textSurfacePlay_3 = TTF_RenderText_Solid(font, "Heartbroken", black);
    SDL_Texture* textTexturePlay_3 = SDL_CreateTextureFromSurface(renderer, textSurfacePlay_3);

    SDL_Rect textRectPlay_3;
    textRectPlay_3.x = 80;
    textRectPlay_3.y = 240;
    textRectPlay_3.w = 80;
    textRectPlay_3.h = 10;

    SDL_RenderCopy(renderer, textTexturePlay_3, NULL, &textRectPlay_3);
    SDL_DestroyTexture(textTexturePlay_3);
    SDL_FreeSurface(textSurfacePlay_3);

    // Render teks album 3
    SDL_Surface* textSurfaceAlbum_3 = TTF_RenderText_Solid(font, "Playlist", black);
    SDL_Texture* textTextureAlbum_3 = SDL_CreateTextureFromSurface(renderer, textSurfaceAlbum_3);

    SDL_Rect textRectAlbum_3;
    textRectAlbum_3.x = 80;
    textRectAlbum_3.y = 250;
    textRectAlbum_3.w = 50;
    textRectAlbum_3.h = 10;

    SDL_RenderCopy(renderer, textTextureAlbum_3, NULL, &textRectAlbum_3);
    SDL_DestroyTexture(textTextureAlbum_3);
    SDL_FreeSurface(textSurfaceAlbum_3);

    // Render Pembatas 2
    SDL_Surface* textSurfaceGap_2 = TTF_RenderText_Solid(font, "-", black);
    SDL_Texture* textTextureGap_2 = SDL_CreateTextureFromSurface(renderer, textSurfaceGap_2);

    SDL_Rect textRectGap_2;
    textRectGap_2.x = -100;
    textRectGap_2.y = 285;
    textRectGap_2.w = 800;
    textRectGap_2.h = textSurfaceGap_2->h;

    SDL_RenderCopy(renderer, textTextureGap_2, NULL, &textRectGap_2);
    SDL_DestroyTexture(textTextureGap_2);
    SDL_FreeSurface(textSurfaceGap_2);

    // Render Semua
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
}

	// Cleanup
	SDL_DestroyTexture(buttonTexture);
    TTF_CloseFont(font);
    SDL_CloseAudio();
    SDL_FreeWAV(wav_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

}

int main(int argc, char* argv[]) {

	Lagu *daftar_lagu = NULL;
    Playlist *playlist = NULL;
    History *history = NULL;

	while (1) {
		system("cls");
        int pilihan;
		banner();
		printf("\n\t\t\tMain Menu\n\n");
		printf("\t\t1. Masukkan Lagu\n");
		printf("\t\t2. Lihat Lagu\n");
		printf("\t\t3. Mainkan Lagu\n");
		printf("\t\t4. Buat Playlist\n");
		printf("\t\t5. Lihat Playlist\n");
		printf("\t\t6. Lihat History\n");
		printf("\t\t7. Tampilan GUI SPOTIPI\n\n");
		printf("\t\t0. Keluar Program\n\n");
		printf("\t\t==> ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                masukkan_lagu(&daftar_lagu);
                break;
            case 2:
            	if (daftar_lagu == NULL) {
                    printf("\n\t\tDaftar lagu kosong\n");
                    getchar();
    				printf("\n\t\tPress Enter to continue...");
    				getchar();
                } else {
                	tampilkan_daftar_lagu(daftar_lagu);
                	getchar();
    				printf("\n\t\tPress Enter to continue...");
    				getchar();
                }
                break;
            case 3:
                if (daftar_lagu == NULL) {
                    printf("\n\t\tDaftar lagu kosong\n");
                    getchar();
    				printf("\n\t\tPress Enter to continue...");
    				getchar();
                } else {
                	tampilkan_daftar_lagu(daftar_lagu);
                    putar_lagu(daftar_lagu, &history);
                }
                break;
            case 4:
            	tampilkan_daftar_lagu(daftar_lagu);
                buat_playlist(&daftar_lagu, &playlist);
                break;
            case 5:
                if (playlist == NULL) {
                    printf("\n\t\tBelum ada playlist yang dibuat\n");
                    getchar();
    				printf("\n\t\tPress Enter to continue...");
    				getchar();
                } else {
                    lihat_playlist(playlist);
                }
                    break;
            case 6:
                lihat_history(history);
                break;
            case 7:
            	play_GUI();
            	break;
            case 0:
            	return 0;
            default:
            	getchar();
                printf("\t\tPilihan tidak valid\n");
                getchar();
                Sleep(5);
        }
    }

    return 0;
}

void my_audio_callback(void *userdata, Uint8 *stream, int len) {
    if (audio_len == 0 || !is_playing) {
       	return;
    }

    len = (len > audio_len ? audio_len : len);

    SDL_memcpy(stream, audio_pos, len);
    audio_pos += len;
    audio_len -= len;
    elapsedTime += (double)len / wav_spec.freq;

}
