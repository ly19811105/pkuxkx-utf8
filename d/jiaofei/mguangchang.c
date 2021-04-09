//Create by whuan@pkuxkx
//铁掌帮
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "玄武堂广场";
  long_describe = 
"这里是兰若寺的广场，整个广场由大块的青石铺成，极为平坦。广场的中间
种着一棵老槐树，枝繁叶茂，看来已有些年头。槐树下是一个一人高的香炉。前
面就是兰若寺的大殿，左右两边是两个侧殿。";
 	doorstr = 20; 
 	nextdirect = "north";
 	npc_type="dalunsi";
 	level=1;
}

void create()
{
	::create();
	set("exits", ([ 
         "south" : __DIR__"msimen",
         "west" : __DIR__"mxicedian",
         "west" : __DIR__"mdongcedian",
         "north" : __DIR__"mdadian",			
      ]));
}