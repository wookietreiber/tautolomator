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

void enqueue(gpointer clause, gpointer unhandled) {
  g_queue_push_tail(unhandled, clause);
}

void add(gpointer literal, gpointer new_clause) {
  g_hash_set_insert(new_clause, literal);
}

GHashTable* join_clauses(GHashTable* clause_a, GHashTable* clause_b) {
  GHashTable* new_clause = g_hash_set_new(g_str_hash, g_str_equal);

  g_hash_set_foreach(clause_a, add, new_clause);
  g_hash_set_foreach(clause_b, add, new_clause);

  return new_clause;
}

gboolean rec_resol(GHashTable* clauses, GQueue* unhandled) {
  if (unhandled->length == 0)
    return FALSE;

  else {
    GHashTable* head = g_queue_pop_head(unhandled);

    if (g_hash_set_size(head) == 0)
      return TRUE;

    else {
      GHashTable* new_clauses = g_hash_set_new(g_str_hash, g_str_equal);

      GList* clause_iterator = g_hash_set_iterator(clauses);
      clause_iterator = g_list_remove(clause_iterator, head);

      for (; clause_iterator; clause_iterator = clause_iterator->next) {
        GHashTable* old_clause = clause_iterator->data;

        GList* literal_iterator = g_hash_set_iterator(head);

        for (; literal_iterator; literal_iterator = literal_iterator->next) {
          gchar*     literal = literal_iterator->data;
          gchar* neg_literal = literal_negated(literal);

          if (g_hash_set_contains(old_clause, neg_literal)) {
            GHashTable* new_clause = join_clauses(head, old_clause);

            g_hash_set_remove(new_clause, literal);
            g_hash_set_remove(new_clause, neg_literal);

            if ( ! g_hash_set_contains(clauses, new_clause) )
              g_hash_set_insert(new_clauses, new_clause);
          }
        }
      }

      g_hash_set_foreach(new_clauses, enqueue, unhandled);

      return rec_resol(clauses, unhandled);
    }
  }
}

gboolean resolution(GHashTable* clauses) {
  GQueue* unhandled = g_queue_new();
  g_hash_set_foreach(clauses, enqueue, unhandled);

  gboolean result = rec_resol(clauses, unhandled);

  g_queue_free(unhandled);

  return result;
}
