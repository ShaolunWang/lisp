build:
	cd build && cmake -G Ninja ../ && cmake --build .
cleanup:
	rm -rf build/*
lsp:
	cp build/compile_commands.json .
