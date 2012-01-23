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


#include <glib.h>
#include <glib/gstdio.h>

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

int main(int argc, char** argv) {
  GError* error = NULL;

  gchar* input;
  gchar* input_string   = NULL;
  gchar* input_filename = NULL;

  GOptionEntry command_line_options[] = {
    { "input", 'i', 0, G_OPTION_ARG_STRING,   &input_string,   "read expression from string", "expression"          },
    { "file",  'f', 0, G_OPTION_ARG_FILENAME, &input_filename, "read expression from file",   "/path/to/input-file" },
    { NULL }
  };

  GOptionContext* context = g_option_context_new(
    "- test whether an expression is a tautology");

  g_option_context_add_main_entries(context, command_line_options, NULL);

  if (!g_option_context_parse(context, &argc, &argv, &error)) {
    g_print("%s\n", error->message);
    return 1;
  }
  g_clear_error(&error);

  if (input_string == NULL && input_filename == NULL) {
    GString* string = g_string_new("");

    g_print("Please input a logical expression: ");

    char c;
    while ((c = getchar()) != '\n') {
      g_string_append_c(string, c);
    }

    input = string->str;
  } else if (input_string == NULL) {
    if (!g_file_get_contents(input_filename, &input, NULL, &error)) {
      g_print("%s\n", error->message);
      return 1;
    }
    g_clear_error(&error);
  } else {
    input = input_string;
  }

  input = g_strstrip(input);

  // TODO convert raw input to set

  g_option_context_free(context);

  return 0;
}
