//龙华天，领奖npc
//论坛奖励由巫师手工修改位于 FORUM_PATH 内的玩家积分文件
//notme 2004-05-31

inherit NPC;
#include <title.h>
#include <ansi.h>
#define HELPER_OF_THE_WEEK "/log/helpnew/helper_of_the_week"
#define HELPER_OF_THE_MONTH "/log/helpnew/helper_of_the_month"
#define HELPNEW_COUNT "/log/helpnew/helpnew_count"
#define FORUM_PATH "/log/forum/"
int reward();
int do_ling(string);
int month_reward();
int forum_reward();

void create()
{
    set_name("龙华天", ({ "long huatian", "long",}) );
    set("gender", "男性" );
    set("age", 42);
    set("long",
            "龙华天一身布衣，穿得甚为朴素，但是神态却是威武绝伦，大有燕赵遗风。\n");
    set("combat_exp", 2000000);
    set("shen_type", 1); 
    set("str", 30);
    set("int", 30);
    set("con", 30);
    set("dex", 30);
    set("max_qi", 4000);
    set("max_jing", 2000);
    set("neili", 3000);
    set("max_neili", 3000);
    set("jiali", 150);
    set_skill("force", 200);
    set_skill("cuff", 200);
    set_skill("dodge", 200);
    set_skill("parry", 200);
    set_skill("taxue-wuhen", 200);
    set_skill("jingang-quan", 200);
    set_skill("hunyuan-yiqi", 200);
    map_skill("cuff", "jingang-quan");
    map_skill("parry", "jingang-quan");
    map_skill("dodge", "taxue-wuhen");
    map_skill("force", "hunyuan-yiqi");
    set("attitude", "friendly");
    set("rank_info/respect", "龙庄主");
    set("inquiry", ([
                "奖励"    : (: reward :),
                "月度奖励": (: month_reward :),
                "论坛奖励": (: forum_reward :),
                ]));
    setup();
}

void init()
{
    object ob;
    
    ::init();
    add_action("do_ling", "ling");
            
    if( interactive(ob = this_player()) && !is_fighting() ) {
        call_out("greeting", 1, ob);
    }
}

void greeting(object ob)
{
    if( !ob || environment(ob) != environment() ) return;
        if( !this_object()->visible(ob)) return;
    switch( random(3) ) {
        case 0:
            say( "龙华天冲你一抱拳，这位" + RANK_D->query_respect(ob) + "，请了。\n");
            break;
        case 1:
            say( "龙华天说道：我辈习武，为的就是行侠仗义，除暴安良。\n");
            break;
        case 2:
            say( "龙华天慨然道：阁下有甚么困难，尽管向我等提出，凡为所能，无不尽心尽力。\n");
            break;
    }
}

int forum_reward()
{
    string filename;
    int forum_score;
    object me = this_player();
    
    filename = FORUM_PATH + me->query("id");
    forum_score = to_int(read_file(filename));
    say("龙华天告诉你：你的论坛积分是 " + forum_score + " 分\n");
    say("论坛积分奖励规则：\n再造丸  600\n菩提子  100\n九转熊胆丸  40\n");
    return 1;
}

int do_ling(string arg)
{
    string filename,my_id;
    int forum_score;
    object obj, me;
    mixed *award;
    mapping award_map = ([ ]);
    
    award = ({ 600 , __DIR__"obj/zaizaowan" });
    award_map += (["再造丸":award ]);
    award = ({ 100 , "/d/shaolin/obj/puti-zi" });
    award_map += (["菩提子":award ]);
    award = ({ 40 , "/d/xiangyang/npc/obj/shanlw" });
    award_map += (["九转熊胆丸":award ]);
    me = this_player();
    my_id = me->query("id");
    
    filename = FORUM_PATH + my_id;
    forum_score = to_int(read_file(filename));
    me->start_busy(2); //加入busy避免一些可能出现的bug 

    if(member_array(arg,keys(award_map)) == -1)
        return notify_fail("你想领什么奖励？\n");
    award = award_map[arg];    
    if(forum_score < to_int(award[0]) )
    {
        command("faceless " + my_id);
        return notify_fail("就你这么点积分，还想来骗吃骗喝不成？\n");
    }
    else
    {
        forum_score -= to_int(award[0]);
        say("你现在的积分是 " + forum_score + " 分。\n");
        write_file(filename,sprintf("%d\n",forum_score),1);
        obj = new(award[1]);
        if(obj->query("id") == "zaizao wan")
            obj->set("owner",my_id);
        obj->move(me);
        log_file("forum_reward",me->name() + "(" + my_id + ")于" + ctime(time()) + "领取了一颗" + obj->name() + "。\n");
        command("addoil " + my_id);
        command("say " + RANK_D->query_respect(me) +"继续努力啊！");
        shout(HIY"【论坛奖励】龙华天："+ me->query("name") + "由于积极在论坛发文，奖励 " + obj->name() + HIY" 一颗！\n" + NOR);
        return 1;
    }
}
    
int reward()
{
    string lines, my_id;
    string *line;
    object award;
    string VoteCount;
    object me = this_player();

    lines = read_file(HELPNEW_COUNT);
    if (lines)
    {
        line = explode(lines,"\n");
        VoteCount = line[0];
    }
    lines = read_file(HELPER_OF_THE_WEEK);
    if (lines)
    {
        line = explode(lines,"\n");
        my_id = line[0];
        if (me->query("id") == my_id)
            if (sizeof(line) > 1)
                message_vision("龙华天诧异地对$N说：我不是已经给过你奖励了吗？\n",me);
            else
            {
                award = new(__DIR__"obj/tianxiangyulu.c");
                award->set("owner",my_id);
                award->move(me);
                command("admire " + my_id);
                shout(HIY+ me->query("name") + "由于乐于助人，当选本周最受欢迎玩家，奖励天香玉露一瓶！\n" + NOR);
                say("龙华天从身旁木匣中小心取出一瓶天香玉露，交给你，叮嘱道：望你再接再厉，发扬我辈侠义精神！\n");
                write_file(HELPER_OF_THE_WEEK,my_id + "\n奖品已领取\n",1);
                me->set("job_title",HIW"本周最受欢迎玩家"NOR);
//title系统记录玩家title by seagate@pkuxkx
	              me->set_title(TITLE_HONOR, HIW"本周最受欢迎玩家"NOR);
                me->set("helpnew_count",VoteCount);
            }
        else
            say("龙华天拿出功劳簿翻了翻说道：本周最受欢迎玩家是：" + my_id + "！\n");

    }
    else
        say("龙华天长叹一口气，说道：本周没有最受新手欢迎的玩家！\n");
    return 1;
}

int month_reward()
{
    string lines, my_id;
    string *line;
    object award;
    string VoteCount;
    object me = this_player();

    lines = read_file(HELPNEW_COUNT);
    if (lines)
    {
        line = explode(lines,"\n");
        VoteCount = line[0];
    }

    lines = read_file(HELPER_OF_THE_MONTH);
    if (lines)
    {
        line = explode(lines,"\n");
        my_id = line[0];
        if (me->query("id") == my_id)
            if (sizeof(line) > 1)
                message_vision("龙华天诧异地对$N说：我不是已经给过你奖励了吗？\n",me);
            else
            {
                award = new(__DIR__"obj/zaizaowan.c");
                award->set("owner",my_id);
                award->move(me);
                command("admire " + my_id);
                shout(HIY+ me->query("name") + "由于乐于助人，当选本月最受欢迎玩家，奖励再造丸一颗！\n" + NOR);
                say("龙华天从身旁木匣中小心取出一颗再造丸，交给你，叮嘱道：望你再接再厉，发扬我辈侠义精神！\n");
                write_file(HELPER_OF_THE_MONTH,my_id + "\n奖品已领取\n",1);
                me->set("job_title",HIY"本月最受欢迎玩家"NOR);
//title系统记录玩家title by seagate@pkuxkx
	              me->set_title(TITLE_HONOR, HIY"本月最受欢迎玩家"NOR);
                me->set("helpnew_count",VoteCount);
            }
        else
            say("龙华天拿出功劳簿翻了翻说道：本月最受欢迎玩家是：" + my_id + "！\n");

    }
    else
        say("龙华天长叹一口气，说道：本月没有最受新手欢迎的玩家！\n");
    return 1;
}

