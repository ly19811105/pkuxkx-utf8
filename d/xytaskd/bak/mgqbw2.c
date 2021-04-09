// 蒙古兵

inherit NPC;
//inherit F_SSERVER;
#include <ansi.h>
#include "mgqb.h"
string *spot=({
       "/d/xiangyang/westr5.c",
       "/d/xiangyang/westr4.c",
       "/d/xiangyang/westr3.c",
       "/d/xiangyang/westr2.c",
       "/d/xiangyang/westr1.c",
       "/d/xiangyang/wgate.c",
       "/d/xiangyang/xywest3.c",
       "/d/xiangyang/xywest2.c",
       "/d/xiangyang/xywest1.c",
       "/d/xiangyang/datiepu1.c",
       "/d/xiangyang/xywest1.c",
       "/d/xiangyang/xycenter.c",
       "/d/xiangyang/xywest1.c",
       "/d/xiangyang/xywest2.c",
       "/d/xiangyang/sfgate.c",
       "/d/xiangyang/sfdating.c",
       "HALT"
});

void create()
{
        set_name(HIR"蒙古骑兵"NOR, ({ "menggu qibing", "qibing" }));
	set("age", 22);
        set("no_clean_up", 1);
        set("max_qi", 3200);
        set("max_jing", 800);
        set("menggu", 1);
	set("gender", "男性");
        set("long", "一个身穿铁甲骑着战马的蒙古兵。\n");
        set("attitude", "aggressive");

	set("str", 24);
	set("dex", 16);
        set("combat_exp", 100000+random(300000));
	set("shen_type", 1);
        set_skill("unarmed", 40);
        set_skill("dodge", 240);
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
      set("index",0);
}


void init()
{
 add_action("do_yun","yun");
 add_action("do_kill","kill");
 add_action("do_yun","exert");
remove_call_out("des");
call_out("des",1800);
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
int i,menggu_number;
me=this_player();
bing=this_object();
if(spot[query("index")]=="HALT") return 1;
if(query("victory"))
{
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
if(bing->is_fighting()&&random(10)>2)
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
message_vision(HIR"杀呀，冲啊....."+query("name")+HIR"往前冲去！\n"NOR,bing);
room=load_object(spot[query("index")]);
bing->move(room);
message_vision(HIR"杀呀，冲啊.....一个"+query("name")+HIR"冲了过来！\n"NOR,bing);
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
if(sizeof(obj->query_enemy())>=5) continue;
bing->kill_ob(obj);
obj->kill_ob(bing);
continue;
}
if(obj->query("id")!="guojing"&&obj->query("id")!="huang rong")
{
message_vision(bing->query("name")+"手起刀落,"+obj->query("name")+"就倒在了血泊之中.....\n",bing);
obj->die();
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
                message( "channel:" + "chat",HIR + "【襄阳战报】郭靖夫妇由于寡不敌众战死杀场！帅府被占，襄阳沦陷！\n"NOR,users());
if(!room->query("occupied"))
{
object task;
room->set("long",@LONG
        这里遭受蒙古兵的洗劫后，已经惨不忍睹。尸横遍野，往日的景象已经荡然无存....
LONG
        );
(task=load_object("/adm/daemons/xytaskd.c"))->add("xyoccupied",1);
if (task->query("xyoccupied")>30)
                message( "channel:" + "chat",HIR + "【襄阳战报】襄阳岌岌可危！\n"NOR,users());
else if(task->query("xyoccupied")>20)
                message( "channel:" + "chat",HIR + "【襄阳战报】襄阳现在已尸横遍野！\n"NOR,users());
else if(task->query("xyoccupied")>10)
                message( "channel:" + "chat",HIR + "【襄阳战报】襄阳大乱！\n"NOR,users());
else if(task->query("xyoccupied")>5)
                message( "channel:" + "chat",HIR + "【襄阳战报】襄阳军情堪忧！\n"NOR,users());
else
{}
switch (random(5)){
case 0:
                message( "channel:" + "chat",MAG + "【襄阳传言】襄阳某处陷入一片火海之中......\n"NOR,users());
break;
case 1:
                message( "channel:" + "chat",MAG + "【襄阳传言】蒙古兵在襄阳某处烧杀抢掠无恶不作......\n"NOR,users());
break;
case 2:
                message( "channel:" + "chat",MAG + "【襄阳传言】襄阳的"+room->query("short")+MAG+"被鞑子夷为平地.....\n"NOR,users());
break;
case 3:
                message( "channel:" + "chat",MAG + "【襄阳传言】襄阳某处死伤严重......\n"NOR,users());
break ;
case 4:
                message( "channel:" + "chat",MAG + "【襄阳传言】襄阳某处已成一片废墟......\n"NOR,users());
break ;
}
}
room->set("occupied",1);
}
return 1;
}
if(!room->query("occupied"))
{
object task;
room->set("long",@LONG
        这里遭受蒙古兵的洗劫后，已经惨不忍睹。尸横遍野，往日的景象已经荡然无存....
LONG
        );
(task=load_object("/adm/daemons/xytaskd.c"))->add("xyoccupied",1);
if (task->query("xyoccupied")>30)
                message( "channel:" + "chat",HIR + "【襄阳战报】襄阳岌岌可危！\n"NOR,users());
else if(task->query("xyoccupied")>20)
                message( "channel:" + "chat",HIR + "【襄阳战报】襄阳现在已尸横遍野！\n"NOR,users());
else if(task->query("xyoccupied")>10)
                message( "channel:" + "chat",HIR + "【襄阳战报】襄阳大乱！\n"NOR,users());
else if(task->query("xyoccupied")>5)
                message( "channel:" + "chat",HIR + "【襄阳战报】襄阳军情堪忧！\n"NOR,users());
else
{}
switch (random(5)){
case 0:
                message( "channel:" + "chat",MAG + "【襄阳传言】襄阳某处陷入一片火海之中......\n"NOR,users());
break;
case 1:
                message( "channel:" + "chat",MAG + "【襄阳传言】蒙古兵在襄阳某处烧杀抢掠无恶不作......\n"NOR,users());
break;
case 2:
                message( "channel:" + "chat",MAG + "【襄阳传言】襄阳的"+room->query("short")+MAG+"被鞑子夷为平地.....\n"NOR,users());
break;
case 3:
                message( "channel:" + "chat",MAG + "【襄阳传言】襄阳某处死伤严重......\n"NOR,users());
break ;
case 4:
                message( "channel:" + "chat",MAG + "【襄阳传言】襄阳某处已成一片废墟......\n"NOR,users());
break ;
}
}
room->set("occupied",1);
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
if(sizeof(obj->query_enemy())>=5) continue;
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
call_out("do_move", random(7));
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
call_out("do_move", random(4));
return 1;
}
inv=all_inventory(room);
for(i=0;i<sizeof(inv);i++)
{
obj=inv[i];
if(obj->query("menggu")) menggu_number++;
}
if(menggu_number<35)
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