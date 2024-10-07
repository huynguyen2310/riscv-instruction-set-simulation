#include "systemc.h"
#include <csignal>

bool debug_session = false;
bool mem_dump = false;

uint32_t dum_addr_start = 0;
uint32_t dum_addr_end = 0;

SC_MODULE(hello_world) {
	SC_CTOR(hello_world) {
		//nothing
	}
	void say_hello() {
		cout << "Hello world\n";
	}
};

void intHandler(int dummy) {
	(void)dummy;
	exit(-1);
}

void process_arguments(int argc, char* argv[]) {
	int c;
	long int debug_level;

	debug_session = false;
	//set up cpu type
	std::string filename;
	for (int i = 1; i < argc; i++) {
		std::string arg = argv[i];
		if (arg == "-D") {
			debug_session = true;
			std::cout << "Jump to debug session\n";
		} else if (arg == "-T") {
			mem_dump = true;
		}
		else if (arg == "-R" && (i + 1) < argc) {
			if (strcmp(argv[i++], "32") == 0) {
				//cpu 32
			}
			else {
				//cpu 64
			}
		}
		else {
			filename = arg;
		}
	}
	if (filename.empty() && (argc > 1)) {
		filename = argv[argc - 1];
	}

	std::cout << "Debug session: " << (debug_session ? "Enable" : "Disable") << "\n";
	std::cout << "Memory Dump: " << (mem_dump ? "Enable" : "Disable") << "\n";
	std::cout << "CPU Type: " << "\n";
	std::cout << "Filename: " << filename << "\n";
}

int sc_main(int argc, char* argv[]) {
	hello_world hello("");
	hello.say_hello();

	signal(SIGINT, intHandler);
	sc_core::sc_set_time_resolution(1, sc_core::SC_NS); //time resolution sets to 1ns
	process_arguments(argc, argv);
	sc_core::sc_start();
	return 0;
}