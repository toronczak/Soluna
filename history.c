#include <stdlib.h>
//	historia wyników
int history(){
	system("cls");
	FILE *record;
	typeEffect(17, "Voyage history:\n\n", 50000);
	record = fopen("score.sln", "r");
    char c = fgetc(record);
    while(c != EOF){
        printf("%c", c);
        c = fgetc(record);
    }
    fclose(record);
	typeEffect(26, "Press any key to continue.", 16666);
	getch();
	return 0;
}
