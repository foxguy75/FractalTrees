#include <memory>

#include <Application.hxx>
#include <SDL2/SDL.h>
#include <math.h>

#include <TreeNode.hxx>

[[nodiscard]] std::pair<int, int> generatePoints( std::pair<int, int> theOrigin, float theAngle,
                                                  int theLength ) noexcept
{
    auto [ x, y ] = theOrigin;

    int yDelta = std::round( theLength * std::sin( theAngle ) );
    int xDelta = std::round( theLength * std::cos( theAngle ) );

    return std::make_pair<int, int>( x + xDelta, y - yDelta );
}

void generatorTreeNodes( TreeNode<std::pair<int, int>>* node, const int maxLevel, int currentLevel, float initAngle,
                         float deltaAngle, int length ) noexcept
{
    if( currentLevel < maxLevel )
    {
        length *= 0.67;
        initAngle += deltaAngle;
        node->left = std::make_unique<TreeNode<std::pair<int, int>>>( generatePoints( node->data, initAngle, length ) );

        float tempAngle = initAngle - deltaAngle * 2;

        node->right =
            std::make_unique<TreeNode<std::pair<int, int>>>( generatePoints( node->data, tempAngle, length ) );

        int newLevel = currentLevel + 1;

        generatorTreeNodes( node->left.get(), maxLevel, newLevel, initAngle, deltaAngle, length );
        generatorTreeNodes( node->right.get(), maxLevel, newLevel, tempAngle, deltaAngle, length );
    }
    return;
}

void drawTree( TreeNode<std::pair<int, int>>* node, SDL_Renderer* theRenderer )
{
    if( node->left != nullptr && node->right != nullptr )
    {
        SDL_RenderDrawLine( theRenderer, node->data.first, node->data.second, node->left->data.first,
                            node->left->data.second );

        SDL_RenderDrawLine( theRenderer, node->data.first, node->data.second, node->right->data.first,
                            node->right->data.second );

        SDL_RenderPresent( theRenderer );

        drawTree( node->left.get(), theRenderer );
        drawTree( node->right.get(), theRenderer );
    }
    return;
}

int tree_main( int argc, char* argv[] )
{
    int screenWidth = 64 * 16;
    int screenHight = 32 * 16;

    Application app{ "Fractal Trees" };

    SDL_SetRenderDrawColor( app.getRenderer(), 255, 255, 255, 0 );

    float initAngle{ M_PI * .5 };
    float deltaAngle{ .78 };

    const int MAX_LEVEL{ 15 };
    const float shrink = 0.67;
    int length = screenHight / 4;

    std::unique_ptr<TreeNode<std::pair<int, int>>> head =
        std::make_unique<TreeNode<std::pair<int, int>>>( std::make_pair( screenWidth / 2, screenHight * .75 ) );

    SDL_RenderDrawLine( app.getRenderer(), screenWidth / 2, screenHight, head->data.first, head->data.second );

    generatorTreeNodes( head.get(), MAX_LEVEL, 0, initAngle, deltaAngle, length );

    drawTree( head.get(), app.getRenderer() );

    app.run();

    return 0;
}
