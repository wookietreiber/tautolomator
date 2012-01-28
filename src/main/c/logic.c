/* **************************************************************************
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

/** Returns a new string containing the negated literal.
  *
  * @literal: the literal to negate
  */
gchar* negate_literal(const gchar* literal) {
  gchar* negated_literal = NULL;

  if (g_str_has_prefix(literal, NOT)) {
    negated_literal = g_strdup(literal);
    negated_literal++;
  } else
    negated_literal = g_strconcat(NOT, literal, NULL);

  return negated_literal;
}

/** Enqueues the element into a queue.
  *
  * @element: element to enqueue
  * @queue:   a queue
  */
static void enqueue(gpointer element, gpointer queue) {
  g_queue_push_tail(queue, element);
}

/** Inserts the element into a hash set.
  *
  * @element:  element to insert
  * @hash_set: a hash set
  */
static void insert(gpointer element, gpointer hash_set) {
  g_hash_set_insert(hash_set, element);
}

static gboolean rec_resol(GHashTable* clauses, GQueue* unhandled_clauses) {
  g_queue_sort(unhandled_clauses, (GCompareDataFunc)g_hash_set_compare_by_size, NULL);

  if (unhandled_clauses->length == 0)
    return TRUE;

  else {
    GHashTable* unhandled_clause = g_queue_pop_head(unhandled_clauses);

    g_print("  handling: %s\n", clause_to_string(unhandled_clause));

    GHashTable* new_clauses = g_hash_set_new((GHashFunc)clause_hash, (GEqualFunc)clause_equal);

    GList* clause_iterator = g_hash_set_iterator(clauses);
    clause_iterator = g_list_remove(clause_iterator, unhandled_clause);

    for (; clause_iterator; clause_iterator = clause_iterator->next) {
      GHashTable* old_clause = clause_iterator->data;

      GList* literal_iterator = g_hash_set_iterator(unhandled_clause);

      for (; literal_iterator; literal_iterator = literal_iterator->next) {
        gchar*     literal = literal_iterator->data;
        gchar* neg_literal = negate_literal(literal);

        if (g_hash_set_contains(old_clause, neg_literal)) {
          GHashTable* new_clause_a = g_hash_set_new(g_str_hash, g_str_equal);
          GHashTable* new_clause_b = g_hash_set_new(g_str_hash, g_str_equal);

          g_hash_set_foreach(unhandled_clause, insert, new_clause_a);
          g_hash_set_foreach(      old_clause, insert, new_clause_b);

          g_hash_set_remove(new_clause_a,     literal);
          g_hash_set_remove(new_clause_b, neg_literal);

          GHashTable* new_clause = g_hash_set_new(g_str_hash, g_str_equal);

          g_hash_set_foreach(new_clause_a, insert, new_clause);
          g_hash_set_foreach(new_clause_b, insert, new_clause);

          if ((!g_hash_set_contains(clauses,     new_clause)) &&
              (!g_hash_set_contains(new_clauses, new_clause))) {

            g_print("    ... and %s with literal %s -> %s\n",
              clause_to_string(old_clause),
              literal,
              clause_to_string(new_clause)
            );

            if (g_hash_set_size(new_clause) == 0) {
              g_print("Found empty clause.\n");
              return FALSE;
            }

            g_hash_set_insert(new_clauses, new_clause);
          }
        }
      }
    }

    g_hash_set_foreach(new_clauses, insert,  clauses);
    g_hash_set_foreach(new_clauses, enqueue, unhandled_clauses);

    g_print("  clauses are now: %s\n", clauses_to_string(clauses));

    return rec_resol(clauses, unhandled_clauses);
  }
}

/** Returns TRUE if the CNF is satisfiable using resolution.
  *
  * @clauses: the CNF as a set of clauses
  */
gboolean is_satisfiable_by_resolution(GHashTable* clauses) {
  g_print("clauses: %s\n", clauses_to_string(clauses));

  GQueue* unhandled_clauses = g_queue_new();
  g_hash_set_foreach(clauses, enqueue, unhandled_clauses);

  gboolean result = rec_resol(clauses, unhandled_clauses);

  g_queue_free(unhandled_clauses);

  return result;
}
