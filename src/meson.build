name = 'eva'

eva_src = files(
	'cli.c',
	'disassemble.c',
	'eva.c',
	'eval.c'
)

eva_lib = static_library(name, eva_src, include_directories: eva_inc)
eva_dep = declare_dependency(link_with: eva_lib, include_directories: eva_inc)

eva_exe = executable(name,
	files('vm.c'),
	dependencies: [sdl_dep, eva_dep],
	link_with: eva_lib,
	install:true)
