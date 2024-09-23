#include <sprite_atlas.hxx>

#include <SDL2/SDL_image.h>

#include <fmt/format.h>

#include <rapidjson/document.h>
#include <rapidjson/pointer.h>

#include <fstream>
#include <iostream>

namespace application
{
    namespace sprite
    {
        Atlas::Atlas( SDL_Renderer* the_render, const std::filesystem::path& the_sprite_path,
                      const std::filesystem::path& the_sprite_json )
        {
            this->assign( the_render, the_sprite_path );

            std::ifstream json_file{ the_sprite_json, std::ifstream::in };

            std::string json_text{};

            if( json_file.is_open() )
            {
                std::string line{};
                while( getline( json_file, line ) )
                {
                    json_text += line;
                }
            }

            rapidjson::Document doc{};

            doc.Parse( json_text.c_str() );

            rapidjson::Value* sprite_json_body = rapidjson::Pointer( "/sprite" ).Get( doc );

            if( !sprite_json_body->IsArray() )
            {
                std::cout << fmt::format( "Failed to load sprite meta data json at location: {}",
                                          the_sprite_json.string().c_str() )
                          << std::endl;
            }
            else
            {
                for( const rapidjson::Value& sprite : sprite_json_body->GetArray() )
                {
                    const rapidjson::Value* display_name = rapidjson::Pointer( "/display_name" ).Get( sprite );
                    const rapidjson::Value* internal_name = rapidjson::Pointer( "/internal_name" ).Get( sprite );
                    const rapidjson::Value* rectangle = rapidjson::Pointer( "/rectangle" ).Get( sprite );

                    if( display_name && internal_name && rectangle )
                    {
                        int rect_x = rectangle->FindMember( "x" )->value.GetInt();
                        int rect_y = rectangle->FindMember( "y" )->value.GetInt();
                        int rect_w = rectangle->FindMember( "w" )->value.GetInt();
                        int rect_h = rectangle->FindMember( "h" )->value.GetInt();
                        SDL_Rect temp_rect{ rect_x, rect_y, rect_w, rect_h };
                        m_sprites.emplace_back( display_name->GetString(), internal_name->GetString(), temp_rect );
                    }
                }
            }
        }

        void Atlas::assign( SDL_Renderer* the_render, const std::filesystem::path& the_sprite_path )
        {
            SDL_Texture* thing = IMG_LoadTexture( the_render, the_sprite_path.string().c_str() );

            SDL_QueryTexture( thing, nullptr, nullptr, &m_max_width, &m_max_hight );

            if( thing == nullptr )
            {
                throw fmt::system_error( 100, "Failed to load texture: {} - Error Message: {}",
                                         the_sprite_path.string(), SDL_GetError() );
            }
            else
            {
                m_atlas_texture.reset( thing );
            }
        }
    }  // namespace sprite
}  // namespace application
