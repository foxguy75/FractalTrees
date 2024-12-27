#ifndef DECK_HXX
#define DECK_HXX

#include <SDL2/SDL_render.h>
#include <card_decl.hxx>
#include <memory>
#include <vector>

#include <sprite_atlas.hxx>

struct Deck
{
   public:
    Deck( int screen_x, int screen_y, SDL_Renderer* the_atlas );
    Deck( const Deck& that ) = default;
    Deck( Deck&& that ) = default;
    Deck& operator=( const Deck& that ) = default;
    Deck& operator=( Deck&& that ) = default;
    ~Deck() = default;

    void draw();

    void shuffle();
    void add( std::shared_ptr<playing_cards::Card> the_card );
    std::shared_ptr<playing_cards::Card> draw_card();
    size_t size() const { return m_deck.size(); }

    class iterator
    {
       private:
        std::vector<std::shared_ptr<playing_cards::Card>>::iterator m_iter{};

       public:
        iterator( std::vector<std::shared_ptr<playing_cards::Card>>::iterator the_iter ) : m_iter{ the_iter } {};
        std::shared_ptr<playing_cards::Card>& operator*() const { return *m_iter; }
        iterator& operator++()
        {
            ++m_iter;
            return *this;
        }
        bool operator!=( const iterator& that ) const { return m_iter != that.m_iter; }
    };

    iterator begin() { return iterator{ m_deck.begin() }; }
    iterator end() { return iterator{ m_deck.end() }; }

    void handle_event( const SDL_Event& the_event );

   private:
    SDL_Point m_position{};
    std::vector<std::shared_ptr<playing_cards::Card>> m_deck{};
    SDL_Renderer* m_renderer{};
    application::sprite::Atlas m_atlas{};
    application::sprite::Sprite m_current_sprite{};
};

#endif  // DECK_HXX
