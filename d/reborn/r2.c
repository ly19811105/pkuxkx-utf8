//by kiden@pkuxkx

inherit ROOM;
#include <room.h>
int stage = 2; //关卡
void create ()
{
  set ("short", "第"+chinese_number(stage)+"关");
  set ("long", @LONG

                         s________________s  
                        /LLLLLLLLLLLLLLLLLL\        
    []__[]             ^^||======||======||^^             []__[]
    []==[]_[]__[]__[]__[]||[]__[]||[]__[]||[]__[]__[]__[]_[]==[]
    []==[]|__|__|__|__|__|__|┏━━━┓_|__|__|__|__|__|__[]==[]
    []==[]__|__|__|__|__|__|_┃第二关┃__|__|__|__|__|__|_[]==[]
    []==[]|__|__|__|__|__|__|┗━━━┛_|__|__|__|__|__|__[]==[]
    []==[]__|__|__|__|__|__|__/       \__|__|__|__|__|__|_[]==[]
    []==[]|__|__|__|__|__|__||        | |_|__||__|__|__|__[]==[]
    []==[]__|__|__|__|__|__|_|        |__┌┐┌┐_|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__|        |_|└┘└┘|__|__|__[]==[]
    []==[]__|__|__|__|__|__|_|        |__|__|__|__|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__|        |_|__|__|__|__|__|__[]==[]
                    飞雪连天射白鹿  笑书神侠倚碧鸳

LONG);

  set("exits", ([ /* sizeof() == 3 */
      "north" : __DIR__"c"+stage,
      ]));
     set("objects", ([
             __DIR__"npc/m"+stage : 1,
             __DIR__"npc/jieshuoyuan2" : 1,
      ]));
     set("no_die", 1); 
     set("no_clean_up", 1);
   setup();
}

int valid_leave(object me, string dir)
{
        if( ((int)me->query("reborn/stage_"+stage)<1) && (dir == "north") )
                return notify_fail("你得闯过这一关才能过去！\n");
        return ::valid_leave(me, dir);
}
