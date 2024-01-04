#include <string.h>
#define FORCE_X86_64 1
#include "hde.h"

int parseInst(uint8_t* pc, hde64s_t* instOut)
{
    int result = -1;
    hde64s instTmp = {0};
    
    memset(instOut, 0, sizeof(hde64s_t));
    hde64_disasm(pc, &instTmp);

    if (
        ((instTmp.opcode & 0xf8) == 0xb8) ||
        ((instTmp.opcode & 0xf8) == 0x58) ||
        ((instTmp.opcode & 0xf8) == 0x50)
        )
    {
        instOut->reg_dst1 = (instTmp.opcode & 0x07) | instTmp.rex_b << 3;
        instOut->opcode1 = instTmp.opcode & 0xf8;
    }
    else
    {
        instOut->reg_src1 = (instTmp.rex_b << 3) | instTmp.modrm_rm;
        instOut->reg_dst1 = (instTmp.rex_r << 3) | instTmp.modrm_reg;
        instOut->opcode1 = instTmp.opcode;
    }

    instOut->addrmode = instTmp.modrm_mod;
    instOut->len = instTmp.len;
    instOut->imm = instTmp.imm.imm64;
    instOut->disp = instTmp.disp.disp32;
    instOut->regsz = instTmp.sib;

    instOut->opcode2 = instTmp.opcode2;

    result = 0;
fail:
    return result;
}
