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

#include "gset.h"
#include "utils.h"
#include "logic.h"

int main(int argc, char** argv) {

  // -----------------------------------------------------------------------
  // fetch command line arguments
  // -----------------------------------------------------------------------

  GError* err = NULL;

  gchar* expression = NULL;
  gchar* filename   = NULL;

  GOptionEntry command_line_options[] = {
    { "input", 'i', 0, G_OPTION_ARG_STRING,   &expression,
      "read expression from string", "expression" },
    { "file",  'f', 0, G_OPTION_ARG_FILENAME, &filename,
      "read expression from file",   "/path/to/expression-file" },
    { NULL }
  };

  GOptionContext* context = g_option_context_new(
    "- test whether an expression is a tautology");

  g_option_context_add_main_entries(context, command_line_options, NULL);

  if (!g_option_context_parse(context, &argc, &argv, &err)) {
    g_print("%s\n", err->message);
    return 1;
  }
  g_clear_error(&err);

  // -----------------------------------------------------------------------
  // parse command line arguments
  // -----------------------------------------------------------------------

  if (expression == NULL && filename == NULL) {
    // no arguments -> fetch from stdin
    GString* string = g_string_new("");

    g_print("Please input a logical expression: ");

    char c;
    while ((c = getchar()) != '\n') {
      g_string_append_c(string, c);
    }

    expression = string->str;
  } else if (expression == NULL) {
    // fetch expression from file
    if (!g_file_get_contents(filename, &expression, NULL, &err)) {
      g_print("%s\n", err->message);
      return 1;
    }
    g_clear_error(&err);
  }

  expression = g_strstrip(expression);

  // -----------------------------------------------------------------------
  // execute algorithm and print solution
  // -----------------------------------------------------------------------

  if (is_satisfiable_by_resolution(cnf_to_clauses(expression)) == TRUE)
    g_print("Expression is satisfiable.\n");
  else
    g_print("Expression is not satisfiable.\n");

  g_option_context_free(context);

  return 0;
}
