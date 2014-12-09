#include <stdio.h>
#include <gtk/gtk.h>

void
on_window_destroy (GtkWidget *widget, gpointer data)
{
  gtk_main_quit ();
}

/* Callback for close button */
void
on_button_clicked (GtkWidget *button, GtkTextBuffer *buffer)
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
  g_print ("%s", text);

  g_free (text);

  gtk_main_quit ();
}

// inserta texto en el panel de abajo
/* Create a scrolled text area that displays a "message" */
static GtkWidget *create_text( void )
{
   GtkWidget *scrolled_window;
   GtkWidget *view;
   GtkTextBuffer *buffer;
   GtkWidget *vbox;
   GtkWidget *button;

   /* Create a new hbox with the appropriate homogeneous
    * and spacing settings */
   vbox = gtk_vbox_new (FALSE, 0);

   view = gtk_text_view_new ();
   buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

   scrolled_window = gtk_scrolled_window_new (NULL, NULL);
   gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
		   	           GTK_POLICY_AUTOMATIC,
				   GTK_POLICY_AUTOMATIC);

   gtk_container_add (GTK_CONTAINER (scrolled_window), view);
   //insert_text (buffer);
   gtk_box_pack_start (GTK_BOX (vbox), view, 0, 0, 0);

   /* agregado*/
    /* Set the default buffer text. */
   gtk_text_buffer_set_text (buffer, "Hello Text View!", -1);

   /* Create a close button. */
   button = gtk_button_new_with_label ("Close");
   gtk_box_pack_start (GTK_BOX (vbox), button, 0, 0, 0);
   g_signal_connect (G_OBJECT (button), "clicked",
                     G_CALLBACK (on_button_clicked),
                     buffer);
   /* desagreado */

   gtk_widget_show_all (scrolled_window);

   return scrolled_window;
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

int
mainold(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *vpaned;
    GtkWidget *list;
    GtkWidget *text;
//    GtkWidget *vbox;
//    GtkWidget *button;
//    GtkTextBuffer *buffer;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Paned Windows");
    g_signal_connect (window, "destroy",
	              G_CALLBACK (gtk_main_quit), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 50);
    gtk_widget_set_size_request (GTK_WIDGET (window), 450, 400);

//    /* Create a new hbox with the appropriate homogeneous
//     * and spacing settings */
//    vbox = gtk_vbox_new (FALSE, 0);

    /* create a vpaned widget and add it to our toplevel window */

    vpaned = gtk_vpaned_new ();
    gtk_container_add (GTK_CONTAINER (window), vpaned);
    gtk_widget_show (vpaned);

    /* Now create the contents of the two halves of the window */

    list = create_list ();
    gtk_paned_add1 (GTK_PANED (vpaned), list);
    gtk_widget_show (list);

    text = create_text ();
    gtk_paned_add2 (GTK_PANED (vpaned), text);
    gtk_widget_show (text);

    /* Create a close button. */
//    button = gtk_button_new_with_label ("Close");
//    gtk_box_pack_start (GTK_BOX (vbox), button, 0, 0, 0);
//    g_signal_connect (G_OBJECT (button), "clicked",
//                      G_CALLBACK (on_button_clicked),
//                      buffer);

    gtk_widget_show_all (window);

    gtk_main ();

    return 0;
}

