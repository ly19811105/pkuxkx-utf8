//v1.0
//by advent
//2006-7-23
//type room
inherit ROOM;

void create ()
  {
    set("short","三味书屋");
set("long", @LONG
这里是行云的书房，一张大大的书桌杂乱的摆了很多书，也不见小丫鬟来收拾一下。
书桌后面挂了一幅字，不知道谁题了四个大字“三味书屋”，字迹苍劲有力，一看就知道出自名家之手。
LONG);
        set("exits",([
       "south" : "/u/advent/workroom",
       "north" : "/u/advent/droproom",
        ]));
        set("objects", ([
//测试菩提子
//        __DIR__"npc/girl" : 2,
/*
                "/d/wizard/obj/box" : 1,
*/
//"/d/wizard/npc/pkuxkx":1,
//        __DIR__"obj/puti-zi" : 5,
//        __DIR__"obj/haagendazs" : 1,
//        __DIR__"obj/tree77" : 1,
//      "/d/xiakedao/obj/xkd_book_test.c": 1,
                        ]) );
     set("no_kill", 1);
         set("alternative_die",1);
     set("sleep_room", 1);
     set("no_steal", 1);
setup();
  "/clone/board/advent_b"->foo();
   }
void alternative_die (object me)
{
         if(userp(me))
         {
                message_vision("天空突然升出一只大脚，一脚将$N踢飞了。\n",me);
                if (me->query("qi")<=10) me->set("qi",10);
                if (me->query("max_qi")<=10) me->set("max_qi",10);
                me->move("/d/city/guangchang");
                me->unconcious();
                
                tell_room(environment(me),"半空中，"+me->query("name")+"倒栽葱的直坠下来。\n");
                return;
        }       
         else
                {
                        if(me->query("id") =="shouhuzhe")
                                me->die();
                        else 
                                {
                                        me->move("/obj/void");
                                        destruct(me);
                                }       
                                        
                        
                        
                        
                }         
         
}
