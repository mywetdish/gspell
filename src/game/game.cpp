#include "game.h"

#include "../renderer/shader_program.h"
#include "../renderer/texture2d.h"
#include "../renderer/sprite.h"
#include "../renderer/animated_sprite.h"
#include "../resources/resource_manager.h"

#include "character.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

Game::Game(const glm::ivec2& windowSize) : m_eCurrentGameState(EGameState::Active), m_windowSize(windowSize) 
{
	m_keys.fill(false);
}
Game::~Game()
{

}

void Game::render()
{
    //ResourceManager::getAnimatedSprite("NewAnimatedSprite")->render();
    
    if (m_pChar) {
        m_pChar->render();
    }
}
void Game::update(const uint64_t delta)
{
	//ResourceManager::getAnimatedSprite("NewAnimatedSprite")->update(delta);
        
    if (m_pChar) {
        if (m_keys[GLFW_KEY_W]) {
            m_pChar->setOrientation(Character::EOrientation::Up);
            m_pChar->move(true);
        } else if (m_keys[GLFW_KEY_A]) {
            m_pChar->setOrientation(Character::EOrientation::Left);
            m_pChar->move(true);
        } else if (m_keys[GLFW_KEY_S]) {
            m_pChar->setOrientation(Character::EOrientation::Down);
            m_pChar->move(true);
        } else if (m_keys[GLFW_KEY_D]) {
            m_pChar->setOrientation(Character::EOrientation::Right);
            m_pChar->move(true);
        } else {
            m_pChar->move(false);
        }
        m_pChar->update(delta);
    }

}
void Game::setKey(const int key, const int action)
{
	m_keys[key] = action;
}
bool Game::init()
{
    auto pSpriteShaderProgram = ResourceManager::loadShaders("SpriteShader", "res/shaders/vSprite.txt", "res/shaders/fSprite.txt");
    if (!pSpriteShaderProgram)
    {
        std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
        return false;
    }
 	std::vector<std::string> subTextureNames = {"Asphalt", 
                                                "Grass", 
                                                "AsHole", 
                                                "FlGrass", 
                                                "FlDirt", 
                                                "Dirt", 
                                                "DiHole", 
                                                "Gravel", 
                                                "AsLU", 
                                                "AsU", 
                                                "AsRU", 
                                                "FenceL", 
                                                "Fence", 
                                                "FenceR"};
    auto pTextureAtlas = ResourceManager::loadTextureAtlas("DefaultTextureAtlas", "res/textures/myOverworld.png", std::move(subTextureNames),16,16);
 	auto pAnimatedSprite = ResourceManager::loadAnimatedSprite("NewAnimatedSprite", "DefaultTextureAtlas", "SpriteShader", 100, 100, "FlGrass");
    pAnimatedSprite->setPosition(glm::vec2(100,100));

    std::vector<std::pair<std::string, uint64_t>> flowerState;

    flowerState.emplace_back(std::make_pair <std::string, uint64_t>("FlGrass", 1000000000));
    flowerState.emplace_back(std::make_pair <std::string, uint64_t>("FlDirt", 1000000000));
    flowerState.emplace_back(std::make_pair <std::string, uint64_t>("Dirt", 1000000000));

 	pAnimatedSprite->insertState("flowerState", std::move(flowerState));
 	pAnimatedSprite->setState("flowerState");
 	glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);
    
    pSpriteShaderProgram->use();
    pSpriteShaderProgram->setMatrix4("projectionMat",projectionMatrix);
    
    std::vector<std::string> subCharTextureNames = {"charDown1",
                                                    "charDown2",
                                                    "charDown3",
                                                    "charDown4",
                                                    "charRight1",
                                                    "charRight2",
                                                    "charRight3",
                                                    "charRight4",
                                                    "charUp1",
                                                    "charUp2",
                                                    "charUp3",
                                                    "charUp4",
                                                    "charLeft1",
                                                    "charLeft2",
                                                    "charLeft3",
                                                    "charLeft4"};
    
    auto pCharTextureAtlas = ResourceManager::loadTextureAtlas("CharacterTextureAtlas", "res/textures/myCharacter.png", std::move(subCharTextureNames), 16, 23);
    auto pCharAnimatedSprite = ResourceManager::loadAnimatedSprite("CharacterAnimatedSprite", "CharacterTextureAtlas", "SpriteShader", 80, 115, "charDown1");
    
    std::vector<std::pair<std::string, uint64_t>> charDownState;

    charDownState.emplace_back(std::make_pair <std::string, uint64_t>("charDown1", 130000000));
    charDownState.emplace_back(std::make_pair <std::string, uint64_t>("charDown2", 130000000));
    charDownState.emplace_back(std::make_pair <std::string, uint64_t>("charDown3", 130000000));
    charDownState.emplace_back(std::make_pair <std::string, uint64_t>("charDown4", 130000000));
    
    std::vector<std::pair<std::string, uint64_t>> charRightState;

    charRightState.emplace_back(std::make_pair <std::string, uint64_t>("charRight1", 130000000));
    charRightState.emplace_back(std::make_pair <std::string, uint64_t>("charRight2", 130000000));
    charRightState.emplace_back(std::make_pair <std::string, uint64_t>("charRight3", 130000000));
    charRightState.emplace_back(std::make_pair <std::string, uint64_t>("charRight4", 130000000));
    
    std::vector<std::pair<std::string, uint64_t>> charUpState;

    charUpState.emplace_back(std::make_pair <std::string, uint64_t>("charUp1", 130000000));
    charUpState.emplace_back(std::make_pair <std::string, uint64_t>("charUp2", 130000000));
    charUpState.emplace_back(std::make_pair <std::string, uint64_t>("charUp3", 130000000));
    charUpState.emplace_back(std::make_pair <std::string, uint64_t>("charUp4", 130000000));
    
    std::vector<std::pair<std::string, uint64_t>> charLeftState;

    charLeftState.emplace_back(std::make_pair <std::string, uint64_t>("charLeft1", 130000000));
    charLeftState.emplace_back(std::make_pair <std::string, uint64_t>("charLeft2", 130000000));
    charLeftState.emplace_back(std::make_pair <std::string, uint64_t>("charLeft3", 130000000));
    charLeftState.emplace_back(std::make_pair <std::string, uint64_t>("charLeft4", 130000000));
    
    pCharAnimatedSprite->insertState("charDownState",   std::move(charDownState));
    pCharAnimatedSprite->insertState("charRightState",  std::move(charRightState));
    pCharAnimatedSprite->insertState("charUpState",     std::move(charUpState));
    pCharAnimatedSprite->insertState("charLeftState",   std::move(charLeftState));
    
    pCharAnimatedSprite->setState("charLeftState");
    
    m_pChar = std::make_unique<Character>(pCharAnimatedSprite,0.0000001f,glm::vec2(100.f,100.f));
    
    return true;
}
