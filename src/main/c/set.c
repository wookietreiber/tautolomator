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

GHashTable* set_new (GHashFunc hash_func, GEqualFunc equal_func, GDestroyNotify destroy) {
  return g_hash_table_new_full (hash_func, equal_func, destroy, NULL);
}

void set_insert (GHashTable *set, gpointer element) {
  g_hash_table_insert (set, element, element);
}

gboolean set_contains (GHashTable *set, gpointer element) {
  return g_hash_table_lookup_extended (set, element, NULL, NULL);
}

gboolean set_remove (GHashTable *set, gpointer element) {
  return g_hash_table_remove (set, element);
}
