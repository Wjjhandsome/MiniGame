#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <string>
#include "Chaser-Object.h"
#include "Draw.h"
void must_init(bool test, const char* description)
{
    if (test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

int main()
{
    
    al_init_font_addon();
    al_init_ttf_addon();
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    // ��ʼ������¼�
    if (!al_install_mouse()) {
        std::cerr << "Failed to initialize the mouse!" << std::endl;
        return -1;
    }

    // ��ʼ��ͼ�νӿ�
    if (!al_init_primitives_addon()) {
        std::cerr << "Failed to initialize primitives addon!" << std::endl;
        return -1;
    }

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_DISPLAY* disp = al_create_display(2000, 1500);
    must_init(disp, "display");

    ALLEGRO_FONT* font = al_load_font("E:/code/FirstGame/font/Chinese.ttf", 20 ,0);

    must_init(font, "font");

    must_init(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    bool done = false;
   
    ALLEGRO_EVENT event;

    bool redraw = true;

    float x, y;
    x = 100;
    y = 200;
    int car_x = 1000;
    if (!al_init_image_addon())
    {
        printf("couldn't initialize image addon\n");
        return 1;
    }
    std::vector<int> locsta;
    Car1_load(PhaseLoop::BeforeMainLoop, 0, 0);
    Car2_load(PhaseLoop::BeforeMainLoop, 0, 0);
    station_load(PhaseLoop::BeforeMainLoop, 0 , locsta);
    Door_load(PhaseLoop::BeforeMainLoop, 0, 0);
    Query_load(PhaseLoop::BeforeMainLoop, 0, 0);
    Star_load(PhaseLoop::BeforeMainLoop, 0, 0);
    Congratulation_load(PhaseLoop::BeforeMainLoop, 880, 630);
    // ����λͼ���飨������30֡��
    al_start_timer(timer);
    
    bool running = true;
    
    while (running)
    {
        al_wait_for_event(queue, &event);
        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            // once again, no game logic. fishy? maybe.
            redraw = true;
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            redraw = true;
            break;
        }
        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {

            al_clear_to_color(al_map_rgb(255, 255, 255));
            redraw = false;
            running = game(queue, font);

            // ����һС��ʱ�䣬����֡��
            al_flip_display();
        }
    }
    station_load(PhaseLoop::AfterMainLoop, 0, locsta);
    Car1_load(PhaseLoop::AfterMainLoop,0,0);
    Car2_load(PhaseLoop::AfterMainLoop, 0, 0);
    Congratulation_load(PhaseLoop::AfterMainLoop, 880, 630);
    Query_load(PhaseLoop::AfterMainLoop, 0, 0);
    Star_load(PhaseLoop::AfterMainLoop, 0, 0);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
//�����Ķ�����뼸���Ѿ���ɣ�����һ�������ŵ���Դ
//����ÿһ�صĴ���˼·�ǣ�
//���ȳ�ʼ���ܵ��Լ�����վ��Դ������Ĭ�ϴ��ܵ��������뿪ʼ
//Ȼ�����������Ϊ������Ҫ�����ܹ����������ض�ȡ�û����룬��������ó�����λ��ʱ����Ⱦ����λ��
//���û�����ü��ͷ�����������Ⱦ���򣬵��������
//��ͼ���ź�λ��ˢ���ܲ��ܶ�����
