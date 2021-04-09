// Room: /d/quanzhou/guajianci.c
//write by yuer

inherit ROOM;

int do_catch(string arg);


void create()
{
        set("short", "挂剑祠");
        set("long", @LONG
 祠边有条小河，有数十条小鱼（fish)游来游去。
LONG
        );
set("exits", ([
                
                "northwest" : __DIR__"hutiaoxia",
        ]));

    set("item_desc", ([
                "fish": "看起来你可以抓住（catch）。\n",
                "鱼": "看起来你可以抓住（catch）。\n",
               ]));
        setup();
}

void init()
{
 add_action("do_catch","catch");
  
 }

int do_catch(string arg)
{
        object me,fish;
        me=this_player();
        if(!arg) return notify_fail("pick <东西>\n");
        if(query_temp("mark/been_get1")) return notify_fail("鱼已被捉走了。\n");
        if((arg == "fish"||arg == "鱼") && (int)me->query_dex()>25)
 {
                        message_vision( "\n$N将小鱼捉了起来。\n",this_player());
                        fish=new(__DIR__"obj/fish.c");
                        fish->move(me); 
 			    set_temp("mark/been_get1",1);
                        return 1;
                }
        message_vision( "\n$N捉来捉去,可是捉不着。\n",this_player());
       
        return 1;
}   
 
void reset()
{
    ::reset();
        delete_temp("mark/been_get1");
    
}



