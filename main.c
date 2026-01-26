#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

typedef uint32_t u32;
typedef int32_t i32;

#define BUFFER_SIZE 60;

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


Token* interpret(char *line){
    u32 length = strlen(line);
    Token *tokens = malloc(sizeof(Token) * length);

    for(int i=0; i<length; i++){
        tokens[i].type = parseToken(line[i]);
        tokens[i].value = line[i];
    }

    return tokens;
}


i32 claculate(Token tokens[], u32 length){
   
    i32 sum = 0;
    u32 actualNumber = 0;

    for (int i=0; i< length; i++){

        Token token = tokens[i];

        if (token.type == INT){
            actualNumber *= 10;
            actualNumber += (token.value - '0');
        }
        else{
            if (token.value == '-'){
                sum -= actualNumber;
                actualNumber = 0;
            }
            else {
                sum += actualNumber;
                actualNumber = 0;
            }
        }
    }

    return sum;

}


int main(){

    char line[BUFFER_SIZE];

    while(1){
        scanf("%60s" , line);

        Token *tokens = interpret(line);

        printf("%d",claculate(tokens , strlen(line)));

        free(tokens);
    }

    return 0;
}


