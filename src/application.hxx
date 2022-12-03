#ifndef APPLICATION_HXX
#define APPLICATION_HXX

#include <SDL.h>
#include <SDL_ttf.h>

#include <memory>
#include <subsystem.hxx>

class Application
{
 public:
  Application();
  ~Application();

  void run();

  SDL_Renderer* const getRenderer() const { return m_renderer.get(); };

 private:
  void displayVersionInfo();

  Subsystem m_subsystem;

  int m_screenWidth;
  int m_screenHight;

  std::unique_ptr<SDL_Window, decltype( &SDL_DestroyWindow )> m_window;
  std::unique_ptr<SDL_Renderer, decltype( &SDL_DestroyRenderer )> m_renderer;
  std::unique_ptr<TTF_Font, decltype( &TTF_CloseFont )> m_font;
};

#endif
