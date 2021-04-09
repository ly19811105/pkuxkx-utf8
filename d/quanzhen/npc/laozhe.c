//qz newbie job Zine
#include <ansi.h>
#include "bonus.h"
inherit NPC;
string ask_yao();
int ask_help();
void create()
{
    set_name("老者",({"lao zhe","lao"}));
    set("nickname",HIC"园圃管家"NOR);
    set("long",@LONG
他就是全真教负责照看园圃的人,
LONG
       );
    set("age",56);
    set("attitude","peaceful");
    set("score",10000);
    set("shen_type",1);

    set("max_neili",500);
    set("neili",500);
    set("combat_exp",5000);

    set_skill("parry",30);
    set_skill("dodge",30);
    set_skill("cuff",30);
    set_temp("apply/dodge",30);
    set_temp("apply/parry",30);
    set_temp("apply/defence",30);
    set("chat_chance",10);
    set("chat_msg",({
                "老者哈哈大笑:这些植物如今能生长的如此好,全是我的功劳啊!\n",
                }));
    set("yao_count",3);
    set("inquiry",([
                "药" : (: ask_yao : ),
                "help" : (:ask_help:),
                "帮忙" : (:ask_help:),
                ]));
	set("bonus",1);
    setup();

    carry_object(__DIR__"obj/jiandao.c");
}

int ask_help()
{
    object me=this_player();
    string * task_list=({"移栽","浇水","施肥","收药"});
    int n;
    if (!me->query_temp("qznewbiejob/task2/start"))
    {
        command("say 我这没什么事，你去别处看看吧。");
        return 1;
    }
    if (me->query_temp("qznewbiejob/task2/type"))
    {
        command("say 又一个光说不练的啊。");
        return 1;
    }
    n=random(sizeof(task_list));
    me->set_temp("qznewbiejob/task2/type",task_list[n]);
    if (n==0)
    {
        command("say 你去"+HIG+"奇草"+NOR+"挖(wa)一株草药栽种(zai)到这里吧。");
    }
    if (n==1)
    {
        command("say 你去"+HIG+"奇草"+NOR+"那里，给那些草浇(jiao)点水，别干死了。");
    }
    if (n==2)
    {
        command("say 你去"+HIG+"奇草"+NOR+"那里，给那些草施(shifei)点肥。");
    }
    if (n==3)
    {
        command("say 最近药圃要收药，缺乏人手，你帮我收齐(shouqi)十株药材吧。");
    }
    return 1;
}

void init()
{
    object me=this_player();
    ::init();
    if (me->query_temp("qznewbiejob/task2/finish"))
    {
        me->delete_temp("qznewbiejob/task2/finish");
        bonus(me);
    }
    if(interactive(me)&&!is_fighting() )
    {
        remove_call_out("greeting");
        call_out("greeting",1,me);
        return;
    }
}

void greeting(object me)
{
    object ob=this_object();
    if (!me) return; 
    command("smile"+ob->query("id"));
    message_vision("$N笑着对$n说:这位"+RANK_D->query_respect(me)+"来看看我的园圃吧\n",ob,me);
}

string ask_yao()
{
    object obj;
    object ob=this_player();
    if(ob->query("family/family_name")!="全真派")
        return HIB"你与我全真素无瓜葛,这话如何说起?\n"NOR;
    if(ob->query("score") < 200 )
        return "你对本派贡献太小，本派的良药现在还不能给你。";
    if(query("yao_count")<1)
        return YEL" 哟,我现在身上已经没有药了\n"NOR;
    if((int)ob->query("eff_qi")==(int)ob->query("max_qi"))
        return RED"我看你血气充盈,似乎并没有受伤,为何找我问药?\n"NOR;
    if((int)ob->query_temp("have_yao"))
        return HIW"刚才你不是给你药了么？ 你真是贪得无厌!!\n"NOR;
    add("yao_count",-1);
    ob->set_temp("have_yao",1);
    obj=new(__DIR__"obj/gao.c");
    obj->move(ob);
    return "我看你似乎受了些伤,这里有些伤药,给你吧";
}



