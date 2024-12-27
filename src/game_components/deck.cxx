#include <card.hxx>
#include <deck.hxx>
#include <fmt/format.h>
#include <random>

namespace
{
    SDL_Point calculate_screen_center( int screen_x, int screen_y ) { return { screen_x / 2, screen_y / 2 }; }

    void expand_rect( SDL_Rect& the_rect, int expand_value )
    {
        the_rect.x -= expand_value / 2;
        the_rect.y -= expand_value / 2;
        the_rect.w += expand_value;
        the_rect.h += expand_value;
    }
}  // namespace

Deck::Deck( int the_screen_x, int the_screen_y, SDL_Renderer* the_renderer ) : m_renderer{ the_renderer }
{
    SDL_Point center = calculate_screen_center( the_screen_x, the_screen_y );
    m_atlas = application::sprite::Atlas( the_renderer,
                                          "E:\\Repos\\sdlTree\\assets\\cards\\Card_Backs_Enhancers_and_Seals.png",
                                          "E:\\Repos\\sdlTree\\assets\\meta_data\\card_back_meta_data.json" );
    m_current_sprite = m_atlas.m_sprites.front();
    m_position = { center.x - this->m_current_sprite.m_rect.w, center.y - this->m_current_sprite.m_rect.h };
}

std::shared_ptr<playing_cards::Card> Deck::draw_card()
{
    std::shared_ptr<playing_cards::Card> temp = m_deck.back();
    m_deck.pop_back();
    return temp;
}

void Deck::draw()
{
    auto& [ current_x, current_y ] = m_position;
    SDL_Rect dest{ current_x, current_y, ( m_current_sprite.m_rect.w * 2 ), ( m_current_sprite.m_rect.h * 2 ) };

    expand_rect( dest, -3 );

    SDL_RenderDrawRect( this->m_renderer, &dest );

    SDL_SetRenderDrawColor( this->m_renderer, 255, 255, 255, 255 );

    expand_rect( dest, -3 );

    SDL_RenderFillRect( m_renderer, &dest );

    SDL_RenderCopy( m_renderer, m_atlas.m_atlas_texture.get(), &m_current_sprite.m_rect, &dest );

    SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 0 );
}

void Deck::shuffle()
{
    std::random_device rd{};

    std::mt19937 g( rd() );

    std::shuffle( m_deck.begin(), m_deck.end(), g );
}

void Deck::add( std::shared_ptr<playing_cards::Card> the_card ) { m_deck.push_back( the_card ); }

void Deck::handle_event( const SDL_Event& the_event )
{
    if( the_event.type == SDL_MOUSEBUTTONDOWN )
    {
        auto& [ current_x, current_y ] = m_position;
        SDL_Rect dest{ current_x, current_y, ( m_current_sprite.m_rect.w * 2 ), ( m_current_sprite.m_rect.h * 2 ) };

        expand_rect( dest, -3 );

        if( the_event.button.button == SDL_BUTTON_LEFT )
        {
            if( the_event.button.x >= dest.x && the_event.button.x <= dest.x + dest.w && the_event.button.y >= dest.y &&
                the_event.button.y <= dest.y + dest.h )
            {
                fmt::print( "Deck Clicked\n" );
            }
        }
    }
}
