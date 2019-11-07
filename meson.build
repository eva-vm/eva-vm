project('evavm', 'c', version: '0.1')

add_project_arguments('-DLOG_LEVEL='+get_option('LOG_LEVEL'), language:'c')

sdl_dep = dependency('sdl2', required: false)

if get_option('SDL').enabled() and not sdl_dep.found()
	sdl_dep = import('cmake').subproject('sdl2').dependency('SDL2main')
endif

eva_inc = include_directories('include')

subdir('include')
subdir('src')
subdir('test')

doxygen_exe = find_program('doxygen', required: get_option('DOCS'))
if doxygen_exe.found()
	doxyout = meson.build_root() / 'docs'
	doxyconf = configuration_data()
	doxyconf.set_quoted('PROJECT_NAME', meson.project_name())
	doxyconf.set_quoted('PROJECT_VERSION', meson.project_version())
	doxyconf.set_quoted('SOURCE_DIR', meson.current_source_dir() / 'src')
	doxyconf.set_quoted('OUTPUT_DIR', doxyout)

	doxyfile = configure_file(input: 'Doxyfile.meson',
							output: 'Doxyfile',
							configuration: doxyconf
	)
	run_target('docs', command: [doxygen_exe, doxyfile])
endif
