#include <iostream>

#include <spdlog/spdlog.h>
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <docopt/docopt.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] const char **argv)
{
  //Use the default logger (stdout, multi-threaded, colored)
  spdlog::info("Starting ImGui + SFML");
  sf::VideoMode mode(1024, 760);
  auto title = "ImGui + SFML = <3";
  sf::RenderWindow window(mode, title);
  window.setFramerateLimit(60);
  ImGui::SFML::Init(window);

  constexpr auto scale_factor = 2.0;
  ImGui::GetStyle().ScaleAllSizes(scale_factor);
  ImGui::GetIO().FontGlobalScale = scale_factor;

  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  std::array<bool, 11> states{ false };

  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    // By doing this ImGui knows how much time has elapsed.
    ImGui::SFML::Update(window, deltaClock.restart());

    ImGui::Begin("The Plan");
    ImGui::Checkbox("0 : The Plan", &states[0]);
    ImGui::Checkbox("1 : Getting Started", &states[1]);
    ImGui::Checkbox("2 : C++ 20 So Far", &states[2]);
    ImGui::Checkbox("3 : Reading SFML Input States", &states[3]);
    ImGui::Checkbox("4 : Managing Game State", &states[4]);
    ImGui::Checkbox("5 : Making Our Game Testable", &states[5]);
    ImGui::Checkbox("6 : Making Game State Allocator Aware", &states[6]);
    ImGui::Checkbox("7 : Add Logging To Game Engine", &states[7]);
    ImGui::Checkbox("8 : Draw a Game Map", &states[8]);
    ImGui::Checkbox("9 : Dialog Trees", &states[9]);
    ImGui::Checkbox("10: Poritng From SFML to SDL", &states[10]);
    ImGui::End();

    window.clear();
    window.draw(shape);
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();

  return 0;
}
