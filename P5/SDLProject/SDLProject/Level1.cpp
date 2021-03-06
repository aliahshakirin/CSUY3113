#include "Level1.h"

#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8

#define LEVEL1_ENEMY_COUNT 1

GLuint loseTextureID;

unsigned int level1_data[] = {
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1,
    3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

Level1::Level1(int *lives) {
    l1_lives = lives;
}

void Level1::Initialize() {
    
    state.nextScene = -1;
    state.mode = GAME_LEVEL;
    
    state.background = new Background();
    state.background->textureID = Util::LoadTexture("bg_star.png");
    state.background->position = glm::vec3(7, -1, 0);
    
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 4, 1);
    
    loseTextureID = Util::LoadTexture("pixel_font.png");
    // Initialize Game Objects
    
    // Initialize Player
    // can put this somewhere else as u will make this a lot of time every level
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->lives = l1_lives;
    
    state.player->position = glm::vec3(3, 0, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0,-9.81f,0);
    state.player->speed = 2.0f;
    state.player->textureID = Util::LoadTexture("george_0.png");
    
    state.player->animRight = new int[4] {3, 7, 11, 15};
    state.player->animLeft = new int[4] {1, 5, 9, 13};
    state.player->animUp = new int[4] {2, 6, 10, 14};
    state.player->animDown = new int[4] {0, 4, 8, 12};

    state.player->animIndices = state.player->animRight;
    state.player->animFrames = 4;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 4;
    state.player->animRows = 4;
    
    state.player->height = 0.8f;
    state.player->width = 0.5f;
    
    state.player->jumpPower = 6.5f;
    
    state.enemies = new Entity[LEVEL1_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("ctg.png");
       
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(12, -4, 0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = WAITANDGO;
    state.enemies[0].aiState = IDLE;
    
    
}
void Level1::Update(float deltaTime) {
    state.background->Update(deltaTime);
    
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);
    }
    
    int prevLives = *l1_lives;
    
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);

    
    if ((*l1_lives) < prevLives && (*l1_lives) != 0 ) {
        state.nextScene = 1;
    }
    
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        if (state.enemies[i].isActive == false) { //only for 1 enemy
            state.nextScene = 2;
        }
    }
    
}

void Level1::Render(ShaderProgram *program) {
    state.background->Render(program);
    state.map->Render(program);
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].Render(program);
    }
    state.player->Render(program);

    if (*l1_lives == 0) {
        Util::DrawText(program, loseTextureID, "You Lose", 0.9, 0.0f, glm::vec3(5.5,-4,0));
    }
     
}
