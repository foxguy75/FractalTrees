#include <iostream>
#include <string>
#include <memory>

#include <config/SDLTree.h>
#include <fmt/core.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


int main(int argc, char** argv) 
{
    constexpr int screenWidth = 64 * 16;
    constexpr int screenHight = 32 * 16;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        if( TTF_Init() < 0 )
        {
            printf( "TTF could not initialize! SDL_Error: %s\n", TTF_GetError() );
        }
        else
        {
            std::string version{ fmt::format("SDL Tree Version: {}.{}.{}", SDLTree_VERSION_MAJOR, SDLTree_VERSION_MINOR, SDLTree_VERSION_PATCH ) };
        
            std::unique_ptr<SDL_Window, decltype( &SDL_DestroyWindow )> window{ SDL_CreateWindow( "Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHight, SDL_WINDOW_SHOWN ), SDL_DestroyWindow };

            std::unique_ptr<SDL_Renderer, decltype( &SDL_DestroyRenderer )> renderer{ SDL_CreateRenderer( window.get(), -1, SDL_RENDERER_ACCELERATED ), SDL_DestroyRenderer };
        
            std::unique_ptr<TTF_Font, decltype( &TTF_CloseFont )> font{ TTF_OpenFont( "", 24 ), TTF_CloseFont };

            SDL_Color black{255,255,255,255};

            std::unique_ptr<SDL_Surface, decltype( &SDL_FreeSurface )> textSurface{ TTF_RenderText_Solid( font.get(), version.c_str(), black ), SDL_FreeSurface };

            std::unique_ptr<SDL_Texture, decltype( &SDL_DestroyTexture )> textTexture{ SDL_CreateTextureFromSurface(renderer.get(), textSurface.get()), SDL_DestroyTexture };

            SDL_Rect dest{0,0, textSurface->w, textSurface->h };

            int quit{0};

            SDL_Event event;

            while( !quit )
            {
                while( SDL_PollEvent( &event ) == 1 )
                {
                    if( event.type == SDL_QUIT )
                    {
                        quit = 1;
                    }
                }
                SDL_RenderCopy( renderer.get(), textTexture.get(), nullptr, &dest );
                SDL_RenderPresent( renderer.get() );
            }


        }
        TTF_Quit();
        
        SDL_Quit();
    }


    return 0;
} 