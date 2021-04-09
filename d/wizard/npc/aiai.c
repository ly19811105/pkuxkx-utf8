#include <ansi.h>
inherit NPC;   
void create()                                                                                          
{  
        set_name(HIG"爱爱"NOR, ({ "aiai npc","aiai"}) ); 
        set("long","aiai原是北侠著名的巫师，退隐之后干起了修理兵器的家当。\n
                    为了照顾新手，爱爱也给新手发放一些免费的兵器。\n
                    相关命令是repair，list和draw。");
        set("gender","女性");   
        set("title",HIY"兵器专家"NOR); 
        set("age",25);
        set("per",40); 
        set("str",40); 
        set("int",40); 
        set("dex",40); 
        set("con",40); 
        set("kar",40);
        set("attitude", "friendly");
        set("combat_exp", 2000000000);
        set("apply/attack",  300000); 
        set("apply/defense", 30000);
        set("inquiry",([
        "修理兵器":"命令格式：fix <兵器名称>，修理费用从存款里面扣。",
        "fix":"命令格式：fix <兵器名称>，修理费用从存款里面扣。",
           ]));
        set("shen_type",1);set("score",500000);setup();
        carry_object("/d/huashan/obj/greenrobe")->wear();
}

void init()
{
        add_action("do_repair","fix"); 
        add_action("do_repair","xiuli"); 
        add_action("do_list","list");
        add_action("do_draw","draw");
}

int do_repair(string arg)
{
        object ob;
        object me=this_player();
        object env=environment(me);
        int i, count;  
        int rig,val; //兵器的硬度，价值
        if( !arg ) return notify_fail("你要修理什么武器？\n");        
        if(!env->query("repair_room"))
                return notify_fail("这里似乎没有修兵器的人吧？\n");
        if( !objectp(ob = present(arg, me)) )
                return notify_fail("你身上没有这样东西。\n");
        if (!ob->query("weapon_prop")) 
                return notify_fail(ob->name()+"又不是兵器，有什么可修的？\n"); 
        if (ob->query("unique") || ob->is_gems() == 1)
                return notify_fail("爱爱皱了皱眉头，说道：这种神兵你还是找别人修吧？\n");
        rig = ob->query("rigidity");
        val = ob->query("value");
        if( rig >= 150 )
                return notify_fail(ob->name()+"结实着呢，还不需要修理。\n");
        //计算要花的钱
        count=(300-rig) * val / 300;
        if (ob->is_gems())
            count=count/5;
        if (count<1000) count = 1000;  //至少10 silver
        if (count>50000) count = 50000 + count /4;  //至少10 silver
        if (me->query("balance")<=count)
               return notify_fail("你的存款不够修这把兵器呢，挣点钱再来吧。\n");
        me->add("balance",-count);
        ob->set("rigidity",300);
        message_vision(HIY"$N接过$n，放到一旁叮叮当当的敲打了几下，说道：“好了！”\n"NOR, this_object(), ob);
        tell_object(me, HIG"爱爱告诉你：“修这把兵器共花了"+ count/100 +"两银子。”\n"NOR);
        return 1;
}

int do_list()
{
              object who = this_player();
              object me = this_object();
        message("vision",""HIG"你现在可以向爱爱领取（draw）如下兵器和盔甲：
        ─────────────────────────────────────"HIC"
          1.青锋剑(sword)
          2.大砍刀(blade)     
          3.芭蕉鞭(whip)
          4.熟铜棍(staff)
          5.北侠战甲(armor)   
          6.北侠战盔(head)   
          7.北侠战衣(cloth)   
          8.北侠战袍(surcoat) 
          9.北侠战靴(boots)
	      10.峨嵋刺(dagger)
         "HIG"─────────────────────────────────────\n"NOR"",who,me);
        return 1;       
}


int do_draw(string arg)
{
           string type;
           object ob;
           object who=this_player();
           object me=this_object();
       
       if (who->query("combat_exp")>1000000 && !wizardp(who))
           {
                command(":D "+who->query("id"));
                return notify_fail("爱爱说：凭您的功夫，还是自己去找装备吧! :D\n");
           }
       
       if (!arg)
                     return notify_fail("爱爱说：你想要什么？兵器？还是盔甲？(比如:draw sword)\n");
             sscanf(arg,"%s",type);
                        switch(type)
                        {  
                                 case "sword":  
                             ob=new("/d/wizard/npc/obj/sword.c");
                           break;
						   case "dagger":  
                             ob=new("/d/wizard/npc/obj/dagger.c");
                           break;
                           case "blade":        
                             ob=new("/d/wizard/npc/obj/blade.c");
                           break;
                           case "whip": 
                             ob=new("/d/wizard/npc/obj/whip.c");
                           break;
                           case "staff":        
                             ob=new("/d/wizard/npc/obj/staff.c");
                           break;
                           case "armor":        
                             ob=new("/d/wizard/npc/obj/armor.c");
                           break;
                           case "surcoat":      
                             ob=new("/d/wizard/npc/obj/surcoat.c");
                           break;
                           case "head": 
                             ob=new("/d/wizard/npc/obj/head.c");
                           break;
                           case "boots":        
                             ob=new("/d/wizard/npc/obj/boots.c");
                           break;
                           case "cloth":        
                             ob=new("/d/wizard/npc/obj/cloth.c");
                           break;
            default:
                 tell_object(who,"爱爱说道：不知道你想要啥，给你个甲算了。\n");
                             ob=new("/d/wizard/npc/obj/armor.c");
            break;
                        }                                                  
                           ob->set("value",0);
                           ob->set("no_get",1);
                           ob->set("no_give",1);
                           ob->set("no_give_user",1);
                           ob->move(who);
                           message_vision("$N把"+ob->query("name")+"交给$n,并告诉$n:带好，别乱丢哦！\n",me,who);
                   return 1;
}
