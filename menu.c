#include <stdio.h>
#include <windows.h>
#include "game.c"
#include "history.c"
//	ciekawy efekt wyœwietlania tekstu
int typeEffect(int length, char text[length], int time){
	for(int i = 0; i < length; i++){
		printf("%c", text[i]);
		usleep(time);
	}
}
//	globalna zmienna czasu, ¿eby znów nie wyœwietlaæ czo³ówki po powrocie do menu.
int t = 1000000;
//	menu g³ówne
int main(){
	char n;
    printf("presented by Toronczak, 2020\n");
    typeEffect(59, "[][][][]  [][][][]  []        []    []  []    []  [][][][]\n", t/24);
    typeEffect(59, "[]        []    []  []        []    []  [][]  []  []    []\n", t/30);
    typeEffect(59, "[][][][]  []    []  []        []    []  []  [][]  [][][][]\n", t/36);
    typeEffect(59, "      []  []    []  []        []    []  []    []  []    []\n", t/42);
    typeEffect(59, "[][][][]  [][][][]  [][][][]  [][][][]  []    []  []    []\n", t/48);
    typeEffect(36, "                                    ", t/60);
    typeEffect(23, "-the solitary odyssey-\n", t/20);
    typeEffect(51, "1 to start,\n2 to display score history,\n3 to exit.\n", t/60);
	scanf("%c", &n);
	t = 0;
	if(n == '1') action();
	else if(n == '2') history();
	else if(n == '3') return 0;
	system("cls");
	main();
}
