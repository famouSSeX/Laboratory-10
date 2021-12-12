#pragma once
#include<SFML\Graphics.hpp>

namespace mt
{
    class Rectangle
    {
    public:
        Rectangle(int x, int y, float a, float skorost, bool L);

        ~Rectangle();

        sf::RectangleShape* Get();

        int Get_x();

        void Move();
        
        void Set_L(bool L);
        
        bool Get_L();

        void Skorost(float skorost);

        void Move1();
    private:
        int m_x, m_y;
        float m_a;
        sf::RectangleShape* m_shape;
        int m_skorost;
        bool m_L;
    };
}