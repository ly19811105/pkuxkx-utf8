// suicide.c

#define MAIL_FILE "/adm/tmp/mailuser"
#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    if (me->is_busy())
        return notify_fail("你上一个动作还没完成。\n");

    if (!arg)
    {
        write("你这样子只能投胎转世,系统需要你加入-f参数.\n");
        return 1;
    }
    if (wizardp(me)) return notify_fail("你有重任在身，不能自杀！\n");

    if (me->is_fighting()) return notify_fail("战斗中不能自杀。\n");

    if (arg != "-f") return notify_fail("自杀有两种，您是要永远死掉还是重新投胎？\n");

    if (!me->query_temp("allow_suicide") && me->query("mud_age") > 86400 * 16)
    {
        write("亲爱的" + me->query("name") + "，你已经是北大侠客行大家庭里不可缺少的一员了。失去你，我们大家都会伤心。\n");
        write("所以，请你认真地考虑考虑，真的要自杀吗？请跟在线wizard及以上巫师联系，看看他们有没有什么能帮你的。\n");
        write("如果你真的要离开这个美丽的世界，你的爱人会思念你，你的朋友会想念你。即便是你的敌人，也会感到痛心。\n");
        write("如果你只是想暂离一段时间，不防设置一个肯定记不起来的密码。等你想这里了，提供相关的资料，巫师帮你把密码重置。\n");
        return 1;
    }

    write(
       "如果您选择永远死掉的自杀方式，这个人物的资料就永远删除了，请务必\n"
       "考虑清楚，确定的话请输入您的密码：");
    input_to("check_password", 1, me, 1);
    return 1;
}

protected void check_password(string passwd, object me, int forever)
{
    object link_ob;
    string old_pass;

    link_ob = me->query_temp("link_ob");
    old_pass = link_ob->query("password");
    if (crypt(passwd, old_pass) != old_pass)
    {
        write("密码错误！\n");
        return;
    }

    if (forever)
    {
        tell_object(me, HIR "\n\n你决定要自杀了，如果十秒钟内不后悔，就真的永别了。\n后悔请输入 halt！\n\n\n" NOR);
        me->set_temp("suicide_countdown", 10);
        me->set_temp("pending/suicide", 1);
        me->start_busy("slow_suicide", "halt_suicide");
    }
}

int slow_suicide(object me)
{
    object link_ob, *inv;
    int stage, i;
    string user_file;
    int usernum;
    string add_cmd;

    stage = me->query_temp("suicide_countdown");
    me->add_temp("suicide_countdown", -1);
    if (stage > 1)
    {
        if (stage % 5 == 0)
            tell_object(me, HIR "你还有 " + stage + " 秒的时间可以后悔。\n" NOR);
        return 1;
    }

    link_ob = me->query_temp("link_ob");
    if (!link_ob)
        return 0;

    log_file("static/SUICIDE", sprintf("%s commits a suicide on %s\n", geteuid(me), ctime(time())));

    seteuid(getuid());

    if( !wizardp(me) )
    {
        inv = all_inventory(me);
        for(i=0; i<sizeof(inv); i++)
        {
            if( userp(inv[i]) ) inv[i]->move(environment(me));
        }
    }

    if ((me->query("combat_exp") > 50000) || (me->query("age") > 17))
    {
        cp(link_ob->query_save_file() + ".o", "/data/suicide-log/" + link_ob->query("id") + ".o");
        cp(me->query_save_file() + ".o", "/data/suicide-bak/" + link_ob->query("id") + ".o");
        write(HIR"你的资料已备份。\n"NOR);
    }
    CNAME_D->remove_cname(link_ob->query("id"));
    //删除邮箱
    if (me->query("havegot_mail"))
    {
        add_cmd = "adduser -kill " + me->query("id");
        write_file(MAIL_FILE, add_cmd + "\n");
        write_file(MAIL_FILE, me->query("id") + "\n");
        write_file(MAIL_FILE, "delete\n");
        write("邮箱已删除。\n");
    }
    GUIDER_D->del_app(me->query("id"));
    rm(link_ob->query_save_file() + ".o");
    rm(me->query_save_file() + ".o");
    write("好吧，永别了:(。\n");
    tell_room(environment(me), me->name() + "自杀了，以后你再也看不到这个人了。\n", ({me}));
//        log_file("static/suicide","来自 "+query_ip_number(me)+" 的玩家 "+me->query("id")+"("+me->query("name")+") 于 "+ctime(time())+" 自杀了。\n");
    CHANNEL_D->do_channel(this_object(), "rumor", me->name() + "自杀了。");
    if (user_file = read_file("/adm/etc/usernum", 1))
    {
        usernum = atoi(user_file);
        usernum--;
    }
    write_file("/adm/etc/usernum", "" + usernum, 1);
    me->start_busy(0);
    destruct(me);
    return 0;
}

int halt_suicide(object me)
{
    me->set_temp("pending/suicide", 1);
    write("你最后还是觉得生命可贵，打消了自杀的念头。\n");
    return 1;
}
int help(object me)
{
    write(@HELP
          指令格式: suicide [-f]

          如果因为某种原因你不想活了, 你可以选择自杀.
          自杀分两种:

          suicide    : 重新投胎
          suicide -f : 永远的除去玩家资料, 系统会要求你
          输入密码以确认身份.

          请慎重选择 :)

HELP);
return 1;
}
