/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>
#include <Player.h>
#include <MazeNode.h>
#include <Maze.h>
#include <ctime>
#include <Collider.h>


const int LEVEL_WIDTH = 1080;
const int LEVEL_HEIGHT = 740;
//Screen dimension constants
const int SCREEN_WIDTH = 645;
const int SCREEN_HEIGHT = 496;
//Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;
const float speed = .1;
//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();

void drawTriangle(SDL_Renderer* renderer, float* X, float* Y);
//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The window renderer
SDL_Renderer* gRenderer = NULL;
//Current displayed texture
SDL_Texture* gTexture = NULL;
//Game Controller 1 handler
SDL_Joystick* gGameController = NULL;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
        if( SDL_NumJoysticks() < 1 )
        {
            printf( "Warning: No joysticks connected!\n" );
        }
        else
        {
            //Load joystick
            gGameController = SDL_JoystickOpen( 0 );
            if( gGameController == NULL )
            {
                printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
            }
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load PNG texture
    gTexture = loadTexture( "../assets/bcg.png" );
    if( gTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }

    return success;
}


void close()
{
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    SDL_JoystickClose( gGameController );
    gGameController = NULL;
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}



int main( int argc, char* args[] )
{
    srand((time(NULL)));
    auto* player1 = new Player( 15, 15);
    auto* player2 = new Player(SCREEN_WIDTH-30, 15, Shape::rect, 0, 0);
    auto* coll1 = new Collider(player1->getX(), player1->getY(), Shape::rect, false, player1, 10, 10);
    auto* coll2 = new Collider(player2->getX(), player2->getY(), Shape::rect, false, player2, 10, 10);
    auto* finish = new Collider((SCREEN_WIDTH/2)-9, SCREEN_HEIGHT-30, Shape::rect, false, nullptr, 10, 10);
    auto* maze = new Maze(0,0, 21, 16);
    //mazenode->addColliders();
    maze->generate();
    player1->start();
    player2->start();
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    //Handling player 1 input
                    else if( e.type == SDL_KEYDOWN ) {
                        //Select surfaces based on key press
                        switch (e.key.keysym.sym) {
                            case SDLK_UP:
                                player1->setSpeedY(-speed);
                                break;

                            case SDLK_DOWN:
                                player1->setSpeedY(speed);
                                break;

                            case SDLK_LEFT:
                                player1->setSpeedX(-speed);
                                break;

                            case SDLK_RIGHT:
                                player1->setSpeedX(speed);
                                break;

                        }

                    } else if(e.type == SDL_KEYUP){
                        switch(e.key.keysym.sym){
                            case SDLK_UP:
                                player1->setSpeedY(0);
                                break;

                            case SDLK_DOWN:
                                player1->setSpeedY(0);
                                break;

                            case SDLK_LEFT:
                                player1->setSpeedX(0);
                                break;

                            case SDLK_RIGHT:
                                player1->setSpeedX(0);
                                break;
                        }
                    }else if(e.type == SDL_JOYAXISMOTION){
                        if(e.jaxis.which == 0){
                            //X axis motion
                            if( e.jaxis.axis == 0 )
                            {
                                //Left of dead zone
                                if( e.jaxis.value < -JOYSTICK_DEAD_ZONE )
                                {
                                    player2->setSpeedX(-speed);
                                }
                                    //Right of dead zone
                                else if( e.jaxis.value > JOYSTICK_DEAD_ZONE )
                                {
                                    player2->setSpeedX(speed);
                                }
                                else
                                {
                                    player2->setSpeedX(0);
                                }
                            }
                            else if(e.jaxis.axis == 1){
                                //Below of dead zone
                                if( e.jaxis.value < -JOYSTICK_DEAD_ZONE )
                                {
                                    player2->setSpeedY(-speed);
                                }
                                    //Above of dead zone
                                else if( e.jaxis.value > JOYSTICK_DEAD_ZONE )
                                {
                                    player2->setSpeedY(speed);
                                }
                                else
                                {
                                    player2->setSpeedY(0);
                                }
                            }
                        }
                    }
                }

                //Update game objects
                player1->update();
                player2->update();
                coll1->update();
                coll2->update();
                //std::cout<<"player1: "<<coll1->getX()<<" "<<coll1->getY()<<" "<<coll1->getX()+coll1->getW()<<" "<<coll1->getY()+coll1->getH()<<std::endl;
                //std::cout<<"player2: "<<coll2->getX()<<" "<<coll2->getY()<<" "<<coll2->getX()+coll2->getW()<<" "<<coll2->getY()+coll2->getH()<<std::endl;
                coll1->checkCollision(coll2);
                //coll2->checkCollision(coll1);



                //Clear screen
                SDL_RenderClear( gRenderer );
                //SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
                //Render red filled quad
                for(int i = 0; i<maze->getWidth(); i++){
                    for(int j = 0; j<maze->getHeight(); j++){
                        for(auto* coll : maze->getNodes()[i][j].colls){
                            coll1 -> checkCollision(coll);
                            coll2 -> checkCollision(coll);
                        }
                    }
                }

                if(coll1->checkCollision(finish) || coll2->checkCollision(finish)){
                    quit = true;
                }



                //std::cout<<player1->getX()<<" "<<player1->getY()<<" "<<player2->getX()<<" "<<player2->getY()<<std::endl;
                maze->render(gRenderer, 0x00, 0xff, 0x00, 0xff);
                player1->render(gRenderer, 0xff, 0x00, 0x00, 0xff);
                player2->render(gRenderer, 0x00, 0x00, 0xff, 124);
                SDL_Rect fillRect = {finish->getX(), finish->getY(), finish->getW(), finish->getH()};
                SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 30);
                SDL_RenderDrawRect(gRenderer, &fillRect);

                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}