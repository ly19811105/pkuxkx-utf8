// wineskin.c  酒袋

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name("牛皮酒袋", ({"jiudai", "wineskin", "skin"}));
	set_weight(7000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一个用来装米酒的大酒袋，大概装得八、九升的酒。\n");
		set("unit", "个");
		set("value", 1000);
        set("max_liquid", 60);
	}

	// because a container can contain different liquid
	// we set it to contain wine at the beginning
	set("liquid", ([
		"type": "alcohol",
		"name": "米酒",
        "remaining": 60,
		"drunk_apply": 6,
	]));
}
