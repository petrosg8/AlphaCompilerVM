#include "scanner.h"


extern int alpha_yylex(void *ylval);

extern FILE *alpha_yyin;
extern FILE *alpha_yyout;

struct alpha_token_t *list_head;
int list_length;

void print_tokens(struct alpha_token_t *current, FILE *alpha_yyout) {
    if (current == NULL) return;

    print_tokens(current->next, alpha_yyout);

    fprintf(alpha_yyout, "%u:  \t", current->line);
    fprintf(alpha_yyout, "#%u  \t", current->n_token);
    fprintf(alpha_yyout, "\"%s\"  \t", current->content);
    fprintf(alpha_yyout, "%s  \t", category_str[current->category]);

    // subcategory
    int index = current->category - 1;
    if (index <= 3) {
        fprintf(alpha_yyout, "%s", subcat_str_table[index][current->subcat]);
    } else
        fprintf(alpha_yyout, "%s", current->content);

    fprintf(alpha_yyout, "\t<- %s\n", table_of_types[index]);

    return;
}

int main(int argc, char **argv) {
    if (!(alpha_yyin = fopen(argv[1], "r"))) {
        fprintf(stderr, "Cannot open file %s for reading.\n", argv[1]);
        return 1;
    }

    if (argc > 2) {
        if (!(alpha_yyout = fopen(argv[2], "w"))) {
            fprintf(stderr, "Cannot open file %s for writing. ", argv[2]);
            fprintf(stderr, "Reverting to stdout instead.\n");
            alpha_yyout = stdout;
        }
    } else {
        alpha_yyout = stdout;
    }

    struct alpha_token_t *token = malloc(sizeof(struct alpha_token_t));
    list_head = NULL;

    while (alpha_yylex(token) != EOF) {
        struct alpha_token_t *new_token = malloc(sizeof(struct alpha_token_t));
        if (new_token == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return 1;
        }

        new_token->content = malloc(strlen(token->content) + 1);
        if (new_token->content == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            free(new_token);
            return 1;
        }
        strcpy(new_token->content, token->content);

        list_length++;
        new_token->line = token->line;
        new_token->n_token = list_length;
        new_token->category = token->category;
        new_token->subcat = token->subcat;
        new_token->next = list_head;
        list_head = new_token;
    }
    fprintf(alpha_yyout, "\n------------------------  Lexical Analysis  ------------------------\n\n");
    print_tokens(list_head, alpha_yyout);

    return 0;
}
