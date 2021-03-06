#include <stdio.h>
#include <stdlib.h>
#include "vh_buffer.h"
#include "vh_setcover.h"


clusterInBuffer listClusterInBuffer[maxSizeOfBuffer];
int countInBuffer;
float maxScoreInBuffer;



int bestFromBuffer()
{
  int bestSet;
  float bestSetScore=10000000;
  int count;
  for (count=0; count<countInBuffer; count++)
    {
      if (bestSetScore>listClusterInBuffer[count].score)
	{
	  bestSetScore=listClusterInBuffer[count].score;
	  bestSet=count;
	}
    }
  /* FEREYDOUN: do we need the fprintf below? Disabling for now */
  /*
    fprintf( stderr, "The Best From Buffer %g %i\n", bestSetScore, listClusterInBuffer[bestSet].clusterId);
  */
  return listClusterInBuffer[bestSet].clusterId;

}


int emptyBuffer()
{
  countInBuffer=0;
  maxScoreInBuffer=0;
}

int addToBuffer(float score, int clusterId)
{


  if (countInBuffer<maxSizeOfBuffer)
    {
      /*		for (int count=0; count<countInBuffer; count++)
			{
			if (listClusterInBuffer[count].valid==false)
			{
			listClusterInBuffer[count].score=score;
			listClusterInBuffer[count].valid=true;
			if (score > maxScoreInBuffer)
			maxScoreInBuffer=score;
			countInBuffer++;
			return 0;
			}
			}*/

      listClusterInBuffer[countInBuffer].score=score;
      listClusterInBuffer[countInBuffer].clusterId=clusterId;
      countInBuffer++;
      if (score>maxScoreInBuffer)
	maxScoreInBuffer=score;
      return 0;
    }
	
  //fprintf( stderr, "%f %f\n", score, maxScoreInBuffer);
	
  if (score<maxScoreInBuffer)
    {
      int count;
      //	fprintf( stderr, "L66 %f %f %i\n", score, maxScoreInBuffer, clusterId);
      for (count=0; count<maxSizeOfBuffer; count++)
	{
	  if (listClusterInBuffer[count].score==maxScoreInBuffer)
	    {
	      listClusterInBuffer[count].score=score;
	      listClusterInBuffer[count].clusterId=clusterId;
	      //listClusterInBuffer[count].valid=true;
	      maxScoreInBuffer=0;
	      int count2;
	      for (count2=0; count2<maxSizeOfBuffer; count2++)
		{
		  if (listClusterInBuffer[count2].score > maxScoreInBuffer)
		    {
		      maxScoreInBuffer= listClusterInBuffer[count2].score;	
		    }
		}
	      return 0;
	    }
	}
		
    }

}
