// destall.c

#include "/doc/help.h"

inherit F_CLEAN_UP;
int destfile(object me,string file);

int main(object me, string arg)
{
	int i, j; 
	string dir; 
	mixed *file; 
         

	if (!arg) return notify_fail("指令格式 : destdir 目录\n" );

	seteuid(ROOT_UID);

	dir = resolve_path(me->query("cwd"), arg); 
	if( file_size(dir)==-2 && dir[strwidth(dir)-1] != '/' ) dir += "/"; 
	file = get_dir(dir, -1); 
	if( !sizeof(file) ) 
	{if (file_size(dir) == -2) return notify_fail("目录是空的。\n"); 
	else 
	return notify_fail("没有这个目录。\n"); 
	} 

	i = sizeof(file); 

	while(i--) { 
	if (file[i][1]==-2) file[i][0] += "/"; 

	} 
	write("目录：" + dir + "\n"); 

	if (sizeof(file))
	{
		for(i=0, j = sizeof(file); i<j; i++) 
		{ 
                  if (file[i][1]!=-2 && sscanf(file[i][0], "%*s.c")  
                     && file[i][0][strwidth(file[i][0])-1]=="c"[0] 
                     && file[i][0][strwidth(file[i][0])-2]=="."[0]) 
                  destfile(me,dir+file[i][0]);  
                  else if (file[i][1]==-2) call_other(__FILE__,"main", me,dir+file[i][0]); 
		}
	}
	else write("    没有任何档案。\n"); 
	write("\n");


	return 1;
}

int destfile(object me,string file) 
{
	int num;
	object* objs;
	int i;
	num=0;
	objs = children(file);
	if(arrayp(objs) && sizeof(objs) > 0)
	{
		for(i=0;i<sizeof(objs);i++)
		{
			if(clonep(objs[i]))
			{
				destruct(objs[i]);
				num++;
			}
		}
	}

	if(num > 0)
		printf("%d objects are destructed for %s.\n",num,file);
	return num;
}


int help(object me)
{
	write(@HELP
指令格式 : destdir 目录
清除某目录下所有的clone对象。
HELP
    );
    return 1;
}
