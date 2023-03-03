/*
 * Copyright (c) 2023 Anstro Pleuton (@AnstroPleuton)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * A Minimal C Linked List
 *   Usage and other information is provided in the README.md file from the
 *   repository. Please refer to that to know how to use this library.
 */

#ifndef LIST_H
#define LIST_H "list.h"

#include <stdlib.h>
#include <stdio.h>

/*
 * Define these for logs
 * PRINT_INFO will print the entering and exiting of function
 * PRINT_DEBUG will print any small debug details
 * PRINT_ERROR will print only the errors occurred in the function
 */

#ifdef PRINT_INFO
#define PRINT_ENTER(function) \
	printf("  Info: file: %s, function enters: %s\n", LIST_H, function)
#define PRINT_RETURN(function) \
	printf("  Info: file: %s, function return: %s\n", LIST_H, function)
#else
#define PRINT_ENTER(function)
#define PRINT_RETURN(function)
#endif

#ifdef PRINT_DEBUG
#define DEBUG(string) printf("    Degug: %s\n", string)
#else
#define DEBUG(string)
#endif

#ifdef PRINT_ERROR
#define ERROR(string) printf("    Error: %s\n", string)
#else
#define ERROR(string)
#endif

/* Implement the list code by defining
 * LIST_IMPL before including this library */

struct element_t{
	void *data;
	void *next;
};

struct list_t {
	/* The base does not contain an element,
	 * the next of the base is the index of 0 */
	struct element_t *base;
	size_t size;
	size_t typesize;
};

struct list_t *create_list(size_t typesize);
struct element_t *get_element(size_t index, struct list_t *list);

int update_list_size(struct list_t *list);
size_t get_list_size(struct list_t *list);

/* These functions are not supposed to be used externally */
struct element_t *create_element(size_t typesize);
int delete_element(struct element_t *element);

/* You can add element at the end of the
 * list by giving it the size of the list */
struct element_t *add_element(size_t index, struct list_t *list);
int remove_element(size_t index, struct list_t *list);

int clear_list(struct list_t *list);
int delete_list(struct list_t *list);

#ifdef LIST_IMPL

struct list_t *create_list(size_t typesize)
{
	PRINT_ENTER("create_list");
	DEBUG("Creating a list");
	struct list_t *list = (struct list_t *) malloc(sizeof(list_t));

	if (!list) {
		ERROR("Unable to allocate memory for a list");
		return NULL;
	}

	list->size = 0;
	list->typesize = typesize;

	DEBUG("Successfully created a list");
	DEBUG("Allocating memory for the base");

	list->base = (struct element_t *) malloc(sizeof(element_t));

	if (!list->base) {
		ERROR("Unable to allocate memory for the base of a list");
		return NULL;
	}

	list->base->data = NULL;
	list->base->next = NULL;

	DEBUG("Successfully allocated the memory for the base");
	PRINT_RETURN("create_list");
	return list;
}

struct element_t *get_element(size_t index, struct list_t *list)
{
	PRINT_ENTER("get_element");
	struct element_t *element = NULL;

	if (!list) {
		ERROR("Unexpected null list");
		return NULL;
	}

	DEBUG("Finding an element");
	element = list->base;

	/* Note, I am not using 'i <= index' because I want
	 * the size to overflow in case the index was -1 */
	for (size_t i = 0; i < (index + 1); i++) {
		element = (struct element_t *) element->next;

		if (!element) {
			ERROR("Element does not exist");
			return NULL;
		}
	}

	PRINT_RETURN("get_element");
	return element;
}



int update_list_size(struct list_t *list)
{
	PRINT_ENTER("update_list_size");
	struct element_t *element = NULL;
	size_t size = 0;

	if (!list) {
		ERROR("Unexpected null list");
		return 1;
	}

	DEBUG("Calculating a list size");
	element = list->base;

	while (element) {
		element = (struct element_t *) element->next;
		size++;
	}

	/* The base is not considered as an element */
	--size;
	DEBUG("Successfully calculated the size of a list");
	PRINT_RETURN("update_list_size");
	return 0;
}

size_t get_list_size(struct list_t *list)
{
	PRINT_ENTER("get_list_size");
	if (!list) {
		ERROR("Unexpected null list");
		return 0;
	}
	if (update_list_size(list)) {
		ERROR("Unable to update list size");
		return 0;
	}
	PRINT_RETURN("get_list_size");
	return list->size;
}



struct element_t *create_element(size_t typesize)
{
	PRINT_ENTER("create_element");
	DEBUG("Creating an element");
	struct element_t *element = (struct element_t *) malloc(sizeof(element_t));

	if (!element) {
		ERROR("Failed to allocate memory for an element");
		return NULL;
	}

	DEBUG("Successfully created an element");
	DEBUG("Allocating memory for the data of an element");

	element->next = NULL;
	element->data = malloc(typesize);
	if (!element->data) {
		ERROR("Failed to allocate memory for the data of an element");
		return NULL;
	}

	DEBUG("Successfully allocated memory for the data of an element");
	PRINT_RETURN("create_element");
	return element;
}

int delete_element(struct element_t *element)
{
	PRINT_ENTER("delete_element");
	if (!element) {
		ERROR("Unexpected null element");
		return 1;
	}

	if (element->data) {
		free(element->data);
	}
	free(element);
	PRINT_RETURN("delete_element");
	return 0;
}



struct element_t *add_element(size_t index, struct list_t *list)
{
	PRINT_ENTER("add_element");
	struct element_t *new_element = NULL;
	struct element_t *prev = NULL;
	struct element_t *temp = NULL;

	if (!list) {
		ERROR("Unexpected null list");
		return NULL;
	}

	if (update_list_size(list)) {
		ERROR("Unable to update list size");
		return NULL;
	}
	if (index > list->size) {
		ERROR("Index larger than the (size + 1) of a list");
		return NULL;
	}

	DEBUG("Adding an element to a list");
	prev = get_element(index - 1, list);
	new_element = create_element(list->typesize);

	/* There can't be no previous because the base should exist */
	if (!prev) {
		ERROR("Cannot find the previous element "
		      "or the base of a list");
		return NULL;
	}
	if (!new_element) {
		ERROR("Cannot allocate memory for an "
		      "element to be added to a list");
		return NULL;
	}

	temp = (struct element_t *) prev->next;
	prev->next = (void *) new_element;
	new_element->next = (void *) temp;

	list->size++;

	DEBUG("Successfully added an element");
	PRINT_RETURN("add_element");
	return new_element;
}

int remove_element(size_t index, struct list_t *list)
{
	PRINT_ENTER("remove_element");
	struct element_t *element = NULL;
	struct element_t *prev = NULL;
	struct element_t *next = NULL;

	if (!list) {
		ERROR("Unexpected null list");
		return 1;
	}
	if (update_list_size(list)) {
		ERROR("Unable to update list size");
		return 2;
	}
	if (index >= list->size) {
		ERROR("Index larger than the size of a list");
		return 3;
	}

	DEBUG("Removing an element");
	element = get_element(index, list);
	if (!element) {
		ERROR("Cannot find an element");
		return 4;
	}

	prev = get_element(index - 1, list);

	/* To prevent unnecessary error logs, I used an 'if' check */
	if (index < list->size - 1) {
		next = get_element(index + 1, list);
	}
	if (!prev) {
		ERROR("Cannot find the previous element "
		      "or the base of a list");
		return 5;
	}

	prev->next = NULL;
	if (next) {
		prev->next = next;
	}

	if (delete_element(element)) {
		ERROR("Unable to delete an element");
		return 6;
	}
	list->size--;

	DEBUG("Removed an element");
	PRINT_RETURN("remove_element");
	return 0;
}



int clear_list(struct list_t *list)
{
	PRINT_ENTER("clear_list");
	if (!list) {
		ERROR("Unexpected null list");
		return 1;
	}

	DEBUG("Clearing a list");
	if (update_list_size(list)) {
		ERROR("Unable to update list size");
		return 2;
	}
	if (list->size == 0) {
		DEBUG("An list is already empty");
		/* This is not considered an error */
		return 0;
	}

	for (int i = list->size - 1; i >= 0; i--) {
		remove_element(i, list);
	}

	DEBUG("Cleared a list");
	PRINT_RETURN("clear_list");
	return 0;
}

int delete_list(struct list_t *list)
{
	PRINT_ENTER("delete_list");
	if (!list) {
		ERROR("Unexpected null list");
		return 1;
	}

	DEBUG("Deleting a list");
	if (clear_list(list)) {
		ERROR("Unable to clear a list");
		return 2;
	}
	if (list->base) {
		free(list->base);
	}
	free(list);
	DEBUG("List deleted");
	PRINT_RETURN("delete_list");
	return 0;
}

/* LIST_IMPL */
#endif

/* LIST_H */
#endif
