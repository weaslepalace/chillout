#include <gio/gio.h>
#include <stdio.h>
#include <errno.h>
void keep_locked(GDBusConnection *con);

void print_signal(
	GDBusProxy *proxy,
	gchar *sender,
	gchar *signal,
	GVariant *params,
	gpointer dat)
{
	fprintf(stderr, "Got a signal!\n");
	fprintf(stderr, "Sender: %s\n", sender);
	fprintf(stderr, "Signal: %s\n", signal);
	fprintf(stderr, "Params: %s\n", g_variant_print(params, TRUE));
}


void print_prop_change(
	GDBusProxy *proxy,
	GVariant *props,
	GStrv inval_props,
	gpointer dat)
{
	fprintf(stderr, "A property has changed!\n");
	fprintf(stderr, "%s\n", g_variant_print(props, TRUE));	
}


int lock(void)
{
	GMainLoop *loop = g_main_loop_new(NULL, FALSE);

	GDBusProxy *proxy = g_dbus_proxy_new_for_bus_sync(
		G_BUS_TYPE_SESSION,
		G_DBUS_PROXY_FLAGS_NONE,
		NULL,
		"org.gnome.ScreenSaver",
		"/org/gnome/ScreenSaver",
		"org.gnome.ScreenSaver",
		NULL,
		NULL);
	if(NULL == proxy)
	{
		fprintf(stderr, "Connect to Bus Failed %s\n", strerror(errno));
		return -1;
	}

	g_signal_connect(proxy, "g-signal", G_CALLBACK(print_signal), NULL);
	g_signal_connect(
		proxy,
		"g-properties-changed",
		G_CALLBACK(print_prop_change),
		NULL);
	

	GVariant *result = g_dbus_proxy_call_sync(
		proxy,
		"Lock",
		NULL,
		G_DBUS_CALL_FLAGS_NONE,
		-1, //Default timeout
		NULL,
		NULL);
	if(NULL == result)
	{
		fprintf(stderr, "Method Call Failed %s\n", strerror(errno));
		goto CLEANUP;
	}

	fprintf(stderr, "%s\n", g_variant_print(result, TRUE));
	g_variant_unref(result);

	g_main_loop_run(loop);
	CLEANUP:
	g_object_unref(proxy);
	return 0;
}

