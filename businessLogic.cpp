#include "businessLogic.h"
#include <cmath>

double resultOperations(action calcObject);
double trigonometricOperations(action calcObject);
double optionalOperations(action calcObject);
double optionalMemory(action calcObject);


double typeOperation(action calcObject){
    double res = CLEAR;
    if(calcObject.action == PLUS || calcObject.action == MINUS || calcObject.action == MULTIPLY || calcObject.action == DIVIDE){
        res = resultOperations(calcObject);
    } else if(calcObject.action == TAN || calcObject.action == CTAN || calcObject.action == SIN || calcObject.action == COS){
        res = trigonometricOperations(calcObject);
    } else if(calcObject.action == X1 || calcObject.action == SQRT){
        res = optionalOperations(calcObject);
    } else if(calcObject.action == MPLUS || calcObject.action == MMINUS){
        res = optionalMemory(calcObject);
    }
    return res;
}

double trigonometricOperations(action calcObject){
    double res = CLEAR;
    if (calcObject.action == SIN){
        res = sin(calcObject.memory);
    } else if (calcObject.action == COS){
        res = cos(calcObject.memory);
    } else if (calcObject.action == TAN){
        if(cos(calcObject.action) != 0){
            res = tan(calcObject.memory);
        } else {
            res = ERROR_TAN;
        }
    }else if(calcObject.action == CTAN){
        if(sin(calcObject.action) != 0){
            res = cos(calcObject.memory) / sin(calcObject.memory);
        } else{
            res = ERROR_CTAN;
        }
    }
    return res;
}

double resultOperations(action calcObject){
    double res = CLEAR;
    if (calcObject.action == PLUS){
        res = calcObject.memory + calcObject.number;
    } else if (calcObject.action == MINUS) {
        res = calcObject.memory - calcObject.number;
    } else if (calcObject.action == MULTIPLY) {
        res = calcObject.memory * calcObject.number;
    } else if (calcObject.action == DIVIDE){
        if(calcObject.number != 0) {
            res = calcObject.memory / calcObject.number;
        } else {
            res = ERROR_DIV;
        }
    }
    return res;
}

double optionalOperations(action calcObject){
    double res = CLEAR;
    if(calcObject.action == X1){
        if(calcObject.memory != 0){
            res = 1.0 / calcObject.memory;
        } else {
            res = ERROR_X1;
        }
    } else if(calcObject.action == SQRT){
        if(calcObject.memory >= 0){
            res = sqrt(calcObject.memory);
        } else {
            res = ERROR_SQRT;
        }
    }
    return res;
}

double optionalMemory(action calcObject){
    double res = CLEAR;
    if(calcObject.action == MPLUS){
        res = calcObject.mRead + calcObject.memory;
    } else if(calcObject.action == MMINUS){
        res = calcObject.memory - calcObject.mRead;
    }

    return res;
}
