/* We save all the structures in this file*/
#define latexFileName "beamer.tex"
#define tableFileName "table.txt"
#define variableFileName "variables.txt"
FILE *latex_file;
FILE *table_file;
FILE *variables_file;

enum TYPE{Z, RESULT, VARIABLE, SLACK, EXCESS, VIRTUAL};
enum SOLUTION {BOUNDED = -2, RESOLVED = -1, NO_FACTIBLE = 0, FACTIBLE = 1};

struct variable{
	char original_name[20];
	int id;
	double value;
	enum TYPE type;
};

int rows;
int cols;
int step_counter = 0;
int optimal_solution;
int show_intermediate_tables;
int normal_variables = 0;
int virtual_variables = 0;
int excess_variables = 0; 
int slack_variables = 0;

// GUI Variables
GtkBuilder *builder;
GtkWidget  *window;
GtkWidget  *BtnCalcular;
GtkWidget  *check_button;

// Save data variables
char *problem_name;
char *variables[9];
double restrictions[10][10];
double objFunction[8];
int extra_pages = 0;
int problemType;