//gengyishi.c

#include <ansi.h>

inherit ROOM;

void create()
{
  set("short",HIC"更衣室"NOR);
  set("long",@LONG
这里是浴堂前的更衣室。

LONG
    );
  set("exits",([
    "north" : __DIR__"zoulang11",
    "south" : __DIR__"yutang",
  ]));
  set("objects",([
     __DIR__"npc/yudao.c" :1,
  ]));
  setup();
}

int valid_leave(object me,string dir)
{
 
 if((string)me->query("family/family_name")!="全真派"&&dir=="south")
 
  return notify_fail("你不是全真派的,还想去白洗澡?!\n");
  
  
 if((int)me->query_temp("have_bath")&&dir=="south")
  
  return notify_fail("你不是刚刚洗过澡了么?\n");
  
  
  return ::valid_leave(me,dir);
}
