#ifndef HDE_H
#define HDE_H

#if defined(__LP64__) || defined(__x86_64__) || defined(_M_X64)
#include "minfuncfind/hde64.h"
#define hde hde64s
#define hde_disasm hde64_disasm

#define VAL_SET_REGMASK 0

typedef enum
{
    e_len=1,
    e_reg_src1=e_len<<1,
    e_reg_src2=e_reg_src1<<1,
    e_reg_dst1=e_reg_src2<<1,
    e_reg_dst2=e_reg_dst1<<1,
    e_opcode1=e_reg_dst2<<1,
    e_opcode2=e_opcode1<<1,
    e_regsz=e_opcode2<<1,
    e_addrmode=e_regsz<<1,
    e_imm=e_addrmode<<1,
    e_disp=e_imm<<1,
} val_set_t;

#define X86_2OPCMD(op1, op2)    ((uint16_t)(op1 | (op2 << 0x10)))

#define CONDJMP_1       0x0f
#define CONDJMP_2       0x84
#define MOV_RR          0x8b
#define SHR_RI          0xc1
#define LEA_RRI         0x8d
#define ADD_RR          0x03
#define MOV_RI          0xb8
#define MOV_RADDR_R     0x89
#define CALL_I          0xe8
#define CALL_DREFREL    0xff
// one or two byte push
#define PUSH_R          0x50
#define POP_R           0x58

#define RETURN_x86      0xc3

// len 0xa
// rax is rex_w

#define ADDRMODE_RR         0x03
#define ADDRMODE_REL        0x00
#define ADDRMODE_DREF       0x01
#define ADDRMODE_DREFW      0x02

#define RAX     0
#define RCX     1
#define RDX     2
#define RBX     3
#define RSP     4
#define RBP     5
#define RSI     6
#define RDI     7

#define R8      8
#define R9      9
#define R10     10
#define R11     11
#define R12     12
#define R13     13
#define R14     14
#define R15     15

typedef struct {
    uint8_t len;
    union
    {
        struct
        {
            uint8_t opcode1;
            uint8_t opcode2;
        };
        uint16_t opcode;        
    };
    uint8_t reg_src1;
    uint8_t reg_src2;
    uint8_t reg_dst1;
    uint8_t reg_dst2;
    uint8_t regsz;
    uint8_t addrmode;
    int64_t imm;
    int32_t disp;
} hde64s_t;

#ifdef __cplusplus
extern "C"
{
#endif
int parseInst(uint8_t* pc, hde64s_t* instTemp);
#ifdef __cplusplus
}
#endif

#else
#include "minfuncfind/hde32.h"
#define hde hde32s
#define hde_disasm hde32_disasm
#endif

#endif