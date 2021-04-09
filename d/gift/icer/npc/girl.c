// girl.c 赌场服务员

inherit NPC;

void create()
{
          set_name("彩票小姐", ({ "girl" }) );
         set("gender", "女性" );
        set("age", 19);
        set("long",
                 "她打扮得花枝招展，不时向你抛个媚眼，试图吸引你多买点彩票，
你不禁意欲将计就计了......\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        setup();
        set("chat_chance", 3); 
        set("chat_msg", ({
"小姐说道：「来吧！买点彩票！支持mud福利事业！」\n",
"小姐作神秘状说道：「昨天刚刚有个人中了头奖呢！」\n",
        }));
}

void init()
{       
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_buy","buy");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) ) {
                case 0:
                          say( "小姐招呼道：「这位" + RANK_D->query_respect(ob)
                                  + "，来买张彩票吧！」\n");
                        break;
                case 1:
                          say( "小姐微笑着说：「" + RANK_D->query_respect(ob)
                                 + "，买张彩票撞个头彩！」\n");
                        break;
        }
}

int do_buy(string arg)
{
        object me;
        object caipiao;
        string strName,fName,file,numberfile,number;
        int i;
        me = this_player();
        
        if (arg != "jingli" && arg != "neili" && arg != "rongmao")      
                return notify_fail("请打buy jingli 或buy neili 或buy rongmao\n");
        if (arg == "jingli")
        {
                if (me->query("max_jingli") < 30)
                        return notify_fail("对不起，您的最大精力不够买一张彩票的！\n");
        }
        if (arg == "neili")
        {
                if (me->query("max_neili") < 30)
                        return notify_fail("对不起，您的最大内力不够买一张彩票的！\n");
        }
        if (arg == "rongmao")
        {
                if (me->query("per") < 5)
                        return notify_fail("对不起，您的尊容还不够买一张彩票的！\n");
        }
        if (this_object()->is_busy())
            return notify_fail("对不起，我正忙着呢！\n");
        this_object()->start_busy(4);
        if (me->query("mud_age")<36000)
            return notify_fail("对不起，至少要在线10小时以上才可以买彩票。\n");
        if ( !(file = read_file("/d/gift/icer/obj/caipiao.c")) )
        {
                write("读文件出错。\n");
                return 1;
        }
        
        if (arg == "jingli")
        {
                numberfile = read_file("/d/gift/icer/obj/caipiao/jlcp");
                sscanf(numberfile,"%d",i);
                i++;
                write_file("/d/gift/icer/obj/caipiao/jlcp",sprintf("%d",i),1);
                strName = "精力彩票";
                  me->add("max_jingli",-30);                    write("你付出了30点最大精力的代价。\n");
        }
        else    if (arg == "neili")
                {
                        numberfile = read_file("/d/gift/icer/obj/caipiao/nlcp");
                        sscanf(numberfile,"%d",i);
                        i++;
                        write_file("/d/gift/icer/obj/caipiao/nlcp",sprintf("%d",i),1);
                        strName = "内力彩票";
                         me->add("max_neili",-30);
                          write("你付出了30点最大内力的代价。\n");
                }
                else    if (arg == "rongmao")
                        {
                                numberfile = read_file("/d/gift/icer/obj/caipiao/rmcp");
                                sscanf(numberfile,"%d",i);
                                i++;
                                write_file("/d/gift/icer/obj/caipiao/rmcp",sprintf("%d",i),1);
                                strName = "容貌彩票";
                                me->add("per",-5);
                                write("你付出了5点容貌的代价。\n");
                        }

        file = replace_string(file, "名字", strName);
        file = replace_string(file, "Number",sprintf("%d",i) + "号");
        seteuid(ROOT_UID);
        fName = "/d/gift/icer/obj/caipiao/" + me->query("id") + time() + ".c";
        if (!write_file(fName, file))
        {
                write("无法写入文件。\n");
                return 1;
        }
        if ( !objectp(caipiao = new(fName)))
        {
                write("无法创建文件。\n");
                return 1;
        }
    message_vision("小姐高高兴兴地给了" + this_player()->query("name") + "一张" + strName + "，说道：「谢谢惠顾！猪你好运！」\n", this_player());
        caipiao->move(me);
        return 1;
}


