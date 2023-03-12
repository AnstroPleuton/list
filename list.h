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
	/* Update the size of the list when modifying externally */
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
	struct list_t *list = (struct list_t *) malloc(sizeof(struct list_t));

	if (!list) {
		return NULL;
	}

	list->size = 0;
	list->typesize = typesize;
	list->base = (struct element_t *) malloc(sizeof(struct element_t));

	if (!list->base) {
		return NULL;
	}

	list->base->data = NULL;
	list->base->next = NULL;
	return list;
}

struct element_t *get_element(size_t index, struct list_t *list)
{
	struct element_t *element = NULL;

	if (!list) {
		return NULL;
	}
	element = list->base;

	/* Note, I am not using 'i <= index' because I want
	 * the size to overflow in case the index was -1 */
	for (size_t i = 0; i < (index + 1); i++) {
		element = (struct element_t *) element->next;
		if (!element) {
			return NULL;
		}
	}
	return element;
}



int update_list_size(struct list_t *list)
{
	struct element_t *element = NULL;
	size_t size = 0;

	if (!list) {
		return 1;
	}
	element = list->base;

	while (element) {
		element = (struct element_t *) element->next;
		size++;
	}

	/* The base is not considered as an element */
	--size;
	return 0;
}

size_t get_list_size(struct list_t *list)
{
	if (!list) {
		return 0;
	}
	if (update_list_size(list)) {
		return 0;
	}
	return list->size;
}



struct element_t *create_element(size_t typesize)
{
	struct element_t *element = (struct element_t *) malloc(sizeof(struct element_t));
	if (!element) {
		return NULL;
	}

	element->next = NULL;
	element->data = malloc(typesize);
	if (!element->data) {
		return NULL;
	}

	return element;
}

int delete_element(struct element_t *element)
{
	if (!element) {
		return 1;
	}
	if (!element->data) {
		return 2;
	}

	free(element->data);
	free(element);
	return 0;
}



struct element_t *add_element(size_t index, struct list_t *list)
{
	struct element_t *new_element = NULL;
	struct element_t *prev = NULL;
	struct element_t *temp = NULL;

	if (!list) {
		return NULL;
	}
	if (index > list->size) {
		return NULL;
	}

	prev = get_element(index - 1, list);
	new_element = create_element(list->typesize);

	/* There can't be no previous because the base should exist */
	if (!prev) {
		return NULL;
	}
	if (!new_element) {
		return NULL;
	}

	temp = (struct element_t *) prev->next;
	prev->next = (void *) new_element;
	new_element->next = (void *) temp;

	list->size++;
	return new_element;
}

int remove_element(size_t index, struct list_t *list)
{
	struct element_t *element = NULL;
	struct element_t *prev = NULL;
	struct element_t *next = NULL;

	if (!list) {
		return 1;
	}
	if (index >= list->size) {
		return 3;
	}

	element = get_element(index, list);
	if (!element) {
		return 4;
	}
	prev = get_element(index - 1, list);

	/* To prevent unnecessary error logs, I used an 'if' check */
	if (index < list->size - 1) {
		next = get_element(index + 1, list);
	}
	if (!prev) {
		return 5;
	}

	prev->next = NULL;
	if (next) {
		prev->next = next;
	}
	if (delete_element(element)) {
		return 6;
	}
	list->size--;

	return 0;
}



int clear_list(struct list_t *list)
{
	if (!list) {
		return 1;
	}
	if (list->size == 0) {
		/* This is not considered an error */
		return 0;
	}

	for (int i = list->size - 1; i >= 0; i--) {
		remove_element(i, list);
	}
	return 0;
}

int delete_list(struct list_t *list)
{
	if (!list) {
		return 1;
	}
	if (clear_list(list)) {
		return 2;
	}
	if (!list->base) {
		return 3;
	}

	free(list->base);
	free(list);
	return 0;
}

/* LIST_IMPL */
#endif

/* LIST_H */
#endif
