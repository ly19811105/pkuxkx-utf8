//v1.0
//by advent
//2006-7-23
//type room
inherit ROOM;
#include <ansi.h>

void create ()
  {
    set("short","大厅");
set("long", @LONG
     这里是行云家的大厅，简陋异常，但是女主人却收拾得很干净。
厅中摆了一张电脑桌，行云的电脑就随意摆在这里，平常玩mud就靠他了。
LONG);
        set("exits",([
//       "out" : "/u/advent/workroom",
        ]));
        set("objects", ([
//测试菩提子

//      "/d/xiakedao/obj/xkd_book_test.c": 1,
                        ]) );
     set("no_fight", 1);
     set("no_kill", 1);
     set("sleep_room", 1);
     set("no_steal", 1);
setup();
replace_program(ROOM);
   }
void init()
{
add_action("do_test","testa");
}
int do_test()
{
 write("haha,test\n");
    return 1;
}
