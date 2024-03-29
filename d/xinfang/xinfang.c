// Modified by iszt@pkuxkx, 2007-04-26

#include <dbase.h>
#include <move.h>
#include <ansi.h>
#include "/d/xinfang/store_limit.h"
inherit ROOM;
inherit F_UNIOBJ;

int do_out();
int do_go(string);
int do_chat(string arg);
int destme();
int do_invite(string);
int do_modify(string);
int do_store(string);

int do_reject(string);
int do_getout(string);
int do_kickout(string);
int do_none();

int do_update(string);
void reset();

void create()
{
	set("short",GRN""NOR);
	set("long","空空如也的新家。\n");
	set("exits", ([
		"out" : __DIR__"bieshuqu",
//                "down" : "/u/iszt/testroom",
	]));

	set("sleep_room",1);
	set("change_name",0);
	set("max_contain_items",50);
	set("is_xinfang",1);
	setup();
}
void init_equips(object me)
{
	object old_lu,lu;
	if (query("owner")!=me->query("id"))
	return;
	if (time()<me->query("RentFurnace/time"))
	{
		lu=new("/obj/remedy/furnace");
		if (old_lu=present(lu->query("id"),this_object()))
		destruct(old_lu);
		lu->set("furnace_lv",me->query("RentFurnace/FurnaceLv"));
		lu->set("capacity",30);
		lu->set("long","这是被租用给"+me->query("name")+"的药炉。\n");
		lu->set("no_get","药炉太重了，根本拿不起来。\n");
		lu->set("LongTerm",me->query("RentFurnace/time"));
		lu->move(this_object());
	}//init药炉
	if (time()<me->query("RentCabinet/time"))
	{
		lu=new("/obj/remedy/cabinet");
		if (old_lu=present(lu->query("id"),this_object()))
		destruct(old_lu);
		me->set("RentCabinet/Cabinet",lu);
		lu->move(this_object());
	}//inity药柜
	return;
}
void init()
{	
    string from;

	add_action("do_out","out");
    add_action("do_go", "go");
    add_action("do_chat","chat");
    add_action("do_chat","chat*");
    add_action("do_invite","invite");
    add_action("do_reject","reject");
    add_action("do_modify","modify");
    add_action("do_modify_short","modify_short");
    add_action("do_getout","getout");
    add_action("do_kickout","kickout");
    add_action("do_none","kill");
    add_action("do_none","killall");
    add_action("do_none","attack");
    add_action("do_store","store");
    add_action("do_check","find");
	init_equips(this_player());
    if(time() - this_player()->query("killer/time") < 15*60)
    {
        write("你刚杀了人就想躲在家里吗？\n");
        this_player()->move(this_player()->query_temp("xinfang/from"));
        this_player()->add_busy(3);
    }
    from = this_player()->query_temp("xinfang/from");
}

int do_update(string arg)
{
	string err;
	err = catch( call_other("/adm/daemons/securityd.c", "???") );
	if (err)
		printf( "发生错误：\n%s\n", err );
	else
		write("成功！\n");
	return 1;
}

int do_out()
{
	object *inv;
	object obj;
	int i,count=0;
	if (this_player()->is_busy())
    {
        write("瞧你手忙脚乱的，打的开门吗？\n");
        return 1;
    }
	message("vision", this_player()->name() + "大步走了出去。\n",
		environment(this_player()), ({this_player()}) );

    if (this_player()->query_temp("xinfang/from"))
    {
        this_player()->move(this_player()->query_temp("xinfang/from"));
    }
    else
    {
        write("你是怎么混进来的？关门...放狗!\n");
        return 1;
    }
    this_player()->delete_temp("xinfang/from");
 
	tell_room(environment(this_player()),this_player()->query("name")+"走了出来。\n",({this_player()}));		  
	obj=this_object();
	inv=all_inventory(obj);
	if (sizeof(inv)==0)
		 call_out("destme",0);
	else
	{
		for(i=0;i<sizeof(inv); i++) 
			if (userp(inv[i])) count++;
		if (count==0)		
			call_out("destme",3600);
	}
	return 1;
}

int do_go(string arg)
{
    if (arg == "out") return do_out();
    else return 0;
}

int destme()
{
    object* inv;
    int count = 0;
    int i = 0;
	inv=all_inventory();    
    if(sizeof(inv) == 0)
    {
        destruct(this_object());
    }
    else 
    {
		for(i=0;i<sizeof(inv); i++) 
			if (userp(inv[i])) count++;
		if (count==0)		
			destruct(this_object());
    
    }
	return 1;
}

int do_invite(string arg)
{
	object my_friend, me;

    me = this_player();
	if (query("owner")!=me->query("id"))
	{
		write("你不是这个房间的主人！\n");
		return 1;
	}
	if (!arg || !find_player(arg))
	{
		write("有这个人在线上？\n");
		return 1;
	}

	my_friend=find_player(arg);
	if (me->visible(my_friend))
		write("好的。\n");
	else
	{
		write("有这个人在线上？\n");
		return 1;
	}
	if (arg==me->query("id"))
	{
		write("没事闲的邀请自己玩？比我还幽默，你真行！\n");
		return 1;
	}
	my_friend->set_temp("invited",me->query("id"));
	tell_object(my_friend,HIG+me->query("name")+"("+me->query("id")+")"+HIG+"邀请你去"
                +((me->query("gender")=="女性")?"她":"他")+"在"
                +load_object(me->query_temp("xinfang/from"))->query_location_name()+"的家呢！\n"NOR);
	write("已经帮你邀请了！\n");
	return 1;
}

int do_reject(string arg)
{	
    object guest;
	if (query("owner")!=this_player()->query("id"))
	{
		write("你不是这个房间的主人！\n");
		return 1;
	}
	if (!arg || !find_player(arg))
	{
		write("有这个人在线上？\n");
		return 1;
	}
    guest = find_player(arg);
    if(!this_player()->visible(guest))
    {
		write("有这个人在线上？\n");
		return 1;
    }
	if (arg==this_player()->query("id"))
	{ 
		write("你有病啊！拒绝自己！\n");
		return 1;
	}
	if (find_player(arg)->query_temp("invited")!=this_player()->query("id"))
	{
		write("当前他并没有受到你的邀请！\n");
		return 1;
	}
	find_player(arg)->delete_temp("invited");
	tell_object(find_player(arg),this_player()->query("name")+"收回了他(她)对您的邀请！\n");
	write("OK！\n");
	return 1;
} 

int do_modify( string arg)
{
	if (!arg) 
	{
		write("要把你的房间修饰成什么样子呢？\n");
		return 1;
	}
	if (this_player()->query("id")==this_object()->query("owner"))
	{	
		arg = replace_string(arg, "$BNK$", BNK);
		arg = replace_string(arg, "$BLK$", BLK);
		arg = replace_string(arg, "$RED$", RED);
		arg = replace_string(arg, "$GRN$", GRN);
		arg = replace_string(arg, "$YEL$", YEL);
		arg = replace_string(arg, "$BLU$", BLU);
		arg = replace_string(arg, "$MAG$", MAG);
		arg = replace_string(arg, "$CYN$", CYN);
		arg = replace_string(arg, "$WHT$", WHT);
		arg = replace_string(arg, "$HIR$", HIR);
		arg = replace_string(arg, "$HIG$", HIG);
		arg = replace_string(arg, "$HIY$", HIY);
		arg = replace_string(arg, "$HIB$", HIB);
		arg = replace_string(arg, "$HIM$", HIM);
		arg = replace_string(arg, "$HIC$", HIC);
		arg = replace_string(arg, "$HIW$", HIW);
		arg = replace_string(arg, "$NOR$", NOR);
		this_object()->set("long","\n"+arg+NOR+"\n");  
		this_object()->delete_temp("mixed_long");
		this_player()->set("myroom/long","\n"+arg+NOR+"\n");
		write("ok!\n");
	}
	else 
	{
		write("别人的房你也要搀和搀和？\n");
	}
	return 1;
}
 
int do_modify_short( string arg)
{
	if (!arg) 
	{
		write("要给你的房子取个什么名字？\n");
		return 1;
	}
	if (this_player()->query("id")==this_object()->query("owner"))
	{	
		arg = replace_string(arg, "$BNK$", BNK);
		arg = replace_string(arg, "$BLK$", BLK);
		arg = replace_string(arg, "$RED$", RED);
		arg = replace_string(arg, "$GRN$", GRN);
		arg = replace_string(arg, "$YEL$", YEL);
		arg = replace_string(arg, "$BLU$", BLU);
		arg = replace_string(arg, "$MAG$", MAG);
		arg = replace_string(arg, "$CYN$", CYN);
		arg = replace_string(arg, "$WHT$", WHT);
		arg = replace_string(arg, "$HIR$", HIR);
		arg = replace_string(arg, "$HIG$", HIG);
		arg = replace_string(arg, "$HIY$", HIY);
		arg = replace_string(arg, "$HIB$", HIB);
		arg = replace_string(arg, "$HIM$", HIM);
		arg = replace_string(arg, "$HIC$", HIC);
		arg = replace_string(arg, "$HIW$", HIW);
		arg = replace_string(arg, "$NOR$", NOR);
		this_player()->set("myroom/short",arg+NOR);
		this_object()->set("short",arg+NOR);
		write("ok!\n");
	}
	else 
	{
		write("别人的房你也要搀和搀和？\n");
	}
	return 1;
}
//******************************************************//
int do_store(string arg)
{ 
	 object ob,me,lover;
	 mapping this_store;
	 mapping *all_ob;
	 string *autoloads;
	 string name;
	 object *list;
	 int i;
	 int find;

	 me=this_player();
	 name=me->query("marry/lover");
 
//iszt@pkuxkx, 2007-02-08
//	if(me->query("id")!=this_object()->query("owner")
//		&&name!=this_object()->query("owner"))
	if(me->query("id")!=this_object()->query("owner"))
		return notify_fail("你发神经呀，好好的把自己的东西往别人家里存？\n"); 
	if( !arg||!(ob = present(arg, this_player())) )
		return notify_fail("你要把什么放到储藏柜里呢？\n");
	if( ob->query("money_id") )	  
		return notify_fail("你要把钱往柜子里放，但又觉得不保险，只得作罢！\n");
	if( (int)ob->query("skill_type") && (int)ob->query("rigidity")<50) return notify_fail("一把破破烂烂的兵器不值得保存！\n");
	if( first_inventory(ob))
		return notify_fail("还是先把"+ob->name()+"里面的东西取出来再往柜子里放吧。\n");
	if (ob->is_character())
		return notify_fail("活物可不能生塞到柜子里呀！\n");
	if(ob->query("no_store"))
		return notify_fail("这个东西不值得保存!\n");
	if(ob->is_gems())
		return notify_fail("这个宝物最好还是存放在荣宝斋吧!\n");
	if(ob->query("unique"))
		return notify_fail("这种宝物你也敢存在家里？亏你也想得出来!\n");
	if(!ob->query("value"))
		return notify_fail("这个东西不值得保存!\n");
	if(ob->query("task_owner"))
		return notify_fail("task物件不能存放。\n");
	all_ob = me->query("store_ob");
	if (name == query("owner"))
	{
		list = users();
		i = sizeof(list);
		find = 0;
		while (i--)
		{
			if (list[i]->query("id") == name)
			{
				lover = list[i];
				find = 1;
			}
		}
		if (find != 1)
		{
			if (objectp(LOGIN_D->find_body(name)))
			{
				tell_object(me,"对不起，你的爱人现在处于断线状态，请等待爱人重新连线或完全退出。\n");
				return 1;
			}
		READWRITE_D->file_write("/d/xinfang/temproom","/data/user/"+name[0..0]+"/"+name,1);
		lover= new("/clone/user/tempuser");
		}
		all_ob = lover->query("store_ob");
	}

	if(!all_ob) all_ob = ({});
	if (sizeof(all_ob)>=room_limit(me))
	return notify_fail("柜子里已经塞了太多的东西了，如果要存放更多，把你家里或者榷场存的东西清一清吧。\n");
  if (ob->query("equipped")) ob->unequip();
	this_store = ([ ]);
	this_store["file"] = base_name(ob);
	this_store["name"] = ob->name();
	this_store["attribute"] = ob->query("attribute");
	if ( ob->query_amount()>0 )
	  this_store["number"] = ob->query_amount();
	else
	  this_store["number"] = 0;

	if (name == query("owner"))
	{
		if ( arrayp(autoloads = lover->query("auto_load")) &&
			member_array( this_store["file"] + ".c", autoloads ) != -1 )
		{
			autoloads -= ({ this_store["file"] + ".c" });
			lover->set("auto_load", autoloads);
		}
	}
	else if ( arrayp(autoloads = me->query("auto_load")) &&
		member_array( this_store["file"] + ".c", autoloads ) != -1 )
	{
		autoloads -= ({ this_store["file"] + ".c" });
		me->set("auto_load", autoloads);
	}

	all_ob += ({this_store});
	message_vision("$N把身上的" + ob->name() + "拿出来放进柜子里了。\n", me);

	if (name == query("owner"))
	{
		lover->set("store_ob",all_ob);
		if (!(find_player(name)))
		{
			lover->save();
			READWRITE_D->dest_ob(lover); 
		}
		else
			lover->save();
	}
	else
	{
		me->set("store_ob",all_ob);
		me->save();
	}
	destruct(ob);

	return 1;
}
/*******************************************/

int do_check()
{
	int i;
	string str,name;
	mapping this_store;
	mapping *all_store;
	object me,lover,ob;
	me=this_player();
	name = me->query("marry/lover");

//iszt@pkuxkx, 2007-02-08
//	if(me->query("id")!=this_object()->query("owner")
//		&& name!=query("owner"))
	if(me->query("id")!=this_object()->query("owner"))
	{
		write("你发神经呀，乱翻别人的柜子作什么？\n");
		return 1;
	}
	if (name == query("owner"))
	{
		if (!(lover=find_player(name)))	
		{
			ob = FINGER_D->acquire_login_ob(name);
			if (objectp(lover = LOGIN_D->make_body(ob)))
			lover->restore();
			destruct(ob);		
		}
		all_store = lover->query("store_ob");
		if (!find_player(name))
			READWRITE_D->dest_ob(lover); 
	}
	else {
		all_store = me->query("store_ob");}

		if(!all_store )
		{
			write("柜子里空空如也，啥也没有！\n");
			return 1;
		}

		write("\n柜子里目前存放的物品有：\n");
		for(i=0;i<sizeof(all_store);i++)
		{
			this_store = all_store[i];
			if(mapp(this_store))
			{
			  if ( this_store["number"]>0 )
			    str=sprintf("%d          %s〖%d〗\n",i,this_store["name"], this_store["number"]); 
			  else
				  str=sprintf("%d          %s\n",i,this_store["name"]); 
				write(str);
			}
		}
		all_store -= ({0});
		set("store_ob",all_store);
		return 1;
}

/**************************************************/
int do_getout( string arg )
{
	object ob,me,lover;
	int num, attribute;
	string file,err,aload,name,lovername;
	mapping this_store;
	mapping *all_store;
	object *list;
	int i;
	int find;

	me = this_player();
       if( me->is_busy() ) return notify_fail("你上一个动作还没有完成。\n");
	lovername = me->query("marry/lover");

//iszt@pkuxkx, 2007-02-28
//	if(me->query("id")!=this_object()->query("owner")
//		&& lovername!=query("owner"))
	if(me->query("id")!=this_object()->query("owner"))
		return notify_fail("你发神经呀，乱翻别人的柜子作什么？\n"); 

	notify_fail("你要把什么从柜子里拿出来？\n");
	if(!arg) return 0;
	if( !sscanf(arg, "%d" , num ) ) return 0;
	all_store = me->query("store_ob");
	if (lovername == query("owner"))
	{
		list = users();
		i = sizeof(list);
		find = 0;
		while (i--)
		{
			if (list[i]->query("id") == lovername)
			{
				lover = list[i];
				find = 1;
			}
		}
				
		if (find != 1)
		{
			if (objectp(LOGIN_D->find_body(lovername)))
			{
				tell_object(me,"对不起，你的爱人现在处于断线状态，请等待爱人重新连线或完全退出。\n");
				return 1;
			}

			READWRITE_D->file_write("/d/xinfang/temproom","/data/user/"+lovername[0..0]+"/"+lovername,1);
			lover= new("/clone/user/tempuser");
		}
		all_store = lover->query("store_ob");
	}
	if((num<0)|| (num>=sizeof(all_store)) )
		return 0;

	this_store = all_store[num];					
	file = this_store["file"] ;
	err = catch(ob = new(file));
	if( err || !ob )
	{
		write("你觉得似乎失落了什麽重要的东西，最好通知一下巫师。\n");
		log_file("AUTOLOAD", sprintf("Fail to autoload %s of %s, error \n",
		file, this_object()->query("name"), err));
		all_store[num] = 0;
		all_store -= ({0});
		me->set("store_ob",all_store);
		return 1;
	}
  
  if ( ob->query_amount()>0 ) 
  {
    if ( this_store["number"]>0 )
      ob->set_amount(this_store["number"]);
    else
      ob->set_amount(1);
  }
  
	export_uid(ob);
	if((int)me->query_encumbrance() + ob->weight()
		> (int)me->query_max_encumbrance() )
	{
		write(ob->name()+"对你来说太重了。\n");
		return 1;
	}
	ob->move(me);
	if( (name = this_store["name"]) != ob->name() )
		ob->set("name",name);
	attribute = this_store["attribute"];
	reset_attribute(me, ob, attribute);
	all_store[num] = 0;
	all_store -= ({0});

	if (lovername == query("owner"))
	{
		if(!sizeof(all_store))lover->delete("store_ob");
			else lover->set("store_ob",all_store);
		if ( ob->query("auto_load") )
			lover->add("auto_load", ({ base_name(ob) + ".c"}));
		if (!(find_player(lovername)))
		{
			lover->save();
			READWRITE_D->dest_ob(lover); 
		}
		else
			lover->save();
	}
	else
	{
		if(!sizeof(all_store))me->delete("store_ob");
		else me->set("store_ob",all_store);
 
		if ( ob->query("auto_load") && (sscanf(base_name(ob), "%*s/" + me->query("id") + "%*d") == 2) )
			me->add("auto_load", ({ base_name(ob) + ".c"}));

		me->save();
 	}
	message_vision("$N从柜子里取出了"+ob->name()+"\n",me );
	return 1;
}
int do_kickout(string arg)
{
	object target;
	object me;
	me=this_player();
	if (query("owner")!=me->query("id"))
	{
		write("你不是这个房间的主人！\n");
		return 1;
	}
	if (!arg || !find_player(arg))
	{
		write("有这个人在线上嘛?\n");
		return 1;
	}
		 
	if( !objectp(target = present(arg, environment(me))) )
	{
		write("这里没有 " + arg + "。\n");
		return 1;
	}
	if (wizardp(find_player(arg)))
	{
		write("巫师欢迎都来不及呢，你怎么好意思赶他走呢？\n");
		return 1;
	}
 
	if (me->visible(find_player(arg)))
	{	
		write("OK!\n");
	}
	else
	{	
		write("有这个人在线上嘛?\n");
		return 1;
	}
	if (arg==this_player()->query("id"))
	{ 
		write("你有病啊？脑子进水了吗？\n");
		return 1;
	}
	message("vision",me->name() + "客客气气的把"+find_player(arg)->name()+"请了出去。\n",environment(me), ({me}));	
	//find_player(arg)->move("/d/xinfang/bieshuqu");
	if (find_player(arg)->query_temp("xinfang/from"))
    {
        find_player(arg)->move(this_player()->query_temp("xinfang/from"));
    }
    else
    {
        write("你是怎么混进来的？你就呆在这里吧!\n");
        return 1;
    }
    find_player(arg)->delete_temp("xinfang/from");

	message("vision",me->name() + "如释重负，哐的一声把门关得严严实实！\n",environment(me), ({me}));
	tell_object(me,"你客客气气的把"+find_player(arg)->name()+"请了出去。\n");	
	tell_object(find_player(arg),me->query("name")+"如释重负，哐的一声把门关得严严实实！\n");
	return 1;
}
int do_none()
{
return 1;
}
int do_chat(string arg)
{
    object me=this_player();
    int my_kar,my_exp;
    int len;//arg的长度
    
    my_kar=(int)me->query_kar();
    my_exp=(int)me->query("combat_exp");
    len=strwidth(arg);
    
    if(  random(my_kar)>=15  
      && random(my_exp)<=500000
      && random(2)
      && random(len)>=5
      && me->query("chatting")>0
      && !me->query_condition("imp_chatting")
      ) 
      {
         me->apply_condition("imp_chatting",4);
         me->improve_skill("chatting",random(my_kar/3));
      }
    return 0;
}

void reset()
{
    object *inv;
    int i;

    inv=all_inventory();
    reset_eval_cost();
    for (i=0;i<sizeof(inv);i++)
    {
        if (inherits(CHARACTER, inv[i])) 
        {
            switch (base_name(inv[i]))
            {
            case "/d/luoyang/npc/xiaofeng":
            case "/d/luoyang/npc/xiaobanhe":
            case "/d/changbai/npc/huyidao":
            case "/clone/npc/han-yuanwai":
            case "/d/jiangzhou/npc/diaoyuren":
            case "/d/city/npc/identifier":
            case "/d/hangzhou/npc/han":
            case "/kungfu/class/murong/murongfu":
                destruct(inv[i]);
            }
        }
    }
}

