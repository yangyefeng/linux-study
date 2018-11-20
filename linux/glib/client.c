



#include <glib.h>
#include <gio/gio.h>

GSocketConnection * connection = NULL;
send()
{
 /* initialize glib */
 

  GError * error = NULL;

  /* create a new connection */
  

  
  /* use the connection */

 //GInputStream * istream = g_io_stream_get_input_stream (G_IO_STREAM (connection));
  GOutputStream * ostream = g_io_stream_get_output_stream (G_IO_STREAM (connection));	
 
  g_output_stream_write  (ostream,
                          "Hello server!\r\n", /* your message goes here */
                          13, /* length of your message */
                          NULL,
                          &error);
if (error != NULL)
  {
      g_error (error->message);
  }
}

int
main (int argc, char *argv[])
{
   g_type_init ();
 GError * error = NULL;
    GSocketClient * client = g_socket_client_new();

  /* connect to the host */
  connection = g_socket_client_connect_to_host (client,
                                               (gchar*)"localhost",
                                                4000, /* your port goes here */
                                                NULL,
                                                &error);

  /* don't forget to check for errors */
  if (error != NULL)
  {
      g_error (error->message);
  }
  else
  {
      g_print ("Connection successful!\n");
  }
  g_timeout_add(1000, send,NULL);
  /* don't forget to check for errors */
  
  GMainLoop *loop = g_main_loop_new(NULL, FALSE); 
                     g_main_loop_run(loop); 
  return 0;
}

