#include "game.h"
#include "../Board/Board.h"


Game::Game(){



    // setup the startupStatus vector
    for(int i=0;i<AMOUNT-1;++i)
        this->startupStatus.push_back(false); // default to false

    // we will setup SDL here
    for(int i=0;i<SURFACEAMOUNT-1;++i)
        this->surfaceController.push_back(new SDL_Surface); // set it to null

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        this->startupStatus[SDL] = false;
	}
	else
	{
		//Create window
		this->gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(this->gWindow == NULL)
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			this->startupStatus[SDL] = false;
		}
		else
		{
			//Get window surface
			//this->gScreenSurface = SDL_GetWindowSurface(this->gWindow);
			this->surfaceController[SCREEN] = SDL_GetWindowSurface(this->gWindow);
			this->startupStatus[SDL] = true;

            // if setup was successful we should add images
			images newImage;

			newImage.name = "TITLESCREEN";
			newImage.file = "res/images/screens/loaded.png";
			this->imageDatabase.push_back(newImage);

			newImage.name = "CHARBOY";
			newImage.file = "res/images/characters/boy.png";
			this->imageDatabase.push_back(newImage);

			newImage.name = "CHARCATGIRL";
			newImage.file = "res/images/characters/catgirl.png";
			this->imageDatabase.push_back(newImage);

			newImage.name = "CHARHORNGIRL";
			newImage.file = "res/images/characters/horngirl.png";
			this->imageDatabase.push_back(newImage);

			newImage.name = "CHARPINKGIRL";
			newImage.file = "res/images/characters/pinkgirl.png";
			this->imageDatabase.push_back(newImage);

			newImage.name = "CHARPRINCESS";
			newImage.file = "res/images/characters/princess.png";
			this->imageDatabase.push_back(newImage);

			newImage.name = "STAR";
			newImage.file = "res/images/objects/Star.png";
			this->imageDatabase.push_back(newImage);

			newImage.name = "GOAL";
			newImage.file = "res/images/objects/RedSelector.png";
			this->imageDatabase.push_back(newImage);

			newImage.name = "GOAL_COMPLETED";
			newImage.file = "res/images/objects/Selector.png";
			this->imageDatabase.push_back(newImage);

			newImage.name = "FLOOR";
			newImage.file = "res/images/walls/Plain_Block.png";
			this->imageDatabase.push_back(newImage);

			newImage.name = "WALL";
			newImage.file = "res/images/walls/Wall_Block_Tall.png";
			this->imageDatabase.push_back(newImage);

		}
	}
}

Game::~Game()
{
    cout << "Size: " << this->surfaceController.size() << endl;
//    while(this->surfaceController.size() != 0)
//    {
        //Deallocate surface
        for(int i=0;i<this->surfaceController.size();++i)
        {
            cout << "SDL" << endl;
            SDL_FreeSurface(this->surfaceController[i]);
            cout << "Set to NULL" << endl;
            this->surfaceController[i] = nullptr; // crash on this for some reason looking into it
            //cout << "delete" << endl;
            delete this->surfaceController[i];
        }
        cout << "Size: " << this->surfaceController.size() << endl;
//    }

	//Destroy window
	SDL_DestroyWindow(this->gWindow);
	gWindow = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
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
		//!Create renderer for window
        gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
        if( gRenderer == NULL )
        {
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        }
		// initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if(!(IMG_Init(imgFlags) & imgFlags))
        {
            printf("SDL_Image could not initialize! SDL_Image ErrorL %s\n", IMG_GetError());
            this->startupStatus[IMAGE] = false;
        }
        else
        {
            // get Window surface
            this->surfaceController[SCREEN] = SDL_GetWindowSurface(this->gWindow);
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
	//SDL_Delay(10000);
	if(record != -1)
        fileName = this->imageDatabase[record].file;
	if(this->file_exists(fileName.c_str()))
    {
        //this->gHelloWorld = IMG_Load(fileName.c_str());
        this->surfaceController[STRETCHED] = loadSurface(fileName);
    }
    else
        printf("Can't load file: %s\n", fileName.c_str());

//	if(this->gHelloWorld == NULL)
    if(this->surfaceController[STRETCHED] == nullptr)
	{
		printf( "Unable to load image %s! SDL Error: %s\n", fileName.c_str(), SDL_GetError() );
		success = false;
	}

	// load levels
	fstream levels("res/levels/levels.dat");
	string tempStr = "";
	if(levels.good())
    {
        Level newLevel;
        while(getline(levels, tempStr))
        {
            if(tempStr[0] != ';')
            {
                //cout << "DEBUG: ~" << tempStr << "~ Size: "  << tempStr.length() << endl;
                if(tempStr.length() > 0)
                {
                    int nonEmpty = 0;
                    for(int i=0;i<tempStr.length();++i)
                    {
                        if(tempStr[i] != ' ' || tempStr[i] != '\n')
                            nonEmpty++;
                    }
                    if(nonEmpty > 0 && tempStr.length() > 0 /*for the sneaky strings*/)
                        newLevel.map.push_back(tempStr);
                }
            }
            else
            {
                if(newLevel.map.size() > 0)
                {
                    this->levelTest.push_back(newLevel);
                    newLevel.map.clear();
                }
            }
        }
        levels.close();
    }
    for(int i=0;i<this->levelTest.size();++i)
    {
        cout << "### START ###" << endl;
        for(int j=0;j<this->levelTest[i].map.size();++j)
        {
            cout << this->levelTest[i].map[j] << endl;
        }
        cout << "### END ###" << endl;
    }
	return success;
}

void Game::createBoard(){
    tempMap.push_back("-########"); tempMap.push_back("##      #"); tempMap.push_back("#   .   #"); tempMap.push_back("#   $   #");
    tempMap.push_back("# .$@$. #"); tempMap.push_back("####$   #"); tempMap.push_back("---#.   #"); tempMap.push_back("---#   ##");
    tempMap.push_back("---#####");

    newBoard.createBoard(tempMap, imageDatabase, gRenderer);

}

bool Game::update()
{
    //Apply the image
    //!SDL_BlitSurface(this->surfaceController[STRETCHED], NULL, this->surfaceController[SCREEN], NULL);

    //Update the surface
    //!SDL_UpdateWindowSurface(this->gWindow);

    //!!!!!!!!! Put in gRenderer updating here !!!!!!!!!!!!!!!!!!!!!
    gRenderer = newBoard.render();
    SDL_RenderPresent(gRenderer);

    return true;
}

EventContainer Game::event()
{
    //we will call the eventhandler and return the container it gives us
    return this->eventHandler.handleAll();
}

SDL_Surface* Game::loadSurface( std::string path )
{
    //The final optimized image
    //SDL_Surface* optimizedSurface = NULL;
    this->surfaceController[OPTIMIZED] = nullptr;
    this->surfaceController[LOADED] = nullptr;
    //Load image at specified path
    //* loadedSurface = IMG_Load(path.c_str());
    this->surfaceController[LOADED] = IMG_Load(path.c_str());
    if(this->surfaceController[LOADED] == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Convert surface to screen format
        this->surfaceController[OPTIMIZED] = SDL_ConvertSurface(this->surfaceController[LOADED], this->surfaceController[SCREEN]->format, NULL);
        if(this->surfaceController[OPTIMIZED] == NULL)
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        //SDL_FreeSurface(loadedSurface);
    }

    //Apply the image stretched
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;
    SDL_BlitScaled(this->surfaceController[OPTIMIZED], NULL, this->surfaceController[LOADED], &stretchRect );
    return this->surfaceController[LOADED];
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
            //cout << this->imageDatabase[i].name << ":" << fileName << endl;
        }
        return record;
    }
    return -1;
}
