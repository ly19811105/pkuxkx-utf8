//wuguan_dating.c

//by zgbl

//2009.8.15 
inherit ROOM;
void create()
{
set("short", "武馆大厅");
set("long", @LONG
这里是太乙武馆的大厅，北墙挂着一块匾(bian)，倚墙放着一张太师椅，太
师椅上坐着一个鹤发童颜的花甲老者。左右各有一个年轻人侍立，看来就是武馆
弟子了。
LONG );
set("exits",  ([
        "north"  :  __DIR__"wuguan_damen",
        "east"   : __DIR__"wuguan_xiuxi",
        "west"   : __DIR__"wuguan_liangong",
      ]));
set("item_desc", ([
   	"bian":"  ==================================\n‖                                  ‖\n‖          太  乙  正  道          ‖\n‖                                  ‖\n  ==================================\n",
   ]) );set("objects",([
	       __DIR__"npc/dizi.c":2,       __DIR__"npc/jiaotou.c":1,

	]));
setup();
replace_program(ROOM);
}