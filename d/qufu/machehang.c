// 马车店 Zine 2012.8.1
inherit WAGON_SHOP;
void create()
{
        set("short", "中原马车行");
		set("exits", ([
		
		"south" : __DIR__"weststreet3",
		"east" : __DIR__"kongfu",
		]));
		set("price",100);//雇车价格
        ::create();
}

