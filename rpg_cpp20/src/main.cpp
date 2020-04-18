#include <iostream>
#include <map>

#include <spdlog/spdlog.h>
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <docopt/docopt.h>

static constexpr auto USAGE =
  R"(C++ Weekly Game.

    Usage:
        game [options]

    Options:
        -h --help    Show this screen.
        --width=N    Screen width in pixels [default: 1024].
        --height=N   Screen height in pixels [default: 768].
        --scale=N    Scaling factor [default: 2].
)";

int main(int argc, const char **argv)
{
  std::map<std::string, docopt::value> args = docopt::docopt(
    USAGE, { std::next(argv), std::next(argv, argc) }, true, "Game 0.0");

  const auto width = args["--width"].asLong();
  const auto height = args["--height"].asLong();
  const auto scale = args["--scale"].asLong();

  if (width < 0 || height < 0 || scale < 1 || scale > 5) {
    spdlog::error("Command line options are out of reasonable range.");
    for (auto const &arg : args) {
      if (arg.second.isString()) {
        spdlog::info(
          "Parameter set: {}='{}'", arg.first, arg.second.asString());
      }
    }
    abort();
  }
  // Use the default logger (stdout, multi-threaded, colored)
  sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(width),
                            static_cast<unsigned int>(height)),
    "ImGui + SFML = <3");
  window.setFramerateLimit(60);
  ImGui::SFML::Init(window);

  const auto scale_factor = static_cast<float>(scale);
  ImGui::GetStyle().ScaleAllSizes(scale_factor);
  ImGui::GetIO().FontGlobalScale = scale_factor;

  constexpr std::array steps = { "The Plan",
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
    "Porting From SFML to SDL" };
  std::array<bool, steps.size()> states{ false };

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
    for (size_t index = 0; const auto &step : steps) {
      ImGui::Checkbox(
        fmt::format("{} : {}", index, step).c_str(), &states.at(index));
      index++;
    }
    ImGui::End();

    window.clear();
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();

  return 0;
}
