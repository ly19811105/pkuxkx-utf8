// 马车店 Zine 2012.8.1
inherit WAGON_SHOP;
void create()
{
        set("short", "边塞马车行");
		set("exits", ([
		
		"east" : __DIR__"guandaos1",
		
		]));
		set("price",100);//雇车价格
        ::create();
}
