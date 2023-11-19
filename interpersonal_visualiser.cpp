/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <vector>
#include <cmath>

#include "interpersonal.cpp"
// #include "interpersonal_visualiser.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

bool init();
void loadMedia();
void close();

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font;
// SDL_Surface* gHelloWorld = NULL;

std::vector<std::pair<int, int>> centres;

void findCentres(int n)
{
	double theta = 360.0 / n;
	for (int i = 0; i < n; i++)
	{
		double ang = (M_PI/180.0) * i * theta;
		int x = 400 + 300 * sin(ang);
		int y = 400 - 300 * cos(ang);
		printf("%f: %i %i\n", i*theta, x , y);
		centres.push_back({x, y});
	}
}

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_ERROR: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		window = SDL_CreateWindow("Relationship Visualiser", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
		}
	}
	TTF_Init();
	font = TTF_OpenFont("times.ttf", 60);
	return success;
}

void drawNodes()
{
	SDL_Color textColor = {255, 255, 255};
	for (int i = 0; i < Entities.size(); i++)
	{
		for (int j = 0; j < Entities.size(); j++)
		{
			if (j == i) continue;
			int midpointX = (centres[i].first + centres[j].first)/2;
			int midpointY = (centres[i].second + centres[j].second)/2;
			int tmp = Entities[i]->relationShips[j][2];

			if (tmp >= 0)
				SDL_SetRenderDrawColor(renderer, 0, 2*tmp + 50, 0, 255);
			else
				SDL_SetRenderDrawColor(renderer, 2*tmp - 50, 0, 0, 255);
			SDL_RenderDrawLine(renderer, centres[i].first, centres[i].second, midpointX, midpointY);
		}
	}
	for (int i = 0; i < Entities.size(); i++)
	{
		auto [x, y] = centres[i];
		SDL_Rect rect = {x-25, y-25, 50, 50};
		SDL_Rect text_rect = {x-20, y-20, 40, 40};
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, (Entities[i]->name).c_str(), textColor);
		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		SDL_RenderCopy(renderer, Message, NULL, &text_rect);
		if (Entities[i]->happiness > 50)
			SDL_SetRenderDrawColor(renderer, 0, 4*(Entities[i]->happiness - 50) + 50, 0, 255);
		else
			SDL_SetRenderDrawColor(renderer, 4*(50-Entities[i]->happiness) + 50, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &rect);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);
	}
	SDL_RenderPresent(renderer);
}
// void loadMedia()
// {
// 	// bool success = true;
// 	rect.x += 50;
// 	SDL_RenderFillRect(gRenderer, &rect);
// 	SDL_RenderDrawPoint(gRenderer, 300, 300);
// }

// void drawSquare(int x, int y)
// {
// 	SDL_Rect rect = {x, y, 20, 20};
// 	SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);
// 	SDL_RenderFillRect(gRenderer, &rect);
// 	SDL_RenderPresent(gRenderer);
// }

void close()
{
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

int main()
{
	initialiseEntities();
	printf("Entities are : %i\n", Entities.size());
	findCentres(Entities.size());
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		SDL_Event e; 
		bool quit = false; 
		bool draw = false;
		int cooldown = 0;
		while (quit == false) 
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			interact();
			drawNodes();
			while (SDL_PollEvent (&e))
			{
				if (e.type == SDL_QUIT) quit = true;
				// else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
				// {
			// if (cooldown)
			// {
				// cooldown = 0;
				// continue;
			}
				// }
			// }
		}
	}
	close();
	return 0;
}