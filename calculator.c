#include<gtk/gtk.h>

#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


// Define a custom data structure named "calc" to hold GTK widgets
typedef struct{
	GtkWidget *window; // Declare a pointer to a GtkWidget object for the main window
	GtkWidget *grid; // Declare a pointer to a GtkWidget object for a grid layout
	GtkWidget *button[17]; // Declare an array of pointers to GtkWidget objects for buttons
}calc;

GtkWidget *box; // Declare a pointer to a GtkWidget object for a box container

#define SIZE 10

char input_buffer[100] = {0}; // Initialize an input buffer to store user input
char output_buffer[100] = {0}; // Initialize an output buffer to display results

bool clear_buffer = false; // Flag to indicate whether the input buffer should be cleared
bool add=false; // Flag to indicate addition operation
bool mul = false; // Flag to indicate multiplication operation
bool divv = false; // Flag to indicate division operation
bool sub = false; // Flag to indicate subtraction operation

double result = 0.0; // Variable to store the result of the calculation
static float num[SIZE]; // Static array to store numbers entered by the user
int count = 0; // Variable to keep track of the number of elements in the "num" array


// Callback function for button click events to perform calculations
static void calculate(GtkButton *button, gpointer data){

	const gchar* text = gtk_button_get_label(button); // Get the label of the clicked button

	if( (strcmp("+", text)==0) ||   (strcmp("-", text)==0) ||  (strcmp("/", text)==0) ||  (strcmp("x", text)==0) ||  (strcmp("=", text)==0) ){
		num[count] = atof(input_buffer); // Convert the input buffer to a number and store it in the "num" array
		count++; // Increment the count of elements in the "num" array
		clear_buffer = true; // Set the flag to clear the input buffer

        // Set the appropriate operation flag based on the clicked operator button
		if(strcmp("+",text)==0){
			add = true;
		}
		if(strcmp("-",text)==0){
			sub = true;
		}
		if(strcmp("/",text)==0){
			divv = true;
		}
		if(strcmp("x",text)==0){
			mul = true;
		}
	}

	if(strcmp("=",text)==0){
		int x = sizeof(num)/sizeof(num[0]);
		
        // Perform the appropriate calculation based on the operation flags
		if(add){
			for(int i=0; i<x; i++){
				result += num[i];
			}
		}

		if(divv){
			result = num[0]/num[1];
		}

		if(sub){
				if(result == 0.0){
					result = num[0]*2;
				}
			for(int i=0; i<x; i++){
				result -= num[i];
			}
		}
	
		if(mul){
			result = num[0]*num[1];
		}

        // Reset all the operation flags
		add = false;
		mul = false;
		divv = false;
		sub = false;
		
		gtk_entry_set_text(GTK_ENTRY(box), ""); // Clear the entry box
		sprintf(output_buffer, "%.3f", result); // Format the result and store it in the output buffer
		gtk_entry_set_text(GTK_ENTRY(box), output_buffer); // Set the output buffer as the text of the entry box
		result = 0.0; // Reset the result variable
	}
	else{
		if(clear_buffer){
			memset(input_buffer,0,strlen(input_buffer)); // Clear the input buffer
			clear_buffer = false; // Reset the clear buffer flag
		}
        else{
			strncat(input_buffer,text, 1); // Append the clicked button label to the input buffer
		}
		
			strncat(output_buffer,text, 1); // Append the clicked button label to the output buffer
			gtk_entry_set_text(GTK_ENTRY(box), output_buffer); // Set the output buffer as the text of the entry box
	}
		
    // Check if the clicked button is the "C" button (clear button)
	if(strcmp("C",text)==0){
		gtk_entry_set_text(GTK_ENTRY(box), ""); // Clear the entry box
		memset(input_buffer,0,strlen(input_buffer)); // Clear the input buffer
		memset(output_buffer,0,strlen(output_buffer)); // Clear the output buffer

		count = 0; // Reset the count of elements in the "num" array
		int x = sizeof(num)/sizeof(num[0]);
		
		for(int i=0; i<x; i++){
				num[i] = 0;
		}

        // Reset all the operation flags
		add = false;
		mul = false;
		divv = false;
		sub = false;
	}
}


// Callback function for the "activate" signal of the GtkApplication
static void activate(GtkApplication *app, gpointer user_data){
	calc widget; // Declare a variable "widget" of type "calc"

	widget.window = gtk_application_window_new(app); // Create a new main window
	gtk_window_set_position(GTK_WINDOW(widget.window),GTK_WIN_POS_CENTER); // Set the position of the window 
	gtk_window_set_title(GTK_WINDOW(widget.window),"Calculator"); // Set the title of the window 
	gtk_window_set_default_size(GTK_WINDOW(widget.window), 200, 200); // Set the default size of the window
	gtk_container_set_border_width(GTK_CONTAINER(widget.window),10); // Set the border width of the window

    // Create a new grid layout and add it to the main window
    widget.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(widget.window),widget.grid);

    // Create an entry box and make it non-editable
	box = gtk_entry_new();
	gtk_editable_set_editable(GTK_EDITABLE(box), FALSE);

    // Create buttons with labels for digits and operators
	widget.button[0] = gtk_button_new_with_label("0");
	widget.button[1] = gtk_button_new_with_label("1");
	widget.button[2] = gtk_button_new_with_label("2");
	widget.button[3] = gtk_button_new_with_label("3");
	widget.button[4] = gtk_button_new_with_label("4");
	widget.button[5] = gtk_button_new_with_label("5");
	widget.button[6] = gtk_button_new_with_label("6");
	widget.button[7] = gtk_button_new_with_label("7");
	widget.button[8] = gtk_button_new_with_label("8");
	widget.button[9] = gtk_button_new_with_label("9");
	widget.button[10] = gtk_button_new_with_label(".");
	widget.button[11] = gtk_button_new_with_label("+");
	widget.button[12] = gtk_button_new_with_label("-");
	widget.button[13] = gtk_button_new_with_label("x");
	widget.button[14] = gtk_button_new_with_label("/");
	widget.button[15] = gtk_button_new_with_label("C");
	widget.button[16] = gtk_button_new_with_label("=");


    // Attach widgets to the grid layout with appropriate positions and spans
	gtk_grid_attach(GTK_GRID(widget.grid),box,0,0,4,1);
	
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[15],0,1,3,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[14],3,1,1,1);
	
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[7],0,2,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[8],1,2,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[9],2,2,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[13],3,2,1,1);


	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[4],0,3,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[5],1,3,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[6],2,3,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[12],3,3,1,1);


	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[1],0,4,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[2],1,4,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[3],2,4,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[11],3,4,1,1);


	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[0],0,5,2,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[10],2,5,1,1);
    gtk_grid_attach(GTK_GRID(widget.grid),widget.button[16],3,5,1,1);

    g_signal_connect(widget.button[0],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[1],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[2],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[3],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[4],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[5],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[6],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[7],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[8],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[9],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[10],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[11],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[12],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[13],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[14],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[15],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[16],"clicked",G_CALLBACK(calculate), NULL);

    gtk_widget_show_all(widget.window); // Show all the widgets inside the main window
}


int main(int argc, char **argv){
	GtkApplication *app; // Declare a pointer to a GtkApplication object

	gtk_init(&argc, &argv); // Initialize GTK with command-line arguments

	int status;
    // Create a new GtkApplication, where:
    // "org.gtk.gui_calculator": This is the application ID, which serves as a unique identifier for this particular application. 
    // Application IDs are commonly used to identify the program within its environment. In this case, "org.gtk.calculator" suggests 
    // that the application is related to the GTK (GIMP Toolkit) and could be a calculator or have something to do with calculator development.
    // G_APPLICATION_FLAGS_NONE: This parameter specifies the flags or options to be used when creating the GtkApplication object. In this context, 
    // using G_APPLICATION_FLAGS_NONE means that no additional flags or options are provided during the creation of the GtkApplication object. 
    // The program will be created with default values, as no specific flags have been set. This implies that the application will work with the 
    // standard default settings for GtkApplication
	app = gtk_application_new("org.gtk.gui_calculator", G_APPLICATION_FLAGS_NONE); 

    // Connect the "activate" signal of the application to the activate callback function
	g_signal_connect(app,"activate", G_CALLBACK(activate), NULL);

	status = g_application_run(G_APPLICATION(app), argc, argv); // Run the application

	g_object_unref(app); // Free the memory used by the GtkApplication object

return status;
}