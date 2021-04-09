//create by glad

inherit F_CLEAN_UP;
int x;
void comp_subdir(string fn,string subdir);
int main(object me,string arg)
{
  string filename,dir,*file,*filter,subfile;
  int j,i,flag;
  
  x=0;
  //参数匹配
  if(!arg) return notify_fail("sfile <filename> <path>\n") ;
  if(sscanf(arg,"-s %s",arg)==1) flag=1;
  if(sscanf(arg,"%s %s",filename,dir)!=2) return notify_fail("Synatx error\n");

//  if(strsrch(filename,".c")==strwidth(filename)-2) 
//         filename=replace_string(filename,".c","");
//  filename+=".c";
//强制匹配！参数filename写全名。
  seteuid(geteuid(this_player(1)));
  dir = resolve_path(me->query("cwd"), dir);
  
  //目录初检

  if( file_size(dir)==-2 && dir[strwidth(dir)-1] != '/' ) 
              dir += "/";
  file = get_dir(dir);
  if( !sizeof(file) )
  {
            if (file_size(dir) == -2) 
                      return notify_fail("目录是空的。\n");
            else
                      return notify_fail("没有这个目录。\n");
  }
  

  //清除多余的"/"
  filter=explode(dir,"/");
  j=sizeof(filter);
  if(j>0)
  {   arg=(strsrch(filter[0],"*")==-1&&strsrch(filter[0],"?")==-1)?filter[0]:"";
            for(i=1;i<j;i++)
            {
               if(!strwidth(filter[i])) i++;
               else arg+="/"+filter[i];
             }
  } 
if(!flag)
write("在"+dir+"中搜索名为"+filename+"的文件或目录：\n");
else write("在"+dir+"及其子目录中搜索名为"+filename+"的文件或目录：\n");

  for(i=0;i<sizeof(file);i++)
{  
//      write(file[i]+"                     "+file_size(dir+file[i])+"\n");
      
      switch(file_size(dir+file[i]))
       {
           case -2:
               if(filename==file[i]) {write(dir+file[i]+"   :   目录\n");x++;}
//             write("\n"+file[i]+":目录\n");
               if(flag) comp_subdir(filename,dir+file[i]);
               break;
           case -1:
               write(file[i]+"   check error\n");break;
           default:
               if(filename==file[i]) {write(dir+file[i]+"\n");x++;}
       }
     
  }
  if(!x) write("没有搜索到此名文件或目录。\n");else write("搜索到"+x+"个结果。\n");
  return 1;
}
void comp_subdir(string fn,string subdir)
{
  string *files;int i,j;
  
  reset_eval_cost();
  subdir+="/";files=get_dir(subdir);
  if (!i=sizeof(files)) return;
//  write("检测子目录"+subdir+"\n");
  while(i)
  {
    i--;
    switch(file_size(subdir+files[i]))
    {
               
        case -2:
       // write("检测下一层子目录"+subdir+files[i]+"\n");
        comp_subdir(fn,subdir+files[i]);
        break;
        case -1:
        write(subdir+files[i]+"   check error\n");
        break;
        default:
        if(fn==files[i]) {write(subdir+files[i]+"\n");x++;}
    }
   }
   return;
}



int help()
{
   write("sfile filename path\n在path中搜寻所有名为filename的文件。\n如果加-s参数:sfile -s filename path则可以搜索子目录");
return 1; 
}

