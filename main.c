#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef uint32_t u32;
typedef int32_t i32;

#define BUFFER_SIZE 64

typedef enum Type{
    INT,
    OPERATOR
}Type;


typedef struct{
    Type type;
    char value;
}Token;


Type parseToken(char letter){
    if (letter >= '0' && letter <= '9'){
        return INT;
    }
    return OPERATOR;
}

// char* removeBlank(char *line){
    
//     u32 blankCount=0;

//     for(int i = 0; i < strlen(line); i++){
//         if (line[i] == ' '){
//             blankCount++;
//         }
//     }


// }


Token* interpret(char *line){
    u32 length = strlen(line);
    Token *tokens = malloc(sizeof(Token) * length);

    for(int i=0; i<length; i++){
        tokens[i].type = parseToken(line[i]);
        tokens[i].value = line[i];
    }

    return tokens;
}

void operate(i32 *sum, char operator, u32 num){
    if (operator == '-'){
        *sum -= num;
    }
    else {
        *sum += num;
    }
}


i32 claculate(Token tokens[], u32 length){
   
    i32 sum = 0;
    u32 actualNumber = 0;
    char previous = '+';

    for (int i=0; i< length; i++){

        Token token = tokens[i];

        if (token.value == ' '){
            continue;
        }

        if (token.type == INT){
            actualNumber *= 10;
            actualNumber += (token.value - '0');
        }
        else{
            operate(&sum, previous, actualNumber);
            actualNumber = 0;
            previous = token.value;
        }
    }

    operate(&sum, previous, actualNumber);

    return sum;

}


int main(){

    char line[BUFFER_SIZE];

    while(1){
        fgets(line, BUFFER_SIZE, stdin);

        Token *tokens = interpret(line);

        printf("%d\n",claculate(tokens , strlen(line)));

        free(tokens);
    }

    return 0;
}


