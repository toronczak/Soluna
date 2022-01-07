#include <math.h>
//	kluczowe dane o zasobach gracza
struct data{
	int flag, move, score, goal, stage;
	int block[7][7];
}info;
//	przygotowywanie gry do ponownego zagrania, zapis wyniku
int reset(){
	char name[101];
	typeEffect(45, "Enter your name in less than 100 characters:\n", 16666);
	fflush(stdin);
	fgets(name, 101, stdin);
	
	FILE *fscore;
	fscore = fopen("score.sln","a");
	fprintf(fscore, "Score: %d\nPlayer: %s\n", info.score, name);
	fclose(fscore);
	
	info.flag = 0;
	info.move = -1;
	info.score = 0;
	info.stage = 1;
	info.goal = info.score+4000+info.stage*1000;
}
//	zamiana dwóch klocków
int swap(int *x, int *y){
    int temp = (*x);
    (*x) = (*y);
    (*y) = temp;
}
//	wyœwietlanie planszy
int display(){
	system("cls");
	HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("Score: %d\tStage: %d\n", info.score, info.stage);
    printf("Moves left: %d\tPoints until clear: %d\n\n", 20-info.move, info.goal-info.score);
    printf("   0 1 2 3 4 5 6\n");
	for(int i = 0; i <= 6; i++){
		SetConsoleTextAttribute(hConsole, 7);
		printf("%d ", i);
    	for(int j = 0; j <= 6; j++){
    		if(info.move == -1) info.block[i][j] = 1;
			int color;
			if		(info.block[i][j] == 0) color = 0;
			else if	(info.block[i][j] == 1) color = 144;
			else if	(info.block[i][j] == 2) color = 160;
			else if	(info.block[i][j] == 3) color = 192;
			else if	(info.block[i][j] == 4) color = 240;
			else if	(info.block[i][j] == 5) color = 48;
			else if	(info.block[i][j] == 6) color = 80;
			else if	(info.block[i][j] == 7) color = 96;
			SetConsoleTextAttribute(hConsole, color);
			printf("  ", info.block[i][j]);
    	}
    	printf("\n");
	}
	printf("\n");
	SetConsoleTextAttribute(hConsole, 7);
}
//	algorytm akcji
int action(){
//	komunikat o przegraniu gry
	display();
	if(info.move >= 20){
		typeEffect(11, "GAME OVER.\n", 50000);
		reset();
		return 0;
	}
//	komunikaty ukoñczenia planszy/rozpoczêcia gry	
	if(info.score >= info.goal){
		if(info.stage == 4){
			typeEffect(13, "ALL CLEAR!!!\n", 50000);
			typeEffect(119, "The SOLUNA drone has managed to analyze the data.\nCongratulations at finishing your mission!\n", 16666);
			reset();
			return 0;
		}
		if(info.stage > 0){	
			typeEffect(13, "STAGE CLEAR!\n", 50000);
			typeEffect(26, "Press any key to continue.", 16666);
			getch();
		}
		else{
			typeEffect(17, "MISSION STARTED.\n", 50000);
			usleep(500000);
			typeEffect(10, "Good luck!", 50000);
			usleep(500000);
		}
		info.stage++;
		info.goal = info.score+4000+info.stage*1000;
		info.move = -1;
	}
//	wybór klocków	
	if(info.move >= 0){
		int a = -1, b = -1;
		while (a < 0 || a > 6 || b < 0 || b > 6){
			typeEffect(49, "Select the first block to be swapped: (i.e. x y)\n", 16666);
			scanf("%d %d", &b, &a);
		}
	
		int c = -1, d = -1;
		while (c < 0 || c > 6 || d < 0 || d > 6 || (c == a && d == b)){
			typeEffect(25, "Second block: (i.e. x y)\n", 16666);
			scanf("%d %d", &d, &c);
		}
		swap(&info.block[a][b], &info.block[c][d]);
	}
	system("cls");
	display();
    sleep(1);
	srand(time(NULL));
//	sprawdzanie, czy dopasowano klocki
    int check[7][7] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int WTFlag = 1;
    while(WTFlag == 1){
		WTFlag = 0;
		int point = 0;
		for(int i = 0; i <= 6; i++){
   		 	for(int j = 0; j <= 6; j++){
				if(info.block[i+1][j] == info.block[i][j]){
					if(info.block[i+2][j] == info.block[i][j]){
						for(int k = 0; k < 3; k++) check[i+k][j] = 1;
					}
				}
				if(info.block[i][j+1] == info.block[i][j]){
					if(info.block[i][j+2] == info.block[i][j]){
						for(int k = 0; k < 3; k++) check[i][j+k] = 1;
					}
				}
			if(check[i][j] == 1){
				info.block[i][j] = 1+rand()%(3+info.stage);
				WTFlag = 1;
				if(info.move != -1) point++;
			}
			check[i][j] = 0;
			}
		}
		if(info.move != -1){
			display();
			if(point >= 3){
				info.score += point*(30+point*10);
				printf("+%d!", point*(30+point*10));
			}
			usleep(500000);
		}
	}

	info.move++;
    action();
}
