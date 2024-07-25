#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <string>

class InputBox {
public:
    float x1, y1, x2, y2;
    std::string text;
    std::string prompt;
    bool active;
    ALLEGRO_FONT* font;
    int model;
    std::vector<int> plan;
    int loc;
    bool yes;
    InputBox(float x1, float y1, float x2, float y2, ALLEGRO_FONT* font, const std::string& prompt, int mod);
    void draw();
    void handle_event(const ALLEGRO_EVENT& ev);
private:
    bool is_valid_integer(const std::string& str);

    void Stringsplit(const std::string& str, const char split, std::vector<int>& res);
};
class LevelButton 
{
public:
    float x1, y1, x2, y2;
    std::string title;
    std::string prompt;
    bool active;
    ALLEGRO_FONT* font;
    bool click;
    LevelButton(float x1, float y1, float x2, float y2, ALLEGRO_FONT* font, const std::string& prompt, const std::string& title);
    void draw();

    void handle_event(const ALLEGRO_EVENT& ev);


};

