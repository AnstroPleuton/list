# list
A Minimal C Linked List

**Note: This project is said to be complete so only bug fixes and patches are maintained.** <br>
...ok small find/replace changes were made... <br>
...ok and implementation prevention changes... <br>
...and it's no longer said to be complete...

# Usage
Define **LIST_IMPL** to implement the function definitions. <br>
Include the library **list.h** to your C/C++ program. <br>
an list is of type **struct list_t** and it's used as a *pointer*. <br>
Use **create_list** function and assign the returning value to **struct list\_t\*** variable (make sure to make one first). <br>
You can add an element to an list using **add_element** function. <br>
You can remove an element from an list by using **remove_element** function. <br>
You can access the element from an list by using **get_element** function. <br>
Make sure to delete an list once you are done with it using **delete_list** function. Don't worry, it will clear an list automatically! <br>

# Access elements
To access an elements of an list, use the function **get_element**, it will return a **struct element_t** pointer to an element <br>.
You can get the void pointer to the data of an element using the **->** operator followed by **data**. <br>
Cast it to the type that you used to get the value of that element. <br>

# Errors
Segmentation faults are most probably what you get when there is an error. You might also see a log displaying the error in the terminal. <br>
If an list failed to be created by the create\_list function then it might return NULL.

# Usage for C++ Wrapper
The C++ Wrapper is designed to use some object oriented approach similar to vectors. <br>
Define **LIST_IMPL** to implement the function definitions. <br>
Include the library **list.hpp** to your C++ program. <br>
an list is of type **list** which is a class template. <br>
Use an list type as **aplib::list\<your_type\>** to use, it will automatically initialize an list. <br>
You can add an element to an list using **insert** method. <br>
You can remove an element from an list by using **erase** method. <br>
You can access the element from an list by using **at** method or by using **[]** operator. <br>
You are not required to delete an list because it is done automatically inside the de-constructor!

# Examples
Please refer to the examples in [test.c](https://github.com/AnstroPleuton/list/blob/main/test.c) and [test.cpp](https://github.com/AnstroPleuton/list/blob/main/test.cpp) for usage examples

# License
License is included in the repository in [LICENSE](https://github.com/AnstroPleuton/list/blob/main/LICENSE) file. In short, it's MIT License.
