#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <iomanip>
#include <iostream>

// TERMINAL MESSAGES COLORS
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

void display_welcome_message(void);
void display_usage(void);
void display_error_usage(void);
void display_add_contact(void);
void display_contact_added_successfully(unsigned int index);
void display_error_add_contact(void);
void display_search(void);
void display_no_contact_created_yet(void);
void display_columns(void);
void display_search_prompt(void);
void display_error_searched_index(void);
void display_error_searched_contact_doesnt_exist(void);
void display_exit(void);

#endif