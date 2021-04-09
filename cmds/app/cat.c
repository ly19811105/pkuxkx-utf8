// cat.c
inherit F_CLEAN_UP;

int main(object me, string arg)
{
    string file;
    object ob;
    seteuid(geteuid(me));
    if (!arg) return notify_fail("指令格式 : cat <档名>|<物件名> \n");
    file = resolve_path(me->query("cwd"), arg);
    if( file_size(file) < 0 ) {
        ob = present(arg, me);
        if( !ob ) ob = present(arg, environment(me));
        if( !ob ) return notify_fail(file+" 这个档案不存在。\n");
        file = base_name(ob) + ".c";
    }
    cat(file);
    return 1;
}

int help(object me)
{
write(@HELP
指令格式 : cat <档案>|<物品名>

此指令可让你直接读取某档案之程式。
HELP
    );
    return 1;
}
