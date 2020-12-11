#include "Menu.h"

GLuint fontTextureID;

void Menu::Initialize() {
    
    state.nextScene = -1;
    state.mode = MAIN_MENU;
    state.background = new Background();
    
    fontTextureID = Util::LoadTexture("pixel_font.png");
    state.background->textureID = Util::LoadTexture("green_bg.png");
    //state.background->position = glm::vec3(7, -1, 0);
    //state.background->scale = glm::vec3(10.0f, 10.0f, 10.0f);
    
}

void Menu::Update(float deltaTime) {
    state.background->Update(deltaTime);
}

void Menu::Render(ShaderProgram *program) {
    
    state.background->Render(program);
    
    Util::DrawText(program, fontTextureID, "Ring of the", 0.9, -0.1f, glm::vec3(-4,1.5,0));
    Util::DrawText(program, fontTextureID, " Mad King", 0.9, 0.0f, glm::vec3(-4,0.3,0));
    
    Util::DrawText(program, fontTextureID, "Press ENTER to start", 0.2, 0.0f, glm::vec3(-1.9,-1,0));
    Util::DrawText(program, fontTextureID, "Instructions:", 0.2, 0.0f, glm::vec3(-1.3,-2,0));
    Util::DrawText(program, fontTextureID, "E to interact", 0.2, 0.0f, glm::vec3(-1.3,-2.5,0));
    Util::DrawText(program, fontTextureID, "SPACE to attack", 0.2, 0.0f, glm::vec3(-1.5,-2.8,0));


}
