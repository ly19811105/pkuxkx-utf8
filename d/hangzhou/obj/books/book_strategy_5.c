//strategy第五本
inherit ITEM;
void create()
{
	set_name( "「黄石公三略」",({ "san lue", "book"}));
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long","这是一部从政治谋略上阐明治国之道，从政治与军事的关系上论述克敌制胜的兵书。\n");
		set("value", 3000);
		set("material", "paper");
		set("Strategy_Book_Series",5); 
		set("skill", ([
	  	"name": "strategy",  //name of the skill
 		"exp_required": 20000 , //minimum combat experience required
		"jing_cost": 30 + random(30),// jing cost every time study this
		"difficulty":	30,	// the base int to learn this skill
		"max_skill":	199,	// the maximum level you can learn
		"min_skill":    160
		]) );
	}
}