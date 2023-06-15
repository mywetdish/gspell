#include "character.h"
#include "../renderer/animated_sprite.h"

Character::Character(std::shared_ptr<Renderer::AnimatedSprite> pSprite, const float velocity, const glm::vec2& position)
              : m_eOrientation(EOrientation::Down),
                m_pSprite(std::move(pSprite)),
                m_move(false),
                m_velocity(velocity),
                m_position(position),
                m_moveOffset(glm::vec2(0.f,1.f))
{
    m_pSprite->setPosition(m_position);
} 

void Character::render() const
{
    m_pSprite->render();
}
void Character::setOrientation(const Character::EOrientation eOrientation)
{
    if (m_eOrientation == eOrientation)
    {
        return;
    }
    
    m_eOrientation = eOrientation;
    switch (m_eOrientation) {
        case Character::EOrientation::Up:
            m_pSprite->setState("charUpState");
            m_moveOffset.x = 0.f;
            m_moveOffset.y = 1.f;
            break;
        case Character::EOrientation::Down:
            m_pSprite->setState("charDownState");
            m_moveOffset.x = 0.f;
            m_moveOffset.y = -1.f;
            break;
        case Character::EOrientation::Left:
            m_pSprite->setState("charLeftState");
            m_moveOffset.x = -1.f;
            m_moveOffset.y = 0.f;
            break;
        case Character::EOrientation::Right:
            m_pSprite->setState("charRightState");
            m_moveOffset.x = 1.f;
            m_moveOffset.y = 0.f;
            break;
        default:
            break;
    }
}
void Character::move(const bool move)
{
    m_move = move;
}
void Character::update(const uint64_t delta)
{
    if (m_move)
    {
        m_position += delta * m_velocity * m_moveOffset;
        m_pSprite->setPosition(m_position);
        m_pSprite->update(delta);
    }
    
}
