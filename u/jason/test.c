#include <ansi.h>
int test(string arg)
{
    shout(BMAG""HIY"八卦之王\n"NOR);
    return 1;
}

void testled()
{
	string test="";
	test = set_bit(test,1);
	//printf("haha:"+test);
	printf("test bit:%d\n",test_bit(test,1));
}

void test2(string code)
{
    object ob = load_object("/d/parties/public/obj/real.c");
    mapping* real_estate = ob->real_estate();
    real_estate[5]["entry_code"] = code;
    ob->save_entry(real_estate);
}