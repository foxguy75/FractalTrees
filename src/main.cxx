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

    // for( int suit = 0; suit < 4; ++suit )
    // {
    //       for( int rank = 9; rank < 15; ++rank )
    //       {
    //           app.deck.push_back( { rank, static_cast<playing_cards::Suit_Value>( suit ) } );
    //       }
    // }

    game.deck.push_back( { 2, playing_cards::Suit_Value::Hearts, game.get_atlas( "card_atlas" ), { 20, 20 } } );
    game.deck.push_back( { 7, playing_cards::Suit_Value::Clubs, game.get_atlas( "card_atlas" ), { 160, 20 } } );
    game.deck.push_back( { 13, playing_cards::Suit_Value::Diamonds, game.get_atlas( "card_atlas" ), { 300, 20 } } );
    game.deck.push_back( { 9, playing_cards::Suit_Value::Spades, game.get_atlas( "card_atlas" ), { 440, 20 } } );

    game.run();

    return 0;
}