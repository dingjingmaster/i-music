/* main.c
 *
 * Copyright 2019 dingjingmaster
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib/gi18n.h>

#include "i_music_config.h"
#include "i_music_main.h"

static void on_activate (GtkApplication *app)
{
    GtkWindow *window;

    g_assert (GTK_IS_APPLICATION (app));
    window = gtk_application_get_active_window (app);
    if (window == NULL) {
        // 创建
        window = g_object_new (I_MUSIC_TYPE_MAIN, "application", app, "default-width", 600, "default-height", 300, NULL);
    }
    gtk_window_present (window);
}

int main (int argc, char *argv[])
{
    g_autoptr(GtkApplication) app = NULL;

    bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
    bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
    textdomain (GETTEXT_PACKAGE);

    app = gtk_application_new ("org.dingjingmaster.music", G_APPLICATION_FLAGS_NONE);

    // 当 g_application_run 执行时触发
    g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);

    return g_application_run (G_APPLICATION (app), argc, argv);
}
