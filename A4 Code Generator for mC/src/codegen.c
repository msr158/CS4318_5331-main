#include "codegen.h"
#include "tree.h"

// Global label counter for generating unique labels
int labelCounter = 0;

// start w/ global and .data, .text
// do funcdecl next
// do startmain
// after .text should be easy(same every case)

int process(tree* node) {
    if (node == NULL) {
        return 0;
    }

    // Check the nodeKind to determine which code generation function to call
    switch (node->nodeKind) { 
        case PROGRAM:
            gen_program(node);
            break;
        case FUNDECL:
            gen_function(node);
            break;
        case STATEMENTLIST:
            for (int i = 0; i < node->numChildren; i++) {
                process(node->children[i]);
            }
            break;
        case ASSIGNSTMT:
            gen_assignment(node);
            break;
        case CONDSTMT:
            gen_conditional(node);
            break;
        case LOOPSTMT:
            gen_loop(node);
            break;
        case RETURNSTMT:
            gen_return(node);
            break;
        case EXPRESSION:  
            gen_expression(node);
            break;
        
        // output function call
        // gen_output_function_call(node);
        // break;
        // other cases as needed
        default:
            printf("Unknown node kind: %d\n", node->nodeKind);
    }

    // // Recursively process children nodes
    // for (int i = 0; i < node->numChildren; i++) {
    //     process(node->children[i]);
    // }

    return 0;
}

void gen_program(tree* node) { //program node
    gen_global_vars(node->children[0]);  // Generate code for global variables, calls function below

    printf("\n.text\n");
    printf("    jal startmain\n");  // Jump to main function
	printf("    li $v0, 10\n");  // Exit syscall
	printf("    syscall\n");
	printf("    # Function definition\n");

    tree* declListNode = node->children[0]; // points to program's 1st child (declList)

    for(int i = 0; i < declListNode->numChildren; i++){
        if(declListNode->children[i]->nodeKind == FUNDECL) {
            process(declListNode->children[i]);
        }
    }

    // goes at the end
    printf("# output function\n");
    printf("startoutput:\n");
	printf("    # Put argument in the output register\n");
	printf("    lw $a0, 4($sp)\n");
	printf("    # print int is syscall 1\n");
	printf("    li $v0, 1\n");
	printf("    syscall\n");
	printf("    # jump back to caller\n");
	printf("    jr $ra\n");
}

void gen_global_vars(tree* node) { //decl list node
    if (node == NULL) {
        return; 
    }

    printf("# Global variable allocations:\n");
    printf(".data\n");

    for (int i = 0; i < node->numChildren; i++) {
        if(node->children[i]->nodeKind == VARDECL) {
            printf("var%s: .word 0\n", strTable[node->children[i]->children[1]->val].id);  // Assume all variables are integers
        } 
    
    }
}

void gen_function(tree* funcNode) {
    if (funcNode == NULL) {
        return;
    }

    printf("func%s:\n", strTable[funcNode->children[0]->children[1]->val].id);  // Function label

    printf("    # Setting up FP\n");
    printf("    sw $fp, ($sp)\n");
    printf("    move $fp, $sp\n");
    printf("    subi $sp, $sp, 4\n\n");

	printf("    # Saving registers\n");
	printf("    sw $s0, ($sp)\n");
    printf("    subi $sp, $sp, 4\n");
    printf("    sw $s1, ($sp)\n");
    printf("    subi $sp, $sp, 4\n");
    printf("    sw $s2, ($sp)\n");
    printf("    subi $sp, $sp, 4\n");
    printf("    sw $s3, ($sp)\n");
    printf("    subi $sp, $sp, 4\n");
    printf("    sw $s4, ($sp)\n");
    printf("    subi $sp, $sp, 4\n");
    printf("    sw $s5, ($sp)\n");
    printf("    subi $sp, $sp, 4\n");
    printf("    sw $s6, ($sp)\n");
    printf("    subi $sp, $sp, 4\n");
    printf("    sw $s7, ($sp)\n");
    printf("    subi $sp, $sp, 4\n\n");

    // Generate code for function body expressions
    for (int i = 0; i < funcNode->numChildren; i++) {
        gen_expression(funcNode->children[i]);
    }

    printf("    # Reloading registers\n");
    printf("    addi $sp, $sp, 4\n");
    printf("    lw $s7, 0($sp)\n");
    printf("    addi $sp, $sp, 4\n");
    printf("    lw $s6, 0($sp)\n");
    printf("    addi $sp, $sp, 4\n");
    printf("    lw $s5, 0($sp)\n");
    printf("    addi $sp, $sp, 4\n");
    printf("    lw $s4, 0($sp)\n");
    printf("    addi $sp, $sp, 4\n");
    printf("    lw $s3, 0($sp)\n");
    printf("    addi $sp, $sp, 4\n");
    printf("    lw $s2, 0($sp)\n");
    printf("    addi $sp, $sp, 4\n");
    printf("    lw $s1, 0($sp)\n");
    printf("    addi $sp, $sp, 4\n");
    printf("    lw $s0, 0($sp)\n\n");

    printf("    # Setting FP back to old value\n");
    printf("    lw $fp, 0($sp)\n"); // restore return address
    printf("    addi $sp, $sp, 4\n\n"); // restore stack pointer

    printf("    # Return to caller\n");
    printf("    jr $ra\n"); // return

    printf("func%s:\n\n", strTable[funcNode->children[0]->children[1]->val].id);  // endfunc

    // get_formDecl(funcNode->children[1]);  // Function parameters
    gen_funBody(funcNode->children[2]);  // Function body


}

void get_formDecl(tree* node) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < node->numChildren; i++) {
        printf("addi $sp, $sp, -4\n");  // Adjust stack pointer
        printf("sw $a%d, 0($sp)\n", i);  // Save parameter
    }
}
void gen_funBody(tree* node) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < node->numChildren; i++) {
        process(node->children[i]);
    }
}

void gen_expression(tree* exprNode) {
    if (exprNode == NULL) {
        return;
    }

    switch (exprNode->nodeKind) {
        case CONST:
        case INTEGER:
            printf("    li $t0, %d\n", exprNode->val);
            break;
        case VAR:
        case IDENTIFIER:
            printf("    lw $t0, var%s\n", strTable[exprNode->val].id);
            break;
        case ADD:
        case ADDOP:
            gen_expression(exprNode->children[0]);
            printf("    sw $t0, 0($sp)\n");
            printf("    subi $sp, $sp, 4\n");
            gen_expression(exprNode->children[1]);
            printf("    lw $t1, 4($sp)\n");
            printf("    add $t0, $t0, $t1\n");
            printf("    addi $sp, $sp, 4\n");
            break;
        case SUB:
            gen_expression(exprNode->children[0]);
            printf("    sw $t0, 0($sp)\n");
            printf("    subi $sp, $sp, 4\n");
            gen_expression(exprNode->children[1]);
            printf("    lw $t1, 4($sp)\n");
            printf("    sub $t0, $t0, $t1\n");
            printf("    addi $sp, $sp, 4\n");
            break;
        case MUL:
        case MULOP:
            gen_expression(exprNode->children[0]);
            printf("    sw $t0, 0($sp)\n");
            printf("    subi $sp, $sp, 4\n");
            gen_expression(exprNode->children[1]);
            printf("    lw $t1, 4($sp)\n");
            printf("    mul $t0, $t0, $t1\n");
            printf("    addi $sp, $sp, 4\n");
            break;
        case DIV:
            gen_expression(exprNode->children[0]);
            printf("    sw $t0, 0($sp)\n");
            printf("    subi $sp, $sp, 4\n");
            gen_expression(exprNode->children[1]);
            printf("    lw $t1, 4($sp)\n");
            printf("    div $t0, $t0, $t1\n");
            printf("    addi $sp, $sp, 4\n");
            break;
        case RELOP:
            gen_expression(exprNode->children[0]);
            printf("    sw $t0, 0($sp)\n");
            printf("    subi $sp, $sp, 4\n");
            gen_expression(exprNode->children[1]);
            printf("    lw $t1, 4($sp)\n");
            switch (exprNode->val) {
                case LT:
                    printf("    slt $t0, $t0, $t1\n");
                    break;
                case GT:
                    printf("    sgt $t0, $t0, $t1\n");
                    break;
                case EQ:
                    printf("    seq $t0, $t0, $t1\n");
                    break;
                default:
                    printf("    # Unsupported relational operator\n");
                    break;
            }
            printf("    addi $sp, $sp, 4\n");
            break;
        case EXPRESSION:
        case ADDEXPR:
        case TERM:
        case FACTOR:
            for (int i = 0; i < exprNode->numChildren; i++) {
                gen_expression(exprNode->children[i]);
            }
            break;
        default:
            printf("    # Unsupported expression type: %d\n", exprNode->nodeKind);
            break;
    }
}

void gen_assignment(tree* node) {
    if (node == NULL) {
        return;
    }

    process(node->children[1]);  // Generate code for the right-hand side (expression)
    printf("sw $t0, var%s\n", strTable[node->children[0]->val].id);  // Store value into the variable
}

void gen_conditional(tree* node) {
    if (node == NULL) {
        return;
    }

    int labelElse = labelCounter++;
    int labelEnd = labelCounter++;

    gen_expression(node->children[0]);  // Condition expression
    printf("    beq $t0, $zero, ELSE_LABEL_%d\n", labelElse);
    process(node->children[1]);  // If body
    printf("    j END_LABEL_%d\n", labelEnd);
    printf("ELSE_LABEL_%d:\n", labelElse);
    if (node->numChildren > 2) {
        process(node->children[2]);  // Else body
    }
    printf("END_LABEL_%d:\n", labelEnd);
}

void gen_loop(tree* node) {
    if (node == NULL) {
        return;
    }

    int labelStart = labelCounter++;
    int labelEnd = labelCounter++;

    printf("LOOP_START_%d:\n", labelStart);
    gen_expression(node->children[0]);  // Condition expression
    printf("    beq $t0, $zero, LOOP_END_%d\n", labelEnd);
    process(node->children[1]);  // Loop body
    printf("    j LOOP_START_%d\n", labelStart);
    printf("LOOP_END_%d:\n", labelEnd);
}
void gen_return(tree* node) {
    if (node == NULL) {
        return;
    }

    if (node->numChildren > 0) {
        gen_expression(node->children[0]);  // Return expression
        printf("    move $v0, $t0\n");
    }

    printf("    # Restore registers\n");
    printf("    lw $s7, 0($sp)\n");
    printf("    addi $sp, $sp, 4\n");
    printf("    lw $s6, 0($sp)\n");
    printf("    addi $sp, $sp, 4\n");
    printf("    lw $s5, 0($sp)\n");
    printf("    addi $sp, $sp, 4\n");
    printf("    lw $s4, 0($sp)\n");
    printf("    addi $sp, $sp, 4\n");
    printf("    lw $s3, 0($sp)\n");
    printf("    addi $sp, $sp, 4\n");
    printf("    lw $s2, 0($sp)\n");
    printf("    addi $sp, $sp, 4\n");
    printf("    lw $s1, 0($sp)\n");
    printf("    addi $sp, $sp, 4\n");
    printf("    lw $s0, 0($sp)\n");
    printf("    addi $sp, $sp, 4\n");

    printf("    # Restore FP\n");
    printf("    lw $fp, 0($sp)\n");
    printf("    addi $sp, $sp, 4\n");

    printf("    jr $ra\n");
}