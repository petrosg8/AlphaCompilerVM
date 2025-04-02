#include "tcode.h"

#include "alphavm.h"
#include "quads.h"
extern quad* quads;
extern unsigned total;
extern unsigned currQuad;

const char* vmopcode_str[] = {
    "assign",    "add",     "sub",         "mul",          "div",
    "mod",       "uminus",  "and",         "or",           "not",
    "jeq",       "jne",     "jle",         "jge",          "jlt",
    "jgt",       "call",    "param",       "ret",          "getretval",
    "funcstart", "funcend", "tablecreate", "tablegetelem", "tablesetelem",
    "jump",      "nop"};

const char* vmarg_str[] = {"label",    "global",  "formal", "local",
                           "number",   "string",  "bool",   "nil",
                           "userfunc", "libfunc", "retval"};

unsigned totalInstr = 1;
unsigned currInstr = 1;
instruction* instructions = (instruction*)0;

unsigned currprocessedquad = 0;

unsigned nextInstructionLabel() { return currInstr; }

/* Const Tables */

double* numConsts;
unsigned totalNumConsts = 0;
unsigned maxNumConsts = 0;

char** stringConsts;
unsigned totalStringConsts = 0;
unsigned maxStringConsts = 0;

// unsigned* boolConsts;
// unsigned totalBoolConsts = 0;
// unsigned maxBoolConsts = 0;

userfunc_t* userFuncs;
unsigned totalUserfuncs = 0;
unsigned maxUserfuncs = 0;

const char* namedLibfuncs[] = {"print",
                               "input",
                               "objectmemberkeys",
                               "objecttotalmembers",
                               "objectcopy",
                               "totalarguments",
                               "argument",
                               "typeof",
                               "strtonum",
                               "sqrt",
                               "cos",
                               "sin"};
const unsigned totalNamedLibfuncs = 12;
const unsigned maxNamedLibfuncs = 12;

void expand_instr() {
    assert(totalInstr == currInstr);

    instruction* p = (instruction*)malloc(NEW_INSTRSIZE);

    if (instructions) {
        memcpy(p, instructions, CURR_SIZE);
        free(instructions);
    }
    instructions = p;
    totalInstr += EXPAND_SIZE;
}
void expand_numConsts() {
    assert(maxNumConsts == totalNumConsts);

    double* p = (double*)malloc(NEW_NUMCONSTSIZE);

    if (numConsts) {
        memcpy(p, numConsts, totalNumConsts * sizeof(double));
        free(numConsts);
    }
    numConsts = p;
    maxNumConsts += C_NUM_EXPAND_SZ;
}
void expand_stringConsts() {
    assert(maxStringConsts == totalStringConsts);

    char** p = (char**)malloc(NEW_STRCONSTSIZE);

    if (stringConsts) {
        memcpy(p, stringConsts, totalStringConsts * sizeof(char*));
        free(stringConsts);
    }
    stringConsts = p;
    maxStringConsts += C_STR_EXPAND_SZ;
}
void expand_userfuncConsts() {
    assert(maxUserfuncs == totalUserfuncs);

    userfunc_t* p = (userfunc_t*)malloc(NEW_USERFCONSTSIZE);

    if (userFuncs) {
        memcpy(p, userFuncs, totalUserfuncs * sizeof(userfunc_t));
        free(userFuncs);
    }
    userFuncs = p;
    maxUserfuncs += C_USERF_EXPAND_SZ;
}
// void expand_boolConsts() {
//     assert(maxBoolConsts == totalBoolConsts);

//     unsigned* p = (unsigned*)malloc(NEW_BOOLCONSTSIZE);

//     if (boolConsts) {
//         memcpy(p, boolConsts, totalBoolConsts * sizeof(unsigned));
//         free(boolConsts);
//     }
//     boolConsts = p;
//     maxBoolConsts += C_BOOL_EXPAND_SZ;
// }
// void expand_libfuncConsts() {
//     assert(maxNamedLibfuncs == totalNamedLibfuncs);

//     char** p = (char**)malloc(NEW_LIBFCONSTSIZE);

//     if (namedLibfuncs) {
//         memcpy(p, namedLibfuncs, totalNamedLibfuncs * sizeof(char*));
//         free(namedLibfuncs);
//     }
//     namedLibfuncs = p;
//     maxNamedLibfuncs += C_LIBF_EXPAND_SZ;
// }

unsigned consts_newstring(char* str) {
    if (totalStringConsts == maxStringConsts) expand_stringConsts();
    for (unsigned i = 0; i < totalStringConsts; i++) {
        if (stringConsts[i] == str) return i;
    }
    stringConsts[totalStringConsts] = str;

    return totalStringConsts++;
}
// unsigned consts_newbool(unsigned val) {
//     if (totalBoolConsts == maxBoolConsts) expand_boolConsts();
//     for (unsigned i = 0; i < totalBoolConsts; i++) {
//         if (boolConsts[i] == val) return i;
//     }
//     boolConsts[totalBoolConsts] = val;

//     return totalBoolConsts++;
// }
unsigned consts_newnumber(double num) {
    if (totalNumConsts == maxNumConsts) expand_numConsts();
    for (unsigned i = 0; i < totalNumConsts; i++) {
        if (numConsts[i] == num) return i;
    }
    numConsts[totalNumConsts] = num;

    return totalNumConsts++;
}
unsigned userfuncs_newfunc(SymTabEntry* sym) {
    if (totalUserfuncs == maxUserfuncs) expand_userfuncConsts();
    assert(sym && sym->type == USERFUNC_T);

    for (unsigned i = 0; i < totalUserfuncs; i++) {
        if (userFuncs[i].address == sym->value.funcVal->iaddress) return i;
    }
    userFuncs[totalUserfuncs].id = get_symbol_name(sym);
    userFuncs[totalUserfuncs].address =
        sym->value.funcVal
            ->iaddress;  // TODO MAY NEED +1/-1 INDEXING,SHOULD BE GOOD
    userFuncs[totalUserfuncs].localSize = sym->value.funcVal->total_locals;

    return totalUserfuncs++;
}

unsigned libfuncs_getindex(char* name) {
    // if (totalNamedLibfuncs == maxNamedLibfuncs) expand_libfuncConsts();

    for (unsigned i = 0; i < totalNamedLibfuncs; i++) {
        if (strcmp(namedLibfuncs[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

unsigned emit_instr(instruction* instr) {
    if (currInstr == totalInstr) expand_instr();
    if (totalNumConsts == maxNumConsts) expand_numConsts();
    if (totalStringConsts == maxStringConsts) expand_stringConsts();
    // if (totalNamedLibfuncs == maxNamedLibfuncs) expand_libfuncConsts();
    if (totalUserfuncs == maxUserfuncs) expand_userfuncConsts();
    // if (totalBoolConsts == maxBoolConsts) expand_boolConsts();

    instruction* i = instructions + currInstr;

    i->opcode = instr->opcode;
    i->arg1 = instr->arg1;
    i->arg2 = instr->arg2;
    i->result = instr->result;
    i->srcLine = instr->srcLine;

    return currInstr++;
}

// void backpatch_instr(returnList* returnlist, unsigned instrLabel) {
//     assert(instrLabel < totalInstr);
//     returnList* temp = returnlist;

//     while (temp) {
//         instructions[temp->instrLabel].result->val = instrLabel;
//         temp = temp->next;
//     }
// }

void reset_operand(vmarg* arg) {
    if (!arg) return;
    arg->val = -1;
}
// TODO: might need to make numbers only REAL
vmarg* make_num_operand(double val) {
    vmarg* arg = (vmarg*)malloc(sizeof(vmarg));
    arg->val = consts_newnumber(val);
    arg->type = number_a;

    return arg;
}
// vmarg* make_bool_operand(unsigned val) {
//     vmarg* arg = (vmarg*)malloc(sizeof(vmarg));
//     arg->val = consts_newbool(val);
//     arg->type = bool_a;

//     return arg;
// }
vmarg* make_retval_operand() {
    vmarg* arg = (vmarg*)malloc(sizeof(vmarg));
    arg->type = retval_a;
    arg->val = -1;

    return arg;
}
vmarg* make_label_operand(unsigned val) {
    vmarg* arg = (vmarg*)malloc(sizeof(vmarg));
    arg->val = val;
    arg->type = label_a;

    return arg;
}

vmarg* make_operand(expr* e) {
    if (!e) return NULL;

    vmarg* arg = (vmarg*)malloc(sizeof(vmarg));
    memset(arg, 0, sizeof(vmarg));

    switch (e->type) {
        case assignexpr_e:
        case var_e:
        case tableitem_e:
        case arithexpr_e:
        case boolexpr_e:
        case newtable_e: {
            assert(e->sym);
            arg->val = get_var_offset(e->sym);

            switch (e->sym->value.varVal->space) {
                case programvar:
                    arg->type = global_a;
                    break;
                case functionlocal:
                    arg->type = local_a;
                    break;
                case formalarg:
                    arg->type = formal_a;
                    break;
                default:
                    assert(0);
            }
            break;
        }
        case constbool_e: {
            // TODO: check
            arg->val = e->boolConst;
            arg->type = bool_a;
            break;
        }
        case conststring_e: {
            arg->val = consts_newstring(e->strConst);
            arg->type = string_a;
            break;
        }
        // TODO: MAKE CONSTREAL AND CONSTINT INTO ONE CONSTNUM
        case constreal_e: {
            arg->val = consts_newnumber(e->realConst);
            arg->type = number_a;
            break;
        }
        case constint_e: {
            arg->val = consts_newnumber(e->intConst);
            arg->type = number_a;
            break;
        }
        case nil_e: {
            arg->type = nil_a;
            break;
        }
        case programfunc_e: {
            // arg->val = e->sym->value.funcVal->iaddress;
            // TODO: OR ALTERNATIVELY:

            arg->val = userfuncs_newfunc(e->sym);
            arg->type = userfunc_a;
            break;
        }
        case libraryfunc_e: {
            arg->type = libfunc_a;
            arg->val = libfuncs_getindex(get_symbol_name(e->sym));
            break;
        }
        default:
            assert(0);
    }

    return arg;
}

instruction* make_instruction(vmopcode opcode, vmarg* result, vmarg* arg1,
                              vmarg* arg2, unsigned srcLine) {
    instruction* t = (instruction*)malloc(sizeof(instruction));
    memset(t, 0, sizeof(instruction));

    t->opcode = opcode;
    t->srcLine = srcLine;
    t->arg1 = arg1;
    t->arg2 = arg2;
    t->result = result;

    return t;
}
instruction* quad_to_instr(quad* q) {
    return make_instruction(q->op, make_operand(q->result),
                            make_operand(q->arg1), make_operand(q->arg2),
                            q->line);
}

void generate(vmopcode op, quad* q) {
    q->taddress = nextInstructionLabel();

    // instruction* t = quad_to_instr(op, q);
    instruction* t = quad_to_instr(q);

    emit_instr(t);

    return;
}

void generate_assign(quad* q) { generate(assign, q); }

void generate_add(quad* q) { generate(add, q); }
void generate_sub(quad* q) { generate(sub, q); }
void generate_mul(quad* q) { generate(mul, q); }
void generate_div(quad* q) { generate(Div, q); }
void generate_mod(quad* q) { generate(mod, q); }

void generate_uminus(quad* q) {
    q->taddress = nextInstructionLabel();

    instruction* t =
        make_instruction(mul, make_operand(q->result), make_operand(q->arg1),
                         make_num_operand(-1), q->line);

    emit_instr(t);

    return;
}

void generate_NOT(quad* q) { assert(0); }
void generate_and(quad* q) { assert(0); }
void generate_or(quad* q) { assert(0); }

void generate_relational(vmopcode op, quad* q) {
    q->taddress = nextInstructionLabel();

    // vmarg* res = NULL;

    // if (q->label < currprocessedquad) {
    //     unsigned val = quads[q->label - 1]
    //                          .taddress;  // TODO:CHECK INDEXING, SHOULD BE
    //                          GOOD
    //     res = make_label_operand(val);
    // } else {
    //     add_incomplete_jump(nextInstructionLabel(), q->label - 1);
    //     // res = make_label_operand(0);
    // }
    vmarg* res = make_label_operand(q->label);

    instruction* t = make_instruction(op, res, make_operand(q->arg1),
                                      make_operand(q->arg2), q->line);

    emit_instr(t);

    return;
}

void generate_jeq(quad* q) { generate_relational(jeq, q); }
void generate_jne(quad* q) { generate_relational(jne, q); }
void generate_jle(quad* q) { generate_relational(jle, q); }
void generate_jge(quad* q) { generate_relational(jge, q); }
void generate_jlt(quad* q) { generate_relational(jlt, q); }
void generate_jgt(quad* q) { generate_relational(jgt, q); }

// funcStack* funcStack_top = (funcStack*)0;

// void funcStack_push(SymTabEntry* func) {
//     assert(func);

//     funcStack* new_func = (funcStack*)malloc(sizeof(funcStack));

//     new_func->func = func;
//     new_func->next = funcStack_top;

//     funcStack_top = new_func;

//     return;
// }

// SymTabEntry* funcStack_pop() {
//     SymTabEntry* func = funcStack_top->func;
//     funcStack_top = funcStack_top->next;
//     return func;
// }

void generate_CALL(quad* q) {
    q->taddress = nextInstructionLabel();

    instruction* t =
        make_instruction(call, NULL, make_operand(q->arg1), NULL, q->line);

    emit_instr(t);
}

void generate_param(quad* q) {
    q->taddress = nextInstructionLabel();

    instruction* t =
        make_instruction(param, NULL, make_operand(q->arg1), NULL, q->line);

    emit_instr(t);
}

// generate_return(quad) {
//     quad.taddress = nextinstructionlabel();
//     instruction t;
//     t.opcode = assign;
//     make_retvaloperand(&t.result);
//     make_operand(quad.arg1, &t.arg1);
//     emit(t);

//     f = top(funcstack);
//     append(f.returnList, nextinstructionlabel());

//     t.opcode = jump;
//     reset_operand(&t.arg1);
//     reset_operand(&t.arg2);
//     t.result.type = label_a;
//     emit(t);
// }

void generate_return(quad* q) {
    q->taddress = nextInstructionLabel();

    instruction* t = make_instruction(assign, make_retval_operand(),
                                      make_operand(q->arg1), NULL, q->line);

    emit_instr(t);

    return;
}

void generate_getretval(quad* q) {
    q->taddress = nextInstructionLabel();

    instruction* t = make_instruction(assign, make_operand(q->result),
                                      make_retval_operand(), NULL, q->line);

    emit_instr(t);
}

void generate_funcstart(quad* q) {
    q->taddress = nextInstructionLabel();
    q->arg1->sym->value.funcVal->taddress = nextInstructionLabel();

    // userfuncs_newfunc(q->arg1->sym);

    instruction* t =
        make_instruction(funcstart, make_operand(q->arg1), NULL, NULL, q->line);

    emit_instr(t);
}

void generate_funcend(quad* q) {
    q->taddress = nextInstructionLabel();

    instruction* t =
        make_instruction(funcend, make_operand(q->arg1), NULL, NULL, q->line);

    emit_instr(t);

    return;
}

void generate_tablecreate(quad* q) { generate(tablecreate, q); }
void generate_tablegetelem(quad* q) { generate(tablegetelem, q); }
void generate_tablesetelem(quad* q) { generate(tablesetelem, q); }

void generate_jump(quad* q) { generate_relational(jump, q); }

void generate_nop() {
    quad* q = (quad*)malloc(sizeof(quad));
    memset(q, 0, sizeof(quad));
    generate(nop, q);
}

generator_func_t generators[] = {
    generate_assign,       generate_add,         generate_sub,
    generate_mul,          generate_div,         generate_mod,
    generate_uminus,       generate_and,         generate_or,
    generate_NOT,          generate_jeq,         generate_jne,
    generate_jle,          generate_jge,         generate_jlt,
    generate_jgt,          generate_CALL,        generate_param,
    generate_return,       generate_getretval,   generate_funcstart,
    generate_funcend,      generate_tablecreate, generate_tablegetelem,
    generate_tablesetelem, generate_jump,        generate_nop};

void generate_target_code() {
    for (unsigned i = 1; i < currQuad; i++) {
        currprocessedquad = i;
        (*generators[quads[i].op])(&quads[i]);
    }

    // patch_incomplete_jumps();
}

char* vmarg_content_string(vmarg* a) {
    vmarg_t type = a->type;
    char string[1024];

    sprintf(string, "%s ", vmarg_str[type]);
    sprintf(string + strlen(string), "(%d)", a->val);

    return strdup(string);
}

void print_instruction(instruction* instr, FILE* fp) {
    fprintf(fp, "%s", vmopcode_str[instr->opcode]);

    if (instr->result)
        fprintf(fp, ", res: %s", vmarg_content_string(instr->result));

    if (instr->arg1)
        fprintf(fp, ", arg1: %s", vmarg_content_string(instr->arg1));

    if (instr->arg2)
        fprintf(fp, ", arg2: %s", vmarg_content_string(instr->arg2));

    fprintf(fp, " [line %u]\n", instr->srcLine);
}
void print_instruction_idx(unsigned idx, FILE* fp) {
    assert(idx >= 1 && idx <= currInstr);
    print_instruction(instructions + idx, fp);
}
void print_instructions(FILE* fp) {
    if (!fp) fp = fopen("tcode.txt", "w");
    if (!fp) fp = stdout;

    for (unsigned i = 1; i < currInstr; ++i) {
        fprintf(fp, "%d: ", i);
        print_instruction_idx(i, fp);
    }
}

void print_constArrays(FILE* consts) {
    // Print numConsts
    fprintf(consts, "Number Constants:\n");
    for (unsigned i = 0; i < totalNumConsts; ++i) {
        fprintf(consts, "%f\n", numConsts[i]);
    }
    fprintf(consts, "\n");

    // Print stringConsts
    fprintf(consts, "String Constants:\n");
    for (unsigned i = 0; i < totalStringConsts; ++i) {
        fprintf(consts, "%s\n", stringConsts[i]);
    }
    fprintf(consts, "\n");

    // Print namedLibfuncs
    fprintf(consts, "Named Library Functions:\n");
    for (unsigned i = 0; i < totalNamedLibfuncs; ++i) {
        fprintf(consts, "%s\n", namedLibfuncs[i]);
    }
    fprintf(consts, "\n");

    // Print userFuncs
    fprintf(consts, "User Functions:\n");
    for (unsigned i = 0; i < totalUserfuncs; ++i) {
        fprintf(consts, "User Function Id: %s, Address: %d\n", userFuncs[i].id,
                userFuncs[i].address);
    }
    fprintf(consts, "\n");

    // // Print boolConsts
    // fprintf(consts, "Boolean Constants:\n");
    // for (unsigned i = 0; i < totalBoolConsts; ++i) {
    //     fprintf(consts, "%u\n", boolConsts[i]);
    // }
    fprintf(consts, "\n");
}

extern unsigned programVarOffset;

void createbin(void) {
    unsigned magic = 340;
    unsigned long str_len;
    FILE* bytefile = fopen("alpha.out", "w");
    ;
    size_t i;

    // magic number
    fwrite(&magic, sizeof(unsigned), 1, bytefile);

    // global offset
    fwrite(&programVarOffset, sizeof(unsigned), 1, bytefile);

    // numerical consts
    unsigned numConstsSize = totalNumConsts;
    fwrite(&numConstsSize, sizeof(unsigned), 1, bytefile);
    for (i = 0; i < numConstsSize; i++) {
        fwrite(&numConsts[i], sizeof(double), 1, bytefile);
    }

    // string consts
    unsigned strConstsSize = totalStringConsts;
    fwrite(&strConstsSize, sizeof(unsigned), 1, bytefile);
    for (i = 0; i < strConstsSize; i++) {
        str_len = strlen(stringConsts[i]);
        fwrite(&str_len, sizeof(unsigned long), 1, bytefile);
        fwrite(strdup(stringConsts[i]), sizeof(char), str_len + 1, bytefile);
    }

    // // bool consts
    // unsigned boolConstsSize = totalBoolConsts;
    // fwrite(&boolConstsSize, sizeof(unsigned), 1, bytefile);
    // for (i = 0; i < boolConstsSize; i++) {
    //     unsigned boolAsInt = boolConsts[i] ? 1 : 0;
    //     fwrite(&boolAsInt, sizeof(unsigned), 1, bytefile);
    // }

    // Library functions
    unsigned libFuncsSize = totalNamedLibfuncs;
    fwrite(&libFuncsSize, sizeof(unsigned), 1, bytefile);
    for (i = 0; i < libFuncsSize; i++) {
        str_len = strlen(namedLibfuncs[i]);
        fwrite(&str_len, sizeof(unsigned long), 1, bytefile);
        fwrite(strdup(namedLibfuncs[i]), sizeof(char), str_len + 1, bytefile);
    }

    // User functions
    unsigned usrFuncsSize = totalUserfuncs;
    fwrite(&usrFuncsSize, sizeof(unsigned), 1, bytefile);
    for (i = 0; i < usrFuncsSize; i++) {
        fwrite(&userFuncs[i].address, sizeof(unsigned), 1, bytefile);
        fwrite(&userFuncs[i].localSize, sizeof(unsigned), 1, bytefile);

        str_len = strlen(userFuncs[i].id);
        fwrite(&str_len, sizeof(unsigned long), 1, bytefile);
        fwrite(strdup(userFuncs[i].id), sizeof(char), str_len + 1, bytefile);
    }

    // instructions
    unsigned instrSize = totalInstr;
    fwrite(&instrSize, sizeof(unsigned), 1, bytefile);
    for (i = 1; i < instrSize; i++) {
        fwrite(&(instructions[i].opcode), sizeof(vmopcode), 1, bytefile);
        // result
        unsigned isResultNull =
            !instructions[i].result;  // all commands have a res
        fwrite(&isResultNull, sizeof(unsigned), 1, bytefile);

        if (!isResultNull) {
            fwrite(&(instructions[i].result->type), sizeof(vmarg_t), 1,
                   bytefile);
            fwrite(&(instructions[i].result->val), sizeof(unsigned), 1,
                   bytefile);
        }

        unsigned isArg1Null = !instructions[i].arg1;
        fwrite(&isArg1Null, sizeof(unsigned), 1, bytefile);
        if (!isArg1Null) {
            fwrite(&(instructions[i].arg1->type), sizeof(vmarg_t), 1, bytefile);
            fwrite(&(instructions[i].arg1->val), sizeof(unsigned), 1, bytefile);
        }

        unsigned isArg2Null = !instructions[i].arg2;
        fwrite(&isArg2Null, sizeof(unsigned), 1, bytefile);
        if (!isArg2Null) {
            fwrite(&(instructions[i].arg2->type), sizeof(vmarg_t), 1, bytefile);
            fwrite(&(instructions[i].arg2->val), sizeof(unsigned), 1, bytefile);
        }

        fwrite(&(instructions[i].srcLine), sizeof(unsigned), 1, bytefile);
    }

    fclose(bytefile);
}
