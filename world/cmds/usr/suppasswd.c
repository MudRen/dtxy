// identify.c  
// By Canoe 2001.03.16

inherit F_CLEAN_UP;
void create() { seteuid( getuid() ); }

int main(object me, string arg)
{
   object ob;

   if( me != this_player(1) ) return 0;

   ob = me->query_temp("link_ob");
   if( !ob ) return 0;
   while( ob && ob->is_character() ) ob = ob->query_temp("link_ob");
   if(ob->query("identify"))
   {
   write("Ϊ�˰�ȫ���������������ԭ������ݼ����룺");
   input_to("get_old_pass", 1, ob);
   }
   else
   {
   write("����û���趨��ݼ����룬���������趨��");
   input_to("get_new_pass",1,ob);
   }   
   return 1;
}

private void get_old_pass(string pass, object ob)
{
   string old_pass;
   write("\n");
   old_pass = ob->query("identify");
   if( crypt(pass, old_pass)!=old_pass ) {
     write("��ݼ��������\n");
     MONITOR_D->report_passwd_error(ob,"change identify");
     return;
   }
   write("�������µ���ݼ����룺");
   input_to("get_new_pass", 1, ob );
}

private void get_new_pass(string pass, object ob)
{
   write("\n");
        if( strlen(pass)<5 ) {
                write("��ݼ���������Ҫ������ַ���ɣ�������������ݼ����룺");
                input_to("get_new_pass", 1, ob);
                return;
        }
   write("\n��������һ���µ���ݼ����룺");
   input_to("confirm_new_pass", 1, ob, crypt(pass,0));
}

private void confirm_new_pass(string pass, object ob, string new_pass)
{
   write("\n");
   if( crypt(pass, new_pass)!=new_pass ) {
     write("�Բ������������ݼ����벢����ͬ������ʹ��ԭ������ݼ����롣\n");
     return;
   }
   seteuid(getuid());
   if( !ob->set("identify", new_pass) ) {
     write("��ݼ�������ʧ�ܣ�\n");
     return;
   }

   ob->save();
   write("��ݼ��������ɹ���\n");
}

int help(object me)
{
   write(@HELP
ָ���ʽ : passwd
 
���ָ������޸����������ݼ����롣
 
HELP
    );
    return 1;
}

