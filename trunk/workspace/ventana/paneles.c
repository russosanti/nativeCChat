/*
 * paneles.c
 *
 *  Created on: May 29, 2011
 *      Author: claudio
 */

/* example-start packbox packbox.c */

#include <stdio.h>
#include <stdlib.h>
#include "gtk/gtk.h"

static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    gtk_main_quit ();
    return FALSE;
}

/* Make a new hbox filled with button-labels. Arguments for the
 * variables we're interested are passed in to this function.
 * We do not show the box, but do show everything inside. */
static GtkWidget *make_box( gboolean homogeneous,
                            gint     spacing,
                            gboolean expand,
                            gboolean fill,
                            guint    padding )
{
    GtkWidget *box;
    GtkWidget *button;
    char padstr[80];

    /* Create a new hbox with the appropriate homogeneous
     * and spacing settings */
    box = gtk_hbox_new (homogeneous, spacing);

    /* Create a series of buttons with the appropriate settings */
    button = gtk_button_new_with_label ("gtk_box_pack");
    gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
    gtk_widget_show (button);

    button = gtk_button_new_with_label ("(box,");
    gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
    gtk_widget_show (button);

    button = gtk_button_new_with_label ("button,");
    gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
    gtk_widget_show (button);

    /* Create a button with the label depending on the value of
     * expand. */
    if (expand == TRUE)
	    button = gtk_button_new_with_label ("TRUE,");
    else
	    button = gtk_button_new_with_label ("FALSE,");

    gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
    gtk_widget_show (button);

    /* This is the same as the button creation for "expand"
     * above, but uses the shorthand form. */
    button = gtk_button_new_with_label (fill ? "TRUE," : "FALSE,");
    gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
    gtk_widget_show (button);

    sprintf (padstr, "%d);", padding);

    button = gtk_button_new_with_label (padstr);
    gtk_box_pack_start (GTK_BOX (box), button, expand, fill, padding);
    gtk_widget_show (button);

    return box;
}


/* Create the list of "messages" */
static GtkWidget *create_list( void )
{

    GtkWidget *scrolled_window;
    GtkWidget *tree_view;
    GtkListStore *model;
    GtkTreeIter iter;
    GtkCellRenderer *cell;
    GtkTreeViewColumn *column;

    int i;

    /* Create a new scrolled window, with scrollbars only if needed */
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
				    GTK_POLICY_AUTOMATIC,
				    GTK_POLICY_AUTOMATIC);

    model = gtk_list_store_new (1, G_TYPE_STRING);
    tree_view = gtk_tree_view_new ();
    gtk_container_add (GTK_CONTAINER (scrolled_window), tree_view);
    gtk_tree_view_set_model (GTK_TREE_VIEW (tree_view), GTK_TREE_MODEL (model));
    gtk_widget_show (tree_view);

    /* Add some messages to the window */
    for (i = 0; i < 10; i++) {
        gchar *msg = g_strdup_printf ("Message #%d", i);
        gtk_list_store_append (GTK_LIST_STORE (model), &iter);
        gtk_list_store_set (GTK_LIST_STORE (model),
	                    &iter,
                            0, msg,
	                    -1);
	g_free (msg);
    }

    cell = gtk_cell_renderer_text_new ();

    column = gtk_tree_view_column_new_with_attributes ("Messages",
                                                       cell,
                                                       "text", 0,
                                                       NULL);

    gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view),
	  		         GTK_TREE_VIEW_COLUMN (column));

    return scrolled_window;
}



/* Callback for send button */
void
al_apretar_boton_old (GtkWidget *button, GtkTextBuffer *buffer)
{
  GtkTextIter start;
  GtkTextIter end;

  gchar *text;

  /* Obtain iters for the start and end of points of the buffer */
  gtk_text_buffer_get_start_iter (buffer, &start);
  gtk_text_buffer_get_end_iter (buffer, &end);

  /* Get the entire buffer text. */
  text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);

  /* Print the text */
  g_print ("%s \n", text);

  g_free (text);

//  gtk_text_buffer_set_text (buffer_resp, "Server: ", -1);
  /* limpia el bufer de texto ingresado para comenzar a ingresar un nuevo mensaje.   */
  gtk_text_buffer_set_text (buffer, "", -1);

}

int mainpaneles( int   argc,
          char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box1;
    GtkWidget *separator;
    GtkWidget *label;
    GtkWidget *quitbox;
    GtkWidget *scrolled_window;
    GtkWidget *view;
    GtkTextBuffer *buffer;
    GtkWidget *list;
    GtkWidget *envio;
    GtkWidget *resp;
    GtkTextBuffer *buffer_resp;

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
    gtk_widget_set_size_request (GTK_WIDGET (window), 450, 250);

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

//	/* Call our make box function - homogeneous = FALSE, spacing = 0,
//	 * expand = FALSE, fill = FALSE, padding = 0 */
//	box2 = make_box (FALSE, 0, FALSE, FALSE, 0);
//	gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
//	gtk_widget_show (box2);

	// Crea la ventana con la lista de mensajes
//    list = create_list ();
	// Crea la ventana con las respuestas
    resp = gtk_text_view_new ();
	buffer_resp = gtk_text_view_get_buffer (GTK_TEXT_VIEW (resp));

	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
			   	           GTK_POLICY_AUTOMATIC,
					   GTK_POLICY_AUTOMATIC);

	gtk_container_add (GTK_CONTAINER (scrolled_window), resp);
	gtk_text_buffer_set_text (buffer_resp, "", -1);
	gtk_box_pack_start (GTK_BOX (box1), scrolled_window, FALSE, FALSE, 0);
	gtk_widget_show (resp);
	gtk_widget_show (scrolled_window);

	/* Another new separator. */
	separator = gtk_hseparator_new ();
	/* The last 3 arguments to gtk_box_pack_start are:
	 * expand, fill, padding. */
	gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 5);
	gtk_widget_show (separator);


	// Crea la vista de la ventana para ingresar los datos
	view = gtk_text_view_new ();
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
			   	           GTK_POLICY_AUTOMATIC,
					   GTK_POLICY_AUTOMATIC);

	gtk_container_add (GTK_CONTAINER (scrolled_window), view);
	gtk_text_buffer_set_text (buffer, "Texto inicial ", -1);
	   //insert_text (buffer);   // traia el texto de un archivo
	gtk_box_pack_start (GTK_BOX (box1), scrolled_window, FALSE, FALSE, 0);
	gtk_widget_show (view);
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
                      G_CALLBACK (al_apretar_boton_old),
                      buffer);

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
