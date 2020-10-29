#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

//FPS
const int FPS = 60;

void limitaFrames(Uint32 frameStart){
	if((1000/FPS) > SDL_GetTicks() - frameStart){
		SDL_Delay((1000/FPS) - (SDL_GetTicks() - frameStart));
	}
}
bool inicializaSDL(SDL_Window** window, SDL_Renderer** renderer){
	//Inicializa a SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1){
		printf("Erro ao inicializar: %s.\n", SDL_GetError());
		return false;
	}
	
	//Cria uma janela
	*window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1040, 650, 0);
	if(!(*window)){
		printf("Erro ao criar janela: %s.\n", SDL_GetError());
		SDL_Quit();
		return false;	
	}

	//Cria um renderer
	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if(!(*renderer)){
		printf("Erro ao criar o renderer: %s.\n", SDL_GetError());
		SDL_DestroyWindow(*window);
		SDL_Quit();
		return false;
	}

	return true;
}
int main(){
	
	SDL_Window* window;
	SDL_Renderer* renderer;
	if(!inicializaSDL(&window, &renderer)){
		return -1;
	}
	
	//Cria uma surface
	SDL_Surface* surface = IMG_Load("Raquete.jpeg");
	if(!surface){
		printf("Erro ao criar uma surface: %s.\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	SDL_Surface* surface2 = IMG_Load("Raquete2.jpeg");
	if(!surface2){
		printf("Erro ao criar uma surface: %s.\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	SDL_Surface* surface3 = IMG_Load("Linha.jpeg");
	if(!surface3){
		printf("Erro ao criar uma surface: %s.\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	//Cria uma textura
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if(!texture){
		printf("Erro ao criar uma textura: %s\n.", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;	
	}
	
	SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
	SDL_FreeSurface(surface2);
	if(!texture2){
		printf("Erro ao criar uma textura: %s\n.", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;	
	}

	SDL_Texture* texture3 = SDL_CreateTextureFromSurface(renderer, surface3);
	SDL_FreeSurface(surface3);
	if(!texture3){
		printf("Erro ao criar uma textura: %s\n.", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;	
	}

	int raquete1 = 0, raquete2 = 1, linha = 2, bola = 3;

	SDL_Rect dest[4];
	//SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	dest[raquete1].w = 20;
	dest[raquete1].h = 105;
	dest[raquete1].x = 20;
	dest[raquete1].y = 270;
	
	dest[raquete2].w = 20;
	dest[raquete2].h = 105;
	dest[raquete2].x =  1040 - 45;
	dest[raquete2].y = 270;

	dest[linha].w = 14;
	dest[linha].h = 610;
	dest[linha].x = 1040 - 527;
	dest[linha].y = 20;

	dest[bola].w = 20;
	dest[bola].h = 20;
	dest[bola].x = 510;
	dest[bola].y = 315;
	
	
	float velocidadeRaquete = 19.5;
	
	
	//Usado para contar tempo de cada frame
	Uint32 frameStart;	

	SDL_Event event;
	bool close = false;
	
	while(!close){
		frameStart = SDL_GetTicks();
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					close = true;
					break;
				
			}
		}
		const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

		if(keyboard_state_array[SDL_SCANCODE_UP] && !(keyboard_state_array[SDL_SCANCODE_DOWN])){
			dest[raquete2].y += (-velocidadeRaquete);
			if (dest[raquete2].y < 0) dest[raquete2].y = 0;			
		}
		else if(!(keyboard_state_array[SDL_SCANCODE_UP]) && keyboard_state_array[SDL_SCANCODE_DOWN]){
			dest[raquete2].y += velocidadeRaquete;
			if (dest[raquete2].y > 545) dest[raquete2].y = 545;
		}

		if(keyboard_state_array[SDL_SCANCODE_W] && !(keyboard_state_array[SDL_SCANCODE_S])){
			dest[raquete1].y += (-velocidadeRaquete);
			if (dest[raquete1].y < 0) dest[raquete1].y = 0;				
		}
		else if(!(keyboard_state_array[SDL_SCANCODE_W]) && keyboard_state_array[SDL_SCANCODE_S]){
			dest[raquete1].y += (velocidadeRaquete);
			if (dest[raquete1].y > 545) dest[raquete1].y = 545;
		}					

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, &dest[raquete1]);
		SDL_RenderCopy(renderer, texture2, NULL, &dest[raquete2]);
		SDL_RenderCopy(renderer, texture3, NULL, &dest[linha]);
		SDL_RenderCopy(renderer, texture2, NULL, &dest[bola]);
		SDL_RenderPresent(renderer);
		
		limitaFrames(frameStart);
	}



	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(texture2);
	SDL_DestroyTexture(texture3);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}
