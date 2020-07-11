#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define WIDTH 700
#define HEIGHT 380

ALLEGRO_DISPLAY *window = NULL;
ALLEGRO_BITMAP *background = NULL;

ALLEGRO_SAMPLE *note_c = NULL;
ALLEGRO_SAMPLE *note_csharp = NULL;
ALLEGRO_SAMPLE *note_d = NULL;
ALLEGRO_SAMPLE *note_dsharp = NULL;
ALLEGRO_SAMPLE *note_e = NULL;
ALLEGRO_SAMPLE *note_f = NULL;

ALLEGRO_EVENT_QUEUE *event_queue = NULL;


void error_msg(char *texto){
    al_show_native_message_box(NULL, "ERROR", "The following error ocurred:", texto, NULL, ALLEGRO_MESSAGEBOX_ERROR);
}

int inicializar(){
    if(! al_init()){
        error_msg("Error while inicializating Allegro");
        return 0;
    }

    window = al_create_display(WIDTH, HEIGHT);
    if(! window){
        error_msg("Error while creating Window");
        return 0;
    }
    al_set_window_title(window, "Piano");

    if(! al_init_acodec_addon()){
        error_msg("Error while inicializating codec addon");
        return 0;
    }

    if(! al_install_audio()){
        error_msg("Error while inicializating audio");
        return 0;
    }

    if(! al_reserve_samples(20)){
        error_msg("Error while reserving samples");
        return 0;
    }

    // audio
    note_c = al_load_sample("resources/note_c.ogg");
    if(! note_c){
        error_msg("Error while loading note c");
        return 0;
    }

    note_csharp = al_load_sample("resources/note_csharp.ogg");
    if(! note_csharp){
        error_msg("Error while loading note c#");
        return 0;
    }

    note_d = al_load_sample("resources/note_d.ogg");
    if(! note_d){
        error_msg("Error while loading note d");
        return 0;
    }

    note_dsharp = al_load_sample("resources/note_dsharp.ogg");
    if(! note_dsharp){
        error_msg("Error while loading note d#");
        return 0;
    }

    note_e = al_load_sample("resources/note_e.ogg");
    if(! note_e){
        error_msg("Error while loading note e");
        return 0;
    }

    if(! al_init_image_addon()){
        error_msg("Error while inicializating image addon");
        return 0;
    }

    background = al_load_bitmap("resources/piano.jpg");
    if(! background){
        error_msg("Error while inicializating loading piano image");
        return 0;
    }

    event_queue = al_create_event_queue();
    if(! event_queue){
        error_msg("Error while inicializating event queue");
        return 0;
    }

    if (! al_install_mouse()){
        error_msg("Error while inicializating mouse");
        return 0;
    }

    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(window));

    al_draw_bitmap(background, 0, 0, 0);
    al_flip_display();
    return 1;
}

int main(){
    char nota;
    int sair = 0;

    if (! inicializar()){
        return -1;
    }
    while (!sair){
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            sair = 1;
        }

        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            if (nota == 'c')
                al_play_sample(note_c, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            else if (nota == 'v')
                al_play_sample(note_csharp, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            else if (nota == 'd')
                al_play_sample(note_d, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            else if (nota == 'b')
                al_play_sample(note_dsharp, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            else if (nota == 'e')
                al_play_sample(note_e, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        }

        else if (event.type = ALLEGRO_EVENT_MOUSE_AXES){
            if (event.mouse.x <= 94 && event.mouse.x >= 15 && event.mouse.y >= 201 && event.mouse.y <= 360
                || event.mouse.x <= 77 && event.mouse.x >= 15 && event.mouse.y <= 201 && event.mouse.y >= 18)
                nota = 'c';
            else if (event.mouse.x <= 129 && event.mouse.x >= 78 && event.mouse.y <= 200 && event.mouse.y >= 15)
                nota = 'v';
            else if (event.mouse.x >= 112 && event.mouse.x <= 191 && event.mouse.y <= 360 && event.mouse.y >= 201
                     || event.mouse.x >= 129 && event.mouse.x <= 174 && event.mouse.y <= 201 && event.mouse.y >= 15)
                nota = 'd';
            else if (event.mouse.x <= 228 && event.mouse.x >= 174 && event.mouse.y <= 200 && event.mouse.y >= 15)
                nota = 'b';
            else if (event.mouse.x >= 211 && event.mouse.x <= 289 && event.mouse.y <= 360 && event.mouse.y >= 201
                     || event.mouse.x >= 227 && event.mouse.x <= 289 && event.mouse.y <= 200 && event.mouse.y >= 15)
                nota = 'e';
            else{
                nota = 'x';
            }
        }

    }

    al_destroy_display(window);
    al_destroy_sample(note_c);
    al_destroy_sample(note_csharp);
    al_destroy_sample(note_d);
    al_destroy_sample(note_dsharp);
    al_destroy_sample(note_e);
    al_destroy_sample(note_f);
    al_destroy_bitmap(background);
    al_destroy_event_queue(event_queue);

    return 0;
}

