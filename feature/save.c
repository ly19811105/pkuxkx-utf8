// save.c

//2008/10/25    boost 添加save profile

#include <ansi.h>

//#define SAVEPROFILE 1   //开启save profile
//#define SAVEVERIFY  1   //开启save verify

#ifdef SAVEPROFILE

#define SAVE_PROFILE  "/u/boost/save_profile_npc.c"

int print_log();

int reset_log()
{
    object save_npc = find_object(SAVE_PROFILE);
    if (!save_npc)
    {
        save_npc = load_object(SAVE_PROFILE);
        save_npc->move("/d/wizard/mingren");  //放在名人堂，不容易被刷新和kill掉
    }
    save_npc->set_temp("time", time());
    save_npc->delete_temp("profile");
    return 1;
}

int log_save()
{
    string verb = query_verb(), id;

    object save_npc = find_object(SAVE_PROFILE);
    if (!save_npc)
        return 0;

    if (this_player())
        id = this_player()->query("id");

    if (verb == "save")
    {
        save_npc->add_temp("profile/pas/" + id, 1);
        save_npc->add_temp("profile/pac", 1);
    }
    else if (verb)
    {
        save_npc->add_temp("profile/pps/" + id, 1);
        save_npc->add_temp("profile/ppv/" + verb, 1);
        save_npc->add_temp("profile/ppc", 1);
    }
    else
        save_npc->add_temp("profile/sc", 1);
    return 1;
}

//打印map里所有元素，如果指定print_half，则只打印value超过最大值一半的元素
string print_map(mapping m, int print_half)
{
    mixed *key, *value;
    string msg = "";
    int i, half = 0;
    if (!m) return "";
    key = keys(m);
    value = values(m);
    if (print_half)
    {
        for (i = 0; i < sizeof(key); i++)
        {
            if (half < value[i] && key[i] != 0)   // sleep时key是0,太多了
                half = value[i];
        }
        half = half / 2;   
    }
    for (i = 0; i < sizeof(key); i++)
    {
        if (print_half && value[i] < half)
            continue;
        msg += key[i] + "\t\t" + value[i] + "\n";
    }
    return msg;
}


int print_log()
{
    object save_npc = find_object(SAVE_PROFILE);
    if (!save_npc)
        return 0;

    write("统计时间间隔：" + (time() - save_npc->query_temp("time")) + "s。\n");
    write("系统调用共：" + save_npc->query_temp("profile/sc") + "次（不准，不知道原因，不过应该可以忽略）。\n\n");
    write("玩家主动调用共：" + save_npc->query_temp("profile/pac") + "次（来自于玩家save命令）（玩家 vs 次数）（只显示超过最大值1/2的项）：\n");
    write(print_map(save_npc->query_temp("profile/pas"), 1));

    write("\n玩家被动调用共：" + save_npc->query_temp("profile/ppc") + "次（来自于玩家非save命令）（玩家 vs 次数）（只显示超过最大值1/2的项）。\n");

    write(print_map(save_npc->query_temp("profile/pps"), 1));


    write("玩家被动调用共：" + save_npc->query_temp("profile/ppc") + "次（来自于玩家非save命令）（命令 vs 次数）。\n");
    write(print_map(save_npc->query_temp("profile/ppv"), 0));

    write("\n\n");

    return 1;

}

#endif

#ifdef SAVEVERIFY
void write_fail_message(string msg)
{
    string verb = query_verb();
    object me = this_player();
    string smsg;
    if (me)
        smsg = me->query("id");
    else
        smsg = "Unkown";

    smsg += " 在命令 " + verb + "中动调用save失败：" + msg + "time:" + time();  //加上时间避免重复chat同一内容

//    write(HIR"" + msg + HIW"并请立即联系wiz，保留当前日志及操作。\n"NOR);
    CHANNEL_D->do_channel(this_object(), "sys", smsg);
}

int save_verify(string file)
{
    int last_modify_time, ret;

    mixed s = stat(file+ __SAVE_EXTENSION__);
    if (sizeof(s) == 0)
    {
        write_fail_message(file + "上次存档丢失，尝试保存...");
    }
	else
    	last_modify_time = s[1];

    ret = save_object(file);

    s = stat(file+ __SAVE_EXTENSION__);
    if (sizeof(s) == 0)
    {
        write_fail_message(file+"保存失败，存档丢失！请稍候尝试再次保存。 ");
        return 0;
    }

    if ((last_modify_time == s[1]) && (last_modify_time != time()))
    {
        write_fail_message(file+"保存失败，存档无法写入！请稍候尝试再次保存。 ");
        return 0;
    }

    return ret;
}
#endif

int save()
{
    string file;

    if( stringp(file = this_object()->query_save_file()) ) {
        assure_file(file+ __SAVE_EXTENSION__);

#ifdef SAVEPROFILE
        log_save();
#endif


#ifdef SAVEVERIFY
	if (userp(this_object()))
        return save_verify(file);
    else
    	return save_object(file);
#else
        return save_object(file);
#endif

    }
    return 0;
}

int restore()
{
    string file;

    if( stringp(file = this_object()->query_save_file()) )
//  return restore_object(file, 1);
        return restore_object(file+".o");
    return 0;
}

