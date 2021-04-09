//quest of vworld
//Made by jason@indeed for vworld
//2001.2.23

#include <ansi.h>
inherit NPC;

int give_quest(object,object);

mixed random_place(string);

string *cannot_file=({
	
});

/*mapping main_dir=([
        "/d/huashan":"华山",
        "/d/wudang":"武当山",
        "/d/shaolin":"少林寺",
        "/d/gumu":"古墓",
        "/d/daili":"大理",
        "/d/pker":"杀手帮",
        "/d/taishan":"泰山",
        "/d/xiangyang":"襄阳",
        "/d/xingxiu":"星宿",
        "/d/quanzhou":"泉州",
        "/d/village":"小山村",
        "/d/quanzhen":"全真",
        "/d/taohuadao":"桃花岛",
        "/d/pingxiwangfu":"平西王府",
        "/d/riyuejiao":"日月神教",
        "/d/gaibang":"丐帮",
        "/d/diaoyudao":"钓鱼岛",
        "/d/mingjiao":"明教",
        "/d/guiyunzhuang":"归云庄",
]);*/
mapping main_dir=([
"/d/city":"扬州",
]);
void init()
{
	add_action("ask_quest","askjob");
	add_action("do_cancel","cancel");
	add_action("do_report","report");
}

int ask_quest() //give quest
{
	object ppl=this_player();
	object ob=this_object();
	
	
	if(ppl->query_temp("quest"))
	{
		write("你不是还有任务没有完成吗？\n");
		return 1;
	}
	give_quest(ob,ppl);
	return 1;
	
	
}

int do_cancel() //cancel quest
{
	object ob=this_object(),ppl=this_player();
	int hor_re,exp_re,mon_re,mor_re;
	if(!ppl->query_temp("quest"))
	{
		write("你不是正闲着吗？偷懒可不好啊！\n");
		return 1;
	}
	if(ppl->query_temp("quest/quest_npc")!=query("id"))
	{
		write("不想做事找让你作的人去啊。\n");
		return 1;
	}
	
	command("sigh");
	command("say 如今的人啊，个个好吃懒做。好吧，你不作就不作吧。");
	command("say 等等，得给你点惩罚才行。");
	if(query("rewards"))
	{
		mapping rewards=query("rewards");
		string *key;
		int *value;
		if(sizeof(rewards)==0) 
		{
			command("say 看在这个任务不是很重要的分上，就不惩罚你了。");
			return 1;
		}
		key=keys(rewards);
		value=values(rewards);
		for(int i=0;i<sizeof(key);i++)
		{
			ppl->add(key[i],-value[i]/3);
			write("你受到了"+value[i]/3+"点"+key[i]+"的惩罚!\n");
		}
	}
	//message("vision","你受到了"+chinese_number(exp_re)+"点经验和\n"+
	//chinese_number(hor_re)+"点荣誉的惩罚。\n",ppl);
	ppl->delete_temp("quest");
	return 1;
}

int do_report() //report quest
{
	object ob=this_object(),ppl=this_player();
	int exp_re,hor_re,mor_re,mon_re;
	if(ppl->query_temp("quest/quest_npc")!=query("id"))
	{
		command("hehe");
		command("say 我不认识你耶。");
		return 1;
	}
	if(!ppl->query_temp("quest/quest_done"))
	{
		write("你还没有完成任务。\n");
		return 1;		
	}
	if(ppl->query_temp("quest/quest_npc")!=query("id"))
	{
		write("跟你师傅领赏去!\n");
		return 1;
	}
	command("smile");
	command("say 好，作的好。");
	if(query("rewards"))
	{
		mapping rewards=query("rewards");
		string *key;
		int *value;
		if(sizeof(rewards)==0) 
		{
			command("say 这个任务太简单了，你就当是作好事吧。");
			return 1;
		}
		key=keys(rewards);
		value=values(rewards);
		for(int i=0;i<sizeof(key);i++)
		{
			ppl->add(key[i],value[i]*ppl->query_temp("quest/quest_level"));
			write("你受到了"+value[i]*ppl->query_temp("quest/quest_level")+"点"+key[i]+"的奖励!\n");
		}
	}
	ppl->delete_temp("quest");
	return 1;
}



int give_quest(object ob,object me)
{
	string *quest_list;
	mapping tmp;
	string *city,cname,id,id2,name,city_dir;
	function f;
	string fnc;
	string city_name,city_cname;
	object room,npc;
	if(me->query("age")>19)
	{
		message("vision","你这么大了还作这种弱智的事情啊！！！\n",me);
		return 1;
	}
	if(me->query_temp("quest"))
	{
		message("vision","你还有任务没有完成那！\n",me);
		return 1;
	}
	if(!function_exists("quest",this_object()))
	{
		message("vision","现在没有什么任务，你稍后再来。\n",me);
		return -1;
	}
	//main_dir=CITYS_D->query_city_list();
	/*if(sizeof(main_dir)<=0) 
	{
		message("vision","虚拟世界目前还没有注册的城市，任务系统不能工作！\n",me);
		return -2;
	}*/
	
	city=keys(main_dir);
	
	if(query("quest_room"))
	{
		string *quest_room=query("quest_room");
		string room_s=quest_room[random(sizeof(quest_room))];
		if(sscanf(room_s,"/d/%s/%*s",city_name)!=2)
		{
			write(room_s+"\n");
			write(city_name+"\n");
			message("vision","现在没有什么任务，你稍后再来。xixi\n",me);
				return -1;
		}
		if(!objectp(room=load_object(room_s)))
		{
			message("vision","现在没有什么任务，你稍后再来。\n",me);
			return -1;
		}
	}
	else if(arrayp(query("quest_city")))
	{
		string *quest_city=query("quest_city");
		string qc=quest_city[random(sizeof(quest_city))];
		if(member_array(qc,city)==-1)
		{
			message("vision","现在没有什么任务，你稍后再来。\n",me);
			return -1;
		}
		city_dir="/d/"+qc;
		if(!objectp(room=random_place(city_dir)))
		{
			message("vision","现在没有什么任务，你稍后再来。\n",me);
			return -1;
		}
	}
	else
	{
		city_dir=city[random(sizeof(city))];
		if(!objectp(room=random_place(city_dir)))
		{
			message("vision","现在没有什么任务，你稍后再来。\n",me);
			return -1;
		}
	}
	
	me->add_temp("quest/quest_level",1);
	if(me->query_temp("quest/quest_level")>9) 
		me->set_temp("quest/quest_level",4);
	if(!query("job_name")) 
		me->set_temp("job_name","工作");
	else 
		me->set_temp("quest/job_name",query("job_name"));
	if(query("job_time")) 
		me->set_temp("quest/quest_time",query("job_time"));
	else 
		me->set_temp("quest/quest_time",120+random(100));
	me->set_temp("quest/begin_time",time());
	me->set_temp("quest/room",room->query("short"));
	me->set_temp("quest/quest_npc",query("id"));
	me->set_temp("quest/quest_room",base_name(room));
	if(!query("quest_room"))
		sscanf(city_dir,"/d/%s",city_name);
	tmp=main_dir;
	if(!mapp(tmp)||member_array(city_dir,keys(tmp))==-1||sizeof(tmp[city_dir])<1)
	{
		message("vision","现在没有任务。\n",me);
		me->delete_temp("quest");
		return 1;
	}
	city_cname=tmp["/d/"+city_name];
	npc=new("/job/sys/job_control");
	npc->set("wait_time",me->query_temp("quest/quest_time")+5);
	name=NAME_D->create_name();
	sscanf(name,"%s@%s %s",cname,id,id2);
	npc->set_name(cname,({id+" "+id2,id}));
	f=bind((:call_other,base_name(this_object()),"quest":),npc);
	//将相应的函数bind到特定的npc身上。
	npc->move(room);
	npc->set("quest_func",f);
	npc->go_leave();
	room->set("quest/have_bind",1);//任务系统bind过的房间作上标记
	message("vision","在"+city_cname+"的"+room->query("short")+"有任务等着你，快点去吧。\n",me);
	if(wizardp(me)&&me->query("env/debug"))
	write(base_name(room)+"\n");
}

//random_place function

mixed random_place(string addrname)
{
        int   j, err,time=0;
        object  room;
        mixed*  file, exit;
        string address,address1;
        file = get_dir( addrname+"/*.c");
        if( !sizeof(file) ) return 0;
	j = random(sizeof(file));
        address1 = addrname+"/"+file[j];	
	while(1&&time<20)
	{ 
		time++;
		j = random(sizeof(file));
           	address1 = addrname+"/"+file[j];	   
           	if( member_array(address, cannot_file) == -1 )
           	{
           		err = catch(call_other(address1, "??"));
			if(err) continue;
			else if( !(room = find_object(address1)) )
				continue;
			if( !(exit=room->query("exits")) || sizeof(exit)<1)
			   	continue;
			if(room->query("quest/have_bind")) continue;
			//bind 过的房间不能再bind
/*			if(query("permit_character"))//有特定属性要求的地域
			{
				string *character=query("permit_character");
				if(member_array(room->query("character"),character)==-1)
					continue;
			}
*/
			return room;
					      	
	   	}
	 }
	return -1;
}




