#include <iostream>
#include <string_view>
#include <vector>

#include <application/application.hxx>
#include <game_components/card.hxx>

#include <fmt/format.h>

int main( const int argc, char const* const* const argv )
{
    constexpr std::string_view asset_location{};
    std::vector<std::string_view> args{ argv, std::next( argv, static_cast<std::ptrdiff_t>( argc ) ) };

    application::Game game{ "Euchre Clone", 1920, 1080 };

    game.add_sprite_atlas( "card_atlas", "E:\\Repos\\sdlTree\\assets\\cards\\Playing_Cards.png",
                           "E:\\Repos\\sdlTree\\assets\\meta_data\\card_meta_data.json" );

    game.add_sprite_atlas( "card_back_atlas", "E:\\Repos\\sdlTree\\assets\\cards\\Card_Backs_Enhancers_and_Seals.png",
                           "E:\\Repos\\sdlTree\\assets\\meta_data\\card_back_meta_data.json" );

    // game.load_game_components();

    game.run();

    return 0;
}