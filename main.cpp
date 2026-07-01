/*Kadir Alpay - December 2025 - Maze Navigation: Recursively finds ways to complete mazes

Note: The old console code (cout, cin, etc.) has been commented out and replaced by allegro functions, the comments are still in the program by choice

Known Bugs/Refinements:
only works with file name maze.txt
BFS doesn't unmark wrong paths
Both algorithms only works on small mazes as they are highly inefficient, and BFS is worse than DFS
*/

#include "maze.h"

using namespace std;

ALLEGRO_DISPLAY *display;
ALLEGRO_TIMER *timer;
ALLEGRO_FONT *arial;
ALLEGRO_EVENT_QUEUE *event_queue;


int initializeAllegro(int width, int height, const char title[]); //Credit to Mr.Creelman for creating this function

int main()
{
    //initialize the allegro display
    initializeAllegro(1280, 720, "Maze Solver");

    //variables
    Maze maze;
    Coords start;
    int pos = 0; //tracks y-position of text for allegro display
    bool doexit;

    //if file opens
    if (maze.read()){
        //locate start of maze
        start = maze.findStart();

        //if start was not found
        if (start.x == -1){
            //cout << "No start in maze" << endl;
            al_draw_text(arial, al_map_rgb(255, 255, 255), 0, pos += 40, ALLEGRO_ALIGN_LEFT, "No start in maze");
            pos += 40;
            al_flip_display();
        } else {
            //input choice for DFS or BFS
            int choice;
            bool result; //if a solution was found or not
            //cout << "Input 1 for Depth First Search" << endl << "Input 2 for Breadth First Search" << endl << "Input 3 for both" << endl;
            al_draw_text(arial, al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT, "Input 1 for Depth First Search");
            al_draw_text(arial, al_map_rgb(255, 255, 255), 0, pos += 40, ALLEGRO_ALIGN_LEFT, "Input 2 for Breadth First Search");
            al_draw_text(arial, al_map_rgb(255, 255, 255), 0, pos += 40, ALLEGRO_ALIGN_LEFT, "Input 3 for Both DFS and BFS");
            pos += 40;
            al_flip_display();
            //cin >> choice;

            //input valid character choice (credit to Mr. Creelman's Allegro tutorial)
            doexit = false;
            while (!doexit){
                ALLEGRO_EVENT ev;
                al_wait_for_event(event_queue, &ev);

                if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                    doexit = true;
                } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
                    switch(ev.keyboard.keycode){
                        case ALLEGRO_KEY_1:
                            choice = 1;
                            doexit = true;
                            break;
                        case ALLEGRO_KEY_2:
                            choice = 2;
                            doexit = true;
                            break;
                        case ALLEGRO_KEY_3:
                            choice = 3;
                            doexit = true;
                            break;
                    }
                }
            }
            //display users choice
            switch (choice){
                case 1:
                    //solve maze using DFS
                    result = maze.findPathDepth(start.x, start.y);
                    if (result){
                        //cout << endl << "Depth First Search Maze Solution Path:" << endl << endl;
                        al_draw_text(arial, al_map_rgb(255, 255, 255), 0, pos += 40, ALLEGRO_ALIGN_LEFT, "Depth First Search Maze Solution Path:");
                        pos += 40;
                    }
                    break;

                case 2:
                    //solve maze using BFS
                    result = maze.findPathBreadth(start.x, start.y);
                    if (result){
                        //cout << endl << "Breadth First Search Maze Solution Path:" << endl << endl;
                        al_draw_text(arial, al_map_rgb(255, 255, 255), 0, pos += 40, ALLEGRO_ALIGN_LEFT, "Breadth First Search Maze Solution Path:");
                        pos += 40;
                    }
                    break;

                case 3:
                    //solve maze both ways and print both
                    result = maze.findPathDepth(start.x, start.y);
                    if (result){
                        maze.replaceStart(start);
                        //cout << endl << "Depth First Search Maze Solution Path:" << endl << endl;
                        al_draw_text(arial, al_map_rgb(255, 255, 255), 640, pos += 40, ALLEGRO_ALIGN_LEFT, "DFS Maze Solution Path:");
                        pos += 40;
                        maze.print(pos, 640, false);
                    }
                    maze.resetMaze();
                    result = maze.findPathBreadth(start.x, start.y);
                    if (result){
                        //cout << endl << "Breadth First Search Maze Solution Path:" << endl << endl;
                        al_draw_text(arial, al_map_rgb(255, 255, 255), 0, pos -= 40, ALLEGRO_ALIGN_LEFT, "BFS Maze Solution Path:");
                        pos += 40;
                    }
                    break;
            }
            if (result){
                //put the S for start back in its place and print the maze
                maze.replaceStart(start);
                maze.print(pos, 0, true);
            } else {
                //cout << "No solution if i coded this right :(" << endl;
                al_draw_text(arial, al_map_rgb(255, 255, 255), 0, pos += 40, ALLEGRO_ALIGN_LEFT, "No solution if i coded this right :(");
                pos += 40;
                al_flip_display();
            }
        }
    } else {
        //cout << "Couldn't read from the file :(" << endl;
        al_draw_text(arial, al_map_rgb(255, 255, 255), 0, pos += 40, ALLEGRO_ALIGN_LEFT, "Couldn't read from the file :(");
        pos += 40;
        al_flip_display();
    }

    //display legend
    ALLEGRO_BITMAP* img = al_load_bitmap("S.png");
    al_draw_bitmap(img, 0, pos += 40, 0);
    al_draw_text(arial, al_map_rgb(255, 255, 255), 40, pos, ALLEGRO_ALIGN_LEFT, " - Start");
    img = al_load_bitmap("G.png");
    al_draw_bitmap(img, 200, pos, 0);
    al_draw_text(arial, al_map_rgb(255, 255, 255), 240, pos, ALLEGRO_ALIGN_LEFT, " - Goal");
    img = al_load_bitmap("+.png");
    al_draw_bitmap(img, 400, pos, 0);
    al_draw_text(arial, al_map_rgb(255, 255, 255), 440, pos, ALLEGRO_ALIGN_LEFT, " - Path");

    al_draw_text(arial, al_map_rgb(255, 255, 255), 0, pos += 40, ALLEGRO_ALIGN_LEFT, "Press escape key to exit!");
    pos += 40;
    al_flip_display();

    //close game when escape key is pressed
    doexit = false;
    while (!doexit){
    	ALLEGRO_EVENT ev;
      	al_wait_for_event(event_queue, &ev);

      	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        	doexit = true;
      	} else if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
         	if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                doexit = true;
         	}
		}
	}

    return 0;
}

int initializeAllegro(int width, int height, const char title[]) {

    const float FPS = 16;           // set frame rate
    ALLEGRO_COLOR background = al_map_rgb(255, 255, 255);       // make background white.

    // Initialize Allegro
	al_init();

	// initialize display
	display = al_create_display(width, height);
	if (!display) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}
	al_set_window_title(display, title);

   	// Initialize keyboard routines
	if (!al_install_keyboard()) {
	    al_show_native_message_box(display, "Error", "Error", "failed to initialize the keyboard!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
     	return -1;
   	}

	// need to add image processor
 	if (!al_init_image_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize image addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	// 2. setup timer
	timer = al_create_timer(1.0 / FPS);
   	if (!timer) {
   		al_show_native_message_box(display, "Error", "Error", "Failed to create timer!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    // Add fonts


   al_init_font_addon(); // initialize the font addon
   al_init_ttf_addon();// initialize the ttf (True Type Font) addon

   arial = al_load_ttf_font("C:/Windows/Fonts/arial.ttf", 36, 0);
   if (!arial){
      al_show_native_message_box(display, "Error", "Error", "Could not load arial.ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
   }

    // Initialize primative add on
 	if (!al_init_primitives_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	// set up event queue
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
      	return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
 	al_register_event_source(event_queue, al_get_keyboard_event_source());

//l_register_event_source(event_queue, al_get_timer_event_source(timer));	*/		// 3. register timer events

	al_clear_to_color(background);

	al_flip_display();
	al_start_timer(timer);
//	std::cout << "Init return zero " << std::endl;
	return 0;
}
