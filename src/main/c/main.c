/****************************************************************************
 *                                                                          *
 *  Copyright (C)  2012  Max Brauer, Christian Krause                       *
 *                                                                          *
 *  Max Brauer       <max.brauer@it2009.ba-leipzig.de>                      *
 *  Christian Krause <christian.krause@it2009.ba-leipzig.de>                *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 *  This file is part of 'tautolomator'.                                    *
 *                                                                          *
 *  This project is free software: you can redistribute it and/or modify    *
 *  it under the terms of the GNU General Public License as published by    *
 *  the Free Software Foundation, either version 3 of the License, or       *
 *  any later version.                                                      *
 *                                                                          *
 *  This project is distributed in the hope that it will be useful,         *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *  GNU General Public License for more details.                            *
 *                                                                          *
 *  You should have received a copy of the GNU General Public License       *
 *  along with this project. If not, see <http://www.gnu.org/licenses/>.    *
 *                                                                          *
 ****************************************************************************/


#include <stdio.h>
#include <glib.h>

#include "set.h"

#define AND "^"
#define OR  "v"
#define NOT "-"

void remove_brackets(char* inputstring) {
  int i;
  int len = strlen(inputstring);
  for (i = 0; i <= len; i++) {
    if(inputstring[i] == '(' ||
        inputstring[i] == ')'){
      inputstring[i] = ' ';
    }
  }
  g_print("The string without brackets: %s\n", inputstring);
}

void get_input_as_clauses() {
  char inputstring;
  g_print("Please insert a logical statement as conjunctive normal form: ");
  scanf("%s", &inputstring);
  g_print("The inserted string is: %s\n", &inputstring);
  remove_brackets(&inputstring);  
}

int main(int argc, char** argv) {
  get_input_as_clauses();
  return 0;
}