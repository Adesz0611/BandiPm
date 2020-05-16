/*
 *    (C) 2020 Adam Hunyadvari
 *        <adesz@jss.hu>
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <locale.h>

#include "init.h"
#include "draw.h"
#include "input.h"
#include "types.h"
#include "curses.h"
#include "logo.h"
#include "version.h"

#ifdef __unix__
#include <signal.h>
#endif

#define ENTER 10
#define KEY_Q 113
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

#define SUCCESS 0
#define FAIL -1

int yWinMax, xWinMax, yAsk, xAsk;
char *choices[] = { "  Start  ", " Options ", "  About  ", "   Quit  " };
char *copyright = "Created by Adesz";
int highlight = 0, beatbutton = ENTER, beatbutton_options;
bool askbefq = false, askbefq_options;
struct timeval start, stop;
int ertek[10], bpmInt, i = 0, sum, a;
float millisec;

wchar_t choice;

static void usage(void);
static void clean(void);
static void emergency_exit(int signr);
static int compare (const void *p1, const void *p2) {
    return *(int*)p1 - *(int*)p2;
}

int main (int argc, const char *argv[]) 
{
    setlocale(LC_ALL, "");
    atexit(clean);

    // Arguments handling
    if(argc > 1)
    {
        if(strcmp(argv[1], "--version") == 0)
        {
            version_print();
            exit(EXIT_FAILURE);
        }

        else if(strcmp(argv[1], "--help") == 0)
        {
            usage();
            exit(EXIT_FAILURE);
        }
    }

#ifdef __unix__
#ifdef SIGWINCH
    signal(SIGWINCH, curses_resize);
#endif
    signal(SIGHUP, emergency_exit);
    signal(SIGTERM, emergency_exit);
#endif

    // Initialize curses
    curses_init();
    
    // Check terminal has colors
    if(!curses_checkTerminalHasColors())
    {
        curses_clean();
        fprintf(stderr, "Terminal does not support colors!\n");
        exit(EXIT_FAILURE);
    }

    // Config file
    FILE *conf = malloc(sizeof(*conf));

    // Load the file to the buffer
    init_configFile(conf, &askbefq, &beatbutton);
    askbefq_options = askbefq;
    beatbutton_options = beatbutton;

    // Return the max size of terminal
    getmaxyx(stdscr, curses->termY, curses->termX);

    // Check terminal size
    if(!curses_checkTerminalSize())
    {
        curses_clean();
        fprintf(stderr, "Terminal size is less than the minimum size!\n");
        exit(EXIT_FAILURE);
    }

    // Create main window
    WINDOW *win = newwin(curses->termY-2, curses->termX-6, 1, 3);
    getmaxyx(win, yWinMax, xWinMax);

    logo.filename = "logo.txt";
    logo_draw(win, curses->termX);
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
                    WINDOW *kilepes = newwin(curses->termY - 12, curses->termX - 16, 6, 8);
                    box(kilepes, 0, 0);
                    refresh();
                    wrefresh(kilepes);

                    mvwprintw(kilepes, 1, 2, "Are you sure to want to quit?");
                    getmaxyx(kilepes, yAsk, xAsk);
                    keypad(kilepes, true);

                    highlight = 0;

                    while(1)
                    {
                        draw_quitmenu(kilepes, highlight, yAsk, xAsk);
                        choice = wgetch(kilepes);
                        input_quitmenu(choice, &highlight);
                        if (choice == ENTER)
                        {
                            // If press "Igen"
                            if(highlight == 0)
                                exit(EXIT_SUCCESS);

                            // If press "Nem"
                            else if(highlight == 1)
                            {
                                input_backToMain(kilepes, win, curses->termX);
                                highlight = 3;
                                break;
                            }
                        }
                    }
                }
                else
                {
                    exit(EXIT_SUCCESS);
                }
            }

            // If press "About"
            else if(choices[highlight] == choices[2])
            {
                WINDOW *about_win = newwin((int)(curses->termY / 2), (int)(curses->termX / 2), (int)(curses->termY / 4), (int)(curses->termX / 4));
                box(about_win, 0, 0);
                char *about_text = "Simple BPM program";
                
                // Draw "About" title
                wattron(about_win, A_REVERSE);
                mvwprintw(about_win, 0, (int)(curses->termX / 2 / 2 - strlen(" About ") / 2), " About ");
                wattroff(about_win, A_REVERSE);

                // Draw the about text
                mvwprintw(about_win, 2, (int)(curses->termX / 2 / 2 - strlen(about_text) / 2), about_text);
                mvwprintw(about_win, 4, (int)(curses->termX / 2 / 2 - strlen("Press 'Q' to quit") / 2), "Press 'Q' to quit");

                wrefresh(about_win);
                refresh();
                while(1)
                {
                    choice = wgetch(about_win);
                    if(choice == KEY_Q)
                    {
                        input_backToMain(about_win, win, curses->termX);
                        break;
                    }
                }
            }

            // If press "Options"
            else if(choices[highlight] == choices[1])
            {
                WINDOW *options_win = newwin((int)(curses->termY / 2), (int)(curses->termX / 2), (int)(curses->termY / 4), (int)(curses->termX / 4));
                box(options_win, 0, 0);

                // Draw "Options" title
                wattron(options_win, A_REVERSE);
                mvwprintw(options_win, 0, (int)(curses->termX / 2 / 2 - strlen(" Options ") / 2), " Options ");
                wattroff(options_win, A_REVERSE);

                // Draw the "options" text
                mvwprintw(options_win, 2, (int)(curses->termX / 2 / 2 - strlen("Press 'Q' to quit") / 2), "Press 'Q' to quit");
                mvwprintw(options_win, 4, 3, "Ask before quit:");
                mvwprintw(options_win, 5, 3, "Beat button:");

                highlight = 0;
                keypad(options_win, true);

                // Buffer = config's value
                askbefq_options = askbefq;
                beatbutton_options = beatbutton;

                wrefresh(options_win);
                refresh();

                while(1)
                {
                    draw_options(options_win, highlight, askbefq_options, (int)(curses->termY / 2), (int)(curses->termX / 2), beatbutton_options);
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

                            input_backToMain(options_win, win, curses->termX);
                            highlight = 1;
                            break;

                        }

                        // If press "Quit"
                        else if(highlight == 3)
                        {
                            input_backToMain(options_win, win, curses->termX);
                            highlight = 1;
                            break;
                        }

                        // If press "Beatbutton"
                        else if(highlight == 1)
                        {
                            WINDOW *bb = newwin((int)(curses->termY * 0.3), (int)(curses->termX * 0.3), (int)(curses->termY * 0.35), (int)(curses->termX * 0.35));
                            box(bb, 0, 0);
                            mvwprintw(bb, 1, (int)(curses->termX * 0.3 / 2 - strlen("Press any key...") / 2), "Press any key...");
                            wrefresh(bb);
                            refresh();
                            beatbutton_options = wgetch(bb);
                            wclear(bb);
                            wrefresh(bb);
                        }
                    }
                        else if(choice == KEY_Q)
                        {
                            input_backToMain(options_win, win, curses->termX);
                            highlight = 1;
                            break;
                        }
                    }
                }

            // If you press "Start"
            else if(choices[highlight] == choices[0])
            {
                WINDOW *bpm = newwin((int)(curses->termY / 2), (int)(curses->termX / 2), (int)(curses->termY / 4), (int)(curses->termX / 4));
                box(bpm, 0, 0);
 
                // Draw "BPM" window title
                wattron(bpm, A_REVERSE);
                mvwprintw(bpm, 0, (int)(curses->termX / 2 / 2 - strlen(" BPM ") / 2), " BPM ");
                wattroff(bpm, A_REVERSE);

                // Draw window content
                mvwprintw(bpm, 2, (int)(curses->termX / 2 / 2 - strlen("Press 'Q' to quit") / 2), "Press 'Q' to quit");
                mvwprintw(bpm, 4, 2, "BPM: ");

                keypad(bpm, true);

                wgetch(bpm);
                if(!input_fillBpmArray(&i, start, stop, &millisec, &bpmInt, &ertek, bpm))
                {               
                    i = 0;
                    while(1)
                    {    
                        if(input_bpm(start, stop, &millisec, &bpmInt, &ertek, i, bpm))
                        {
                            input_backToMain(bpm, win, curses->termX);
                            highlight = 0;
                            break;
                        }
                        qsort(ertek, ARRAY_SIZE(ertek), sizeof(ertek[0]), compare);
                        sum = 0;
                        for(a = 3; a < 7; a++)
                            sum += ertek[a];
                        mvwprintw(bpm, 4, 7, "%d            ", sum / 4);
                        i++;
                        if(i == 10)
                            i = 0;
                    }
                }

                else
                {
                    input_backToMain(bpm, win, curses->termX);
                    highlight = 0;
                }
            }
        }
    }

    // Clear and close
    exit(EXIT_SUCCESS);
    return 0;
}

static void usage(void)
{
    printf("Usage: %s [options]\n", PROGRAM_NAME);
    fputs(
        "Options:\n"
        "          --help     print this help and exit\n"
        "          --version  print version and exit\n"
        ,stdout
    );
}

static void emergency_exit(int signr)
{
    (void)signr;
    exit(EXIT_FAILURE);
}

static void clean(void)
{
    curses_clean();
}
