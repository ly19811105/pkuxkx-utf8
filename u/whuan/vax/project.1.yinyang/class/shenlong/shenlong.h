// shenlong.h for join shenlongjiao
#include <ansi.h>;

int do_join(string arg)
{
	object me, ob, obj ;
	string men;
	mapping party;

	me = this_object () ;
	ob = this_player () ;

	if( !arg || arg!="shenlongjiao" )
		return notify_fail("你要加入什么组织？\n"); 

	if ((int)ob->query("shen") > 0)
	{
	message_vision(HIR"$N对$n大怒道：还想入教？一看你就不是好人! \n"NOR,me,ob);
		set_leader(this_player());
		remove_call_out("kill_ob");
		me->kill_ob(ob); 
		return 1;
	}

//	if( !mapp(party = ob->query("party")) || party["party_name"] != HIY "神龙教" NOR )
	if(  ob->query("party") && ob->query("party/party_name") != HIY "神龙教" NOR )
	{
		message_vision("$N摇摇头，对$n说道：你已经加入其他帮会了，不能再入我神龙教。\n",me,ob);
		return 1;
	}
	if( ob->query("party/party_name") == HIY "神龙教" NOR )
	{
		message_vision("$N摇摇头，对$n说道：你已经是我神龙教的人了。\n",me,ob);
		return 1;
	}
	if ( (string)ob->query("gender") == "女性" ) men=HIR"赤";
	else
	{
		switch (random(4))
		{
		case 0 : men=HIG"青"; break;
		case 1 : men=HIW"白"; break;
		case 2 : men=BLU"黑"; break;
		default: men=YEL"黄"; break;
		}
	}
	party = allocate_mapping(5);
	party["party_name"] = HIY "神龙教" NOR;
	party["rank"] = men+"龙使"NOR"座下教众";
	party["level"] = 1;
	party["tasks"] = 0;
	party["enter_time"] = time();
	ob->set("party", party);
	//LOG_D->do_log( ob, "你开始在"+HIY "神龙教"NOR+men+"龙使"NOR+"座下效力。" );
	command("smile");
	write("\n");
	message_vision("$N对$n说道：你就暂时在"+men+"龙使"NOR+"座下效力吧！\n", me, ob);

	return 1;
}

