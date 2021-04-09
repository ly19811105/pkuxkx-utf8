// quit.c
// Modified by iszt@pkuxkx, 2007-04-14

#include <command.h>
#include <ansi.h>
inherit F_DBASE;
inherit F_CLEAN_UP;
int closecastle(object);
void create() 
{
    seteuid(getuid());
    set("name", "离线指令");
    set("id", "quit");
}

int main(object me, string arg)
{
    int i;
    int exp,limit;
    object *inv, link_ob, pet,room;
    room=environment(me);
    
    if(time() - me->query("killer/time") < 15*60)
    {
        write("你刚刚杀了人，别想这么容易跑掉。\n");
        return 1;
    }
    //计算存款上限
    if (!me->query("lingjiu/xiulian"))
    {
        if (me->query("combat_exp")>=80000000) limit=2000000000;
        else limit = me->query("combat_exp") * 25;
    }
    else
    {
        if (me->query("lingjiu/combat_exp")>=80000000) limit=2000000000;
        else limit = me->query("lingjiu/combat_exp") * 25;            
    }

    if(limit > 2000000000 || limit < 0)
        limit = 2000000000;
    if(limit < 500000) limit = 500000;        

    if (me->is_busy() && !me->query_temp("netdead"))
    {
        //      me->interrupt_me(me, "halt");
        write("你正忙着呢，无法退出。\n");
        return 1;
    }
    if(me->is_fighting())
    {
        write("你正在战斗，无法退出。\n");
        return 1;
    }
    if(me->query("id")==room->query("host"))
    {
        write("在自己的山庄里不允许退出。\n");
        return 1;
    }
    if(me->query("noDeadNetnoIdle")=="Pkuxkx" && !me->query_temp("confirm_quit"))
    {
        write("你被巫师设置了断线不退出，你直接关闭mud就行。\n");
        write("如果真想quit，再输入quit即可。\n");
        me->add_temp("confirm_quit",1);
        return 1;
    }
    if(room->query("no_quit"))
    {
        write("这里不允许退出。\n");
        return 1;
    }
    if(TOPTEN_D->how_many_money(me) > limit && !me->query_temp("confirm_quit1") && !wizardp(me))
    {       
        write("你随身携带的金钱和存款超过了你可以承受的上限，退出可能导致金钱遗失。\n");
        write("确认退出请再次输入quit！\n");
        me->add_temp("confirm_quit1",1);
        return 1;
    }

    if( !wizardp(me) )
    {
        me->set_temp("redundant_save", 1);  //add by boost. 防止后面的move产生大量的save

        inv = all_inventory(me);
        for(i=0; i<sizeof(inv); i++)
            if( !inv[i]->query_autoload() )
                DROP_CMD->do_drop(me, inv[i]);
    }

    link_ob = me->query_temp("link_ob");

    // We might be called on a link_dead player, so check this.
    if( link_ob ) {

        // Are we possessing in others body ?
        if( link_ob->is_character() ) {
            write("你的魂魄回到" + link_ob->name(1) + "的身上。\n");
            exec(link_ob, me);
            link_ob->setup();
            return 1;
        }
        //防止短时间重复登录多次
        if ( (time()-link_ob->query("last_on"))<60 )
            link_ob->add("freqreconnect",1);
        link_ob->set("last_on", time());
        link_ob->set("last_from", query_ip_number(me));
        link_ob->save();
        destruct(link_ob);
    }
	
	TOP_D->compare_status(me);
	//STATISTIC_D->register_user(me);
    if (me->query("antirobot/seg_first_activity_time"))
    {
        me->add("antirobot/total_activity_time", time()-me->query("antirobot/seg_first_activity_time"));
        me->set("antirobot/seg_first_activity_time",0);
    }
    if (me->query("antirobot/deactivity") < 4)
    {
        me->set("antirobot/last_activity_time", time());
    }
    if (time()-me->query("antirobot/last_activity_time")>3600*5)
    {
        me->set("antirobot/first_activity_time", 0);
        me->set("antirobot/first_activity_exp", 0);
        me->set("antirobot/total_activity_time", 0);
        me->set("antirobot/last_activity_time", 0);
        me->set("antirobot/pic_fullme_times", 0);
        me->set("antirobot/hand_fullme_times", 0);
    }

	TOPTEN_D->topten_checkplayer(me);

    switch (random(8))
    {
	    case 0:cat("/adm/etc/byes/bye1");break;
	    case 1:cat("/adm/etc/byes/bye2");break;
	    case 2:cat("/adm/etc/byes/bye3");break;
	    case 3:cat("/adm/etc/byes/bye4");break;
	    case 4:cat("/adm/etc/byes/bye5");break;
	    case 5:cat("/adm/etc/byes/bye6");break;
	    case 6:
	    	  write(HBGRN"                                                    \n"NOR);
	    	  write(HBGRN"冰冰："+me->name()+"是个好同志。                    \n"NOR);
	    	  write(HBGRN"无欢：我觉得冰冰说的有几分道理。                    \n"NOR);
	    	  write(HBGRN"无际：凡是icer同志的理论，我们要充分理解后执行。    \n"NOR);
	    	  write(HBGRN"变态：凡事不能理解的，要在必须理解的基础上贯彻执行。\n"NOR);
	    	  write(HBGRN"虫二："+me->name()+"你还是走吧，再不走我都想死你了。\n"NOR);
	    	  write(HBGRN"                                                    \n"NOR);
	    	  break;
	    case 7:
	    	  write(HBGRN"                                                    \n"NOR);
    		  write(HBGRN"hash：听说"+me->name()+"要睡觉去了。                \n"NOR);
          write(HBGRN"ark：你怎么知道是睡觉不是去吃饭？                   \n"NOR);
          write(HBGRN"tianying：这有区别么？                              \n"NOR);
          write(HBGRN"religiose：当然，吃饭可以是一个人，也可以是两个人。 \n"NOR);
          write(HBGRN"tianying：那睡觉呢？                                \n"NOR);
          write(HBGRN"zgbl：睡觉也可以是一个人，也可以是两个人。          \n"NOR);
          write(HBGRN"tianying：那不一回事么？                            \n"NOR);
          write(HBGRN"ajump：不一样。两个人吃饭和一个人吃饭没什么区别     \n"NOR);
          write(HBGRN"       但是一个人睡觉和两个人睡觉可就完全不同了。   \n"NOR);
          write(HBGRN"众人：你可以去死了。                                \n"NOR);
          write(HBGRN"                                                    \n"NOR);
    		  break;
    }
    if (!me->query("env/invisibility")||(int)me->query("env/invisibility")==0)
    {
        message("system", me->name() + "离开游戏。\n", room, me);
    }

    CHANNEL_D->do_channel(this_object(), "sys",
        sprintf("%s(%s)离开游戏了。", me->name(), capitalize(me->query("id"))) );

    if( (pet = me->query_temp("created_pet")) && present(pet, environment(me)) )
    {
        pet->save();
        destruct(pet);
    }
    //"/adm/daemons/savetotxtd"->savetotxt(me);
    if(me->query("selfcreate/havecreated"))
        closecastle(me);
    ////去掉上次保存时间,保证实时存盘
    //me->delete("last_save_time");
    //me->save();
    
    me->delete_temp("redundant_save");  
    me->save();                         //保证原来的save操作

    destruct(me);

    return 1;
}

int help(object me)
{
    write(@HELP
指令格式 : quit

当你想暂时离开时, 可利用此一指令。
HELP
       );
    return 1;
}

int closecastle(object me)
{
    string filename,str;
    object ob;
    int i;
    str=me->query("id");
    for(i=1;i<=me->query("selfcreate/hotel");i++)
    {
        filename="/data/home/file/"+str[0..0]+"/"+str+"/hotel"+i+"/npc/waiter.c";
        if(wizardp(me))
            printf("filename=%s\n",filename);
        if( file_size(filename)<1 )
            continue;
        if(!( ob = find_object(filename)) )
            ob = load_object(filename);
        if( objectp(ob) && living(ob) )
        {
            if(wizardp(me))
                printf("找到一个.\n");
        }

        ob->set("closed",1);
        ob->save();
        ob->restore();
    }
    me->set("selfcreate/closed",1);
    return 1;
}
