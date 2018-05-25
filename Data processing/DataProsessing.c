/////////////////////////////////////////////////////////////////////
// problem_name : It has the problem name 
// variables    : This is a list with the variable names
// restrictions : It has just the valid restrictions
// extra_pages  : It indicates if user wants extra page (1 = yes, 0 = not)
// problemType  : It has the problem type (1 means MAX, 0 means MIN)
// objFunction  : It has the objective function 
/////////////////////////////////////////////////////////////////////
void pre_prosessing(char *problem_name, char *variables[], double restrictions[11][11], 
	int restriction_counter, int extra_pages, int problemType)
{
	// Count the columns
	int counter = 0;
	for (int j = 0; j < 9; j++){ // col
		int flag = 0;
		for (int i = 0; i < restriction_counter; i++){ // fil
			if (restrictions[i][j] != 0)
			{
				flag = 1;
			}
		}
		if (flag == 1)
		{
			counter++;
		}
	}
	// Omito los símbolos y el resultado.	
	counter += 2;


	
	// Delete the column without use. 
	double valid_restrictions[restriction_counter][counter]; // 
	int col = 0;
	int varCol = -1;
	for (int j = 0; j < 9; j++) // col //
	{
		int flag = 0;
		for (int i = 0; i < restriction_counter; i++) // fil
		{
			if (restrictions[i][j] != 0 && !flag)
			{
				// add the restriction 
				for (int k = 0; k < restriction_counter; k++)
				{
					valid_restrictions[k][col] = restrictions[k][j];
				}
				col++;
				flag = 1;
			}
		}
		if (flag == 0)
		{
			variables[varCol] = "";
		}
		varCol++;
	}
	for (int i = 0; i < restriction_counter; i++)
	{
		valid_restrictions[i][counter-2] = restrictions[i][9]; 
		valid_restrictions[i][counter-1] = restrictions[i][10];  
	}

	// Count of the extra variables that exist in the problem  
	int extra_column = 0;
    for (int i = 1; i < restriction_counter; i++)
    {
    	if (valid_restrictions[i][counter-2] == 0){extra_column++;}
    	if (valid_restrictions[i][counter-2] == 1){extra_column += 2;}
    	if (valid_restrictions[i][counter-2] == 2){extra_column++;}
    }
    
    int total_colums = counter + extra_column -1;

    cols = total_colums;
    rows = restriction_counter;

	double final_restrictions_with_extra_variables[restriction_counter][total_colums];
	for (int i = 0; i < restriction_counter; i++)
	{
		for (int j = 0; j < total_colums; j++)
		{
			final_restrictions_with_extra_variables[i][j] = 0;
		}
	}
	final_restrictions_with_extra_variables[0][0] = 1;


	///////////////////////////////
	// Construction of the table //
	///////////////////////////////

	normal_variables = counter - 2 - 1;
	// Add variables values 
	for (int i = 0; i < restriction_counter; i++)
	{
		for (int j = 1; j < counter - 2; j++)
		{
			final_restrictions_with_extra_variables[i][j] = valid_restrictions[i][j];
		}
		final_restrictions_with_extra_variables[i][total_colums-1] = valid_restrictions[i][counter-1];
	}


	// add olgura variables
	int extra_variables_counter = counter - 2;
	for (int i = 1; i < restriction_counter; i++)
	{
	 	if (valid_restrictions[i][counter - 2] == 2)
	 	{
	 		final_restrictions_with_extra_variables[i][extra_variables_counter] = 1;
	 		extra_variables_counter++;
	 		slack_variables++;
	 	}
	} 

	// add excess variables 
	for (int i = 1; i < restriction_counter; i++)
	{
	 	if (valid_restrictions[i][counter - 2] == 1)
	 	{
	 		final_restrictions_with_extra_variables[i][extra_variables_counter] = -1;
	 		extra_variables_counter++;
	 		excess_variables++;
	 	}
	}

	// add artificial variables 
	for (int i = 1; i < restriction_counter; i++)
	{
	 	if((valid_restrictions[i][counter-2] == 1) || (valid_restrictions[i][counter-2] == 0))
	 	{
	 		final_restrictions_with_extra_variables[i][extra_variables_counter] = 1;
	 		extra_variables_counter++;
	 		virtual_variables++;
	 	}
	}

	printf("\n\nRestricciones \n"); 
	for (int i = 0; i < restriction_counter; i++) 
	{ 
		for (int j = 0; j < total_colums; j++) { 
			printf("%2f ", final_restrictions_with_extra_variables[i][j]); 
		} 
		printf("\n"); 
	} 
	printf("######################################\n\n");
    
}



void second_pre_prosessing(char *problem_name, char *variables[], double restrictions[11][11], 
	int restriction_counter, int extra_pages, int problemType, double simplex_matrix[rows][cols])
{
	// Count the columns
	int counter = 0;
	for (int j = 0; j < 9; j++){ // col
		int flag = 0;
		for (int i = 0; i < restriction_counter; i++){ // fil
			if (restrictions[i][j] != 0)
			{
				flag = 1;
			}
		}
		if (flag == 1)
		{
			counter++;
		}
	}
	// Omito los símbolos y el resultado.	
	counter += 2;

	// Delete the column without use. 
	double valid_restrictions[restriction_counter][counter]; // 
	int col = 0;
	int varCol = -1;
	for (int j = 0; j < 9; j++) // col //
	{
		int flag = 0;
		for (int i = 0; i < restriction_counter; i++) // fil
		{
			if (restrictions[i][j] != 0 && !flag)
			{
				// add the restriction 
				for (int k = 0; k < restriction_counter; k++)
				{
					valid_restrictions[k][col] = restrictions[k][j];
				}
				col++;
				flag = 1;
			}
		}
		if (flag == 0)
		{
			variables[varCol] = "";
		}
		varCol++;
	}
	for (int i = 0; i < restriction_counter; i++)
	{
		valid_restrictions[i][counter-2] = restrictions[i][9]; 
		valid_restrictions[i][counter-1] = restrictions[i][10];  
	}

	// Count of the extra variables that exist in the problem  
	int extra_column = 0;
    for (int i = 1; i < restriction_counter; i++)
    {
    	if (valid_restrictions[i][counter-2] == 0){extra_column++;}
    	if (valid_restrictions[i][counter-2] == 1){extra_column += 2;}
    	if (valid_restrictions[i][counter-2] == 2){extra_column++;}
    }
    
    // Create the simplex Matrix.
    for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			simplex_matrix[i][j] = 0;
		}
	}

	simplex_matrix[0][0] = 1;


	///////////////////////////////
	// Construction of the table //
	///////////////////////////////

	// Add variables values 
	for (int i = 0; i < rows; i++)
	{
		for (int j = 1; j < counter - 2; j++)
		{
			simplex_matrix[i][j] = valid_restrictions[i][j];
		}
		simplex_matrix[i][cols-1] = valid_restrictions[i][counter-1];
	}


	// add olgura variables
	int extra_variables_counter = counter - 2;
	for (int i = 1; i < rows; i++)
	{
	 	if (valid_restrictions[i][counter - 2] == 2)
	 	{
	 		simplex_matrix[i][extra_variables_counter] = 1;
	 		extra_variables_counter++;
	 	}
	} 

	// add excess variables 
	for (int i = 1; i < rows; i++)
	{
	 	if (valid_restrictions[i][counter - 2] == 1)
	 	{
	 		simplex_matrix[i][extra_variables_counter] = -1;
	 		extra_variables_counter++;
	 	}
	}

	// add artificial variables 
	for (int i = 1; i < rows; i++)
	{
	 	if((valid_restrictions[i][counter-2] == 1) || (valid_restrictions[i][counter-2] == 0))
	 	{
	 		simplex_matrix[i][extra_variables_counter] = 1;
	 		extra_variables_counter++;
	 	}
	}

	for (int i = 1; i < cols; i++)
	{
		if (simplex_matrix[0][i] != 0){
			simplex_matrix[0][i] *= -1;
		}
	}
    
}

// Receive the information and sent them to pre_prosessing 
void receive_data(char *problem_name, char *variables[], double restrictions[10][10], int *tot_counter,
	int extra_pages, int problemType, double objFunction[], double final_restrictions_objFunction[11][11])
{
	// Select the valid restrinction
	double valid_restrictions[10][10];
	double final_restrictions[10][10];
	(*tot_counter) = 0;

	for (int i = 0; i < 10; i++)
    {
    	// Check if the restriction is valid or not 
    	int valid_flag = 0;
    	for (int j = 0; j < 10; j++)
    	{
    		if ((restrictions[i][j] != 0) && (j != 8)  )
    		{
    			valid_flag = 1;
    		}
    	}
    	// If is a valid restriction
    	if (valid_flag == 1)
    	{
    		for (int k = 0; k < 10; k++)
    		{
    			valid_restrictions[(*tot_counter)][k] = restrictions[i][k];
    		}
    		(*tot_counter)++;
    	}
    }
    int counter = (*tot_counter);

    // Check the problem name 
	if (!strcmp(problem_name, "")){problem_name = "Default_Problem_Name";}	

	// Convet the restriction table to double 
	for (int i = 0; i < counter; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			final_restrictions[i][j] = (double) valid_restrictions[i][j];
		}
	}

	for (int i = 0; i < 11; i++)
    {
    	for (int j = 0; j < 11; j++)
	    {
	       	final_restrictions_objFunction[i][j] = 0.0;
	    }
    }
	final_restrictions_objFunction[0][0] = 1;
	for (int i = 0; i < 8; i++)
	{
		final_restrictions_objFunction[0][i+1] = (double) objFunction[i];
	}
              

	for (int i = 0; i < 10; i++)
    {
    	for (int k = 0; k < 10; k++)
	    {
	       	final_restrictions_objFunction[i+1][k+1] = final_restrictions[i][k];
	    }
    }
}


