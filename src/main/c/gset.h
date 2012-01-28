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

/** Returns a new hash set. */
GHashTable*   g_hash_set_new                (GHashFunc       hash_func,
                                             GEqualFunc      equal_func);

/** Returns a new hash set. */
GHashTable*   g_hash_set_new_full           (GHashFunc       hash_func,
                                             GEqualFunc      equal_func,
                                             GDestroyNotify  destroy_func);

/** Destroys the hash set. */
void          g_hash_set_destroy            (GHashTable*     hash_set);

/** Returns the size of the hash set. */
guint         g_hash_set_size               (GHashTable*     hash_set);

/** Inserts the element into the hash set. */
void          g_hash_set_insert             (GHashTable*     hash_set,
                                             gpointer        element);

/** Returns TRUE if the hash set contains the given element. */
gboolean      g_hash_set_contains           (GHashTable*     hash_set,
                                             gpointer        element);

/** Returns TRUE if the given element has been found and removed. */
gboolean      g_hash_set_remove             (GHashTable*     hash_set,
                                             gpointer        element);

/** Calls the given function for every element of the hash set. */
void          g_hash_set_foreach            (GHashTable*     hash_set,
                                             GFunc           func,
                                             gpointer        user_data);

/** Returns an iterator over all elements of the hash set. */
GList*        g_hash_set_iterator           (GHashTable*     hash_set);

/** Compares two hash sets by their size. */
gint          g_hash_set_compare_by_size    (GHashTable*     set_a,
                                             GHashTable*     set_b,
                                             gpointer        user_data);
