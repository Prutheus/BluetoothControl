#include <libappindicator/app-indicator.h>

static void activate_powersafe(GtkAction *action);
static void deactivate_powersafe(GtkAction *action);

GtkWidget*      indicator_menu;
GtkActionGroup* action_group;
GtkUIManager*   uim;
AppIndicator*   indicator;
GError*         error = NULL;

static GtkActionEntry entries[] = { {"Activate Powersafe", "gtk-go-forward-ltr", "_Activate Powersafe", "<control>A", "", G_CALLBACK(activate_powersafe)}
                                  , {"Deactivate Powersafe", "gtk-go-forward-ltr", "_Deactivate Powersafe", "<control>D", "", G_CALLBACK(deactivate_powersafe)}
                                  , {"Quit", "application-exit", "_Quit", "<control>Q", "", G_CALLBACK(gtk_main_quit)},
                                  };

static guint n_entries = G_N_ELEMENTS(entries);

static const gchar *ui_info =
"<ui>"
"  <popup name='IndicatorPopup'>"
"    <menuitem action='Activate Powersafe' />"
"    <menuitem action='Deactivate Powersafe' />"
"    <menuitem action='Quit' />"
"  </popup>"
"</ui>";

static void activate_powersafe(GtkAction *action) {
  app_indicator_set_icon_theme_path(indicator, "/home/prutheus/workspace/programming/c/BluetoothControl/");
  app_indicator_set_icon(indicator, "bt_off");

  system("sudo hciconfig hci0 down");
}

static void deactivate_powersafe(GtkAction *action) {
  app_indicator_set_icon_theme_path(indicator, "/home/prutheus/workspace/programming/c/BluetoothControl/");
  app_indicator_set_icon(indicator, "bt_on");

  system("sudo hciconfig hci0 up");
}

int main(int argc, char **argv) {
  gtk_init(&argc, &argv);

  action_group = gtk_action_group_new("BluetoothControl");
  gtk_action_group_add_actions(action_group, entries, n_entries, NULL);

  uim = gtk_ui_manager_new();
  gtk_ui_manager_insert_action_group(uim, action_group, 0);

  if(!gtk_ui_manager_add_ui_from_string(uim, ui_info, -1, &error)) {
    g_message("Failed to build menus: %s\n", error->message);
    g_error_free(error);
    error = NULL;
  }

  indicator = app_indicator_new_with_path("BluetoothControl", "/home/prutheus/workspace/programming/c/BluetoothControl/bt_on.svg", APP_INDICATOR_CATEGORY_APPLICATION_STATUS, "/home/prutheus/workspace/programming/c/BluetoothControl/");

  indicator_menu = gtk_ui_manager_get_widget(uim, "/ui/IndicatorPopup");

  app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);

  app_indicator_set_menu(indicator, GTK_MENU(indicator_menu));

  system("sudo hciconfig hci0 up");

  gtk_main();

  return 0;
}
