// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
// user list
// by canoe 2001.08.24

int help(object me);
inherit F_CLEAN_UP;

int main(object me,string arg)
{
        object *ob;
        int i,flag;
        string str;
        if(arg && sscanf(arg,"number %s",str)==1)
        {
        ob=users();
        i = sizeof(ob);
        flag=1;
        while (i--)
        	{
        	if (str==file_name(ob[i]))
        		{
        		write(sprintf("�û��ļ���Ϊ[1;33m%s[m�������[1;33m%s [m�� \n",
        		file_name(ob[i]),ob[i]->query("id")));
        		flag=0;
        		}
        	}
       if(flag) return notify_fail("�Բ��𣬲��޴��ˡ�\n");
       return 1; 
	}
	else if(arg && sscanf(arg,"id %s",str)==1)
       {
     	if(!find_player(str))
       		return notify_fail("�Բ��𣬲��޴��ˡ�\n");
      	write(sprintf("���[1;33m%s[m���û��ļ�����[1;33m%s[m��\n",str,file_name(find_player(str))));
        return 1; 
	}
	else return help(me); 
}

int help(object me)
{
write(@HELP
[1;37m  
��    �ã��г���ҵ�user number��
[1;33m 
ָ���ʽ��ulist1 number <����ļ���>
         ulist1 id     <���id>
[1;37m        
���磺���canoe ��user number Ϊ/obj/user#1
[1;33m 
 1��  ��ulist1 number /obj/user#1 ,����ʾ 
      �û��ļ���Ϊ/obj/user#1�������canoe��
      
 2��  ��ulist1 id canoe ,����ʾ 
      ���canoe�û��ļ���Ϊ/obj/user#1��    
[0;1;37;34m       
�Ը�������Ϣ�Ƚ����á�
[m
HELP
    );
    return 1;
}
