Hutu{
	printf("  %-34s %u", "Version:", buffer[EI_VERSION]);

	if (buffer[EI_VERSION] == EV_CURRENT)
		printf(" (current)\n");
	else
		printf("\n");
}
/**
 * elf_osabi - a fxn dat print ELF OS/ABI
 * @buffer: d ELF header
 */
void elf_osabi(const unsigned char *buffer)
{
	const char *os_table[19] = {
		"UNIX - System V",
		"UNIX - HP-UX",
		"UNIX - NetBSD",
		"UNIX - GNU",
		"<unknown: 4>",
		"<unknown: 5>",
		"UNIX - Solaris",
		"UNIX - AIX",
		"UNIX - IRIX",
		"UNIX - FreeBSD",
		"UNIX - Tru64",
		"Novell - Modesto",
		"UNIX - OpenBSD",
		"VMS - OpenVMS",
		"HP - Non-Stop Kernel",
		"AROS",
		"FenixOS",
		"Nuxi CloudABI",
		"Stratus Technologies OpenVOS"
	};
	printf("  %-34s ", "OS/ABI:");

	if (buffer[EI_OSABI] < 19)
		printf("%s\n", os_table[(unsigned int) buffer[EI_OSABI]]);
	else
		printf("<unknown: %x>\n", buffer[EI_OSABI]);
}
/**
 * elf_abivers - a fxn dat print ELF ABI version
 * @buffer: d ELF header
 */
void elf_abivers(const unsigned char *buffer)
{
	printf("  %-34s %u\n", "ABI Version:", buffer[EI_ABIVERSION]);
}
/**
 * elf_type - a fxn dat print ELF type
 * @buffer: d ELF header
 * @big_endian: endianness (big endian if non-zero)
 */
void elf_type(const unsigned char *buffer, int big_endian)
{
	char *Type_table[5] = {
		"NONE (No file type)",
		"REL (Relocatable file)",
		"EXEC (Executable file)",
		"DYN (Shared object file)",
		"CORE (Core file)"
	};
	unsigned int typed;

	printf("  %-34s ", "Type:");

	if (big_endian)
		typed = 0x100 * buffer[16] + buffer[17];
	else
		typed = 0x100 * buffer[17] + buffer[16];

	if (typed < 5)
		printf("%s\n", Type_table[typed]);
	else if (typed >= ET_LOOS && typed <= ET_HIOS)
		printf("OS Specific: (%4x)\n", typed);
	else if (typed >= ET_LOPROC && typed <= ET_HIPROC)
		printf("Processor Specific: (%4x)\n", typed);
	else
		printf("<unknown: %x>\n", typed);
}
/**
 * elf_entry - a fxn dat prints entry point address
 * @buffer: it is a string containing d entry point address
 * @bit_mode: a bit mode (32 or 64)
 * @big_endian: d endianness (big endian if non-zero)
 */
void elf_entry(const unsigned char *buffer, size_t bit_mode, int big_endian)
{
	int Address_size = bit_mode / 8;

	printf("  %-34s 0x", "Entry point address:");

	if (big_endian)
	{
		while (Address_size && !*(buffer))
			--Address_size, ++buffer;

		printf("%x", *buffer & 0xff);

		while (--Address_size > 0)
			printf("%02x", *(++buffer) & 0xff);
	}
	else
	{
		buffer += Address_size;

		while (Address_size && !*(--buffer))
			--Address_size;

		printf("%x", *buffer & 0xff);

		while (--Address_size > 0)
			printf("%02x", *(--buffer) & 0xff);
	}

	printf("\n");
}
/**
 * main - a fxn dat copy's a file's contents to another file
 * @argc: the argument count
 * @argv: the argument figures
 *
 * Return: Always 0
 */
int main(int argc, const char *argv[])
{
	unsigned char buffer[18];
	unsigned int bit_mode;
	int big_endian;
	int fd;

	if (argc != 2)
	{
		write(STDERR_FILENO, "Usage: elf_header elf_filename\n", 31);
		exit(98);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(STDERR_FILENO, "Error: Can't read from file\n", 28);
		exit(98);
	}

	_read(fd, (char *) buffer, 18);

	elf_magic(buffer);
	bit_mode = elf_class(buffer);
	big_endian = elf_data(buffer);
	elf_version(buffer);
	elf_osabi(buffer);
	elf_abivers(buffer);
	elf_type(buffer, big_endian);

	lseek(fd, 24, SEEK_SET);
	_read(fd, (char *) buffer, bit_mode / 8);

	elf_entry(buffer, bit_mode, big_endian);

	_close(fd);

	return (0);
}

