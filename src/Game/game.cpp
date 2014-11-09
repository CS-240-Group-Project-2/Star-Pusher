#include "game.h"

Game::Game():
    gWindow(nullptr), gScreenSurface(nullptr), gHelloWorld(nullptr)
{
    // setup the startupStatus vector
    for(int i=0;i<AMOUNT-1;++i)
        this->startupStatus.push_back(false); // default to false
    // we will setup SDL here
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        this->startupStatus[SDL] = false;
	}
	else
	{
		//Create window
		this->gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if(this->gWindow == NULL)
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			this->startupStatus[SDL] = false;
		}
		else
		{
			//Get window surface
			this->gScreenSurface = SDL_GetWindowSurface(this->gWindow);
			// if setup was successful we should add images
			images newImage;
			newImage.name = "TITLESCREEN";
			newImage.file = "res/images/screens/star_title.png";
			this->imageDatabase.push_back(newImage);
			this->startupStatus[SDL] = true;
		}
	}
}

Game::~Game()
{
    //Deallocate surface
	SDL_FreeSurface(this->gHelloWorld );
	gHelloWorld = nullptr;

	//Destroy window
	SDL_DestroyWindow(this->gWindow);
	gWindow = nullptr;

	//Quit SDL subsystems
	SDL_Quit();
}

bool Game::init()
{
    //Start up SDL and create window
	if(!this->startupStatus[SDL])
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if(!this->loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
            this->startupStatus[MEDIA] = true;
		}
	}
	return true;
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	string fileName = "";
	int record = this->searchImages("TITLESCREEN");
	cout << record << endl;
	SDL_Delay(10000);
	if(record != -1)
        fileName = this->imageDatabase[record].file;
	if(this->file_exists(fileName.c_str()))
    {
        this->gHelloWorld = IMG_Load(fileName.c_str());
    }
    else
        printf("Can't load file: %s\n", fileName.c_str());

	if(this->gHelloWorld == NULL)
	{
		printf( "Unable to load image %s! SDL Error: %s\n", fileName.c_str(), SDL_GetError() );
		success = false;
	}
	return success;
}


bool Game::update()
{
    //Apply the image
    SDL_BlitSurface(this->gHelloWorld, NULL, this->gScreenSurface, NULL);

    //Update the surface
    SDL_UpdateWindowSurface(this->gWindow);
    return true;
}

EventContainer Game::event()
{
    EventContainer newEvent;
    if(SDL_PollEvent(&this->sdlEvent) != 0)
    {
        int keyPressed = this->sdlEvent.key.keysym.sym;
        newEvent.type = this->sdlEvent.type;
        newEvent.key  = this->sdlEvent.key.keysym.sym;
    }
    return newEvent;
}

bool Game::file_exists(string file)
{
	ifstream f(file.c_str());
	if (f.good())
	{
		f.close();
		return true;
	}
	else
	{
		f.close();
		return false;
	}
}

int Game::searchImages(string fileName)
{
    if(this->imageDatabase.size() > 0)
    {
        int record = 0;
        for(int i = 0;i<(int)this->imageDatabase.size();++i)
        {
            if(this->imageDatabase[i].name == fileName)
            {
                record = i;
                break;
            }
            cout << this->imageDatabase[i].name << ":" << fileName << endl;
        }
        return record;
    }
    return -1;
}
