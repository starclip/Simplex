#include "../Data processing/DataProsessing.c"

//////////////////////////////////////////////////////////////////
// This function return the value written by the user in a textbox
// 		- data: Is the GtkWidget name.
//////////////////////////////////////////////////////////////////
char* getVariableData(GtkWidget *data)
{
    return gtk_entry_get_text(GTK_ENTRY(data));
}


//////////////////////////////////////////////////////////////////
// This function return the item (textbox, etc)
// 		- builder: Is the builder of the GUI.
//      - name: Is the name of the item in the GUI
//////////////////////////////////////////////////////////////////
GtkWidget* getItem(GtkBuilder *builder, char* name)
{
	return GTK_WIDGET(gtk_builder_get_object(builder, name));
}


//////////////////////////////////////////////////////////////////
// Convert from int to char[]
// - int value    : Is the value to convert
// - char *result : Is the varuable where is gonna be saved the result
// - int base     : Is the base of the numbre
//////////////////////////////////////////////////////////////////
char * itoa (int value, char *result, int base)
{
    if (base < 2 || base > 36) 
    { 
      *result = '\0'; 
      return result; 
    }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}


//////////////////////////////////////////////////////////////////
// This function save the variable names in a list 
// 		- builder: Is the builder of the GUI.
// 		- variables: Is the list where they are going to be saved
//////////////////////////////////////////////////////////////////
void save_data_values(GtkBuilder *builder, char *data[], char name[], int max)
{
	for (int i = 0; i <= max; i++)
	{
		char str[10]; 
		char snum[2];
		itoa(i+1, snum, 10);
		strcpy(str, name);
		strcat(str, snum);
		data[i] = getVariableData(getItem(builder, str));
	}
}


//////////////////////////////////////////////////////////////////
// This function leave as a number the text in the combobox
//      - 0 if is "="
//      - 1 if is ">="
//      - 2 if is "<="
//////////////////////////////////////////////////////////////////
void put_data_on_matris(double data[10][10], int i, int j, char *value)
{
    if (!strcmp(value, "=")) {data[i][j] = 0;}
    if (!strcmp(value, ">=")){data[i][j] = 1;}
    if (!strcmp(value, "<=")){data[i][j] = 2;}
}


//////////////////////////////////////////////////////////////////
// This function get every date in the restriction part on GUI
// and leave this data in the restriction matrix
//////////////////////////////////////////////////////////////////
void get_restrictions(GtkBuilder *builder, double data[10][10], char name[])
{
    // Get variables data
    int conter = 1;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char str[10]; 
            char snum[3];
            itoa(conter, snum, 10);
            strcpy(str, name); 
            strcat(str, snum);
            data[i][j] = atof(getVariableData(getItem(builder, str)));
            conter++; 
        }
    }

    // Get data from results
    for (int i = 0; i < 10; i++)
    {
        char str[10]; 
        char snum[3];
        itoa(i+100, snum, 10);
        strcpy(str, name); 
        strcat(str, snum);
        data[i][9] = atof(getVariableData(getItem(builder, str)));
    }

    // Get data from combo box
    char *value;
    for (int i = 0; i < 10; i++)
    {
        char str[] = "comboboxtext"; 
        char snum[3];
        itoa(i, snum, 10); 
        strcat(str, snum);
        value = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(getItem(builder, str)));
        put_data_on_matris(data, i, 8, value);
    }
}



//////////////////////////////////////////////////////////////////
// This layer sends the data to the data processing layer 
//////////////////////////////////////////////////////////////////
void send_data(char *problem_name, char *variables[], double restrictions[10][10], 
    int *tot_counter, int extra_pages, int problemType, double objFunction[], 
    double final_restrictions_objFunction[11][11])
{
    receive_data(problem_name, variables, restrictions, tot_counter, extra_pages,
        problemType, objFunction, final_restrictions_objFunction);
}


//////////////////////////////////////////////////////////////////
// Assign the type of the variables to a list of variables.
//////////////////////////////////////////////////////////////////
void create_variables(struct variable list_var[cols])
{
    int pos = 0;
    char name[10];
    char end[2];
    char num[2];
    //Generate the Z
    list_var[pos].type = Z;
    //list_var[pos].original_name = "Z"; 
    strcpy(list_var[pos].original_name, "Z");
    pos++;

    //Generate the variables.
    for (int i = 0; i < normal_variables; i++)
    {
        list_var[pos].type = VARIABLE;
        list_var[pos].id = i + 1;
        itoa(i + 1, num, 10);
        if (strcmp(variables[i], "") == 0){
            strcpy(name, "$x_{");
            strcpy(end, "}$");
            strcat(name, num);
            strcat(name, end);
            strcpy(list_var[pos].original_name, name);
        }else{
            strcpy(list_var[pos].original_name, variables[i]);
        }
        pos++;
    }

    //Generate the slack values.
    for (int i = 0; i < slack_variables; i++)
    {
        list_var[pos].type = SLACK;
        list_var[pos].id = i + 1;
        itoa(i + 1, num, 10);
        strcpy(name, "$s_{");
        strcpy(end, "}$");
        strcat(name, num);
        strcat(name, end);
        strcpy(list_var[pos].original_name, name);
        pos++;
    }

    //Generate the excess values.
    for (int i = 0; i < excess_variables; i++)
    {
        list_var[pos].type = EXCESS;
        list_var[pos].id = i + 1;
        itoa(i + 1, num, 10);
        strcpy(name, "$e_{");
        strcpy(end, "}$");
        strcat(name, num);
        strcat(name, end);
        strcpy(list_var[pos].original_name, name);
        pos++;
    }

    //Generate the slack values.
    for (int i = 0; i < virtual_variables; i++)
    {
        list_var[pos].type = VIRTUAL;
        list_var[pos].id = i + 1;
        itoa(i + 1, num, 10);
        strcpy(name, "$a_{");
        strcpy(end, "}$");
        strcat(name, num);
        strcat(name, end);
        strcpy(list_var[pos].original_name, name);
        pos++;
    }

    //Generate the Z
    list_var[pos].type = RESULT;
    //list_var[pos].original_name = "#"; 
    strcpy(list_var[pos].original_name, "#");

}