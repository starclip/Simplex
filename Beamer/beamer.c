// Presentación Beamer

void create_latex(FILE *output)
{
    fprintf(output, "%s\n", "\\documentclass{beamer}");
    fprintf(output, "%s\n", "\\usepackage[utf8]{inputenc}");
    fprintf(output, "%s\n", "\\usepackage{color, colortbl}");
    fprintf(output, "%s\n", "\\usepackage{tabu}");
    fprintf(output, "%s\n", "\\usepackage{ragged2e}");
    fprintf(output, "%s\n", "\\usepackage{wasysym}");
    fprintf(output, "%s\n", "\\usepackage{amsmath}");
    fprintf(output, "%s\n", "\\usetheme[progressbar=frametitle]{metropolis}");
    fprintf(output, "%s\n", "\\usecolortheme{albatross}");
    fprintf(output, "%s\n", "\\setbeamercolor{normal text}{bg=black, fg=white}");
    fprintf(output, "%s\n", "\\setbeamerfont{normal text}{size=3pt}");
}

//#############################################################
// Genero la portada.
//#############################################################
void cover(FILE *output)
{
    fprintf(output, "%s\n", "\\title{\\small IC6400 - Operations Research \\newline");
    fprintf(output, "%s\n", "       \\large Project 4: Simplex }");
    fprintf(output, "%s\n", "\\author{\\large Jason Barrantes Arce  2015048456 \\newline");
    fprintf(output, "%s\n", "                 Steven Bonilla Zuniga 2015048456 \\newline");
    fprintf(output, "%s\n", "                 Prof: Francisco Torres Rojas \\newline \\newline}");
    fprintf(output, "%s\n", "\\date{I Semester 2018}");
    fprintf(output, "%s\n", "\% start the document");
    fprintf(output, "%s\n", "\\begin{document}");
    fprintf(output, "%s\n", "\\frame{\\titlepage}");
}


//#############################################################
// Definition of simplex
//#######################################################
void definitions(FILE *output)
{
	fprintf(output, "%s\n", "\\begin{frame}");
	fprintf(output, "%s\n", "\\color{yellow}");
	fprintf(output, "%s\n", "{\\fontsize{15}{10}\\selectfont Simplex \\newline \\newline}");
	fprintf(output, "%s\n", "\\color{white}");
	fprintf(output, "%s\n", "\\frametitle{Simplex's definition}");
	fprintf(output, "%s\n", "{\\fontsize{8}{10}\\selectfont Simplex is a mechanic method \n\
		that looks for the optimus solution of a LP problem. Its objective is solving linear \n\
		programming problems. To do this, uses a matrix to find the solution. \n\
		Simplex' inputs are the constraints and the objective function that the user (you) wrote, \n\
		making a matrix N x M, in which the N are the numbers of variables and M are the  \n\
		total of restrictions (the basic's constraints are not considered) and the objective function.}");
	fprintf(output, "%s\n", "\\end{frame}");

	fprintf(output, "%s\n", "\\begin{frame}");
	fprintf(output, "%s\n", "\\color{yellow}");
	fprintf(output, "%s\n", "\\frametitle{Simplex steps}");
	fprintf(output, "%s\n", "{\\fontsize{15}{10}\\selectfont Steps \\newline}");
	fprintf(output, "%s\n", "\\color{white}");
	fprintf(output, "%s\n", "{\\fontsize{8}{10}\\selectfont \n\
		\\color{red}{0)} \\color{white}{If there are artificial variables, \n\
			you have to add M to the objective function. \n\
		+M if you are maximizing and -M if you are minimizing.}  \\newline \n\
		\\color{red}{1)} \\color{white}{Become inequalities to equalities. \n\
			If the inequality is less than, you have to add a slack variable. \n\
		In opposite, you have to rest a excess variable.} \\newline \n\
		\\color{red}{2)} \\color{white}{Objective function is equalized to zero.} \\newline \n\
		\\color{red}{3)} \\color{white}{Create a matrix with the variables as columns and \n\
			the number of constrains and objective function as rows.} \\newline \n\
		Thereafter, you have to drop these M variables that are ubicated in \n\
		the same columns that the artificial variables.}");
	fprintf(output, "%s\n", "\\end{frame}");

	fprintf(output, "%s\n", "\\begin{frame}");
	fprintf(output, "%s\n", "\\color{yellow}");
	fprintf(output, "%s\n", "\\frametitle{Simplex mechanic}");
	fprintf(output, "%s\n", "{\\fontsize{15}{10}\\selectfont Mechanics \\newline}");
	fprintf(output, "%s\n", "\\color{white}");
	fprintf(output, "%s\n", "{\\fontsize{8}{10}\\selectfont \n\
		\\color{red}{0)} \\color{white}{Compare the last tables with the actual one. \n\
			If is different or last tables is empty, continue. If is not, it's a degenerate problem.} \n\
		\\newline \n\
		\\color{red}{1)} \\color{white}{We divide the variables that are in the base. \n\
			And those that do not.} \\newline \n\
		\\color{red}{2)} \\color{white}{Select the column of the most negative if you are maximizing, \n\
			or the most positive if you are minimizing of the no base variables. \n\
			If there aren't you have finished} \\newline \n\
		\\color{red}{3)} \\color{white}{Choose the pivot in the selected column. Go through the \n\
			entire row. The pivot is the lesser of the division of the element of the last column \n\
			between the actual column value.} \\newline \n\
		\\color{red}{4)} \\color{white}{Become the column in a identity column. The pivot \n\
			has to value 1. You can do this through algebraic operations.} \\newline \n\
		\\color{red}{5)} \\color{white}{Go to the step 0.} }");
	fprintf(output, "%s\n", "\\end{frame}");
}

void text_base(FILE *output)
{
	fprintf(table_file, "%s\n", "\\definecolor{RedGayran}{rgb}{0.5,0,0.12}");
    fprintf(table_file, "%s\n", "\\definecolor{CadetBlue}{rgb}{0.37,0.62,0.63}");
	fprintf(output, "%s\n", "{\\fontsize{8}{10}\\selectfont ");
	fprintf(output, "%s\n", "\\begin{center}");
	fprintf(output, "%s\n", "\\color{RedGayran}{Base} \\color{white}{-} \\color{CadetBlue}{No Base}");
	fprintf(output, "%s\n", "\\end{center}");
	fprintf(output, "%s\n", " }");
}

void text_most(FILE *output, char* text)
{
	fprintf(table_file, "%s\n", "\\definecolor{RedGayran}{rgb}{0.5,0,0.12}");
    fprintf(table_file, "%s\n", "\\definecolor{CadetBlue}{rgb}{0.37,0.62,0.63}");
	fprintf(output, "%s\n", "{\\fontsize{8}{10}\\selectfont ");
	fprintf(output, "%s\n", "\\begin{center}");
	fprintf(output, "%s", "\\color{RedGayran}{");
	fprintf(output, "%s\n", text);
	fprintf(output, "%s", "} ");
	fprintf(output, "%s\n", "\\end{center}");
	fprintf(output, "%s\n", " }");
}


void generate_fractions(FILE *output, double simplex_matrix[rows][cols], int num_pivots, 
    int position_pivots[rows], int column_chosen, int pos_pivot)
{
    int last_pos = cols - 1;
    double pivot_fraction_selected = 0.0;
    fprintf(output, "%s\n", "\\definecolor{RedGayran}{rgb}{0.5,0,0.12}");
    fprintf(output, "%s\n", "\\definecolor{CadetBlue}{rgb}{0.37,0.62,0.63}");
    fprintf(output, "%s\n", "{\\fontsize{8}{10}\\selectfont ");
    fprintf(output, "%s\n", "\\begin{center}");
    for(int i=0; i < num_pivots; i++)
    {
        int pos = position_pivots[i];
        double first = simplex_matrix[pos][last_pos];
        double second = simplex_matrix[pos][column_chosen];
        pivot_fraction_selected = first / second;
        if (pos == pos_pivot){
            fprintf(output, "%s", "\\color{RedGayran}{");
        }else{
            fprintf(output, "%s", "\\color{CadetBlue}{");
        }

        fprintf(output, " $ \\frac{%.2f}{%.2f} = %.2f $ } ", first, 
            second, pivot_fraction_selected);
    }
    fprintf(output, "%s\n", "\\end{center}");
    fprintf(output, "%s\n", " }");
}

//#############################################################
// Start the frame with the title.
//#######################################################
void start_table(FILE *table_file, char* title, char* title_2)
{
	fprintf(table_file, "%s\n", "\\begin{frame}");
	fprintf(table_file, "%s\n", "\\color{yellow}");
	fprintf(table_file, "%s\n", "{\\fontsize{15}{10}\\selectfont ");
	fprintf(table_file, "%s} \\newline \\newline", title);
	fprintf(table_file, "%s\n", "\\color{white}");
	fprintf(table_file, "%s\n", "\\frametitle{");
	fprintf(table_file, "%s}", title_2);
}

//#############################################################
// End the table of the document
//#######################################################
void end_table(FILE *table_file)
{
	fprintf(table_file, "%s\n", "\\end{frame}");
}

//#############################################################
// Generate the row of the M.
//#######################################################
void generate_listM(FILE *table_file, double M_value, double matrix_value, int last_one)
{
	fprintf(table_file, "{\\fontsize{5}{7}\\selectfont ");
    if (M_value != 1){
        fprintf(table_file, "%.2fM", M_value);
    }else{
        fprintf(table_file, "%s", "M");
    }

    if (matrix_value != 0){
        fprintf(table_file, "+%.2f", matrix_value);
    }
    fprintf(table_file, "%s", "}");
    if (!last_one){
        fprintf(table_file, "%s", " &");
	}
}

//#############################################################
// Generate the start table.
//#######################################################
void generate_start_table(FILE *table_file, int num_vars, char *name)
{
    fprintf(table_file, "%s\n", "\\definecolor{Gray}{gray}{0.9}");
    fprintf(table_file, "%s\n", "\\definecolor{Cordovan}{rgb}{0.54,0.25,0.27}");
    fprintf(table_file, "%s\n", "\\definecolor{Caquis}{rgb}{0.40,0.24,0.2}");
    fprintf(table_file, "%s\n", "\\definecolor{CamoGreen}{rgb}{0.47,0.53,0.42}");
    fprintf(table_file, "%s\n", "\\definecolor{CadetBlue}{rgb}{0.37,0.62,0.63}");
    fprintf(table_file, "%s\n", "\\definecolor{Amaranth}{rgb}{0.9,0.17,0.31}");
    fprintf(table_file, "%s\n", "\\definecolor{RedGayran}{rgb}{0.5,0,0.12}");
    fprintf(table_file, "%s\n", "\\definecolor{Cool}{rgb}{0.0, 0.18, 0.39}");
    fprintf(table_file, "%s", "\\begin{table}\\renewcommand{\\arraystretch}");

    if (num_vars >= 10){
        fprintf(table_file, "%s\n", "{0.5}");
    }else{
        fprintf(table_file, "%s\n", "{1}");
    }
    fprintf(table_file, "%s", "\\caption{\\large \\textbf{");
    fprintf(table_file, "%s}}\n", name);
    fprintf(table_file, "%s\n", "\\centering");
    fprintf(table_file, "%s", "\\begin{tabular} { |");
    for(int i = 0; i < cols + 1; i++)
    {
        if (num_vars >= 10){
            fprintf(table_file, "%s", "m{0.6cm}|");  
        }else if (num_vars > 6 && num_vars < 10) {
            fprintf(table_file, "%s", "m{0.8cm}|");
        }else{
            fprintf(table_file, "%s", "m{1.3cm}|");
        }
    }
    fprintf(table_file, "%s\n", "}");
    fprintf(table_file, "%s\n", "\\hline");
}

//#############################################################
// Generate the table's names of the variables.
//#######################################################
void generate_names_table(FILE *table_file, struct variable variables[cols])
{
    fprintf(table_file, "%s\n", "\\rowcolor{Cool}");

    for(int i = 0; i < cols; i++)
    {
        if (i < cols - 1){
            fprintf(table_file, "%s", "\\centering \\tiny \\textbf{\\textcolor{CadetBlue}{");
            fprintf(table_file, "%s", variables[i].original_name);
            fprintf(table_file, "%s", "}} &");
        }else{
            fprintf(table_file, "%s\n", "\\tiny \\textbf{\\textcolor{CadetBlue}{\\#}} \\\\");
        }
    }
    fprintf(table_file, "%s\n", "\\hline");
}


//#############################################################
// Generate the table of simplex
//#######################################################
void generate_Table(FILE *table_file, double mat[rows][cols], 
	double list_M[cols], struct variable variables[cols], char* name)
{
    generate_start_table(table_file, cols, name);
    generate_names_table(table_file, variables);

    // Print the values of the tables.
    for(int i=0; i < rows; i++)
    {
        for(int j=0; j < cols; j++)
        {
        	// If you have to print the M in the table.
        	if (i == 0 && (list_M[j] > 0.00001 || list_M[j] < -0.00001)){
        		if (j == cols - 1){
        			generate_listM(table_file, list_M[j], mat[i][j], 1);
        		}else{
        			generate_listM(table_file, list_M[j], mat[i][j], 0);
        		}
        	}else{
        		if (j >= cols - 1){
	            	fprintf(table_file, "{\\fontsize{6}{7}\\selectfont %.2f}", mat[i][j]);
	            }else{
	            	fprintf(table_file, "{\\fontsize{6}{7}\\selectfont %.2f} &", mat[i][j]);
	            }
        	}
        }
        fprintf(table_file, "%s\n", " \\\\");
        fprintf(table_file, "%s\n", "\\hline");
    }
    fprintf(table_file, "%s\n", "\\end{tabular} \\\\");
    fprintf(table_file, "%s\n", "\\end{table}");
}

//#############################################################
// Generate the table of simplex
//#######################################################
void generate_table_negative(FILE *table_file, double mat[rows][cols], 
	double list_M[cols], int column_chosen, struct variable variables[cols], char* name)
{
    generate_start_table(table_file, cols, name);
    generate_names_table(table_file, variables);

    // Print the values of the tables.
    for(int i=0; i < rows; i++)
    {
        for(int j=0; j < cols; j++)
        {
        	// If you have to print the M in the table.
        	if (j == column_chosen && i == 0){
        		fprintf(table_file, "%s", "\\cellcolor{Caquis}");
        	}

        	if (i == 0 && (list_M[j] > 0.00001 || list_M[j] < -0.00001)){
        		if (j == cols - 1){
        			generate_listM(table_file, list_M[j], mat[i][j], 1);
        		}else{
        			generate_listM(table_file, list_M[j], mat[i][j], 0);
        		}
        	}else{
        		if (j >= cols - 1){
	            	fprintf(table_file, "{\\fontsize{6}{7}\\selectfont %.2f}", mat[i][j]);
	            }else{
	            	fprintf(table_file, "{\\fontsize{6}{7}\\selectfont %.2f} &", mat[i][j]);
	            }
        	}
        }
        fprintf(table_file, "%s\n", " \\\\");
        fprintf(table_file, "%s\n", "\\hline");
    }
    fprintf(table_file, "%s\n", "\\end{tabular} \\\\");
    fprintf(table_file, "%s\n", "\\end{table}");
}


//#############################################################
// Generate the table of simplex
//#######################################################
void generate_table_pivot(FILE *table_file, double mat[rows][cols], 
	double list_M[cols], int column_chosen, int row_chosen, struct variable variables[cols], char* name)
{
    generate_start_table(table_file, cols, name);
    generate_names_table(table_file, variables);

    // Print the values of the tables.
    for(int i=0; i < rows; i++)
    {
        for(int j=0; j < cols; j++)
        {
        	// If you have to print the M in the table.
        	if (j == column_chosen && i == row_chosen){
        		fprintf(table_file, "%s", "\\cellcolor{Cordovan}");
        	}

        	if (i == 0 && (list_M[j] > 0.00001 || list_M[j] < -0.00001)){
        		if (j == cols - 1){
        			generate_listM(table_file, list_M[j], mat[i][j], 1);
        		}else{
        			generate_listM(table_file, list_M[j], mat[i][j], 0);
        		}
        	}else{
        		if (j >= cols - 1){
	            	fprintf(table_file, "{\\fontsize{6}{7}\\selectfont %.2f}", mat[i][j]);
	            }else{
	            	fprintf(table_file, "{\\fontsize{6}{7}\\selectfont %.2f} &", mat[i][j]);
	            }
        	}
        }
        fprintf(table_file, "%s\n", " \\\\");
        fprintf(table_file, "%s\n", "\\hline");
    }
    fprintf(table_file, "%s\n", "\\end{tabular} \\\\");
    fprintf(table_file, "%s\n", "\\end{table}");
}


//#############################################################
// Generate the table of simplex
//#######################################################
void generate_table_bounded(FILE *table_file, double mat[rows][cols], 
    double list_M[cols], int column_chosen, struct variable variables[cols], char* name)
{
    generate_start_table(table_file, cols, name);
    generate_names_table(table_file, variables);

    // Print the values of the tables.
    for(int i=0; i < rows; i++)
    {
        for(int j=0; j < cols; j++)
        {
            // If you have to print the M in the table.
            if (j == column_chosen && i > 0){
                fprintf(table_file, "%s", "\\cellcolor{Cordovan}");
            }

            if (i == 0 && (list_M[j] > 0.00001 || list_M[j] < -0.00001)){
                if (j == cols - 1){
                    generate_listM(table_file, list_M[j], mat[i][j], 1);
                }else{
                    generate_listM(table_file, list_M[j], mat[i][j], 0);
                }
            }else{
                if (j >= cols - 1){
                    fprintf(table_file, "{\\fontsize{6}{7}\\selectfont %.2f}", mat[i][j]);
                }else{
                    fprintf(table_file, "{\\fontsize{6}{7}\\selectfont %.2f} &", mat[i][j]);
                }
            }
        }
        fprintf(table_file, "%s\n", " \\\\");
        fprintf(table_file, "%s\n", "\\hline");
    }
    fprintf(table_file, "%s\n", "\\end{tabular} \\\\");
    fprintf(table_file, "%s\n", "\\end{table}");
}

//#############################################################
// Generate the table of simplex
//#######################################################
void generate_table_one(FILE *table_file, double mat[rows][cols], 
	double list_M[cols], int row_chosen, int column_chosen, struct variable variables[cols], char* name)
{
    generate_start_table(table_file, cols, name);
    generate_names_table(table_file, variables);

    // Print the values of the tables.
    for(int i=0; i < rows; i++)
    {
        for(int j=0; j < cols; j++)
        {
        	// If you have to print the M in the table.
        	if (i != row_chosen && j != column_chosen){
        		fprintf(table_file, "%s", "\\cellcolor{Cordovan}");
        	}else if (i != row_chosen && j == column_chosen){
                fprintf(table_file, "%s", "\\cellcolor{Amaranth}");
            }

        	if (i == 0 && (list_M[j] > 0.00001 || list_M[j] < -0.00001)){
        		if (j == cols - 1){
        			generate_listM(table_file, list_M[j], mat[i][j], 1);
        		}else{
        			generate_listM(table_file, list_M[j], mat[i][j], 0);
        		}
        	}else{
        		if (j >= cols - 1){
	            	fprintf(table_file, "{\\fontsize{6}{7}\\selectfont %.2f}", mat[i][j]);
	            }else{
	            	fprintf(table_file, "{\\fontsize{6}{7}\\selectfont %.2f} &", mat[i][j]);
	            }
        	}
        }
        fprintf(table_file, "%s\n", " \\\\");
        fprintf(table_file, "%s\n", "\\hline");
    }
    fprintf(table_file, "%s\n", "\\end{tabular} \\\\");
    fprintf(table_file, "%s\n", "\\end{table}");
}

//#############################################################
// Generate the table of simplex
//#######################################################
void generate_table_zero(FILE *table_file, double mat[rows][cols], 
    double list_M[cols], int row_chosen, int column_chosen, struct variable variables[cols], char* name)
{
    generate_start_table(table_file, cols, name);
    generate_names_table(table_file, variables);

    // Print the values of the tables.
    for(int i=0; i < rows; i++)
    {
        for(int j=0; j < cols; j++)
        {
            // If you have to print the M in the table.
            if (i == row_chosen && j != column_chosen){
                fprintf(table_file, "%s", "\\cellcolor{Cordovan}");
            }else if (i == row_chosen && j == column_chosen){
                fprintf(table_file, "%s", "\\cellcolor{Amaranth}");
            }

            if (i == 0 && (list_M[j] > 0.00001 || list_M[j] < -0.00001)){
                if (j == cols - 1){
                    generate_listM(table_file, list_M[j], mat[i][j], 1);
                }else{
                    generate_listM(table_file, list_M[j], mat[i][j], 0);
                }
            }else{
                if (j >= cols - 1){
                    fprintf(table_file, "{\\fontsize{6}{7}\\selectfont %.2f}", mat[i][j]);
                }else{
                    fprintf(table_file, "{\\fontsize{6}{7}\\selectfont %.2f} &", mat[i][j]);
                }
            }
        }
        fprintf(table_file, "%s\n", " \\\\");
        fprintf(table_file, "%s\n", "\\hline");
    }
    fprintf(table_file, "%s\n", "\\end{tabular} \\\\");
    fprintf(table_file, "%s\n", "\\end{table}");
}

//#############################################################
// Generate the table of simplex
//#######################################################
void generate_table_with_bases(FILE *table_file, double mat[rows][cols], 
	double list_M[cols], int base[cols], struct variable variables[cols], char* name)
{
	int row_pos = 0;
    generate_start_table(table_file, cols, name);
    generate_names_table(table_file, variables);

    // Print the values of the tables.
    for(int i=0; i < rows; i++)
    {
        for(int j=0; j < cols; j++)
        {
        	// If you have to print the M in the table.
        	if (j == base[row_pos]){
        		fprintf(table_file, "%s\n", "\\cellcolor{RedGayran}");
        		row_pos++;
        	}else{
        		fprintf(table_file, "%s\n", "\\cellcolor{CadetBlue}");
        	}

        	if (i == 0 && (list_M[j] > 0.00001 || list_M[j] < -0.00001)){
        		if (j == cols - 1){
        			generate_listM(table_file, list_M[j], mat[i][j], 1);
        		}else{
        			generate_listM(table_file, list_M[j], mat[i][j], 0);
        		}
        	}else{
        		if (j >= cols - 1){
	            	fprintf(table_file, "{\\fontsize{6}{7}\\selectfont %.2f}", mat[i][j]);
	            }else{
	            	fprintf(table_file, "{\\fontsize{6}{7}\\selectfont %.2f} &", mat[i][j]);
	            }
        	}
        }
        row_pos = 0;
        fprintf(table_file, "%s\n", " \\\\");
        fprintf(table_file, "%s\n", "\\hline");
    }
    fprintf(table_file, "%s\n", "\\end{tabular} \\\\");
    fprintf(table_file, "%s\n", "\\end{table}");
}

//#############################################################
// Describe the objective function.
//#######################################################
void objective_function(FILE *output, double simplex_matrix[rows][cols],
    struct variable variables[cols], int isMax)
{
    fprintf(output, "%s\n", "{\\fontsize{15}{10}\\selectfont Objective Function \\newline}");
    fprintf(output, "%s\n", "\\color{white}");
    fprintf(output, "%s\n", "{\\fontsize{8}{10}\\selectfont ");

    if (isMax){
        fprintf(output, "%s", "\\textcolor{red}{MAX(Z)} = ");
    }else{
        fprintf(output, "%s", "\\textcolor{red}{MIN(Z)} = ");
    }

    for(int i = 1; i < cols - 1; i++)
    {
        double val = -1 * simplex_matrix[0][i];
        if (variables[i].type == VIRTUAL){
            fprintf(output, "%s", " + ");
            if (isMax){
                fprintf(output, "-M%s", variables[i].original_name);
            }else{
                fprintf(output, "+M%s", variables[i].original_name);
            }
        }else{
            if (i > 1 && val != 0){
                fprintf(output, "%s", " + ");
            }
            if (val != 0){
                fprintf(output, "%.1f$\\cdot$%s", val, variables[i].original_name);
            }
        }
    }
    fprintf(output, "%s", "} \\newline \\newline");
}

void define_restrictions(FILE *output, double simplex_matrix[rows][cols], 
    struct variable variables[cols], int isMax)
{
    fprintf(output, "%s\n", "\\color{yellow}");
    fprintf(output, "%s\n", "{\\fontsize{15}{10}\\selectfont Subject to: \\newline}");
    fprintf(output, "%s\n", "\\color{white}");
    fprintf(output, "%s\n", "{\\fontsize{8}{10}\\selectfont ");
    for(int i = 1; i < rows; i++)
    {

        for(int j = 1; j < cols; j++)
        {
            if (simplex_matrix[i][j] != 0){
                if (j == cols - 1){
                    fprintf(output, " %s ", " = ");
                    fprintf(output, "%.1f", simplex_matrix[i][j]);
                }else{
                    if (j > 1){
                        fprintf(output, "%s", " + ");
                    }
                    fprintf(output, "%.1f$\\cdot$%s", simplex_matrix[i][j], variables[j].original_name);
                }
            }
        }
        fprintf(output, "%s\n", " \\newline");
    }
    fprintf(output, "%s\n", "} ");
}


//#############################################################
// Original problem to solve
//#######################################################
void original_problem(FILE *output, double simplex_matrix[rows][cols], 
    struct variable variables[cols], int isMax)
{
	fprintf(output, "%s\n", "\\begin{frame}");
	fprintf(output, "%s\n", "\\color{yellow}");
	fprintf(output, "%s\n", "\\frametitle{Original problem}");

	objective_function(output, simplex_matrix, variables, isMax);
	define_restrictions(output, simplex_matrix, variables, isMax);

	fprintf(output, "%s\n", "\\end{frame}");
}

void title_multiple_solution(FILE *output)
{
    fprintf(table_file, "%s\n", "\\definecolor{RedGayran}{rgb}{0.5,0,0.12}");
    fprintf(table_file, "%s\n", "\\definecolor{CadetBlue}{rgb}{0.37,0.62,0.63}");
    fprintf(output, "%s\n", "\\definecolor{Cool}{rgb}{0.0, 0.18, 0.39}");
    fprintf(output, "%s\n", "{\\fontsize{14}{10}\\selectfont ");
    fprintf(output, "%s\n", "\\begin{center}");
    fprintf(output, "%s\n", "\\color{RedGayran}{");
    fprintf(output, "%s", "Solution 1 - $v$}");
    fprintf(output, "%s", " \\hspace{1.5cm} ");
    fprintf(output, "%s", "\\color{CadetBlue}{");
    fprintf(output, "%s", "Solution 2 - $w$");
    fprintf(output, "%s\n", "} \n \n");
    fprintf(output, "%s\n", "\\color{Cool}{$\\alpha_{1}$} = \\color{gray}{0.25} ");
    fprintf(output, "%s", " \\hspace{1cm} ");
    fprintf(output, "%s\n", "\\color{Cool}{$\\alpha_{2}$} = \\color{gray}{0.5} ");
    fprintf(output, "%s", " \\hspace{1cm} ");
    fprintf(output, "%s\n", "\\color{Cool}{$\\alpha_{3}$} = \\color{gray}{0.75} ");
    fprintf(output, "%s\n", "\\newline ");
    fprintf(output, "%s\n", "\\[");
    fprintf(output, "%s\n", "\\alpha_{i} \\cdot ");
    fprintf(output, "%s\n", "\\begin{pmatrix}");
    fprintf(output, "%s\n", "v_{0}\\\\");
    fprintf(output, "%s\n", "v_{1} \\\\");
    fprintf(output, "%s\n", "\\vdots \\\\");
    fprintf(output, "%s\n", "v_{n} ");
    fprintf(output, "%s\n", "\\end{pmatrix}");
    fprintf(output, "%s\n", " + (1 - \\alpha_{i}) \\cdot ");
    fprintf(output, "%s\n", "\\begin{pmatrix}");
    fprintf(output, "%s\n", "w_{0}\\\\");
    fprintf(output, "%s\n", "w_{1} \\\\");
    fprintf(output, "%s\n", "\\vdots \\\\");
    fprintf(output, "%s\n", "w_{n} ");
    fprintf(output, "%s\n", "\\end{pmatrix}");
    fprintf(output, "%s\n", "\\]");
    fprintf(output, "%s\n", "\\end{center}");
    fprintf(output, "%s\n", " }");
}

void multiple_solution_latex(FILE *output, int num_solutions, 
    struct variable solutions[cols][num_solutions], int isMax)
{
    double alpha = 0.25;
    for (int sol_count = 1; sol_count < num_solutions; sol_count++)
    {
        fprintf(output, "%s\n", "\\begin{frame}");
        fprintf(output, "%s\n", "\\color{yellow}");
        fprintf(output, "%s\n", "\\definecolor{CadetBlue}{rgb}{0.37,0.62,0.63}");
        fprintf(output, "%s\n", "\\definecolor{Amaranth}{rgb}{0.9,0.17,0.31}");
        fprintf(output, "%s\n", "\\definecolor{RedGayran}{rgb}{0.5,0,0.12}");
        fprintf(output, "%s\n", "\\definecolor{Cool}{rgb}{0.0, 0.18, 0.39}");
        fprintf(output, "%s", "{\\fontsize{15}{10}\\selectfont Solution ");
        fprintf(output, "%d ", sol_count);
        fprintf(output, "%s\n", "\\newline \\newline}");
        fprintf(output, "%s\n", "\\color{white}");
        fprintf(output, "%s\n", "\\frametitle{Multiple Solution}");
        fprintf(output, "%s\n", "\\newline ");
        fprintf(output, "%s\n", "\\begin{center}");
        if (sol_count > 1){
            fprintf(output, "%s\n", "{\\fontsize{12}{10}\\selectfont \\hspace{1.8cm} ");
            fprintf(output, "%s\n", "\\textcolor{gray}{$\\alpha$} =  \\textcolor{Cool}{");
            fprintf(output, "%.2f } } \\newline \\newline \n", alpha);
        }
        fprintf(output, "%s\n", "{\\fontsize{12}{10}\\selectfont \\centering The results of simplex are: \n");
        if (isMax){
            fprintf(output, "\\hspace{1.5cm} \\textcolor{orange}{MAX(Z)} = \\textcolor{gray}{%.2f\n}",
             solutions[0][sol_count].value);  
        }else{
            fprintf(output, "\\hspace{1.5cm} \\textcolor{orange}{MIN(Z)} = \\textcolor{gray}{%.2f\n}", 
            solutions[0][sol_count].value);  
        }
        fprintf(output, "%s\n", "} \\newline \\newline");
        fprintf(output, "%s\n", "{\\fontsize{12}{10}\\selectfont Variables: \n");
        for(int i = 1; i < cols; i++)
        {
            if (solutions[i][sol_count].type == VARIABLE){
                fprintf(output, "\\textcolor{gray}{%s} = \\textcolor{RedGayran}{%.2f\n}", 
                solutions[i][sol_count].original_name, solutions[i][sol_count].value);
            }else if (solutions[i][sol_count].type == SLACK){
                fprintf(output, "\\textcolor{gray}{%s} = \\textcolor{CadetBlue}{%.2f\n}", 
                solutions[i][sol_count].original_name, solutions[i][sol_count].value);
            }else if (solutions[i][sol_count].type == EXCESS){
                fprintf(output, "\\textcolor{gray}{%s} = \\textcolor{Cool}{%.2f\n}", 
                solutions[i][sol_count].original_name, solutions[i][sol_count].value);
            }
        }
        fprintf(output, "%s\n", "}");
        fprintf(output, "%s\n", "\\end{center}");
        fprintf(output, "%s\n", "\\end{frame}");

        if (sol_count > 1){
            alpha += 0.25;
        }
    }
}

void solution_latex(FILE *output, struct variable variables[cols], int isMax)
{
    fprintf(output, "%s\n", "\\begin{frame}");
    fprintf(output, "%s\n", "\\color{yellow}");
    fprintf(output, "%s\n", "\\definecolor{CadetBlue}{rgb}{0.37,0.62,0.63}");
    fprintf(output, "%s\n", "\\definecolor{Amaranth}{rgb}{0.9,0.17,0.31}");
    fprintf(output, "%s\n", "\\definecolor{RedGayran}{rgb}{0.5,0,0.12}");
    fprintf(output, "%s\n", "\\definecolor{Cool}{rgb}{0.0, 0.18, 0.39}");
    fprintf(output, "%s\n", "{\\fontsize{15}{10}\\selectfont Solution \\newline \\newline}");
    fprintf(output, "%s\n", "\\color{white}");
    fprintf(output, "%s\n", "\\frametitle{Solution}");
    fprintf(output, "%s\n", "\\newline ");
    fprintf(output, "%s\n", "\\begin{center}");
    fprintf(output, "%s\n", "{\\fontsize{12}{10}\\selectfont \\centering The results of simplex are: \n");
    if (isMax){
        fprintf(output, "\\hspace{1.5cm} \\textcolor{orange}{MAX(Z)} = \\textcolor{gray}{%.2f\n}", variables[0].value);  
    }else{
        fprintf(output, "\\hspace{1.5cm} \\textcolor{orange}{MIN(Z)} = \\textcolor{gray}{%.2f\n}", variables[0].value);  
    }
    fprintf(output, "%s\n", "} \\newline \\newline");
    fprintf(output, "%s\n", "{\\fontsize{12}{10}\\selectfont Variables: \n");
    for(int i = 1; i < cols; i++)
    {
        if (variables[i].type == VARIABLE){
            fprintf(output, "\\textcolor{gray}{%s} = \\textcolor{RedGayran}{%.2f\n}", 
            variables[i].original_name, variables[i].value);
        }else if (variables[i].type == SLACK){
            fprintf(output, "\\textcolor{gray}{%s} = \\textcolor{CadetBlue}{%.2f\n}", 
            variables[i].original_name, variables[i].value);
        }else if (variables[i].type == EXCESS){
            fprintf(output, "\\textcolor{gray}{%s} = \\textcolor{Cool}{%.2f\n}", 
            variables[i].original_name, variables[i].value);
        }
    }
    fprintf(output, "%s\n", "}");
    fprintf(output, "%s\n", "\\end{center}");
    fprintf(output, "%s\n", "\\end{frame}");
}

//#############################################################
// End document
//##########################################################
void end_document(FILE *output)
{
	fprintf(output, "%s\n", "\\end{document}");
}

//#############################################################
// Execute the latex file.
//##########################################################
void execute_latex()
{
	system("pdflatex beamer.tex && evince -s beamer.pdf &");
}

//#############################################################
// close all files.
//#############################################################
void close_Files(FILE *file1, FILE *file2, FILE *file3){
	fclose(file1);
	fclose(file2);
	fclose(file3);
}

//#############################################################
// Delete the files.
//#############################################################
void delete_Files(){
	remove(tableFileName);
	remove(variableFileName);
}

//#############################################################
// Save in the target file the content of source
//#######################################################
void saveLatex(FILE *target, FILE *source, char *name){
    char c;
    fclose(source);
    source = fopen(name, "r");
    fseek(source, 0, SEEK_SET);
    while((c=fgetc(source)) != EOF){
        fprintf(target, "%c", c); // Write caracter.
    }
}

// ############################################################
// Create "file.tex" , save the tables, draw the variables, drop the files and execute.
// ############################################################
void generate_latex(FILE *output, FILE *tables, FILE *variables){
	create_latex(output);                       // Declarations of latex
	cover(output);                              // Generate the cover.
	definitions(output);						// We define the concept of Simplex and its steps
    saveLatex(output, variables, variableFileName);
	saveLatex(output, tables, tableFileName); 	// Copie el contenido de las tabla principal e intermedia.
	// Solution
	end_document(output);						// End the document
	close_Files(output, tables, variables);		// Close all the files
	delete_Files();								// delete the files.
	//execute_latex();							// Execute latex.
}
