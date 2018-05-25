#include "simplex_functions.c"

//#############################################################
// Review all the tables saved.
//##########################################################
void step_one(double simplex_matrix[rows][cols], double list_M[cols], 
	struct variable variables[cols], int step)
{
	compare_table_with_previous();

	if (show_intermediate_tables == 0){
		return;
	}
	
	char word[40];
	strcpy(word, "Iteration ");
	char* title = concat_string(word, step_counter);

	char word_two[40];
	strcpy(word_two, "Step ");
	char* title_two = concat_string(word_two, step);
	start_table(table_file, title_two, title);
	generate_Table(table_file, simplex_matrix, list_M, variables, "Table");
	end_table(table_file);
}

//#############################################################
// Determine the bases and no bases.
//##########################################################
enum SOLUTION step_two(double simplex_matrix[rows][cols], double list_M[cols],
	int base[cols], int *base_length, int no_base[cols], int *no_base_length, 
	struct variable variables[cols], int step)
{
	int state;
	int len_base;
	get_bases(base, no_base, base_length, no_base_length, simplex_matrix, list_M);
	len_base = (*base_length);
	state = verify_bases(base, len_base, simplex_matrix, list_M);

	if (state == 0){
		// It's not a identity matriz.
		printf("There is not factible. \n");
		return NO_FACTIBLE;
	}

	if (no_base_length <= 0){
		// There is a problem with the matriz.
		printf("There is not factible. \n");
		return NO_FACTIBLE;
	}

	if (show_intermediate_tables == 0){
		return FACTIBLE;
	}

	char word[40];
	strcpy(word, "Iteration ");
	char* title = concat_string(word, step_counter);

	char word_two[40];
	strcpy(word_two, "Step ");
	char* title_two = concat_string(word_two, step);
	start_table(table_file, title_two, title);
	generate_table_with_bases(table_file, simplex_matrix, list_M, base, variables, "Table");
	text_base(table_file);
	end_table(table_file);
	
	return FACTIBLE;
}

//#############################################################
// Determine the most positive and negative of the row 0.
//##########################################################
enum SOLUTION step_three(double simplex_matrix[rows][cols], double list_M[cols], 
	int no_base[cols], int no_base_length, int isMax, struct variable variables[cols], int step)
{
	int column_chosen;
	int are_positive = -1;
	char* text;

	if (isMax == 1){
		column_chosen = choose_negative(no_base, no_base_length, 
		simplex_matrix, list_M, variables);
		text = "Choose the most negative";
	}else{
		column_chosen = choose_positive(no_base, no_base_length, 
		simplex_matrix, list_M, variables);
		text = "Choose the most positive";
	}

	if (column_chosen == are_positive){
		// All the numbers of the first row are positive. We have finished.
		printf("We have finished \n");
		return RESOLVED;
	}

	if (show_intermediate_tables == 0){
		return column_chosen;
	}

	char word[40];
	strcpy(word, "Iteration ");
	char* title = concat_string(word, step_counter);

	char word_two[40];
	strcpy(word_two, "Step ");
	char* title_two = concat_string(word_two, step);
	start_table(table_file, title_two, title);
	generate_table_negative(table_file, simplex_matrix, list_M, column_chosen, 
		variables, "Table");
	text_most(table_file, text);
	end_table(table_file);

	return column_chosen;
}

//#############################################################
// Choose the pivot.
//##########################################################
enum SOLUTION step_four(double simplex_matrix[rows][cols], double posible_pivots[rows], 
	int position_pivots[rows], int column_chosen, int step, int ties[rows], 
	int *pivots, int *num_ties, double list_M[cols], struct variable variables[cols])
{
	int pos_pivot, num_pivots;
	int multiple_solution = -1;

	looking_pivots(posible_pivots, position_pivots, pivots, column_chosen, simplex_matrix);

	num_pivots = (*pivots);
	if (num_pivots < 1){
		printf("This problem is bounded. \n");
		optimal_solution = column_chosen; // It's gonna indicate the place when it falls.
		return BOUNDED;
	}

	// The pivot is the position of the row in which the pivot is here.
	num_pivots = (*pivots);
	pos_pivot = choose_pivot(posible_pivots, position_pivots, ties, num_ties, num_pivots);

	print_table(simplex_matrix);
	if (pos_pivot == multiple_solution){
		// Se generan las multiples soluciones.
		printf("Generate multiple solutions to this point.\n");
	}

	if (show_intermediate_tables == 0){
		return pos_pivot;
	}

	char text[50];
	sprintf(text, "The pivot selected is : %.4f\n", simplex_matrix[pos_pivot][column_chosen]);

	char word[40];
	strcpy(word, "Iteration ");
	char* title = concat_string(word, step_counter);

	char word_two[40];
	strcpy(word_two, "Step ");
	char* title_two = concat_string(word_two, step);
	start_table(table_file, title_two, title);
	generate_fractions(table_file, simplex_matrix, num_pivots, position_pivots, column_chosen, pos_pivot);
	generate_table_pivot(table_file, simplex_matrix, list_M, column_chosen, 
	 pos_pivot, variables, "Table");
	
	text_most(table_file, text);
	end_table(table_file);

	return pos_pivot;
}

//#############################################################
// Review all the tables saved.
//##########################################################
void step_five(double simplex_matrix[rows][cols], double list_M[cols], int column_chosen, 
	int pos_pivot, struct variable variables[cols], int step)
{
	alg_op_zero(pos_pivot, column_chosen, simplex_matrix, list_M);

	if (show_intermediate_tables){
		char word[40];
		strcpy(word, "Iteration ");
		char* title = concat_string(word, step_counter);
		char* text_one = "Become the pivot in one (all row is afected).";

		char word_two[40];
		strcpy(word_two, "Step ");
		char* title_two = concat_string(word_two, step);
		start_table(table_file, title_two, title);
		generate_table_zero(table_file, simplex_matrix, list_M, pos_pivot, column_chosen,
			variables, "Table");
		text_most(table_file, text_one); 
		end_table(table_file);	
	}

	alg_op_others(pos_pivot, column_chosen, simplex_matrix, list_M);

	if (show_intermediate_tables){
		char word_three[40];
		strcpy(word_three, "Iteration ");
		char* title_three = concat_string(word_three, step_counter);
		char* text_two = "Become the others to zero.";

		char word_four[40];
		strcpy(word_four, "Step ");
		char* title_four = concat_string(word_four, step);
		start_table(table_file, title_four, title_three);
		generate_table_one(table_file, simplex_matrix, list_M, pos_pivot, column_chosen, 
			variables, "Table");
		text_most(table_file, text_two);
		end_table(table_file);
	}
}


//#############################################################
// Solution of the Simplex.
//##########################################################
enum SOLUTION Simplex(double simplex_matrix[rows][cols], double list_M[cols], int isMax,
	struct variable variables[cols])
{
	int pos_pivot = 0, step = 1;
	int base[cols], no_base[cols], position_pivots[rows], ties[rows];
	double posible_pivots[rows];
	int base_num = 0, base_no_num = 0, pivots = 0, num_ties = 0;
	enum SOLUTION factible_state;
	int column_chosen;

	step_one(simplex_matrix, list_M, variables, step);
	step++;

	factible_state = step_two(simplex_matrix, list_M, base, &base_num, no_base,
	 &base_no_num, variables, step);

	if (factible_state != FACTIBLE){
		return factible_state;
	}
	step++;

	factible_state = step_three(simplex_matrix, list_M, no_base, base_no_num, 
		isMax, variables, step);

	if (factible_state == RESOLVED){
		return factible_state;
	}
	column_chosen = factible_state;
	step++;

	factible_state = step_four(simplex_matrix, posible_pivots, position_pivots, 
		column_chosen, step, ties, &pivots, &num_ties, list_M, variables);

	if (factible_state == BOUNDED){
		return factible_state;
	}
	pos_pivot = factible_state;
	step++;

	step_five(simplex_matrix, list_M, column_chosen, pos_pivot, variables, step);

	step_counter++;
	return Simplex(simplex_matrix, list_M, isMax, variables);
}

// Do the preprocess to Simplex.

enum SOLUTION pre_Simplex(double simplex_matrix[rows][cols], double list_M[cols],
	int isMax, struct variable variables[cols])
{
	int num_art_var = 0;
	fill_list_M(list_M); // Fills with zeros.

	/* Show the first table */
	char word[40];
	strcpy(word, "Initial Table ");
	start_table(table_file, "Original table", word);
	generate_Table(table_file, simplex_matrix, list_M, variables, "Table");
	end_table(table_file); 

	// Busque en las variables si hay variables artificiales.
	for(int i = 0; i < cols; i++)
	{
		if (variables[i].type == VIRTUAL){
			num_art_var++;
		}
	}

	if (num_art_var > 0)
	{
		strcpy(word, "Previous Step");
		previous_step(simplex_matrix, cols, isMax, num_art_var, list_M); // Put M operations

		if (show_intermediate_tables){
			start_table(table_file, "Table with new Numbers", word);
			generate_Table(table_file, simplex_matrix, list_M, variables, "Table");
			end_table(table_file);
		}
	}

	enum SOLUTION state = Simplex(simplex_matrix, list_M, isMax, variables);
	/* Show the first table */
	char word_2[40];
	strcpy(word_2, "Last Table ");
	start_table(table_file, "Final Table", word_2);
	generate_Table(table_file, simplex_matrix, list_M, variables, "Result");
	end_table(table_file); 
	return state;
}


void generate_multiple_solutions(struct variable solution_1[cols], 
	struct variable solution_2[cols], int isMax)
{
	int num_solutions = 5;
	struct variable solutions[cols][num_solutions];
	double alpha = 0.25;

	for(int i = 2; i < num_solutions; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			if (solution_1[j].type == VARIABLE || solution_1[j].type == SLACK || 
				solution_1[j].type == EXCESS)
			{
				double first = alpha * solution_1[j].value;
				double second = (1 - alpha) * solution_2[j].value;
				solutions[j][i].value = first + second;
			}else{
				solutions[j][i].value = solution_1[j].value;
			}
			solutions[j][i].type = solution_1[j].type;
			//solutions[j][i].original_name = solution_1[j].original_name;
			strcpy(solutions[j][i].original_name, solution_1[j].original_name);
		}
		alpha += 0.25;
	}

	for(int i = 0; i < cols; i++)
	{
		solutions[i][0].value = solution_1[i].value;
		solutions[i][0].type = solution_1[i].type;
		//solutions[i][0].original_name = solution_1[i].original_name;
		strcpy(solutions[i][0].original_name, solution_1[i].original_name);
	}

	for(int i = 0; i < cols; i++)
	{
		solutions[i][1].value = solution_2[i].value;
		solutions[i][1].type = solution_2[i].type;
		//solutions[i][1].original_name = solution_2[i].original_name;
		strcpy(solutions[i][1].original_name, solution_2[i].original_name);
	}
	multiple_solution_latex(table_file, num_solutions, solutions, isMax);
}

//#############################################################
// Determine the solution number two.
//##########################################################
void get_other_solution(double simplex_matrix[rows][cols], struct variable variables[cols],
	int isMax, int column_chosen)
{
	struct variable solution_1[cols];
	struct variable solution_2[cols];
	int position_pivots[rows], ties[rows];
	int row_pivot = 0;
	double list_M[cols], posible_pivots[rows];
	int base[cols], no_base[cols], no_base_length = 0, base_length = 0;
	int pivots = 0, num_ties = 0, step = 0;
	enum SOLUTION factible_state;

	fill_list_M(list_M); // Fills with zeros.

	copy_solution(solution_1, variables); // Copia la solución en la matriz solución.

	factible_state = step_four(simplex_matrix, posible_pivots, position_pivots, 
		column_chosen, step, ties, &pivots, &num_ties, list_M, variables);

	printf("Pivot : %d \n", factible_state);

	row_pivot = factible_state;
	step_five(simplex_matrix, list_M, column_chosen, row_pivot, variables, step);
	get_bases(base, no_base, &base_length, &no_base_length, simplex_matrix, list_M);
	write_solution(simplex_matrix, base, variables, base_length);

	copy_solution(solution_2, variables);

	generate_multiple_solutions(solution_1, solution_2, isMax);
}


//#############################################################
// Determines if the solution is factible and there are not problem. 
// Also, if it has multiple solutions.
//##########################################################
void analyse_solution(double simplex_matrix[rows][cols], struct variable variables[cols],
	double list_M[cols], int isMax)
{
	int state = 0;
	char *title, *title_two, *text_one;
	int base[cols], no_base[cols], no_base_length = 0, base_length = 0;

	get_bases(base, no_base, &base_length, &no_base_length, simplex_matrix, list_M);
	state = verify_art_bases(simplex_matrix, list_M, base, base_length, variables);
	if (state == 0){
		// Genero latex para el caso NO FACTIBLE.
		title = "No Factible";
		title_two = "Finished";
		text_one = "One base has a M in its values.";
		start_table(table_file, title_two, title);
		generate_table_with_bases(table_file, simplex_matrix, list_M, base, variables, "Base with M");
		text_most(table_file, text_one); 
		end_table(table_file);
		return;
	}

	write_solution(simplex_matrix, base, variables, base_length);
	int mul_solutions = eval_multiple_solutions(simplex_matrix, no_base, variables, no_base_length);

	solution_latex(table_file, variables, isMax);

	if (mul_solutions > 0){
		title = "Multiple Solutions";
		title_two = "Formula";
		start_table(table_file, title_two, title);
		title_multiple_solution(table_file);
		end_table(table_file);
		get_other_solution(simplex_matrix, variables, isMax, mul_solutions);
	}
}


//#############################################################
// Verifies the state of the solution.
//##########################################################
void solution(double simplex_matrix[rows][cols], double list_M[cols], struct variable variables[cols],
	enum SOLUTION state, int isMax)
{
	char *title;
	char *title_two;
	char *text_one;

	switch(state)
	{
		case BOUNDED:
			// Genero latex para el caso BOUNDED.
			title = "No Bounded";
			title_two = "Finished";
			text_one = "The case is no bounded. There's no factible.";
			start_table(table_file, title_two, title);
			generate_table_bounded(table_file, simplex_matrix, list_M, 
					optimal_solution, variables, "No Bounded Table");
			text_most(table_file, text_one); 
			end_table(table_file);
			return;
		case NO_FACTIBLE:
			// Genero latex para el caso NO FACTIBLE.
			title = "No Factible";
			title_two = "Finished";
			text_one = "There are problem with the bases. There's no factible.";
			start_table(table_file, title_two, title);
			generate_Table(table_file, simplex_matrix, list_M, 
					variables, "No Factible");
			text_most(table_file, text_one); 
			end_table(table_file);
			return;
		default:
			analyse_solution(simplex_matrix, variables, list_M, isMax);
	}
}