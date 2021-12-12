#include <Rectangle.hpp>

namespace mt
{
    
        Rectangle::Rectangle(int x, int y, float a, float skorost, bool L)
        {
            m_L = L;
            m_skorost = skorost;
            m_a = a;
            m_x = x;
            m_y = y;
            m_shape = new sf::RectangleShape(sf::Vector2f(m_a, m_a));
            m_shape->setOrigin(m_a / 2, m_a / 2);
            m_shape->setFillColor(sf::Color::White);
            m_shape->setPosition(m_x, m_y);
           
        }


        Rectangle::~Rectangle()
        {
            delete m_shape;
        }

        sf::RectangleShape* Rectangle::Get()
        {
            return m_shape;
        }

        int Rectangle::Get_x()
        {
            return m_x;
        }

        void Rectangle::Move()
        {
            m_x -= m_skorost;
            m_shape->setPosition(m_x, m_y);
        }

        void Rectangle::Set_L(bool L)
        {
            m_L = L;
        }

        bool Rectangle::Get_L()
        {
            return m_L;
        }

        void Rectangle::Skorost(float skorost)
        {
            m_skorost = skorost;
        }
        void Rectangle::Move1()
        {
            m_x += m_skorost;
            m_shape->setPosition(m_x, m_y);
        }

}