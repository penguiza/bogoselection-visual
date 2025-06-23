#define SDL_MAIN_HANDLED
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>
#include <utility>
#include <SDL2/SDL.h>r>
#include <SDL2/SDL_mixer.h>
#include <string>

std::vector<Mix_Chunk*> tones(100);
const int screen_width = 960;
const int screen_height = 540;

void renderArray(SDL_Renderer* renderer, const std::vector<int>& arr)
{
    int max_value = *std::max_element(arr.begin(), arr.end());
    float bar_width = static_cast<float>(screen_width) / arr.size();

    for (size_t i = 0; i < arr.size(); ++i)
    {
        int x = static_cast<int>(i * bar_width);
        int next_x = static_cast<int>((i + 1) * bar_width);
        int actual_bar_width = next_x - x;

        float normalized = static_cast<float>(arr[i]) / max_value;
        int height = static_cast<int>(normalized * screen_height);
        int y = screen_height - height;

        SDL_Rect bar = { x, y, actual_bar_width, height };

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &bar);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &bar);
    }

    SDL_RenderPresent(renderer);
}


unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 generator(seed);


int find_lowest(std::vector<int>& arr, int first_prefix)
{

    auto minimum = std::min_element(arr.begin() + first_prefix, arr.end());
    int idx = std::distance(arr.begin(), minimum);
    return idx;

}

bool is_sorted(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

void print(std::vector<int>& arr, SDL_Renderer* render, int delay)
{

    int first_prefix = 0;

    while (!is_sorted(arr))
    {
        auto target = find_lowest(arr, first_prefix);

        if (arr[target] != arr[first_prefix]) {
            std::shuffle(arr.begin() + first_prefix, arr.end(), generator);
        }
        else if (arr[target] == arr[first_prefix]) {
            int value = arr[first_prefix];
            Mix_PlayChannel(-1, tones[value - 1], 0);
            ++first_prefix;
            SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        }
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);
        renderArray(render, arr);
        SDL_Delay(delay);

    }



}


int main(int argc, char* argv[])
{

    std::vector<int> arr(100);
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer failed: " << Mix_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    for (int i = 0; i < tones.size(); ++i)
    {
        std::string file_name = "tones/note_" + std::to_string(i + 1) + ".wav";
        tones[i] = Mix_LoadWAV(file_name.c_str());
    }

  

    for (int i = 0; i < arr.size(); ++i)
    {
        arr[i] = i + 1;
    }
    std::shuffle(arr.begin(), arr.end(), generator);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL failed: " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Visualization",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screen_width,
        screen_height,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    SDL_Event e;
    int delay;
    std::cout << "R TO SHUFFLE K TO START" << std::endl;
    std::cout << "How much delay between shuffles: ";
    std::cin >> delay;
    renderArray(renderer, arr);


    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_k) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);

                    print(arr, renderer, delay);
                    SDL_Delay(100);
                }
                if (e.key.keysym.sym == SDLK_r) {
                    std::shuffle(arr.begin(), arr.end(), generator);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    renderArray(renderer, arr);
                }
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }

            }

        }


    }

    for (auto* chunk : tones)
        Mix_FreeChunk(chunk);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}