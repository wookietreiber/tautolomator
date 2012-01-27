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

#include "gset.h"
#include "logic.h"

/** Returns a new string stripped of all occurrences of the delimiter.
  *
  * @string: the string to strip
  * @delim:  the delimiter to strip from the string
  */
gchar* strdel(gchar* str, gchar* delim) {
  return g_strjoinv("", g_strsplit(str, delim, 0));
}

/** Returns a set of literals parsed from the given string.
  *
  * @string: the disjunction as a string,
  *          e.g. "-AvBvC"
  */
GHashTable* disjunction_to_clause(gchar* string) {
  GHashTable* clause = g_hash_set_new(g_str_hash, g_str_equal);

  gchar** literals = g_strsplit(string, OR, -1);

  int i;
  for (i = 0; literals[i] != NULL; i++) {
    g_hash_set_insert(clause, literals[i]);
  }

  return clause;
}

/** Returns a set of clauses parsed from the given string.
  *
  * @string: the conjunction of disjunctions of literals as a string,
  *          e.g. "(AvB)^(Av-B)"
  */
GHashTable* cnf_to_clauses(gchar* input) {
  GHashTable* clauses = g_hash_set_new((GHashFunc)clause_hash, (GEqualFunc)clause_equal);

  gchar** clauses_strings = g_strsplit(input, AND, -1);

  int i;
  for (i = 0; clauses_strings[i] != NULL; i++) {
    g_hash_set_insert(clauses, disjunction_to_clause(
      strdel(strdel(clauses_strings[i], "("), ")")
    ));
  }

  return clauses;
}
