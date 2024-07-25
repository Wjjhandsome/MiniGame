#include "Draw.h"
#include <iostream>
InputBox::InputBox(float x1, float y1, float x2, float y2, ALLEGRO_FONT* font, const std::string& prompt, int mod)
    : x1(x1), y1(y1), x2(x2), y2(y2), text(""), prompt(prompt), active(false), font(font), model(mod), loc(0), plan(0), yes{false} {}
void InputBox::draw() {
    // 绘制输入框
    al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(255, 0, 0), 2);
    al_draw_text(font, al_map_rgb(255, 255, 255), x1 + 10, y1 + 10, 0, prompt.c_str());
    al_draw_text(font, al_map_rgb(255, 255, 255), x1 + 10, y1 + 30, 0, text.c_str());
    // 如果输入框处于激活状态，则高亮显示（例如用不同颜色边框）
    if (active) {
        al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(0, 0, 255), 2);
    }
    if (yes) 
    {
        al_draw_circle(x2 + 30, y1 + (y2 - y1) / 2, 20, al_map_rgb(0, 255, 0), 10);
    }
}
void InputBox::handle_event(const ALLEGRO_EVENT& ev) {
    if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        // 检查鼠标是否点击在输入框内
        if (ev.mouse.x >= x1 && ev.mouse.x <= x2 && ev.mouse.y >= y1 && ev.mouse.y <= y2) {
            active = true;
        }
        else {
            active = false;
        }
    }
    else if (ev.type == ALLEGRO_EVENT_KEY_CHAR && active) {
        // 处理键盘输入
        if (isdigit(ev.keyboard.unichar) || ev.keyboard.keycode == 72) {
            text += (char)ev.keyboard.unichar;
        }
        else if (ev.keyboard.unichar == ',')
        {
            text += (char)ev.keyboard.unichar;
        }
        else if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && text.length() > 0) {
            text.pop_back();
        }
    }
    else if (ev.type == ALLEGRO_EVENT_KEY_DOWN && active) {
        // 确认输入
        
        switch (model)
        {
        case 0:
            if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                yes = true;
                // 验证输入是否为整数
                    loc = std::stoi(text);
                    std::cout << loc << std::endl;
                    text = "";
            }
            break;
        case 1:
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                yes = true;
                std::vector<int> res;
                Stringsplit(text, ',', res);
                plan.clear();
                for (size_t i = 0; i < res.size(); i++)
                {
                    plan.emplace_back(res[i]);
                }
            }
        }
        break;
        default:
            break;
        }
    }
}
bool InputBox::is_valid_integer(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}
void InputBox::Stringsplit(const std::string& str, const char split, std::vector<int>& res)
{
    if (str == "")		return;
    //在字符串末尾也加入分隔符，方便截取最后一段
    std::string strs = str + split;
    size_t pos = strs.find(split);
    // 若找不到内容则字符串搜索函数返回 npos
    while (pos != strs.npos)
    {
        std::string temp = strs.substr(0, pos);
        int a = std::stoi(temp);
        res.push_back(a);
        //去掉已分割的字符串,在剩下的字符串中进行分割
        strs = strs.substr(pos + 1, strs.size());
        pos = strs.find(split);
    }
}

LevelButton::LevelButton(float x1, float y1, float x2, float y2, ALLEGRO_FONT* font, const std::string& prompt, const std::string& title)
    : x1(x1), y1(y1), x2(x2), y2(y2), title(title), prompt(prompt), active(false), font(font), click(false) 
{
}

void LevelButton::draw()
{
    al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(0, 255, 0));
    al_draw_text(font, al_map_rgb(0, 0, 255), x1 + 10, y1 + 30, 0, prompt.c_str());
    al_draw_text(font, al_map_rgb(0, 0, 255), x1 + 10, y1 + 10, 0, title.c_str());
    // 如果输入框处于激活状态，则高亮显示（例如用不同颜色边框）
    if (active) {
        al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(0, 0, 255), 2);
    }
}

void LevelButton::handle_event(const ALLEGRO_EVENT& ev)
{
    if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
        // 检查鼠标是否点击在输入框内
        if (ev.mouse.x >= x1 && ev.mouse.x <= x2 && ev.mouse.y >= y1 && ev.mouse.y <= y2) {
            active = true;
        }
        else {
            active = false;
        }
    }
    else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && active) {
        // 处理鼠标输入
        if (ev.mouse.x >= x1 && ev.mouse.x <= x2 && ev.mouse.y >= y1 && ev.mouse.y <= y2) {
            click = true;
        }
    }
}
