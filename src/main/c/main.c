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
#include <string.h>
#include <glib.h>

#include "resolution.h"
#include "set.h"
#include "logic.h"

gchar* strdel(gchar* str, gchar* delim) {
  return g_strjoinv("", g_strsplit(str, delim, 0)); 
}

void generate_clauses(gchar* conjunctionstring) {
  gchar** clauseslist;
  clauseslist = g_strsplit(conjunctionstring, OR, 0);
  g_strfreev(clauseslist);
  //GHashTable* clausesset = g_hash_set_new();
}

void get_input_as_clauses() {
  gchar inputstring[200];
  gchar* conjunctionstring;
  g_print("Please insert a logical statement as conjunctive normal form: ");
  scanf("%200s", inputstring);
  g_print("The inserted string is: %200s\n", inputstring);
  conjunctionstring = strdel(strdel(inputstring, "("), ")");
  g_print("The string without brackets: %s\n", conjunctionstring);
  generate_clauses(conjunctionstring);
}

int main(int argc, char** argv) {
  get_input_as_clauses();
  return 0;
}
