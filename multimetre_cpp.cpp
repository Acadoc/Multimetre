#ifndef Multimetre_h 
	#include "Multimetre.h"
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

#endif