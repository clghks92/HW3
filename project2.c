#include<ncurses.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>
#include<malloc.h>
#include<termio.h>

#define ENTER 13
#define LEFT 68
#define RIGHT 67
#define UP 65
#define DOWN 66

#define MAINMENU 0
#define SIGN_UP 1
#define SIGN_IN 2
#define PLAY 3
#define SIGN_AFTER 10
#define SIGN_OUT 4
#define WITHDRAWAL 5
#define EXIT 6
#define LOGIN 7
#define INGAME 8
#define BACK 9
#define YES 11
#define STATISTICS 12
#define ID 18
#define PASSWARD 14
#define PSIGNIN 15


#define NEXTTURN 17
#define GAMESTART 19
#define REGAME 21

#define IDPWLENGTH 20
#define MEM_COUNT 100

int mygetch(void)
{
    struct termios oldt,
    newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}




struct Mem {
	char name[IDPWLENGTH];
	char passwd[IDPWLENGTH];
	int win, lose;
	bool login;
};


int main_menu();
int sign_up();
int sign_in();
int withdrawal();
int sign_after();
int statistics();
int playin();
void init_scr();
void saveinfo();
int P_sign_in();

struct Mem Mem;
struct Mem Mem2;


void topbottomWindow(WINDOW *upWindow, WINDOW *downWindow)
{
	
	upWindow = subwin(stdscr, 23, 80, 0, 0);
	wbkgd(upWindow, COLOR_PAIR(1));
	downWindow = subwin(stdscr, 7, 80, 16, 0);
	wbkgd(downWindow, COLOR_PAIR(2));
	attron(COLOR_PAIR(1));
}

void init_scr()
{
	initscr();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_CYAN);
	init_pair(2, COLOR_CYAN, COLOR_WHITE);
}




int main_menu()
{

	werase(stdscr);
	curs_set(0);
	char key; //유저 키 입력
	int sel_menu = SIGN_IN;

	WINDOW *upMenu, *downMenu;

	topbottomWindow(upMenu, downMenu);

	attron(COLOR_PAIR(1));
	mvprintw(5, 28, "System Software Practice");
	mvprintw(7, 37, "OTHELLO");
	mvprintw(13, 68, "2014726094");
	mvprintw(15, 68, "Kim chi hwan");

	while(1){
		attron(COLOR_PAIR(2));
		mvprintw(19, 5, "SIGN IN");
		mvprintw(19, 38, "SIGN UP");
		mvprintw(19, 72, "EXIT");

		attron(A_STANDOUT | A_UNDERLINE);

		switch(sel_menu){
			case SIGN_IN:
				mvprintw(19, 5, "SIGN_IN");
				break;
			case SIGN_UP:
				mvprintw(19, 38, "SIGN_UP");
				break;
			case EXIT:
				mvprintw(19, 72, "EXIT");
				break;
			}

		attroff(A_STANDOUT | A_UNDERLINE);
		
		refresh();

		key = getchar();

		switch(key){
			case RIGHT:
				if (sel_menu == SIGN_IN){
					sel_menu = SIGN_UP;
				}
				else if (sel_menu == SIGN_UP){
					sel_menu = EXIT;
				}
				else if (sel_menu == EXIT){
					sel_menu = SIGN_IN;
				}
				break;

			case LEFT:
				if (sel_menu == SIGN_IN){
					sel_menu = EXIT;
				}
				else if (sel_menu == SIGN_UP){
					sel_menu = SIGN_IN;
				}
				else if (sel_menu == EXIT){
					sel_menu = SIGN_UP;
				}
				break;

			case ENTER:
				delwin(upMenu);
				delwin(downMenu);
				if (sel_menu == SIGN_IN){
                                        sign_in();
                                }
                                else if (sel_menu == SIGN_UP){
                                        sign_up();
                                }
                                else if (sel_menu == EXIT){
                                        exit(1);
                                }
                                break;

		}
	}
}

int sign_up(){
	werase(stdscr);
	char key;
	char id[IDPWLENGTH] ="";
	char passwd[IDPWLENGTH] ="";
	int i;
	int sel_signup = ID;
	char ch;
	

	WINDOW *upMenu, *downMenu;

        topbottomWindow(upMenu, downMenu);

	 attron(COLOR_PAIR(1));
	 mvprintw(4, 32, "SIGN UP");
	 mvprintw(5, 31, ":");
	 mvprintw(6, 31, ":");

      	while(1){
		attron(COLOR_PAIR(1));
		mvprintw(5, 27, "ID");
		mvprintw(5, 32, "                ");
		mvprintw(5, 32, id);
		mvprintw(6, 21, "PASSWARD");
		mvprintw(6, 32, "                ");
		for(i=0; i<strlen(passwd); i++)
		{
			mvprintw(5, 32, "*");
		}

		attron(COLOR_PAIR(2));



	       	mvprintw(19, 5, "SIGN UP");
		mvprintw(19, 72, "BACK");
		
		attron(A_STANDOUT | A_UNDERLINE);

		switch(sel_signup){
			case ID:
				curs_set(1);
				mvprintw(5, 27, "ID: ");
				move(5, 31 + strlen(id) );
				break;
			case PASSWARD:
				curs_set(1);
				mvprintw(6, 21, "PASSWORD: ");
				move(7, 31+strlen(passwd));
				break;
			case SIGN_UP:
				curs_set(0);
                                mvprintw(19, 5, "SIGN_UP");
                                break;
                        case BACK:
				curs_set(0);
                                mvprintw(19, 72, "BACK");
                                break;

		}

		attroff(A_STANDOUT | A_UNDERLINE);

		refresh();
                key = getchar();
				
				switch(key){
					case RIGHT:
						if(sel_signup == SIGN_UP){
							sel_signup = BACK;
						}

						else if(sel_signup == BACK){
							sel_signup = SIGN_UP;
						
						
						}
						
						break;
					case LEFT:
						
						if(sel_signup == SIGN_UP){
							sel_signup = BACK;
						
						}
						else if(sel_signup == BACK){
							sel_signup = SIGN_UP;
						}
						break;

				        case DOWN:
						if(sel_signup == ID){
							sel_signup = PASSWARD;
						}
						else if(sel_signup == PASSWARD){
							sel_signup = SIGN_UP;
						}
						else if(sel_signup == SIGN_UP){
							sel_signup = BACK;
						}
						break;

					case ENTER:
						if(sel_signup == SIGN_UP)
						{
							int fd = open("info", O_RDWR|O_CREAT, 0644);

							int buflength = IDPWLENGTH + IDPWLENGTH + 10;
							char saveinfo[buflength];
							char saveid[buflength], savepw[buflength];
							int savewin, savelose;
							bool loginsuccess = true;

							while(read(fd, saveinfo, buflength) > 0)
							{
								sscanf(saveinfo, "%s %s %d %d", saveid, savepw, &savewin, &savelose);
								if(strcmp(saveid, id) == 0)
								{
									mvprintw(22, 1, "%s has already exist in DB!(please any key)", id);
									loginsuccess = false;
									break;
									
								}
							}
							if(loginsuccess == true )
							{
									mvprintw(22, 1, "Welcome to OTHELLO world(please any key)");
									sprintf(saveinfo, "%s %s %d %d", saveid, savepw, 0, 0);
									write(fd, saveinfo, buflength);
									getch();
									
									close(fd);
									delwin(upMenu);
									delwin(downMenu);
									return main_menu();
							}
							else
							{
								close(fd);
								break;
							}

						}
						
						else if(sel_signup == ID){
							sel_signup = PASSWARD;
						}
						else if(sel_signup == PASSWARD){
							sel_signup = SIGN_UP;
						}

						else if(sel_signup == BACK){
							return main_menu();
						}
						break;
				}
				}
		
}


                                             
                                         
                                                       
                                                                                                                
                                                                                    
                                                                                      
                                                                                      
                                                                            
                                                                    
int sign_in()
{
	char id[IDPWLENGTH] ="";
	char passwd[IDPWLENGTH] ="";
	int i;
	werase(stdscr);
	char key, ch;
	int sel_signin = ID;

	WINDOW *upMenu, *downMenu;
        topbottomWindow(upMenu, downMenu);


	mvprintw(4, 32, "SIGN IN");
	mvprintw(5, 29, ":");
	mvprintw(7, 29, ":");



	while(1){

		attron(COLOR_PAIR(1));
		mvprintw(5, 26, "ID");
		mvprintw(5, 32, "               ");
		mvprintw(5, 32, id);
                mvprintw(7, 20, "PASSWORD");
		mvprintw(7, 32, "                  ");
		for(i=0; i<strlen(passwd); i++)
		{
			mvprintw(7, 32, "*");
		}
		attron(COLOR_PAIR(2));

		mvprintw(19, 5, "SIGN IN");
		mvprintw(19, 72, "BACK");
	
		attron(A_STANDOUT | A_UNDERLINE);

		switch(sel_signin){
			case ID:
				curs_set(1);
				mvprintw(5, 26, "ID");
				move(5, 32+strlen(id));
				break;
			case PASSWARD:
				curs_set(1);
				mvprintw(7, 20, "PASSWARD");
				move(7, 32+strlen(passwd));
				break;
                        case SIGN_IN:
				curs_set(0);
                                mvprintw(19, 5, "SIGN_IN");
                                break;
                        case BACK:
				curs_set(0);
                                mvprintw(19, 72, "BACK");
                                break;

                }
		attroff(A_STANDOUT | A_UNDERLINE);

		refresh();

		key = getchar();

		switch(key){
			case DOWN:
				if(sel_signin == ID){
					sel_signin = PASSWARD;
				}
				else if(sel_signin == PASSWARD){
					sel_signin = SIGN_IN;
				}
				break;
			case UP:
				if(sel_signin == ID){
					sel_signin = SIGN_IN;
				}
				else if(sel_signin == PASSWARD){
					sel_signin = ID;
				}
				break;
			case RIGHT:
				if(sel_signin == SIGN_IN){
					sel_signin = BACK;

				}

				else if (sel_signin == BACK){
					sel_signin = SIGN_IN;
				}
				break;
				
			case LEFT:
				if(sel_signin = SIGN_IN){
					sel_signin = BACK;
				}

			        else if (sel_signin == BACK){
					 sel_signin = SIGN_IN;              
                                }
                                break;
			case ENTER:
				if(sel_signin == ID){
					sel_signin = PASSWARD;
				}
				else if(sel_signin == PASSWARD){
					sel_signin = SIGN_IN;
				}
				else if(sel_signin == SIGN_IN){
					int fd = open("info", O_RDWR|O_CREAT, 0644);

					int buflength = IDPWLENGTH + IDPWLENGTH + 10;
					char saveinfo[buflength];
					char saveid[IDPWLENGTH], savepasswd[IDPWLENGTH];
					int savewin, savelose;

					while(read(fd, saveinfo, buflength) > 0)
					{
						sscanf(saveinfo, "%s %s %d %d", saveid, savepasswd, &savewin, &savelose);
						if(strcmp(saveid, id) == 0)
						{
							if(strcmp(savepasswd, passwd) == 0)
							{
								Mem.login = true;
								strcpy(Mem.name, id);
								strcpy(Mem.passwd, passwd);
								Mem.win = savewin;
								Mem.lose = savelose;
								close(fd);
								delwin(upMenu);
								delwin(downMenu);
								return P_sign_in();
							}
					
						}
					
					}
					close(fd);
					mvprintw(22, 1, "Login Failed");	
					
				}
				else if(sel_signin == BACK){
					delwin(upMenu);
					delwin(downMenu);
					return main_menu();
				}
				break;
		}
	}
}


int P_sign_in()
{
	char id[IDPWLENGTH] ="";
	char passwd[IDPWLENGTH] ="";
	int i;
	werase(stdscr);
	char key;
	int psign_in = ID;

	WINDOW *upMenu, *downMenu;
        topbottomWindow(upMenu, downMenu);

	mvprintw(4, 32, "2P LOGIN");

	while(1){
		attron(COLOR_PAIR(1));
		mvprintw(5, 26, "ID: ");
		mvprintw(5, 32, id);
		mvprintw(7, 20, "PASSWARD: ");
		for(i=0; i<strlen(passwd); i++){
			mvprintw(7, 32, "*");
		}

		attron(COLOR_PAIR(2));

		mvprintw(19, 5, "SIGN_IN");
		mvprintw(19, 72, "BACK");

		attron(A_STANDOUT | A_UNDERLINE);

		switch(psign_in){
			case ID:
				curs_set(1);
				mvprintw(5, 26, "ID: ");
				move(5, 32+strlen(id));
				break;
			case PASSWARD:
				curs_set(1);
				mvprintw(7, 20, "PASSWARD: ");
				move(7, 32+strlen(passwd));
				break;
			case SIGN_IN:
				curs_set(0);
				mvprintw(19, 5, "SING_IN");
				break;
			case BACK:
				curs_set(0);
				mvprintw(19, 72, "BACK");
				break;
		}

		attroff(A_STANDOUT | A_UNDERLINE);

		refresh();

		key = getchar();

		switch(key){
			case UP:
				if(psign_in == ID){
					psign_in = BACK;
				}
				else if(psign_in == PASSWARD){
					psign_in = ID;
				}
				else if(psign_in == SIGN_IN){
					psign_in = PASSWARD;
				}
				break;
			case DOWN:
				if(psign_in == BACK){
				        psign_in = ID;
				}
				else if(psign_in == ID){
					psign_in = PASSWARD;
				}
				else if(psign_in == PASSWARD){
					psign_in = SIGN_IN;
				}
				break;
			case RIGHT:
				if(psign_in == SIGN_IN){
					psign_in = BACK;
				}
				else if(psign_in == BACK){
					psign_in = SIGN_IN;
				}
				break;
			case LEFT:
				if(psign_in == SIGN_IN){
					psign_in = BACK;
				}
				else if(psign_in == BACK){
					psign_in = SIGN_IN;
				}
				break;
			case ENTER:
				if(psign_in == ID){
					psign_in = PASSWARD;
				}
				else if(psign_in == PASSWARD){
					psign_in = SIGN_IN;
				}
				else if(psign_in == SIGN_IN){
					int fd = open("info", O_RDWR|O_CREAT, 0644);

					int buflength = IDPWLENGTH + IDPWLENGTH + 10;
                                        char saveinfo[buflength];
                                        char saveid[IDPWLENGTH], savepasswd[IDPWLENGTH];
                                        int savewin, savelose;
				

                                        while(read(fd, saveinfo, buflength) > 0)
                                        {
                                                sscanf(saveinfo, "%s %s %d %d", saveid, savepasswd, &savewin, &savelose);
                                                if(strcmp(saveid, id) == 0)
                                                {
						
                                                        if(strcmp(savepasswd, passwd) == 0)
                                                        {
                                                                Mem2.login = true;
                                                                strcpy(Mem2.name, id);
                                                                strcpy(Mem2.passwd, passwd);
                                                                Mem2.win = savewin;
                                                                Mem2.lose = savelose;
                                                                close(fd);
                                                                delwin(upMenu);
                                                                delwin(downMenu);
                                                                return sign_after();
                                                        }
                                                  
                                                    
						}
                                                
					}         
                                        close(fd);
                                        mvprintw(22, 1, "Login Failed");
                                                
                                       
				}
				else if(psign_in == BACK){
					return main_menu();
				}
				break;
		}
	}
}




	








int withdrawal()
{
        werase(stdscr);
        char id[IDPWLENGTH]="";
        char passwd[IDPWLENGTH]="";
        int i;
        char key, ch;
        int sel_with = ID;

        WINDOW *upMenu, *downMenu;
        topbottomWindow(upMenu, downMenu);

	mvprintw(4, 26, "WITHDRAWAL");

	while(1){
		attron(COLOR_PAIR(2));
                mvprintw(19, 5, "WITHDRAWAL");
                mvprintw(19, 72, "BACK");

		mvprintw(5, 20, "PLAYER ID: ");
		mvprintw(5, 32, id);
		mvprintw(7, 21, "PASSWARD: ");
		for(i=0; i<strlen(passwd); i++){
			mvprintw(7, 32, "*");
		}

    
		attron(A_STANDOUT | A_UNDERLINE);

		switch(sel_with){
			case ID:
				curs_set(1);
				mvprintw(5, 20, "PLAYER ID: ");
				move(5, 32+strlen(id));
				break;
			case PASSWARD:
				curs_set(1);
				mvprintw(7, 21, "PASSWARD: ");
				move(5, 32+strlen(passwd));
				break;
                        case WITHDRAWAL:
				curs_set(0);
                                mvprintw(19, 5, "SIGN_UP");
                                break;
                        case BACK:
				curs_set(0);
                                mvprintw(19, 72, "BACK");
                                break;

                }

		attroff(A_STANDOUT | A_UNDERLINE);

		refresh();

		key = getchar();

		switch(key){
			case RIGHT:
				if(sel_with == WITHDRAWAL){
					sel_with = BACK;
					
				}
				else if(sel_with == BACK){
					sel_with = WITHDRAWAL;
				}
				break;

			case LEFT:
				if(sel_with == WITHDRAWAL){
                                        sel_with = BACK;

                                }
                                else if(sel_with == BACK){
                                        sel_with = WITHDRAWAL;
                                }
                                break;
			case UP:
				if(sel_with == ID || sel_with == BACK){
					sel_with = WITHDRAWAL;
				}
				else if(sel_with == PASSWARD){
					sel_with = ID;
				}
				else if(sel_with == WITHDRAWAL){
					sel_with = PASSWARD;
				}
				break;
			case DOWN:
				if(sel_with == ID){
					sel_with = PASSWARD;
				}
				else if(sel_with == PASSWARD){
					sel_with = WITHDRAWAL;
				}
				break;
			case ENTER:
				if(sel_with == ID){
					sel_with = PASSWARD;
				}
				else if(sel_with == PASSWARD){
					sel_with = WITHDRAWAL;
				}
				else if(sel_with == BACK){
					return sign_after();
				}
				break;
							


		
		}
	}
}

int sign_after()
{
	werase(stdscr);
        char id[IDPWLENGTH] ="";
        char passwd[IDPWLENGTH]="";
        int i;
        char key, ch;
        int sel_signafter = PLAY;

        WINDOW *upMenu, *downMenu;
        topbottomWindow(upMenu, downMenu);


	while(1){
		attron(COLOR_PAIR(2));
                mvprintw(13, 5, "PLAY");
                mvprintw(13, 20, "SIGN OUT");
                mvprintw(13, 40, "WITHDRAWAL");

		mvprintw(5, 17, "PLAYER ID: %s", Mem.name);

		attron(A_STANDOUT | A_UNDERLINE);

		switch(sel_signafter){
			case PLAY:
				
				mvprintw(13, 5, "PLAY");
				break;
			case SIGN_OUT:
				
				mvprintw(13, 20, "SIGN OUT");
				break;
			case BACK:
				
				mvprintw(13, 40, "WITHDARWAL");
				break;
			}

		attroff(A_STANDOUT | A_UNDERLINE);

		refresh();
		key = getchar();

		switch(key){
			case ENTER:
				if(sel_signafter == PLAY){
					delwin(upMenu);
                                        delwin(downMenu);
					statistics();
				}
				else if (sel_signafter == SIGN_OUT){
				        Mem.login = false;
					delwin(upMenu);
                                        delwin(downMenu);
					sign_in();
				}
				else if(sel_signafter == WITHDRAWAL){
					delwin(upMenu);
                                        delwin(downMenu);
					withdrawal();
				}
			case RIGHT:
				if(sel_signafter == PLAY){
					sel_signafter == SIGN_OUT;
				}
				else if(sel_signafter == SIGN_OUT){
					sel_signafter == WITHDRAWAL;
				}
				else if(sel_signafter == WITHDRAWAL){
					sel_signafter == PLAY;
				}
				break;

			case LEFT:
				if(sel_signafter == PLAY){
					sel_signafter == WITHDRAWAL;
				}
				else if(sel_signafter == SIGN_OUT){
					sel_signafter == PLAY;
				}
				else if(sel_signafter == WITHDRAWAL){
					sel_signafter == SIGN_OUT;
				}
				break;
		}
	}
}


int statistics()
{
        werase(stdscr);
        int i;
        char key;
	curs_set(0);
        int sel_stat = YES;

        WINDOW *upMenu, *downMenu;
        topbottomWindow(upMenu, downMenu);

        mvprintw(4, 5, "PLAYER1: %s", Mem.name);
	mvprintw(6, 11, "STATISTICS");
	if(Mem.win + Mem.lose != 0){
		mvprintw(8, 3, "WIN: %d / LOSE: %d (%d)", Mem.win, Mem.lose, (Mem.win*100) / Mem.win + Mem.lose);
	}
	else{
		mvprintw(8, 3, "WIN: 0 / LOSE: 0 (0)");
	}
	mvprintw(4, 45, "PLAYER2: %s", Mem2.name);
	mvprintw(6, 51, "STATISTICS");
	if(Mem2.win + Mem2.lose != 0){
		mvprintw(8, 43, "WIN: %d / LOSE: %d (%d)", Mem2.win, Mem2.lose, (Mem2.win*100) / Mem2.win + Mem2.lose);
	}
	else{
		mvprintw(8, 43, "WIN: 0 / LOSE: 0 (0)");
	}

	while(1){
		attron(COLOR_PAIR(2));

	        mvprintw(19, 39, "OK");
		attron(A_STANDOUT | A_UNDERLINE);


		switch(sel_stat)
		{
			case YES:
				mvprintw(19, 39, "OK");
				break;

		}

		key = getchar();

		switch(key){
			case ENTER:
				if(sel_stat == OK){
					playin();
				}
			break;
		}
	}
}

int playin()
{
	werase(stdscr);
	curs_set(0);
	char key; 
	int cur;
	int x=15;
	int y=5;
	int i = 0;
	int j = 0;
	char game[12][28];
	int sel_play = INGAME;
	int turn = 1;
	char endkey;
	bool nextturn = false;

	int first = 0;
	int second = 0;

	for(i=0;i<12;i++)
	{

		for(j=0;j<28;j++)
		{
			game[i][j]=' ';

		}
	}

	game[5][15]='o';
	game[7][19]='o';
	game[5][19]='x';
	game[7][15]='x';

	for(i=0;i<12;i++)
	{
		for(j=0;j<28;j++)
		{
			if(game[i][j]=='o')
				first+=1;

			else if(game[i][j] == 'x')
				second+=1;
		}
	}


        int select = 0;
	int endgame = 0;

	WINDOW *rightWindow, *leftWindow;
	rightWindow = subwin(stdscr, 30, 60, 0, 0);
	wbkgd(rightWindow, COLOR_PAIR(2));
	leftWindow = subwin(stdscr, 30, 20, 0, 60);
	wbkgd(leftWindow, COLOR_PAIR(1));
	attron(COLOR_PAIR(1));

	while(1){

		attron(COLOR_PAIR(1));

		mvprintw(12, 16, "+---+---+---+---+---+---+");
		mvprintw(13, 16, "| %c | %c | %c | %c | %c | %c |",game[1][7],game[1][11],game[1][15],game[1][19],game[1][23],game[1][27]);
		mvprintw(14, 16, "+---+---+---+---+---+---+");
		mvprintw(15, 16, "| %c | %c | %c | %c | %c | %c |",game[3][7],game[3][11],game[3][15],game[3][19],game[3][23],game[3][27]);
		mvprintw(16, 16, "+---+---+---+---+---+---+");
		mvprintw(17, 16, "| %c | %c | %c | %c | %c | %c |",game[5][7],game[5][11],game[5][15],game[5][19],game[5][23],game[5][27]);
		mvprintw(18, 16, "+---+---+---+---+---+---+");
		mvprintw(19, 16, "| %c | %c | %c | %c | %c | %c |",game[7][7],game[7][11],game[7][15],game[7][19],game[7][23],game[7][27]);
		mvprintw(20, 16, "+---+---+---+---+---+---+");
		mvprintw(21, 16, "| %c | %c | %c | %c | %c | %c |",game[9][7],game[9][11],game[9][15],game[9][19],game[9][23],game[9][27]);
		mvprintw(22, 16, "+---+---+---+---+---+---+");
		mvprintw(23, 16, "| %c | %c | %c | %c | %c | %c |",game[11][7],game[11][11],game[11][15],game[11][19],game[11][23],game[11][27]);
		mvprintw(24, 16, "+---+---+---+---+---+---+");

		first = 0;
		second = 0;

		for(i=0; i<12; i++)
		{
			for(j=0; j<28; j++)
			{
				if(game[i][j] == 'o'){
					first += 1;
				}
				else if(game[i][j] == 'x'){
					second += 1;
				}
			}
		}

		attroff(COLOR_PAIR(1));
		attron(COLOR_PAIR(2));
		attron(A_UNDERLINE);
		mvprintw(15, 65, "N");
		mvprintw(17, 66, "R");
		mvprintw(19, 68, "X");
		attroff(A_UNDERLINE);
		mvprintw(15, 66, "EXT TURN");
		mvprintw(17, 67, "EGAME");
		mvprintw(19, 67, "E");
		mvprintw(19, 69, "IT");
		mvprintw(11, 62, "%s(O) : %d", Mem.name, first);
		mvprintw(12, 62, "%s(X) : %d", Mem2.name, second);

		if(first + second == 36)
		{
			if(first > second)
			{
				mvprintw(15, 65, "1P WIN!");
				Mem.win++;
				Mem2.lose--;
				saveinfo();
				endgame = REGAME;
			}
			else if(first < second)
			{
				mvprintw(15, 65, "2P WIN!");
				Mem.lose--;
				Mem2.win++;
				saveinfo();
				endgame = REGAME;
			}
			else if(first == second)
			{
				mvprintw(15, 65, "DRAW!");
				endgame = REGAME;
			}
		

		        while(1){
			     attron(A_UNDERLINE);
			     mvprintw(17, 66, "R");
			     mvprintw(19, 68, "X");
			     attroff(A_UNDERLINE);
			     mvprintw(17, 67, "EGAME");
			     mvprintw(19, 67, "E");
			     mvprintw(19, 69, "IT");
			     attron(A_STANDOUT|A_UNDERLINE);

			     switch(endgame){
				    case REGAME:
				        mvprintw(17, 66, "REGAME");
					break;
				    case EXIT:
					mvprintw(19, 67, "EXIT");
					break;
			      }  

			      attroff(A_STANDOUT|A_UNDERLINE);
			      move(y,x);
			      refresh();
			      endkey = getchar();

			      switch(endkey){
			        	case UP:
				        	if(endgame==REGAME){
							endgame = EXIT;
							y=19;
						}
						else if(endgame == EXIT){
							endgame = REGAME;
							y=17;
						}
						break;
					case DOWN:
						if(endgame==REGAME){
							endgame = EXIT;
							y=19;
						}
						else if(endgame==EXIT){
							endgame = REGAME;
							y=17;
						}
						break;
					case ENTER:
						if(endgame==REGAME){
							delwin(rightWindow);
							delwin(leftWindow);
							return playin();
						}
						else if(endgame == EXIT){
							delwin(rightWindow);
							delwin(leftWindow);
							return sign_after();
						}
			      }
			}
		}

		else if(first + second != 36 && second == 0)
		{
			mvprintw(15, 65, "1P WIN!");
			Mem.win++;
			Mem2.lose--;
			saveinfo();
			endgame = REGAME;

                        while(1){
                             attron(A_UNDERLINE);
                             mvprintw(17, 66, "R");
                             mvprintw(19, 68, "X");
                             attroff(A_UNDERLINE);
                             mvprintw(17, 67, "EGAME");
                             mvprintw(19, 67, "E");
                             mvprintw(19, 69, "IT");
                             attron(A_STANDOUT|A_UNDERLINE);

                             switch(endgame){
                                    case REGAME:
                                        mvprintw(17, 66, "REGAME");
                                        break;
                                    case EXIT:
                                        mvprintw(19, 67, "EXIT");
                                        break;
                              }

                              attroff(A_STANDOUT|A_UNDERLINE);
                              move(y,x);
                              refresh();
                              endkey = getchar();

			                                   switch(endgame){
                                    case REGAME:
                                        mvprintw(17, 66, "REGAME");
                                        break;
                                    case EXIT:
                                        mvprintw(19, 67, "EXIT");
                                        break;
                              }

                              attroff(A_STANDOUT|A_UNDERLINE);
                              move(y,x);
                              refresh();
                              endkey = getchar();

                              switch(endkey){
                                        case UP:
                                                if(endgame==REGAME){
                                                        endgame = EXIT;
                                                        y=19;
                                                }
                                                else if(endgame == EXIT){
                                                        endgame = REGAME;
                                                        y=17;
                                                }
                                                break;
                                        case DOWN:
                                                if(endgame==REGAME){
                                                        endgame = EXIT;
                                                        y=19;
                                                }
                                                else if(endgame==EXIT){
                                                        endgame = REGAME;
                                                        y=17;
                                                }
                                                break;
                                        case ENTER:
                                                if(endgame==REGAME){
                                                        delwin(rightWindow);
                                                        delwin(leftWindow);
                                                        return playin();
                                                }
                                                else if(endgame == EXIT){
                                                        delwin(rightWindow);
                                                        delwin(leftWindow);
                                                        return sign_after();
                                                }
                              }
			}
		}

		else if(first + second != 36 && first == 0)
		{
			mvprintw(15, 65, "2P WIN!");
                        Mem2.win++;
                        Mem.lose--;
                        saveinfo();
                        endgame = REGAME;

                        while(1){
                             attron(A_UNDERLINE);
                             mvprintw(17, 66, "R");
                             mvprintw(19, 68, "X");
                             attroff(A_UNDERLINE);
                             mvprintw(17, 67, "EGAME");
                             mvprintw(19, 67, "E");
                             mvprintw(19, 69, "IT");
                             attron(A_STANDOUT|A_UNDERLINE);

                             switch(endgame){
                                    case REGAME:
                                        mvprintw(17, 66, "REGAME");
                                        break;
                                    case EXIT:
                                        mvprintw(19, 67, "EXIT");
                                        break;
                              }

                              attroff(A_STANDOUT|A_UNDERLINE);
                              move(y,x);
                              refresh();
                              endkey = getchar();

			      switch(endgame){
                                    case REGAME:
                                        mvprintw(17, 66, "REGAME");
                                        break;
                                    case EXIT:
                                        mvprintw(19, 67, "EXIT");
                                        break;
                              }
			      attroff(A_STANDOUT|A_UNDERLINE);
                              move(y,x);
                              refresh();
                              endkey = getchar();

                              switch(endkey){
                                        case UP:
                                                if(endgame==REGAME){
                                                        endgame = EXIT;
                                                        y=19;
                                                }
                                                else if(endgame == EXIT){
                                                        endgame = REGAME;
                                                        y=17;
                                                }
                                                break;
                                        case DOWN:
                                                if(endgame==REGAME){
                                                        endgame = EXIT;
                                                        y=19;
                                                }
                                                else if(endgame==EXIT){
                                                        endgame = REGAME;
                                                        y=17;
                                                }
                                                break;
                                        case ENTER:
                                                if(endgame==REGAME){
                                                        delwin(rightWindow);
                                                        delwin(leftWindow);
                                                        return playin();
                                                }
                                                else if(endgame == EXIT){
                                                        delwin(rightWindow);
                                                        delwin(leftWindow);
                                                        return sign_after();
                                                }
                              }
                        }
		}


		attron(A_UNDERLINE|A_STANDOUT);

		if(turn%2 == 1){
			mvprintw(11, 62, "%s (O)", Mem.name);
		}
		else if(turn%2 == 0){
			mvprintw(12, 62, "%s (X)", Mem2.name);
		}
		switch(select){
			case NEXTTURN:
				mvprintw(15, 65, "NEXTTURN");
				break;
			case REGAME:
				mvprintw(17, 66, "REGAME");
				break;
			case EXIT:
				mvprintw(19, 67, "EXIT");
		}

		attroff(A_STANDOUT | A_UNDERLINE);
		mvprintw(y,x,"%c",game[y][x]);
		refresh();

		key = getchar();

		switch(key){
			case 'x':
				x=67;
				y=19;
				select = EXIT;
				break;
			case 'g':
				x = 15;
				y = 5;
				break;
			case 'n':
				x = 65;
				y = 15;
				select = NEXTTURN;
				break;
			case 'r':
				x = 66;
				y = 17;
				select = REGAME;
				break;
			case DOWN:
				if(select == EXIT){
					select = NEXTTURN;
				}
				else if(select == NEXTTURN){
					select = REGAME;
				}
				else if(select == REGAME){
					select = EXIT;
				}

				else{
					y = y+2;
					 if(y == 13){
						 y = 1;
					 }
				}
				break;
			case UP:
				if(select == EXIT){
					select = REGAME;
				}
				else if(select == REGAME){
					select = NEXTTURN;
				}
			        else if(select == NEXTTURN){
				        select = EXIT;
				}

				else{
					y = y-2;
					if(y == -1){
						y =11;
					}
				}
				break;
			case RIGHT:
			        x += 4;
				if(x = 31){
					x = 4;
				}
				break;
			        	
			case LEFT:
				x -= 4;
				if(x = 3){
					x = 31;
				}
				break;
				

			case ENTER:
				if(select != REGAME && select != NEXTTURN && select != EXIT && turn%2 == 1)
				{
					if(game[y][x] == ' ')
					{
						if(game[y-2][x] == 'x')
						{
							if(game[y-4][x] == 'o')
							{
								game[y-2][x] = 'o';
								game[y][x] = 'o';
								nextturn = true;
							}
							else if(game[y-4][x] == 'x')
							{
								if(game[y-6][x] == 'o')
								{
									game[y-4][x] = 'o';
									game[y-2][x] = 'o';
									game[y][x]='o';
									nextturn = true;
								}

								else if(game[y-6][x] == 'x'){
									if(game[y-8][x] == 'o'){
										game[y-6][x] = 'o';
										game[y-4][x] = 'o';
										game[y-2][x] = 'o';
										game[y][x] = 'o';
										nextturn = true;
									}

									else if(game [y-8][x] == 'x'){
										if(game [y-10][x] == 'o'){
											game[y-8][x] = 'o';
											game[y-6][x] = 'o';
											game[y-4][x] = 'o';
											game[y-2][x] = 'o';
											game[y][x] = 'o';
											nextturn = true;
										}							
									}
								}
							}
						}
						if(game[y+2][x] == 'x')
						{
							if(game[y+4][x] == 'o')
							{
								game[y+2][x] = 'o';
								game[y][x] = 'o';
								nextturn = true;
							}
							else if(game[y+4][x] == 'x')
							{
								if(game[y+6][x] == 'o')
								{
									game[y+4][x] = 'o';
									game[y+2][x] = 'o';
									game[y][x]='o';
									nextturn = true;
								}

								else if(game[y+6][x] == 'x'){
									if(game[y+8][x] == 'o'){
										game[y+6][x] = 'o';
										game[y+4][x] = 'o';
										game[y+2][x] = 'o';
										game[y][x] = 'o';
										nextturn = true;
									}

									else if(game [y+8][x] == 'x'){
										if(game [y+10][x] == 'o'){
											game[y+8][x] = 'o';
											game[y+6][x] = 'o';
											game[y+4][x] = 'o';
											game[y+2][x] = 'o';
											game[y][x] = 'o';
											nextturn = true;
										}
									}
								}
							}
						}
						if(game[y][x+4] == 'x')
						{
							if(game[y][x+8] == 'o'){
								game[y][x+4] = 'o';
								game[y][x] = 'o';
								nextturn=true;
							}

							else if(game[y][x+8] == 'x')
							{
								if(game[y][x+12] == 'o')
								{
									game[y][x+8] = 'o';
									game[y][x+4] = 'o';
									game[y][x]='o';
									nextturn=true;
								}
								else if(game[y][x+12] == 'x')
								{
									if(game[y][x+16] == 'o')
									{
										game[y][x+12] = 'o';
										game[y][x+8] = 'o';
										game[y][x+4] = 'o';
										game[y][x] = 'o';
										nextturn = true;
									}

									else if(game [y][x+16] == 'x')
									{
										if(game [y][x+20] == 'o')
										{
											game[y][x+16] = 'o';
											game[y][x+12] = 'o';
											game[y][x+8] = 'o';
											game[y][x+4] = 'o';
											game[y][x] = 'o';
											nextturn = true;
										}
									}
								}
							}
						}
						if(game[y][x-4] == 'x')
						{
							if(game[y][x-8] == 'o')
							{
								game[y][x-4] = 'o';
								game[y][x] = 'o';
								nextturn = true;
							}
							else if(game[y][x-8] == 'x')
							{
								if(game[y][x-12] == 'o')
								{
									game[y][x-8] = 'o';
									game[y][x-4] = 'o';
									game[y][x]='o';
									nextturn = true;
								}
								else if(game[y][x-12] == 'x')
								{
									if(game[y][x-16] == 'o')
									{
										game[y][x-12] = 'o';
										game[y][x-8] = 'o';
										game[y][x-4] = 'o';
										game[y][x] = 'o';
										nextturn = true;
									}

									else if(game [y][x-16] == 'x'){
										if(game [y][x-20] == 'o')
										{
											game[y][x-16] = 'o';
											game[y][x-12] = 'o';
											game[y][x-8] = 'o';
											game[y][x-4] = 'o';
											game[y][x] = 'o';
											nextturn = true;
										}
									}
								}
							}
						}
						if(game[y-2][x-4] == 'x')
						{
							if(game[y-4][x-8] == 'o')
							{
								game[y-2][x-4] = 'o';
								game[y][x] = 'o';
								nextturn = true;
							}
							else if(game[y-4][x-8] == 'x')
							{
								if(game[y-6][x-12] == 'o')
								{
									game[y-4][x-8] = 'o';
									game[y-2][x-4] = 'o';
									game[y][x]='o';
									nextturn = true;
								}
								else if(game[y-6][x-12] == 'x')
								{
									if(game[y-8][x-16] == 'o')
									{
										game[y-6][x-12] = 'o';
										game[y-4][x-8] = 'o';
										game[y-2][x-4] = 'o';
										game[y][x] = 'o';
										nextturn = true;
									}
									else if(game [y-8][x-16] == 'x')
									{
										if(game [y-10][x-20] == 'o')
										{
											game[y-8][x-16] = 'o';
											game[y-6][x-12] = 'o';
											game[y-4][x-8] = 'o';
											game[y-2][x-4] = 'o';
											game[y][x] = 'o';
											nextturn = true;
										}
									}
								}
							}
						}
						if(game[y+2][x-4] == 'x')
						{
							if(game[y+4][x-8] == 'o')
							{
								game[y+2][x-4] = 'o';
								game[y][x] = 'o';
								nextturn = true;
							}
							else if(game[y+4][x-8] == 'x')
							{
								if(game[y+6][x-12] == 'o')
								{
									game[y+4][x-8] = 'o';
									game[y+2][x-4] = 'o';
									game[y][x]='o';
									nextturn = true;
								}
								else if(game[y+6][x-12] == 'x')
							        {
									if(game[y+8][x-16] == 'o')
									{
										game[y+6][x-12] = 'o';
										game[y+4][x-8] = 'o';
										game[y+2][x-4] = 'o';
										game[y][x] = 'o';
										nextturn = true;
									}
									else if(game [y+8][x-16] == 'x')
									{
										if(game [y+10][x-20] == 'o')
										{
											game[y+8][x-16] = 'o';
											game[y+6][x-12] = 'o';
											game[y+4][x-8] = 'o';
											game[y+2][x-4] = 'o';
											game[y][x] = 'o';
											nextturn = true;
										}
									}
								}
							}
						}
						if(game[y-2][x+4] == 'x')
						{
							if(game[y-4][x+8] == 'o')
							{
								game[y-2][x+4] = 'o';
								game[y][x] = 'o';
								nextturn = true;
							}
							else if(game[y+4][x+8] == 'x')
							{
								if(game[y-6][x+12] == 'o')
								{
									game[y-4][x+8] = 'o';
									game[y-2][x+4] = 'o';
									game[y][x] = 'o';
									nextturn = true;
								}
								else if(game[y-6][x+12] == 'x')
								{
									if(game[y-8][x+16] == 'o')
									{
										game[y-6][x+12] = 'o';
										game[y-4][x+8] = 'o';
										game[y-2][x+4] = 'o';
										game[y][x] = 'o';
									        nextturn = true;
									}
									else if(game [y-8][x+16] == 'x')
									{
										if(game [y-10][x+20] == 'o')
										{
											game[y-8][x+16] = 'o';
											game[y-6][x+12] = 'o';
											game[y-4][x+8] = 'o';
											game[y-2][x+4] = 'o';
											game[y][x] = 'o';
											nextturn = true;
										}
									}
						               }
							}
						}
						if(game[y+2][x+4] == 'x')
						{
							if(game[y+4][x+8] == 'o')
							{
								game[y+2][x+4] = 'o';
								game[y][x] = 'o';
								nextturn = true;
							}
							else if(game[y+4][x+8] == 'x')
							{
								if(game[y+6][x+12] == 'o')
								{
									game[y+4][x+8] = 'o';
									game[y+2][x+4] = 'o';
									game[y][x] = 'o';
									nextturn = true;
								}
								else if(game[y+6][x+12] == 'x')
								{
									if(game[y+8][x+16] == 'o')
									{
										game[y+6][x+12] = 'o';
										game[y+4][x+8] = 'o';
										game[y+2][x+4] = 'o';
										game[y][x] = 'o';
										nextturn = true;
									}
									else if(game [y+8][x+16] == 'x')
									{
										if(game [y+10][x+20] == 'o')
										{
											game[y+8][x+16] = 'o';
											game[y+6][x+12] = 'o';
											game[y+4][x+8] = 'o';
											game[y+2][x+4] = 'o';
											game[y][x] = 'o';
											nextturn = true;
										}
									}
								}
							}
						}
					}
					if(nextturn)
					{
						turn += 1;
						nextturn = false;
					}
					if(game[y][x] == 'x' || game[y][x] == 'o')
					{
						break;
					}
				}
				else if(select != REGAME && select != NEXTTURN && select != EXIT && turn%2 == 0)
				{
					if(game[y][x] ==' ')
					{
						if(game[y-2][x] == 'o')
						{
							if(game[y-4][x] == 'x')
							{
								game[y-2][x] = 'x';
								game[y][x] = 'x';
								nextturn = true;
							}
							else if(game[y-4][x] == 'o')
							{
								if(game[y-6][x] == 'x')
								{
									game[y-4][x] = 'x';
									game[y-2][x] = 'x';
									game[y][x]='x';
									nextturn = true;
								}
								else if(game[y-6][x] == 'o')
								{
									if(game[y-8][x] == 'x')
									{
										game[y-6][x] = 'x';
										game[y-4][x] = 'x';
										game[y-2][x] = 'x';
										game[y][x] = 'x';
										nextturn = true;
									}
									else if(game [y-8][x] == 'o')
									{
										if(game [y-10][x] == 'x')
										{
											game[y-8][x] = 'x';
											game[y-6][x] = 'x';
											game[y-4][x] = 'x';
											game[y-2][x] = 'x';
											game[y][x] = 'x';
											nextturn = true;
										}
									}
								}
							}
						}
						if(game[y+2][x] == 'o')
						{
							if(game[y+4][x] == 'x')
							{
								game[y+2][x] = 'x';
								game[y][x] = 'x';
								nextturn = true;
							}
							else if(game[y+4][x] == 'o')
							{
								if(game[y+6][x] == 'x')
								{
									game[y+4][x] = 'x';
									game[y+2][x] = 'x';
									game[y][x]='x';
									nextturn = true;
								}
								else if(game[y+6][x] == 'o')
								{
									if(game[y+8][x] == 'x')
									{
										game[y+6][x] = 'x';
										game[y+4][x] = 'x';
										game[y+2][x] = 'x';
										game[y][x] = 'x';
										nextturn = true;
									}
									else if(game [y+8][x] == 'o')
									{
										if(game [y+10][x] == 'x')
										{
											game[y+8][x] = 'x';
											game[y+6][x] = 'x';
											game[y+4][x] = 'x';
											game[y+2][x] = 'x';
											game[y][x] = 'x';
											nextturn = true;
										}
									}
								}
							}
						}
						if(game[y][x+4] == 'o')
						{
							if(game[y][x+8] == 'x')
							{
								game[y][x+4] = 'x';
								game[y][x] = 'x';
								nextturn = true;
							}
							else if(game[y][x+8] == 'o')
							{
								if(game[y][x+12] == 'x'){
									game[y][x+8] = 'x';
									game[y][x+4] = 'x';
									game[y][x]='x';
									nextturn = true;
								}
								else if(game[y][x+12] == 'o')
								{
									if(game[y][x+16] == 'x')
									{
										game[y][x+12] = 'x';
										game[y][x+8] = 'x';
										game[y][x+4] = 'x';
										game[y][x] = 'x';
										nextturn = true;
									}
									else if(game [y][x+16] == 'o')
									{
										if(game [y][x+20] == 'x')
										{
											game[y][x+16] = 'x';
											game[y][x+12] = 'x';
											game[y][x+8] = 'x';
											game[y][x+4] = 'x';
											game[y][x] = 'x';
											nextturn = true;
										}
									}
								}
							}
						}
						if(game[y][x-4] == 'o')
						{
							if(game[y][x-8] == 'x')
							{
								game[y][x-4] = 'x';
								game[y][x] = 'x';
								nextturn = true;
							}
							else if(game[y][x-8] == 'o')
							{
								if(game[y][x-12] == 'x')
								{
									game[y][x-8] = 'x';
									game[y][x-4] = 'x';
									game[y][x]='x';
									nextturn = true;
								}
								else if(game[y][x-12] == 'o')
								{
									if(game[y][x-16] == 'x')
									{
										game[y][x-12] = 'x';
										game[y][x-8] = 'x';
										game[y][x-4] = 'x';
										game[y][x] = 'x';
										nextturn = true;
									}
									else if(game [y][x-16] == 'o')
									{
										if(game [y][x-20] == 'x')
										{
											game[y][x-16] = 'x';
											game[y][x-12] = 'x';
											game[y][x-8] = 'x';
											game[y][x-4] = 'x';
											game[y][x] = 'x';
											nextturn = true;
										}
									}
								}
							}
						}
						if(game[y-2][x-4] == 'o')
						{
							if(game[y-4][x-8] == 'x')
							{
								game[y-2][x-4] = 'x';
								game[y][x] = 'x';
								nextturn=TRUE;
							}
							else if(game[y-4][x-8] == 'o')
							{
								if(game[y-6][x-12] == 'x')
								{
									game[y-4][x-8] = 'x';
									game[y-2][x-4] = 'x';
									game[y][x]='x';
									nextturn=TRUE;
								}
								else if(game[y-6][x-12] == 'o')
								{
									if(game[y-8][x-16] == 'x')
									{
										game[y-6][x-12] = 'x';
										game[y-4][x-8] = 'x';
										game[y-2][x-4] = 'x';
										game[y][x] = 'x';
										nextturn=TRUE;
									}
									else if(game [y-8][x-16] == 'o')
									{
										if(game [y-10][x-20] == 'x')
										{
											game[y-8][x-16] = 'x';
											game[y-6][x-12] = 'x';
											game[y-4][x-8] = 'x';
											game[y-2][x-4] = 'x';
											game[y][x] = 'x';
											nextturn=TRUE;
										}
									}
								}
							}
						}
						if(game[y+2][x-4] == 'o')
						{
							if(game[y+4][x-8] == 'x')
							{
								game[y+2][x-4] = 'x';
								game[y][x] = 'x';
								nextturn = true;
							}
							else if(game[y+4][x-8] == 'o')
							{
								if(game[y+6][x-12] == 'x')
								{
									game[y+4][x-8] = 'x';
									game[y+2][x-4] = 'x';
									game[y][x]='x';
									nextturn = true;
								}
								else if(game[y+6][x-12] == 'o')
								{
									if(game[y+8][x-16] == 'x')
									{
										game[y+6][x-12] = 'x';
										game[y+4][x-8] = 'x';
										game[y+2][x-4] = 'x';
										game[y][x] = 'x';
										nextturn = true;
									}
									else if(game [y+8][x-16] == 'o')
									{
										if(game [y+10][x-20] == 'x')
										{
											game[y+8][x-16] = 'x';
											game[y+6][x-12] = 'x';
											game[y+4][x-8] = 'x';
											game[y+2][x-4] = 'x';
											game[y][x] = 'x';
											nextturn = true;
										}
									}
								}
							}
						}
						if(game[y-2][x+4] == 'o')
						{
							if(game[y-4][x+8] == 'x')
							{
								game[y-2][x+4] = 'x';
								game[y][x] = 'x';
								nextturn = true;
							}
							else if(game[y+4][x+8] == 'o')
							{
								if(game[y-6][x+12] == 'x')
								{
									game[y-4][x+8] = 'x';
									game[y-2][x+4] = 'x';
									game[y][x] = 'x';
									nextturn = true;
								}
								else if(game[y-6][x+12] == 'o')
								{
									if(game[y-8][x+16] == 'x')
									{
										game[y-6][x+12] = 'x';
										game[y-4][x+8] = 'x';
										game[y-2][x+4] = 'x';
										game[y][x] = 'x';
										nextturn = true;
									}
									else if(game [y-8][x+16] == 'o')
									{
										if(game [y-10][x+20] == 'x')
										{
											game[y-8][x+16] = 'x';
											game[y-6][x+12] = 'x';
											game[y-4][x+8] = 'x';
											game[y-2][x+4] = 'x';
											game[y][x] = 'x';
											nextturn = true;
										}
									}
								}
							}
						}
						if(game[y+2][x+4] == 'o')
						{
							if(game[y+4][x+8] == 'x')
							{
								game[y+2][x+4] = 'x';
								game[y][x] = 'x';
								nextturn = true;
							}
							else if(game[y+4][x+8] == 'o')
							{
								if(game[y+6][x+12] == 'x')
								{
									game[y+4][x+8] = 'x';
									game[y+2][x+4] = 'x';
									game[y][x] = 'x';
									nextturn =true;
								}
								else if(game[y+6][x+12] == 'o')
								{
									if(game[y+8][x+16] == 'x')
									{
										game[y+6][x+12] = 'x';
										game[y+4][x+8] = 'x';
										game[y+2][x+4] = 'x';
										game[y][x] = 'x';
										nextturn = true;
									}
									else if(game [y+8][x+16] == 'o')
									{
										if(game [y+10][x+20] == 'x')
										{
											game[y+8][x+16] = 'x';
											game[y+6][x+12] = 'x';
											game[y+4][x+8] = 'x';
											game[y+2][x+4] = 'x';
											game[y][x] = 'x';
											nextturn = true;
										}
									}
								}
							}
						}
					}
					if(nextturn)
					{
						turn += 1;
						nextturn = false;
					}
					if(game[y][x] == 'o' || game[y][x] == 'x')
					{
						break;
					}

					else if(select == NEXTTURN)
					{
						turn += 1;
						select = 0;
						y = 5;
						x = 15;
						break;
					}
					else if(select == REGAME)
					{
						delwin(rightWindow);
						delwin(leftWindow);
						return playin();
					}
					else if(select == EXIT)
					{
						delwin(rightWindow);
						delwin(leftWindow);
						return sign_after();
					}
				}
		}
	}
}

int main(){
	init_scr();


	int menu = MAINMENU;

	while(menu != EXIT){
		switch(menu){
			case MAINMENU:
			      menu =  main_menu();
			      break;

			case SIGN_UP:
			      menu = sign_up();
			      break;

			case SIGN_IN:
			      menu = sign_in();
			      break;

		        case WITHDRAWAL:
			      menu = withdrawal();
			      break;

		        case SIGN_AFTER:
			     menu = sign_after();
			     break;

		        case STATISTICS:
			     menu = statistics();
			     break;

		        case INGAME:
			     menu = playin();
			     break;
			   
			case PSIGNIN:
			     menu = P_sign_in();
		             break;	     
			   }
		    
	}
        endwin();
        return 0;
}

void saveinfo()
{
	int fd = open("info", O_RDWR);
	
	int buflength = IDPWLENGTH + IDPWLENGTH + 10;
	char saveinfo[buflength];
	char saveid[IDPWLENGTH], savepw[IDPWLENGTH];
	int savewin, savelose;

	while(read(fd, saveinfo, buflength) < 0)
	{
		sscanf(saveinfo, "%s" "%s" "%d" "%d", saveid, savepw, &savewin, &savelose);
		if(strcmp(saveid, Mem.name) == 0)
		{
			sprintf(saveinfo, "\n %s %s %d %d", Mem.name, Mem.passwd, Mem.win, Mem.lose);
			lseek(fd, (off_t)-buflength, SEEK_CUR);
			write(fd, saveinfo, buflength);

			close(fd);
		}
	}

	int fd2 = open("info", O_RDWR);
	
	char saveinfo2[buflength];
	char saveid2[IDPWLENGTH], savepw2[IDPWLENGTH];
	int savewin2, savelose2;

	while(read(fd2, saveinfo2, buflength) < 0)
	{
		sscanf(saveinfo2, "%s %s %d %d", saveid2, savepw2, &savewin2, &savelose2);
		if(strcmp(saveid2, Mem2.name) == 0)
		{
			sprintf(saveinfo2, "\n %s %s %d %d", Mem2.name, Mem2.passwd, Mem2.win, Mem2.lose);
			lseek(fd, (off_t)-buflength, SEEK_CUR);
			write(fd2, saveinfo2, buflength);

			close(fd2);
		}
	}
}



































