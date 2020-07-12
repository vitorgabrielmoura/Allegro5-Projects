#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

ALLEGRO_DISPLAY *window = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_BITMAP *icon = NULL;
ALLEGRO_BITMAP *wallpaper = NULL;
ALLEGRO_BITMAP *image = NULL;
ALLEGRO_BITMAP *xis = NULL;
ALLEGRO_BITMAP *circulo = NULL;
ALLEGRO_BITMAP *simbolo = NULL;
ALLEGRO_FONT *font = NULL;
ALLEGRO_FONT *font2 = NULL;
ALLEGRO_FONT *font3 = NULL;
ALLEGRO_FONT *font4 = NULL;

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

    font = al_load_font("resources/rainbow.ttf", 67, 0);
    if (! font){
        error_msg("Error while creating font");
        al_destroy_display(window);
        return 0;
    }

    font2 = al_load_font("resources/rainbow.ttf", 50, 0);
    if (! font2){
        error_msg("Error while creating font");
        al_destroy_display(window);
        return 0;
    }

    font3 = al_load_font("resources/arial.ttf", 50, 0);
    if (! font3){
        error_msg("Error while creating font");
        al_destroy_display(window);
        return 0;
    }

    font4 = al_load_font("resources/rainbow.ttf", 20, 0);
    if (! font4){
        error_msg("Error while creating font");
        al_destroy_display(window);
        return 0;
    }


    al_register_event_source(event_queue, al_get_display_event_source(window));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    wallpaper = al_load_bitmap("resources/wallpaper.jpg");
    image = al_load_bitmap("resources/tabela.png");
    xis = al_load_bitmap("resources/xis.png");
    circulo = al_load_bitmap("resources/circulo.png");
    icon = al_load_bitmap("resources/icon.png");

    al_set_display_icon(window, icon);

    al_draw_bitmap(wallpaper, 0, 0, 0);
    //al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_text(font, al_map_rgb(0,0,0), WIDTH/7.8, 10, 0, "Jogo da Velha");
    al_draw_text(font2, al_map_rgb(0,0,0), 590, 170, 0, "Versus");
    al_draw_text(font4, al_map_rgb(0,0,0), 535, 500, 0, "Jogo desenvolvido para apresentacao");
    al_draw_text(font4, al_map_rgb(0,0,0), 535, 520, 0, "na disciplina Algoritmos e Logica");
    al_draw_text(font4, al_map_rgb(0,0,0), 535, 540, 0, "           de programacao");

    al_draw_text(font3, al_map_rgb(0,128,0), 630, 230, 0, "0");
    al_draw_text(font3, al_map_rgb(0,0,0), 630, 235, 0, "_");
    al_draw_text(font3, al_map_rgb(128,0,0), 630, 290, 0, "0");

    al_draw_bitmap(image, 0, 80, 0);
    al_flip_display();

    return 1;
}

int verificajogo(int tabela [][3], int jog){
    int l, c, draw=0;

	// verifica as linhas
	if (tabela[0][0] == jog && tabela[0][1] == jog && tabela[0][2] == jog){
		return jog;}
	else if (tabela[1][0] == jog && tabela[1][1] == jog && tabela[1][2] == jog){
		return jog;}
	else if (tabela[2][0] == jog && tabela[2][1] == jog && tabela[2][2] == jog){
		return jog;}

	// verifica as colunas
	if (tabela[0][0] == jog && tabela[1][0] == jog && tabela[2][0] == jog){
		return jog;}
	else if (tabela[0][1] == jog && tabela[1][1] == jog && tabela[2][1] == jog){
		return jog;}
	else if (tabela[0][2] == jog && tabela[1][2] == jog && tabela[2][2] == jog){
		return jog;}

	// verifica as diagonais
	if (tabela[0][0] == jog && tabela[1][1] == jog && tabela[2][2] == jog){
		return jog;}
	else if (tabela[0][2] == jog && tabela[1][1] == jog && tabela[2][0] == jog){
		return jog;}

    for(l=0; l < 3; l++){
        for(c=0; c < 3; c++){
            if (tabela[l][c] != 0){
                draw += 1;
            }
        }
    }
    if (draw == 9)
        return 3;

	return 0;
}

int main(){
    char cwinner1[5], cwinner2[5];
    int i,jog, coluna, linha, sair=0, winner, resp, winner1=0, winner2=0;
	int tabela[3][3] = {{0, 0, 0},
							  {0, 0, 0},
							  {0, 0, 0}
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
            else if (event.mouse.x >= 362 && event.mouse.x <= 512)
                coluna = 2;
            else
                coluna = 666;

            if (event.mouse.y <= 230 && event.mouse.y >= 65)
                linha = 0;
            else if (event.mouse.y >= 262 && event.mouse.y <= 410)
                linha = 1;
            else if (event.mouse.y >= 442 && event.mouse.x <= 512)
                linha = 2;
            else
                linha = 666;

            }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            jog = 2;
            if (i % 2 == 0)
                jog = 1;

            simbolo = xis;
            if (jog == 1)
                    simbolo = circulo;
            if (tabela[linha][coluna] == 0){
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
            winner = verificajogo(tabela, jog);
            if (winner){
                if (winner == 3){
                    resp = al_show_native_message_box(window, "FIM", "O Jogo Acabou! Temos um empate!", "Deseja jogar novamente?", NULL, ALLEGRO_MESSAGEBOX_YES_NO);

                    }
                    else{
                        resp = al_show_native_message_box(window, "FIM", "O jogo acabou! Temos um vencedor!", "Deseja jogar novamente?", NULL, ALLEGRO_MESSAGEBOX_YES_NO);
                    }
                if (resp){
                    int l, c;

                    for(l=0; l < 3; l++){
                        for(c=0; c < 3; c++){
                            tabela[l][c] = 0;
                        }
                    }
                    al_draw_bitmap(wallpaper, 0, 0, 0);
                    al_draw_text(font, al_map_rgb(0,0,0), WIDTH/7.8, 10, 0, "Jogo da Velha");
                    al_draw_text(font2, al_map_rgb(0,0,0), 590, 170, 0, "Versus");
                    al_draw_bitmap(image, 0, 80, 0);

                    if (winner == 1)
                        winner1 += 1;
                    else if (winner == 2)
                        winner2 += 1;

                    itoa(winner1, cwinner1, 10);
                    itoa(winner2, cwinner2, 10);

                    al_draw_text(font3, al_map_rgb(0,128,0), 630, 230, 0, cwinner1);
                    al_draw_text(font3, al_map_rgb(0,0,0), 630, 235, 0, "_");
                    al_draw_text(font3, al_map_rgb(128,0,0), 630, 290, 0, cwinner2);

                    al_draw_text(font4, al_map_rgb(0,0,0), 535, 500, 0, "Jogo desenvolvido para apresentacao");
                    al_draw_text(font4, al_map_rgb(0,0,0), 535, 520, 0, "na disciplina Algoritmos e Logica");
                    al_draw_text(font4, al_map_rgb(0,0,0), 535, 540, 0, "           de programacao");

                    winner = 0;
                }
            al_flip_display();
            }
        }
    }


    return 0;
}

