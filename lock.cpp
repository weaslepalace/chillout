/**
 * Just writing this from the reference: www.matthew.ath.cx/misc/dbus
 * There may be other reference out there. It is clearly incomplete
 */

DBusMessage *msg;
DBusMessageIter args;
DBusPendingCall *pending;

//Make the message
msg = dbus_mesg_new_method_call(
	"org.gnome.ScreenSaver",  //Service
	"/org/gnome/ScreenSaver"  //Path
	"org.gnone.ScreenSaver",  //Interface
	"Lock");                  //Method
if(NULL == mesg)
{
	//Something's wrong
}

//Send the message
//where does conn come from?
dbus_connection_send_with_reply(conn, msg, NULL, -1);
