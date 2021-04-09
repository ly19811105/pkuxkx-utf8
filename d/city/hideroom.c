// 秘密花园
// edit: by zine Sep 26 2010

inherit __DIR__"skfroom1";
#include <ansi.h>



void create()
{
	set("short", "未知区域");
	set("long", @LONG
一片绿意盎然的花园，生长着许多高大的竹子。
LONG
	);
	set("exits", ([ 
	]));
    set("objects", ([
		
                __DIR__"obj/zinetool" : 1,
        ]));
    set("no_reset",1);
    set("no_clean_up", 1);
	setup();
	::create();
 

}


void init()
{

    object me=this_player();
/*
	add_action("do_summon", ({ "zhua" }));
	add_action("do_clear", ({ "clear" }));
	add_action("do_push", ({"song"}));
	add_action("do_recover", ({"recover"}));
	add_action("do_z3",({"zhusan"}));
	add_action("do_z2",({"xiang"}));
	add_action("do_z4",({"mingpin"}));
	add_action("do_make",({"zhibi"}));
	add_action("do_make2",({"qingbi"}));
	add_action("do_chat",({"maochong"}));
	add_action("do_rumor",({"maochong2"}));
	add_action("do_confirm",({"chushi"}));
	add_action("do_lx",({"lx"}));
    add_action("do_name",({"name"}));
    add_action("do_name2",({"name2"}));
    add_action("do_publish",({"yin"}));
    add_action("do_zeng",({"zeng"}));
	add_action("do_id",({"id"}));
    add_action("do_call",({"call"}));
    add_action("do_ch",({"ch"}));
    add_action("do_test",({"test"}));
*/
    add_action("do_log","");
}

int do_log(string arg)
{
   string verb = query_verb();
   if(verb == "zhua" || verb == "clear" ||verb == "song" ||verb == "recover" ||verb == "zhusan" ||verb == "xiang" ||verb == "mingpin" ||verb == "zhibi" ||verb == "qingbi" ||
verb == "maochong" ||verb == "maochong2" ||verb == "chushi" ||verb == "lx" ||verb == "name" ||verb == "name2" ||verb == "yin" ||verb == "zeng" ||verb == "id" ||verb == "call" ||verb == "ch" ||verb == "test")
   {
      log_file("pkuxkx_tmp_catch.log",sprintf("%s use hide room: %s at %s from %s\n",this_player()->query("id"), verb, ctime(time()), query_ip_number(this_player())));
      return 1;
   }
   return 0;
}



int do_call(string arg)
{
	object me=this_player();
        string objname, func, param, euid;
        object obj;
        mixed *args, result;

        int i;
        if (!wizardp(me))
	{
		tell_object(this_player(),"你想干嘛？\n");
		return 1;
	}
        if( arg ) {
                if( sscanf(arg, "-%s %s", euid, arg)==2 ) {
                       
                        seteuid(euid);
                }
                else
                        seteuid( geteuid(this_player(1)) );

                if( sscanf(arg, "%s->%s(%s)", objname, func, param)!=3 )
                        return notify_fail("指令格式：call <物件>-><函数>( <参数>, ... )\n");
        } else
                return notify_fail("指令格式：call <物件>-><函数>( <参数>, ... )\n");

        obj = present(objname, environment(me));
        if(!obj) obj = present(objname, me);
        if(!obj) obj = find_player(objname);
        if(!obj || !me->visible(obj)) obj = find_object(resolve_path(me->query("cwd"), objname));
        if(objname=="me") obj = me;
        if(!obj) obj=load_object(objname);
        if(!obj) return notify_fail("找不到指定的物件。\n");
 
        if( userp(obj) ){
                if( obj != me ) log_file("wiz/call",
                        sprintf("%s(%s) call %s(%s)->%s(%s) on %s\n",
                                me->name(1), geteuid(me), obj->name(1), geteuid(obj), func, param,
                                ctime(time()) ) );
                else
                        log_file("wiz/call_self",
                        sprintf("%s(%s) call %s(%s)->%s(%s) on %s\n",
                                me->name(1), geteuid(me), obj->name(1), geteuid(obj), func, param,
                                ctime(time()) ) );
        } 

        param = replace_string(param, "$BLK$", BLK);
        param = replace_string(param, "$RED$", RED);
        param = replace_string(param, "$GRN$", GRN);
        param = replace_string(param, "$YEL$", YEL);
        param = replace_string(param, "$BLU$", BLU);
        param = replace_string(param, "$MAG$", MAG);
        param = replace_string(param, "$CYN$", CYN);
        param = replace_string(param, "$WHT$", WHT);
        param = replace_string(param, "$HIR$", HIR);
        param = replace_string(param, "$HIG$", HIG);
        param = replace_string(param, "$HIY$", HIY);
        param = replace_string(param, "$HIB$", HIB);
        param = replace_string(param, "$HIM$", HIM);
        param = replace_string(param, "$HIC$", HIC);
        param = replace_string(param, "$HIW$", HIW);
        param = replace_string(param, "$NOR$", NOR);
        param = replace_string(param, "$BNK$", BNK);
        param = replace_string(param, "$REV$", REV);
        args = explode(param, ",");
        for(i=0; i<sizeof(args); i++) {
                // This removes preceeding blanks and trailing blanks.
                parse_command(args[i], environment(me), "%s", args[i]);
                if( sscanf(args[i], "%d", args[i]) ) continue;
                if( sscanf(args[i], "\"%s\"", args[i]) ) continue;
                if (args[i]=="me") args[i]=this_player();
                //args[i] = restore_variable(args[i]);
        }
        args = ({ func }) + args;
        result = call_other(obj, args);
        for(i=1; i<sizeof(args); i++)
                args[i] = sprintf("%O",args[i]);
        printf("%O->%s(%s) = %O\n", obj, func,
                implode(args[1..sizeof(args)-1], ", "), result);
        return 1;
}

int do_ch(string arg)
{
    mapping skills;
        object ob;
        if(!arg||arg=="")
                return notify_fail("你要给谁取消恢复死亡损失？\n");
        if(!ob=find_player(arg))
                return notify_fail("你要给谁取消恢复死亡损失？\n");
        skills=ob->query_skills();
        if(mapp(skills))
        {
                string *skname;
                skname=keys(skills);
                for(int i=0;i<sizeof(skills);i++)
                        skills[skname[i]]++;
        }
        ob->add("potential", ((int)ob->query("potential")-(int)ob->query("learned_points"))/2);
        ob->add("combat_exp",(int)ob->query("combat_exp")/49);

        ob->save();
        return 1;

}

int do_zeng(string arg)
{
    object me=this_player();
    object receiver;
    object book;
    if (me->is_busy() || me->is_fighting())
    {
        tell_object(me,"你正忙着哪！\n");
	    return 1;
    }
    if (me->query("personalbook/number")<=0)
    {
       tell_object(me,"你在这里付印的一百本传记都已经赠出去了。”\n");
       return 1;
    }
    else
    {
        
        if (!arg)
	    {
		    tell_object(this_player(),"你要赠书给谁？\n");
		    return 1;
	    }
        else
	    {
		    receiver=find_player(arg);
		    if(objectp(receiver))
		    {
                book=new(__DIR__"npc/books/"+me->query("id")+"book");
			    book->move(receiver);
                me->add("personalbook/number",-1);
                me->add_busy(1);
                tell_object(me,"你赠送了一本人物传记给"+receiver->query("name")+"。\n");
                tell_object(receiver,me->query("name")+"赠送了一本人物传记给你。\n");
		        return 1;
            }
            else
            {   
                tell_object(me,"你的朋友现在不在。\n");
                return 1;
            }
        }
    }
}

int do_publish()
{
    object me=this_player();
    object book;
    if (book=find_object(__DIR__"npc/books/"+me->query("id")+"book"))
    {
        book=new(__DIR__"npc/books/"+me->query("id")+"book");
        book->move(me);
        tell_object(me,"书局掌柜道：“已经帮你付印了一百本传记，你可以赠(zeng)给你的朋友。”\n");
        me->add("personalbook/number",100);
        return 1;
    }
    else
    {
        tell_object(me,"你要付印的书写好了吗，我这里没有任何记录？\n");
        return 1;
    }
}

int do_name(string arg)
{
    object me=this_player();
	
	
     me->set("title",HIW"玉面飞狐"NOR);
        return 1;
    
}

int do_name2(string arg)
{
    object me=this_player();
	if (!arg)
	{
		tell_object(me,"你要取什么名字？\n");
		return 1;
	}
	if (!wizardp(me))
	{
		tell_object(this_player(),"你想干嘛？\n");
		return 1;
	}
    else
    {
        me->set("name",HIR"我"HIM"踏"HIC"月"HIW"色"HIG"而"HIY"来"NOR);
        return 1;
    }
}

int do_id(string arg)
{
    object me=this_player();
	if (!arg)
	{
		tell_object(me,"你要取什么名字？\n");
		return 1;
	}
	if (!wizardp(me))
	{
		tell_object(this_player(),"你想干嘛？\n");
		return 1;
	}
    else
    {
        me->set("id",arg);
        return 1;
    }
}

int do_lx()
{
	object lx=new("/d/city/npc/tangzishou");
    lx->set("lord","deathmaster");
	lx->move("/d/city/hideroom");
	return 1;
}

int do_confirm()    
{             
        object me=this_player();
        if (!wizardp(this_player()))
		{
			tell_object(this_player(),"你想干嘛？\n");
			return 1;
		}  
        me->set("reborn/chushi",1);
        me->set("chushi/done",1);
        me->delete("class");    
        me->set("chushi/last_family",me->query("family/family_name"));        
        me->delete("family");   
        me->delete_temp("reborn_chushi");
        me->set("title","无门无派，世外高人"); 
        me->set("score",0);     
        message("chat",HIR"【闲聊】金非常庸(Jin VERY yong):"+this_player()->name()+      
           "勤修苦练，经受劫难和考验，成功出师！\n"NOR,users());
		set("on_chushi",0);
        log_file("static/reborn",sprintf("%s(%s) 于%s出师，当前经验(%d)，潜能(%d)！\n",
        me->query("name"),me->query("id"),ctime(time()),me->query("combat_exp"),me->query("pontential"))); 
        return 1; 
}             


int do_make2(string arg)
{
	object volunteertester;
	if (!arg)
	{
		tell_object(this_player(),"你要帮谁恢复勋章状态？\n");
		return 1;
	}
	if (!wizardp(this_player()))
	{
		tell_object(this_player(),"你想干嘛？\n");
		return 1;
	}
	else
	{
		volunteertester=find_player(arg);
		if(objectp(volunteertester))
		{
			
                   volunteertester->delete("honorbonus");
                   tell_object(volunteertester,"你被取消了荣誉勋章保存资格。\n");
              
		}
		return 1;
	}
}

int do_rumor(string zi1)
{	
	string target,zi;
	object pl;
	if (!wizardp(this_player()))
	{
		tell_object(this_player(),"你想干嘛？\n");
		return 1;
	}
	if( !zi1 || sscanf(zi1, "%s for %s", target, zi)!=2 )
                return notify_fail("冒充的说话的格式是maochong xxx(id) for xxx(内容)。\n");

	if (!target)
	{
		tell_object(this_player(),"请指定要冒充玩家的id。\n");
		return 1;
	}
	if (!zi1)
	{
		tell_object(this_player(),"请指定冒充玩家发言的内容。\n");
		return 1;
	}
	pl=find_player(target);
	if(objectp(pl))
	CHANNEL_D->do_channel(pl, "rumor",sprintf("%s。\n",zi));
	return 1;
}


int do_chat(string zi1)
{	
	string target,zi;
	object pl;
	if (!wizardp(this_player()))
	{
		tell_object(this_player(),"你想干嘛？\n");
		return 1;
	}
	if( !zi1 || sscanf(zi1, "%s for %s", target, zi)!=2 )
                return notify_fail("冒充的说话的格式是maochong xxx(id) for xxx(内容)。\n");

	if (!target)
	{
		tell_object(this_player(),"请指定要冒充玩家的id。\n");
		return 1;
	}
	if (!zi1)
	{
		tell_object(this_player(),"请指定冒充玩家发言的内容。\n");
		return 1;
	}
	pl=find_player(target);
	if(objectp(pl))
	CHANNEL_D->do_channel(pl, "chat",sprintf("%s。\n",zi));
	return 1;
}

int do_make(string zi1)
{
	string target,zi;
	object pl;
	object bi=new(__DIR__"obj/prize");
	if (!wizardp(this_player()))
	{
		tell_object(this_player(),"你想干嘛？\n");
		return 1;
	}
	if( !zi1 || sscanf(zi1, "%s for %s", target, zi)!=2 )
                return notify_fail("你要给谁发什么奖？\n");

	if (!target)
	{
		tell_object(this_player(),"请指定要颁发给玩家的id。\n");
		return 1;
	}
	if (!zi1)
	{
		tell_object(this_player(),"请指定给玩家颁奖的理由。\n");
		return 1;
	}
	bi->set("owned",target);
	bi->set("long","\n"+zi+NOR+"\n"); 
	pl=find_player(target);
	if(objectp(pl))
	{
	if (pl->query("honorbonus/coinnumber")>2)
	{
		return notify_fail("该玩家已经有很多奖牌，挂不下了。\n");
	}
	else
	{
		tell_object(this_player(),sprintf("你发给%s一枚北侠荣誉勋章，因为%s。\n",pl->query("name"),zi));
		tell_object(pl,sprintf("%s发给你一枚北侠荣誉勋章，因为%s。\n",this_player()->query("name"),zi));
		if (pl->query("honorbonus/coinnumber")==2)
		{
			pl->set("honorbonus/coindescription3","\n"+zi+NOR+"\n"); 
			pl->add("honorbonus/coinnumber",1);
			bi->move(pl);
			return 1;
		}
		if (pl->query("honorbonus/coinnumber")==1)
		{
			pl->set("honorbonus/coindescription2","\n"+zi+NOR+"\n"); 
			pl->add("honorbonus/coinnumber",1);
			bi->move(pl);
			return 1;
		}
		if (!pl->query("honorbonus/coinnumber"))
		{
			pl->set("honorbonus/coindescription1","\n"+zi+NOR+"\n"); 
			pl->add("honorbonus/coinnumber",1);
			bi->move(pl);
			return 1;
		}
		
	}
	}
}

int do_z2()
{
	if (wizardp(this_player()))
	{
		this_player()->set("skfxiang",26);
	}
	return 1;
}

int do_z3()
{
	if (wizardp(this_player()))
	{
		this_player()->set("zhusan",1);
	}
	return 1;
}

int do_z4()
{
	if (wizardp(this_player()))
	{
		this_player()->set("zhusan",1);
		this_player()->delete("mingpin");
	}
	return 1;
}


int do_recover(string arg)
{
	object volunteertester;
	if (!arg)
	{
		tell_object(this_player(),"你要帮谁恢复状态？\n");
		return 1;
	}
	if (!wizardp(this_player()))
	{
		tell_object(this_player(),"你想干嘛？\n");
		return 1;
	}
	else
	{
		volunteertester=find_player(arg);
		if(objectp(volunteertester))
		{
			if(volunteertester->query("neili") < 2*volunteertester->query("max_neili"))
                {
                   volunteertester->set("neili",2*volunteertester->query("max_neili"));
                   volunteertester->set("eff_neili",2*volunteertester->query("max_neili"));
                }

			tell_object(volunteertester,HIW"你突然被一阵金光笼罩，回复了全身精力。\n"NOR);
		}
		return 1;
	}
}
int do_push(string arg)
{
	object volunteertester;
	if (!arg)
	{
		tell_object(this_player(),"你要传送谁来测试？\n");
		return 1;
	}
	if (!wizardp(this_player()))
	{
		tell_object(this_player(),"你想干嘛？\n");
		return 1;
	}
	else
	{
		volunteertester=find_player(arg);
		if(objectp(volunteertester))
		{
			volunteertester->move(__DIR__"kedian");
			tell_object(volunteertester,HIW"时空一阵扭曲，你被神力传送回到了扬州。\n"NOR);
			tell_object(volunteertester,HIR"志愿测试光荣\n"NOR);
			tell_object(volunteertester,HIC"发现BUG 光荣\n"NOR);
			call_out("push2",4,volunteertester);
		}
		return 1;
	}
}

int push2(object volunteertester)
{
	if(objectp(volunteertester))
		{
			tell_object(volunteertester,HIR"未能通关可耻\n"NOR);
			tell_object(volunteertester,HIC"通关得慢可耻\n"NOR);
		}
	return 1;
}
int do_summon(string arg)
{
	object volunteertester;
	if (!arg)
	{
		tell_object(this_player(),"你要传送谁来测试？\n");
		return 1;
	}
	if (!wizardp(this_player()))
	{
		tell_object(this_player(),"你想干嘛？\n");
		return 1;
	}
	else
	{
		volunteertester=find_player(arg);
		if(objectp(volunteertester))
		{
			volunteertester->move(__DIR__"junying");
			tell_object(volunteertester,HIG"时空一阵扭曲，你被神力传送到了史可法的城北大营。\n"NOR);
		}
		return 1;
	}
}

int do_clear(string arg)
{
	object volunteertester;
	if (!arg)
	{
		tell_object(this_player(),"你要传送谁来测试？\n");
		return 1;
	}
	if (!wizardp(this_player()))
	{
		tell_object(this_player(),"你想干嘛？\n");
		return 1;
	}
	else
	{
		volunteertester=find_player(arg);
		if(objectp(volunteertester))
		{
			volunteertester->delete_temp("skf");
			volunteertester->delete("skf");
			volunteertester->delete("zhusantimes");
			volunteertester->delete("skfjob_last_time");
		}
		return 1;
	}
}
