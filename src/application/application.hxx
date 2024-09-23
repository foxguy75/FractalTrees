#ifndef APPLICATION_HXX
#define APPLICATION_HXX

#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <SDL.h>
/* Undefine main since including SDL.h defines main here and since is a library it does not care about a main. */
#undef main
#include <SDL_ttf.h>

#include <subsystem/subsystem.hxx>

#include <game_components/card.hxx>

#include <sprite_atlas.hxx>

namespace fs = std::filesystem;

namespace application
{
    struct Version
    {
        std::string get_string() const;

        int m_major{ 0 };
        int m_minor{ 0 };
        int m_patch{ 1 };
    };

    class Game
    {
       public:
        Game();
        Game( int theScreenWidth, int theScreenHight );
        Game( std::string theName, int theScreenWidth, int theScreenHight );
        Game( std::string theName );
        ~Game() = default;

        void run();

        void add_sprite_atlas( const std::string&, const std::filesystem::path&, const std::filesystem::path& );

        SDL_Renderer* const get_renderer() const { return m_renderer.get(); };

        std::string get_application_name() const { return m_application_name; };

        // Return the requested sprite atlas.
        const sprite::Atlas* get_atlas( const std::string& the_atlas_name ) const
        {
            return m_atlas.at( the_atlas_name ).get();
        }

        int m_screenWidth{ 64 * 16 };
        int m_screenHight{ 32 * 16 };

        std::vector<playing_cards::Card> deck{};

        void shuffle_deck();

        Version m_version{};

       private:
        std::string m_application_name{ "Test Application" };
        subsystem::Subsystem m_subsystem{};
        fs::path m_font_path{};
        std::map<std::string, std::unique_ptr<sprite::Atlas>> m_atlas{};

        std::unique_ptr<SDL_Window, decltype( &SDL_DestroyWindow )> m_window{
            SDL_CreateWindow( m_application_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth,
                              m_screenHight, SDL_WINDOW_SHOWN ),
            SDL_DestroyWindow };
        std::unique_ptr<SDL_Renderer, decltype( &SDL_DestroyRenderer )> m_renderer{
            SDL_CreateRenderer( m_window.get(), -1, SDL_RENDERER_ACCELERATED ), SDL_DestroyRenderer };
        // TODO: Better Asset Loading!
        std::unique_ptr<TTF_Font, decltype( &TTF_CloseFont )> m_font{
            TTF_OpenFont( "E:\\Repos\\sdlTree\\assets\\fonts\\FiraCode-Regular.ttf", 16 ), TTF_CloseFont };

        void display_version_info();

    };  // namespace std::filesystem

}  // namespace application

#endif
