/* In this place are written the fuctions that are going to be used in Simplex*/

// Fills the list M with zeros.
void fill_list_M(double list[cols])
{
	for(int i=0; i < cols; i++)
	{
		list[i] = 0.0;
	}
}

// Fills table with zeros.
void fill_list_boolean(int list[rows])
{
	for(int i=0; i < rows; i++)
	{
		list[i] = 0;
	}
}

char* concat_string(char* first, int num)
{
	char second[5];
	sprintf(second, "%d", num);
	strcat(first, second);
	return first;
}

// Do algebraic operations in the respective list M.
void algebraic_operations_with_M(double simplex_matrix[rows][cols], double list_M[cols], 
	int row_chosen, int pos_column, int opposite){
	
	for(int i = 0; i < cols; i++)
	{
		if (i != pos_column){
			double num = simplex_matrix[row_chosen][i] * opposite;
			list_M[i] += num;
		}
	}
}


// Files the table M that is going to be used in case of artificial variables.
void previous_step(double simplex_matrix[rows][cols], int num_var, int isMax,
	int num_art, double list_M[cols])
{
	// Multiplicate the list M.
	int M = 1;
	if (isMax == 1){
		M = 1;
	}else{
		M = -1;
	}

	int position = cols - num_art - 1; // Position in the column.

	// Searching for all artificial variables.
	for(int i = 0; i < num_art; i++)
	{
		// Searching for all rows.
		for(int j = 0; j < rows; j++)
		{
			int pos_new = position + i; // Position of the column
			if (simplex_matrix[j][pos_new] == 1){
				int opposite = -1 * M;
				algebraic_operations_with_M(simplex_matrix, list_M, j, 
					pos_new, opposite);
				break;
			}
		}
	}
}


void compare_table_with_previous(){};


// Add the position of the column in the base.
void add_base(int col_select, int base[cols], int *base_num)
{
	base[(*base_num)] = col_select;
}

// Add the position of the column in the no base.
void add_no_base(int col_select, int no_base[cols], int *base_no_num)
{
	no_base[(*base_no_num)] = col_select;
}

//Check if the bases' list is a identity matrix.
int verify_bases(int base[cols], int base_len,
	double simplex_matrix[rows][cols], double list_M[cols])
{
	int boolean_one[rows];
	fill_list_boolean(boolean_one);
	int error = 0;
	int success = 1;

	if (base_len == rows){
		// Look in all the table identifing the 1 in the array.
		for(int i = 0; i < rows; i++)
		{
			for(int j=0; j < rows; j++)
			{
				int pos = base[j];
				if (simplex_matrix[i][pos] == 1){
					boolean_one[i] = 1;
					break;
				}
			}
		}
		// Look if the identity is not completed.
		for(int i = 0; i < rows; i++)
		{
			if (boolean_one[i] != 1){
				return error;
			}
		}
	}else{
		return error;
	}

	return success;
}

// Insert bases and no bases in the variables.
void get_bases(int base[cols], int no_base[cols], int *base_num, int *base_no_num, 
	double simplex_matrix[rows][cols], double list_M[cols])
{
	(*base_num) = 0;
	(*base_no_num) = 0;

	// Look in all the table, looking first by columns.
	for(int i = 0; i < cols; i++)
	{
		int one_count = 0;
		int zero_count = 0;
		// Analyse the row.
		for(int j = 0; j < rows; j++)
		{
			if (simplex_matrix[j][i] == 0){
				zero_count++;
			}else if(simplex_matrix[j][i] == 1){
				one_count++;
			}else{
				break;
			}
		}

		// If the line has 0 - 0 - 1 - 0 - is a base line.
		if ( (one_count == 1) && (zero_count == (rows - 1)) && (list_M[i] == 0)){
			add_base(i, base, base_num);
			(*base_num)++; 
		}else{
			add_no_base(i, no_base, base_no_num);
			(*base_no_num)++; 
		}
	}
}


int verify_art_bases(double simplex_matrix[rows][cols], double list_M[cols], 
	int base[cols], int base_length, struct variable variables[cols])
{
	int error = 0, accept = 1;
	for(int i = 0; i < base_length; i++)
	{
		int pos = base[i];
		if(variables[pos].type == VIRTUAL){
			return error;
		}
		if (list_M[pos] > 0.00001 && list_M[pos] < -0.00001){
			return error;
		}
	}

	if (list_M[cols - 1] > 0.00001 && list_M[cols - 1] < -0.00001){
		return error;
	}
	return accept;
}


// Choose the most positive of the first row of the no base variables.
int choose_positive(int no_base[cols], int base_no_num, double simplex_matrix[rows][cols], 
	double list_M[cols], struct variable variables[cols])
{
	int positive = 0, pos_positive = 0, most_positive = 0;
	int is_negative = -1;

	for(int i = 0; i < base_no_num; i++)
	{
		int pos = no_base[i];
		// If I am in the finale column.
		if (pos == cols - 1){
			break;
		}

		// If I am in the artificial variables.
		if (variables[pos].type == VIRTUAL){
			break;
		}

		double posit = list_M[pos] * 100000;
		posit += simplex_matrix[0][pos];

		// If is positive?
		if(posit > 0){
			if (most_positive < posit){
				most_positive = posit;
				pos_positive = pos;
			}
			positive++;
		}
	}

	// If there are positive numbers, return the position of the most positive.
	if (positive > 0){
		return pos_positive;
	}
	return is_negative;
}


// Choose the most negative of the first row of the no base variables.
int choose_negative(int no_base[cols], int base_no_num, double simplex_matrix[rows][cols], 
	double list_M[cols], struct variable variables[cols])
{
	int negative = 0, pos_negative = 0, most_negative = 0;
	int is_positive = -1;

	for(int i = 0; i < base_no_num; i++)
	{
		int pos = no_base[i];
		// If I am in the finale column.
		if (pos == cols - 1){
			break;
		}

		// If I am in the artificial variables.
		if (variables[pos].type == VIRTUAL){
			break;
		}

		double negat = list_M[pos] * 100000;
		negat += simplex_matrix[0][pos];

		// If is negative?
		if(negat < 0){
			if (most_negative > negat){
				most_negative = negat;
				pos_negative = pos;
			}
			negative++;
		}
	}

	// If is negative, return the position of the most negative.
	if (negative > 0){
		return pos_negative;
	}
	return is_positive;
}

// Looking the pivot
void looking_pivots(double posible_pivots[rows], int position_pivots[rows], int *pivots, 
	int pos_column, double simplex_matrix[rows][cols])
{
	int last_pos = cols - 1;
	fill_list_boolean(position_pivots);
	// Indicate the position of the positive pivots.
	for(int i = 1; i < rows; i++)
	{
		if (simplex_matrix[i][pos_column] > 0){
			double val = simplex_matrix[i][last_pos] / simplex_matrix[i][pos_column];

			posible_pivots[(*pivots)] = val;
			position_pivots[(*pivots)] = i;
			(*pivots)++;
		}
	}
}

// Function that selects the position of the pivot or return multiples solutions.
int choose_pivot(double posible_pivots[rows], int position_pivots[rows], 
	int less_pivots[rows], int *num_ties, int pivots)
{
	double lesser = posible_pivots[0]; // The less value.
	int count = 0; 	// Numbers of ties.
	int pos_less = position_pivots[0];
	int multiple_solution = -1;
	less_pivots[count] = position_pivots[0];


	// Select the less value of the pivot.
	for(int i = 1; i < pivots; i++)
	{
		double val = posible_pivots[i];
		if (val < lesser){
			lesser = val;
			count = 0;
			pos_less = position_pivots[i];
		}else if(val == lesser){
			count++;
			less_pivots[count] = position_pivots[i]; // Select the position of the less value.
		}
	}

	// If there are more than one, we have multiple solutions.
	if (count > 0){
		(*num_ties) = count;
		return multiple_solution;
	}
	return pos_less; // Return the position of the pivot.
}

// Makes operation that convert the column in one identity column.
void alg_op_zero(int row_chosen, int column_chosen, 
	double simplex_matrix[rows][cols], double list_M[cols])
{
	double x = 0;

	// If the pivot is different to 1, become 1.
	if (simplex_matrix[row_chosen][column_chosen] != 1){
		x = 1 / simplex_matrix[row_chosen][column_chosen];

		for(int j = 0; j < cols; j++)
		{
			simplex_matrix[row_chosen][j] = simplex_matrix[row_chosen][j] * x;
		}
	}
}

// Makes operation that convert the column in one identity column.
void alg_op_others(int row_chosen, int column_chosen, 
	double simplex_matrix[rows][cols], double list_M[cols])
{

	// Converts the other's row in 0.
	for (int i = 0; i < rows; i++)
	{
		if (i == 0 && list_M[column_chosen] != 0){
			double opposite_M = -1 * list_M[column_chosen];
			double opposite = -1 * simplex_matrix[i][column_chosen];
			for(int j = 0; j < cols; j++)
			{
				list_M[j] = (opposite_M * simplex_matrix[row_chosen][j]
										+ list_M[j]);
				simplex_matrix[i][j] = (opposite * simplex_matrix[row_chosen][j]) + 
										simplex_matrix[i][j];
			}
		}else if (row_chosen != i){
			double opposite = -1 * simplex_matrix[i][column_chosen];
			for(int j = 0; j < cols; j++)
			{
				simplex_matrix[i][j] = (opposite * simplex_matrix[row_chosen][j]) + 
										simplex_matrix[i][j];
			}
		}
	}
}


void write_solution(double simplex_matrix[rows][cols], int base[cols], 
	struct variable variables[cols], int base_length)
{
	int pos_base = 0;
	int pos_in_base = 0;

	for (int pos_var = 0; pos_var < cols - 1; pos_var++)
	{
		if (pos_base < base_length){
			pos_in_base = base[pos_base];
		}else{
			pos_in_base = -1;
		}
		// If there is in the base.
		if (pos_var == pos_in_base){
			for(int i = 0; i < rows; i++)
			{
				if (simplex_matrix[i][pos_var] == 1){
					variables[pos_var].value = simplex_matrix[i][cols - 1];
					break;
				}
			}
			pos_base++;
		}else{
			variables[pos_var].value = 0.0;
		}
	}
}

void copy_solution(struct variable target[cols], struct variable source[cols])
{
	for(int i = 0; i < cols; i++)
	{
		target[i].type = source[i].type;
		strcpy(target[i].original_name, source[i].original_name);
		//target[i].original_name = source[i].original_name;
		target[i].value = source[i].value;
	}
}


int eval_multiple_solutions(double simplex_matrix[rows][cols], int no_base[cols], 
	struct variable variables[cols], int no_base_length)
{
	int there_are_mult_sol = -1;
	int pos_no_base = 0;

	for(int i = 0; i < no_base_length; i++)
	{
		pos_no_base = no_base[i];
		if ((variables[pos_no_base].type == VARIABLE || variables[pos_no_base].type == SLACK || 
			variables[pos_no_base].type == EXCESS) && simplex_matrix[0][pos_no_base] == 0.0){
			there_are_mult_sol = pos_no_base;
		break;
		}
	}
	return there_are_mult_sol;
}

void print_base_table(int num_var, int table[num_var], int table_len)
{
	printf("\n");
	for(int i=0; i < table_len; i++)
	{
		printf("- %d -", table[i]);
	}
	printf("\n");
}

void print_M_table(int num_var, double table[num_var], int table_len)
{
	printf("List M: \n");
	for(int i=0; i < table_len; i++)
	{
		printf("- %f -", table[i]);
	}
	printf("\n \n");
}

void print_table(double simplex_matrix[rows][cols])
{
	printf("Table: \n");
	for(int i=0; i < rows; i++)
	{
		printf("|");
		for(int j=0; j < cols; j++)
		{
			if (j == cols - 1){
				printf(" %f ", simplex_matrix[i][j]);
			}else{
				printf(" %f -", simplex_matrix[i][j]);
			}
		}
		printf("| \n");
	}
	printf("\n");
}

