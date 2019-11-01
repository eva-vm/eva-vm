name = 'eva'

eva_src = files(
	'cli.c',
	'disassemble.c',
	'eva.c',
	'eval.c'
)

eva_lib = static_library(name, eva_src)

eva_exe = executable(name,
	files('vm.c'),
	# dependencies: sdl_dep,
	link_with: eva_lib,
	install:true)
