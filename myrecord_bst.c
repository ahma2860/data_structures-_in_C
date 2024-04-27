/*
 * your program signature
 */

#include <stdio.h>
#include <math.h>
#include "queue_stack.h"
#include "bst.h"
#include "myrecord_bst.h"

void add_record(BSTDS *ds, RECORD record) {

	if(ds->count==0){
		ds->count++;
		ds->mean=record.score;
		ds->stddev=0;
	}else{
	int n=ds->count;
	float mean=ds->mean;
	float stddev=ds->stddev;
	ds->mean=((n*mean + record.score)/(n+1));
//	printf("\n%f\n",ds->mean);

	ds->stddev=sqrt((((n*(pow(stddev,2)+pow(mean,2))+pow(record.score,2))/(n+1)-pow(ds->mean,2))));
	ds->count++;
	}
bst_insert(&(ds->root) , record);
return;
}

void remove_record(BSTDS *ds, char *name) {
	if(ds->count==1){
			ds->count--;
			ds->mean=0;
			ds->stddev=0;
		}else{
		BSTNODE *p=bst_search(ds->root, name);
		int n=ds->count;
		float mean=ds->mean;
		float stddev=ds->stddev;
		float score=p->data.score;
		ds->mean=((n*mean - score)/(n-1));


		ds->stddev=((pow(stddev,2)+pow(mean,2))*(n)-pow(score,2))/(n-1)-pow(ds->mean,2);
		ds->count--;
		}
	bst_delete(&(ds->root), name);
	return;

}

void clean_bstds(BSTDS *ds) {
  clean_bst(&ds->root);
  ds->count = 0;
  ds->mean = 0;
  ds->stddev = 0;
}
