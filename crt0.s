push $0        # argv = NULL
push $0        # argc = 0
call main      # Start C's main function
mov $0x4c, %ah # End program
int $0x21
