/**
 * @author 		Abdelhakim RAFIK
 * @version 	v1.0.1
 * @license 	MIT License
 * @Copyright 	Copyright (c) 2021 Abdelhakim RAFIK
 * @date 		Feb 2021
 */

#include <stdio.h>
#include <string.h>
#include "lib/hashTable.h"

typedef struct
{
	char nom[50];
	char cne[20];
	char filier[5];
	int niveau;
	float notes[8];
} etudiant_t;

void print_table(ht_table_t* table)
{
	printf("\n======== Hash table print ========\n");
	printf("table size: %d\n", table->size);
	printf("table count: %d\n", table->count);
	printf("-------------- Items --------------\n");
	ht_node_t *currentNode;
	for(int i=0; i<table->size; ++i)
	{
		printf("%d:", i);
		currentNode = table->items[i];
		if(!currentNode)
			printf(" -> NULL");
		else
		{
			while(currentNode)
			{
				printf(" -> %s", currentNode->key);
				currentNode = currentNode->next;
			}
		}
		printf("\n");
	}
	printf("===================================\n");
}

void addPersonToTable(ht_table_t* table, char *key, const char *nom, const char *cne, const char *filier, int niveau, float n1, float n2, float n3)
{
	etudiant_t e1;
	memcpy(e1.nom, nom, strlen(nom)+1);
	memcpy(e1.cne, cne, strlen(cne)+1);
	memcpy(e1.filier, filier, strlen(filier)+1);
	e1.niveau = niveau;
	e1.notes[0] = n1;
	e1.notes[1] = n2;
	e1.notes[2] = n3;

	ht_insert(table, key, &e1, sizeof(e1));
}

void printPerson(etudiant_t *e)
{
	printf("\nNOM: %s\n\tCNE: %s, FILIERE: %s, NIVEAU: %d\n", e->nom, e->cne, e->filier, e->niveau);
	printf("\tNotes: N1: %f, N2: %f, N3: %f\n", e->notes[0], e->notes[1], e->notes[2]);
}


int main()
{
	ht_table_t* table = ht_create(5);

	addPersonToTable(table, "hakim", "Abdelhakim", "1412014364", "GLSID", 1, 19, 18, 19.5);
	addPersonToTable(table, "hamza", "Hamza", "1543264985", "GLSID", 1, 18, 17, 19);
	addPersonToTable(table, "nadia", "Nadia", "P15243659", "BDCC", 1, 15, 19, 16);
	addPersonToTable(table, "zakariya", "Zakariya", "154365948", "GLSID", 1, 18.5, 17, 19);
	addPersonToTable(table, "hakim", "Abdelhakim", "154935949", "GLSID", 1, 19, 18, 19.5);
	addPersonToTable(table, "fatima", "Fatima", "25846954256", "GLSID", 1, 20, 19, 19.5);
	addPersonToTable(table, "mohamed", "Mohamed Ali", "1452365978", "BDCC", 1, 15, 19, 18);
	addPersonToTable(table, "fatiha", "Fatiha Mansoury", "1245934587", "GLSID", 1, 17.5, 15, 19);
	addPersonToTable(table, "fatiha1", "Fatiha Mansoury", "1245934587", "GLSID", 1, 17.5, 15, 19);
	addPersonToTable(table, "fatiha2", "Fatiha Mansoury", "1245934587", "GLSID", 1, 17.5, 15, 19);
	addPersonToTable(table, "fatiha3", "Fatiha Mansoury", "1245934587", "GLSID", 1, 17.5, 15, 19);
	addPersonToTable(table, "fatiha4", "Fatiha Mansoury", "1245934587", "GLSID", 1, 17.5, 15, 19);
	addPersonToTable(table, "fatiha5", "Fatiha Mansoury", "1245934587", "GLSID", 1, 17.5, 15, 19);
	addPersonToTable(table, "fatiha6", "Fatiha Mansoury", "1245934587", "GLSID", 1, 17.5, 15, 19);
	addPersonToTable(table, "fatiha7", "Fatiha Mansoury", "1245934587", "GLSID", 1, 17.5, 15, 19);
	addPersonToTable(table, "fatiha8", "Fatiha Mansoury", "1245934587", "GLSID", 1, 17.5, 15, 19);

	etudiant_t *e = (etudiant_t*) ht_find(table, "hamza");
	printPerson(e);

	e = (etudiant_t*) ht_find(table, "hakim");
	printPerson(e);

	e = (etudiant_t*) ht_find(table, "nadia");
	printPerson(e);

	e = (etudiant_t*) ht_find(table, "fatiha");
	printPerson(e);

	print_table(table);

	ht_delete(table, "fatima");

	print_table(table);

	ht_delete_all(table);

	print_table(table);
}
