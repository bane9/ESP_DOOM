void app_main(void)
{
	extern int doom_main(int argc, char **argv);

	char* argv[] = {"doom", "-mb", "3","-iwad", "doom1.wad", 0};
	int argc = sizeof(argv) / sizeof(argv[0]) - 1;

	doom_main(argc, argv);
}
