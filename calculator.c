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


static void activate(GtkApplication *app, gpointer user_data){
	calc widget; // Declare a variable "widget" of type "calc"

	widget.window = gtk_application_window_new(app); // Create a new main window
	gtk_window_set_position(GTK_WINDOW(widget.window),GTK_WIN_POS_CENTER); // Set the position of the window 
	gtk_window_set_title(GTK_WINDOW(widget.window),"Calculator"); // Set the title of the window 
	gtk_window_set_default_size(GTK_WINDOW(widget.window), 200, 200); // Set the default size of the window
	gtk_container_set_border_width(GTK_CONTAINER(widget.window),10); // Set the border width of the window

    gtk_widget_show_all(widget.window);
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