#ifndef DECK_HXX
#define DECK_HXX

#include <random>
#include <vector>

template <typename T>
class Deck
{
   public:
    Deck() = default;
    Deck( std::initializer_list<T> the_list ) : m_deck( the_list ) {}
    Deck( const Deck& that ) = default;
    Deck( Deck&& that ) = default;
    Deck& operator=( const Deck& that ) = default;
    Deck& operator=( Deck&& that ) = default;
    ~Deck() = default;

    void shuffle()
    {
        std::random_device rd{};

        std::mt19937 g( rd() );

        std::shuffle( m_deck.begin(), m_deck.end(), g );
    }

    T draw()
    {
        T card = m_deck.back();
        m_deck.pop_back();
        return card;
    }
    void add( T card );

    T operator[]( size_t index ) const { return m_deck[ index ]; }

    size_t size() const { return m_deck.size(); }

   private:
    std::vector<T> m_deck{};
};

#endif  // DECK_HXX