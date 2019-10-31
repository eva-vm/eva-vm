project('evavm', 'c', version: '0.1')

sdl_dep = dependency('sdl2', fallback: ['sdl2', 'sdl2_dep'], required: get_option('SDL'))

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
