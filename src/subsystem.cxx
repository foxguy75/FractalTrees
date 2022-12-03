#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <fmt/core.h>

#include <subsystem.hxx>

Subsystem::Subsystem() : m_successfullyInit{ true }
{
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    m_successfullyInit = false;
    fmt::print( "SDL could not initialize! SDL_Error: {}\n", SDL_GetError() );
  }
  else
  {
    if( TTF_Init() < 0 )
    {
      m_successfullyInit = false;
      fmt::print( "TTF could not initialize! SDL_Error: {}\n", TTF_GetError() );
    }
  }
}

Subsystem::~Subsystem()
{
  TTF_Quit();
  SDL_Quit();
}