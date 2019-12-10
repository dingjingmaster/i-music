/* i_music-main.c
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

#include "i_music_config.h"
#include "i_music_main.h"

struct _IMusicMain
{
    GtkApplicationWindow  parent_instance;

    GtkWidget* main_box;
    GtkWidget* main_box_header;
    //GtkWidget* main_box_header_back;
    //GtkWidget* main_box_header_title;
};

/* 宏 */
G_DEFINE_TYPE (IMusicMain, i_music_main, GTK_TYPE_APPLICATION_WINDOW)
#define IMUSIC_MAIN(obj)\
        G_TYPE_CHECK_INSTANCE_CAST ((obj), I_MUSIC_TYPE_MAIN, IMusicMain)

/* 事件回调 */
static gboolean main_back_enter_event (GtkWidget* widget, GdkEventExpose* event, gpointer data);
static gboolean main_back_leave_event (GtkWidget* widget, GdkEventExpose* event, gpointer data);

/* 全局常量 */
static GtkWidget* main_header_back_normal = NULL;
static GtkWidget* main_header_back_activity = NULL;

static void test_quit (GtkWidget* widget, gpointer data)
{
    gtk_widget_destroy (GTK_WIDGET (data));
}

/* 公共函数 */
static void load_picture (GtkWidget* img, const char* path, int width, int height);

static void init_main_header (GtkWidget* widget)
{
    IMusicMain* mm = NULL;
    GtkWidget* overlay = NULL;
    GtkWidget* header_hbox = NULL;

    GtkWidget* main_box_header_back = NULL;
    GtkWidget* main_box_header_title = NULL;

    mm = IMUSIC_MAIN (widget);
    main_box_header_back = gtk_event_box_new ();

    header_hbox = mm->main_box_header;
    gtk_window_set_decorated (GTK_WINDOW(mm), FALSE);

    // 返回键
    overlay = gtk_overlay_new ();
    load_picture (main_header_back_normal, "/org/dingjingmaster/music/pic/back_normal.png",
                  I_MUSIC_HEADER_BACK_SIZE, I_MUSIC_HEADER_BACK_SIZE);
    load_picture (main_header_back_activity, "/org/dingjingmaster/music/pic/back_activity.png",
                  I_MUSIC_HEADER_BACK_SIZE, I_MUSIC_HEADER_BACK_SIZE);
    gtk_container_add(GTK_CONTAINER (overlay), main_header_back_normal);
    gtk_overlay_add_overlay (GTK_OVERLAY (overlay), main_header_back_activity);
    gtk_container_add (GTK_CONTAINER (main_box_header_back), overlay);
    gtk_widget_hide (main_header_back_activity);
    gtk_widget_show (main_header_back_normal);
    gtk_widget_set_size_request (main_box_header_back, I_MUSIC_HEADER_BACK_SIZE, I_MUSIC_HEADER_BACK_SIZE);
    g_signal_connect (G_OBJECT(main_box_header_back), "enter-notify-event", G_CALLBACK(main_back_enter_event), NULL);
    g_signal_connect (G_OBJECT(main_box_header_back), "leave-notify-event", G_CALLBACK(main_back_leave_event), NULL);

    // 标题
    main_box_header_title = gtk_label_new ("I-Music");

    // 最小化、关闭按钮

    gtk_box_pack_start (GTK_BOX(header_hbox), main_box_header_back, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX(header_hbox), main_box_header_title, TRUE, TRUE, 0);
    gtk_widget_show_all (header_hbox);
}

static void i_music_main_class_init (IMusicMainClass *klass)
{
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

    // 由resource文件中提供的ui资源设置模板
    gtk_widget_class_set_template_from_resource (widget_class, "/org/dingjingmaster/music/ui/i_music_main.ui");
    gtk_widget_class_bind_template_child (widget_class, IMusicMain, main_box);
    gtk_widget_class_bind_template_child (widget_class, IMusicMain, main_box_header);
}

static void i_music_main_init (IMusicMain *self)
{
    // 初始化变量
    main_header_back_normal = gtk_image_new();
    main_header_back_activity = gtk_image_new();

    // 初始化ui资源中的所有子控件
    gtk_widget_init_template (GTK_WIDGET (self));

    // 设置窗口大小限制
    gtk_widget_set_size_request (GTK_WIDGET (self), I_MUSIC_MAIN_WIDTH, I_MUSIC_MAIN_HEIGHT);

    // 初始化主窗口头
    init_main_header (GTK_WIDGET(self));
}

static gboolean main_back_enter_event (GtkWidget* widget, GdkEventExpose* event, gpointer data)
{
    gtk_widget_show (main_header_back_activity);
    gtk_widget_hide (main_header_back_normal);
    return TRUE;
}

static gboolean main_back_leave_event (GtkWidget* widget, GdkEventExpose* event, gpointer data)
{
    gtk_widget_show (main_header_back_normal);
    gtk_widget_hide (main_header_back_activity);
    return TRUE;
}

static void load_picture (GtkWidget* img, const char* path, int width, int height)
{
    GdkPixbuf* pixbuf = NULL;
    GdkPixbuf* scaled = NULL;

    pixbuf = gdk_pixbuf_new_from_resource (path, NULL);
    if (NULL == pixbuf) {
        return;
    }
    scaled = gdk_pixbuf_scale_simple (pixbuf, width, height, GDK_INTERP_BILINEAR);
    if (NULL == scaled) {
        g_print ("back2");
        g_object_unref (pixbuf);
        return;
    }
    gtk_image_set_from_pixbuf (GTK_IMAGE(img), scaled);
    g_object_unref (scaled);
    g_object_unref (pixbuf);
}
