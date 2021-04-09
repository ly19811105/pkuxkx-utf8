// 蒙古兵

inherit NPC;
#include <ansi.h>
string *spot=({
       "/d/xiangyang/caiyuan.c",
       "/d/xiangyang/eroad1.c",
       "/d/xiangyang/egate.c",
       "/d/xiangyang/xyeast3.c",
       "HALT"
});
protected nosave int index;

void create()
{
        set_name("蒙古兵", ({ "menggu bing", "bing" }));
	set("age", 22);
        set("menggu", 1);
	set("gender", "男性");
        set("long", "一个身穿铁甲的蒙古兵。\n");
        set("attitude", "aggressive");

	set("str", 24);
	set("dex", 16);
        set("combat_exp", 20000);
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
        set("chat_chance_combat", 10);
	set("chat_msg_combat", ({
                "冲啊.......\n",
                "杀啊.......\n",
	}));
	setup();
        carry_object("/clone/weapon/gangdao")->wield();
   remove_call_out("start_move");
call_out("start_move",1);
        carry_object("/clone/armor/tiejia")->wear();
    index=0;
}


void init()
{
 add_action("do_yun","exert");
 add_action("do_yun","yun");
return ;
}
int start_move()
{
remove_call_out("do_move");
call_out("do_move", 1);
return 1;
}
int do_move()
{
object room,me,obj,bing,*inv;
int i;
me=this_player();
bing=this_object();
if(spot[index]=="HALT") return 1;
message_vision(HIR"杀呀，冲啊....."+query("name")+HIR"往前冲去！\n"NOR,bing);
room=load_object(spot[index]);
bing->move(room);
if(!room->query("occupied"))
room->set("long",@LONG
        这里遭受蒙古兵的洗劫后，已经惨不忍睹。尸横遍野，往日的景象已经荡然无存....
LONG
        );
room->set("occupied",1);
index=index+1;
inv=all_inventory(room);
for(i=0;i<sizeof(inv);i++)
{
obj=inv[i];
if(!obj->is_character()) continue;
if(obj->query("menggu")) continue;
if(!living(obj)) continue;
if(userp(obj))
{
bing->kill_ob(obj);
obj->kill_ob(bing);
continue;
}
message_vision(bing->query("name")+"手起刀落,"+obj->query("name")+"就倒在了血泊之中.....\n",bing);
obj->die();
}
if(!room->query("gate"))
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
if (!room->query("gate"))
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
if(menggu_number<20)
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
return 1;
}
}
int do_yun()
{
tell_object(this_player(),"你想运用内功御敌，怎奈蒙古兵实在太多，你竟然无法使出!!\n");
return 1;
}
