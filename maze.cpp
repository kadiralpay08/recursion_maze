#include "maze.h"

Maze::Maze(){   //default constructor
    start_row = 0;
    start_col = 0;
}

Maze::Maze(int r, int c){   //constructor with set start
    start_row = r;
    start_col = c;
}

bool Maze::read(){  //reads a maze from text file
    ifstream inFile("maze.txt");
    //check if file opened before reading in values
    if (!inFile.is_open()){
        return false;
    } else {
        //read in maze dimensions
        inFile >> maze_rows;
        inFile >> maze_cols;
        maze.resize(maze_rows, vector<char>(maze_cols)); //chatgpt helped me find this error, you have to resize vectors for them to be dynamic

        //read in maze from file
        for (int i = 0; i < maze_rows; i++){
            for (int j = 0; j < maze_cols; j++){
                inFile >> maze[i][j];
            }
        }
    }
    //copy maze into maze solution matrix
    mazeSolution = maze;
    inFile.close();
    return true;
}

Coords Maze::findStart(){   //find start of maze
    Coords start;
    start.x = -1;
    start.y = -1;
    for (int i = 0; i < maze_rows; i++){
        for (int j = 0; j < maze_cols; j++){
            if (maze[i][j] == 'S'){
                start.x = i;
                start.y = j;
                return start;
            }
        }
    }
    //returns -1 -1 if no start found
    return start;
}

bool Maze::findPathDepth(int r, int c){  //recursive solver, that starts at position (r,c) and tries to find 'G' in maze

    //bound check
    if ((r < 0 || r >= maze_rows) || (c < 0 || c >= maze_cols)){
        return false;
    }

    //goal check
    if (mazeSolution[r][c] == 'G'){
        return true;
    }

    //valid move check
    if (mazeSolution[r][c] == '#' || mazeSolution[r][c] == '+' || mazeSolution[r][c] == 'x'){ //forgot to do the x check so used chatgpt to debug (spent hours trying and couldnt find it :(
        return false;
    }

    //mark as part of solution path
    mazeSolution[r][c] = '+';

    //North
    if (findPathDepth(r - 1, c) == true){
        return true;
    }

    //East
    if (findPathDepth(r, c + 1) == true){
        return true;
    }

    //South
    if (findPathDepth(r + 1, c) == true){
        return true;
    }

    //West
    if (findPathDepth(r, c - 1) == true){
        return true;
    }

    //unmark as part of solution path
    mazeSolution[r][c] = 'x';

    return false;
}

bool Maze::findPathBreadth(int r, int c){ //breadth first search
    //variables
    Q q;
    Coords temp;

    temp.x = r;
    temp.y = c;
    q.enqueue(temp);
    mazeSolution[r][c] = '+';

    //while queue isnt empty
    while (!q.isEmpty()){
        //dequeue item then check around it
        temp = q.dequeue();
        r = temp.x;
        c = temp.y;

        //North
        if ((r - 1 >= 0) && (mazeSolution[r - 1][c] != '#' && mazeSolution[r - 1][c] != '+' && mazeSolution[r - 1][c] != 'x')){
            if (maze[r - 1][c] == 'G'){
                return true;
            }

            //mark as part of solution path and add to queue
            mazeSolution[r - 1][c] = '+';
            temp.x = r - 1;
            temp.y = c;
            q.enqueue(temp);
        }

        //East
        if ((c + 1 < maze_cols) && (mazeSolution[r][c + 1] != '#' && mazeSolution[r][c + 1] != '+' && mazeSolution[r][c + 1] != 'x')){
            if (mazeSolution[r][c + 1] == 'G'){
                return true;
            }

            //mark as part of solution path and add to queue
            mazeSolution[r][c + 1] = '+';
            temp.x = r;
            temp.y = c + 1;
            q.enqueue(temp);
        }

        //South
        if ((r + 1 < maze_rows) && (mazeSolution[r + 1][c] != '#' && mazeSolution[r + 1][c] != '+' && mazeSolution[r + 1][c] != 'x')){
            if (mazeSolution[r + 1][c] == 'G'){
                return true;
            }

            //mark as part of solution path and add to queue
            mazeSolution[r + 1][c] = '+';
            temp.x = r + 1;
            temp.y = c;
            q.enqueue(temp);
        }

        //West
        if ((c - 1 >= 0) && (mazeSolution[r][c - 1] != '#' && mazeSolution[r][c - 1] != '+' && mazeSolution[r][c - 1] != 'x')){
            if (mazeSolution[r][c - 1] == 'G'){
                return true;
            }

            //mark as part of solution path and add to queue
            mazeSolution[r][c - 1] = '+';
            temp.x = r;
            temp.y = c - 1;
            q.enqueue(temp);
        }
    }

    return false;
}

void Maze::replaceStart(Coords start){  //replace start S after findPathDepth
    mazeSolution[start.x][start.y] = 'S';
}

void Maze::print(int &pos, int Xpos, bool affectPos){   //prints the maze.
    //variables (load in image files)
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *S = al_load_bitmap("S.png");
    ALLEGRO_BITMAP *G = al_load_bitmap("G.png");
    ALLEGRO_BITMAP *Plus = al_load_bitmap("+.png");
    ALLEGRO_BITMAP *x = al_load_bitmap("x.png");
    ALLEGRO_BITMAP *dot = al_load_bitmap("-.png");
    ALLEGRO_BITMAP *hashtag = al_load_bitmap("#.png");

    //print maze
    for (int i = 0; i < maze_rows; i++){
        for (int j = 0; j < maze_cols; j++){
            //cout << mazeSolution[i][j];
            if (mazeSolution[i][j] == 'S'){
                img = S;
            } else if (mazeSolution[i][j] == 'G'){
                img = G;
            } else if (mazeSolution[i][j] == '+'){
                img = Plus;
            } else if (mazeSolution[i][j] == 'x'){
                img = x;
            } else if (mazeSolution[i][j] == '.'){
                img = dot;
            } else {
                img = hashtag;
            }
            //if position of text is affected by print
            if (affectPos){
                al_draw_bitmap(img, Xpos + 40*j, pos, 0);
            } else {
                al_draw_bitmap(img, Xpos + 40*j, pos + 40*i, 0);
            }
        }
        //cout << endl;
        if (affectPos){
            pos += 40;
        }
    }
    al_flip_display();
}

void Maze::resetMaze(){
    mazeSolution = maze;
} //resets maze
