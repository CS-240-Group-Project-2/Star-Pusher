#include "Core.h"

Core::Core():
    gWindow(nullptr), gScreenSurface(nullptr), gHelloWorld(nullptr), setupSuccess(false)
{
    // we will setup SDL here
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		this->setupSuccess = false;
	}
	else
	{
		//Create window
		this->gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if(this->gWindow == NULL)
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			this->setupSuccess = false;
		}
		else
		{
			//Get window surface
			this->gScreenSurface = SDL_GetWindowSurface(this->gWindow);
			// if setup was successful we should add images
			images newImage;
			newImage.name = "TITLESCREEN";
			newImage.file = "res/images/star_title.png";
			this->imageDatabase.push_back(newImage);
			this->setupSuccess = true;
		}
	}
}

Core::~Core()
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

bool Core::init()
{
    //Start up SDL and create window
	if(!this->setupSuccess)
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
			//Apply the image
			SDL_BlitSurface(this->gHelloWorld, NULL, this->gScreenSurface, NULL);

			//Update the surface
			SDL_UpdateWindowSurface(this->gWindow);

			// we will loop until we exit
			bool loop = true;
			while(loop)
			{
			    if(SDL_PollEvent(&this->event) != 0)
                {
                    int keyPressed = this->event.key.keysym.sym;
                    switch(this->event.type)
                    {
                    case SDL_KEYDOWN:
                        printf( "%c was press\n", keyPressed);
                        break;
                    case SDL_KEYUP:
                        printf( "%c was released\n", keyPressed);
                        break;
                    case SDL_QUIT:
                        loop = false;
                        break;
                    default:
                        break;
                    }
                }
			}
		}
	}
	return true;
}

bool Core::loadMedia()
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


bool Core::file_exists(string file)
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

int Core::searchImages(string fileName)
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
