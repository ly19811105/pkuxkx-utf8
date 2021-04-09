// 礼品店小姐
// 
// by bing

#include <ansi.h>

inherit NPC;

string *gifts = ({
	"common", "watch", "ring", "necklace", "flower", "clothing", "toy", "mirror", 
});

string *types = ({
	"cap", "weibo", "cloth", "surcoat", "yaodai", "huwan", "zhitao", "shoutao", "shoes",
});

void get_type(string);
int get_armor(string);
string checkstr(string);

void create()
{
        set_name("礼品店小姐", ({ "girl" }));
        set("long",
                "这是一位礼品店里卖礼品的小姐。她大概20岁左右，身材苗条，面带微笑，
正期待着你会选中一两样礼品。\n");
	set("gender", "女性" );
	set("age", 20);
	set("combat_exp", 5000000);
	set("attitude", "friendly");
        set("shen_type",1);set("score",200);setup();
}
void init()
{
	object ob;
	::init();
        add_action("do_ding", "make");
	add_action("do_dest", "destroy");
  	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
        if( !this_object()->visible(ob)) return;
        if (ob->query("gender")=="女性")
           {
	    command("xixi");
            command("say 这位姑娘，是不是想送点什么东西给他呀？");
        
           }
        else if (ob->query("gender")=="无性")
           {
	    command("xixi");
            command("say 难得公公也来照顾小店的生意，请慢慢看！");
           } 
	else {
            command("xixi");
	    command("say 这位先生，是不是看中了哪个姑娘？赶快给她送点东西吧！");
             }
           
}

int do_ding(string arg)
{
	string cat, color, name, id, desc, userid, isauto;
	
	object me;

	me = this_player();

	if ( !arg||sscanf(arg, "%s %s %s %s %s %s %s", cat, color, name, id, userid, desc, isauto) != 7)
		return notify_fail("指令格式：make <种类> <颜色> <中文名> <英文名> <要送的人的id> <描述> <是否可以自动保存(y/n)>\n
种类有普通(common)，手表(watch)，鲜花(flower)，项链(necklace)，戒指(ring)，衣服(clothing)，玩具(toy)，镜子(mirror)。\n");

	if ( member_array( cat, gifts ) == -1 )
		return notify_fail("小姐说道：「这里没有你想要的礼物呀！」\n");

	if ( !LOGIN_D->check_legal_id(id) )
		return notify_fail("小姐说道：「对不起，巫师不让我们作这种id的东西。」\n");

	if ( !LOGIN_D->check_legal_name(name) )
		return notify_fail("小姐说道：「对不起，巫师不让我们给礼品起这个名字。」\n");

	if ( !LOGIN_D->check_legal_describe(desc))
		return notify_fail("小姐说道：「对不起，ｂｕｇ已经改了，让你失望了。」\n");

	if (!find_player(userid))
		return notify_fail("小姐说道：「你要送礼物的人还没来呢！等他（她）来了再送吧！」\n");

	set("cat",cat);
	set("color",color);
	set("objname",name);
	set("objid",id);
	set("userid",userid);
	set("desc",desc);
	set("isauto",isauto);
	
	if (cat == "clothing")
	{
		set("clothing",1);
		message_vision("小姐说道：「你想送的衣物是帽子(cap)、围脖(weibo)、衣服(cloth)、
外套(surcoat)、腰带(yaodai)、护腕(huwan)、指套(zhitao)、手套(shoutao)还是鞋子(shoes)？\n",me);
		input_to( (:get_type:) );
		return 1;
	}
	if (cat == "toy")
	{
		set("toy",1);
		write("小姐说道：「请你写一下玩这件玩具时候的现象，玩的人的名字请用$N代替。」\n");
		input_to( (:get_armor:) );
		return 1;
	}
	write("小姐说道：「请你输入自己的id。」\n");
	input_to( (:get_armor:) );
	return 1;
}

int do_dest(string arg)
{
	string basefile;
	object obj,me;
	string *autoloads;

	me = this_player();
         if (!arg) return notify_fail("你要销毁什么？\n");

	if (objectp(obj=present(arg,me)))
	if (obj->query("auto_load"))
	if (obj->query("owner")== me->query("id"))
	{
		basefile = base_name(obj) + ".c" ;
		message_vision("小姐接过了" + obj->query("name") + "，把它扔进了废品堆里。\n",this_player());
		destruct(obj);
		if ( arrayp(autoloads = me->query("auto_load")) &&
      			  member_array( basefile, autoloads ) != -1 )
   		{
        		autoloads -= ({ basefile });
	       		me->set("auto_load", autoloads);
   		}
		rm(basefile);
		return 1;
	}
	else return notify_fail("小姐说道：「这东西不是你的吧？」\n");
	else return notify_fail("小姐说道：「这又不是可以自动保存的物品，扔了就是了。」\n");
	return notify_fail("你要销毁什么？\n");
}


void get_type(string arg)
{
		if ( member_array( arg, types ) == -1 )
		{
			write("小姐说道：「对不起，我们没有您要的种类的衣物，请您重新输入。」\n");
			input_to( (:get_type:) );
			return;
		}
		if (arg == "cap")
			set("type", "HEAD");
		else if (arg == "weibo")
			set("type", "NECK");
		else if (arg == "cloth")
			set("type", "CLOTH");
		else if (arg == "surcoat")
			set("type", "SURCOAT");
		else if (arg == "yaodai")
			set("type", "WAIST");
		else if (arg == "huwan")
			set("type", "WRISTS");
		else if (arg == "zhitao")
			set("type", "FINGER");
		else if (arg == "shoutao")
			set("type", "HANDS");
		else if (arg == "shoes")
			set("type", "BOOTS");
        write("小姐低下头在键盘上敲了几下，又抬起头来说道：「不知您要的衣服防御力应该是多少呢？我们这里可以作防御力1－100的衣物。」");


	input_to( (:get_armor:) );

	return;
}

int get_armor(string arg)
{
	string color,userid,cat,objarmor,action;
	string file, fname;
	object me,ob,armor;
	int intarmor;

	me = this_player();
	intarmor = 1;

	if (query("clothing"))
	{
                if (sscanf(arg,"%d",intarmor)!=1 || (intarmor<1) || (intarmor>100))
		{
			write("小姐说道：「对不起，你要的防御力超出了我们的制作能力。请您重新输入。」\n");
			input_to( (:get_armor:) );
			return 1;
		}
		else objarmor = arg;
	}
	if (query("toy"))
		action = arg;
	
	cat = query("cat");
	color = query("color");
	userid = query("userid");

	if (query("isauto") != "y")
		cat = cat+"2";	

	if ( !(file = read_file("/clone/gift/" + cat + ".c")) )
	{
		write("读文件出错。\n");
		return 1;
	}

        if (color == "$BLK$") file = replace_string(file, "HIR", "BLK");
        else
        if (color == "$RED$") file = replace_string(file, "HIR", "RED");
        else
        if (color == "$GRN$") file = replace_string(file, "HIR", "GRN");
        else
        if (color == "$YEL$") file = replace_string(file, "HIR", "YEL");
        else
        if (color == "$BLU$") file = replace_string(file, "HIR", "BLU");
        else
        if (color == "$MAG$") file = replace_string(file, "HIR", "MAG");
        else
        if (color == "$CYN$") file = replace_string(file, "HIR", "CYN");
        else
        if (color == "$WHT$") file = replace_string(file, "HIR", "WHT");
        else
        if (color == "$HIR$") file = replace_string(file, "HIR", "HIR");
        else
        if (color == "$HIG$") file = replace_string(file, "HIR", "HIG");
        else
        if (color == "$HIY$") file = replace_string(file, "HIR", "HIY");
        else
        if (color == "$HIB$") file = replace_string(file, "HIR", "HIB");
        else
        if (color == "$HIM$") file = replace_string(file, "HIR", "HIM");
        else
        if (color == "$HIC$") file = replace_string(file, "HIR", "HIC");
        else
        if (color == "$HIW$") file = replace_string(file, "HIR", "HIW");
        else
        if (color == "$NOR$") file = replace_string(file, "HIR", "NOR");
        else
          if (color == "$BNK$") file = replace_string(file, "HIR", "BNK");
        else
          if (color == "$REV$") file = replace_string(file, "HIR", "REV");

        else {	write("没有你想要的颜色！\n");
		return 1;
		}

		ob = new("/clone/gift/" + cat + ".c");
		if (me->query("balance") < (ob->query("value")*intarmor)) 
		{
			write("小姐说道：「对不起，您的存款不够！」\n");
			return 1;
		}
		else me->add("balance",-(ob->query("value")*intarmor));
		destruct(ob);


	file = replace_string(file, "名字", query("objname"));
	file = replace_string(file, "ＩＤ", query("objid"));
	file = replace_string(file, "LONG", query("desc"));
	file = replace_string(file, "OWNER", userid);
	if (query("clothing"))
	{
		file = replace_string(file, "WRISTS", query("type"));
		file = replace_string(file, "ARMOR", objarmor);
		delete("clothing");
	}
	if (query("toy"))
	{
		action=checkstr(action);
		file = replace_string(file,"ACTION",action);
		delete("toy");
	}
	seteuid(ROOT_UID);
	fname = "/data/giftmade/" + userid + time() + ".c";
	if (!write_file(fname, file))
	{
		write("无法写入文件。\n");
		return 1;
	}
	if ( !objectp(ob = new(fname)))
	{
		write("无法创建文件。\n");
		return 1;
	}
	message_vision("小姐嫣然一笑，将你要的礼品名输入电脑，然后抬起头来说道：「我们已经把"+query("objname")
+"送到了" + find_player(userid)->query("name") + "那里，谢谢惠顾！」\n", me);
	ob->move(find_player(userid));
	tell_object(find_player(userid),me->query("name") + "送了你一件礼物：" +
 ob->query("name") + "!\n");
	if (query("isauto") == "y")
	{
		find_player(userid)->add("auto_load", ({ base_name(ob) + ".c" }) );
	}
	else rm (base_name(ob) + ".c");
	return 1;
}

string checkstr(string arg)
{
	arg=replace_string(arg,"/","");
	arg=replace_string(arg,"'","");
	arg=replace_string(arg,"/*","");
	arg=replace_string(arg,"*","");
	arg=replace_string(arg,"~","");
	arg=replace_string(arg,"!","");
	arg=replace_string(arg,"|","");
	arg=replace_string(arg,"||","");
	arg=replace_string(arg,"&","");
	arg=replace_string(arg,"^","");
	arg=replace_string(arg,"%","");
	arg=replace_string(arg,";","");
	arg=replace_string(arg,")","");
	arg=replace_string(arg,"}","");
	arg=replace_string(arg,"]","");
	return arg;
}
