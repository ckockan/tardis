#include "vh_heap.h"
#include "vh_divethandler.h"
Heap *g_intersectInterval;



int vh_writeHeap (Heap * heapName)
{
  int count;
  for (count = 0; count < heapName->heapSize; count++)
    {
      printf ("%i %i %i *", heapName->heapArray[count].priorityValue,
	      heapName->heapArray[count].readMappingPtr->locMapLeftEnd,
	      heapName->heapArray[count].readMappingPtr->locMapRightStart);
    }
  printf ("END\n");
}


int vh_copyHeapEl (HeapEl * dest, HeapEl * src)
{
  dest->readMappingPtr = src->readMappingPtr;
  dest->priorityValue = src->priorityValue;
}


int vh_push_heap (Heap * heapName, HeapEl * newEl)
{
  int heapIndex = heapName->heapSize;
  HeapEl tempEl;
  heapName->heapSize++;
  vh_copyHeapEl (&(heapName->heapArray[heapIndex]), newEl);
  heapIndex = heapName->heapSize - 1;;
  while (heapIndex > 0
	 && heapName->heapArray[heapIndex].priorityValue <
	 heapName->heapArray[(heapIndex + 1) / 2 - 1].priorityValue)
    {
      vh_copyHeapEl (&tempEl, &heapName->heapArray[heapIndex]);
      vh_copyHeapEl (&(heapName->heapArray[heapIndex]),
		     &(heapName->heapArray[(heapIndex + 1) / 2 - 1]));
      vh_copyHeapEl (&(heapName->heapArray[(heapIndex + 1) / 2 - 1]), &tempEl);
      heapIndex = (heapIndex + 1) / 2 - 1;
    }
}

int vh_minValue_heap (Heap * heapName)
{
  if (heapName->heapSize > 0)
    return (heapName->heapArray[0].priorityValue);
  else
    return -1000;
}

int vh_heapBubleDown (Heap * heapName)
{
  int heapIndex = 0;
  HeapEl tempEl;
  while ((heapIndex * 2 + 1 < heapName->heapSize
	  && heapName->heapArray[heapIndex].priorityValue >
	  heapName->heapArray[heapIndex * 2 + 1].priorityValue)
	 || (heapIndex * 2 + 2 < heapName->heapSize
	     && heapName->heapArray[heapIndex].priorityValue >
	     heapName->heapArray[heapIndex * 2 + 2].priorityValue))
    {

      if (heapIndex * 2 + 2 < heapName->heapSize)
	{
	  if (heapName->heapArray[heapIndex * 2 + 1].priorityValue >
	      heapName->heapArray[heapIndex * 2 + 2].priorityValue)
	    {
	      vh_copyHeapEl (&tempEl, &(heapName->heapArray[heapIndex]));
	      vh_copyHeapEl (&(heapName->heapArray[heapIndex]),
			     &(heapName->heapArray[heapIndex * 2 + 2]));
	      vh_copyHeapEl (&(heapName->heapArray[heapIndex * 2 + 2]), &tempEl);
	      heapIndex = heapIndex * 2 + 2;

	    }
	  else
	    {
	      vh_copyHeapEl (&tempEl, &(heapName->heapArray[heapIndex]));
	      vh_copyHeapEl (&(heapName->heapArray[heapIndex]),
			     &(heapName->heapArray[heapIndex * 2 + 1]));
	      vh_copyHeapEl (&(heapName->heapArray[heapIndex * 2 + 1]), &tempEl);
	      heapIndex = heapIndex * 2 + 1;
	    }
	}
      else
	{
	  vh_copyHeapEl (&tempEl, &(heapName->heapArray[heapIndex]));
	  vh_copyHeapEl (&(heapName->heapArray[heapIndex]),
			 &(heapName->heapArray[heapIndex * 2 + 1]));
	  vh_copyHeapEl (&(heapName->heapArray[heapIndex * 2 + 1]), &tempEl);
	  heapIndex = heapIndex * 2 + 1;
	}
    }
}

int vh_heap_remove_top (Heap * heapName)
{


  if (heapName->heapSize > 0)
    {
      vh_copyHeapEl (&(heapName->heapArray[0]),
		     &(heapName->heapArray[heapName->heapSize - 1]));
      vh_heapBubleDown (heapName);
      heapName->heapSize--;
    }
}

int vh_addToHeap (DivetRow * readMappingPtr, int priorityValue, Heap * heapName)
{
  HeapEl *newEl;
  newEl = (HeapEl *) malloc (sizeof (HeapEl));
  newEl->readMappingPtr = readMappingPtr;
  newEl->priorityValue = priorityValue;
  vh_push_heap (heapName, newEl);
  free (newEl);
}
