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
#include "utils.h"

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
  * @str: the disjunction as a string, e.g. "-AvBvC"
  */
GHashTable* disjunction_to_clause(gchar* str) {
  GHashTable* clause = g_hash_set_new(g_str_hash, g_str_equal);

  gchar** literals = g_strsplit(str, OR, -1);

  int i;
  for (i = 0; literals[i] != NULL; i++) {
    g_hash_set_insert(clause, literals[i]);
  }

  return clause;
}

/** Returns a set of clauses parsed from the given string.
  *
  * @str: the conjunction of disjunctions of literals as a string,
  *       e.g. "(AvB)^(Av-B)"
  */
GHashTable* cnf_to_clauses(gchar* str) {
  GHashTable* clauses = g_hash_set_new((GHashFunc)clause_hash, (GEqualFunc)clause_equal);

  gchar** clauses_strings = g_strsplit(str, AND, -1);

  int i;
  for (i = 0; clauses_strings[i] != NULL; i++) {
    g_hash_set_insert(clauses, disjunction_to_clause(
      strdel(strdel(clauses_strings[i], "("), ")")
    ));
  }

  return clauses;
}

  // -----------------------------------------------------------------------
  // hash functions
  // -----------------------------------------------------------------------

/** Returns a hash value corresponding to the given clause.
  *
  * @clause: clause from which to create the hash value
  */
guint clause_hash(GHashTable* clause) {
  guint hash = 0;

  GList* literal_iterator = g_hash_set_iterator(clause);
  for (; literal_iterator; literal_iterator = literal_iterator->next) {
    gchar* literal = literal_iterator->data;

    if (g_str_has_prefix(literal, NOT))
      hash = hash + g_str_hash(literal)*42;
    else
      hash = hash + g_str_hash(literal);
  }

  return hash;
}

/** Returns TRUE if the two clauses match.
  *
  * @clause_a: a clause
  * @clause_b: another clause
  */
gboolean clause_equal(GHashTable* clause_a, GHashTable* clause_b) {
  return clause_hash(clause_a) == clause_hash(clause_b);
}

  // -----------------------------------------------------------------------
  // to string functions
  // -----------------------------------------------------------------------

/** Returns the string representation of the clause.
  *
  * @clause: a clause
  */
gchar* clause_to_string(GHashTable* clause) {
  GString* string = g_string_new("{ ");

  GList* literal_iterator = g_hash_set_iterator(clause);
  for (; literal_iterator; literal_iterator = literal_iterator->next) {
    g_string_append(string, literal_iterator->data);
    g_string_append_c(string, ',');
  }
  g_string_truncate(string, string->len - 1);
  g_string_append(string, " }");

  return g_string_free(string, FALSE);
}

/** Returns the string representation of the set of clauses.
  *
  * @clauses: a set of clauses
  */
gchar* clauses_to_string(GHashTable* clauses) {
  GString* string = g_string_new("{ ");

  GList* clause_iterator = g_hash_set_iterator(clauses);
  for (; clause_iterator; clause_iterator = clause_iterator->next) {
    g_string_append(string, clause_to_string(clause_iterator->data));
    g_string_append_c(string, ',');
  }
  g_string_truncate(string, string->len - 1);
  g_string_append(string, " }");

  return g_string_free(string, FALSE);
}
