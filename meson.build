project(
  'deckhandler',
  'c',
  version: '0.0.1',
  meson_version: '>= 0.56.0',
  default_options: ['warning_level=3', 'c_std=c99'],
)

cc = meson.get_compiler('c')

extra_flags = [
  '-fno-common',
  '-fstack-protector-strong',
  '-Wformat-security',
  '-Wshadow',
  '-Wstrict-overflow=5',
  '-Werror=odr',
  '-Werror=strict-aliasing',
]

add_project_arguments(cc.get_supported_arguments(extra_flags), language: 'c')

# Parse version components
version_components = meson.project_version().split('.')
major_version = version_components[0]
minor_version = version_components[1]
patch_version = version_components[2]

conf = configuration_data()
conf.set('DH_VERSION_MAJOR', major_version)
conf.set('DH_VERSION_MINOR', minor_version)
conf.set('DH_VERSION_PATCH', patch_version)
config_h = configure_file(output : 'config.h', configuration : conf)

src = files('deckhandler.c')

pcg = subproject('pcg')
pcg_dep = pcg.get_variable('pcg_dep')

buildtarget = library(
  meson.project_name(),
  src,
  c_args: '-DDECKHANDLER_BUILD',
  dependencies: pcg_dep,
  version: meson.project_version(),
  install: not meson.is_subproject(),
)

# How to use in a superproject and other info
# https://mesonbuild.com/Subprojects.html
_compile_args = get_option('default_library') == 'static' ? ['-DDECKHANDLER_STATIC'] : []

deckhandler_dep = declare_dependency(
  link_with: buildtarget,
  compile_args: _compile_args,
  dependencies: pcg_dep,
  include_directories: '.',
)

if not meson.is_subproject()
  pkg = import('pkgconfig')
  pkg.generate(buildtarget, description: 'Library to handle a deck of cards')

  install_headers('deckhandler.h')
  subdir('test')

  #  install_subdir(
  #  join_paths('docs'),
  #  install_dir : join_paths(get_option('docdir'), 'html'),
  #  strip_directory : true
  #  )

  #  install_data(files(
  #    'LICENSE',
  #    'README.md',
  #    'SWIG_INTERFACE.md'
  #    ),
  #    install_dir : get_option('docdir'))
endif

swig_lang = get_option('swig_lang')
if swig_lang != ''
  subdir('swig')
endif
