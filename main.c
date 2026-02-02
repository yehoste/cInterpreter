#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
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

i32 calculate(Token **tokens, u32 length);


Type parseToken(char letter){
    if (letter >= '0' && letter <= '9'){
        return INT;
    }
    return OPERATOR;
}

Token* interpret(char *line){

    u32 length = strlen(line) - 1;

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

u32 getLengthOfInt(i32 number){
    u32 length = 0;

    if (number < 0){
        number *= -1;
        length +=1;
    }

    while(number >= 10){
        number /= 10;
        length++;
    }

    return length+1;
}


u32 powI(u32 base, u32 exp){
    u32 result = 1;
    for(int i = 0; i < exp; i++){
        result *= base;
    }

    return result;
}

void removeBrackets(Token **tokens, u32 *length){

    i32 startIndex = -1;
    u32 endingIndex;

    bool noBrackets=false;

    u32 counter = 0;

    for (int i=0; i < *length; i++){

        if ((*tokens)[i].value == '('){
            if (startIndex == -1){
                startIndex = i;
            }
            counter++;
        }
        if ((*tokens)[i].value == ')'){
            counter--;
            if (counter == 0){
                endingIndex = i;
                break;
            }
        }
    }

    u32 length2 = endingIndex - startIndex - 1;

    Token *newTokens = malloc(sizeof(Token) * length2);

    for (int i = startIndex + 1; i < endingIndex; i++){
        newTokens[i - startIndex - 1] = (*tokens)[i];
    }

    i32 result = calculate(&newTokens, length2);

    free(newTokens);

    u32 lengthR = getLengthOfInt(result);

    Token *tokensU = malloc(sizeof(Token) * (*length - length2 - 2 + lengthR));

    for (int i = 0; i < *length - length2 - 2 + lengthR; i++){

        if (i < startIndex || i >= startIndex +lengthR){
            tokensU[i] = (*tokens)[i];
            continue;
        }

        if (result < 0){
            tokensU[i].value = '-';
            tokensU[i].type = OPERATOR;
            result *= -1;
            continue;
        }
        tokensU[i].value = (char)(result % powI(10, (startIndex + lengthR - i)) + '0');
        tokensU[i].type = INT; 
    }

    free(*tokens);

    *length = *length - length2 - 2 + lengthR;

    *tokens = tokensU;

}


i32 calculate(Token **tokens, u32 length){

    i32 sum = 0;
    u32 actualNumber = 0;
    char previous = '+';

    for (int i = 0; i < length; i++){
        if ((*tokens)[i].value == '('){
            removeBrackets(tokens, &length);
            i = -1;
        }
    }

    for (int i=0; i< length; i++){

        Token token = (*tokens)[i];

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

        printf("%d\n",calculate(&tokens , strlen(line) - 1));

        free(tokens);
    }

    return 0;
}


