#include <ansi.h>;

inherit ROOM;

void create()
{
        set("short", HIR"无欢工作室"NOR);
        set("long", @LONG
LONG NOR);

        set("exits", ([
                "south" : "/d/city/guangchang",
                "southeast" : "/d/wizard/biwuchang",
        "west" : __DIR__"dream_room" ,
        "southwest" : "/d/wizard/mingren" ,
        "haiv" : "/u/haiv/wizard_room_haiv" ,
				"lx" : "/d/jiaofei/lx" ,

                "north" : "/d/wizard/wizard_room_advent",
                "northwest" : "/u/whuan/workroom",

        ]));
        set("objects", ([
        ]));

        set("valid_startroom", 1);
        set("outdoors", "city");

        setup();
}

void init()
{
        object me = this_player();
        add_action("do_search","search");
        add_action("do_enter","enter");
        if(me->query("id") == "ztpal")
        {
                me->move("/d/city/guangchang");
                me->delete("env/immortal");
                me->delete("invisibility");
                me->die();
                message("channel:rumor",HIM"【谣言】听说"+me->query("name")+HIM"从"HIY"香蕉树"HIM"上掉到中央广场摔死了！\n"NOR,users());
        }
        return;
}

int do_search()
{
        object me = this_player();
        object obj = random(20)<14 ? new("/clone/story/obj/lingzhi.c") : new("/d/xiangyang/npc/obj/shanlw.c");
        message_vision("$N在树洞里四下搜寻着，找到一颗"+obj->query("name")+"！\n", me);
        message_vision("只可惜一股强大的内力袭来，$N不得不将它丢掉。\n", me);
        destruct(obj);

        return 1;
}
void alternative_die (object me)
{
         object ob;
          ob = me->get_damage_origin_object();
          if (! ob)
            return;  
          
          if(!userp(ob)){
                destruct (ob);
                return ;
                }
          if(!userp(me)){
                destruct (me);
                return ;
                }
}
int do_enter(string arg)
{ 
        object room, me,lover,ob;
        object studyroom;
        int i,j;
        object *ob_list, *room_list;

        me = this_player();

        if (!arg)
        {
                write("你要进入哪间房？\n");
                return 1;
        }

        if (arg==me->query("marry/lover") ||  arg==me->query("id") )
        {
                if (arg==me->query("marry/lover"))
                {
                        if (objectp(lover=find_player(arg)))
                        {
                                if (undefinedp(lover->query("myroom")))
                                {
                                        write("你的爱人还没有自己的房间!\n"); 
                                        return 1;
                                }
                                
                                tell_object(lover,"你爱人进入了你的房间。\n");
                                if ( !objectp(room = lover->query_temp("xinfang")) )
                                {
                                        room=new("/d/xinfang/xinfang");
                                        lover->set_temp("xinfang", room);
                                }
                        }
                        else 
                        {
                                ob = FINGER_D->acquire_login_ob(arg);
                                if( !ob ) {
                                                write("你的爱人已经不在了。\n");
                                                destruct(ob);
                                                return 1;
                                        }
                                if (objectp(lover = LOGIN_D->make_body(ob)))
                                if ( lover->restore())
                                {
                                        if (undefinedp(lover->query("myroom")))
                                        {
                                                write("你的爱人还没有自己的房间!\n"); 
                                                 READWRITE_D->dest_ob(lover);
                                                destruct(ob);
                                                return 1;
                                        }
                                        room=new("/d/xinfang/xinfang");
                                }
                                destruct(ob);
                        }
                        if (room->query("change_name")==0) 
                        {     
                                if (undefinedp(lover->query("myroom/short"))&&
                                                lover->query("myroom/long")!="")        
                                room->set("short",lover->query("name")+"的甜蜜小屋");
                                else room->set("short",lover->query("myroom/short"));
                        
                                if (!undefinedp(lover->query("myroom/long"))&&
                                                lover->query("myroom/long")!="")
                                        room->set("long",lover->query("myroom/long")+"\n");             
                                room->set("owner",lover->query("id"));
                                room->set("change_name",1);
                        }
                        if (!objectp(find_player(arg)))
                                 READWRITE_D->dest_ob(lover);
        
                        message("vision", me->name() + "进入了爱人的房间。\n",
                        environment(me), ({ me }) );
                }               
        
                if (arg==me->query("id"))
                {
                        if (undefinedp(me->query("myroom")))
                        {
                                write("你还没有自己的房间!\n"); 
                                return 1;
                        }
                        if ( !objectp(room = me->query_temp("xinfang")) )
                        {
                                room=new("/d/xinfang/xinfang");
                                me->set_temp("xinfang", room);
                                if (room->query("change_name")==0) 
                                {     
                                        if (undefinedp(me->query("myroom/short"))&&
                                                        me->query("myroom/long")!="")        
                                                room->set("short",me->query("name")+"的甜蜜小屋");
                                        else room->set("short",me->query("myroom/short"));
        
                                        if (!undefinedp(me->query("myroom/long"))&&
                                                        me->query("myroom/long")!="")
                                                room->set("long",me->query("myroom/long")+"\n");             
                                        room->set("owner",this_player()->query("id"));
                                        room->set("change_name",1);
                                }
                        }
                        message("vision", me->name() + "进入了自己的房间。\n",
                                environment(me), ({ me }) );
                }
                room_list = children("/d/xinfang/xinfang");
                for(i=sizeof(room_list)-1; i>=0; i--) {
                        if (!( room == room_list[i] ) && (room_list[i]->query("owner") == room->query("owner"))) 
                        {
                                ob_list = all_inventory(room_list[i]);
                                for(j=0;j<sizeof(ob_list);j++)
                                        ob_list[j]->move(room);
                                destruct(room_list[i]);
                        }
                }

                me->move(room);
                message("vision", me->name() + "走了进来！\n",
                environment(me), ({ me }) );
                return 1;
        }
        else 
        {
                room_list = children("/d/xinfang/xinfang");
                for(i=sizeof(room_list)-1; i>=0; i--) 
                {
                        if (room_list[i]->query("owner") == arg) 
                        {
                                room = room_list[i];
                        }
                }
                me->move(room);
                message("vision", me->name() + "走了进来！\n",
                environment(me), ({ me }) );
                return 1;       	
        }
}
