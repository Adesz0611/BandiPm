/* Created by Adesz */
#include "main.h"
#include "init.h"
#include "draw.h"
#include "input.h"
#include <stdbool.h>

#define ENTER 10
#define KEY_Q 113

int yMax, xMax, yWinMax, xWinMax, yAsk, xAsk;
char *choices[] = { "  Start  ", " Options ", "  About  ", "   Quit  " };
char *copyright = "Created by Adesz";
int choice, highlight = 0, beatbutton, beatbutton_options;
bool askbefq = false, askbefq_options;

int main (int argc, const char *argv[]) 
{
	// Initialize
	init_screen();
	init_checkTerminalHasColors();

	// Config file
	FILE *conf;
	if((conf = fopen("bpmprog.dat", "rb")) == NULL)
	{
		conf = fopen("bpmprog.dat", "wb");
		bool askbee = 0;
		beatbutton = ENTER;
		fwrite(&askbee, sizeof(askbee), 1, conf);
		fwrite(&beatbutton, sizeof(beatbutton), 1, conf);
		fclose(conf);
		conf = fopen("bpmprog.dat", "rb");
	}
	fread(&askbefq, sizeof(askbefq), 1, conf);
	fread(&beatbutton, sizeof(beatbutton), 1, conf);
	fclose(conf);

	askbefq_options = askbefq;
	beatbutton_options = beatbutton;

	// Return the max size of terminal
	getmaxyx(stdscr, yMax, xMax);

	// Check terminal size
	if(yMax < 20 || xMax < 75) {
		endwin();
		printf("Terminal size is less than the min size!\n");
		exit(1);
	}
	
	// Create main window
	WINDOW *win = newwin(yMax-2, xMax-6, 1, 3);
	getmaxyx(win, yWinMax, xWinMax);

	logo.filename = "logo.txt";
	draw_logo(win, xMax);
	draw_creator(win, yWinMax, xWinMax, copyright);

	// Draw window border
	box(win, 0, 0);
	refresh();
	wrefresh(win);

	keypad(win, true);

	// Menu loop
	while(1)
	{
		draw_menu(win, highlight, choices, xWinMax, 4);
		choice = wgetch(win);
		input(choice, &highlight);
		if(choice == ENTER)
			{
				// If you press "Quit" button
				if(choices[highlight] == choices[3])
					{
						// Ask before quit
						if(askbefq)
						{	
								WINDOW *kilepes = newwin(yMax - 12, xMax - 16, 6, 8);
								box(kilepes, 0, 0);
								refresh();
								wrefresh(kilepes);
							
								mvwprintw(kilepes, 1, 2, "Biztosan ki szeretne lépni?");
								getmaxyx(kilepes, yAsk, xAsk);
								keypad(kilepes, true);
								
								choice = highlight = 0;

								while(1)
								{
									draw_quitmenu(kilepes, highlight, yAsk, xAsk);
									choice = wgetch(kilepes);
									input_quitmenu(choice, &highlight);
									if (choice == ENTER)
										{
											if(highlight == 0)
												{
													endwin();
													exit(1);
												}
											else if(highlight == 1)
												{
													wclear(kilepes);
													wrefresh(kilepes);
													draw_logo(win, xMax);
													box(win, 0, 0);
													refresh();
													highlight = 3;
													break;
												}
										}
								}
						}
						else
						{
							break;
						}
					}
					
					// If press "About"
					else if(choices[highlight] == choices[2])
					{
						WINDOW *about_win = newwin((int)(yMax / 2), (int)(xMax / 2), (int)(yMax / 4), (int)(xMax / 4));
						box(about_win, 0, 0);
						char *about_text = "Simple BPM porogram";
						// Draw "About" title
						wattron(about_win, A_REVERSE);
						mvwprintw(about_win, 0, (int)(xMax / 2 / 2 - strlen(" About ") / 2), " About ");
						wattroff(about_win, A_REVERSE);

						// Draw the about text
						mvwprintw(about_win, 2, (int)(xMax / 2 / 2 - strlen(about_text) / 2), about_text);
						mvwprintw(about_win, 4, (int)(xMax / 2 / 2 - strlen("Press 'Q' to quit") / 2), "Press 'Q' to quit");

						wrefresh(about_win);
						refresh();
						while(1)
						{
							choice = wgetch(about_win);
							if(choice == KEY_Q)
							{
								wclear(about_win);
								wrefresh(about_win);
								draw_logo(win, xMax);
								box(win, 0, 0);
								refresh();
								break;
							}
						}
					}

					// If press "Options"
					else if(choices[highlight] == choices[1])
					 {
						WINDOW *options_win = newwin((int)(yMax / 2), (int)(xMax / 2), (int)(yMax / 4), (int)(xMax / 4));
						box(options_win, 0, 0);

						// Draw "Options" title
						wattron(options_win, A_REVERSE);
						mvwprintw(options_win, 0, (int)(xMax / 2 / 2 - strlen(" Options ") / 2), " Options ");
						wattroff(options_win, A_REVERSE);

						// Draw the "options" text
						mvwprintw(options_win, 2, (int)(xMax / 2 / 2 - strlen("Press 'Q' to quit") / 2), "Press 'Q' to quit");
						mvwprintw(options_win, 4, 3, "Ask before quit:");
						mvwprintw(options_win, 5, 3, "Beat button:");

						highlight = 0;
						keypad(options_win, true);

						askbefq_options = askbefq;

						wrefresh(options_win);
						refresh();
						while(1)
						{
							draw_options(options_win, highlight, askbefq_options, (int)(yMax / 2), (int)(xMax / 2), beatbutton_options);
							choice = wgetch(options_win);
							input_options(choice, &highlight, &askbefq_options);
							
							if(choice == ENTER)
							{
								// If press "Apply"
								if(highlight == 2)
								{
									askbefq = askbefq_options;
									beatbutton = beatbutton_options;
									conf = fopen("bpmprog.dat", "wb");
									fwrite(&askbefq, sizeof(askbefq), 1, conf);
									fwrite(&beatbutton, sizeof(beatbutton), 1, conf);
									fclose(conf);
									
									// TODO függvényben megcsinálni!
									wclear(options_win);
									wrefresh(options_win);
									draw_logo(win, xMax);
									box(win, 0, 0);
									refresh();
									highlight = 1;
									break;

								}

								// If press "Quit"
								else if(highlight == 3)
								{
									wclear(options_win);
									wrefresh(options_win);
									draw_logo(win, xMax);
									box(win, 0, 0);
									refresh();
									highlight = 1;
									break;

								}

								// If press "Beatbutton"
								else if(highlight == 1)
								{
									WINDOW *bb = newwin((int)(yMax * 0.3), (int)(xMax * 0.3), (int)(yMax * 0.35), (int)(xMax * 0.35));
									box(bb, 0, 0);
									mvwprintw(bb, 1, (int)(xMax * 0.3 / 2 - strlen("Press any key...") / 2), "Press any key...");
									wrefresh(bb);
									refresh();
									beatbutton_options = wgetch(bb);
									wclear(bb);
									wrefresh(bb);
								}
							}
							else if(choice == KEY_Q)
								{
									wclear(options_win);
									wrefresh(options_win);
									draw_logo(win, xMax);
									box(win, 0, 0);
									refresh();
									highlight = 1;
									break;
								}
						}
					}
			}
	}

	// Clear and close
	endwin();

	printf("A beatbutton értéke: %d\n", beatbutton);
	return 0;
 }
