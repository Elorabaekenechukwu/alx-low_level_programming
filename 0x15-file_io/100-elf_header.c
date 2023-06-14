#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <unistd.h>
#include <fcntl.h>
/**
 * _strncmp - comparing double strings
 * @s1: the 1st string
 * @s2: the 2nd string
 * @n: the maximum num of bytes to compare
 *
 * Return: 0 if d first n bytes of s1 and s2 are equal, otherwise non-zero
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	for ( ; n && *s1 && *s2; --n, ++s1, ++s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
	}
	if (n)
	{
		if (*s1)
			return (1);
		if (*s2)
			return (-1);
	}
	return (0);
}
/**
 * _close - a fxn dat close a file descript & print an error msg  upon failure
 * @fd: d file descriptor 2 close
 */
void _close(int fd)
{
	if (close(fd) != -1)
		return;
	write(STDERR_FILENO, "Error: Can't close fd\n", 22);
	exit(98);
}
/**
 * _read - read frm a file &  print an error msg upon failure
 * @fd: d file descript 2 read frm
 * @buf: d buffer 2 write to
 * @count: d num of bytes 2 read
 */
void _read(int fd, char *buf, size_t count)
{
	if (read(fd, buf, count) != -1)
		return;
	write(STDERR_FILENO, "Error: Can't read from file\n", 28);
	_close(fd);
	exit(98);
}
/**
 * elf_magic - a fxn dat print ELF magic
 * @buffer: d ELF header
 */
void elf_magic(const unsigned char *buffer)
{
	unsigned int a;

	if (_strncmp((const char *) buffer, ELFMAG, 4))
	{
		write(STDERR_FILENO, "Error: Not an ELF file\n", 23);
		exit(98);
	}

	printf("ELF Header:\n  Magic:   ");

	for (a = 0; a < 16; ++a)
		printf("%02x%c", buffer[a], a < 15 ? ' ' : '\n');
}
/**
 * elf_class - a fxn dat print ELF class
 * @buffer: d ELF header
 *
 * Return: the bit mode (32 or 64)
 */
size_t elf_class(const unsigned char *buffer)
{
	printf("  %-34s ", "Class:");

	if (buffer[EI_CLASS] == ELFCLASS64)
	{
		printf("ELF64\n");
		return (64);
	}
	if (buffer[EI_CLASS] == ELFCLASS32)
	{
		printf("ELF32\n");
		return (32);
	}
	printf("<unknown: %x>\n", buffer[EI_CLASS]);
	return (32);
}
/**
 * elf_data - a fxn dat print ELF data
 * @buffer: d ELF header
 *
 * Return: 1 if big endian, otherwise 0
 */
int elf_data(const unsigned char *buffer)
{
	printf("  %-34s ", "Data:");

	if (buffer[EI_DATA] == ELFDATA2MSB)
	{
		printf("2's complement, big endian\n");
		return (1);
	}
	if (buffer[EI_DATA] == ELFDATA2LSB)
	{
		printf("2's complement, little endian\n");
		return (0);
	}
	printf("Invalid data encoding\n");
	return (0);
}
/**
 * elf_version - a fxn dat print ELF version
 * @buffer: d ELF header
 */
void elf_version(const unsigned char *buffer)
{
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
