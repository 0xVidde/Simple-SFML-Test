#include "SFML/Graphics.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Window Title");
    ImGui::SFML::Init(window);

    bool boxExists = true;
    bool followBoxMouse = false;

    static char title[128] = "Window Title";
    int fps = 60;
    sf::Vector2i windowSize = sf::Vector2i(800, 800);

    sf::Vector2f boxSize = sf::Vector2f(100, 100);
    sf::Vector2f boxPos = sf::Vector2f(200, 200);
    float boxAngle = 0;
    float boxOutlineThickness = 0;

    float boxColor[3] = { (float)24 / 255, (float)77 / 255, (float)5 / 255 };
    float boxOutlineColor[3] = { (float)24 / 255, (float)77 / 255, (float)5 / 255 };
    float windowColor[3] = { (float)18 / 255, (float)33 / 255, (float)43 / 255 };

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Box");

        ImGui::Checkbox("Box", &boxExists);
        ImGui::Checkbox("Follow Mouse", &followBoxMouse);
        ImGui::SliderFloat("Box X Size: ", &boxSize.x, 1, windowSize.x);
        ImGui::SliderFloat("Box Y Size: ", &boxSize.y, 1, windowSize.y);
        ImGui::SliderFloat("Box X Position: ", &boxPos.x, 1, windowSize.x);
        ImGui::SliderFloat("Box Y Position: ", &boxPos.y, 1, windowSize.y);
        ImGui::SliderFloat("Box Angle: ", &boxAngle, 0, 360);
        ImGui::SliderFloat("Box Outline Thickness: ", &boxOutlineThickness, -100, 100);
        ImGui::ColorEdit3("Box Color", boxColor);
        ImGui::ColorEdit3("Box Outline Color", boxOutlineColor);


        ImGui::End();

        ImGui::Begin("Window");

        ImGui::InputText("Window Title", title, IM_ARRAYSIZE(title));
        ImGui::SliderInt("Window Framerate", &fps, 1, 120);
        ImGui::ColorEdit3("Background Color", windowColor);
        ImGui::SliderInt("Window X Size", &windowSize.x, 50, 1200);
        ImGui::SliderInt("Window Y Size", &windowSize.y, 50, 1200);

        ImGui::End();

        if (followBoxMouse) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f mouseCoord = window.mapPixelToCoords(mousePosition);

            boxPos = sf::Vector2f(mouseCoord.x - (boxSize.x / 2), mouseCoord.y - (boxSize.y / 2));
        }
        sf::RectangleShape box(boxSize);
        box.setFillColor(sf::Color(204, 77, 5));
        box.setPosition(boxPos);
        box.setRotation(boxAngle);
        box.setFillColor(sf::Color(
            (int)(boxColor[0] * 255),
            (int)(boxColor[1] * 255),
            (int)(boxColor[2] * 255)
        ));
        box.setOrigin(sf::Vector2f((boxSize.x / 2), (boxSize.y / 2)));
        box.setOutlineThickness(boxOutlineThickness);
        box.setOutlineColor(sf::Color(
            (int)(boxOutlineColor[0] * 255),
            (int)(boxOutlineColor[1] * 255),
            (int)(boxOutlineColor[2] * 255)
        ));

        window.clear(sf::Color(
            (int)(windowColor[0] * 255),
            (int)(windowColor[1] * 255),
            (int)(windowColor[2] * 255)
        )); // Color background

        window.setTitle(title);
        window.setSize(sf::Vector2u(windowSize.x, windowSize.y));

        if (boxExists)
            window.draw(box);
        window.setFramerateLimit(fps);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}