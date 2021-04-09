inherit F_CLEAN_UP;
//create by glad
int main(object me,string arg)
{
   string cmd;
  if(!arg) return notify_fail("你要搜寻哪个命令？\n");
   cmd=me->find_command(arg);
   if(!cmd) return notify_fail("没有这个命令。\n");
   cmd+=".c";
   write("你使用的"+arg+"这个指令的源文件是：\n"+cmd+"\n");
   return 1;
}
int help(object me)
{
write(@HELP
指令格式 : fcmd <command>
这个命令显示你调用的command的源文件。

HELP
    );
    return 1;
}
