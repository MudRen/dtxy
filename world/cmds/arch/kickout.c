#include "/doc/help.h"

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        if(!arg) return notify_fail("ָ�kick <living>\n");
        ob = find_player(arg);
        if (!ob) return notify_fail("�Ҳ��������ҡ�\n");
if(ob->query("id")=="bear"&&ob->query("name")=="С��")
return notify_fail("����ô���԰�С�ܴ����߳�ȥ�أ�\n");
        write("�����һ�Ž�"+ob->name()+"�ߵĻҷ����𣡣�\n");
        ob->set("kickout_time",time());
        ob -> save();
        seteuid(ROOT_UID);
        destruct(ob);
        return 1;
}

int help(object me)
{
   write(@HELP
ָ���ʽ: nuke <���>
��ĳ������߳����ƣ�����ʹ����һ��Сʱ�ڲ���������


HELP
   );
   return 1;
}
