#include<stdio.h>
#include <string.h>
#define SoPhanTu 100
typedef float ElementType;
typedef struct {
	ElementType DuLieu[SoPhanTu]; 
	int Dinh; 
}Stack;

//Tao danh sach rong
void makenullStack(Stack *S){
	S->Dinh = SoPhanTu;
}

//Kiem tra ngan xep rong
int emptyStack(Stack S){
	return S.Dinh == SoPhanTu;
}

//Kiem tra ngan xap day
int fullStack(Stack S){
	return S.Dinh == 0;
}

//Gia tri dinh stack
ElementType top(Stack S){
	return S.DuLieu[S.Dinh];
}

//Xoa phan tu tai dinh Stack
void pop(Stack *S){
	S->Dinh++;
}

//Them phan tu X vao stack
void push(ElementType X, Stack *S){
	if(fullStack(*S)) {
		printf("Stack day");
	} else {
		S->Dinh--;
		S->DuLieu[S->Dinh] = X;
	}
}

//tính giá trị của một biểu thức hậu tố
float tinh(char X, float a, float b){
	float kq;
	switch(X){
		case '+':
			kq = a + b;
			break;
		case '-':
			kq = a - b;
			break;
		case '*':
			kq = a * b;
			break;
		case '/':
			kq = a / b;
			break;
	}
	return kq;
}
float chuoi(char *st){
	int i, n = strlen(st) - 1;
	Stack S;
	makenullStack(&S);
	for(i = 0; i < n; i++){
		float tren, duoi;
		if(st[i] != ' '){			
			if(st[i] >= '0' && st[i] <= '9'){		
				push((st[i] - 48), &S);		
			} else {			
				tren = top(S);
				pop(&S);	
				duoi = top(S);
				pop(&S);
				push(tinh(st[i], duoi, tren), &S);	
			}
		}	
	}
	return top(S);
}

//đổi biểu thức toán học thành biểu thức hậu tố
void chen(char x, char *st){
	int n = strlen(st);
	st[n++] = x;
	st[n++] =' ';
	st[n] ='\0';
}              
int uutien(char c){
	int x;
	if(c == '(') x = 0;;
	if(c == '+' || c == '-') x = 1;
	if(c == '*' || c == '/' || c == '%') x = 2;
	return x;
}

void hauto(){
	Stack S; 
	makenullStack(&S);
	char x[256];
	char st[256] = "";
	int i;
	fgets(x, 256, stdin);
	for(i = 0; i < strlen(x)-1; i++){
		if(x[i] != ' '){
			if(x[i] >= '0' && x[i] <= '9') chen(x[i], st);
			else{
				if(x[i] == '(') push(x[i], &S);
				else{
					if(x[i] == ')'){
						while(top(S) != '('){
							chen(top(S), st);
							pop(&S);
						}
						pop(&S);
					}
					else {
						while(S.Dinh != SoPhanTu && uutien(x[i]) <= uutien(top(S))){
							chen(top(S), st);
							pop(&S);
						}
						push(x[i], &S);
					}	
				}
			}
		}	
	}
	while(S.Dinh != SoPhanTu) {
		chen(top(S), st);
		pop(&S);
	}	
	st[strlen(st)-1] = '\0';
	printf("%s", st);
}
