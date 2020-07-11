#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

#define WIDTH 512
#define HEIGHT 600

ALLEGRO_DISPLAY *window = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_BITMAP *image = NULL;
ALLEGRO_BITMAP *xis = NULL;
ALLEGRO_BITMAP *circulo = NULL;
ALLEGRO_BITMAP *simbolo = NULL;
ALLEGRO_FONT *font = NULL;

void error_msg(char *text){
    al_show_native_message_box(NULL, "ERROR", "The following error ocurred:", text, NULL, ALLEGRO_MESSAGEBOX_ERROR);
}

int inicializate(){
    if (! al_init()){
        error_msg("Error while inicializating Allegro");
        return 0;
    }

    window = al_create_display(WIDTH, HEIGHT);
    if(!window) {
        error_msg("Error creating window");
        return 0;
    }
    al_set_window_title(window, "Jogo da Velha");

    event_queue = al_create_event_queue();
    if(!event_queue) {
        error_msg("Error while creating event queue");
        al_destroy_display(window);
        return 0;
    }

    if (! al_install_mouse()){
        error_msg("Error while installing mouse");
        return 0;
    }
    al_set_system_mouse_cursor(window, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    font = al_load_font("resources/rainbow.ttf", 50, 0);
    if (! font){
        error_msg("Error while creating font");
        al_destroy_display(window);
        return 0;
    }


    al_register_event_source(event_queue, al_get_display_event_source(window));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    image = al_load_bitmap("resources/tabela.png");
    xis = al_load_bitmap("resources/xis.png");
    circulo = al_load_bitmap("resources/circulo.png");

    al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_text(font, al_map_rgb(0,0,0), WIDTH/4, 10, 0, "Jogo da Velha");
    al_draw_bitmap(image, 0, 80, 0);
    al_flip_display();

    return 1;
}

int verificajogo(char tabela [][3], int jog){
	// verifica as linhas
	if (tabela[0][0] == jog && tabela[0][1] == jog && tabela[0][2] == jog){
		return 1;}
	else if (tabela[1][0] == jog && tabela[1][1] == jog && tabela[1][2] == jog){
		return 1;}
	else if (tabela[2][0] == jog && tabela[2][1] == jog && tabela[2][2] == jog){
		return 1;}

	// verifica as colunas
	if (tabela[0][0] == jog && tabela[1][0] == jog && tabela[2][0] == jog){
		return 1;}
	else if (tabela[0][1] == jog && tabela[1][1] == jog && tabela[2][1] == jog){
		return 1;}
	else if (tabela[0][2] == jog && tabela[1][2] == jog && tabela[2][2] == jog){
		return 1;}

	// verifica as diagonais
	if (tabela[0][0] == jog && tabela[1][1] == jog && tabela[2][2] == jog){
		return 1;}
	else if (tabela[0][2] == jog && tabela[1][1] == jog && tabela[2][0] == jog){
		return 1;}

	return 0;
};

int main(){
    int i,jog, coluna, linha, status1, status2, winner=1, sair=0;
	int tabela[3][3] = {{5, 5, 5},
							  {5, 5, 5},
							  {5, 5, 5}
							  };

    if (! inicializate()){
        return -1;
    }

    while (! sair){
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sair = 1;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_AXES){
            if (event.mouse.x <= 150)
                coluna = 0;
            else if (event.mouse.x >= 182 && event.mouse.x <= 330)
                coluna = 1;
            else if (event.mouse.x >= 362)
                coluna = 2;
            else
                coluna = 666;

            if (event.mouse.y <= 230 && event.mouse.y >= 65)
                linha = 0;
            else if (event.mouse.y >= 262 && event.mouse.y <= 410)
                linha = 1;
            else if (event.mouse.y >= 442)
                linha = 2;
            else
                linha = 666;

            }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            jog = 2;
            if (i % 2 == 0)
			jog = 1;

			printf("\n\nCOLUNA %d - LINHA %d", coluna, linha);

            simbolo = xis;
            if (jog == 1)
                    simbolo = circulo;
            if (tabela[linha][coluna] == 5){
                if (coluna == 0){
                    if (linha == 0){
                       al_draw_bitmap(simbolo, 20,100,0);
                        tabela[linha][coluna] = jog;
                    }
                    else if (linha == 1){
                        al_draw_bitmap(simbolo, 20,280,0);
                        tabela[linha][coluna] = jog;
                    }
                    else if (linha == 2){
                        al_draw_bitmap(simbolo, 20,460,0);
                        tabela[linha][coluna] = jog;
                    }
                }
                else if (coluna == 1){
                    if (linha == 0){
                       al_draw_bitmap(simbolo, 200,100,0);
                        tabela[linha][coluna] = jog;
                    }
                    else if (linha == 1){
                        al_draw_bitmap(simbolo, 200,280,0);
                        tabela[linha][coluna] = jog;
                    }
                    else if (linha == 2){
                        al_draw_bitmap(simbolo, 200,460,0);
                        tabela[linha][coluna] = jog;
                    }
            }
            else if (coluna == 2){
                    if (linha == 0){
                       al_draw_bitmap(simbolo, 380,100,0);
                        tabela[linha][coluna] = jog;
                    }
                    else if (linha == 1){
                        al_draw_bitmap(simbolo, 380,280,0);
                        tabela[linha][coluna] = jog;
                    }
                    else if (linha == 2){
                        al_draw_bitmap(simbolo, 380,460,0);
                        tabela[linha][coluna] = jog;
                    }
            }
            i++;
            }

            al_flip_display();
        }
        printf("\n%d", verificajogo(tabela, 1));
    }


    return 0;
}

