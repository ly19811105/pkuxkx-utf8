// cat.c

inherit F_CLEAN_UP;

int help(object me);


int main(object me, string arg)
{       
	string *files;
	/*arg = "/d/fy/"; */
	string* str1;	
	 string dir;
     	object obj;
    	int size;
    	int i;
     	files= get_dir(arg);
     
	for(i=0; i<sizeof(files); i++) 
    	{
    	    size=sizeof(files[i]);
        	if(files[i][(size-2)..size]==".c"){
        		
				obj = find_object(arg+files[i]);
	if (!obj)
       obj = load_object(arg+files[i]);
    str1=explode(base_name(obj),"/");
    dir=sprintf("/temp/%s/%s.c",str1[1],str1[2]);
	write_file(dir,	
	  "#include \"../domain.h\"\n"+"inherit \"/std/room\";\n"+  "void setup(void) { \n\n"+  "add_area( str1[1]); \n"+
	  "set_short(\"" +  obj->query("short") + "\" );\n "+  "set_long(\"" +  obj->query("long") + "\" );\n "+ "set_exits(" +save_variable(  obj->query("exits")) + " );\n \n    }"   ,1);
	
			
			}	

        }   



	return 1;
}

int help(object me)
{
write(@HELP
[0;1;37m────────────────────────────────[0m
[0;1;36m巫师指令格式 : 	more <档案>|<物件名>[0m
[0;1;37m────────────────────────────────[0m   

分页显示档案内容。
 
more 模式下的指令:
q      : 离开 more.
b      : 显示前一页的内容.
[ENTER]: 显示下一页的内容.

[0;1;37m────────────────────────────────[0m 
HELP
    );
    return 1;
}
