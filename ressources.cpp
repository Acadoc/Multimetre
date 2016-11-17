#include "Multimetre.h"


 const int TableInterp_V100M[] PROGMEM  = INTERP_TABLE_V100M;
 const int TableInterp_V10M[]  PROGMEM 	= INTERP_TABLE_V10M;
 const int TableInterp_V1M[]   PROGMEM 	= INTERP_TABLE_V1M;
 const int TableInterp_V100K[] PROGMEM  = INTERP_TABLE_V100K;
 const int TableInterp_V10K[]  PROGMEM 	= INTERP_TABLE_V10K;
 const int TableInterp_V1K[]   PROGMEM 	= INTERP_TABLE_V1K;
 const int TableInterp_V100[]  PROGMEM 	= INTERP_TABLE_V100;
 const int TableInterp_V10[]   PROGMEM	= INTERP_TABLE_V10;
 short active_chan;

/****************************** ReadAllSerial	******************************/
void ReadAllSerial(char *output_ptr)
{
	char read_char;
	int pending_char;
	int cpt;
	String tmp_str;

	tmp_str = "";

	pending_char = Serial.available();


	if(pending_char != 0)
	{	
		for(cpt = 0; (cpt<15) && (cpt<pending_char); cpt++)
		{
			*(output_ptr + cpt) = Serial.read();
			tmp_str = tmp_str + *(output_ptr + cpt);
		}

		for(cpt = pending_char; (cpt<15); cpt++)
		{
			*(output_ptr + cpt) = 0;
		}

		DEBUG_PRINT("\nRecieved : ");
		DEBUG_PRINT(tmp_str);
	}
	else
	{
		*output_ptr = -1;
	}
}

/****************************************************************************/


/****************************** GetRes	******************************/
float GetRes(short active_chan)
{
	float tmp_return;
	switch(active_chan)
	{
		case Pin_10 :
		{	
			/*resistance is given with an accuracy of 1% of the mesure range, but calibration tables are written with*/
			/* a fix dot. So the real value is " table_elt * mesure_range / 100" */
			tmp_return = float(pgm_read_word(TableInterp_V10+(unsigned int)(analogRead(0))))/10.0;
			DEBUG_PRINT("\nActive chan is 10, value read is : ");
			DEBUG_PRINT(pgm_read_word(TableInterp_V10+(unsigned int)(analogRead(0))));
			DEBUG_PRINT("\tActive chan is 10, value read is : ");
			DEBUG_PRINT(tmp_return);
			DEBUG_PRINT(" .\n");
			return tmp_return;
			break;
		}
		case Pin_100 :
		{	
			tmp_return = float(pgm_read_word(TableInterp_V100+(unsigned int)(analogRead(0))));
			DEBUG_PRINT("\nActive chan is 100, value read is : ");
			DEBUG_PRINT(pgm_read_word(TableInterp_V100+(unsigned int)(analogRead(0))));
			DEBUG_PRINT("\tActive chan is 100, value read is : ");
			DEBUG_PRINT(tmp_return);
			DEBUG_PRINT(" .\n");
			return tmp_return;
			break;
		}
		case Pin_1k :
		{	
			tmp_return = float(pgm_read_word(TableInterp_V1K+(unsigned int)(analogRead(0))))/100.0;
			DEBUG_PRINT("\nActive chan is 1k, value read is : ");
			DEBUG_PRINT(pgm_read_word(TableInterp_V1K+(unsigned int)(analogRead(0))));
			DEBUG_PRINT("\tActive chan is 1k, value read is : ");
			DEBUG_PRINT(tmp_return);
			DEBUG_PRINT("k .\n");
			return tmp_return;
			break;
		}
		case Pin_10k :
		{	
			tmp_return = float(pgm_read_word(TableInterp_V10K+(unsigned int)(analogRead(0))))/10.0;
			DEBUG_PRINT("\nActive chan is 10k, value read is : ");
			DEBUG_PRINT(pgm_read_word(TableInterp_V10K+(unsigned int)(analogRead(0))));
			DEBUG_PRINT("\tActive chan is 10k, value read is : ");
			DEBUG_PRINT(tmp_return);
			DEBUG_PRINT("k .\n");
			return tmp_return;
			break;
		}
		case Pin_100k :
		{	
			tmp_return = float(pgm_read_word(TableInterp_V100K+(unsigned int)(analogRead(0))));
			DEBUG_PRINT("\nActive chan is 100k, value read is : ");
			DEBUG_PRINT(pgm_read_word(TableInterp_V100K+(unsigned int)(analogRead(0))));
			DEBUG_PRINT("\tActive chan is 100k, value read is : ");
			DEBUG_PRINT(tmp_return);
			DEBUG_PRINT("k .\n");
			return tmp_return;
			break;
		}
		case Pin_1M :
		{	
			tmp_return = float(pgm_read_word(TableInterp_V1M+(unsigned int)(analogRead(0))))/100.0;
			DEBUG_PRINT("\nActive chan is 1M, value read is : ");
			DEBUG_PRINT(pgm_read_word(TableInterp_V1M+(unsigned int)(analogRead(0))));
			DEBUG_PRINT("\tActive chan is 1M, value read is : ");
			DEBUG_PRINT(tmp_return);
			DEBUG_PRINT("M .\n");
			return tmp_return;
			break;
		}
		case Pin_10M :
		{	
			tmp_return = float(pgm_read_word(TableInterp_V10M+(unsigned int)(analogRead(0))))/10.0;
			DEBUG_PRINT("\nActive chan is 10M, value read is : ");
			DEBUG_PRINT(pgm_read_word(TableInterp_V10M+(unsigned int)(analogRead(0))));
			DEBUG_PRINT("\tActive chan is 10M, value read is : ");
			DEBUG_PRINT(tmp_return);
			DEBUG_PRINT("M .\n");
			return tmp_return;
			break;
		}
		case Pin_100M :
		{	
			tmp_return = float(pgm_read_word(TableInterp_V100M+(unsigned int)(analogRead(0))));
			DEBUG_PRINT("\nActive chan is 100M, value read is : ");
			DEBUG_PRINT(pgm_read_word(TableInterp_V100M+(unsigned int)(analogRead(0))));
			DEBUG_PRINT("\tActive chan is 100M, value read is : ");
			DEBUG_PRINT(tmp_return);
			DEBUG_PRINT("M .\n");
			return tmp_return;
			break;
		}
		default:
		{
			DEBUG_PRINT("\nno chanel activated \n");
			return -1;
			break;
		}
	}
}
/****************************************************************************/


/****************************** UserCmdExe	******************************/
void UserCmdExe(char *user_cmd)
{
	String tmp_cmd;
	String tmp_cmd_value;
	short u, v;
	unsigned int tmp_val;
	bool EndOfCmd,EndOfVal;


	/* here we consider that a command uses a maximum of 15 char. */
	EndOfCmd = FALSE;
	EndOfVal = FALSE;
	tmp_cmd="";
	tmp_cmd_value="";

	/*get the type of command */



	for( u=0; (u<15) && (user_cmd[u] >1) && (EndOfCmd == FALSE); u++)
	{
		if((user_cmd[u]!='(') && (EndOfCmd==FALSE))
		{
			/*DEBUG_PRINT("\nuser_cmd[");
			DEBUG_PRINT(u);
			DEBUG_PRINT("] :");
			DEBUG_PRINT(user_cmd[u]);*/

			tmp_cmd = tmp_cmd +user_cmd[u];

			/*DEBUG_PRINT("\t tmp_cmd:");
			DEBUG_PRINT(tmp_cmd);
			DEBUG_PRINT(".");*/
		}
		else if(EndOfCmd==FALSE)
		{
			/*DEBUG_PRINT("\nEndOfCmd\nuser_cmd[");
			DEBUG_PRINT(u);
			DEBUG_PRINT("] :");
			DEBUG_PRINT(user_cmd[u]);*/

			EndOfCmd = TRUE;
			v=u+1;
		}
	}

	DEBUG_PRINT("\n tmp_cmd:");
	DEBUG_PRINT(tmp_cmd);
	DEBUG_PRINT(".\n");

	/* get the optional value of the command*/
	for( u=v; (u<15) && (user_cmd[u] != 0) && (EndOfVal==FALSE); u++)
	{
		if((user_cmd[u]!=')') && (EndOfVal==FALSE))
		{
			/*DEBUG_PRINT("\nuser_cmd[");
			DEBUG_PRINT(u);
			DEBUG_PRINT("] :");
			DEBUG_PRINT(user_cmd[u]);*/

			tmp_cmd_value = tmp_cmd_value + user_cmd[u];

		/*	DEBUG_PRINT("\t tmp_cmd_value:");
			DEBUG_PRINT(tmp_cmd_value);
			DEBUG_PRINT(".");*/
		}
		else if(EndOfVal==FALSE)
		{
			/*DEBUG_PRINT("\nEnfOfVal\nuser_cmd[");
			DEBUG_PRINT(u);
			DEBUG_PRINT("] :");
			DEBUG_PRINT(user_cmd[u]);*/
			EndOfVal = TRUE;
			v=u;
		}
	}

	if ( (EndOfVal = TRUE) && (EndOfCmd = TRUE) )
	{
		/* there can't ben"switch" operand on String, so only if and else if are used */


		/*SetPinOn*/
		if(tmp_cmd=="SetPinOn")
		{
			if((tmp_cmd_value.toInt()>=0)||(tmp_cmd_value.toInt()<=NB_DIO))
			{
				digitalWrite(tmp_cmd_value.toInt(),HIGH);
				DEBUG_PRINT("\nPin Set ON : ");
				DEBUG_PRINT(tmp_cmd_value.toInt());
				DEBUG_PRINT(" .\n");
			}
			else
			{
				DEBUG_PRINT("\nInvalid PIN :");
				DEBUG_PRINT(tmp_cmd_value.toInt());
				DEBUG_PRINT(".\n");
			}
		}
		/*SetPinOff*/
		else if(tmp_cmd=="SetPinOff")
		{
			if((tmp_cmd_value.toInt()>=0)||(tmp_cmd_value.toInt()<=NB_DIO))
			{
				digitalWrite(tmp_cmd_value.toInt(),LOW);
				DEBUG_PRINT("\nPin Set OFF : ");
				DEBUG_PRINT(tmp_cmd_value.toInt());
				DEBUG_PRINT(" .\n");
			}
			else
			{
				DEBUG_PRINT("\nInvalid PIN :");
				DEBUG_PRINT(tmp_cmd_value.toInt());
				DEBUG_PRINT(".\n");
			}
		}
		/*SetChan*/
		else if(tmp_cmd=="SetChan")
		{

			digitalWrite(Pin_10,LOW);
			digitalWrite(Pin_100,LOW);
			digitalWrite(Pin_1k,LOW);
			digitalWrite(Pin_10k,LOW);
			digitalWrite(Pin_100k,LOW);
			digitalWrite(Pin_1M,LOW);
			digitalWrite(Pin_10M,LOW);
			digitalWrite(Pin_100M,LOW);

			delay(100);

			switch(tmp_cmd_value.toInt())
			{
				case Pin_10 :
				{	
					digitalWrite(Pin_10,HIGH);
					active_chan = Pin_10;
					digitalWrite(tmp_cmd_value.toInt(),HIGH);
					DEBUG_PRINT("\nChan 10 Set ON : ");
					DEBUG_PRINT(" .\n");
					break;
				}

				case Pin_100 :
				{
					digitalWrite(Pin_100,HIGH);
					active_chan = Pin_100;
					digitalWrite(tmp_cmd_value.toInt(),HIGH);
					DEBUG_PRINT("\nChan 100 Set ON : ");
					DEBUG_PRINT(" .\n");
					break;
				}

				case Pin_1k :
				{
					digitalWrite(Pin_1k,HIGH);
					active_chan = Pin_1k;
					digitalWrite(tmp_cmd_value.toInt(),HIGH);
					DEBUG_PRINT("\nChan 1k Set ON : ");
					DEBUG_PRINT(" .\n");
					break;
				}

				case Pin_10k :
				{
					digitalWrite(Pin_10k,HIGH);
					active_chan = Pin_10k;
					digitalWrite(tmp_cmd_value.toInt(),HIGH);
					DEBUG_PRINT("\nChan 10k Set ON : ");
					DEBUG_PRINT(" .\n");
					break;
				}

				case Pin_100k :
				{
					digitalWrite(Pin_100k,HIGH);
					active_chan = Pin_100k;
					digitalWrite(tmp_cmd_value.toInt(),HIGH);
					DEBUG_PRINT("\nChan 100k Set ON : ");
					DEBUG_PRINT(" .\n");
					break;
				}

				case Pin_1M :
				{
					digitalWrite(Pin_1M,HIGH);
					active_chan = Pin_1M;
					digitalWrite(tmp_cmd_value.toInt(),HIGH);
					DEBUG_PRINT("\nChan 1M Set ON : ");
					DEBUG_PRINT(" .\n");
					break;
				}

				case Pin_10M :
				{
					digitalWrite(Pin_10M,HIGH);
					active_chan = Pin_10M;
					digitalWrite(tmp_cmd_value.toInt(),HIGH);
					DEBUG_PRINT("\nChan 10M Set ON : ");
					DEBUG_PRINT(" .\n");
					break;
				}

				case Pin_100M :
				{
					digitalWrite(Pin_100M,HIGH);
					active_chan = Pin_100M;
					digitalWrite(tmp_cmd_value.toInt(),HIGH);
					DEBUG_PRINT("\nChan 100M Set ON : ");
					DEBUG_PRINT(" .\n");
					break;
				}
				default:
				{
					active_chan = 0;
					DEBUG_PRINT("\nnot a right chanel :");
					DEBUG_PRINT(tmp_cmd_value.toInt());
					DEBUG_PRINT("\n");
					break;
				}

				digitalWrite(tmp_cmd_value.toInt(),LOW);
				DEBUG_PRINT("\nPin Set OFF : ");
				DEBUG_PRINT(tmp_cmd_value.toInt());
				DEBUG_PRINT(" .\n");
			}
		}

		/*GetAnalog*/
		else if(tmp_cmd=="GetAnalog")
		{
			DEBUG_PRINT("\nAnalog Read : ");
			DEBUG_PRINT(analogRead(0));
			DEBUG_PRINT(" .\n");
		}

		/*GetRes*/
		else if(tmp_cmd=="GetRes")
		{
			DEBUG_PRINT("\nAnalog Read : ");
			DEBUG_PRINT(analogRead(0));

			(void) (GetRes(active_chan));
		}
		/* not supported cmd */
		else
		{

				DEBUG_PRINT("\nInvalid command :");
				DEBUG_PRINT(tmp_cmd);
				DEBUG_PRINT(".\n");
		}

	}
}

/****************************************************************************/

/*
const int find_dichotomy(const int value_to_find, const int *table_to_parse)
{
	const int return_value = table_to_parse[value_to_find];
	return return_value;
}
*/