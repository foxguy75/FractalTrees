#ifndef APPLICATION_SPRITE_ATLAS_HXX
#define APPLICATION_SPRITE_ATLAS_HXX

#include <filesystem>
#include <string>

#include <SDL2/SDL_render.h>
#include <memory>

namespace application
{
    namespace sprite
    {
        struct Sprite
        {
            std::string m_display_name{ "" };
            std::string m_internal_name{ "" };
            SDL_Rect m_rect{ 0, 0, 0, 0 };
        };

        struct Atlas
        {
            Atlas() = default;
            Atlas( SDL_Renderer*, const std::filesystem::path&, const std::filesystem::path& );

            void assign( SDL_Renderer*, const std::filesystem::path& );

            int m_max_width{ 0 };
            int m_max_hight{ 0 };

            std::unique_ptr<SDL_Texture, decltype( &SDL_DestroyTexture )> m_atlas_texture{ nullptr,
                                                                                           SDL_DestroyTexture };

            std::vector<Sprite> m_sprites{};
        };
    }  // namespace sprite

}  // namespace application

#endif