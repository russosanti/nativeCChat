/*
 * paneles.c
 *
 *  Created on: May 29, 2011
 *      Author: santiago
 */


#include <stdio.h>
#include <stdlib.h>
#include "gtk/gtk.h"

/* structure to hold references to our widgets */
typedef struct
{
        GtkWidget *view;
        GtkWidget *resp;
} MyWidgets;

static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    gtk_main_quit ();
    return FALSE;
}



/* Callback for send button */
void
al_apretar_boton (GtkWidget *button, gpointer user_data)
{
	MyWidgets               *widgets;
	GtkTextBuffer           *buffer;
	GtkTextBuffer           *buffer_resp;
    widgets = (MyWidgets *)user_data;

  GtkTextIter start;
  GtkTextIter end;

  gchar *text;

  buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (widgets->view));

  /* Obtain iters for the start and end of points of the buffer */
  gtk_text_buffer_get_start_iter (buffer, &start);
  gtk_text_buffer_get_end_iter (buffer, &end);

  /* Get the entire buffer text. */
  text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);

  /* Print the text */
//  g_print ("%s \n", text);

  buffer_resp = gtk_text_view_get_buffer (GTK_TEXT_VIEW (widgets->resp));
  gtk_text_buffer_insert_at_cursor (buffer_resp, "Server: ", -1);
  gtk_text_buffer_insert_at_cursor(buffer_resp, text, -1);   // Agrega el texto tipeado a la pantalla
  gtk_text_buffer_insert_at_cursor(buffer_resp, "\n", -1);   // pasa nueva linea

  /* limpia el bufer de texto ingresado para comenzar a ingresar un nuevo mensaje.   */
  gtk_text_buffer_set_text (buffer, "", -1);

  g_free (text);
}

int main(int   argc,
        char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box1;
    GtkWidget *separator;
    GtkWidget *label;
    GtkWidget *quitbox;
    GtkWidget *scrolled_window;
    GtkTextBuffer *buffer;
    GtkWidget *envio;
    GtkTextBuffer *buffer_resp;
    MyWidgets *widgets;

    // similar al malloc pero para widgets con estructura
    widgets = g_slice_new (MyWidgets);

    /* Our init, don't forget this! :) */
    gtk_init (&argc, &argv);

    /* Create our window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /* You should always remember to connect the delete_event signal
     * to the main window. This is very important for proper intuitive
     * behavior */
    g_signal_connect (window, "delete-event",
		      G_CALLBACK (delete_event), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (GTK_WIDGET (window), 350, 230);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    /* We create a vertical box (vbox) to pack the horizontal boxes into.
     * This allows us to stack the horizontal boxes filled with buttons one
     * on top of the other in this vbox. */
    box1 = gtk_vbox_new (FALSE, 0);

	/* create a new label. */
	label = gtk_label_new ("Mensajería Instantánea");

	/* Align the label to the left side.  We'll discuss this function and
	 * others in the section on Widget Attributes. */
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0);

	/* Pack the label into the vertical box (vbox box1).  Remember that
	 * widgets added to a vbox will be packed one on top of the other in
	 * order. */
	gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 0);

	/* Show the label */
	gtk_widget_show (label);

	// Crea la ventana con las respuestas
	widgets->resp = gtk_text_view_new ();
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (widgets->resp), GTK_WRAP_WORD_CHAR);
	buffer_resp = gtk_text_view_get_buffer (GTK_TEXT_VIEW (widgets->resp));

	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
			   	           GTK_POLICY_AUTOMATIC,
					   GTK_POLICY_AUTOMATIC);

	gtk_container_add (GTK_CONTAINER (scrolled_window), widgets->resp);
	gtk_text_buffer_set_text (buffer_resp, "", -1);
	gtk_text_view_set_editable(GTK_TEXT_VIEW (widgets->resp), FALSE);
	gtk_box_pack_start (GTK_BOX (box1), scrolled_window, FALSE, FALSE, 0);
	gtk_widget_show (widgets->resp);
	gtk_widget_show (scrolled_window);

	/* Another new separator. */
	separator = gtk_hseparator_new ();
	/* The last 3 arguments to gtk_box_pack_start are:
	 * expand, fill, padding. */
	gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 5);
	gtk_widget_show (separator);


	// Crea la vista de la ventana para ingresar los datos
	widgets->view = gtk_text_view_new ();
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (widgets->view), GTK_WRAP_WORD_CHAR);
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (widgets->view));

	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
			   	           GTK_POLICY_AUTOMATIC,
					   GTK_POLICY_AUTOMATIC);

	gtk_container_add (GTK_CONTAINER (scrolled_window), widgets->view);
	gtk_text_buffer_set_text (buffer, "Texto inicial ", -1);
	   //insert_text (buffer);   // traia el texto de un archivo
	gtk_box_pack_start (GTK_BOX (box1), scrolled_window, FALSE, FALSE, 0);
	gtk_widget_show (widgets->view);
	gtk_widget_show (scrolled_window);


	/* Another new separator. */
	separator = gtk_hseparator_new ();
	/* The last 3 arguments to gtk_box_pack_start are:
	 * expand, fill, padding. */
	gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 5);
	gtk_widget_show (separator);


    /* Create another new hbox.. remember we can use as many as we need! */
    quitbox = gtk_hbox_new (FALSE, 0);

    /* Create a Send button. */
    envio = gtk_button_new_with_label ("Enviar");
    gtk_box_pack_start (GTK_BOX (quitbox), envio, TRUE, FALSE, 0);
    g_signal_connect (G_OBJECT (envio), "clicked",
                      G_CALLBACK (al_apretar_boton),
                      widgets);

    /* Our quit button. */
    button = gtk_button_new_with_label ("Salir");

    /* Setup the signal to terminate the program when the button is clicked */
    g_signal_connect_swapped (button, "clicked",
			      G_CALLBACK (gtk_main_quit),
			      window);
    /* Pack the button into the quitbox.
     * The last 3 arguments to gtk_box_pack_start are:
     * expand, fill, padding. */
    gtk_box_pack_start (GTK_BOX (quitbox), button, TRUE, FALSE, 0);
    /* pack the quitbox into the vbox (box1) */
    gtk_box_pack_start (GTK_BOX (box1), quitbox, FALSE, FALSE, 0);

    /* Pack the vbox (box1) which now contains all our widgets, into the
     * main window. */
    gtk_container_add (GTK_CONTAINER (window), box1);

    /* And show everything left */
    gtk_widget_show (envio);
    gtk_widget_show (button);
    gtk_widget_show (quitbox);

    gtk_widget_show (box1);
    /* Showing the window last so everything pops up at once. */
    gtk_widget_show (window);

    /* And of course, our main function. */
    gtk_main ();

    /* Control returns here when gtk_main_quit() is called, but not when
     * exit() is used. */

    return 0;
}
