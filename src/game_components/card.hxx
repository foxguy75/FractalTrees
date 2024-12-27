#ifndef CARDS_HXX
#define CARDS_HXX

#include <memory>
#include <string>

#include <SDL2/SDL_render.h>

#include <sprite_atlas.hxx>

#include <SDL_events.h>
#include <SDL_mouse.h>

namespace playing_cards
{
    enum struct Suit_Value
    {
        Hearts,
        Clubs,
        Diamonds,
        Spades
    };

    struct Card
    {
        Card( int rank, Suit_Value value, const application::sprite::Atlas* the_atlas, SDL_Point init_position );
        Card() = default;
        auto operator<=>( const Card& that ) const;
        bool operator==( const Card& that ) const = default;

        std::string get_name() const;

        operator std::string() const { return get_name(); };

        void handle_event( const SDL_Event& the_event );

        void draw( SDL_Renderer* the_renderer );

        bool m_display{ true };
        int m_rank{};
        int m_render_priority{ 0 };
        Suit_Value m_suite{};
        SDL_Point m_position{ 0, 0 };

       private:
        const application::sprite::Atlas* m_atlas{};
        const application::sprite::Sprite* m_current_sprite{};

        SDL_Point m_previous_mouse_pos{ 0, 0 };

        bool m_is_selected{ false };
        bool m_is_left_selected{ false };
        bool m_is_right_selected{ false };
        void check_if_selected();
        void advance_sprite();
        void handle_mouse_moment_event();
        // #2F7B23
    };
}  // namespace playing_cards

#endif