


#ifndef utils
#define utils

#define SETBIT(REG,X) (REG|=(1<<X))
#define RESETBIT(REG,X) (REG&=~(1<<X))
#define SET_NIB_HIGH(REG) (REG|=(15<<4))
#define SET_NIB_LOW(REG) (REG|=(15))
#define RESET_NIB_HIGH(REG) (REG&(~(15<<4)))
#define RESET_NIB_LOW(REG) (REG&(~15))
#define GET_NIB_HIGH(REG) (REG&(15<<4))>>4
#define GET_NIB_LOW(REG) (REG&15)
#define SET_NIB_HIGHVAL(REG,VALUE) (REG &(~(15<<4)))|(VALUE <<4)
#define SET_NIB_LOWVAL(REG,VALUE) (REG&(~15))|(VALUE)
#define GETBIT(REG,NO) (((REG)&(1<<NO))>>NO)


#endif

