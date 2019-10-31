name = 'eva'

eva_src = files('disassemble.c')

eva_lib = static_library(name, eva_src)

eva_exe = executable(name,
	files('vm.c'),
	# dependencies: sdl_dep,
	link_with: eva_lib,
	install:true)
