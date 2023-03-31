#ifndef BUSINESSLOGIC_H
#define BUSINESSLOGIC_H

#define PLUS 1
#define MINUS -1
#define MULTIPLY 2
#define DIVIDE 3

#define MREAD 50
#define MPLUS 51
#define MMINUS 52
#define MCLEAR 53


#define SIN 100
#define COS 101
#define TAN 102
#define CTAN 103

#define SQRT 150
#define X1 151

#define ERROR_SQRT -9999999999
#define ERROR_X1 -9999999998
#define ERROR_TAN -9999999997
#define ERROR_CTAN -9999999996
#define ERROR_DIV -9999999995

#define CLEAR 0

typedef struct actionObj{
    double mRead;
    double memory;
    double number;
    int action;
}action;

double typeOperation(action calcObject);

#endif // BUSINESSLOGIC_H
