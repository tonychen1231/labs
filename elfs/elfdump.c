#include <elf.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int header_read(FILE *fp, Elf32_Ehdr *hdr);

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file.elf\n", argv[0]);
        exit(1);
    }

    FILE *fp = fopen(argv[1], "rb");
    Elf32_Ehdr hdr;

    printf("\n== Elf32_Ehdr ==\n");
    if (header_read(fp, &hdr)) {
        fprintf(stderr, "\n== Not ELF format file ==\n");
        exit(2);
    }

    putchar('\n');
    return 0;
}

int header_read(FILE*fp, Elf32_Ehdr *hdr)
{
    unsigned i;
    unsigned char *p = (unsigned char*)hdr->e_ident;

    if (fread(hdr, sizeof(Elf32_Ehdr), 1, fp) != 1) 
        return -1;

    printf("e_ident[%d]:\n  ", EI_NIDENT);
    for (i = 0; i < EI_NIDENT; ++i) {
        if (isprint(*p))
            printf("%3c ", *p);
        else 
            printf("%03o ", *p);
        ++p;
    }
    putchar('\n');

    p -= EI_NIDENT;
    if (*p != 0x7f || *(p+1) != 'E' || *(p+2) != 'L' || *(p+3) != 'F') 
        return -1;

    printf("  EI_CLASS:%s, EI_DATA:%s, EI_VERSION:%d\n",
            (*(p+EI_CLASS) == ELFCLASSNONE) ? "ELFCLASSNONE" :
            (*(p+EI_CLASS) == ELFCLASS32) ? "ELFCLASS32" :
            (*(p+EI_CLASS) == ELFCLASS64) ? "ELFCLASS64" : "Unknown", 
            (*(p+EI_DATA) == ELFDATANONE) ? "ELFDATANONE" : 
            (*(p+EI_DATA) == ELFDATA2LSB) ? "ELFDATA2LSB" : 
            (*(p+EI_DATA) == ELFDATA2MSB) ? "ELFDATA2MSB" : "Unknown",
            *(p+EI_VERSION)
          );

    Elf32_Half etype = hdr->e_type;
    printf("e_type:\n  %s\n", 
              (etype == ET_NONE) ? "No filetype" : 
              (etype == ET_REL) ? "Relacatable file" : 
              (etype == ET_EXEC) ? "Executable file" : 
              (etype == ET_DYN) ? "Shared object file" : 
              (etype == ET_CORE) ? "Core file" : 
              (etype >= ET_LOPROC && etype <= ET_HIPROC) ? "Processor-specific" : "Unknown");

    Elf32_Half emachine = hdr->e_machine;
    printf("e_machine:\n  %s\n", 
            (emachine == EM_NONE) ? "No machine" : 
            (emachine == EM_M32) ? "AT&T WE 32100" : 
            (emachine == EM_SPARC) ? "SUN SPARC" : 
            (emachine == EM_386) ? "Intel 80386" : 
            (emachine == EM_68K) ? "Motorola m68k family" : 
            (emachine == EM_88K) ? "Motorola m88k family" : 
            (emachine == EM_860) ? "Intel 80860" : 
            (emachine == EM_MIPS) ? "MIPS R3000 big-endian" : 
            (emachine == EM_S370) ? "IBM System/370" : 
            (emachine == EM_MIPS_RS3_LE) ? "MIPS R3000 little-endian" : 
            (emachine == EM_PARISC) ? "HPPA" : 
            (emachine == EM_VPP500) ? "Fujitsu VPP500" : 
            (emachine == EM_SPARC32PLUS) ? "Sun's \"v8plus\"" : 
            (emachine == EM_960) ? "Intel 80960" : 
            (emachine == EM_PPC) ? "PowerPC" : 
            (emachine == EM_PPC64) ? "PowerPC 64-bit" : 
            (emachine == EM_S390) ? "IBM S390" : 
            (emachine == EM_V800) ? "NEC V800 series" : 
            (emachine == EM_FR20) ? "Fujitsu FR20" : 
            (emachine == EM_RH32) ? "TRW RH-32" : 
            (emachine == EM_RCE) ? "Motorola RCE" : 
            (emachine == EM_ARM) ? "ARM" : 
            (emachine == EM_FAKE_ALPHA) ? "Digital Alpha" : 
            (emachine == EM_SH) ? "Hitachi SH" : 
            (emachine == EM_SPARCV9) ? "SPARC v9 64-bit" : 
            (emachine == EM_TRICORE) ? "Siemens Tricore" : 
            (emachine == EM_ARC) ? "Argonaut RISC Core" : 
            (emachine == EM_H8_300) ? "Hitachi H8/300" : 
            (emachine == EM_H8_300H) ? "Hitachi H8/300H" : 
            (emachine == EM_H8S) ? "Hitachi H8S" : 
            (emachine == EM_H8_500) ? "Hitachi H8/500" : 
            (emachine == EM_IA_64) ? "Intel Merced" : 
            (emachine == EM_MIPS_X) ? "Stanford MIPS-X" : 
            (emachine == EM_COLDFIRE) ? "Motorola Coldfire" : 
            (emachine == EM_68HC12) ? "Motorola M68HC12" : 
            (emachine == EM_MMA) ? "EM_MMA" : 
            (emachine == EM_PCP) ? "Siemens PCP" : 
            (emachine == EM_NCPU) ? "Sony nCPU embeeded RISC" : 
            (emachine == EM_NDR1) ? "Denso NDR1 microprocessor" : 
            (emachine == EM_STARCORE) ? "Motorola Start*Core processor" : 
            (emachine == EM_ME16) ? "Toyota ME16 processor" : 
            (emachine == EM_ST100) ? "STMicroelectronic ST100 processor" : 
            (emachine == EM_TINYJ) ? "EM_TINY" : 
            (emachine == EM_X86_64) ? "AMD x86-64 architecture" : 
            (emachine == EM_PDSP) ? "Sony DSP Processor" : 
            (emachine == EM_FX66) ? "Siemens FX66 microcontroller" : 
            (emachine == EM_ST9PLUS) ? "STMicroelectronics ST9+ 8/16 mc" : 
            (emachine == EM_ST7) ? "STmicroelectronics ST7 8 bit mc" : 
            (emachine == EM_68HC16) ? "Motorola MC68HC16 microcontroller" : 
            (emachine == EM_68HC11) ? "Motorola MC68HC11 microcontroller" : 
            (emachine == EM_68HC08) ? "Motorola MC68HC08 microcontroller" : 
            (emachine == EM_68HC05) ? "Motorola MC68HC05 microcontroller" : 
            (emachine == EM_SVX) ? "Silicon Graphics SVx" : 
            (emachine == EM_ST19) ? "STMicroelectronics ST19 8 bit mc" : 
            (emachine == EM_VAX) ? "Digital VAX" : 
            (emachine == EM_CRIS) ? "Axis Communications 32-bit embedded processor" : 
            (emachine == EM_JAVELIN) ? "Infineon Technologies 32-bit embedded processor" : 
            (emachine == EM_FIREPATH) ? "Element 14 64-bit DSP Processor" : 
            (emachine == EM_ZSP) ? "LSI Logic 16-bit DSP Processor" : 
            (emachine == EM_MMIX) ? "Donald Knuth's educational 64-bit processor" : 
            (emachine == EM_HUANY) ? "Harvard University machine-independent object files" : 
            (emachine == EM_PRISM) ? "SiTera Prism" : 
            (emachine == EM_AVR) ? "Atmel AVR 8-bit microcontroller" : 
            (emachine == EM_FR30) ? "Fujitsu FR30" : 
            (emachine == EM_D10V) ? "Mitsubishi D10V" : 
            (emachine == EM_D30V) ? "Mitsubishi D30V" : 
            (emachine == EM_V850) ? "NEC v850" : 
            (emachine == EM_M32R) ? "Mitsubishi M32R" : 
            (emachine == EM_MN10300) ? "Matsushita MN10300" : 
            (emachine == EM_MN10200) ? "Matsushita MN10200" : 
            (emachine == EM_PJ) ? "picoJava" : 
            (emachine == EM_OPENRISC) ? "OpenRISC 32-bit embedded processor" : 
            (emachine == EM_ARC_A5) ? "ARC Cores Tangent-A5" : 
            (emachine == EM_XTENSA) ? "Tensilica Xtensa Architecture" : "Unknown");

    return 0;
}
