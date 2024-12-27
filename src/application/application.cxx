#include <string>

#include <fmt/core.h>

#include <application.hxx>
#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <thread>

#include <SDL_events.h>
#include <SDL_mouse.h>

#include <game_components/card.hxx>

namespace
{
    bool points_eq( const SDL_Point& left, const SDL_Point& right ) { return left.x == right.x && left.y == right.y; }
}  // namespace

namespace application
{

    Game::Game() { display_version_info(); }

    Game::Game( std::string theName ) : m_application_name{ theName } { display_version_info(); }

    Game::Game( int theScreenWidth, int theScreenHight )
        : m_screenWidth{ theScreenWidth }, m_screenHight{ theScreenHight }
    {
        display_version_info();
    }

    Game::Game( std::string theName, int theScreenWidth, int theScreenHight )
        : m_application_name{ theName }, m_screenWidth{ theScreenWidth }, m_screenHight{ theScreenHight }
    {
        display_version_info();
    }

    void Game::add_sprite_atlas( const std::string& the_atlas_name, const std::filesystem::path& the_sprite_atlas,
                                 const std::filesystem::path& the_sprite_meta_data )
    {
        m_atlas.emplace( std::make_pair(
            the_atlas_name,
            std::make_unique<sprite::Atlas>( this->m_renderer.get(), the_sprite_atlas, the_sprite_meta_data ) ) );
    }

    void Game::display_version_info()
    {
        std::string version{ fmt::format( "{} {}", m_application_name, m_version.get_string() ) };

        SDL_Color white{ 255, 255, 255, 255 };

        std::unique_ptr<SDL_Surface, decltype( &SDL_FreeSurface )> textSurface{
            TTF_RenderText_Solid( m_font.get(), version.c_str(), white ), SDL_FreeSurface };

        std::unique_ptr<SDL_Texture, decltype( &SDL_DestroyTexture )> textTexture{
            SDL_CreateTextureFromSurface( m_renderer.get(), textSurface.get() ), SDL_DestroyTexture };

        int padding{ 2 };

        SDL_Rect dest{ m_screenWidth - textSurface->w - padding, m_screenHight - textSurface->h - padding,
                       textSurface->w, textSurface->h };

        SDL_RenderCopy( m_renderer.get(), textTexture.get(), nullptr, &dest );
    }

    void Game::run()
    {
        int quit{ 0 };
        bool mouse_held{ false };
        bool left_mouse_button_held{ false };
        bool right_mouse_button_held{ false };
        SDL_Event event;
        while( !quit )
        {
            SDL_RenderClear( m_renderer.get() );

            SDL_PollEvent( &event );

            // Process Event
            switch( event.type )
            {
                case SDL_QUIT:
                {
                    quit = 1;
                    break;
                }
            }

            for( auto& card : m_deck )
            {
                card->handle_event( event );
                card->draw( m_renderer.get() );
            }

            m_deck.handle_event( event );
            m_deck.draw();

            display_version_info();

            SDL_RenderPresent( m_renderer.get() );
        }
    }

    void Game::load_game_components()
    {
        m_deck.add( std::shared_ptr<playing_cards::Card>(
            new playing_cards::Card{ 2, playing_cards::Suit_Value::Hearts, get_atlas( "card_atlas" ), { 20, 20 } } ) );
        m_deck.add( std::shared_ptr<playing_cards::Card>(
            new playing_cards::Card{ 7, playing_cards::Suit_Value::Clubs, get_atlas( "card_atlas" ), { 160, 20 } } ) );
        m_deck.add( std::shared_ptr<playing_cards::Card>( new playing_cards::Card{
            13, playing_cards::Suit_Value::Diamonds, get_atlas( "card_atlas" ), { 300, 20 } } ) );
        m_deck.add( std::shared_ptr<playing_cards::Card>(
            new playing_cards::Card{ 9, playing_cards::Suit_Value::Spades, get_atlas( "card_atlas" ), { 440, 20 } } ) );
    }

    std::string Version::get_string() const { return fmt::format( "Version: {}.{}.{}", m_major, m_minor, m_patch ); }
}  // namespace application