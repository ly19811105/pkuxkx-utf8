// 蒙古兵

inherit NPC;
//inherit F_SSERVER;
#include <ansi.h>
string *spot=({
       "HALT"
});

void create()
{
        set_name("鬼面", ({ "gui mian", "mian" }));
	set("age", 22);
        set("changed", 0);
        set("no_clean_up", 1);
        set("max_qi", 3200);
        set("max_jing", 800);
        set("menggu", 1);
	set("gender", "男性");
        set("long", "扮人高手\n");
        set("attitude", "aggressive");

	set("str", 24);
	set("dex", 16);
        set("combat_exp", 100000+random(300000));
	set("shen_type", 1);
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set_skill("blade", 40);
        set_skill("force", 40);
	set_temp("apply/attack", 40);
	set_temp("apply/defense", 40);
	set_temp("apply/damage", 20);
	set_temp("apply/armor", 40);
        set("chat_chance", 40);
        set("chat_msg", ({
                "嘻嘻.......\n",
                "哈哈.......\n",
                (: random_move :),
                (: random_move :),
                (: random_move :),
                (: random_move :),
	}));
	setup();
        carry_object("/clone/weapon/gangdao")->wield();
//   remove_call_out("start_move");
//call_out("start_move",1);
        carry_object("/clone/armor/tiejia")->wear();
      set("index",0);
remove_call_out("cheat");
call_out("cheat",1);
}


void init()
{
 add_action("do_kill","kill");
 add_action("do_yun","exert");
remove_call_out("des");
call_out("des",1800);
return ;
}
int cheat()
{
object *inv,obj,ar,weapon1,weapon2;
mapping armor;
string msg;
int i;
//if(query("changed")) return 1;
inv=all_inventory(environment(this_object()));
for(i=0;i<sizeof(inv);i++)
{
obj=inv[i];
if(!obj->is_character()) continue;
if(!living(obj)) continue;
if(userp(obj))
{
//伪装
armor=obj->query_temp("armor");
ar=armor["cloth"];
weapon1=obj->query_temp("weapon");
weapon2=obj->query_temp("secondary_weapon");
if(ar) msg="身穿"+ar->query("name")+"走了过来。\n";
else msg="光着身子走了过来。\n";
if(weapon1) msg="右手拿着"+weapon1->query("name")+"，"+msg;
if(weapon2) msg="左手拿着"+weapon2->query("name")+"，"+msg;
msg=obj->query("name")+msg;
set("come_msg",msg);
set("title",obj->query("title"));
//set("id",obj->query("id"));
set_name(obj->query("name"),({obj->query("id")}));
set("long",obj->query("long"));
set("nickname",obj->query("nickname"));
set("age",obj->query("age"));
set("changed",1);
return 1;
}
}
remove_call_out("cheat");
call_out("cheat",1);
return 1;
}
int start_move()
{
remove_call_out("do_move");
call_out("do_move", 1);
return 1;
}
int do_move()
{
object here;
string leave_direction;
string *pname;
object room,me,obj,bing,*inv;
int i,menggu_number;
me=this_player();
bing=this_object();
if(spot[query("index")]=="HALT") return 1;
if(query("victory"))
{
        set_name("蒙古奸细", ({ "menggu jianxi", "jianxi" }));
        set("age", 22);
        set("long", "一个鬼鬼祟祟的蒙古奸细。\n");
        delete("title");
        delete("nickname");
        delete("come_msg");
        set("chat_chance", random(300));
        set("chat_msg", ({
       "这些汉狗，简直不堪一击！.\n",
       "大汗说过，襄阳城破之日起，屠城三日！\n",
       "哈哈，哈哈......\n",
       "我们蒙古族个个都是好汉，骁勇善战....\n",
       "哼，想那郭靖本是我们的金刀驸马，现在落的这样下场真是自找的!@#%$@#!@\n",
       "只是可惜我们的华筝公主，却是终生未嫁......\n"
        }) );
return 1;
}
if(bing->is_fighting())
{
remove_call_out("do_move");
call_out("do_move", 5);
return 1;
}
if(!living(bing))
{
remove_call_out("do_move");
call_out("do_move", 5);
return 1;
}
here=environment(this_object());
if(here) pname=keys(here->query("exits"));
leave_direction=pname[random(sizeof(pname))];
if(!leave_direction)
message_vision(query("name")+"向前离开。\n",bing);
else if(leave_direction=="east")
message_vision(query("name")+"往东离开。\n",bing);
else if(leave_direction=="south")
message_vision(query("name")+"往南离开。\n",bing);
else if(leave_direction=="west")
message_vision(query("name")+"往西离开。\n",bing);
else if(leave_direction=="north")
message_vision(query("name")+"往北离开。\n",bing);
else 
message_vision(query("name")+"往"+leave_direction+"离开。\n",bing);
room=load_object(spot[query("index")]);
bing->move(room);
if(!query("changed")) message_vision("一个"+query("name")+"走了过来.\n",bing);
else
{
if(query("come_msg")) message_vision(query("come_msg"),bing);
else message_vision(query("name")+"身穿铁甲手持钢刀走了过来.\n",bing);
}
if(room->query("shuaifu"))
{
inv=all_inventory(room);
for(i=0;i<sizeof(inv);i++)
{
obj=inv[i];
if(!obj->is_character()) continue;
if(obj->query("menggu"))
{
menggu_number++;
continue;
}
if(!living(obj)) continue;
if(userp(obj))
{
continue;
}
if(obj->query("id")!="guojing"&&obj->query("id")!="huang rong")
{
continue;
}
bing->kill_ob(obj);
obj->kill_ob(bing);
}
if(menggu_number>40)  //失败判据
{
object xytaskd;
xytaskd=load_object("/adm/daemons/xytaskd.c");
xytaskd->set("begin",0);
xytaskd->set("victory",0);
//任务失败
room->set("shuaifu",0);
inv=all_inventory(room);
for(i=0;i<sizeof(inv);i++)
{
obj=inv[i];
if(!obj->is_character()) continue;
if(obj->query("menggu")) continue;
if(!living(obj)) continue;
if(userp(obj)) continue;
message_vision(bing->query("name")+"手起刀落,"+obj->query("name")+"就倒在了血泊之中.....\n",bing);
obj->set("killed",1);
obj->die();
}
                message( "channel:" + "chat",HIR + "【襄阳战报】郭靖夫妇被蒙古奸细杀死，帅府被占，襄阳沦陷！\n"NOR,users());
}
return 1;
}
add("index",1);
inv=all_inventory(room);
for(i=0;i<sizeof(inv);i++)
{
obj=inv[i];
if(!obj->is_character()) continue;
if(obj->query("menggu")) continue;
if(!living(obj)) continue;
if(userp(obj))
{
continue;
}
}
if(!room->query("gate")||query("changed"))
{
remove_call_out("do_move");
call_out("do_move", random(20));
}
else
{
remove_call_out("do_judge");
call_out("do_judge",1,room);
}
return 1;
}
int do_judge(object room)
{
int menggu_number;
object obj,*inv;
int i;
if(!room->query("gate")||query("changed"))
{
remove_call_out("do_move");
call_out("do_move", random(10));
return 1;
}
inv=all_inventory(room);
for(i=0;i<sizeof(inv);i++)
{
obj=inv[i];
if(obj->query("menggu")) menggu_number++;
}
if(menggu_number<25)
{
remove_call_out("do_judge");
call_out("do_judge",1,room);
return 1;
}
else
{
room->set("gate",0);
remove_call_out("do_move");
call_out("do_move", 1);
message_vision(HIR"蒙古兵破门而入！\n"NOR,this_object());
// 沦陷
                message( "channel:" + "chat",HIR + "【襄阳战报】" + room->query("short") + "沦陷！\n"NOR,users());
(load_object("/adm/daemons/xytaskd.c"))->add("occupied",1);
(load_object("/adm/daemons/xytaskd.c"))->set("north",1);
return 1;
}
}
int do_kill(string arg)
{
if(sizeof(this_player()->query_enemy())>35)
{
tell_object(this_player(),HIW"你对付的人够多了！\n"NOR);
return 1;
}
return 0;
}
int do_yun()
{
tell_object(this_player(),"你想运用内功御敌，怎奈蒙古兵实在太多，你竟然无法使出!!\n");
return 1;
}
int die()
{
object me,xytaskd;
if(query("victory"))
{
message_vision(this_object()->query("name")+"死了,你仔细一看发现他竟然是蒙古奸细假扮的！\n",this_object());
destruct(this_object());
return 1;
}
me=this_object()->query_temp("last_damage_from");
//if(!me) me=offensive_target(this_object());
if(!me) me=this_player();
xytaskd=load_object("/adm/daemons/xytaskd.c");
if(query("taskid")!=me->query_temp("xytaskd/taskid"))
{
me->set_temp("xytaskd/number",0);
}
me->add_temp("xytaskd/number",1);
me->set_temp("xytaskd/taskid",xytaskd->query("taskid"));
//::die();
message_vision(this_object()->query("name")+"死了,你仔细一看发现他竟然是蒙古奸细假扮的！\n",this_object());
destruct(this_object());
return 1;
}
/*
int unconcious()
{
die();
return 1;
}
*/
int des()
{
destruct(this_object());
return 1;
}
