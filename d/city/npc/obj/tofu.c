// tofu.c 豆腐

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("翡翠豆腐", ({"doufu", "tofu"}));
	set_weight(400);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一块水灵灵的大豆腐，嫩的令人不禁想到阿庆嫂的脸蛋儿。\n");
		set("unit", "块");
             set("value", 600);
		set("food_remaining", 5);
             //set("food_supply", 30);
		set("food_supply", 100);
	}
}
