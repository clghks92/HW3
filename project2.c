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
#define ID 13
#define PASSWARD 14

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




struct _Mem {
	char name[IDPWLENGTH];
	char passwd[IDPWLENGTH];
	int win, lose;
	struct _Mem *link;
};
typedef struct _Mem MEM;

int main_menu();
int sign_up(MEM *p);
int sign_in(MEM *p);
int withdrawal(MEM *p);
int sign_after(MEM *p);
int statistics(MEM *p);
int playin();
void init_scr();

int person = 0; //회원수


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
	MEM *p;
	p = (MEM *)malloc(sizeof(MEM));
	p->link = NULL;

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
                                        sign_in(p);
                                }
                                else if (sel_menu == SIGN_UP){
                                        sign_up(p);
                                }
                                else if (sel_menu == EXIT){
                                        exit(1);
                                }
                                break;

		}
	}
}

int sign_up(MEM *p){
	werase(stdscr);
	char key;
	char id[IDPWLENGTH];
	char passwd[IDPWLENGTH];
	int i =0;
	int sel_signup = SIGN_UP;
	char ch;
	

	while(p->link != NULL)
		p=p->link;

	WINDOW *upMenu, *downMenu;

        topbottomWindow(upMenu, downMenu);

	 attron(COLOR_PAIR(1));
	 mvprintw(5, 28, "ID: ");
	 mvprintw(7, 22, "PASSWORD: ");

      	while(1){

		p->link = (MEM *)malloc(sizeof(MEM));
		p = p->link;


		attron(COLOR_PAIR(2));

	       	mvprintw(19, 5, "SIGN UP");
		mvprintw(19, 72, "BACK");

                re:

		move(5, 31);
		getstr(id);
		mvscanw(7, 31, "%d", passwd);
		



		attron(A_STANDOUT | A_UNDERLINE);

		switch(sel_signup){
			case ID:
				
				mvprintw(5, 28, "ID: ");
				move(5, 31 + strlen(id) );
				break;
			case PASSWARD:
				
				mvprintw(7, 22, "PASSWORD: ");
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
						break;

					case ENTER:
						if(sel_signup == SIGN_UP){
							if(person<MEM_COUNT){
								       if(strcmp(p->name, id) == 0){
                                                                                      mvprintw(22, 1, "%s has already exist! (please any key..)", id);
                                                                                      getch();

                                                                                      goto re;
                                                                              }
                                                                              else {
                                                                                      person++;
                                                                                      mvprintw(22, 1, "Welcome to OTHELLO world!(please any key)");                                                                      
										      strcpy(p->name, id);
                                                                                      strcpy(p->passwd, passwd);
										      getch();
										      sel_signup = SIGN_UP; 
                                                                              }
                                                                      } 
						}
						

						else if(sel_signup == BACK){
							main_menu();
						}
						break;
				}
				}
		
}



	                                               

                                               
                                                       
                                                                                 
                                                                              
                                                                                    
                                                                                      
                                                                                      
                                                                            
                                                                              
int sign_in(MEM *p)
{
	werase(stdscr);
	char id[IDPWLENGTH];
	char passwd[IDPWLENGTH];
	int i;
	char key, ch;
	int sel_signin = SIGN_IN;

	WINDOW *upMenu, *downMenu;
        topbottomWindow(upMenu, downMenu);



	while(1){

		attron(COLOR_PAIR(2));
		mvprintw(5, 26, "ID: ");
                mvprintw(7, 20, "PASSWORD: ");

		mvprintw(19, 5, "SIGN IN");
		mvprintw(19, 72, "BACK");

                re:
		mvscanw(5, 31, "%s", id);
		mvscanw(7, 31, "%d", passwd);
	
		attron(A_STANDOUT | A_UNDERLINE);

		switch(sel_signin){
			case ID:
				curs_set(1);
				mvprintw(5, 26, "ID: ");
				break;
			case PASSWARD:
				curs_set(1);
				mvprintw(7, 20, "PASSWARD: ");
				break;
                        case SIGN_IN:
				curs_set(0);
                                mvprintw(13, 5, "SIGN_UP");
                                break;
                        case BACK:
				curs_set(0);
                                mvprintw(13, 40, "BACK");
                                break;

                }
		attroff(A_STANDOUT | A_UNDERLINE);

		refresh();

		key = getchar();

		switch(key){
			case RIGHT:
				if(sel_signin == SIGN_IN){
					sel_signin == BACK;

				}

				else if (sel_signin == BACK){
					sel_signin == SIGN_IN;
				}
				break;
				
			case LEFT:
				if(sel_signin = SIGN_IN){
					sel_signin = BACK;
				}

			        else if (sel_signin == BACK){
					 sel_signin == SIGN_IN;              
                                }
                                break;
			case ENTER:
				if(sel_signin == SIGN_IN){
				  if(strcmp(p->name, id) != 0){
				        mvprintw(22, 1, "LOGIN FAILED");
                                        getch();
                                        goto re;
                                  }
				}

                                else {
                                       person++;
                                       mvprintw(22, 1, "LOGIN SUCCESS");
				       statistics(p);
				}                                 
                                }



		}
	}


int withdrawal(MEM *p)
{
        werase(stdscr);
        char id[IDPWLENGTH];
        char passwd[IDPWLENGTH];
        int i;
        char key, ch;
        int sel_with = WITHDRAWAL;
	MEM *temp;

        WINDOW *upMenu, *downMenu;
        topbottomWindow(upMenu, downMenu);

	while(1){
		attron(COLOR_PAIR(2));
                mvprintw(19, 5, "WITHDRAWAL");
                mvprintw(19, 72, "BACK");

		mvprintw(5, 28, "PLAYER ID: ");
		mvprintw(7, 20, "PASSWARD: ");

                start:
		mvscanw(5, 31, "%s", id);
                mvscanw(7, 31, "%d", passwd);
    
		attron(A_STANDOUT | A_UNDERLINE);

		switch(sel_with){
			case ID:
				curs_set(1);
				mvprintw(5, 28, "PLAYER ID: ");
				break;
			case PASSWARD:
				curs_set(1);
				mvprintw(7, 20, "PASSWARD: ");
				break;
                        case SIGN_IN:
				curs_set(0);
                                mvprintw(13, 5, "SIGN_UP");
                                break;
                        case BACK:
				curs_set(0);
                                mvprintw(13, 40, "BACK");
                                break;

                }

		attroff(A_STANDOUT | A_UNDERLINE);

		refresh();

		key = getchar();

		switch(key){
			case ENTER:
				if(sel_with == 	WITHDRAWAL){
				           while(p->link != NULL){
							temp = p;
							p = p->link;
					   if(strcmp(p->name, id) == 0){
						   if(strcmp(p->passwd, passwd) == 0){
							   temp->link = p->link;
							   free(p);
							   mvprintw(22, 1, "%d delete", id);
							   break;

						   }
						   else {
							   mvprintw(22, 1, "wrong passwd");
					           }
			                  }
					 
					   else {
						   mvprintw(22, 1, "%d is not exist", id);
						   getch();
						   goto start;
					   }
					}
				}
				
				else if(sel_with == BACK){
					delwin(upMenu);
                                        delwin(downMenu);
                                        sign_after(p);
				}
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
		}
	}
}

int sign_after(MEM *p)
{
	werase(stdscr);
        char id[IDPWLENGTH];
        char passwd[IDPWLENGTH];
        int i;
        char key, ch;
        int sel_signafter = SIGN_AFTER;

        WINDOW *upMenu, *downMenu;
        topbottomWindow(upMenu, downMenu);


	while(1){
		attron(COLOR_PAIR(2));
                mvprintw(13, 5, "PLAY");
                mvprintw(13, 20, "SIGN OUT");
                mvprintw(13, 40, "WITHDRAWAL");

		mvprintw(5, 17, "PLAYER ID: %s", p->name);

		attron(A_STANDOUT | A_UNDERLINE);

		switch(sel_signafter){
			case PLAY:
				
				mvprintw(13, 5, "PLAY");
				break;
			case SIGN_OUT:
				
				mvprintw(13, 20, "SIGN OUT");
				break;
			case BACK:
				
				mvprintw(13, 40, "BACK");
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
					statistics(p);
				}
				else if (sel_signafter == SIGN_OUT){
					delwin(upMenu);
                                        delwin(downMenu);
					sign_in(p);
				}
				else if(sel_signafter == BACK){
					delwin(upMenu);
                                        delwin(downMenu);
					withdrawal(p);
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


int statistics(MEM *p)
{
        werase(stdscr);
        char id[IDPWLENGTH];
        char passwd[IDPWLENGTH];
        int i;
        char key, ch;
        int sel_stat = STATISTICS;

        WINDOW *upMenu, *downMenu;
        topbottomWindow(upMenu, downMenu);

        attron(COLOR_PAIR(1));
	mvprintw(5, 20, "PLAYER ID : %s", p->name);
        mvprintw(7, 23, "STATISTICS");
        mvprintw(9, 15, "WIN : %s / LOSE : %s (%ld)", p->win, p->lose, (p->win * 100) / (p->win + p->lose));


	while(1){
		attron(COLOR_PAIR(2));

	        mvprintw(19, 39, "OK");


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
					playin(p);
				}
		}
	}
}

int playin(MEM *p)
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

	int first, second;

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



	WINDOW *rightWindow, *leftWindow;
	rightWindow = subwin(stdscr,13,18,0,35);
	wbkgd(rightWindow, COLOR_PAIR(2));
	attron(COLOR_PAIR(1));

	while(1){

		attron(COLOR_PAIR(1));

		mvprintw(0, 5, "+---+---+---+---+---+---+");
		mvprintw(1, 5, "| %c | %c | %c | %c | %c | %c |",game[1][7],game[1][11],game[1][15],game[1][19],game[1][23],game[1][27]);
		mvprintw(2, 5, "+---+---+---+---+---+---+");
		mvprintw(3, 5, "| %c | %c | %c | %c | %c | %c |",game[3][7],game[3][11],game[3][15],game[3][19],game[3][23],game[3][27]);
		mvprintw(4, 5, "+---+---+---+---+---+---+");
		mvprintw(5, 5, "| %c | %c | %c | %c | %c | %c |",game[5][7],game[5][11],game[5][15],game[5][19],game[5][23],game[5][27]);
		mvprintw(6, 5, "+---+---+---+---+---+---+");
		mvprintw(7, 5, "| %c | %c | %c | %c | %c | %c |",game[7][7],game[7][11],game[7][15],game[7][19],game[7][23],game[7][27]);
		mvprintw(8, 5, "+---+---+---+---+---+---+");
		mvprintw(9, 5, "| %c | %c | %c | %c | %c | %c |",game[9][7],game[9][11],game[9][15],game[9][19],game[9][23],game[9][27]);
		mvprintw(10, 5, "+---+---+---+---+---+---+");
		mvprintw(11, 5, "| %c | %c | %c | %c | %c | %c |",game[11][7],game[11][11],game[11][15],game[11][19],game[11][23],game[11][27]);
		mvprintw(12, 5, "+---+---+---+---+---+---+");

		key = getchar();

		switch(key){
			case 'x':
				sel_play == EXIT;
				break;
			case 'g':
				x = 15;
				y = 5;
			case UP:
				if(sel_play == EXIT){
					sel_play == EXIT;
				}
				else{
					y = y-2;
					 if(y == -1){
						 y = 11;
					 }
				}
				break;
			case DOWN:
				if(sel_play == EXIT){
					sel_play == EXIT;
				}
				else{
					y = y+2;
					if(y == 13){
						y =1;
					}
				}
				break;
			case RIGHT:
				if(sel_play == EXIT){
					sel_play == EXIT;
				}
				else{
					x =x+4;
					if(x == 31){
						x=7;
					}

				}
				break;
			case LEFT:
				if(sel_play == EXIT){
                                        sel_play == EXIT;
                                }
				else{
					x = x-4;
					if(x == 3){
						x=27;
					}
				}
				break;

			case ENTER:
				if(sel_play == EXIT){
					sign_after(p);
				}
		}
	}
}

int main(){
	init_scr();

	MEM *p;
	p = (MEM *)malloc(sizeof(MEM));
	p->link = NULL;


	int menu = MAINMENU;

	while(menu != EXIT){
		switch(menu){
			case MAINMENU:
			      menu =  main_menu();
			      break;

			case SIGN_UP:
			      menu = sign_up(p);
			      break;

			case SIGN_IN:
			      menu = sign_in(p);
			      break;

		        case WITHDRAWAL:
			      menu = withdrawal(p->link);
			      break;

		        case SIGN_AFTER:
			     menu = sign_after(p);
			     break;

		        case STATISTICS:
			     menu = statistics(p);
			     break;

		        case INGAME:
			     menu = playin(p);
			     break;
			   }
	}
        endwin();
        return 0;
}










