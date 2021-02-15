/**
 * @author 		Abdelhakim RAFIK
 * @version 	v1.0.1
 * @license 	MIT License
 * @Copyright 	Copyright (c) 2021 Abdelhakim RAFIK
 * @date 		Feb 2021
 */

#include "hashTable.h"

/**
 * create new hash table with given size
 * @param  size 	items table size
 * @return 			pointer to creates hash table
 */
ht_table_t* ht_create(int size)
{
	// check given table items size, should be greather than 0
	if(size <= 0) return NULL;
	// create new hash table
	ht_table_t* table = (ht_table_t*) malloc(sizeof(ht_table_t));
	table->size = size;
	table->count = 0;
	// create items table as pointer's table to nodes
	table->items = (ht_node_t**) malloc(size * sizeof(ht_node_t*));

	// set all items pointers to NULL
	for(int i=0; i<size; ++i)
		table->items[i] = NULL;

	// return created table
	return table;
}

/**
 * create items table index from given key
 * @param  key 		key value
 * @return 			index of items table between 0 and table size-1
 */
unsigned int ht_hash(unsigned int maxSize, unsigned char *key)
{
	unsigned int hashedKey = 1;
	// create hash from key
	for(; *key != '\0'; ++key)
		hashedKey = hashedKey * 19 + *key;
	// return created index
	return hashedKey % maxSize;
}

/**
 * inset new element to hash table by given key
 * @param  table 	pointer to created hash table
 * @param  key 		key for value to insert
 * @param  value 	element to be inserted
 * @param  size 	size of element in bytes
 * @return 			1: inserted successfully
 * 					0: error occured while inserting value
 */
unsigned char ht_insert(ht_table_t* table, unsigned char *key, void *value, size_t size)
{
	// check table and key are not NULL
	if(!table || !key) return 0;
	// index from key
	unsigned int index;
	// check whether the element with associated key already in table and get generated index
	ht_node_t *newNode = ht_find_node(table, key, &index, NULL);
	if(newNode)
	{
		// reallocate memory for new content value
		newNode->value = (void*) realloc(newNode->value, size);
		// copy value to allocated node value memory
		memcpy(newNode->value, value, size);
	}
	else
	{
		// create new node
		newNode = (ht_node_t*) malloc(sizeof(ht_node_t));
		// create node key and copy it's value
		newNode->key = (char*) malloc(strlen(key) + 1);
		strcpy(newNode->key, key);
		// create node value memory
		newNode->value = (void*) malloc(size);
		// copy value to allocated node value memory
		memcpy(newNode->value, value, size);
		// if index position is not empty link nodes
		if(table->items[index] != NULL)
			newNode->next = table->items[index];
		else
			newNode->next = NULL;
		// add created node to items table
		table->items[index] = newNode;
		// increment table count
		++table->count;
	}
	return 1;
}

/**
 * find associated node to given key
 * @param  table 	pointer to hash table
 * @param  key 		key associated to the node
 * @param  index 	index of found node in items table
 * @param  prev 	pointer to previous node
 * @return 			node pointer if found or NULL otherwise
 */
ht_node_t* ht_find_node(ht_table_t* table, unsigned char *key, unsigned int *index, ht_node_t **prev)
{
	// get index for given key
	unsigned int _index = ht_hash(table->size, key);
	if(index)
		*index = _index;
	// get head items at index position
	ht_node_t* currentNode = table->items[_index];
	ht_node_t* _prev = NULL;
	// search in linked array nodes until a NULL pointer
	while(currentNode)
	{
		if(strcmp(currentNode->key, key) == 0)
			break;
		// go to next linked node
		_prev = currentNode;
		currentNode = currentNode->next;
	}

	if(currentNode)
	{
		if(prev)
			*prev = _prev;
		// return found node
		return currentNode;
	}
	// value associated with the key not found
	return NULL;
}

/**
 * find value in hash table by given key
 * @param table 	pointer to hash table
 * @param key 		key of the value searching
 */
void* ht_find(ht_table_t* table, unsigned char *key)
{
	// check table and key are not NULL
	if(!table || !key) return NULL;

	// get associated node to key
	ht_node_t *currentNode = ht_find_node(table, key, NULL, NULL);
	// node not found
	if(!currentNode) return NULL;
	// return node's value
	return currentNode->value;
}

/**
 * delete value by given key
 * @param  table 	pointer to hash table
 * @param  key 		value's key to delete
 * @return 			1: deleted successfully
 * 					0: error occured while deleting the value
 */
unsigned char ht_delete(ht_table_t* table, unsigned char *key)
{
	// check table and key are not NULL
	if(!table || !key) return 0;

	ht_node_t *prevNode;
	unsigned int index;
	// get associated node to key
	ht_node_t* currentNode = ht_find_node(table, key, &index, &prevNode);
	// node not found
	if(!currentNode) return 0;

	// set previous node next element to current node next element
	if(currentNode->next != NULL)
	{
		if(prevNode != NULL)
			prevNode->next = currentNode->next;
		else
			table->items[index] = currentNode->next;
	}
	else if(prevNode == NULL)
		table->items[index] = NULL;

	// delete node
	free(currentNode->key);
	free(currentNode->value);
	free(currentNode);

	// decrement table count
	--table->count;

	return 1;
}

/**
 * delete all table items
 * @param table 	pointer to hash table
 */
unsigned char ht_delete_all(ht_table_t* table)
{
	// check table is not NULL
	if(!table) return 0;

	// delete table items if not empty
	if(table->count != 0)
	{
		ht_node_t *currentNode = NULL, *nextNode = NULL;
		for (int i=0; i<table->size; ++i)
		{
			// get next node
			nextNode = table->items[i];
			while(nextNode)
			{
				currentNode = nextNode;
				nextNode = currentNode->next;
				// free memory allocated by current node
				free(currentNode->key);
				free(currentNode->value);
				free(currentNode);
			}
			table->items[i] = NULL;
		}
		// set table count to 0
		table->count = 0;
	}
}

/**
 * free allocated memory for given hash table
 * @param  table 	pointer to hash table
 */
unsigned char ht_free(ht_table_t* table)
{
	// check table is not NULL
	if(!table) return 0;
	// delete table items if not empty
	if(table->count != 0)
		ht_delete_all(table);
	// free table parts
	free(table->items);
	free(table);
	return 1;
}
