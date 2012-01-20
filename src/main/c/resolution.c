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
#include "set.h"

void enqueue(gpointer clause, gpointer unhandled) {
  g_queue_push_tail(unhandled, clause);
}

gboolean rec_resol(GHashTable* clauses, GQueue* unhandled) {
  if (unhandled->length == 0)
    return FALSE;

  else {
    GHashTable* head = g_queue_pop_head(unhandled);

    if (g_hash_set_size(head) == 0)
      return TRUE;

    else {
      GList* iter = g_hash_set_iterator(clauses);
      iter = g_list_remove(iter, head);

      for (; iter; iter = iter->next) {
        // find resolvent
        // if clauses not contains resolvent add to clauses and unhandled
      }

      return rec_resol(clauses, unhandled);
    }
  }
}

gboolean resolution(GHashTable* clauses) {
  GQueue* q = g_queue_new();
  g_hash_set_foreach(clauses, enqueue, q);

  gboolean result = rec_resol(clauses, q);

  g_queue_free(q);

  return result;
}
