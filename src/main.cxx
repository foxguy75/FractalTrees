#include <SDL2/SDL.h>
#include <math.h>

#include <application.hxx>
#include <filesystem>
#include <iostream>
#include <memory>
#include <ranges>
#include <string>
#include <subsystem.hxx>
#include <vector>

[[nodiscard]] std::pair<int, int> generatePoints( std::pair<int, int> theOrigin,
                                                  float theAngle,
                                                  int theLength )
{
  auto [ x, y ] = theOrigin;

  int yDelta = std::round( theLength * std::sin( theAngle ) );
  int xDelta = std::round( theLength * std::cos( theAngle ) );

  return std::make_pair<int, int>( x + xDelta, y - yDelta );
}

void thing( SDL_Renderer* theRenderer, std::pair<int, int> point,
            float initAngle, float deltaAngle, int length )
{
  static constexpr float shrink = 0.67;
  if( length < 5 )
  {
    return;
  }
  else
  {
    std::pair<int, int> newPoint = generatePoints( point, initAngle, length );

    SDL_RenderDrawLine( theRenderer, point.first, point.second, newPoint.first,
                        newPoint.second );
    SDL_RenderPresent( theRenderer );

    length *= shrink;
    initAngle += deltaAngle;
    thing( theRenderer, newPoint, initAngle, deltaAngle, length );
    return;
  }
}
int main( int argc, char** argv )
{
  constexpr int screenWidth = 64 * 16;
  constexpr int screenHight = 32 * 16;

  Application app{};

  SDL_SetRenderDrawColor( app.getRenderer(), 255, 255, 255, 0 );

  float initAngle{ M_PI * .5 };
  float deltaAngle{ 0.698132 };
  // float deltaAngle{ M_PI * .5 };

  int length = screenHight - ( screenHight - screenHight / 4 );

  std::pair<int, int> pointsToDraw{ screenWidth / 2, screenHight };
  thing( app.getRenderer(), pointsToDraw, initAngle, deltaAngle, length );

  app.run();

  return 0;
}