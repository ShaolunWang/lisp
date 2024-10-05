build:
	cd build && cmake -G Ninja ../ && cmake --build .
cleanup:
	rm -rf build/*
