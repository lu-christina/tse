/*
 * index.h - header file for TSE index module
 *
 * An *index* is a modified hashtable, which is a set of (key, item) pairs. The
 * index uses (const char, counters_t) in order to keep track of counters. It 
 * is efficient for large collections.
 *
 * Christina Lu, August 2017
 */

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdbool.h>

/**************** global types ****************/
typedef hashtable_t index_t; // opaque to users of the module

/**************** functions ****************/

/* Create a new (empty) index; return NULL if error. */
index_t *index_new(const int num_slots);

/* Insert counters, idnetified by key (string), into the given index.
 * The key string is copied for use by the index; that is, the module
 * is responsible for allocating memory for a copy of the key string, and
 * later deallocating that memory; thus, the caller is free to re-use or
 * deallocate its key string after this call.
 * Re turn false if key exists in index, any parameter is NULL, or error;
 * return true iff new counters was inserted.
 */
bool index_insert(index_t *ht, const char *key, counters_t *ct);

/* Return the item associated with the given key;
 * return NULL if hashtable is NULL, key is NULL, key is not found.
 */
counters_t *index_find(index_t *ht, const char *key);

/* Delete the whole index; ignore NULL index.
 */
void index_delete(index_t *ht);

/* Writes the data structure in the memory to an external file. Takes index
 * to be written to the file, and path name of file to write to. Writes in the
 * format "word doc_id count [doc_id count]..." one line per word.
 * Returns true upon sucess, false if error.
 */
bool index_save(index_t *ht, char* filename);

/* Loads information from a file and builds an index data structure in the
 * memory. Returns the index structure.
 */
index_t *index_load(char* filename);

#endif // __INDEX_H
