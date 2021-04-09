//by whuan
//发布消息，启动event和vertuald
//发布飞贼
inherit NPC;
#include <ansi.h>
#include "notice.h"
#include <localtime.h>

void create()
{
        set_name(HIW"北大侠客行"NOR, ({"pkuxkx"}));
        set("gender", "男性" );
        set("age", 13);
        set("title", "北侠新闻发言人");
        set("env/invisibility",1);
        set("long", "一个可爱的小童，每天负责在这里迎接远道而来的客人．\n");
        set("combat_exp", 200);
        set("attitude", "friendly");
        set_skill("dodge", 10);
        set("per", 30);
        set("max_qi", 1500000);
        set("qi",1500000);
        set("jing",1500000);
        set("max_jing", 1500000);
        set("shen_type",1);set("score",0);setup();
        remove_call_out("pkumsg");
        call_out("pkumsg",1);
        remove_call_out("speweek");
        call_out("speweek",5);   
        remove_call_out("event");
        call_out("event",5);  
        remove_call_out("feizei");
        call_out("feizei",10);    
        remove_call_out("feizei1");
        call_out("feizei1",20);                   

        remove_call_out("reward");
        call_out("reward",5);  

        set("reward_notify_flag",0);

}

void reward()
{
	mixed* timeinfos;
	int hour;

	timeinfos = localtime(time());

	hour = timeinfos[LT_HOUR];

    //每天21到22点，奖励增加
    if((hour == 21 || hour == 22) && !query("reward_notify_flag"))
    {
        CHANNEL_D->do_channel(this_object(), "jh", BMAG+"亥时已到,所有奖励，打坐，学习等效率提高百分之"+chinese_number(REWARD_D->get_special_hour_reward_factor())+NOR, -1);
        set("reward_notify_flag",1);
    }
    else if(hour == 23 && query("reward_notify_flag"))
    {
        set("reward_notify_flag",0);
    }
    remove_call_out("reward");
    call_out("reward",60);      
}

void pkumsg()
{
    if (environment(this_object()))
    {
        CHANNEL_D->do_channel(this_object(), "jh", HBRED+msg[random(sizeof(msg))]+NOR, -1);
        remove_call_out("pkumsg");
        call_out("pkumsg",300);
    }
}
void speweek()
{
        if (environment(this_object()))
        {
              object speweek;
              speweek=load_object("/adm/daemons/speweek");
              if(speweek) speweek->start();
        remove_call_out("speweek");
        call_out("speweek",7000+random(400));         
              }
}
void feizei()
{
        if (environment(this_object()))
        {
         FEIZEI_D->random_feizei();
         if (random(5)) FEIZEI_D->random_feizei();
         if (random(4)) FEIZEI_D->random_feizei();
         if (random(3)) FEIZEI_D->random_feizei();
         if (random(2)) FEIZEI_D->random_feizei();	
         remove_call_out("feizei");           
         call_out("feizei",1000+random(80));          
         }
}

void feizei1()
{       
        object ob, where;
        object ob1;
        if (environment(this_object())) 
        {     
        remove_call_out("feizei1");                   
        call_out("feizei1",1400+random(80));          
        if(random(4))
               return;
        ob = new("/d/wizard/npc/feizei");
//过滤非法任务地点和不明区域 by segate@pkuxkx
        while (!objectp(where) || 
               !where->isroom()||
               TASK_D->place_belong(where)=="不明区域"||
               base_name(where) == "/adm/daemons/taskd")
        {
          where = TASK_D->random_place();
        }
//        where = TASK_D->random_place();
        ob->move(where);
        CHANNEL_D->do_channel(this_object(), "jh", HIR"听说"HIY+TASK_D->place_belong(where)+HIR"有飞贼横行，据说身携重宝！" NOR, -1);        
        if(random(3))
               return;
     //   ob1=new("/d/reborn/jinyong/npc/sj_huo");
     //   ob1->move("/d/xingxiu/saimachang");
      //  by hubo,新做了书剑的迷题，以前的废除了。
        }
}
void event()
{
        if (environment(this_object()))
        {
              object event;
              object virtuald;
              event=load_object("/adm/daemons/eventd");
              if(event) event->create();
              "/cmds/app/update1.c"->main(this_object(),"/adm/daemons/virtuald"); 	 
              }
}

