#include <gtk/gtk.h>

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "tinyexpr.h"

typedef struct{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *button[20];
	
}calc;

GtkWidget *box;

#define g_expression_size 64
char g_expression[g_expression_size] = {0};
int g_pos = 0;

static void calculate (GtkButton *button, gpointer data){
		const gchar *input = gtk_button_get_label(button);
		char tecla = *input;
		
		if ((tecla != '=') && (tecla != '<') && (tecla != 'C')){
			g_expression[g_pos] = tecla;
			g_pos++;				
			gtk_entry_set_text(GTK_ENTRY(box), g_expression);
			
		}else if (tecla == '<'){
			memset(&g_expression[g_pos], 0, 1);
			g_pos--;		
			gtk_entry_set_text(GTK_ENTRY(box), g_expression);
			
		}else if (tecla == 'C'){
			memset(g_expression, 0, sizeof(g_expression));
			g_pos = 0;	
			gtk_entry_set_text(GTK_ENTRY(box), g_expression);
			
		}else{
			const char *expression = g_expression;
			double resp = te_interp(expression, 0);
			
			gchar *g_resp = g_strdup_printf("%g", resp);	
			gtk_entry_set_text(GTK_ENTRY(box), g_resp);
			g_free(g_resp);
			
		}
	}
	
static void ativar(GtkApplication *app, gpointer user_data){
	calc widget;
	
	widget.window = gtk_application_window_new(app);
	gtk_window_set_position(GTK_WINDOW(widget.window), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(widget.window), "Calculadorazinha GTK");
	gtk_window_set_default_size(GTK_WINDOW(widget.window),200,200);
	gtk_container_set_border_width(GTK_CONTAINER(widget.window),10);

	widget.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(widget.window), widget.grid);

	box = gtk_entry_new();
	gtk_editable_set_editable(GTK_EDITABLE(box), FALSE);

	widget.button[0]  = gtk_button_new_with_label("0");
	widget.button[1]  = gtk_button_new_with_label("1");
	widget.button[2]  = gtk_button_new_with_label("2");
	widget.button[3]  = gtk_button_new_with_label("3");
	widget.button[4]  = gtk_button_new_with_label("4");
	widget.button[5]  = gtk_button_new_with_label("5");
	widget.button[6]  = gtk_button_new_with_label("6");
	widget.button[7]  = gtk_button_new_with_label("7");
	widget.button[8]  = gtk_button_new_with_label("8");
	widget.button[9]  = gtk_button_new_with_label("9");
	widget.button[10] = gtk_button_new_with_label(",");
	widget.button[11] = gtk_button_new_with_label("+");
	widget.button[12] = gtk_button_new_with_label("-");
	widget.button[13] = gtk_button_new_with_label("*");
	widget.button[14] = gtk_button_new_with_label("/");
	widget.button[15] = gtk_button_new_with_label("=");
	widget.button[16] = gtk_button_new_with_label("(");
	widget.button[17] = gtk_button_new_with_label(")");
	widget.button[18] = gtk_button_new_with_label("<");
	widget.button[19] = gtk_button_new_with_label("C");

	gtk_grid_attach(GTK_GRID(widget.grid),box,0,0,4,1);

	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[7] ,0,1,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[8] ,1,1,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[9] ,2,1,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[14],3,1,1,1);

	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[6] ,0,2,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[5] ,1,2,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[4] ,2,2,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[13],3,2,1,1);

	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[3] ,0,3,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[2] ,1,3,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[1] ,2,3,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[12],3,3,1,1);

	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[10],0,4,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[0] ,1,4,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[15],2,4,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[11],3,4,1,1);
	
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[16],0,5,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[17],1,5,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[18],2,5,1,1);
	gtk_grid_attach(GTK_GRID(widget.grid),widget.button[19],3,5,1,1);

	g_signal_connect(widget.button[0] ,"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[1] ,"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[2] ,"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[3] ,"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[4] ,"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[5] ,"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[6] ,"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[7] ,"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[8] ,"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[9] ,"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[10],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[11],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[12],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[13],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[14],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[15],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[16],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[17],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[18],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.button[19],"clicked",G_CALLBACK(calculate), NULL);

	gtk_widget_show_all(widget.window);
}

int main(int argc, char **argv){
	int status;
	GtkApplication *app;
	app = gtk_application_new("io.github.alix.calculadora", G_APPLICATION_DEFAULT_FLAGS);

	g_signal_connect(app, "activate", G_CALLBACK(ativar), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	
	return status;
}
