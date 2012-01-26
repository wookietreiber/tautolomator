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

/** Returns a new hash set.
  *
  * @hash_func:  function to create hashes from elements
  * @equal_func: function to compare elements
  */
GHashTable* g_hash_set_new(GHashFunc hash_func, GEqualFunc equal_func) {
  return g_hash_table_new(hash_func, equal_func);
}

/** Returns a new hash set.
  *
  * @hash_func:    function to create hashes from elements
  * @equal_func:   function to compare elements
  * @destroy_func: function to free memory allocated for the element
  */
GHashTable* g_hash_set_new_full(GHashFunc hash_func, GEqualFunc equal_func, GDestroyNotify destroy_func) {
  return g_hash_table_new_full(hash_func, equal_func, destroy_func, NULL);
}

/** Returns the size of the hash set.
  *
  * @hash_set: a hash set
  */
guint g_hash_set_size(GHashTable* hash_set) {
  return g_hash_table_size(hash_set);
}

/** Inserts the element into the hash set.
  *
  * @hash_set: a hash set
  * @element:  the element to insert
  */
void g_hash_set_insert(GHashTable* hash_set, gpointer element) {
  g_hash_table_insert(hash_set, element, element);
}

/** Returns TRUE if the hash set contains the given element.
  *
  * @hash_set: a hash set
  * @element:  the element to check for
  */
gboolean g_hash_set_contains(GHashTable* hash_set, gpointer element) {
  return g_hash_table_lookup_extended(hash_set, element, NULL, NULL);
}

/** Returns TRUE if the given element has been found and removed.
  *
  * @hash_set: a hash set
  * @element:  the element to remove
  */
gboolean g_hash_set_remove(GHashTable* hash_set, gpointer element) {
  return g_hash_table_remove(hash_set, element);
}

/** Calls the given function for every element of the hash set.
  *
  * @hash_set:  a hash set
  * @func:      function to call for every element
  * @user_data: user data to pass to the function
  */
void g_hash_set_foreach(GHashTable* hash_set, GFunc func, gpointer user_data) {
  g_list_foreach(g_hash_table_get_keys(hash_set), func, user_data);
}

/** Returns an iterator over all elements of the hash set.
  *
  * @hash_set: a hash set
  */
GList* g_hash_set_iterator(GHashTable* hash_set) {
  return g_hash_table_get_keys(hash_set);
}
