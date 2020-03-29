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
  // Use the default logger (stdout, multi-threaded, colored)
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

  std::array<bool, 13> states{ false };

  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed) { window.close(); }
    }

    // By doing this ImGui knows how much time has elapsed.
    ImGui::SFML::Update(window, deltaClock.restart());
    ImGui::Begin("The Plan");
    int index = 0;
    for (const auto &step : { "The Plan",
           "Getting Started",
           "Finding Errors as Soon as Possible",
           "Handling Command Line Parameters",
           "C++ 20 So Far",
           "Reading SFML Input States",
           "Managing Game State",
           "Making Our Game Testable",
           "Making Game State Allocator Aware",
           "Add Logging To Game Engine",
           "Draw a Game Map",
           "Dialog Trees",
           "Porting From SFML to SDL" }) {
      ImGui::Checkbox(fmt::format("{} : {}", index, step).c_str(),
        std::next(std::begin(states), index));
      index++;
    }
    ImGui::End();

    window.clear();
    window.draw(shape);
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();

  return 0;
}
