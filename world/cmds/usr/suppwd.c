// by canoe
#include <ansi.h>
inherit F_CLEAN_UP;
void create() { seteuid( getuid() ); }
int main(object me, string arg)
{
   object ob;
   if( me != this_player(1) ) return 0;
   ob = me->query_temp("link_ob");
   if( !ob ) 
   	return notify_fail("�㲻��������;������ģ������޸Ĺ������룡\n");
   while( ob && ob->is_character() ) ob = ob->query_temp("link_ob");
   write(HIG"\nע�⣺��������޸ġ��������ݡ���ɱ����Ҫ�������룻\n\n"NOR);
   write(HIR"      һ������²�����ģ���������Ʊ��档\n\n"NOR);
	
   if(ob->query("super_password"))
   {
   write("Ϊ�˰�ȫ���������������ԭ���Ĺ������룺");
   input_to("get_old_pass", 1, ob);
   }
   else
   {
   write("����û���趨�������룬���������趨��");
   input_to("get_new_pass",1,ob);
   }   
   return 1;
}

private void get_old_pass(string pass, object ob)
{
   string old_pass;
   write("\n");
   old_pass = ob->query("super_password");
   if( crypt(pass, old_pass)!=old_pass ) {
     write("�����������\n");
     MONITOR_D->report_system_object_msg(ob,"�޸Ĺ����������");
     return;
   }
   write("�������µĹ������룺");
   input_to("get_new_pass", 1, ob );
}

private void get_new_pass(string pass, object ob)
{
   write("\n");
        if( strlen(pass)<7 ) {
                write("������������Ҫ���߸��ַ���ɣ����������Ĺ������룺");
                input_to("get_new_pass", 1, ob);
                return;
        }
   write("\n��������һ���µĹ������룺");
   input_to("confirm_new_pass", 1, ob, crypt(pass,0));
}

private void confirm_new_pass(string pass, object ob, string new_pass)
{
   write("\n");
   if( crypt(pass, new_pass)!=new_pass ) {
     write("�Բ���������Ĺ������벢����ͬ������ʹ��ԭ���Ĺ������롣\n");
     return;
   }
   seteuid(getuid());
   if( !ob->set("super_password", new_pass) ) {
     write("����������ʧ�ܣ�\n");
     return;
   }

   ob->save();
   write("�����������ɹ���\n");
}

int help(object me)
{
   write(@HELP
ָ���ʽ : passwd
 
���ָ������޸��������������롣
 
HELP
    );
    return 1;
}
