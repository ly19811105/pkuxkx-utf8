void test()
{
	object * temp = children("/u/boost/test.c");
	int i;
	for( i = 0; i < sizeof(temp); i++)
		destruct(temp[i]);
}
