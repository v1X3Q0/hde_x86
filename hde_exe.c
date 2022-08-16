#include <stdio.h>
#include <stdlib.h>

#include <localUtil.h>

#ifdef _WIN32
#include <localUtil_windows.h>
#include <getopt.h>
#elif defined(__linux__)
#include <localUtil_linux.h>
#include <unistd.h>
#include <elf.h>
#endif

#include "hde.h"

void usage(const char* argv)
{
    printf("usage: %s [-v] [-m] disasm_file offset\n", argv);
    exit(0);
}

void dump_hde64s(hde64s* hs)
{
#define PRINT_BMEM(MEM_NAME) \
    printf(# MEM_NAME " 0x%02hhx\n", hs->MEM_NAME)

#define PRINT_QMEM(MEM_NAME) \
    printf(# MEM_NAME " 0x%016lx\n", hs->MEM_NAME)

#define PRINT_WMEM(MEM_NAME) \
    printf(# MEM_NAME " 0x%08x\n", hs->MEM_NAME)

    PRINT_BMEM(len);
    PRINT_BMEM(p_rep);
    PRINT_BMEM(p_lock);
    PRINT_BMEM(p_seg);
    PRINT_BMEM(p_66);
    PRINT_BMEM(p_67);
    PRINT_BMEM(rex);
    PRINT_BMEM(rex_w);
    PRINT_BMEM(rex_r);
    PRINT_BMEM(rex_x);
    PRINT_BMEM(rex_b);
    PRINT_BMEM(opcode);
    PRINT_BMEM(opcode2);
    PRINT_BMEM(modrm);
    PRINT_BMEM(modrm_mod);
    PRINT_BMEM(modrm_reg);
    PRINT_BMEM(modrm_rm);
    PRINT_BMEM(sib);
    PRINT_BMEM(sib_scale);
    PRINT_BMEM(sib_index);
    PRINT_BMEM(sib_base);
    PRINT_QMEM(imm.imm64);
    PRINT_WMEM(disp.disp32);
    PRINT_WMEM(flags);
}

int main(int argc, char** argv)
{
    int result = -1;
    int opt = 0;
    const char* exec_path = 0;
    void* allocBase = 0;
    size_t fSize = 0;
    int isVirt = 0;
    int is32bit = 0;
    size_t offset = 0;
    hde64s hs = { 0 };

    while ((opt = getopt(argc, argv, "vm")) != -1)
    {
        switch (opt)
        {
        case 'v':
            isVirt = 1;
            break;
        case 'm':
            is32bit = 1;
            break;
        default: /* '?' */
            usage(argv[0]);
        }
    }

    if (optind == argc)
    {
        usage(argv[0]);
    }
    else
    {
        exec_path = argv[optind];
        optind++;
    }

    if (optind == argc)
    {
        usage(argv[0]);
    }
    else
    {
        offset = strtoul(argv[optind], NULL, 16);
        optind++;
    }

    SAFE_PAIL(block_grab(exec_path, &allocBase, &fSize) == -1, "couldn't find file %s\n", exec_path);

    if (isVirt == 1)
    {
        SAFE_PAIL(virt_to_file(allocBase, offset, &offset) == -1, "translation failed\n");
        printf("provided with virt, translated to 0x%016lx\n", offset);
    }

    SAFE_PAIL(hde64_disasm((const void*)((size_t)allocBase + offset), &hs) == 0, "disasm failed\n");

    dump_hde64s(&hs);
    result = 0;
fail:
    return result;
    
}