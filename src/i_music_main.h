/* i_music-main.h
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

#pragma once

#include <gtk/gtk.h>
#include "i_music_param.h"

G_BEGIN_DECLS

#define I_MUSIC_TYPE_MAIN (i_music_main_get_type())

/* 不可被继承的类型用 G_DECLARE_FINAL_TYPE 声明，要在 .c 中定义结构体
 * 传入参数分别是：定义的类、标签、
 */
G_DECLARE_FINAL_TYPE (IMusicMain, i_music_main, I_MUSIC, WINDOW, GtkApplicationWindow)

G_END_DECLS
