

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

HW_component read_components(char* components_file_name)
{
	char name[NAME_LENGTH] = "";
	char word[NAME_LENGTH];
	BOOL num_flag = FALSE, name_flag = FALSE;
	
	HW_component* head = NULL;
	HW_component* current_component = NULL;
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
			new_component = (HW_component*)my_malloc(sizeof(HW_component));
			strcpy(new_component->name, name);
			new_component->copies = str2int(word);

			if (head == NULL)
				head = new_component;
			else
				current_component->next = new_component;
			
			current_component = new_component;
			num_flag = FALSE;
			strcpy(name, "");
		}
	
		fscanf(components_file_ptr, "%s", word);
	}
	fclose(components_file_ptr);
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

	HW_component components = read_components(argv[2]);

	
	FILE* action_file_ptr = fopen(argv[1], "r");
	

	//if (action_file_ptr == NULL || components_file_ptr == NULL) {
	//	printf("File did not open. Exit..\n");
	//	return 1;
	//}


	return 0;
}
