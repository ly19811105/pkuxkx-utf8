// jianjiao.c	by XiaoYao 4/22/99

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("素煎饺", ({"jian jiao", "jiao", "dumpling"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一盘嫩黄脆皮的素煎饺。\n");
		set("unit", "盘");
		set("value", 800);
		set("food_remaining", 5);
		set("food_supply", 10);
	}
}
