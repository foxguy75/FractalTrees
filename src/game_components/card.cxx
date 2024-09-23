#include <card.hxx>
#include <iostream>
#include <string>

#include <fmt/format.h>

#include <SDL2/SDL_mouse.h>

namespace
{
    bool points_eq( const SDL_Point& left, const SDL_Point& right ) { return left.x == right.x && left.y == right.y; }

    void expand_rect( SDL_Rect& the_rect, int expand_value )
    {
        the_rect.x -= expand_value / 2;
        the_rect.y -= expand_value / 2;
        the_rect.w += expand_value;
        the_rect.h += expand_value;
    }

}  // namespace

namespace playing_cards
{
    Card::Card( int rank, Suit_Value value, const application::sprite::Atlas* the_atlas, SDL_Point init_position )
        : m_rank{ rank }, m_suite{ value }, m_atlas{ the_atlas }, m_position{ init_position }
    {
        m_suite = static_cast<playing_cards::Suit_Value>( ( static_cast<int>( m_suite ) + 1 ) % 4 );
        auto result = std::ranges::find_if( m_atlas->m_sprites, [ this ]( const application::sprite::Sprite& sprite )
                                            { return this->get_name() == sprite.m_display_name; } );

        if( result != m_atlas->m_sprites.end() )
        {
            m_current_sprite = &*result;
        }
        else if( m_atlas->m_sprites.size() > 0 )
        {
            m_current_sprite = &m_atlas->m_sprites.at( 0 );
        }
    }

    auto Card::operator<=>( const Card& that ) const { return m_rank <=> that.m_rank; }

    std::string Card::get_name() const
    {
        std::string display_string{};

        // Determine Royal Rank
        switch( m_rank )
        {
            case 2:
                display_string += "Two";
                break;
            case 3:
                display_string += "Three";
                break;
            case 4:
                display_string += "Four";
                break;
            case 5:
                display_string += "Five";
                break;
            case 6:
                display_string += "Six";
                break;
            case 7:
                display_string += "Seven";
                break;
            case 8:
                display_string += "Eight";
                break;
            case 9:
                display_string += "Nine";
                break;
            case 10:
                display_string += "Ten";
                break;
            case 11:
                display_string += "Jack";
                break;
            case 12:
                display_string += "Queen";
                break;
            case 13:
                display_string += "King";
                break;
            case 14:
                display_string += "Ace";
                break;

            default:
                display_string += fmt::format( "{}", m_rank );
                break;
        }

        display_string += " of ";

        switch( m_suite )
        {
            case Suit_Value::Diamonds:
                display_string += "Diamonds";
                break;
            case Suit_Value::Clubs:
                display_string += "Clubs";
                break;
            case Suit_Value::Hearts:
                display_string += "Hearts";
                break;
            case Suit_Value::Spades:
                display_string += "Spades";
                break;
            default:
                break;
        }

        return display_string;
    }

    void Card::handle_event( const SDL_Event& the_event )
    {
        switch( the_event.type )
        {
            case SDL_MOUSEMOTION:
            {
                handle_mouse_moment_event();
                break;
            }

            case SDL_MOUSEBUTTONDOWN:
            {
                check_if_selected();

                if( the_event.button.button == SDL_BUTTON_RIGHT && m_is_selected )
                {
                    advance_sprite();
                    m_is_right_selected = true;
                }

                if( the_event.button.button == SDL_BUTTON_LEFT && m_is_selected )
                {
                    m_is_left_selected = true;
                    m_render_priority = 1;
                }

                break;
            }

            case SDL_MOUSEBUTTONUP:
            {
                if( m_is_selected && the_event.button.button == SDL_BUTTON_LEFT && m_is_left_selected )
                {
                    m_is_left_selected = false;
                    m_previous_mouse_pos.x = 0;
                    m_previous_mouse_pos.y = 0;
                    m_render_priority = 0;
                }

                if( m_is_selected && the_event.button.button == SDL_BUTTON_RIGHT && m_is_right_selected )
                {
                    m_is_right_selected = false;
                }

                m_is_selected = m_is_left_selected || m_is_right_selected;

                break;
            }
        }
    }

    void Card::draw( SDL_Renderer* the_renderer )
    {
        if( m_display )
        {
            // Atlas check here to get the sprite info.
            auto& [ current_x, current_y ] = m_position;
            SDL_Rect dest{ current_x, current_y, ( m_current_sprite->m_rect.w * 2 ),
                           ( m_current_sprite->m_rect.h * 2 ) };

            expand_rect( dest, -3 );

            SDL_RenderDrawRect( the_renderer, &dest );

            SDL_SetRenderDrawColor( the_renderer, 255, 255, 255, 255 );

            expand_rect( dest, -3 );

            SDL_RenderFillRect( the_renderer, &dest );

            SDL_RenderCopy( the_renderer, m_atlas->m_atlas_texture.get(), &m_current_sprite->m_rect, &dest );

            SDL_SetRenderDrawColor( the_renderer, 0, 0, 0, 0 );
        }
    }

    void Card::check_if_selected()
    {
        int mouse_x = 0;
        int mouse_y = 0;
        SDL_GetMouseState( &mouse_x, &mouse_y );

        SDL_Point point{ mouse_x, mouse_y };

        SDL_Rect test_rect{ m_position.x, m_position.y, ( m_current_sprite->m_rect.w * 2 ),
                            ( m_current_sprite->m_rect.h * 2 ) };

        m_is_selected = SDL_PointInRect( &point, &test_rect );
    }

    void Card::advance_sprite()
    {
        // the docs of SDL_GetKeyboardState says we do not free the array we are getting
        const Uint8* keyboard_state = SDL_GetKeyboardState( nullptr );

        if( keyboard_state[ SDL_SCANCODE_RSHIFT ] || keyboard_state[ SDL_SCANCODE_LSHIFT ] )
        {
            m_suite = static_cast<playing_cards::Suit_Value>( ( static_cast<int>( m_suite ) + 1 ) % 4 );
            auto result =
                std::ranges::find_if( m_atlas->m_sprites, [ this ]( const application::sprite::Sprite& sprite )
                                      { return this->get_name() == sprite.m_display_name; } );

            if( result != m_atlas->m_sprites.end() )
            {
                m_current_sprite = &*result;
            }
        }
        else
        {
            m_rank++;

            if( m_rank % 15 == 0 )
            {
                m_rank = 2;
            }

            auto result =
                std::ranges::find_if( m_atlas->m_sprites, [ this ]( const application::sprite::Sprite& sprite )
                                      { return this->get_name() == sprite.m_display_name; } );

            if( result != m_atlas->m_sprites.end() )
            {
                m_current_sprite = &*result;
            }
        }
    }

    void Card::handle_mouse_moment_event()
    {
        if( m_is_left_selected )
        {
            int mouse_x = 0;
            int mouse_y = 0;
            SDL_GetMouseState( &mouse_x, &mouse_y );

            SDL_Point point{ mouse_x, mouse_y };

            if( !points_eq( m_previous_mouse_pos, point ) && !points_eq( m_previous_mouse_pos, { 0, 0 } ) )
            {
                m_position.x += ( mouse_x - m_previous_mouse_pos.x );
                m_position.y += ( mouse_y - m_previous_mouse_pos.y );
            }

            m_previous_mouse_pos.x = mouse_x;
            m_previous_mouse_pos.y = mouse_y;
        }
    }

}  // namespace playing_cards