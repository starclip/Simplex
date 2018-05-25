#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <gtk/gtk.h>
#include "Simplex/structures.c"
#include "GUI/functions.c"
#include "Beamer/beamer.c"
#include "Simplex/Simplex.c"

//////////////////////////////////////////////////////////////////
// This function set the value of extra_pages, if is 1
// means that the user wants to see the extra pages if
// is 0 the user dont want to see this pages.  
//////////////////////////////////////////////////////////////////
void set_extra_tables_flag()
{
	if (extra_pages == 0)
	{
		extra_pages = 1;
	}
	else if (extra_pages == 1)
	{
		extra_pages = 0;
	}
}

//////////////////////////////////////////////////////////////////
// This function develops the simplex process.
//////////////////////////////////////////////////////////////////
void process_Simplex(double simplex_matrix[rows][cols])
{
	struct variable list_var[cols];
	double list_M[cols];

	latex_file = fopen(latexFileName, "w");
	table_file = fopen(tableFileName, "w");
	variables_file = fopen(variableFileName, "w");
	enum SOLUTION state;

	printf("\n\nRestricciones \n"); 
	for (int i = 0; i < rows; i++) 
	{ 
		for (int j = 0; j < cols; j++) { 
			printf("%2f ", simplex_matrix[i][j]); 
		} 
		printf("\n"); 
	} 
	printf("######################################\n\n");

	show_intermediate_tables = extra_pages;
	printf("Tipo de problema: %d \n", problemType);

	create_variables(list_var);

	original_problem(variables_file, simplex_matrix, list_var, problemType);

	state = pre_Simplex(simplex_matrix, list_M, problemType, list_var);

	print_table(simplex_matrix);

	solution(simplex_matrix, list_M, list_var, state, problemType);

	generate_latex(latex_file, table_file, variables_file);

}


//////////////////////////////////////////////////////////////////
// This function find the data in the GUI and save them in lists
//////////////////////////////////////////////////////////////////
void find_variables(GtkButton* button, gpointer user_data)
{
	// Step 1: Get the problem name
	problem_name = getVariableData(getItem(builder, "problemName")); 

	// Step 2: Put the variables name in a list
	save_data_values(builder, variables, "variable", 7);

	// Paso 3: Guardar todas las restricciones en una lista 
	get_restrictions(builder, restrictions, "sp");


	// Step 4: Get the problem type
	char *value = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(getItem(builder, "problemType"))); 
    if (!strcmp(value, "MAX")) {problemType = 1;}
    if (!strcmp(value, "MIN")) {problemType = 0;}

    // Step 5: Get obj function
    for (int i = 0; i < 8; i++)
    {
    	char str[10]; 
        char snum[3];
        itoa(i+81, snum, 10);
        strcpy(str, "sp"); 
        strcat(str, snum);
        objFunction[i] = atof(getVariableData(getItem(builder, str)));
    }

    double final_restrictions_objFunction[11][11];
    int counter = 0;

	// Step 6: Send data to pre-processing  
	send_data(problem_name, variables, restrictions, &counter, extra_pages, problemType, 
		objFunction, final_restrictions_objFunction);

	printf("Counter __ %d \n", counter);

	// Step 7: Count the num of rows and cols.
	pre_prosessing(problem_name, variables, final_restrictions_objFunction, counter+1,
	 extra_pages, problemType);

	double simplex_matrix[rows][cols];

	second_pre_prosessing(problem_name, variables, final_restrictions_objFunction, counter+1,
	 extra_pages, problemType, simplex_matrix);

	// Make the simplex process.
	process_Simplex(simplex_matrix);
}


//////////////////////////////////////////////////////////////////
// Main 
//////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]){
	// Variables for the main window 
	gtk_init(&argc, &argv);
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "GUI/GUISimplex.glade", NULL);
	window = GTK_WIDGET(gtk_builder_get_object(builder, "BeginWindow"));
	
	// Assign action to the button
	BtnCalcular = GTK_WIDGET(gtk_builder_get_object(builder, "calcular"));
	g_signal_connect(BtnCalcular, "clicked", G_CALLBACK(find_variables), NULL);
	
	check_button = GTK_WIDGET(gtk_builder_get_object(builder, "checkbutton1"));
	g_signal_connect(check_button, "clicked", G_CALLBACK(set_extra_tables_flag), NULL);

	// Show the main window
	gtk_widget_show(window);
	gtk_main();
	return 0;
}