#include <config/SDLTree.h>
#include <fmt/core.h>

#include <application.hxx>
#include <string>

Application::Application()
    : m_subsystem{},
      m_screenWidth{ 64 * 16 },
      m_screenHight{ 32 * 16 },
      m_window{ SDL_CreateWindow( "Test Window", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, m_screenWidth,
                                  m_screenHight, SDL_WINDOW_SHOWN ),
                SDL_DestroyWindow },
      m_renderer{
          SDL_CreateRenderer( m_window.get(), -1, SDL_RENDERER_ACCELERATED ),
          SDL_DestroyRenderer },
      m_font{ TTF_OpenFont( "D:\\Repos\\sdlTree\\assets\\FiraCode-Regular.ttf",
                            16 ),
              TTF_CloseFont }
{
  displayVersionInfo();
}

Application::~Application() {}

void Application::displayVersionInfo()
{
  std::string version{ fmt::format(
      "SDL Tree Debug Build Version: {}.{}.{} ", SDLTree_VERSION_MAJOR,
      SDLTree_VERSION_MINOR, SDLTree_VERSION_PATCH ) };

  SDL_Color black{ 255, 255, 255, 255 };

  std::unique_ptr<SDL_Surface, decltype( &SDL_FreeSurface )> textSurface{
      TTF_RenderText_Solid( m_font.get(), version.c_str(), black ),
      SDL_FreeSurface };

  std::unique_ptr<SDL_Texture, decltype( &SDL_DestroyTexture )> textTexture{
      SDL_CreateTextureFromSurface( m_renderer.get(), textSurface.get() ),
      SDL_DestroyTexture };

  int padding{ 2 };

  SDL_Rect dest{ m_screenWidth - textSurface->w - padding,
                 m_screenHight - textSurface->h - padding, textSurface->w,
                 textSurface->h };

  SDL_RenderCopy( m_renderer.get(), textTexture.get(), nullptr, &dest );
}

void Application::run()
{
  int quit{ 0 };
  SDL_Event event;
  while( !quit )
  {
    SDL_PollEvent( &event );

    if( event.type == SDL_QUIT )
    {
      quit = 1;
    }
  }
}