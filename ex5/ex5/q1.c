#define NAME_LENGTH 200
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef int BOOL;
#define TRUE  (1)
#define FALSE (0)


typedef struct hw_component
{
	char name[NAME_LENGTH];
	int copies;
	struct hw_component* next;
}HW_component;


int chr2int(char c)
{
	return c - 48;
}

int str2int(char* st)
{
	int num = 0;
	for (int i = 0; i < strlen(st); i++)
	{
		num += chr2int(st[i]) * pow(10, strlen(st)-1-i);
	}
	return num;
}

void* my_malloc(const int size)
{
	void* pointer = malloc(size);
	if (pointer == NULL)
	{
		printf("Fatal error : unable to allocate memory!\n");
		exit(1);
	}
	return pointer;
}

FILE* read_file(char* file_name)
{
	FILE* file_ptr = fopen(file_name, "r");

	if (file_ptr == NULL)
	{
		printf("File did not open. Exit..\n");
		exit(1);
	}
	return file_ptr;
}

char* read_string(FILE* file_pointer)
{
	char final_string[NAME_LENGTH];
	char word[NAME_LENGTH];

	fscanf(file_pointer, "%s", word);
	strcpy(final_string, word);
	fscanf(file_pointer, "%s", word);
	while (strcmp(word, "$$$") != 0)
	{
		strcat(final_string, " ");
		strcat(final_string, word);
		fscanf(file_pointer, "%s", word);
	}
	return final_string;
}


HW_component* add_component(HW_component* head, HW_component* to_add)
{
	HW_component* curr_com, *prev_com = NULL;

	if (head == NULL)
		return to_add;

	if (strcmp(to_add->name, head->name) < 0)
	{
		to_add->next = head;
		return to_add;
	}

	curr_com = head;
	while (curr_com != NULL && strcmp(to_add->name, curr_com->name) >0)
	{
		prev_com = curr_com;
		curr_com = curr_com->next;
	}
	
	prev_com->next = to_add;
	to_add->next = curr_com;

	return head;
}

HW_component* add_raw_component(HW_component* head, char* name, int copies)
{
	HW_component* new_component = (HW_component*)my_malloc(sizeof(HW_component));
	strcpy(new_component->name, name);
	new_component->copies = copies;
	new_component->next = NULL;
	return add_component(head, new_component);
}

HW_component* read_components(char* components_file_name)
{
	char name[NAME_LENGTH] = "";
	char word[NAME_LENGTH];
	BOOL num_flag = FALSE, name_flag = FALSE;
	
	HW_component* head = NULL;
	HW_component* new_component = NULL;
	
	FILE* components_file_ptr = read_file(components_file_name);

	fscanf(components_file_ptr, "%s", word);
	while (!feof(components_file_ptr)) 
	{
		if (strcmp(word, "$$$") == 0)
		{
			num_flag = TRUE;
			name_flag = FALSE;
		}

		else if (!num_flag)
		{
			if (!name_flag)
			{
				strcat(name, word);
				name_flag = TRUE;
			}
			else
			{
				strcat(name, " ");
				strcat(name, word);
			}
		}
		
		else if (num_flag)
		{
			head = add_raw_component(head, name, str2int(word));
			
			num_flag = FALSE;
			strcpy(name, "");
		}
		fscanf(components_file_ptr, "%s", word);
	}
	fclose(components_file_ptr);
	return head;
}


HW_component* rename_component(HW_component* head, char* name, char* new_name)
{
	HW_component *current_component = head, *prev_component = NULL;

	// Handel first node match
	if (strcmp(current_component->name, name) == 0)
	{
		head = current_component->next;
		strcpy(current_component->name, new_name);
		head = add_component(head, current_component);
		return head;
	}
	current_component = current_component->next;
	prev_component = current_component;
	
	while(current_component->next != NULL)
	{
		if (strcmp(current_component->name, name) == 0)
		{
			strcpy(current_component->name, new_name);
			prev_component->next = current_component->next;
			head = add_component(head, current_component);
			return head;
		}
		current_component = current_component->next;
		prev_component = current_component;
	}

}

void finalize(HW_component* head)
{
	// TODO: Itamari
}

void returned_from_customer()
{
	// TODO: Itamari
}

HW_component* production(HW_component* head, char* name, int copies)
{
	// TODO: check if the production should REPLACE or ADD the num of copies
	HW_component* current_component = head;

	while (current_component->next != NULL)
	{
		if (strcmp(current_component->name, name) == 0)
		{
			current_component->copies = copies;
			return head;
		}
		current_component = current_component->next;
	}

	return add_raw_component(head, name, copies);
}

void fatal_malfunction(HW_component* head, char* name, int malfunction_copies)
{
	// TODO: check if the copies functions are not reversed 

	HW_component* current_component = head;

	while (current_component->next != NULL)
	{
		if (strcmp(current_component->name, name) == 0)
		{
			if (malfunction_copies > current_component->copies)
				current_component->copies = 0;
			else
				current_component->copies -= malfunction_copies;
			return;
		}
		current_component = current_component->next;
	}
}

void fire()
{
	// TODO: Itamari
}

void read_actions(char* actions_file_name)
{

	// TODO: Itamari
	char action[NAME_LENGTH];
	char word[NAME_LENGTH];

	FILE* actions_file_ptr = read_file(actions_file_name);

	fscanf(actions_file_ptr, "%s", word);
	fscanf(actions_file_ptr, "%s", word);
	//Initialize before while loop

	while (strcmp(word, "Finalize") != 0)
	{
		if (strcmp(word, "Returned_from_customer") == 0)
		{
			char component_name[NAME_LENGTH];
			int quantity;

			fscanf(actions_file_ptr, "%s", word);

			strcpy(component_name, read_string(actions_file_ptr));

			fscanf(actions_file_ptr, "%s", word);
			strcpy(component_name, word);
			fscanf(actions_file_ptr, "%s", word);
			fscanf(actions_file_ptr, "%s", word);
			quantity = str2int(word);
			//returned_from_customer(component_name, quantity);
		}
		else if (strcmp(word, "Fire") == 0)
		{
			char component_name[NAME_LENGTH];
			int quantity;
			fscanf(actions_file_ptr, "%s", word);
			fscanf(actions_file_ptr, "%s", word);
			strcpy(component_name, word);
			fscanf(actions_file_ptr, "%s", word);
			fscanf(actions_file_ptr, "%s", word);
			quantity = str2int(word);
			//fire(component_name, quantity);
		}
		else if (strcmp(word, "Production") == 0)
		{
			char component_name[NAME_LENGTH];
			int quantity;
			fscanf(actions_file_ptr, "%s", word);
			fscanf(actions_file_ptr, "%s", word);
			strcpy(component_name, word);
			fscanf(actions_file_ptr, "%s", word);
			fscanf(actions_file_ptr, "%s", word);
			quantity = str2int(word);
			//production(component_name, quantity);
		}
		else if (strcmp(word, "Rename") == 0)
		{
			char component_name[NAME_LENGTH];
			char new_name[NAME_LENGTH];
			fscanf(actions_file_ptr, "%s", word);
			fscanf(actions_file_ptr, "%s", word);
			strcpy(component_name, word);
			fscanf(actions_file_ptr, "%s", word);
			fscanf(actions_file_ptr, "%s", word);
			strcpy(new_name, word);
			//rename(component_name, new_name);
		}
		else if (strcmp(word, "Fatal_malfunction") == 0)
		{
			char component_name[NAME_LENGTH];
			int quantity;
			fscanf(actions_file_ptr, "%s", word);
			fscanf(actions_file_ptr, "%s", word);
			strcpy(component_name, word);
			fscanf(actions_file_ptr, "%s", word);
			fscanf(actions_file_ptr, "%s", word);
			quantity = str2int(word);
			//fatal_malfunction(component_name, quantity);
		}
		fscanf(actions_file_ptr, "%s", word);
	}
	//finalize();
}

int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
	{
		printf("\n");
		printf(argv[i]);
	}

	if (argc < 3)
		return -1;

	HW_component *components = read_components(argv[2]);

	//components = rename_component(components, "Hub", "Hobbies");
	//components = rename_component(components, "Hobbies", "Ilan");
	//components = production(components, "Hub pro", 56);
	//components = production(components, "Hub", 25);
	//components = production(components, "Gate Master", 25);
	//fatal_malfunction(components, "Hub", 25);
	//fatal_malfunction(components, "Hub pro", 600);

	return 0;
}
