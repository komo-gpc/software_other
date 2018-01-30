#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int rand_s[100];
int MAXRAND,gyou4,x;
void kyoukabetu();

void rand2();
void sakuzyo();
int kesu[100];
void time_attack();
int question(int,int,int);

void kiroku();
void sakujo2();
int kkg, sgk, eng, rk, scl, sg, ta, dth;

void kyoukabetsu()
{	
	int MAXRAND=20;
	int i,k;
	FILE *fp;
	char chr;
	int qora,daisuu,kotae,kaitou,bangou,monme;
	int seikaisu=0;
	char kyouka[100]={0};
	int ransu[21]={0};
	char toi[21][500]={{0},{0}};
	char marubatu[21][10]={{0},{0}};
	char komento[21][200]={{0},{0}};

	int iaRandarray[MAXRAND];
	int iCounter;
	int iNumRand;
	int iRandKey;
	int iRandVal;

	//乱数を作る
	srand(time(NULL));
	for( iCounter = 0 ; iCounter < MAXRAND ; ++iCounter)
	{
		iaRandarray[ iCounter] = iCounter + 1;
	}
	iNumRand = MAXRAND;
	for( iCounter = 0 ; iCounter < MAXRAND ; ++iCounter)
	{
		iRandKey = rand();
		iRandKey %= iNumRand;
		iRandVal = iaRandarray[iRandKey];
		iaRandarray[ iRandKey ] = iaRandarray[ iNumRand - 1 ];
		--iNumRand;
		ransu[iCounter]=iRandVal;
	}
	
	printf("科目を選択してください。\n");
	printf("1.国語　2.数学　3.英語　4.理科　5.社会\n");
	scanf("%d",&k);
	switch(k)
	{
		case 1:
			strcpy(kyouka,"kokugo.txt");
			kkg++;
			break;
		case 2:
			strcpy(kyouka,"math.txt");
			sgk++;
			break;
		case 3:
			strcpy(kyouka,"English.txt");
			eng++;
			break;
		case 4:
			strcpy(kyouka,"rika.txt");
			rk++;
			break;
		case 5:
			strcpy(kyouka,"social.txt");
			scl++;
			break;
		default:
			printf("入力が正しくありません。\n");
			break;
	}
	fp = fopen(kyouka,"r");
	if(fp == NULL)
	{
		printf("問題のテキストファイルが見つかりません。\n");
	}
	if(k==4)
	{
		for(daisuu=0;daisuu<20;daisuu++)
		{
			for(qora=1;qora<4;qora++)
			{
				i=0;
				while((chr = fgetc(fp))!='/')
				{
					if(chr =='\n')
					{
						break;
					}
					switch(qora)
					{
						case 1:
							toi[daisuu][i]=chr;
							break;
						case 2:
							marubatu[daisuu][i]=chr;
							break;
						case 3:
							komento[daisuu][i]=chr;
							break;
					}
					i++;
				}
			}
		}
	}else
	{
		for(daisuu=0;daisuu<20;daisuu++)
		{
			for(qora=1;qora<4;qora++)
			{
				i=0;
				while((chr=fgetc(fp))!='\n')
				{
					switch(qora)
					{
						case 1:
							toi[daisuu][i]=chr;
							break;
						case 2:
							marubatu[daisuu][i]=chr;
							break;
						case 3:
							komento[daisuu][i]=chr;
							break;
					}
					i++;
				}
			}
		}
	}

	for(i=0;i<20;i++)
	{
		bangou=ransu[i]-1;
		monme=i+1;
		printf("\n%d問目:",monme);
		printf("%s\n",toi[bangou]);
		printf(" ○ なら１、 × なら２を入力してください。\n");
		scanf("%d",&kaitou);
		if((strcmp(marubatu[bangou],"○")==0) || (strcmp(marubatu[bangou],"1")==0))
			kotae=1;
		else if((strcmp(marubatu[bangou],"×")==0) || (strcmp(marubatu[bangou],"2")==0))
			kotae=2;
		else if(kaitou==kotae)
		{
			printf("正解!\n");
			seikaisu++;
		}else
		{
			printf("残念!　正解は");
			if(kotae==1)
				printf("○ です!\n");
			else
				printf("× です!\n");
		}
		if(kotae==2)
			printf("正しい答えは、%s\n",komento[bangou]);
	}
	printf("お疲れ様でした。今回の成績は20問中%d問正解です！\n",seikaisu);
	fclose(fp);
}

int sougou()
{
	FILE *fp;
	FILE *kokugo;
	FILE *rika;
	FILE *social;
	FILE *math;
	FILE *English;
	FILE *sougou;
	char c;
	int error=0;
	char toi[200],kotae[100],marubatu[10];
	int kaitou,read,i,j,hikaku;
	
	/*問題統合*/
	kokugo = fopen("kokugo.txt","r");
	rika = fopen("rika.txt","r");
	social = fopen("social.txt","r");
	math = fopen("math.txt","r");
	English = fopen("English.txt","r");
	sougou = fopen("sougou.txt","w");
	if(kokugo==NULL || rika==NULL || social==NULL || math==NULL || English==NULL || sougou==NULL)
		error=1;

	if(!error)
	{
		while(1)
		{
			/*国語の問題をコピー */
			fread(&c,sizeof(c),1,kokugo);
			if(feof(kokugo))
				break;
			else if(ferror(kokugo))
			{
				error=1;
				break;
			}
			fwrite(&c,sizeof(c),1,sougou);
			if(ferror( sougou))
			{
				error=1;
				break;
			}
		}
		
		while(1)
		{
			/*理科の問題をコピー*/
			fread(&c,sizeof(c),1,rika);
			if(feof(rika))
				break;
			if(ferror(rika))
			{
				error=1;
				break;
			}
			fwrite(&c,sizeof(c),1,sougou);
			if(ferror(sougou))
			{
				error=1;
				break;
			}
		}
		
		while(1)
		{
			/* 社会の問題をコピー */
			fread(&c,sizeof(c),1,social);
			if(feof(social))
				break;
			if(ferror(social))
			{
				error=1;
				break;
			}
			fwrite( &c, sizeof(c), 1, sougou );
			if( ferror( sougou ) ){
				error = 1;
				break;
			}
		}
		
				while( 1 ){
			/*数学の問題をコピー */
			fread( &c, sizeof(c), 1, math );
			if( feof( math ) ){
				break;
			}
			if( ferror( math ) ){
				error = 1;
				break;
			}
			fwrite( &c, sizeof(c), 1, sougou );
			if( ferror( sougou ) ){
				error = 1;
				break;
			}
		}
		
		while( 1 ){
			/*英語の問題をコピー */
			fread( &c, sizeof(c), 1, English );
			if( feof( English ) ){
				break;
			}
			if( ferror( English ) ){
				error = 1;
				break;
			}
			fwrite( &c, sizeof(c), 1, sougou );
			if( ferror( sougou ) ){
				error = 1;
				break;
			}
		}
		
	}

	if( sougou != NULL ){
		if( fclose( sougou ) == EOF ){
			error = 1;
		}
	}
	if( kokugo != NULL ){
		if( fclose( kokugo ) == EOF ){
			error = 1;
		}
	}
	if( rika != NULL ){
		if( fclose( rika ) == EOF ){
			error = 1;
		}
	}
	if( social != NULL ){
		if( fclose( social ) == EOF ){
			error = 1;
		}
	}
	if( math != NULL ){
		if( fclose( math ) == EOF ){
			error = 1;
		}
	}
	if( English != NULL ){
		if( fclose( English ) == EOF ){
			error = 1;
		}
	}
	if( error ){
		fputs( "問題ファイルが正しくありません。\n", stderr );
	}

	
	fp=fopen("sougou.txt","r");

	if(fp == NULL){
		printf("ファイルを開けません！\n");
		exit(1);
	}


	MAXRAND = 100;
	printf("\n");


/*問題出題*/
	printf("問題に○ × (○ → 1,× → 2)答えてください。\n");
	rand2();
		
	for(i=0;i<MAXRAND;i++){
		
		fp=fopen("sougou.txt","r");
		
			if(fp == NULL){
				printf("ファイルを開けません！\n");
				exit(1);
			}
		read = rand_s[i]*3-2;
		j=1;
			while(j<read){
				fgets(toi,200,fp);
				j++;
			}
		
		fgets(toi,200,fp);
		fgets(marubatu,10,fp);
		hikaku = marubatu[0] - '0';

		fgets(kotae,200,fp);
	
		printf("問%d %s",i+1,toi);
		printf("答　");
		
		/*ループバグ対策*/
		while (scanf(" %d", &kaitou) != 1) {
	       scanf("%*s");
	            if (feof(stdin) != 0) {
	                return 1;
	            }
			}
		if(kaitou==1||kaitou==2){
		}else{
			for(;;){
				scanf(" %d", &kaitou);
				if(kaitou==1||kaitou==2){
					break;
				}
			}
		}

			if(kaitou==hikaku){
				printf("正解‼\n\n");
				}
			else{
				printf("不正解 %s\n",kotae);
				
				FILE* hozon;
				hozon=fopen("hozon.txt","a");
				fprintf(hozon,"%s",toi);
				fprintf(hozon,"%s",marubatu);
				fprintf(hozon,"%s",kotae);
				fclose(hozon);
				}
				fclose(fp);
			}
return 0;
}

/* 乱数取得 */
void rand2(){
int iaRandarray[MAXRAND]; /*乱数候補収納用変数*/
int iCounter; /*ループカウンタ用変数*/
int iNumRand; /*残り乱数候補数*/
int iRandKey; /*乱数候補取得用変数*/
int iRandVal; /*乱数の取得用変数*/

srand(time(NULL));
for( iCounter = 0 ; iCounter < MAXRAND ; ++iCounter){
iaRandarray[ iCounter] = iCounter + 1;
}
iNumRand = MAXRAND;
for( iCounter = 0 ; iCounter < MAXRAND ; ++iCounter){
iRandKey = rand();
iRandKey %= iNumRand;
iRandVal = iaRandarray[ iRandKey ];
iaRandarray[ iRandKey ] = iaRandarray[ iNumRand - 1 ];
--iNumRand;
rand_s[iCounter] = iRandVal;

}
}

int death()
{
	FILE*fp;
	FILE* kokugo;
	FILE* rika;
	FILE* social;
	FILE* math;
	FILE* English;
	FILE* sougou;
	char c;
	int error = 0;
	char toi[200],kotae[100],marubatu[10];
	int kaitou,read,i,j,hikaku;
	
	/*問題統合*/
	kokugo = fopen( "kokugo.txt", "r" );
	rika = fopen( "rika.txt", "r" );
	social = fopen( "social.txt", "r" );
	math = fopen( "math.txt", "r" );
	English = fopen( "English.txt", "r" );
	sougou = fopen( "sougou.txt", "w" );
	if(kokugo==NULL || rika==NULL || social==NULL || math==NULL || English==NULL || sougou==NULL){
		error = 1;
	}

	if( !error ){
		while( 1 ){
			/*国語の問題をコピー */
			fread( &c, sizeof(c), 1, kokugo );
			if( feof( kokugo ) ){
				break;
			}
			if( ferror( kokugo ) ){
				error = 1;
				break;
			}
			fwrite( &c, sizeof(c), 1, sougou );
			if( ferror( sougou ) ){
				error = 1;
				break;
			}
		}
		
		while( 1 ){
			/* 理科の問題をコピー */
			fread( &c, sizeof(c), 1, rika);
			if( feof( rika ) ){
				break;
			}
			if( ferror( rika ) ){
				error = 1;
				break;
			}
			fwrite( &c, sizeof(c), 1, sougou );
			if( ferror( sougou ) ){
				error = 1;
				break;
			}
		}
		
		while( 1 ){
			/* 社会の問題をコピー */
			fread( &c, sizeof(c), 1, social );
			if( feof( social ) ){
				break;
			}
			if( ferror( social ) ){
				error = 1;
				break;
			}
			fwrite( &c, sizeof(c), 1, sougou );
			if( ferror( sougou ) ){
				error = 1;
				break;
			}
		}
		
				while( 1 ){
			/*数学の問題をコピー */
			fread( &c, sizeof(c), 1, math );
			if( feof( math ) ){
				break;
			}
			if( ferror( math ) ){
				error = 1;
				break;
			}
			fwrite( &c, sizeof(c), 1, sougou );
			if( ferror( sougou ) ){
				error = 1;
				break;
			}
		}
		
		while( 1 ){
			/*英語の問題をコピー */
			fread( &c, sizeof(c), 1, English );
			if( feof( English ) ){
				break;
			}
			if( ferror( English ) ){
				error = 1;
				break;
			}
			fwrite( &c, sizeof(c), 1, sougou );
			if( ferror( sougou ) ){
				error = 1;
				break;
			}
		}
		
	}

	if( sougou != NULL ){
		if( fclose( sougou ) == EOF ){
			error = 1;
		}
	}
	if( kokugo != NULL ){
		if( fclose( kokugo ) == EOF ){
			error = 1;
		}
	}
	if( rika != NULL ){
		if( fclose( rika ) == EOF ){
			error = 1;
		}
	}
	if( social != NULL ){
		if( fclose( social ) == EOF ){
			error = 1;
		}
	}
	if( math != NULL ){
		if( fclose( math ) == EOF ){
			error = 1;
		}
	}
	if( English != NULL ){
		if( fclose( English ) == EOF ){
			error = 1;
		}
	}
	if( error ){
		fputs( "問題ファイルが正しくありません。\n", stderr );
	}

	
	fp=fopen("sougou.txt","r");

	if(fp == NULL){
		printf("ファイルを開けません！\n");
		exit(1);
	}


	MAXRAND = 100;
	printf("\n");


/*問題出題*/
	printf("問題に○ × (○ → 1,× → 2)答えてください。\n");
	rand2();
		
	for(i=0;i<MAXRAND;i++){
		
		fp=fopen("sougou.txt","r");
		
			if(fp == NULL){
				printf("ファイルを開けません！\n");
				exit(1);
			}
		read = rand_s[i]*3-2;
		j=1;
			while(j<read){
				fgets(toi,200,fp);
				j++;
			}
		
		fgets(toi,200,fp);
		fgets(marubatu,10,fp);
		hikaku = marubatu[0] - '0';

		fgets(kotae,200,fp);
	
		printf("問%d %s",i+1,toi);
		printf("答　");
		
		/*ループバグ対策*/
		while (scanf(" %d", &kaitou) != 1) {
	       scanf("%*s");
	            if (feof(stdin) != 0) {
	                return 1;
	            }
			}
		if(kaitou==1||kaitou==2){
		}else{
			for(;;){
				scanf(" %d", &kaitou);
				if(kaitou==1||kaitou==2){
					break;
				}
			}
		}

			if(kaitou==hikaku){
				printf("正解‼\n\n");
				}
			else{
				printf("不正解 %s\n",kotae);
				
				FILE* hozon;
				hozon=fopen("hozon.txt","a");
				fprintf(hozon,"%s",toi);
				fprintf(hozon,"%s",marubatu);
				fprintf(hozon,"%s",kotae);
				fclose(hozon);
				printf("%d問正解しました!\n",i);
				break;
				}
				fclose(fp);
			}
return 0;
}


int nigate()
{

	//変数//
	char toi[200],kotae[100],kazoeru[200],marubatu[10],hikaku;
	int kaitou,read;
	int l,j,i;
	int narabi;
    char buf[256];
    FILE*fp3;
//苦手数表示//
fp3=fopen("hozon.txt","r");

    if(fp3 == NULL){
    		printf("ファイルを開けません！\n");
    		exit(1);
    }

    gyou4=0;
	
    while(fgets(kazoeru,sizeof(kazoeru),fp3)!=NULL){
    	gyou4++;
    }//問題数数える

fclose(fp3);

gyou4=gyou4/3;

printf("ただいま,苦手問題は%d問です\n",gyou4);

MAXRAND = gyou4; //ランダム出だす数上限

printf("\n");

    if(gyou4<1){
		  printf("おめでとう\n");
	}else{
	    
	  

	//問題出題//
	printf("問題に○ × (○ → 1,× → 2)で答えてください。\n\n");
	
	
	rand2();    //ランダム数字生成
		
    l=0;
    
		for(i=0;i<gyou4;i++){        // 問題数分回す
		
		    fp3=fopen("hozon.txt","r");
		
		        read = rand_s[i]*3-2;       //問題のある行
		        
		        j=1;
		        
			        while(j<read){      //問題のある行までポインタを移動
				        fgets(toi,200,fp3);  
				        j++;
			        }
		
		        fgets(toi,200,fp3);
			    fgets(marubatu,10,fp3);
		        hikaku = marubatu[0] - '0';     //文字列を数字に
                fgets(kotae,200,fp3);
	
	
		        printf("問%d %s",i+1,toi);
		       
		        
		        for(;;){                    //エラー処理
		        printf("答　");
		        
    			    if(scanf("%d",&kaitou)==0){
    			        printf("入力が間違っています。解きなおしてください\n");
			            (void)fgets(buf,sizeof buf,stdin);
    			    }else if(kaitou != 1 && kaitou != 2){
			                printf("入力が間違っています。解きなおしてください\n");
			        }
			        else
			            break;
		        }       
			        if(kaitou==hikaku){     //正解
				        printf("正解‼\n\n");
				        fclose(fp3);
				        kesu[l]=read;   //  正解行
				        l++;    //正解数
				    }
			        else{           // 間違い
				        printf("不正解 %s\n",kotae);
				        fclose(fp3);
			        } 
		}
	
	for(j=0;j<20;j++){          //削除時削除指定した行が変わらないよう降順に
	    for(i=j+1;i<20;i++){
	        if(kesu[j]<kesu[i]){
	            narabi=kesu[j];
	            kesu[j]=kesu[i];
	            kesu[i]=narabi;
	        }
	    }
	}
	
gyou4=gyou4*3;
gyou4=gyou4+3;//gyou4を削除のとき減らすけど1回目は減らさなくていいから

	for(x=0;x<l;x++){
	    gyou4=gyou4-3;        //行も減らす
	    sakuzyo();      //正解問題を削除
	}
	
fp3=fopen("hozon.txt","r");
    
    gyou4=0;
	
        while(fgets(kazoeru,sizeof(kazoeru),fp3)!=NULL){
	        gyou4++;
        }//問題数数える

fclose(fp3);

gyou4=gyou4/3;

printf("今回は%d問の苦手を克服したよ!\n",l);
printf("ただいま,苦手問題は%d問です\n",gyou4);

}
	
return 0;
}



void sakuzyo()  //削除関数
{
	//変数//
	FILE*fp2;
	FILE*fp;
	int num;
//	char *filename = "output.txt";//ファイル作成後ファイル消すため	
	char toi2[200],kotae2[100],marubatu2[10];
	num=1;
	
	fp=fopen("hozon.txt","r");
	fp2=fopen("output.txt","w");//別ファイルに削除行以外を写す
	

	while(num<kesu[x]){     //消す行までの行をoutput.txtに
		
		fgets(toi2,200,fp);
			
		fgets(marubatu2,10,fp);

		fgets(kotae2,200,fp);
		
		fprintf(fp2,"%s",toi2);
		num++;
		fprintf(fp2,"%s",marubatu2);
		num++;
		fprintf(fp2,"%s",kotae2);
		num++;
	}
		fgets(toi2,200,fp);      //消す行を空打ち
		num++;	
		fgets(marubatu2,10,fp);
        num++;
		fgets(kotae2,200,fp);
	    num++;

	while(num<gyou4){            //消す行以降をoutput.txtに
		fgets(toi2,200,fp);
			
		fgets(marubatu2,10,fp);

		fgets(kotae2,200,fp);
		
		fprintf(fp2,"%s",toi2);
		num++;
		fprintf(fp2,"%s",marubatu2);
		num++;
		fprintf(fp2,"%s",kotae2);
		num++;
	}
	
    fclose(fp2);
	fclose(fp);

	num=1;
	fp2=fopen("output.txt","r");
	fp=fopen("hozon.txt","w");

	
	
	while(num<gyou4-3){          //output.txtから元のファイルに打ち直し
		
		fgets(toi2,200,fp2);
			
		fgets(marubatu2,10,fp2);

		fgets(kotae2,200,fp2);
		
		fprintf(fp,"%s",toi2);
		num++;
		fprintf(fp,"%s",marubatu2);
		num++;
		fprintf(fp,"%s",kotae2);
		num++;
		
	}
	fclose(fp2);
	fclose(fp);

}


void time_attack(){
	int i;

	//乱数発生
	int s_rand[20],q_rand[20];
	MAXRAND = 20;
	rand2();
	for(i=0;i<20;i++) s_rand[i] = rand_s[i]%5;
	rand2();
	for(i=0;i<20;i++) q_rand[i] = rand_s[i];
	
	//問題呼びだしと時間計測
	time_t start,end;
	start = time(NULL);
	for(i=0;i<20;i++){
		if(question(i, s_rand[i], q_rand[i]) == 1)start-=5;
		end = time(NULL);
		printf("ただいま %d秒 \n\n",(int)end-(int)start);
	}
	end = time(NULL);
	printf("記録 %d秒!! \n\n",(int)end-(int)start);
	//問題呼びだしと時間計測
}

int question(int cnt, int sub, int que){	//sub : 科目乱数, que : 問題乱数
	printf("問題に○ × (○ → 1,× → 2)で答えてください。\n");
	//ランダムな科目のファイルオープン***************************************
	FILE *fp;
	
	switch(sub){
		case 0:
		fp=fopen("kokugo.txt","r");
		if(fp == NULL){
			printf("ファイルを開けません！\n");
			exit(1);
		}
		break;
		
		case 1:
		fp=fopen("math.txt","r");
		if(fp == NULL){
			printf("ファイルを開けません！\n");
			exit(1);
		}
		break;
		
		case 2:
		fp=fopen("English.txt","r");
		if(fp == NULL){
			printf("ファイルを開けません！\n");
			exit(1);
		}
		break;
		
		case 3:
		fp=fopen("rika.txt","r");
		if(fp == NULL){
			printf("ファイルを開けません！\n");
			exit(1);
		}
		break;
		
		case 4:
		fp=fopen("social.txt","r");
		if(fp == NULL){
			printf("ファイルを開けません！\n");
			exit(1);
		}
		break;
	}
	//ランダムな科目のファイルオープン*****ここまで***********************
	
	char toi[200],kotae[100],marubatu[10];
	int hikaku, kaitou;
	char buf[256];
	int j = 0, read = que*3-2;	//読みたい問題の最初の行
	while(j<read){	//指定行まで読み進める
		fgets(toi,200,fp);
		j++;
	}
	
	fgets(marubatu,10,fp);
	hikaku = marubatu[0] - '0';
	fgets(kotae,200,fp);
	
	fclose(fp);
	
	//問題出力と正解・不正解判定*****************************************
	printf("問%d %s",cnt+1,toi);
	for(;;){                    //エラー処理
		        printf("答　");
		        
    			    if(scanf("%d",&kaitou)==0){
    			        printf("入力が間違っています。解きなおしてください\n");
			            (void)fgets(buf,sizeof buf,stdin);
    			    }else if(kaitou != 1 && kaitou != 2){
			                printf("入力が間違っています。解きなおしてください\n");
			        }
			        else
			            break;
		        }       
	while(kaitou!=1 && kaitou!=2){	
		printf("'1'か'2'で答えてね！\n");
		printf("答　");
		scanf("%d",&kaitou);
	}

	if(kaitou==hikaku){
		if(hikaku==1) printf("正解！\n");
		else printf("正解！ %s\n",kotae);
		return 0;
	}
	else{
		fp=fopen("hozon.txt","a");	//間違えた問題を保存
		fprintf(fp,"%s",toi);		//
		fprintf(fp,"%s",marubatu);	//
		fprintf(fp,"%s",kotae);		//
		fclose(fp);					//ここまで
		
		printf("残念 \n正解は");
		if(hikaku==1) printf("○\n");
		else printf("× , %s",kotae);
		
		printf("5秒加算");
		return 1;
	}
	//問題出力と正解・不正解判定*****ここまで**************************
}

	 void kiroku(){

		int q=0;
		char day[256],koku[256],su[256],ei[256],sya[256],ri[256],hyaku[256],timen[256],death[256];

		time_t now;
		struct tm *ltm;		
		FILE *fi;
		time( &now );
		ltm = localtime( &now );

		fi = fopen("memory.txt","a");

		fprintf(fi, "%4d/", ltm->tm_year + 1900);
		fprintf(fi, "%2d/", ltm->tm_mon + 1);
		fprintf(fi, "%2d\n", ltm->tm_mday);
		fprintf(fi, "国語：	%d\n", kkg);
		fprintf(fi, "数学：	%d\n", sgk);
		fprintf(fi, "英語：	%d\n", eng);
		fprintf(fi, "社会：	%d\n", scl);
		fprintf(fi, "理科：	%d\n", rk);
		fprintf(fi, "総合100問：%d\n", sg);
		fprintf(fi, "タイムアタック：%d\n", ta);
		fprintf(fi, "デスマッチ：%d\n", dth);
		
		fclose(fi);
		
		fi = fopen("memory.txt","r");
		while(1){
			fgets(day,200,fi);
			fgets(koku,200,fi);
			fgets(su,200,fi);
			fgets(ei,200,fi);
			fgets(sya,200,fi);
			fgets(ri,200,fi);
			fgets(hyaku,200,fi);
			fgets(timen,200,fi);
			fgets(death,200,fi);
			q=q+9;
			if(feof(fi)!=0)	break;
		}
		
		if(q>45)	sakujo2();
	}

void sakujo2()
{
		FILE *fp;
		FILE *fp2;
		int num;
		char day[256],koku[256],su[256],ei[256],sya[256],ri[256],hyaku[256],timen[256],death[256];

		num=1;

		fp=fopen("memory.txt","r");
		    fp2=fopen("output.txt","w");

		            fgets(day,200,fp);
		            num++;
		            fgets(koku,200,fp);
		    		num++;
		            fgets(su,200,fp);
		       		num++;
		            fgets(ei,200,fp);
		       		num++;
		            fgets(sya,200,fp);
		       		num++;
		            fgets(ri,200,fp);
		       		num++;
		            fgets(hyaku,200,fp);
		       		num++;
		            fgets(timen,200,fp);
		       		num++;

		            fgets(death,200,fp);
		       		num++;

		    while(num<54){
		            fgets(day,200,fp);
		            fgets(koku,200,fp);
		            fgets(su,200,fp);
		            fgets(ei,200,fp);
		            fgets(sya,200,fp);
		            fgets(ri,200,fp);
		            fgets(hyaku,200,fp);
		            fgets(timen,200,fp);
		            fgets(death,200,fp);

		            fprintf(fp2,"%s",day);
		            num++;
		            fprintf(fp2,"%s",koku);
		            num++;
		            fprintf(fp2,"%s",su);
		            num++;
		            fprintf(fp2,"%s",ei);
		            num++;
		            fprintf(fp2,"%s",sya);
		            num++;
		            fprintf(fp2,"%s",ri);
		            num++;
		            fprintf(fp2,"%s",hyaku);
		            num++;
		            fprintf(fp2,"%s",timen);
		            num++;
		            fprintf(fp2,"%s",death);
		            num++;
		    }

	   		fclose(fp2);
		    fclose(fp);

		    num=1;
		    fp2=fopen("memory.txt","w");
		    fp=fopen("output.txt","r");

		    while(num<45){
		            fgets(day,200,fp);
		            fgets(koku,200,fp);
		            fgets(su,200,fp);
		            fgets(ei,200,fp);
		            fgets(sya,200,fp);
		            fgets(ri,200,fp);
		            fgets(hyaku,200,fp);
		            fgets(timen,200,fp);
		            fgets(death,200,fp);

		            fprintf(fp2,"%s",day);
		            num++;
		            fprintf(fp2,"%s",koku);
		            num++;
		            fprintf(fp2,"%s",su);
		            num++;
		            fprintf(fp2,"%s",ei);
		            num++;
		            fprintf(fp2,"%s",sya);
		            num++;
		            fprintf(fp2,"%s",ri);
		            num++;
		            fprintf(fp2,"%s",hyaku);
		            num++;
		            fprintf(fp2,"%s",timen);
		            num++;
		            fprintf(fp2,"%s",death);
		            num++;
		    }
		    fclose(fp);
		    fclose(fp2);
	}





int main(){
	int i,n;
	FILE *fp3;
	char str[1024];

	while(1){
	printf("モードを選択してください。\n");
	printf("1.勉強モード　2.勉強の記録　3.苦手克服モード　4.終了\n");
	scanf("%d",&i);
	switch(i){
		case 1:
				printf("モードを選択してください。\n");
				printf("1.各教科モード　2.総合100問モード　3.タイムアタックモード　4.デスマッチモード	5.戻る\n");
				scanf("%d",&n);
				/*isdigit()*/
				switch(n){
					case 1:
							kyoukabetsu();
							break;
					case 2:
							sougou();
							sg++;
							break;
					case 3:
							time_attack();
							ta++;
							break;
					case 4:
							death();
							dth++;
							break;
					case	5:
							break;
					default:
							printf("入力が正しくありません。\n");
							break;
				};
				break;
		case 2:
				kiroku();
				fp3 = fopen("memory.txt", "r");
				while((fgets(str, 256, fp3))!=NULL){
					printf("%s", str);
				}
				fclose(fp3);
				break;
		case 3:
				nigate();
				break;
		case 4:
				return 0;
		default:
				printf("入力が正しくありません。\n");
				break;
	};
	};

	return 0;
}
