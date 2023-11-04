#include <SDL.h>
#include <SDL_syswm.h>
#include <windows.h>
#include <cstdlib>
#include <cstring>

int main(int argc, char* argv[]) {
  HWND parent = 0;
  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "--parent") == 0) {
      if (i + 1 < argc) {
        char* end_p = nullptr;
        parent = reinterpret_cast<HWND>(std::atoi(argv[++i]));
        break;
      }
    }
  }

  SDL_Init(SDL_INIT_VIDEO);

  auto window =
      SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       640, 480, SDL_WINDOW_RESIZABLE);
  auto renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (parent) {
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);
    SDL_GetWindowWMInfo(window, &info);
    HWND child = info.info.win.window;

    auto style = GetWindowLong(child, GWL_STYLE);
    style &= ~(WS_POPUP | WS_BORDER);
    style |= WS_CHILD;
    SetWindowLong(child, GWL_STYLE, style);

    auto r = SetParent(child, parent);
    if (!r) {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR",
                               "SetParent() failed", window);
    }

    RECT rc;
    GetClientRect(parent, &rc);
    SetWindowPos(child, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
                 SWP_NOZORDER);
  }

  int x = 0, y = 0;
  int vx = 1, vy = 1;

  bool loop = true;
  while (loop) {
    {
      SDL_Event e;
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
          loop = false;
        }
        if (e.type == SDL_WINDOWEVENT &&
            e.window.event == SDL_WINDOWEVENT_CLOSE &&
            e.window.windowID == SDL_GetWindowID(window)) {
          loop = false;
        }
      }
    }

    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);

    x += vx;
    y += vy;
    if ((vx < 0 && x < 0) || (vx > 0 && x > w)) {
      vx = -vx;
    }
    if ((vy < 0 && y < 0) || (vy > 0 && y > h)) {
      vy = -vy;
    }

    SDL_SetRenderDrawColor(renderer, 0x22, 0x22, 0x22, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xee, 0xee, 0xee, 255);
    const int RADIUS = 20;
    SDL_Rect rect = {
        x - RADIUS / 2,
        y - RADIUS / 2,
        RADIUS,
        RADIUS,
    };
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
