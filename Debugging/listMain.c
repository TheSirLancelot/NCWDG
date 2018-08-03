#include "myList.h"

int main(int argc, char * argv[]) {

	clientStruct * client1 = createClientStruct(1, "111111111");
	clientStruct * client2 = createClientStruct(2, "222222222");
	clientStruct * client3 = createClientStruct(3, "333333333");
	clientStruct * temp = NULL;
	list * myList = NULL;
	int findVal1 = 2;
	int findVal2 = 3;
	int findVal3 = 1;

	myList = initializeList((void *) client1);
	addMember(&myList, (void *) client2);
	addMember(&myList, (void *) client3);

	temp = (clientStruct *) find_member(&myList, &(findVal1), cmpFunc);
	printf("%p\t%p\n", temp, myList);

	removeMember(&myList, &(findVal1), cmpFunc);//remove middle
	removeMember(&myList, &(findVal2), cmpFunc);//remove tail
	removeMember(&myList, &(findVal3), cmpFunc);//remove head

}
