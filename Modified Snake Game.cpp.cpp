#include<bits/stdc++.h>
#include<iostream>
#include<graphics.h>
#include<time.h>




int main()
{
    std::cout << "\tControl Guide\n";
    std::cout << "Use W or Up arrow to move up \n";         //(MODIFICATION)**Added control Guide**
    std::cout << "Use S or Down arrow to move down \n";
    std::cout << "Use A or Left arrow to move left \n";
    std::cout << "Use D or Right arrow to move right \n";
    char name[100];                                         //(MODIFICATION)**Added option to take player's name as input**
    std::cout << "Enter player name: ";
    gets(name);
    int gd = DETECT,gm,key_dir,foodX,foodY,snakeX[200],snakeY[200];   // DETECT = 0; gm = graph mode ; gd =graph diver
    initgraph(&gd,&gm,(char*)" ");

    //initialization

    int  delayTime = 250;
    int food = 0;        // snake food
    int body= 500;   // snake body
    int p_dir = 1;     //p_dir = previous direction;
    int length = 1;   // snake game;
    bool game = true;  // declaration a bool variable for the loop

    // snake array
    for(int i=0; i<200; i++){
        snakeX[i] = 0;
        snakeY[i] = 0;
    }
    // initialization for display snake ;

    snakeX[0] = 200,snakeY[0] = 200; // starting position of the snake
    foodX = 200, foodY = 200; // starting position of food
    key_dir = 1;


    // drawing game panel
    int maxy = getmaxy()-30;
    while(game)
    {


        setfillstyle(SOLID_FILL,BLACK);  //(MODIFICATION)**Changed background colour for better visualization**
        bar(0,0,630,470);  //  initializing background size or wide (lower width 630 and right length 470)

        setfillstyle(SOLID_FILL,RED);  //(MODIFICATION) **Changed border colour for better visualization**

        bar(0,0,630,10); // upper boarder width,length

        bar(0,0,10,470); // right boarder width,length

        bar(0,470,630,460); // lower boarder width,length

        bar(620,10,630,470); // lower boarder width,length


        setfillstyle(SOLID_FILL,	YELLOW); // initialization food color

        if(snakeX[0] == foodX && snakeY[0] == foodY) // checking snake and food is in the same position or not
        {
            length = length + 2;
            food = food + 1 ;
            delayTime = delayTime - 5;  //(MODIFICATION)**Optimized delay time**

            bar(foodX,foodY,foodX + 10 , foodY + 10 ); // food position

            do{
                foodX = (10 + rand() % 600);
                foodY = (10 + rand() % 450);
            }while(getpixel(foodX,foodY) != 0 && foodX > 10 && foodY>10); //condition for food visualization

            // condition for not overlaping food or snake

            foodX = foodX / 10;
            foodX = foodX * 10;
            foodY = foodY / 10;
            foodY = foodY * 10;

            // condition for food coordinate can't be 10, if so then the food will situated beside the boarder line every time

            if(foodX == 10){
                foodX = rand() % 10 + 5;
                foodX = food * 10;
            }
            else if(foodY == 10)
            {
                foodY = rand() % 10 + 5;
                foodY = foodY * 10;
            }

        }

        bar(foodX,foodY,foodX + 10, foodY + 10); // final  food position for display

        setfillstyle(SOLID_FILL,	GREEN); // initialize snake color

        // condition for key direction

        if(GetAsyncKeyState(VK_RIGHT)||GetAsyncKeyState('D')){          //(MODIFICATION)**Added W, A, S, D as alternative control option**
            key_dir = 1;
        }
        else if(GetAsyncKeyState(VK_LEFT)||GetAsyncKeyState('A')){
            key_dir = 2;
        }
        else if(GetAsyncKeyState(VK_UP)||GetAsyncKeyState('W')){
            key_dir = 3;
        }
        else if(GetAsyncKeyState(VK_DOWN)||GetAsyncKeyState('S')){
            key_dir = 4;
        }
        else {
                key_dir = 0;
        }
        char ara1[200];
        char ara2[200];
        sprintf(ara1,"%s ", name);                  //(MODIFICATION)**Displayed player's name on screen**
        sprintf(ara2,"Scored: %d",(food-1)*10);     //(MODIFICATION)**Live update of player's score**
        setcolor(LIGHTBLUE);
        settextstyle(6,0,2);
        settextstyle(6,0,2);
        outtextxy(220,maxy,ara2);
        outtextxy(220,0,ara1);

        // condition for moving snake according to key direction

        switch(key_dir)
        {
        case 0:
            if(p_dir == 1){
                snakeX[0] = snakeX[0] + 10;
            }
            else if(p_dir == 2){
                snakeX[0] = snakeX[0] - 10;
            }
            else if(p_dir == 3){
                snakeY[0] = snakeY[0] - 10;
            }
            else if(p_dir == 4){
                snakeY[0] = snakeY[0] + 10;
            }
            else{
                key_dir = 0;
            }
            break;

        case 1:
            snakeX[0] = snakeX[0] + 10;
            p_dir = 1;
            break;
        case 2:
            snakeX[0] = snakeX[0] - 10;
            p_dir = 2;
            break;
        case 3:
            snakeY[0] = snakeY[0] - 10;
            p_dir = 3;
            break;
        case 4:
            snakeY[0] = snakeY[0] + 10;
            p_dir = 4;
            break;

        }

       // displaying snake

       for(int i =0; i < length; i++)
       {
           bar(snakeX[i], snakeY[i], snakeX[i] + 10, snakeY[i] + 10);
       }

       // body of snake

       for(int i = 199; i > 0; i--)
       {
           snakeX[i] = snakeX[i - 1];
           snakeY[i] = snakeY[i - 1];
       }

    // checking bumping into body

    for(int i = 2; i < length; i++)
    {
        if(snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
        {
            body = i;
            break;
        }
    }

    delay(delayTime);

    // checking bumping in to boundary;

    if(snakeX[0] >= 615 || snakeX[0] <=5 || snakeY[0] <= 5|| snakeY[0] >= 455){
        std::cout<<"Snake bumped into the wall !!\n\n";
        game = false;
    }

    // checking bumping into body

    if(snakeX[0] == snakeX[body] && snakeY[0] ==  snakeY[body] ){
        std::cout<<"Snake bumped into itself !!!\n\n";
        game = false;
    }

    }

    // game result

    std::cout<<"Your score : " <<(food-1)*10<<"\n\n";
    std::cout<<"Game Over !!!\n\n";
    getch();
    return 0;
}
