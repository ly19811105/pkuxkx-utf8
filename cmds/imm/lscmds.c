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
		string _filename;
        int opt_l;
        mixed *file;
        string result;

		arg = "/cmds/std/*.c";

        dir = resolve_path(me->query("cwd"), arg);

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

        if (! sizeof(file))
        {
                write(sprintf("%s    没有任何档案。\n\n", result));
                return 1;
        }

        {
                //col = 70 / (w+6);
                for(i=0, j = sizeof(file); i<j; i++)
				{
					sscanf(file[i][0], "%s.c",_filename);
                    result += sprintf(CYN "%s%-*s%s" NOR,
                        //(file[i][3] ? (file[i][1] == -2 || find_object(path + file[i][0])? WHT:GRN) : HIR),
						WHT,
                        w + 1, _filename,
                        "\n");
				}
        }
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
指令格式: lscmds
 
列出目录下所有的子目录及档案, 如果没有指定目录, 则列出所在目录
的内容，所列出的档案中，白色的代表路径或是已经载入的物件对应的
文件，正常色的代表普通的文件。红色则表示你对该目录或文件没有写
入权限。-l参数可以列出详细资料。
 
范例:
'lscmds' 会列出所有位於根目录下的档案及子目录。
 
HELP
        );
        return 1;
}


