#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <deque>

using namespace std;

extern int current_index;
extern deque<string> his;

#define MAXLEN 5 // Maximum length of deque

void save_to_history(string& command);
int getch();
void get_history(string &command);

#endif // HISTORY_H