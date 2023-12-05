#include "../include/spritesheet.hpp"
Drawer::Drawer(char const *ss_terrain, char const *ss_feature,
               char const *ss_agent) {
  this->width = SIZE * 10;
  this->height = SIZE * 10;

  this->window = SDL_CreateWindow("window", 0, 0, this->width, this->height,
                                  SDL_WINDOW_ALLOW_HIGHDPI);

  this->renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

  this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_STATIC, SIZE, SIZE);

  this->ss_terrain = IMG_LoadTexture(renderer, ss_terrain);
  this->ss_feature = IMG_LoadTexture(renderer, ss_feature);
  this->ss_agent = IMG_LoadTexture(renderer, ss_agent);

  clip.w = 10;
  clip.h = 10;
};

Drawer::~Drawer() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyTexture(texture);
  SDL_DestroyWindow(window);
};

void Drawer::draw_sprite(const std::unique_ptr<Terrain> &entity, const int x,
                         const int y) {
  // get coords in pixels
  clip.x = entity->get_spritesheet_pos_x() * 10;
  clip.y = entity->get_spritesheet_pos_y() * 10;

  clip.w = 10;
  clip.h = 10;

  SDL_Rect position;
  position.x = x;
  position.y = y;
  position.w = 10;
  position.h = 10;

  SDL_RenderCopy(renderer, ss_terrain, &clip, &position);
};

void Drawer::draw_sprite(const std::unique_ptr<Feature> &entity, const int x,
                         const int y) {
  // get coords in pixels
  clip.x = entity->get_spritesheet_pos_x() * 10;
  clip.y = entity->get_spritesheet_pos_y() * 10;

  clip.w = 10;
  clip.h = 10;

  SDL_Rect position;
  position.x = x;
  position.y = y;
  position.w = 10;
  position.h = 10;

  SDL_RenderCopy(renderer, ss_feature, &clip, &position);
};

void Drawer::draw_sprite(const std::unique_ptr<Agent> &entity, const int x,
                         const int y) {
  // get coords in pixels
  clip.x = entity->get_spritesheet_pos_x() * 10;
  clip.y = entity->get_spritesheet_pos_y() * 10;

  clip.w = 10;
  clip.h = 10;

  SDL_Rect position;
  position.x = x;
  position.y = y;
  position.w = 10;
  position.h = 10;

  // printf("Agent at: %i, %i", position.x, position.y);

  SDL_RenderCopy(renderer, ss_agent, &clip, &position);
};

void Drawer::draw_game(Game &game) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      // Terrain *terrain = game->terrain[i][j];
      // Feature *feature = game->feature[i][j];
      //  Agent* agent = game->agent[i][j];

      pointer_terrain terrain_pointer = std::move(game.get_terrain(i, j));
      pointer_feature feature_pointer = std::move(game.get_feature(i, j));
      pointer_agent agent_pointer = std::move(game.get_agent(i, j));

      int draw_pos_x = i * 10;
      int draw_pos_y = j * 10;
      // Character* character = game->character[i][j];
      if (terrain_pointer)
        draw_sprite(terrain_pointer, draw_pos_x, draw_pos_y);
      if (feature_pointer && terrain_pointer->get_type() == "dirt")
        draw_sprite(feature_pointer, draw_pos_x, draw_pos_y);
      if (agent_pointer) // TODEBUG
        draw_sprite(agent_pointer, draw_pos_x, draw_pos_y);

      // if (agent) draw_sprite(agent, draw_pos_x, draw_pos_y);
      game.set_terrain(i, j, terrain_pointer);
      game.set_feature(i, j, feature_pointer);
      game.set_agent(i, j, agent_pointer);
    }
  }
  // draw_agents();
}

void Drawer::draw_agents() {
  for (std::pair<int, Agent *> agent : Agent::AgentList) {
    // draw_sprite(agent.second, agent.second->posX * 10, agent.second->posY *
    // 10);
  }
}

void Drawer::present() { SDL_RenderPresent(renderer); };

void Drawer::flush() { SDL_RenderClear(renderer); }
