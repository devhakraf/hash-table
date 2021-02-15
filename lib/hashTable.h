/**
 * @author 		Abdelhakim RAFIK
 * @version 	v1.0.1
 * @license 	MIT License
 * @Copyright 	Copyright (c) 2021 Abdelhakim RAFIK
 * @date 		Feb 2021
 */

#include <stdlib.h>
#include <string.h>

/* hash table node definition */
typedef struct _node
{
	unsigned char *key;
	void *value;
	struct _node *next;
} ht_node_t;

/* hash table definition */
typedef struct
{
	unsigned int size;
	unsigned int count;
	ht_node_t **items;
} ht_table_t;


/**
 * create new hash table with given size
 * @param  size 	items table size
 * @return 			pointer to creates hash table
 */
ht_table_t* ht_create(int size);

/**
 * create items table index from given key
 * @param  key 		key value
 * @return 			index of items table between 0 and table size-1
 */
unsigned int ht_hash(unsigned int maxSize, unsigned char *key);

/**
 * inset new element to hash table by given key
 * @param  table 	pointer to created hash table
 * @param  key 		key for value to insert
 * @param  value 	element to be inserted
 * @param  size 	size of element in bytes
 * @return 			1: inserted successfully
 * 					0: error occured while inserting value
 */
unsigned char ht_insert(ht_table_t* table, unsigned char *key, void *value, size_t size);

/**
 * find associated node to given key
 * @param  table 	pointer to hash table
 * @param  key 		key associated to the node
 * @param  index 	index of found node in items table
 * @param  prev 	pointer to previous node
 * @return 			node pointer if found or NULL otherwise
 */
ht_node_t* ht_find_node(ht_table_t* table, unsigned char *key, unsigned int *index, ht_node_t **prev);

/**
 * find value in hash table by given key
 * @param table 	pointer to hash table
 * @param key 		key of the value searching
 */
void* ht_find(ht_table_t* table, unsigned char *key);

/**
 * delete value by given key
 * @param  table 	pointer to hash table
 * @param  key 		value's key to delete
 * @return 			1: deleted successfully
 * 					0: error occured while deleting the value
 */
unsigned char ht_delete(ht_table_t* table, unsigned char *key);

/**
 * delete all table items
 * @param table 	pointer to hash table
 */
unsigned char ht_delete_all(ht_table_t* table);

/**
 * free allocated memory for given hash table
 * @param  table 	pointer to hash table
 */
unsigned char ht_free(ht_table_t* table);
