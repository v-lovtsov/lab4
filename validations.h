#ifndef validations_h
#define validations_h


int validateToken(char token) {
    if (token >= '0' && token <= '9')
        return 1;
    
    if (token >= '(' && token <= '+')
        return 1;

    if (token == '-' || token == '/')
        return 1;

    return 0;
}

// 1 - числа, 2 - операнды, 3 - откр. скобка, 4 - закр. скобка, 5 - конец строки
int validatePreviousToken(int curtype, int prevtype) {
    if (curtype == 1 && prevtype == 4)
        return 0;
    
    if (curtype == 2 && (prevtype == 3 || prevtype == 2))
        return 0;

    if (curtype == 3 && (prevtype != 2 && prevtype != 3))
        return 0;

    if (curtype == 4 && (prevtype != 1 && prevtype != 4))
        return 0;

    if (curtype == 5 && prevtype != 4 && prevtype != 1)
        return 0;

    return 1;
}

int isOperand(char token) {
    return token == '+' || token == '-' || 
                token == '*' || token == '/';
}
#endif