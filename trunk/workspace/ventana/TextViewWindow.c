#include <gtk/gtk.h>

void
on_window_destroy2 (GtkWidget *widget, gpointer data)
{
  gtk_main_quit ();
}

/* Callback for close button */
void
on_button_clicked2 (GtkWidget *button, GtkTextBuffer *buffer)
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

int
main22(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *vbox;
  GtkWidget *text_view;
  GtkWidget *button;
  GtkTextBuffer *buffer;
  GtkWidget *scrolled_window;

  gtk_init (&argc, &argv);

  /* Create a Window. */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Simple Multiline Text Input");

  /* Set a decent default size for the window. */
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  g_signal_connect (G_OBJECT (window), "destroy",
                    G_CALLBACK (on_window_destroy2),
                    NULL);

  vbox = gtk_vbox_new (FALSE, 2);
  gtk_container_add (GTK_CONTAINER (window), vbox);

  /* Create a multiline text widget. */
  text_view = gtk_text_view_new ();
  gtk_box_pack_start (GTK_BOX (vbox), text_view, 1, 1, 0);

  /* scroll */
 /* scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
  	GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
  gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);
*/
  /* end scroll */

  /* Obtaining the buffer associated with the widget. */
  buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));
  /* Set the default buffer text. */
  gtk_text_buffer_set_text (buffer, "Hello Text View!", -1);

  /* Create a close button. */
  button = gtk_button_new_with_label ("Close");
  gtk_box_pack_start (GTK_BOX (vbox), button, 0, 0, 0);
  g_signal_connect (G_OBJECT (button), "clicked",
                    G_CALLBACK (on_button_clicked2),
                    buffer);

  gtk_widget_show_all (window);

  gtk_main ();
  return 0;
}
