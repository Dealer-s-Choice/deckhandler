project(
    'pcg',
    'c',
    version: '0.9',
    meson_version: '>= 0.56.0',
    default_options: ['warning_level=3', 'c_std=c99'],
)

extra_flags = [
    '-fno-common',
    '-fstack-protector-strong',
    '-Wformat-security',
    '-Wshadow',
    '-Wstrict-overflow=5',
    '-Werror=odr',
    '-Werror=strict-aliasing',
]

add_project_arguments(extra_flags, language: 'c')

_pcg = static_library('pcg', 'pcg_basic.c')

pcg_dep = declare_dependency(link_with: _pcg, include_directories: '.')
