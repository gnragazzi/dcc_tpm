***
Casos Válidos

void main(){
    int a, b = 0;
    
    a = b + 1;
}

***

int a;

void main(){
    int b = a + 1;
}

***

void main(){
    int a, b[1] = {0};
    
    a = b[0] + 1;
}

***

int a[] = {1,2,3};

void main(){
    int b = a[4] + 1; // no chequeamos (en análisis semántico) que el índice esté entre 0 y n-1
}


*** 

Casos inválidos

void main(){
    int a;

    a = b + 1;
}

     Error 71: Identificador no declarado

***

int fun(){
    a = 1;
}

void main(){
    int a;
    fun();
}

     Error 71: Identificador no declarado

***
void main(){
    int a;
    fun();
}

int fun(){
    a = 1;
}

     Error 71: Identificador no declarado
     Error 71: Identificador no declarado

***

void main(){
    int a;
    fun(a);
}

     Error 71: Identificador no declarado

***

***

void main(){
    if (1){
        int a = 0;
   }else
        a = 1;
}

     Error 71: Identificador no declarado

***

void main(){
    int x;
    {
        int a = 0;
    }
    x = a;
}

     Error 71: Identificador no declarado
