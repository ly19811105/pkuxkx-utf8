// guiquan.c 土匪窝
// by llin

inherit ROOM;

void create()
{
	set("short", "土匪窝");
	set("long", 
"这是一个阴森森的岩洞，四处烧着松明火把，仍然显得十\n"
"分阴暗。借着火光可以看到四面岩壁上挂着几块红布，贴着数\n"
"个“喜”字。与阴暗的岩洞极不相称。洞口有一个黑粗大汉坐\n"
"在一张破破烂烂的太师椅上，色迷迷的看着你，真是恶心。\n"
	);

	set("exits", ([
		"out" : __DIR__"tufeiwo3",
	]));
	set("objects",([
			__DIR__"npc/tufeitou.c" : 1,
		]));
	setup();
}
int valid_leave(object me,string dir)
{
    if ( dir=="out" && objectp(present("tufei tou",environment(me)))
    && living(present("tufei tou",environment(me))))
        return notify_fail("土匪头咧开大嘴狞笑一声：嘿嘿，既然来了这里，就别想走了。\n");
    return ::valid_leave(me,dir);
}
