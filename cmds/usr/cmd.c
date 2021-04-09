// lscmds.c

#include <ansi.h>

inherit F_CLEAN_UP;

int filter_list(mixed ob, string path, object user);
int sort_list(mixed ob1, mixed ob2);

int main(object me, string arg)
{
        int mark_loaded;
        int i, j, w, col;
        string dir;
        string path;
        string arg1;
        string _filename;
        int opt_l;
        mixed *file;
        string result;

        if (!arg || (arg !="usr" && arg !="std" && arg !="skill" &&arg !="stunt"))   
        return notify_fail(HIG"你想查看哪种（std, skill, usr, stunt）命令？请用cmd [种类]查看！\n"NOR);
        if (arg =="usr")     arg1 = "/cmds/usr/*.c";
        if (arg =="std")     arg1 = "/cmds/std/*.c";
        if (arg =="skill")   arg1 = "/cmds/skill/*.c";
        if (arg =="stunt")   arg1 = "/cmds/stunt/*.c";
        dir = resolve_path(me->query("cwd"), arg1);

        if (me != this_player())
                return notify_fail("不是当前使用者进行操作。\n");

        seteuid(getuid());
        if (file_size(dir) == -2 && dir[strwidth(dir) - 1] != '/') dir += "/";

        if (file_size(dir) == -2)
        {
                path = dir;
        } else
        {
                string *p;
                p = explode(dir, "/");
                if (sizeof(p) >= 2)
                {
                        p = p[0..sizeof(p) - 2];
                        path = "/" + implode(p, "/") + "/";
                } else
                        path = "/";
                p = 0;
        }

        file = get_dir(dir, -1);
        seteuid(geteuid(me));

        if (! sizeof(file))
        {
                if (file_size(dir) == -2)
                        return notify_fail(sprintf("目录(%s)是空的。\n", dir));
                else
                        return notify_fail(sprintf("没有这个目录(%s)。\n", dir));
        }

        file = filter_array(file, (: filter_list :), path, me);
        file = sort_array(file, (: sort_list :));

        i = sizeof(file);
        w = 0;
        while (i--)
        {
                if (file[i][1] == -2) file[i][0] += "/";
                if (strwidth(file[i][0])>w) w = strwidth(file[i][0]) + 1;
                file[i] += ({ MASTER_OB->valid_write(path + file[i][0], me, "ls") });
        }
        //result = "目录：" + path + "\n";

        result = "";
        if (arg =="usr")         result += HIY"\n你可以使用的玩家命令如下：";
        if (arg =="std")         result += HIY"\n你可以使用的标准命令如下：";
        if (arg =="skill")       result += HIY"\n你可以使用的武功相关命令如下：";
		if (arg =="stunt")       result += HIY"\n你可以使用的绝技相关命令如下：";
        result += sprintf(HIR"\n─────────────────────────────────────────\n"NOR);
        if (! sizeof(file))
        {
                write(sprintf("%s    没有任何档案。\n\n", result));
                return 1;
        }
        else
        {
                //col = 70 / (w+6);
                for(i=0, j = sizeof(file); i<j; i++)
                                {
                    sscanf(file[i][0], "%s.c",_filename);
                    result += sprintf(CYN "%s%-*s%s" NOR,WHT,
                    w + 1, _filename,(i%5==4)?"\n"NOR:""NOR);
                                }
        }
        result += sprintf(HIR"\n─────────────────────────────────────────\n"NOR);
        me->start_more(result);

        return 1;
}

int filter_list(mixed ob, string path, object user)
{
        return MASTER_OB->valid_read(path + ob[0], user, "ls");
}

int sort_list(mixed ob1, mixed ob2)
{
        if (ob1[1] == -2 && ob2[1] != -2)
                return -1;

        if (ob1[1] != -2 && ob2[1] == -2)
                return 1;

        return strcmp(ob1[0], ob2[0]);
}

int help(object me)
{
        write(@HELP
指令格式: cmd [命令种类]
 
列出你可以使用的命令，命令的种类有std，usr，skill三种。
  
HELP
        );
        return 1;
}

