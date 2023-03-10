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
 * Feature tests for the Minimal C List
 */

#include <stdio.h>
#define LIST_IMPL
#include "list.h"

int main(void)
{
	/* Create a list */
	struct list_t *my_list = create_list(sizeof (int));

	/* List creation fail check */
	if (!my_list) {
		/* In that case, we end the program */
		return 1;
	}

	/* Print the size of the list */
	printf("Number of elements in list: %lu\n",
	       get_list_size(my_list));

	/* Add an element at the end of a list */
	struct element_t *element = add_element(get_list_size(my_list), my_list);

	/* While adding an element, we can check for errors */
	if (!element) {
		/* If we hit an error, we end the program, again */
		return 2;
	}

	/* Print the size of the list again */
	printf("Number of elements in list: %lu\n",
	       get_list_size(my_list));

	/* Get the first element of a list */
	element = get_element(0, my_list);

	/* It is possible to get error when getting an element */
	if (!element) {
		/* In that case, we end the program, again */
		return 3;
	}

	/* Set the first element of a list to 20 */
	*(int *) element->data = 20;

	/* Add an element at the beginning of a list */
	element = add_element(0, my_list);

	/* You get the idea... */
	if (!element) {
		/* Just note that it is very rare to get errors like this */
		return 4;
	}

	/* The following two functions are immune to errors */

	/* Set the first element of a list to 40 in a different way */
	*(int *) get_element(0, my_list)->data = 40;

	/* Immediately set the added element to 60 */
	*(int *) add_element(1, my_list)->data = 60;

	/* Print the size of the list again */
	printf("Number of elements in list: %lu\n",
	       get_list_size(my_list));

	/* Print all the elements from a list */
	for (size_t i = 0; i < get_list_size(my_list); i++) {
		printf("Element #%lu: %i\n", i,
		       *(int *) get_element(i, my_list)->data);
	}

	/* Remove an element from the end of a list with error checking */
	if (remove_element(get_list_size(my_list) - 1, my_list)) {
		/* This means the function failed to remove an element */
		return 5;
	}

	/* Print the size of the list again */
	printf("Number of elements in list: %lu\n",
	       get_list_size(my_list));

	/* The following function is immune to errors */

	/* Remove an element from the beginning of a list */
	remove_element(0, my_list);

	/* Clear the elements from the list with error checking */
	if (clear_list(my_list)) {
		/* This means the function failed to clear a list */
		return 6;
	}

	/* Print the size of the list again */
	printf("Number of elements in list: %lu\n",
	       get_list_size(my_list));

	/* Delete a list with error checking */
	if (delete_list(my_list)) {
		/* Failed to delete a list... */
		return 7;
	}
	return 0;
}

/* Expected output:
 *
 * Number of elements in list: 0
 * Number of elements in list: 1
 * Number of elements in list: 3
 * Element #0: 40
 * Element #1: 60
 * Element #2: 20
 * Number of elements in list: 2
 * Number of elements in list: 0
 */
