//Create by whuan@pkuxkx
//铁掌帮
#include <ansi.h>
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "石阶";
  long_describe = "你顺着山路走了许久，终于到了小指峰的第一节，远远望去，其余四峰直插
云霄，若隐若现";
 	doorstr = 30; 
 	nextdirect = "northup";
 	npc_type="baituo";
 	level=5;
 	
}

void create()
{
	::create();
	set("exits", ([ 
  "southeast" : __DIR__"xshanlu3", 
  "northup" : __DIR__"xshijie2",
      ]));
  set("outdoors", "tiezhang");    
}