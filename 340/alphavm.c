#include "alphavm.h"

extern FILE *out;

// Stack
#define AVM_ENDING_PC currInstr
avm_memcell stack[AVM_STACKSIZE];
// Stack pointers
unsigned top, topsp;

// Registers
avm_memcell ax, bx, cx;
avm_memcell retval;

instruction *code = (instruction *)0;
extern instruction *instructions;

unsigned char executionFinished = 0;
unsigned pc = 0;
unsigned currLine = 0;
unsigned codeSize = 0;
unsigned totalActuals = 0;
extern unsigned currInstr;

extern const char *vmopcode_str[];

const char *typeStrings[] = {"number",   "string",  "bool", "table",
                             "userfunc", "libfunc", "nil",  "undef"};

// extern int search_array();

// Constant Tables
extern double *numConsts;
extern unsigned totalNumConsts;

// extern unsigned *boolConsts;
// extern unsigned totalBoolConsts;

extern char **stringConsts;
extern unsigned totalStringConsts;

extern const char *namedLibfuncs[];
extern const unsigned totalNamedLibfuncs;

extern userfunc_t *userFuncs;
extern unsigned totalUserfuncs;

void *avm_error(char *msg, ...) {
    fprintf(stderr, "\033[1;31merror\033[0m ");
    fprintf(stderr, "at line %u: ", code[pc].srcLine);

    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    fprintf(stderr, "\n");
    executionFinished = 1;
    // fclose(out);
    return NULL;
}

void avm_warning(char *msg, ...) {
    fprintf(stderr, "\033[1;35mwarning\033[0m ");
    fprintf(stderr, "at line %u: ", code[pc].srcLine);
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    fprintf(stderr, "\n");
    return;
}

void index_not_found_warning(avm_memcell *t, avm_memcell *i) {
    char *ts = table_tostring(t);
    // char *ts = avm_tostring(t);
    char *is = avm_tostring(i);
    avm_warning("(%s)[%s] not found!", ts, is);
    free(ts);
    free(is);
}

int is_0(char *s) {
    int dec = 0;
    for (int i = 0; s[i]; ++i) {
        if (s[i] == '.') {
            if (dec) return 0;
            dec = 1;
        }
        if (s[i] != '0' && s[i] != '.') return 0;
    }
    return 1;
}

int hash_sizes[] = {AVM_TABLE_HASHSIZE, AVM_TABLE_HASHSIZE, 2,
                    AVM_TABLE_HASHSIZE, AVM_TABLE_HASHSIZE, 12};

unsigned hash_i(int i) { return ((HASH << 5) + HASH) + i; }
unsigned hash_num(double d) { return hash_i((int)d) % AVM_TABLE_HASHSIZE; }
unsigned hash_str(unsigned char *str) {
    unsigned hash = HASH;
    int c;

    while (c = *str++) hash = hash_i(hash) + c;

    return hash % AVM_TABLE_HASHSIZE;
}

char *number_tostring(avm_memcell *m) {
    assert(m && m->type == number_m);
    // fprintf(stdout, "!%f!\n", m->data.numVal);
    char *s = (char *)malloc(100 * sizeof(char));
    sprintf(s, "%.3f", m->data.numVal);
    return s;
}
char *string_tostring(avm_memcell *m) {
    assert(m && m->type == string_m);
    return strdup(m->data.strVal);
}
char *bool_tostring(avm_memcell *m) {
    assert(m && m->type == bool_m);
    return m->data.boolVal ? strdup("true") : strdup("false");
}
char *table_tostring(avm_memcell *m) {
    assert(m && m->type == table_m);
    char *s = (char *)malloc(100 * sizeof(char));
    sprintf(s, "table (%p)", m->data.tableVal);
    return s;
}

int avmtable_apply(avm_table *t,
                   avm_memcell *(*func)(avm_memcell *, avm_memcell *)) {
    int n = 0;

    for (int i = 0; i < INDEXED_TYPES; i++) {
        avm_table_bucket **type_indices = t->indices[i];
        if (!type_indices) continue;
        for (int j = 0; j < hash_sizes[i]; j++) {
            avm_table_bucket *b = type_indices[j];
            while (b) {
                func(b->key, b->value);
                n++;
                b = b->next;
            }
        }
    }

    return n;
}
char *table_content_tostring(avm_memcell *m) {
    assert(m && m->type == table_m);

    char *s = (char *)malloc(100 * sizeof(char));
    // sprintf(s, "table (%p) [", m->data.tableVal);
    sprintf(s, "[ ");
    avm_table *t = m->data.tableVal;
    avm_memcell *print_pair(avm_memcell * k, avm_memcell * v) {
        char *ks = avm_tostring(k);
        char *vs = avm_tostring(v);
        // sprintf(s, "%s%s\t: ", strdup(s), ks);
        sprintf(s, "%s%s, ", strdup(s), vs);
        free(ks);
        free(vs);
        return k;
    }

    if (!avmtable_apply(t, print_pair))
        sprintf(s, "%s]", s);
    else
        sprintf(s, "%s\b\b ]", s);
    return s;
}

char *userfunc_tostring(avm_memcell *m) {
    assert(m && m->type == userfunc_m);
    // return strdup(userFuncs[m->data.funcVal].id);
    char *s = (char *)malloc(100 * sizeof(char));
    sprintf(s, "userfunc %s", userFuncs[m->data.funcVal].id);
    return s;
}
unsigned libfunc_idx_outofbounds(unsigned idx) {
    return idx == -1 || idx >= totalNamedLibfuncs;
}
char *libfunc_tostring(avm_memcell *m) {
    assert(m && m->type == libfunc_m);
    // return m->data.libfuncVal;
    char *s = (char *)malloc(100 * sizeof(char));
    // sprintf(s, "libfunc %s", m->data.libfuncVal);
    if (libfunc_idx_outofbounds(m->data.libfuncVal)) {
        sprintf(s, "libfunc (invalid)");
        return s;
    }
    sprintf(s, "libfunc %s", namedLibfuncs[m->data.libfuncVal]);
    return s;
}
char *nil_tostring(avm_memcell *m) {
    assert(m && m->type == nil_m);
    return strdup("nil");
}
char *undef_tostring(avm_memcell *m) {
    // assert(0);
    assert(m && m->type == undef_m);
    return strdup("(undefined)");
}

tostring_func_t tostringFuncs[] = {
    number_tostring,   string_tostring,  bool_tostring, table_content_tostring,
    userfunc_tostring, libfunc_tostring, nil_tostring,  undef_tostring};

char *avm_tostring(avm_memcell *m) {  // Caller frees;
    assert(m->type >= 0 && m->type <= undef_m);
    // fprintf(stdout, "TYPE:%d\n", m->type);
    return (*tostringFuncs[m->type])(m);
}

double consts_getnumber(unsigned index) {
    assert(index >= 0 && index < totalNumConsts);
    return numConsts[index];
}
char *consts_getstring(unsigned index) {
    assert(index >= 0 && index < totalStringConsts);
    return stringConsts[index];
}
char *libfuncs_getused(unsigned index) {
    assert(index >= 0 && index < totalNamedLibfuncs);
    return strdup(namedLibfuncs[index]);
}
// userfunc_t *userfuncs_getfunc(unsigned index) {
//     assert(index >= 0 && index < totalUserfuncs);
//     return &userFuncs[index];
// }
userfunc_t *userfuncs_getfunc(unsigned id) {
    // fprintf(stdout, "SEARCHING FOR USERFUNCTION WITH id: %d\n", id);
    assert(id < totalUserfuncs);

    return &userFuncs[id];
}
userfunc_t *avm_getfuncinfo(unsigned address) {
    assert(address < totalUserfuncs);
    return &userFuncs[address];
}

avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg) {
    fprintf(stdout, "TRANSLATING OPERAND:\n");
    if (!arg) avm_error("null arg");
    assert(arg);
    switch (arg->type) {
        case global_a:
            printf("GLOBAL %d\n", arg->val);
            return (&stack[AVM_STACKSIZE - 1 - arg->val]);
        case local_a:
            printf("LOCAL %d\n", arg->val);
            return (&stack[topsp - arg->val]);
        case formal_a:
            printf("FORMAL %d\n", arg->val);
            return (&stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val]);
        case retval_a:
            printf("RETVAL\n");
            return (&retval);
        case number_a:
            printf("NUMBER %d\n", arg->val);
            reg->type = number_m;
            reg->data.numVal = consts_getnumber(arg->val);
            return reg;
        case string_a:
            printf("STRING %d\n", arg->val);
            reg->type = string_m;
            reg->data.strVal = strdup(consts_getstring(arg->val));
            return reg;
        case bool_a:
            printf("BOOL %d\n", arg->val);
            reg->type = bool_m;
            // reg->data.boolVal = consts_getbool(arg->val);
            reg->data.boolVal = arg->val;
            return reg;
        case nil_a:
            printf("NIL\n");
            reg->type = nil_m;
            return reg;
        case userfunc_a:
            reg->type = userfunc_m;
            // reg->data.funcVal = userfuncs_getfunc(arg->val)->address;
            reg->data.funcVal = arg->val;
            return reg;
        case libfunc_a:
            reg->type = libfunc_m;
            // reg->data.libfuncVal = libfuncs_getused(arg->val);
            reg->data.libfuncVal = arg->val;
            return reg;
        // case label_a :
        default:
            assert(0);
    }
    return reg;
}

void return_nil() {
    avm_memcellclear(&retval);
    retval.type = nil_m;
}

void avm_initstack() {
    for (unsigned i = 0; i < AVM_STACKSIZE; i++) {
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }
}

void avm_dec_top() {
    if (!top) {
        avm_error("stack overflow");
    } else
        --top;
}

void avm_push_envvalue(unsigned val) {
    stack[top].type = number_m;
    stack[top].data.numVal = val;
    avm_dec_top();
}

void avm_callSaveEnv() {
    avm_push_envvalue(totalActuals);
    avm_push_envvalue(pc + 1);
    avm_push_envvalue(top + totalActuals + 2);
    avm_push_envvalue(topsp);
}

unsigned avm_get_envvalue(unsigned i) {
    if (stack[i].type != number_m) {
        // fprintf(stdout, "STACK[i] TYPE %d\n", stack[i].type);
        avm_error("stack i not number");
    }
    if (stack[i].type > number_m) avm_error("stack overflow");
    assert(stack[i].type == number_m);

    // assert(stack[i].type == number_m);
    unsigned val = (unsigned)stack[i].data.numVal;
    assert(stack[i].data.numVal == (double)val);
    return val;
}

unsigned avm_totalactuals() {
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell *avm_getactual(unsigned i) {
    // assert(i < avm_totalactuals());
    // fprintf(stdout, "GETING ACTUAL %d\n", topsp + AVM_STACKENV_SIZE + 1 + i);
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

void memclear_string(avm_memcell *m) {
    assert(m->data.strVal);
    free(m->data.strVal);
}
void memclear_table(avm_memcell *m) {
    assert(m->data.tableVal);
    avm_tabledecrefcounter(m->data.tableVal);
}
void empty_func(avm_memcell *m) { return; }

memclear_func_t memclearFuncs[] = {
    empty_func,       // number
    memclear_string,  // string
    empty_func,       // bool
    memclear_table,   // table
    empty_func,       // userfunc
    empty_func,       // libfunc
    empty_func,       // nil
    empty_func        // undef
};

void avm_memcellclear(avm_memcell *m) {
    return;
    printf("memcell clearing a memcell of memcell type %d\n", m->type);

    (*memclearFuncs[m->type])(m);
    m->type = undef_m;

    printf("clear\n");
}

/* EXECUTE FUNCS*/
execute_func_t executeFuncs[] = {
    execute_assign,       execute_add,         execute_sub,
    execute_mul,          execute_div,         execute_mod,
    execute_uminus,       execute_not,         execute_and,
    execute_or,           execute_jeq,         execute_jne,
    execute_jle,          execute_jge,         execute_jlt,
    execute_jgt,          execute_call,        execute_param,
    execute_ret,          execute_getretval,   execute_funcstart,
    execute_funcend,      execute_tablecreate, execute_tablegetelem,
    execute_tablesetelem, execute_jump,        execute_nop};

void avm_assign(avm_memcell *lv, avm_memcell *rv) {
    printf("ASSIGNING %d %d\n", lv->type, rv->type);
    if (lv == rv) return;

    if (lv->type == table_m && rv->type == table_m &&
        lv->data.tableVal == rv->data.tableVal)
        return;

    if (rv->type == undef_m) avm_warning("assigning from undefined content");

    if (lv) avm_memcellclear(lv);

    memcpy(lv, rv, sizeof(avm_memcell));

    if (lv->type == string_m)
        lv->data.strVal = strdup(rv->data.strVal);
    else if (lv->type == table_m)
        avm_tableincrefcounter(lv->data.tableVal);

    printf("ASSIGNED %d %d\n", lv->type, rv->type);
}

void execute_assign(instruction *instr) {
    avm_memcell *lv = avm_translate_operand(instr->result, NULL);

    if (lv == &retval && ((int)!instr->arg1)) {
        avm_memcellclear(lv);
        lv->type = nil_m;
        return;
    }
    avm_memcell *rv = avm_translate_operand(instr->arg1, &ax);

    // assert(lv && (&stack[N-1] >= lv && lv > &stack[top] || lv == &retval));
    assert(rv);  // should do similar assertion tests here

    avm_assign(lv, rv);
}

/* ARITHMETIC */
double add_impl(double x, double y) { return x + y; }
double sub_impl(double x, double y) { return x - y; }
double mul_impl(double x, double y) { return x * y; }
double div_impl(double x, double y) {
    if (y == 0) {
        // avm_error("div by 0");
        avm_warning("div by 0");
        return 0;
    }
    return x / y;
}
double mod_impl(double x, double y) {
    if (y == 0) {
        // avm_error("mod by 0");
        avm_warning("mod by 0");
        return 0;
    }
    return ((unsigned)x) % ((unsigned)y);
}

arithmetic_func_t arithmeticFuncs[] = {add_impl, sub_impl, mul_impl, div_impl,
                                       mod_impl};

void execute_arithmetic(instruction *instr) {
    avm_memcell *lv = avm_translate_operand(instr->result, (avm_memcell *)0);
    avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);

    // TODO: Runtime error checks?
    // assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] ||
    //               lv == &retval));
    assert(rv1 && rv2);

    if (rv1->type != number_m || rv2->type != number_m) {
        avm_error("not a number in arithmetic!");
        return;
    }

    arithmetic_func_t op = arithmeticFuncs[instr->opcode - add];
    avm_memcellclear(lv);
    lv->type = number_m;
    lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
}

/* UNUSED */
void execute_uminus(instruction *instr) { assert(0); }
void execute_not(instruction *instr) { assert(0); }
void execute_and(instruction *instr) { assert(0); }
void execute_or(instruction *instr) { assert(0); }

/* COMPARISONS */
unsigned char number_tobool(avm_memcell *m) { return m->data.numVal != 0; }
unsigned char string_tobool(avm_memcell *m) { return m->data.strVal[0] != 0; }
unsigned char bool_tobool(avm_memcell *m) { return m->data.boolVal; }
unsigned char table_tobool(avm_memcell *m) { return 1; }
unsigned char userfunc_tobool(avm_memcell *m) { return 1; }
unsigned char libfunc_tobool(avm_memcell *m) { return 1; }
unsigned char nil_tobool(avm_memcell *m) { return 0; }
unsigned char undef_tobool(avm_memcell *m) {
    // assert(0);
    return 0;
}

tobool_func_t toboolFuncs[] = {number_tobool, string_tobool,   bool_tobool,
                               table_tobool,  userfunc_tobool, libfunc_tobool,
                               nil_tobool,    undef_tobool};

unsigned char avm_tobool(avm_memcell *m) {
    assert(m->type >= 0 && m->type < undef_m);
    return (*toboolFuncs[m->type])(m);
}

unsigned char number_eq(avm_memcell *rv1, avm_memcell *rv2) {
    printf("NUMBER_EQ: %f %f\n", rv1->data.numVal, rv2->data.numVal);
    return rv1->data.numVal == rv2->data.numVal;
}
unsigned char string_eq(avm_memcell *rv1, avm_memcell *rv2) {
    return !strcmp(rv1->data.strVal, rv2->data.strVal);
}
unsigned char bool_eq(avm_memcell *rv1, avm_memcell *rv2) {
    return rv1->data.boolVal == rv2->data.boolVal;
}
unsigned char table_eq(avm_memcell *rv1, avm_memcell *rv2) {
    return rv1->data.tableVal == rv2->data.tableVal;
}
unsigned char userfunc_eq(avm_memcell *rv1, avm_memcell *rv2) {
    return rv1->data.funcVal == rv2->data.funcVal;
}
unsigned char libfunc_eq(avm_memcell *rv1, avm_memcell *rv2) {
    // return !strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal);
    unsigned idx1 = rv1->data.libfuncVal;
    unsigned idx2 = rv2->data.libfuncVal;
    printf("LIBFUNC_EQ: %d %d\n", idx1, idx2);
    if (libfunc_idx_outofbounds(idx1) || libfunc_idx_outofbounds(idx2))
        return 0;
    return idx1 == idx2;
}
unsigned char nil_eq(avm_memcell *rv1, avm_memcell *rv2) {
    assert(0);
    return 0;
}
unsigned char undef_eq(avm_memcell *rv1, avm_memcell *rv2) {
    assert(0);
    return 0;
}

eq_func_t eqFuncs[] = {number_eq,   string_eq,  bool_eq, table_eq,
                       userfunc_eq, libfunc_eq, nil_eq,  undef_eq};

unsigned char are_equal(avm_memcell *rv1, avm_memcell *rv2) {
    assert(rv1->type == rv2->type);
    printf("ARE_EQUAL %d %d\n", rv1->type, rv2->type);
    return (*eqFuncs[rv1->type])(rv1, rv2);
}

unsigned char check_equality(avm_memcell *rv1, avm_memcell *rv2) {
    if (rv1->type == undef_m || rv2->type == undef_m) {
        avm_error("'undef' involved in comparison");
        return 'e';
    } else if (rv1->type == bool_m || rv2->type == bool_m)
        return (avm_tobool(rv1) == avm_tobool(rv2));
    else if (rv1->type == nil_m || rv2->type == nil_m)
        return (rv1->type == nil_m) && (rv2->type == nil_m);
    else if (rv1->type != rv2->type) {
        avm_error("%s == %s is illegal!", typeStrings[rv1->type],
                  typeStrings[rv2->type]);
        return 'e';
    }

    return are_equal(rv1, rv2);
}

void execute_jeq(instruction *instr) {
    assert(instr->result->type == label_a);

    avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);

    unsigned char result = check_equality(rv1, rv2);
    if (result == 'e') return;
    if (!executionFinished && result) pc = instr->result->val;
}

void execute_jne(instruction *instr) {
    assert(instr->result->type == label_a);

    avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);

    unsigned char result = check_equality(rv1, rv2);
    if (result == 'e') return;
    if (!executionFinished && !result) pc = instr->result->val;
}

unsigned char jle_impl(double x, double y) { return x <= y; }
unsigned char jge_impl(double x, double y) { return x >= y; }
unsigned char jlt_impl(double x, double y) { return x < y; }
unsigned char jgt_impl(double x, double y) { return x > y; }

comp_func_t comparisonFuncs[] = {jle_impl, jge_impl, jlt_impl, jgt_impl};

void execute_comparison(instruction *instr) {
    avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);

    assert(rv1 && rv2);

    if (rv1->type != number_m || rv2->type != number_m) {
        avm_error("not a number in comparison!");
        return;
    }

    comp_func_t op = comparisonFuncs[instr->opcode - jle];
    printf("comparison: %s\n", vmopcode_str[instr->opcode]);
    unsigned char result = (*op)(rv1->data.numVal, rv2->data.numVal);
    if (!executionFinished && result) pc = instr->result->val;
}

/* FUNCTIONS */
libraryfunc_t libfuncs[] = {libfunc_print,
                            libfunc_input,
                            libfunc_objectmemberkeys,
                            libfunc_objecttotalmembers,
                            libfunc_objectcopy,
                            libfunc_totalarguments,
                            libfunc_argument,
                            libfunc_typeof,
                            libfunc_strtonum,
                            libfunc_sqrt,
                            libfunc_cos,
                            libfunc_sin};

libraryfunc_t avm_getlibraryfunc(char *id) {
    int idx = libfuncs_getindex(id);

    if (idx == -1) return NULL;

    return libfuncs[idx];
}

void call_libfunc(libraryfunc_t f) {
    avm_callSaveEnv();

    topsp = top;
    totalActuals = 0;

    (*f)();
    if (!executionFinished) execute_funcend((instruction *)0);
}
void avm_callLibFunc_idx(unsigned idx) {
    if (idx < 0 || idx >= totalNamedLibfuncs) {
        avm_error("unsupported lib func called");
        return;
    }

    libraryfunc_t f = libfuncs[idx];
    call_libfunc(f);
}

void avm_callLibFunc_name(char *id) {
    libraryfunc_t f = avm_getlibraryfunc(id);

    if (!f) {
        avm_error("unsupported lib func '%s' called", id);
        return;
    }

    call_libfunc(f);
}

void call_ufunc(avm_memcell *func) {
    avm_callSaveEnv();
    //     pc = func->address;
    pc = userfuncs_getfunc(func->data.funcVal)->address + 1;
    // assert(pc < AVM_ENDING_PC && code[pc].opcode == funcstart);
}

void call_func(avm_memcell *func) {
    assert(func);
    // avm_callSaveEnv();
    switch (func->type) {
        case userfunc_m:
            // pc = userfuncs_getfunc(func->data.funcVal)->address + 1;
            call_ufunc(func);
            return;
        case string_m:
            avm_callLibFunc_name(func->data.strVal);
            return;
        case libfunc_m:
            avm_callLibFunc_idx(func->data.libfuncVal);
            return;
        case table_m:
            avm_call_functor(func);
            return;
    }

    char *s = avm_tostring(func);
    avm_error("call: cannot bind '%s' to function", s);
    free(s);
}

void execute_call(instruction *instr) {
    avm_memcell *func = avm_translate_operand(instr->arg1, &ax);
    call_func(func);
}

void avm_call_functor(avm_memcell *t) {
    avm_table *table = t->data.tableVal;
    cx.type = string_m;
    cx.data.strVal = "()";

    avm_memcell *f = avm_tablegetelem(table, &cx);
    if (!f) {
        avm_error("in calling table: no '()' element found!");
        return;
    }

    if (f->type == table_m)
        avm_call_functor(f);
    else {
        avm_push_table_arg(t);
        call_func(f);
    }
}

void execute_param(instruction *instr) {
    avm_memcell *arg = avm_translate_operand(instr->arg1, &ax);
    printf("param type %d stack top %d\n", arg->type, top);
    assert(arg);

    // fprintf(stdout, "ASSIGNING TO STACK TOP %d\n", top);
    avm_assign(&stack[top], arg);
    ++totalActuals;
    avm_dec_top();
}

void execute_ret(instruction *instr) { assert(0); }
void execute_getretval(instruction *instr) { assert(0); }

void execute_funcstart(instruction *instr) {
    avm_memcell *func = avm_translate_operand(instr->result, &ax);
    assert(func);
    // assert(pc == func->data.funcVal + 1); /* func address should match PC */
    assert(pc == userFuncs[func->data.funcVal].address + 1);

    // TODO: avm_infunc++;
    unsigned localSize = userFuncs[func->data.funcVal].localSize;

    /* Callee actions here. */
    totalActuals = 0;
    // userfunc_t *funcInfo = avm_getfuncinfo(pc);
    topsp = top;
    // top = top - funcInfo->localSize;
    top = top - localSize;
}

void execute_funcend(instruction *instr) {
    unsigned oldTop = top;

    top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    // fprintf(stdout, "GOTENVVALUE1\n");

    pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    // fprintf(stdout, "GOTENVVALUE2\n");
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    // fprintf(stdout, "GOTENVVALUE3\n");

    // while (++oldTop <= top) avm_memcellclear(&stack[oldTop]);
    while (++oldTop < top) avm_memcellclear(&stack[oldTop]);

    // TODO: avm_infunc--;
}

/* TABLES */

void avm_push_table_arg(avm_memcell *t) {
    stack[top].type = table_m;
    avm_assign(&stack[top], t);
    printf("PUSHING TABLE ARGUMENT top %d\n", top);
    // avm_tableincrefcounter(stack[top].data.tableVal = t);
    ++totalActuals;
    avm_dec_top();
}
// void avm_push_table_arg(avm_table *t) {
//     stack[top].type = table_m;
//     avm_assign(&stack[top], &retval);
//     // avm_tableincrefcounter(stack[top].data.tableVal = t);
//     ++totalActuals;
//     avm_dec_top();
// }

void avm_tableincrefcounter(avm_table *t) { ++t->refCounter; }
void avm_tabledecrefcounter(avm_table *t) {
    assert(t->refCounter > 0);
    if (!--t->refCounter) avm_tabledestroy(t);
}
avm_table_bucket **avm_tablebucketsinit_s(unsigned size) {
    avm_table_bucket **p =
        (avm_table_bucket **)malloc(size * sizeof(avm_table_bucket *));
    memset(p, 0, size * sizeof(avm_table_bucket *));

    // for (unsigned i = 0; i < size; i++) p[i] = (avm_table_bucket *)0;
    return p;
}
// void avm_tablebucketsinit(avm_table_bucket **p) {
//     avm_tablebucketsinit_s(p, AVM_TABLE_HASHSIZE);
// }

avm_table *avm_tablenew() {
    avm_table *t = (avm_table *)malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);

    t->indices =
        // (avm_table_bucket **)malloc(type_indicesS *
        // sizeof(avm_table_bucket*));
        (avm_table_bucket ***)malloc((libfunc_m + 1) *
                                     sizeof(avm_table_bucket **));
    memset(t->indices, 0, (libfunc_m + 1) * sizeof(avm_table_bucket **));
    t->refCounter = t->total = 0;

    // for (int i = 0; i < libfunc_m + 1; i++) {
    //     avm_tablebucketsinit_s(t->indices[i], hash_sizes[i]);
    // }

    return t;
}
void avm_tablebuckets_destroy_s(avm_table_bucket **p, unsigned size) {
    for (unsigned i = 0; i < size; i++) {
        if (!p[i]) continue;
        for (avm_table_bucket *b = *p; b;) {
            avm_table_bucket *del = b;
            b = b->next;
            printf("DESTROYING TABLE BUCKET\n");
            // avm_memcellclear(&del->key);
            // avm_memcellclear(&del->value);
            // free(del);
            printf("DESTROYING TABLE BUCKET\n");
        }
        // p[i] = (avm_table_bucket *)0;
        free(p[i]);
    }
    free(p);
}

void avm_tablebuckets_destroy(avm_table_bucket **p) {
    avm_tablebuckets_destroy_s(p, AVM_TABLE_HASHSIZE);
}

void avm_tabledestroy(avm_table *t) {
    printf("DESTROYING TABLE >:(\n");

    // for (int i = 0; i < libfunc_m + 1; i++) {
    //     if (!t->indices[i]) continue;
    //     avm_tablebuckets_destroy_s(t->indices[i], hash_sizes[i]);
    // }

    free(t);
    printf("DESTROYED TABLE :))\n");
}

void execute_tablecreate(instruction *instr) {
    printf("EXECUTING tablecreate :P\n");
    avm_memcell *lv = avm_translate_operand(instr->result, (avm_memcell *)0);
    assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] ||
                  lv == &retval));

    printf("memcell clearing *-\n");
    if (lv) avm_memcellclear(lv);
    printf("cleared!!! :P\n");

    lv->type = table_m;
    lv->data.tableVal = avm_tablenew();
    avm_tableincrefcounter(lv->data.tableVal);
}

unsigned hash_number(avm_memcell *m) { return hash_num(m->data.numVal); }
unsigned hash_string(avm_memcell *m) { return hash_str(m->data.strVal); }
unsigned hash_bool(avm_memcell *m) { return m->data.boolVal; }
unsigned hash_table(avm_memcell *m) {
    return hash_num((unsigned long)m->data.tableVal);
}
unsigned hash_ufunc(avm_memcell *m) { return hash_num(m->data.funcVal); }
unsigned hash_libfunc(avm_memcell *m) {
    // return hash_str((unsigned char *)m->data.libfuncVal);
    return m->data.libfuncVal;
}
unsigned hash_nil(avm_memcell *m) { return 0; }
unsigned hash_undef(avm_memcell *m) { avm_error("'undef' table index type"); }

unsigned (*hash_funcs[])(avm_memcell *) = {
    hash_number, hash_string,  hash_bool, hash_table,
    hash_ufunc,  hash_libfunc, hash_nil,  hash_undef};

unsigned hash(avm_memcell *m) {
    assert(m->type >= 0 && m->type <= undef_m);
    return (*hash_funcs[m->type])(m);
}

int check_table_index(avm_memcell *index) {
    if (index->type == nil_m) {
        avm_error("Illegal use of type nil as table index! ");
        return 0;
    }
    if (index->type == undef_m) {
        avm_error("Illegal use of type undef as table index! ");
        return 0;
    }
    // printf(" tt");
    return 1;
}

avm_table_bucket *search_indices(avm_table_bucket **type_indices,
                                 avm_memcell *index) {
    printf("SEARCHING indices!! type %d\n", index->type);
    // assert(indices && index);
    if (!check_table_index(index)) return (avm_table_bucket *)0;

    avm_table_bucket *b = type_indices[hash(index)];

    for (; b; b = b->next) {
        printf("types %d %d\n", b->key->type, index->type);
        if (are_equal(b->key, index)) {
            return b;
        }
    }
    printf("not found :(\n");

    return (avm_table_bucket *)0;
}
avm_memcell *search_indices_value(avm_table_bucket **type_indices,
                                  avm_memcell *index) {
    printf("SEARCHING indices val ;)\n");
    avm_table_bucket *b = search_indices(type_indices, index);
    if (b) return b->value;
    return (avm_memcell *)0;
}

avm_memcell *avm_tablegetelem(avm_table *table, avm_memcell *index) {
    assert(table && index);
    printf("GETTING TABLE ELEM!!!\n");
    avm_table_bucket **type_indices = table->indices[index->type];
    avm_memcell *res = search_indices_value(type_indices, index);
    return res;
}

void execute_tablegetelem(instruction *instr) {
    avm_memcell *lv = avm_translate_operand(instr->result, (avm_memcell *)0);
    avm_memcell *t = avm_translate_operand(instr->arg1, (avm_memcell *)0);
    avm_memcell *i = avm_translate_operand(instr->arg2, &ax);

    assert(lv && &stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] ||
           lv == &retval);
    assert(t && &stack[AVM_STACKSIZE - 1] >= t && t > &stack[top]);
    assert(i);

    if (t->type != table_m) {
        avm_error("Illegal use of type %s as table! ", typeStrings[t->type]);
        return return_nil();
    }

    avm_memcell *content = avm_tablegetelem(t->data.tableVal, i);
    if (content) {
        avm_assign(lv, content);
    } else {
        index_not_found_warning(t, i);
        return_nil();
        avm_assign(lv, &retval);
    }
}

void table_remove(avm_table *table, avm_memcell *index) {
    // assert(table && index);
    if (!check_table_index(index)) return;

    unsigned i = hash(index);
    avm_table_bucket *p = (avm_table_bucket *)0;
    avm_table_bucket *b = table->indices[index->type][i];

    for (; b; p = b, b = b->next) {
        if (are_equal(b->key, index)) {
            if (p)
                p->next = b->next;
            else
                table->indices[index->type][i] = b->next;

            avm_memcellclear(b->key);
            avm_memcellclear(b->value);
            free(b);
            --table->total;
            return;
        }
    }
    // index_not_found_warning(table, index);
}
avm_table_bucket **indices_add_entry(avm_table_bucket **type_indices,
                                     avm_memcell *key, avm_memcell *value) {
    printf("ADDING ENTRY TO INDICES\n");
    avm_table_bucket *b = (avm_table_bucket *)malloc(sizeof(avm_table_bucket));
    b->key = (avm_memcell *)malloc(sizeof(avm_memcell));
    b->value = (avm_memcell *)malloc(sizeof(avm_memcell));
    avm_assign(b->key, key);
    avm_assign(b->value, value);

    unsigned i = hash(key);
    b->next = type_indices[i];
    type_indices[i] = b;
    return type_indices;
}

void avm_tablesetelem(avm_table *table, avm_memcell *key, avm_memcell *value) {
    assert(table && key);
    printf("SETTING TABLE ELEM\t\tt\n");
    if (!check_table_index(key)) return;

    if (value->type == table_m && value->data.tableVal == table) {
        avm_error("self reference in table assignment");
        return;
    }

    avm_table_bucket **type_indices = table->indices[key->type];
    avm_table_bucket *b;
    if (!type_indices) {
        printf("creating type indices for type %d\n", key->type);
        type_indices = avm_tablebucketsinit_s(hash_sizes[key->type]);
        table->indices[key->type] = type_indices;
    } else if (value->type == nil_m) {
        table_remove(table, key);
        return;
    } else if (value->type == undef_m) {
        avm_error("illegal use of type undef as table value");
        return;
    } else if (b = search_indices(type_indices, key)) {
        avm_assign(b->value, value);
        return;
    }

    type_indices = indices_add_entry(type_indices, key, value);
    ++table->total;
}

void execute_tablesetelem(instruction *instr) {
    avm_memcell *t = avm_translate_operand(instr->result, (avm_memcell *)0);
    avm_memcell *i = avm_translate_operand(instr->arg1, &ax);
    avm_memcell *c = avm_translate_operand(instr->arg2, &bx);

    assert(t && &stack[AVM_STACKSIZE - 1] >= t && t > &stack[top]);
    assert(i && c);

    if (t->type != table_m)
        avm_error("illegal use of type %s as table", typeStrings[t->type]);
    else
        avm_tablesetelem(t->data.tableVal, i, c);

    printf("SET TABLE ELEM\n");
}

void execute_jump(instruction *instr) {
    assert(instr->result->type == label_a);
    printf("JUMPING TO %d\n", instr->result->val);
    if (!executionFinished) pc = instr->result->val;
}

void execute_nop(instruction *instr) { assert(0); }

/* LIBRARY FUNCTIONS */

void libfunc_print() {
    fprintf(stdout, "LIBFUNC_PRINT CALLED\n");
    unsigned n = avm_totalactuals();

    // out = fopen("out.txt", "a");

    for (unsigned i = 0; i < n; ++i) {
        avm_getactual(i);
        char *s = avm_tostring(avm_getactual(i));
        // puts(s);
        fputs(s, out);
        fflush(out);
        free(s);
    }
    // fclose(out);
}

void libfunc_input() {
    avm_memcellclear(&retval);
    char *s = (char *)malloc(100 * sizeof(char));
    fgets(s, 100, stdin);
    s[strlen(s) - 1] = '\0';

    if (s == NULL) {
        avm_error("input error");
        return return_nil();
    }
    if (s[0] == '\"') {
        retval.type = string_m;
        retval.data.strVal = s;
    }
    double num = atof(s);
    if (num || is_0(s)) {
        retval.type = number_m;
        retval.data.numVal = num;
        return;
    }
    if (!strcmp(s, "true") || !strcmp(s, "false")) {
        retval.type = bool_m;
        printf("BOOL:\n");
        retval.data.boolVal = !strcmp(s, "true");
        printf("BOOL: %d\n", retval.data.boolVal);
        return;
    }
    if (!strcmp(s, "nil")) {
        retval.type = nil_m;
        return;
    }

    retval.type = string_m;
    retval.data.strVal = s;
}

avm_table *get_memberkeys(avm_table *t) {
    avm_table *keys = avm_tablenew();
    avm_tableincrefcounter(keys);

    avm_memcell *return_key(avm_memcell * key, avm_memcell * value) {
        avm_memcell *k = (avm_memcell *)malloc(sizeof(avm_memcell));
        k->type = number_m;
        k->data.numVal = keys->total;
        avm_tablesetelem(keys, k, key);
    }

    avmtable_apply(t, return_key);

    return keys;
}

void libfunc_objectmemberkeys() {
    printf("MEMBERKEYS\n");
    unsigned n = avm_totalactuals();

    if (n != 1) {
        avm_error("one argument (not %d) expected in 'objectmemberkeys'", n);
        return return_nil();
    }

    avm_memcell *arg = avm_getactual(0);
    if (arg->type != table_m) {
        avm_error("'objectmemberkeys' argument must be a table");
        return return_nil();
    }

    avm_memcellclear(&retval);
    retval.type = table_m;
    retval.data.tableVal = get_memberkeys(arg->data.tableVal);
}

void libfunc_objecttotalmembers() {
    unsigned n = avm_totalactuals();

    if (n != 1) {
        avm_error("one argument (not %d) expected in 'objecttotalmembers'", n);
        return return_nil();
    }

    avm_memcell *arg = avm_getactual(0);
    if (arg->type != table_m) {
        avm_error("'objecttotalmembers' argument must be a table");
        return return_nil();
    }

    avm_memcellclear(&retval);
    retval.type = number_m;
    retval.data.numVal = arg->data.tableVal->total;
}

void libfunc_objectcopy() {
    unsigned n = avm_totalactuals();

    if (n != 1) {
        avm_error("one argument (not %d) expected in 'objectcopy'", n);
        return return_nil();
    }

    avm_memcell *arg = avm_getactual(0);
    if (arg->type != table_m) {
        avm_error("'objectcopy' argument must be a table");
        return return_nil();
    }
    // avm_warning("totals %d", arg->data.tableVal->total);

    avm_assign(&retval, arg);
    // avm_table *t = arg->data.tableVal;
    // avm_table *new = avm_tablenew();
    // new->total = t->total;
    // avm_tableincrefcounter(new);

    // for (int i = 0; i < libfunc_m + 1; i++) {
    //     avm_table_bucket **type_indices = t->indices[i];
    //     if (!type_indices) continue;
    //     new->indices[i] = avm_tablebucketsinit_s(hash_sizes[i]);
    //     avm_warning("copying table type %d", i);
    //     for (avm_table_bucket *b = type_indices[0]; b;) {
    //         avm_warning("copying bucket type %d", b->key->type);
    //         avm_memcell *key = (avm_memcell *)malloc(sizeof(avm_memcell));
    //         avm_memcell *value = (avm_memcell *)malloc(sizeof(avm_memcell));
    //         avm_assign(key, b->key);
    //         avm_assign(value, b->value);
    //         avm_warning("copying bucket type %d", b->key->type);
    //         b = b->next;
    //         // avm_tablesetelem(new, key, value);
    //     }
    // }

    // avm_table *keys = get_memberkeys(arg->data.tableVal);

    // for (int i = 0; i < keys->total; i++) {
    //     avm_memcell *key = (avm_memcell *)malloc(sizeof(avm_memcell));
    //     key->type = number_m;
    //     key->data.numVal = i;
    //     avm_memcell *value = avm_tablegetelem(arg->data.tableVal, key);
    //     avm_tablesetelem(keys, key, value);
    // }

    // avm_memcellclear(&retval);
    // retval.type = table_m;
    // retval.data.tableVal = new;
}

void libfunc_totalarguments() {
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

    if (!p_topsp) {
        avm_error("'totalarguments' called outside a function!");
        return return_nil();
    }

    avm_memcellclear(&retval);
    retval.type = number_m;
    retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
}

void libfunc_argument() {
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    unsigned n = avm_totalactuals();

    if (!p_topsp) {
        // avm_error("'argument' called outside a function!");
        avm_warning("'argument' called outside a function!");
        return return_nil();
    }

    if (n != 1) {
        avm_error("one argument (not %d) expected in 'argument'", n);
        return return_nil();
    }

    avm_memcell *arg = avm_getactual(0);
    if (arg->type != number_m) {
        avm_error("'argument' argument must be a number");
        return return_nil();
    }

    avm_memcellclear(&retval);
    unsigned i = (unsigned)arg->data.numVal;
    if (i < avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET)) {
        // avm_assign(&retval, avm_getactual(i));
        avm_assign(&retval, &stack[p_topsp + AVM_NUMACTUALS_OFFSET + i + 1]);
    } else {
        // avm_error("'argument' argument %d out of range", i);
        avm_warning("'argument' argument %d out of range", i);
        retval.type = nil_m;
    }
}

void libfunc_typeof() {
    unsigned n = avm_totalactuals();

    if (n != 1) {
        avm_error("one argument (not %d) expected in 'typeof'", n);
        return return_nil();
    }

    avm_memcellclear(&retval);
    retval.type = string_m;
    retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
}

// int isdigit(char c) { return c >= '0' && c <= '9'; }
int only_has_digits(char *s) {
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] != '.' && !isdigit(s[i])) return 0;
    }
    return 1;
}
void libfunc_strtonum() {
    unsigned n = avm_totalactuals();
    if (n != 1) {
        avm_error("one argument (not %d) expected in 'strtonum'", n);
        return return_nil();
    }

    avm_memcell *arg = avm_getactual(0);
    if (arg->type != string_m) {
        avm_error("'strtonum' argument must be a string");
        return return_nil();
    }

    char *s = arg->data.strVal;
    double num = atof(s);
    if (num == 0 && s[0] != 0 || !only_has_digits(s)) {
        // avm_error("'strtonum' argument must be a number");
        avm_warning("'strtonum' argument not a number");
        return return_nil();
    }
    avm_memcellclear(&retval);
    retval.type = number_m;
    retval.data.numVal = num;
}
void libfunc_sqrt() {
    unsigned n = avm_totalactuals();

    if (n != 1) {
        avm_error("one argument (not %d) expected in 'sqrt'", n);
        return return_nil();
    }
    avm_memcell *arg = avm_getactual(0);
    if (arg->type != number_m) {
        avm_error("'sqrt' argument must be a number");
        return return_nil();
    }
    if (arg->data.numVal < 0) {
        // avm_error("'sqrt' argument must be non-negative");
        avm_warning("negative argument in 'sqrt'");
        return return_nil();
    }

    avm_memcellclear(&retval);
    retval.type = number_m;
    retval.data.numVal = sqrt(arg->data.numVal);
}
#define pi 3.1415926535897932384626433832795
void libfunc_cos() {
    unsigned n = avm_totalactuals();

    if (n != 1) {
        avm_error("one argument (not %d) expected in 'cos'", n);
        return return_nil();
    }
    avm_memcell *arg = avm_getactual(0);
    if (arg->type != number_m) {
        avm_error("'cos' argument must be a number");
        return return_nil();
    }

    avm_memcellclear(&retval);
    retval.type = number_m;
    retval.data.numVal = cos(arg->data.numVal * pi / 180);
}
void libfunc_sin() {
    unsigned n = avm_totalactuals();

    if (n != 1) {
        avm_error("one argument (not %d) expected in 'sin'", n);
        return return_nil();
    }
    avm_memcell *arg = avm_getactual(0);
    if (arg->type != number_m) {
        avm_error("'sin' argument must be a number");
        return return_nil();
    }

    avm_memcellclear(&retval);
    retval.type = number_m;
    retval.data.numVal = sin(arg->data.numVal * pi / 180);
}

int execute_cycle() {
    if (executionFinished) return 0;

    if (pc == AVM_ENDING_PC) {
        executionFinished = 1;
        return 0;
    }

    assert(pc < AVM_ENDING_PC);
    instruction *instr = code + pc;
    fprintf(stdout, "\nEXECUTING INSTRUCTION %d (line %d)\n", pc,
            instr->srcLine);

    assert(instr->opcode >= 0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);

    if (instr->srcLine) currLine = instr->srcLine;

    unsigned oldPC = pc;
    (*executeFuncs[instr->opcode])(instr);

    // if(instr->opcode == jump_v)
    if (pc == oldPC) ++pc;

    return 1;
}

extern unsigned programVarOffset;

void avm_initialize() {
    avm_initstack();
    code = instructions;

    // ax.type = undef_m;
    // bx.type = undef_m;
    // cx.type = undef_m;
    // retval.type = undef_m;

    topsp = AVM_STACKSIZE - 1;
    // fprintf(stdout, "PROGRAMVAROFFSET: %d\n", programVarOffset);
    top = AVM_STACKSIZE - 1 - programVarOffset;
    pc = 1;
}