// qkill.c
// tomcat
// ��ѯ��ǰ����������

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string yaos ,yaos_status;
	int yaos_num,t ;
	
        if (!me->query_temp("mieyao/ob")){
            write("\n��Ŀǰû����������\n");
            return 1;
           }  
	yaos = me->query("mieyao/name");
	yaos_num = me->query_temp("mieyao/level"); 
	yaos_status = "�Ѿ����";

         if( (t=(int)me->query("mieyao/time_start")) &&
		!me->query("mieyao/done")) {
	    if(t<=time() &&
		    time()<t+1800) {
		yaos_status="û�����"; }}

	
	write("\n�㵱ǰ������������:"+yaos);
	write("\n�ڸ�"+yaos_num+"�� "+ yaos_status+"\n");
	return 1;
}

