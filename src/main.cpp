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

#include <ctime>
#include <Collider.h>
#include <Layers.h>


const int LEVEL_WIDTH = 1080;
const int LEVEL_HEIGHT = 740;
//Screen dimension constants
const int SCREEN_WIDTH = 645;
const int SCREEN_HEIGHT = 496;
//Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;
const float speed = .02;
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
SDL_Texture* gTextureDino = NULL;
SDL_Texture* gTextureBCG1 = NULL;
SDL_Texture* gTextureBCG2 = NULL;
SDL_Texture* gTextureBCG3 = NULL;
SDL_Texture* gTextureBCG4 = NULL;
SDL_Texture* gTexturePLATFORM = NULL;
SDL_Texture* gTextureStar = NULL;
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
    gTextureDino = loadTexture("../assets/dino.png" );
    if(gTextureDino == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    gTextureBCG1 = loadTexture("../assets/mountain.png" );
    if(gTextureBCG1 == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    gTextureBCG2 = loadTexture("../assets/mountain.png" );
    if(gTextureBCG2 == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    gTextureBCG3 = loadTexture("../assets/mountain.png" );
    if(gTextureBCG3 == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    gTextureBCG4 = loadTexture("../assets/mountain.png" );
    if(gTextureBCG4 == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    gTexturePLATFORM = loadTexture("../assets/PLATFORM.png" );
    if(gTexturePLATFORM == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    gTextureStar = loadTexture("../assets/star.png" );
    if(gTextureStar == NULL )
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
    float bcgspeed=0;
    auto* player1 = new Player(0, 300, texture, 0, 0);
   // player1->setTexture(gTextureDino);
    bool grounded = false;
    auto* coll1 = new Collider(player1->getX(), player1->getY(), Shape::rect, false, player1, 50, 100);
    auto* layers = new Layers();
    auto* bcg1 = new GameObject(0, 0);
    layers->addGOtoLayer(0, bcg1);
    auto* bcg2 = new GameObject(LEVEL_WIDTH/2.0, 0);
    layers->addGOtoLayer(0, bcg2);
    auto* bcg3 = new GameObject(LEVEL_WIDTH, 0);
    layers->addGOtoLayer(0, bcg3);
    auto* bcg4 = new GameObject((3*LEVEL_WIDTH)/2.0, 0);
    layers->addGOtoLayer(0, bcg4);
    auto* obst = new GameObject(LEVEL_WIDTH/2.0, 350);
    auto* obstColl = new Collider(obst->getX(), obst->getY(), Shape::rect, false, obst, 50, 100);
    layers->addGOtoLayer(1, obst);
    auto* star = new GameObject(LEVEL_WIDTH, 100);
    layers->addGOtoLayer(2, star);



    auto* floor = new Collider(-2*SCREEN_WIDTH, SCREEN_HEIGHT-30, Shape::rect, false, nullptr, 4*SCREEN_WIDTH, 10);

    //mazenode->addColliders();

    player1->start();

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
                                if(grounded) player1->setSpeedY(-12*speed);
                                break;

                            case SDLK_DOWN:
                                player1->setSpeedY(speed);
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

                        }
                    }

                }
                //player1->setSpeedY(speed);
                //Update game objects
                layers->update(bcgspeed);
                if(player1->getX()>200){
                    player1->setSpeedX(0);
                    bcgspeed = 2*speed;
                }
                else
                {
                    player1->setSpeedX(2*speed);
                    bcgspeed = 2*speed;
                }
                player1->update();
                coll1->update();
                obstColl->update();

                //Clear screen
                SDL_RenderClear( gRenderer );
                //SDL_RenderCopy( gRenderer, gTextureDino, NULL, NULL );
                //Render red filled quad


                grounded = coll1->checkCollision(floor);
                if(!grounded)
                {
                    player1->setAccY(.0001);
                }
                else
                {
                    player1->setAccY(0);
                }
                //std::cout<<star->getX()<<" "<<star->getY()<<" "<<std::endl;

                //player1->render(gRenderer, 0x00, 0x00, 0x00, 0xff);
                if(obstColl->checkCollision(coll1)){
                    return 0;
                }

                SDL_Rect fillRect;
                //rendering player
                SDL_RenderDrawRect(gRenderer, &fillRect);
                fillRect = {bcg1->getX(), bcg1->getY(), LEVEL_WIDTH/2, LEVEL_HEIGHT};
                SDL_RenderCopy(gRenderer, gTextureBCG1, nullptr, &fillRect);
                fillRect = {bcg2->getX(), bcg2->getY(), LEVEL_WIDTH/2, LEVEL_HEIGHT};
                SDL_RenderCopy(gRenderer, gTextureBCG2, nullptr, &fillRect);
                fillRect = {bcg2->getX(), bcg2->getY(), LEVEL_WIDTH/2, LEVEL_HEIGHT};
                SDL_RenderCopy(gRenderer, gTextureBCG3, nullptr, &fillRect);
                fillRect = {bcg3->getX(), bcg3->getY(), LEVEL_WIDTH/2, LEVEL_HEIGHT};
                SDL_RenderCopy(gRenderer, gTextureBCG4, nullptr, &fillRect);
                fillRect = {0, 450, LEVEL_WIDTH, 50};
                SDL_RenderCopy(gRenderer, gTexturePLATFORM, nullptr, &fillRect);
                fillRect = {obstColl->getX(), obstColl->getY(), obstColl->getW(), obstColl->getH()};
                SDL_RenderCopy(gRenderer, gTexturePLATFORM, nullptr, &fillRect);
                fillRect = {star->getX(),0, 100, 100};
                SDL_RenderCopy(gRenderer, gTextureStar, nullptr, &fillRect);
                fillRect = {player1->getX(), player1->getY(), 100, 100};
                SDL_RenderCopy(gRenderer, gTextureDino, nullptr, &fillRect);



                //4A3071
                SDL_SetRenderDrawColor(gRenderer, 0x4a, 0x30, 0x71, 0xFF);
                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}