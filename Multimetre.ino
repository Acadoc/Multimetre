#include "Multimetre.h"

#if defined(find_dichotomy)
	#define toto 4
#else
	#define toto 0
#endif

//const int *active_channel_tble=NULL;
short active_channel_Pin,tmp_cpt;
int read_value;
char UserCmdIn[15];
char trucdemerde[6] = {'G','e','t','R','e','s'};


void setup() {
  // put your setup code here, to run once:

	//active_chan = 0;

	pinMode(Pin_10,OUTPUT);
	pinMode(Pin_100,OUTPUT);
	pinMode(Pin_1k,OUTPUT);
	pinMode(Pin_10k,OUTPUT);
	pinMode(Pin_100k,OUTPUT);
	pinMode(Pin_1M,OUTPUT);
	pinMode(Pin_10M,OUTPUT);

	digitalWrite(Pin_10,LOW);
	digitalWrite(Pin_100,LOW);
	digitalWrite(Pin_1k,LOW);
	digitalWrite(Pin_10k,LOW);
	digitalWrite(Pin_100k,LOW);
	digitalWrite(Pin_1M,LOW);
	digitalWrite(Pin_10M,LOW);


	Serial.begin(9600);

	DEBUG_PRINT("Go !\n");

	digitalWrite(Pin_10,LOW);
	digitalWrite(Pin_100,LOW);
	digitalWrite(Pin_1k,LOW);
	digitalWrite(Pin_10k,LOW);
	digitalWrite(Pin_100k,LOW);
	digitalWrite(Pin_1M,LOW);
	digitalWrite(Pin_10M,LOW);
	digitalWrite(Pin_100M,LOW);

	/*DEBUG_PRINT( pgm_read_word(TableInterp_V100M+56));
	DEBUG_PRINT("\t end\n");
	DEBUG_PRINT( pgm_read_word(TableInterp_V10M+256));
	DEBUG_PRINT("\t end\n")	;
	DEBUG_PRINT( pgm_read_word(TableInterp_V1M+ 356));
	DEBUG_PRINT("\t end\n")	;
	DEBUG_PRINT( pgm_read_word(TableInterp_V100K+ 456));
	DEBUG_PRINT("\t end\n");
	DEBUG_PRINT( pgm_read_word(TableInterp_V10K+ 556));
	DEBUG_PRINT("\t end\n")	;
	DEBUG_PRINT( pgm_read_word(TableInterp_V1K+ 656));
	DEBUG_PRINT("\t end\n")	;
	DEBUG_PRINT( pgm_read_word(TableInterp_V100+ 756));
	DEBUG_PRINT("\t end\n")	;*/
	//*UserCmdIn = NULL;


}

void loop() {
	// put your main code here, to run repeatedly:
	delay(500);
	for(tmp_cpt=0;tmp_cpt<15;tmp_cpt++)
	{
		UserCmdIn[tmp_cpt]=0;
	}
	ReadAllSerial(UserCmdIn);

	if(*UserCmdIn!=-1)
	{
		UserCmdExe(UserCmdIn);
	}

	//UserCmdExe(trucdemerde);

}
