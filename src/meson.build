i_music_sources = [
  'main.c',
  'i_music-window.c',
]

i_music_deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
]

gnome = import('gnome')

i_music_sources += gnome.compile_resources('i_music-resources',
  'i_music.gresource.xml',
  c_name: 'i_music'
)

executable('i-music', i_music_sources,
  dependencies: i_music_deps,
  install: true,
)
